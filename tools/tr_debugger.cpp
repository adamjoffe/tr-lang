#include "tr_debugger.h"

#include <ctime>

namespace TR {

    TRDebugger::TRDebugger(TRInterpreter& driver, std::string& loc) : 
        driver(driver) {
            driver.existAndMake(loc);

            // get timestamp for the file
            time_t rawtime;
            char buffer [512];
            time(&rawtime);
            strftime(buffer,512,"%F-%H-%M-%S",localtime(&rawtime));

            dout = new std::ofstream((loc + "debugger-" + buffer + ".log").c_str());
        }

	void TRDebugger::start_node(ASTNode* ast) {
        // note data values at start of a node
        ast->visit(this,&pre);
	}

    void TRDebugger::end_node(ASTNode* ast) {
        // note data values at end of a node
        ast->visit(this,&post);
    }

    void TRDebugger::notify_before() {
        // output start of execution
        exe_cyles();

        // set scope level back to intial incase exited outside of scope level
        scope_level = 0;

        // go through all global variables and check values
        // check TR defined variables and built-in ones
        for (size_t i = 0; i < driver.symtbl->getTable().size() ; ++i) {
            for (auto it = driver.symtbl->getTable()[i].begin(); it != driver.symtbl->getTable()[i].end(); ++it) {
                // only check the built in variables
                if (it->second->dt == DeclType::BIVAR_DECL) {
                    it->second->visit(this,&in);
                }
            }
            ++scope_level;
        }

        // reset scope before exiting global inits
        scope_level = 0;

    }
        
    void TRDebugger::notify_after() {
        ++exe_counter; // increment number of executions
    }

    void TRDebugger::notify_exit() {
        // do nothing
    }

    /// Visitor function definitions
    // START INCLUSION POINT
    ASTNode* TRDebugger::visitActionList(ActionList* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitActionStmt(ActionStmt* ast, ASTNode* n) {
        // only do this if called within debugger, since outside calls
        // from the attachable interface all pass ASTDummys
        if (n == nullptr) {
            std::cout << "action visit success" << std::endl;
            return ast->rgs->visit(this,nullptr);
        }
    	return nullptr;
    }

    ASTNode* TRDebugger::visitArg(Arg* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitArgList(ArgList* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitAssignStmt(AssignStmt* ast, ASTNode* n) {
        std::string dname = dynamic_cast<ASTDummy*>(n)->name;

        // Check symbole table
        std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
        ASTDecl* vdecl = nullptr;
        // attempt to retrieve para table first, then from global scope
        if (vdecl = driver.paratbl->retrieve(vname)) {
            // NOP
        } else if (vdecl = driver.symtbl->retrieve(vname)) {
            // NOP
        }
        ASTVariable* avar = dynamic_cast<ASTVariable*>(vdecl);

        GVar* storeval = avar->getValue();
        if (storeval) {
            variable_state(dname, vname, TypeToString(storeval), 
                (storeval->t == Type::NULL_T || storeval->t == Type::VOID_T) ? "noval" : ValToString(storeval), 
                "TR", std::to_string(scope_level), ast->src_code);
        } else {
            variable_state(dname, vname, "null", "noval", "TR", std::to_string(scope_level), ast->src_code);
        }
    	return nullptr;
    }

    ASTNode* TRDebugger::visitBBCall(BBCall* ast, ASTNode* n) {
        std::string dname = dynamic_cast<ASTDummy*>(n)->name;
        std::string mod = dynamic_cast<Ident&>(*(ast->mod.get())).name;
        std::string dstruct = dynamic_cast<Ident&>(*(ast->dstruct.get())).name;
        std::string func = dynamic_cast<Ident&>(*(ast->func.get())).name;
        if (dname == post.name) {
            std::string fname = "blackboard." + mod + "." + dstruct + "." + func;
            std::string trbi = "TR";
            function_return(dname, fname, TypeToString(ast->val), 
                    (ast->val->t == Type::NULL_T || ast->val->t == Type::VOID_T) ? "noval" : ValToString(ast->val), 
                    trbi, ast->src_code);
        }
    	return nullptr;
    }

    ASTNode* TRDebugger::visitBIVarDecl(BIVarDecl* ast, ASTNode* n) {
        std::string dname = dynamic_cast<ASTDummy*>(n)->name;
        std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
        GVar* storeval = ast->getValue();
        if (storeval) {
            variable_state(dname, vname, TypeToString(storeval), 
                (storeval->t == Type::NULL_T || storeval->t == Type::VOID_T) ? "noval" : ValToString(storeval), 
                "TR", std::to_string(scope_level), ast->src_code);
        } else {
            variable_state(dname, vname, "null", "noval", "TR", std::to_string(scope_level), ast->src_code);
        }
    	return nullptr;
    }

    ASTNode* TRDebugger::visitBinaryExpr(BinaryExpr* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitBlackboardDecl(BlackboardDecl* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitCond(Cond* ast, ASTNode* n) {
        std::string dname = dynamic_cast<ASTDummy*>(n)->name;
        // only post
        if (dname == post.name) {
            std::string cname = dynamic_cast<Ident&>(*(ast->id.get())).name;
            // visit the action statement to get the name of the regression through returning of a ASTDummy
            ASTNode* dummy = ast->as->visit(this,nullptr);
            std::string rname = dynamic_cast<ASTDummy*>(dummy)->name;
            cond_rgr(dname, cname, rname, ast->src_code);
            delete dummy; // delete since allocated it to the heap in regressionstmt visitor
        }
    	return nullptr;
    }

    ASTNode* TRDebugger::visitCondStmt(CondStmt* ast, ASTNode* n) {
        std::string dname = dynamic_cast<ASTDummy*>(n)->name;
        // only post if true condition
        if (dname == post.name) {
            if (ast->as != nullptr) {
                ASTNode* dummy = ast->as->visit(this,nullptr);
                std::string rname = dynamic_cast<ASTDummy*>(dummy)->name;
                cond_rgr(dname, "true", rname, ast->src_code);
                delete dummy; // delete since allocated it to the heap in regressionstmt visitor
            }
        }
    	return nullptr;
    }

    ASTNode* TRDebugger::visitElifStmt(ElifStmt* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitElseStmt(ElseStmt* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitEmptyActionList(EmptyActionList* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitEmptyArgList(EmptyArgList* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitEmptyParaList(EmptyParaList* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitEmptyTRProgList(EmptyTRProgList* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitExitStmt(ExitStmt* ast, ASTNode* n) {
        std::string dname = dynamic_cast<ASTDummy*>(n)->name;
        // ignore pre since not needed, only care about when thrown
        if (dname == post.name) {
            exit_clause(dname, std::to_string(ast->etr.code), ast->etr.msg, ast->src_code);
        }      
    	return nullptr;
    }

    ASTNode* TRDebugger::visitExprStmt(ExprStmt* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitFCall(FCall* ast, ASTNode* n) {
        std::string dname = dynamic_cast<ASTDummy*>(n)->name;
        std::string fname = dynamic_cast<Ident&>(*(ast->id.get())).name;
        if (ASTDecl* vdecl = driver.symtbl->retrieve(fname)) {
            std::string trbi;
            if (vdecl->dt == DeclType::BIFUNC_DECL) {
                trbi = "BI";
            } else if (vdecl->dt == DeclType::FUNC_DECL || vdecl->dt == DeclType::TR_DECL) {
                trbi = "TR";
            }
            function_return(dname, fname, TypeToString(ast->val), 
                    (ast->val->t == Type::NULL_T || ast->val->t == Type::VOID_T) ? "noval" : ValToString(ast->val), 
                    trbi, ast->src_code);
        }
    	return nullptr;
    }

    ASTNode* TRDebugger::visitFuncDecl(FuncDecl* ast, ASTNode* n) {
        std::string dname = dynamic_cast<ASTDummy*>(n)->name;
        std::string fname = dynamic_cast<Ident&>(*(ast->id.get())).name;
        if (dname == pre.name) {
            ++scope_level;
            // note scope change
            new_scope(dname, fname, "FD", std::to_string(scope_level), ast->src_code);

            // get param values
            std::vector<std::string> vname;
            std::vector<std::string> type;
            std::vector<std::string> val;
            for (size_t i = 0; i < ast->params.size(); ++i) {
                vname.push_back(dynamic_cast<Ident&>(*(ast->params[i]->id.get())).name);
                GVar* storeval = ast->params[i]->getValue();
                type.push_back(TypeToString(storeval));
                val.push_back(ValToString(storeval));
            }
            param_values(dname, fname, vname, type, val, ast->src_code);
        } else if (dname == post.name) {
            --scope_level;
            // note scope change
            new_scope(dname, fname, "FD", std::to_string(scope_level), ast->src_code);
        }
    	return nullptr;
    }

    ASTNode* TRDebugger::visitIdent(Ident* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitIfStmt(IfStmt* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitInitExpr(InitExpr* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitLiteralExpr(LiteralExpr* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitLogicStmt(LogicStmt* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitOnceDecl(OnceDecl* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitOperator(Operator* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitOtherwiseStmt(OtherwiseStmt* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitParaDecl(ParaDecl* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitParaList(ParaList* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitRegressionStmt(RegressionStmt* ast, ASTNode* n) {
        // only do this if called within debugger, since outside calls
        // from the attachable interface all pass ASTDummys
        if (n == nullptr) {
            // get dummy name from id
            ASTDummy* rname = new ASTDummy(dynamic_cast<Ident&>(*(ast->id.get())).name);
            return rname; // pass it back
        }
    	return nullptr;
    }

    ASTNode* TRDebugger::visitReturnStmt(ReturnStmt* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitTRNode(TRNode* ast, ASTNode* n) {
        std::string dname = dynamic_cast<ASTDummy*>(n)->name;
        std::string fname = dynamic_cast<Ident&>(*(ast->id.get())).name;
        if (dname == pre.name) {
            ++scope_level;
            // note scope change
            new_scope(dname, fname, "TRD", std::to_string(scope_level), ast->src_code);

            // get param values
            std::vector<std::string> vname;
            std::vector<std::string> type;
            std::vector<std::string> val;
            for (size_t i = 0; i < ast->params.size(); ++i) {
                vname.push_back(dynamic_cast<Ident&>(*(ast->params[i]->id.get())).name);
                GVar* storeval = ast->params[i]->getValue();
                type.push_back(TypeToString(storeval));
                val.push_back(ValToString(storeval));
            }
            param_values(dname, fname, vname, type, val, ast->src_code);
        } else if (dname == post.name) {
            --scope_level;
            // note scope change
            new_scope(dname, fname, "TRD", std::to_string(scope_level), ast->src_code);
        }
    	return nullptr;
    }

    ASTNode* TRDebugger::visitTRProgList(TRProgList* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitTRProgram(TRProgram* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitUnaryExpr(UnaryExpr* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRDebugger::visitVarDecl(VarDecl* ast, ASTNode* n) {
        std::string dname = dynamic_cast<ASTDummy*>(n)->name;
        std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
        std::string type;
        std::string val;
        if (ast->val) {
            variable_state(dname, vname, TypeToString(ast->val), 
                (ast->val->t == Type::NULL_T || ast->val->t == Type::VOID_T) ? "noval" : ValToString(ast->val), 
                "TR", std::to_string(scope_level), ast->src_code);
        } else {
            variable_state(dname, vname, "null", "noval", "TR", std::to_string(scope_level), ast->src_code);
        }
    	return nullptr;
    }

    ASTNode* TRDebugger::visitVarExpr(VarExpr* ast, ASTNode* n) {
    	return nullptr;
    }

    // END INCLUSION POINT

}
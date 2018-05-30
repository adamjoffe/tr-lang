#include "tr_profiler.h"

#include <ctime>
#include <cstdlib>

namespace TR {

    TRProfiler::TRProfiler(TRInterpreter& driver, std::string& loc, int yr) : 
        driver(driver), yield_rate(yr),
        exe_counter(0), num_outputs(0) {
            driver.existAndMake(loc);

            // get timestamp for the file
            time_t rawtime;
            char buffer [512];
            time(&rawtime);
            strftime(buffer,512,"%F-%H-%M-%S",localtime(&rawtime));

            pout = new std::ofstream((loc + "profiler-" + buffer + ".log").c_str());
            // output header
            *pout << "Source code | Num Executions | Clock Ticks | Seconds | Avg Time Per Execution"
                  << std::endl;
        }

	void TRProfiler::start_node(ASTNode* ast) {
        ast->tmp_c = clock();
	}

    void TRProfiler::end_node(ASTNode* ast) {
        ast->exe_time += clock() - ast->tmp_c;
        ++ast->count; // increment count for this node
    }

    void TRProfiler::notify_before() {
        // NOP
    }
        
    void TRProfiler::notify_after() {
        ++exe_counter; // increment number of executions first since notified after
        // output based on yield rate set
        if (yield_rate != 0 && (exe_counter % yield_rate == 0)) {
            print_profile();
        }
    }

    void TRProfiler::notify_exit() {
        ++exe_counter;
        print_profile();
    }

    void TRProfiler::print_profile() {
        // visit entire tree and output profiler information for
        // required nodes
        ++num_outputs; // increment number of times output
        driver.info("Profiler Outputing #" + num_outputs);
        *pout << "-------------Profiler Out " << num_outputs << "-------------" << std::endl;
        driver.ast->visit(this,nullptr);
    }

    /// Visitor function definitions
    // START INCLUSION POINT
    ASTNode* TRProfiler::visitActionList(ActionList* ast, ASTNode* n) {
        ast->s->visit(this, nullptr);
        ast->al->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitActionStmt(ActionStmt* ast, ASTNode* n) {
        ast->al->visit(this, nullptr);
        ast->rgs->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitArg(Arg* ast, ASTNode* n) {
        ast->e->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitArgList(ArgList* ast, ASTNode* n) {
        ast->a->visit(this, nullptr);
        ast->al->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitAssignStmt(AssignStmt* ast, ASTNode* n) {
        display_node(ast);
        ast->id->visit(this, nullptr);
        ast->e->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitBBCall(BBCall* ast, ASTNode* n) {
        display_node(ast);
        ast->mod->visit(this, nullptr);
        ast->dstruct->visit(this, nullptr);
        ast->func->visit(this, nullptr);
        ast->al->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitBIVarDecl(BIVarDecl* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRProfiler::visitBinaryExpr(BinaryExpr* ast, ASTNode* n) {
        ast->e1->visit(this, nullptr);
        ast->o->visit(this, nullptr);
        ast->e2->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitBlackboardDecl(BlackboardDecl* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRProfiler::visitCond(Cond* ast, ASTNode* n) {
        display_node(ast);
        ast->id->visit(this, nullptr);
        ast->e->visit(this, nullptr);
        ast->as->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitCondStmt(CondStmt* ast, ASTNode* n) {
        if (ast->as != nullptr) {
            display_node(ast);
            ast->as->visit(this, nullptr);
        } else {
            ast->c->visit(this, nullptr);
            ast->cs->visit(this, nullptr);
        }
    	return nullptr;
    }

    ASTNode* TRProfiler::visitElifStmt(ElifStmt* ast, ASTNode* n) {
        display_node(ast);
        ast->e->visit(this, nullptr);
        ast->s->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitElseStmt(ElseStmt* ast, ASTNode* n) {
        display_node(ast);
        ast->s->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitEmptyActionList(EmptyActionList* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRProfiler::visitEmptyArgList(EmptyArgList* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRProfiler::visitEmptyParaList(EmptyParaList* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRProfiler::visitEmptyTRProgList(EmptyTRProgList* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRProfiler::visitExitStmt(ExitStmt* ast, ASTNode* n) {
        display_node(ast);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitExprStmt(ExprStmt* ast, ASTNode* n) {
        display_node(ast);
        ast->e->visit(this,nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitFCall(FCall* ast, ASTNode* n) {
        display_node(ast);
        ast->id->visit(this, nullptr);
        ast->al->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitFuncDecl(FuncDecl* ast, ASTNode* n) {
        display_node(ast);
        ast->id->visit(this, nullptr);
        ast->pl->visit(this, nullptr);
        ast->s->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitIdent(Ident* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRProfiler::visitIfStmt(IfStmt* ast, ASTNode* n) {
        display_node(ast);
        ast->e->visit(this, nullptr);
        ast->s->visit(this, nullptr);
        ast->ows->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitInitExpr(InitExpr* ast, ASTNode* n) {
        display_node(ast);
        ast->e->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitLiteralExpr(LiteralExpr* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRProfiler::visitLogicStmt(LogicStmt* ast, ASTNode* n) {
        ast->ifs->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitOnceDecl(OnceDecl* ast, ASTNode* n) {
        ast->al->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitOperator(Operator* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRProfiler::visitOtherwiseStmt(OtherwiseStmt* ast, ASTNode* n) {
        if (ast->els != nullptr) {
            ast->els->visit(this, nullptr);
        } else {
            ast->efs->visit(this, nullptr);
            ast->ows->visit(this, nullptr);
        }
    	return nullptr;
    }

    ASTNode* TRProfiler::visitParaDecl(ParaDecl* ast, ASTNode* n) {
        ast->id->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitParaList(ParaList* ast, ASTNode* n) {
        ast->pd->visit(this, nullptr);
        ast->pl->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitRegressionStmt(RegressionStmt* ast, ASTNode* n) {
        ast->id->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitReturnStmt(ReturnStmt* ast, ASTNode* n) {
        display_node(ast);
        ast->e->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitTRNode(TRNode* ast, ASTNode* n) {
        display_node(ast);
        ast->id->visit(this, nullptr);
        ast->pl->visit(this, nullptr);
        ast->cs->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitTRProgList(TRProgList* ast, ASTNode* n) {
        ast->d->visit(this, nullptr);
        ast->pl->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitTRProgram(TRProgram* ast, ASTNode* n) {
        ast->pl->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitUnaryExpr(UnaryExpr* ast, ASTNode* n) {
        ast->o->visit(this, nullptr);
        ast->e->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitVarDecl(VarDecl* ast, ASTNode* n) {
        display_node(ast);
        ast->id->visit(this, nullptr);
        ast->e->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRProfiler::visitVarExpr(VarExpr* ast, ASTNode* n) {
        ast->id->visit(this, nullptr);
    	return nullptr;
    }

    // END INCLUSION POINT

}
#include "print_tree.h"

namespace TR {

    PrintTree::PrintTree(TRInterpreter& driver) : driver(driver), indent(0) {}

    void PrintTree::print_tree() {
        // visit start of program, with visitor and no optional node
        driver.ast->visit(this,nullptr);
        if (indent != 0) {
            // check to ensure indents closed properly
            driver.debug("WARNING: indent was never zeroed");
        }
    }

    /// Visitor function definitions
    // START INCLUSION POINT
    ASTNode* PrintTree::visitActionList(ActionList* ast, ASTNode* n) {
        print_node(ast,"ActionList");
        ++indent;
        ast->s->visit(this, nullptr);
        ast->al->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitActionStmt(ActionStmt* ast, ASTNode* n) {
        print_node(ast,"ActionStmt");
        ++indent;
        ast->al->visit(this, nullptr);
        ast->rgs->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitArg(Arg* ast, ASTNode* n) {
        print_node(ast,"Arg");
        ++indent;
        ast->e->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitArgList(ArgList* ast, ASTNode* n) {
        print_node(ast,"ArgList");
        ++indent;
        ast->a->visit(this, nullptr);
        ast->al->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitAssignStmt(AssignStmt* ast, ASTNode* n) {
        print_node(ast,"AssignStmt");
        ++indent;
        ast->id->visit(this, nullptr);
        ast->e->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitBBCall(BBCall* ast, ASTNode* n) {
        print_node(ast,"BBCall");
        ++indent;
        ast->mod->visit(this, nullptr);
        ast->dstruct->visit(this, nullptr);
        ast->func->visit(this, nullptr);
        ast->al->visit(this, nullptr);
        --indent;
    	return nullptr;
    }

    ASTNode* PrintTree::visitBIVarDecl(BIVarDecl* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* PrintTree::visitBinaryExpr(BinaryExpr* ast, ASTNode* n) {
        print_node(ast,"BinaryExpr");
        ++indent;
        ast->e1->visit(this, nullptr);
        ast->o->visit(this, nullptr);
        ast->e2->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitBlackboardDecl(BlackboardDecl* ast, ASTNode* n) {
        print_node(ast, "BlackboardDecl");
        ++indent;
        ast->id->visit(this, nullptr);
        print_node(ast, ast->struct_type);
        print_node(ast, ast->tr_type);
        --indent;
    	return nullptr;
    }

    ASTNode* PrintTree::visitCond(Cond* ast, ASTNode* n) {
        print_node(ast,"Cond");
        ++indent;
        ast->id->visit(this, nullptr);
        ast->e->visit(this, nullptr);
        ast->as->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitCondStmt(CondStmt* ast, ASTNode* n) {
        print_node(ast,"CondStmt");
        ++indent;
        if (ast->as != nullptr) {
            ast->as->visit(this, nullptr);
        } else {
            ast->c->visit(this, nullptr);
            ast->cs->visit(this, nullptr);
        }
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitElifStmt(ElifStmt* ast, ASTNode* n) {
        print_node(ast,"ElifStmt");
        ++indent;
        ast->e->visit(this, nullptr);
        ast->s->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitElseStmt(ElseStmt* ast, ASTNode* n) {
        print_node(ast,"ElseStmt");
        ++indent;
        ast->s->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitEmptyActionList(EmptyActionList* ast, ASTNode* n) {
        print_node(ast,"EmptyActionList");
        return nullptr;
    }

    ASTNode* PrintTree::visitEmptyArgList(EmptyArgList* ast, ASTNode* n) {
        print_node(ast,"EmptyArgList");
        return nullptr;
    }

    ASTNode* PrintTree::visitEmptyParaList(EmptyParaList* ast, ASTNode* n) {
        print_node(ast,"EmptyParaList");
        return nullptr;
    }

    ASTNode* PrintTree::visitEmptyTRProgList(EmptyTRProgList* ast, ASTNode* n) {
        print_node(ast,"EmptyTRProgList");
        return nullptr;
    }

    ASTNode* PrintTree::visitExitStmt(ExitStmt* ast, ASTNode* n) {
        print_node(ast,"ExitStmt: code = " + std::to_string(ast->etr.code) + " | msg = " + ast->etr.msg);
        return nullptr;
    }

    ASTNode* PrintTree::visitExprStmt(ExprStmt* ast, ASTNode* n) {
        print_node(ast,"ExprStmt");
        ++indent;
        ast->e->visit(this,nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitFCall(FCall* ast, ASTNode* n) {
        print_node(ast,"FCall");
        ++indent;
        ast->id->visit(this, nullptr);
        ast->al->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitFuncDecl(FuncDecl* ast, ASTNode* n) {
        print_node(ast,"FuncDecl");
        ++indent;
        ast->id->visit(this, nullptr);
        ast->pl->visit(this, nullptr);
        ast->s->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitIdent(Ident* ast, ASTNode* n) {
        print_node(ast,"Ident: " + ast->name);
        return nullptr;
    }

    ASTNode* PrintTree::visitIfStmt(IfStmt* ast, ASTNode* n) {
        print_node(ast,"IfStmt");
        ++indent;
        ast->e->visit(this, nullptr);
        ast->s->visit(this, nullptr);
        ast->ows->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitInitExpr(InitExpr* ast, ASTNode* n) {
        print_node(ast,"InitExpr");
        ++indent;
        ast->e->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitLiteralExpr(LiteralExpr* ast, ASTNode* n) {
        print_node(ast,"LiteralExpr: Type = " + TypeToString(ast->val) + " Value = " + ValToString(ast->val));
        return nullptr;
    }

    ASTNode* PrintTree::visitLogicStmt(LogicStmt* ast, ASTNode* n) {
        print_node(ast,"LogicStmt");
        ++indent;
        ast->ifs->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitOnceDecl(OnceDecl* ast, ASTNode* n) {
        print_node(ast,"OnceDecl");
        ++indent;
        ast->al->visit(this, nullptr);
        --indent;
    	return nullptr;
    }

    ASTNode* PrintTree::visitOperator(Operator* ast, ASTNode* n) {
        switch(ast->o) {
            case OP::OR:
                print_node(ast,"Operator: or");
                break;
            case OP::AND:
                print_node(ast,"Operator: and");
                break;
            case OP::EQEQ:
                print_node(ast,"Operator: ==");
                break;
            case OP::NOTEQ:
                print_node(ast,"Operator: !=");
                break;
            case OP::NOT:
                print_node(ast,"Operator: not");
                break;
            case OP::LT:
                print_node(ast,"Operator: <");
                break;
            case OP::LTEQ:
                print_node(ast,"Operator: <=");
                break;
            case OP::GT:
                print_node(ast,"Operator: >");
                break;
            case OP::GTEQ:
                print_node(ast,"Operator: >=");
                break;
            case OP::PLUS:
                print_node(ast,"Operator: +");
                break;
            case OP::MINUS:
                print_node(ast,"Operator: -");
                break;
            case OP::MULT:
                print_node(ast,"Operator: *");
                break;
            case OP::DIV:
                print_node(ast,"Operator: /");
                break;
            default:
                print_node(ast,"UNKNOWN OPERATOR");
                break;
        }
        return nullptr;
    }
   
    ASTNode* PrintTree::visitOtherwiseStmt(OtherwiseStmt* ast, ASTNode* n) {
        print_node(ast,"OtherwiseStmt");
        ++indent;
        if (ast->els != nullptr) {
            ast->els->visit(this, nullptr);
        } else {
            ast->efs->visit(this, nullptr);
            ast->ows->visit(this, nullptr);
        }
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitParaDecl(ParaDecl* ast, ASTNode* n) {
        print_node(ast,"ParaDecl");
        ++indent;
        ast->id->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitParaList(ParaList* ast, ASTNode* n) {
        print_node(ast,"ParaList");
        ++indent;
        ast->pd->visit(this, nullptr);
        ast->pl->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitRegressionStmt(RegressionStmt* ast, ASTNode* n) {
        print_node(ast,"RegressionStmt");
        ++indent;
        ast->id->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitReturnStmt(ReturnStmt* ast, ASTNode* n) {
        print_node(ast,"ReturnStmt");
        ++indent;
        ast->e->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitTRNode(TRNode* ast, ASTNode* n) {
        print_node(ast,"TRNode");
        ++indent;
        ast->id->visit(this, nullptr);
        ast->pl->visit(this, nullptr);
        ast->cs->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitTRProgList(TRProgList* ast, ASTNode* n) {
        print_node(ast,"TRProgList");
        ++indent;
        ast->d->visit(this, nullptr);
        --indent;
        ast->pl->visit(this, nullptr);
        return nullptr;
    }
 
    ASTNode* PrintTree::visitTRProgram(TRProgram* ast, ASTNode* n) {
        print_node(ast,"TRProgram");
        ++indent;
        ast->pl->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitUnaryExpr(UnaryExpr* ast, ASTNode* n) {
        print_node(ast,"UnaryExpr");
        ++indent;
        ast->o->visit(this, nullptr);
        ast->e->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitVarDecl(VarDecl* ast, ASTNode* n) {
        print_node(ast,"VarDecl");
        ++indent;
        ast->id->visit(this, nullptr);
        ast->e->visit(this, nullptr);
        --indent;
        return nullptr;
    }

    ASTNode* PrintTree::visitVarExpr(VarExpr* ast, ASTNode* n) {
        print_node(ast,"VarExpr");
        ++indent;
        ast->id->visit(this, nullptr);
        --indent;
        return nullptr;
    }

// END INCLUSION POINT

}
#include "abstract_visitor.h"

namespace TR {

    // Below is generated from makeAbstractVisitor.py
    //START IMPLEMENTATION POINT

    ASTNode* ActionList::visit(Visitor* v, ASTNode* n) {
    	 return v->visitActionList(this, n);
    }

    ASTNode* ActionStmt::visit(Visitor* v, ASTNode* n) {
    	 return v->visitActionStmt(this, n);
    }

    ASTNode* Arg::visit(Visitor* v, ASTNode* n) {
    	 return v->visitArg(this, n);
    }

    ASTNode* ArgList::visit(Visitor* v, ASTNode* n) {
    	 return v->visitArgList(this, n);
    }

    ASTNode* AssignStmt::visit(Visitor* v, ASTNode* n) {
    	 return v->visitAssignStmt(this, n);
    }

    ASTNode* BBCall::visit(Visitor* v, ASTNode* n) {
    	 return v->visitBBCall(this, n);
    }

    ASTNode* BIVarDecl::visit(Visitor* v, ASTNode* n) {
    	 return v->visitBIVarDecl(this, n);
    }

    ASTNode* BinaryExpr::visit(Visitor* v, ASTNode* n) {
    	 return v->visitBinaryExpr(this, n);
    }

    ASTNode* BlackboardDecl::visit(Visitor* v, ASTNode* n) {
    	 return v->visitBlackboardDecl(this, n);
    }

    ASTNode* Cond::visit(Visitor* v, ASTNode* n) {
    	 return v->visitCond(this, n);
    }

    ASTNode* CondStmt::visit(Visitor* v, ASTNode* n) {
    	 return v->visitCondStmt(this, n);
    }

    ASTNode* ElifStmt::visit(Visitor* v, ASTNode* n) {
    	 return v->visitElifStmt(this, n);
    }

    ASTNode* ElseStmt::visit(Visitor* v, ASTNode* n) {
    	 return v->visitElseStmt(this, n);
    }

    ASTNode* EmptyActionList::visit(Visitor* v, ASTNode* n) {
    	 return v->visitEmptyActionList(this, n);
    }

    ASTNode* EmptyArgList::visit(Visitor* v, ASTNode* n) {
    	 return v->visitEmptyArgList(this, n);
    }

    ASTNode* EmptyParaList::visit(Visitor* v, ASTNode* n) {
    	 return v->visitEmptyParaList(this, n);
    }

    ASTNode* EmptyTRProgList::visit(Visitor* v, ASTNode* n) {
    	 return v->visitEmptyTRProgList(this, n);
    }

    ASTNode* ExitStmt::visit(Visitor* v, ASTNode* n) {
    	 return v->visitExitStmt(this, n);
    }

    ASTNode* ExprStmt::visit(Visitor* v, ASTNode* n) {
    	 return v->visitExprStmt(this, n);
    }

    ASTNode* FCall::visit(Visitor* v, ASTNode* n) {
    	 return v->visitFCall(this, n);
    }

    ASTNode* FuncDecl::visit(Visitor* v, ASTNode* n) {
    	 return v->visitFuncDecl(this, n);
    }

    ASTNode* Ident::visit(Visitor* v, ASTNode* n) {
    	 return v->visitIdent(this, n);
    }

    ASTNode* IfStmt::visit(Visitor* v, ASTNode* n) {
    	 return v->visitIfStmt(this, n);
    }

    ASTNode* InitExpr::visit(Visitor* v, ASTNode* n) {
    	 return v->visitInitExpr(this, n);
    }

    ASTNode* LiteralExpr::visit(Visitor* v, ASTNode* n) {
    	 return v->visitLiteralExpr(this, n);
    }

    ASTNode* LogicStmt::visit(Visitor* v, ASTNode* n) {
    	 return v->visitLogicStmt(this, n);
    }

    ASTNode* OnceDecl::visit(Visitor* v, ASTNode* n) {
    	 return v->visitOnceDecl(this, n);
    }

    ASTNode* Operator::visit(Visitor* v, ASTNode* n) {
    	 return v->visitOperator(this, n);
    }

    ASTNode* OtherwiseStmt::visit(Visitor* v, ASTNode* n) {
    	 return v->visitOtherwiseStmt(this, n);
    }

    ASTNode* ParaDecl::visit(Visitor* v, ASTNode* n) {
    	 return v->visitParaDecl(this, n);
    }

    ASTNode* ParaList::visit(Visitor* v, ASTNode* n) {
    	 return v->visitParaList(this, n);
    }

    ASTNode* RegressionStmt::visit(Visitor* v, ASTNode* n) {
    	 return v->visitRegressionStmt(this, n);
    }

    ASTNode* ReturnStmt::visit(Visitor* v, ASTNode* n) {
    	 return v->visitReturnStmt(this, n);
    }

    ASTNode* TRNode::visit(Visitor* v, ASTNode* n) {
    	 return v->visitTRNode(this, n);
    }

    ASTNode* TRProgList::visit(Visitor* v, ASTNode* n) {
    	 return v->visitTRProgList(this, n);
    }

    ASTNode* TRProgram::visit(Visitor* v, ASTNode* n) {
    	 return v->visitTRProgram(this, n);
    }

    ASTNode* UnaryExpr::visit(Visitor* v, ASTNode* n) {
    	 return v->visitUnaryExpr(this, n);
    }

    ASTNode* VarDecl::visit(Visitor* v, ASTNode* n) {
    	 return v->visitVarDecl(this, n);
    }

    ASTNode* VarExpr::visit(Visitor* v, ASTNode* n) {
    	 return v->visitVarExpr(this, n);
    }

    //END IMPLEMENTATION POINT

    // call for TR parts are just wrapped visitor call
    void TRNode::call(Visitor* v, ASTNode* n) {
        v->visitTRNode(this, n);
    }

    void FuncDecl::call(Visitor* v, ASTNode* n) {
        v->visitFuncDecl(this, n);
    }
    
}
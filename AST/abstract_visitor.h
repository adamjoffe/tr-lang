#ifndef ABSTRACT_VISITOR_H
#define ABSTRACT_VISITOR_H

// abstract inclusions
#include "ast_abstract_nodes.h"
#include "ast_concrete_nodes.h"

namespace TR {

    class Visitor { 
    public:
        // Below is generated from makeAbstractVisitor.py
        // START INTERFACE POINT
        virtual ASTNode* visitActionList(ActionList* ast, ASTNode* n) = 0;
        virtual ASTNode* visitActionStmt(ActionStmt* ast, ASTNode* n) = 0;
        virtual ASTNode* visitArg(Arg* ast, ASTNode* n) = 0;
        virtual ASTNode* visitArgList(ArgList* ast, ASTNode* n) = 0;
        virtual ASTNode* visitAssignStmt(AssignStmt* ast, ASTNode* n) = 0;
        virtual ASTNode* visitBBCall(BBCall* ast, ASTNode* n) = 0;
        virtual ASTNode* visitBIVarDecl(BIVarDecl* ast, ASTNode* n) = 0;
        virtual ASTNode* visitBinaryExpr(BinaryExpr* ast, ASTNode* n) = 0;
        virtual ASTNode* visitBlackboardDecl(BlackboardDecl* ast, ASTNode* n) = 0;
        virtual ASTNode* visitCond(Cond* ast, ASTNode* n) = 0;
        virtual ASTNode* visitCondStmt(CondStmt* ast, ASTNode* n) = 0;
        virtual ASTNode* visitElifStmt(ElifStmt* ast, ASTNode* n) = 0;
        virtual ASTNode* visitElseStmt(ElseStmt* ast, ASTNode* n) = 0;
        virtual ASTNode* visitEmptyActionList(EmptyActionList* ast, ASTNode* n) = 0;
        virtual ASTNode* visitEmptyArgList(EmptyArgList* ast, ASTNode* n) = 0;
        virtual ASTNode* visitEmptyParaList(EmptyParaList* ast, ASTNode* n) = 0;
        virtual ASTNode* visitEmptyTRProgList(EmptyTRProgList* ast, ASTNode* n) = 0;
        virtual ASTNode* visitExitStmt(ExitStmt* ast, ASTNode* n) = 0;
        virtual ASTNode* visitExprStmt(ExprStmt* ast, ASTNode* n) = 0;
        virtual ASTNode* visitFCall(FCall* ast, ASTNode* n) = 0;
        virtual ASTNode* visitFuncDecl(FuncDecl* ast, ASTNode* n) = 0;
        virtual ASTNode* visitIdent(Ident* ast, ASTNode* n) = 0;
        virtual ASTNode* visitIfStmt(IfStmt* ast, ASTNode* n) = 0;
        virtual ASTNode* visitInitExpr(InitExpr* ast, ASTNode* n) = 0;
        virtual ASTNode* visitLiteralExpr(LiteralExpr* ast, ASTNode* n) = 0;
        virtual ASTNode* visitLogicStmt(LogicStmt* ast, ASTNode* n) = 0;
        virtual ASTNode* visitOnceDecl(OnceDecl* ast, ASTNode* n) = 0;
        virtual ASTNode* visitOperator(Operator* ast, ASTNode* n) = 0;
        virtual ASTNode* visitOtherwiseStmt(OtherwiseStmt* ast, ASTNode* n) = 0;
        virtual ASTNode* visitParaDecl(ParaDecl* ast, ASTNode* n) = 0;
        virtual ASTNode* visitParaList(ParaList* ast, ASTNode* n) = 0;
        virtual ASTNode* visitRegressionStmt(RegressionStmt* ast, ASTNode* n) = 0;
        virtual ASTNode* visitReturnStmt(ReturnStmt* ast, ASTNode* n) = 0;
        virtual ASTNode* visitTRNode(TRNode* ast, ASTNode* n) = 0;
        virtual ASTNode* visitTRProgList(TRProgList* ast, ASTNode* n) = 0;
        virtual ASTNode* visitTRProgram(TRProgram* ast, ASTNode* n) = 0;
        virtual ASTNode* visitUnaryExpr(UnaryExpr* ast, ASTNode* n) = 0;
        virtual ASTNode* visitVarDecl(VarDecl* ast, ASTNode* n) = 0;
        virtual ASTNode* visitVarExpr(VarExpr* ast, ASTNode* n) = 0;
        // END INTERFACE POINT
    };
}

#endif

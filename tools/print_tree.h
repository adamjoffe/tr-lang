#ifndef PRINT_TREE_H
#define PRINT_TREE_H

#include "../AST/abstract_visitor.h"
#include "../tr_interpreter.h"

namespace TR {

    class PrintTree : public Visitor {

    public:

        /// remove default constructor
        PrintTree() = delete;

        /**
         * Semantic analyser driver constructor
         *
         * Constructor using a reference to the driver
         *
         * @param driver The driver object instantiating this
         * object
         */
        PrintTree(TRInterpreter& driver);

        /**
         * Prints the AST
         *
         * Prints the Abstract Syntax Tree stored by the driver
         */
        void print_tree();

        /// Declaration of visitor interface functions
        // START INCLUSION POINT
        virtual ASTNode* visitActionList(ActionList* ast, ASTNode* n);
        virtual ASTNode* visitActionStmt(ActionStmt* ast, ASTNode* n);
        virtual ASTNode* visitArg(Arg* ast, ASTNode* n);
        virtual ASTNode* visitArgList(ArgList* ast, ASTNode* n);
        virtual ASTNode* visitAssignStmt(AssignStmt* ast, ASTNode* n);
        virtual ASTNode* visitBBCall(BBCall* ast, ASTNode* n);
        virtual ASTNode* visitBIVarDecl(BIVarDecl* ast, ASTNode* n);
        virtual ASTNode* visitBinaryExpr(BinaryExpr* ast, ASTNode* n);
        virtual ASTNode* visitBlackboardDecl(BlackboardDecl* ast, ASTNode* n);
        virtual ASTNode* visitCond(Cond* ast, ASTNode* n);
        virtual ASTNode* visitCondStmt(CondStmt* ast, ASTNode* n);
        virtual ASTNode* visitElifStmt(ElifStmt* ast, ASTNode* n);
        virtual ASTNode* visitElseStmt(ElseStmt* ast, ASTNode* n);
        virtual ASTNode* visitEmptyActionList(EmptyActionList* ast, ASTNode* n);
        virtual ASTNode* visitEmptyArgList(EmptyArgList* ast, ASTNode* n);
        virtual ASTNode* visitEmptyParaList(EmptyParaList* ast, ASTNode* n);
        virtual ASTNode* visitEmptyTRProgList(EmptyTRProgList* ast, ASTNode* n);
        virtual ASTNode* visitExitStmt(ExitStmt* ast, ASTNode* n);
        virtual ASTNode* visitExprStmt(ExprStmt* ast, ASTNode* n);
        virtual ASTNode* visitFCall(FCall* ast, ASTNode* n);
        virtual ASTNode* visitFuncDecl(FuncDecl* ast, ASTNode* n);
        virtual ASTNode* visitIdent(Ident* ast, ASTNode* n);
        virtual ASTNode* visitIfStmt(IfStmt* ast, ASTNode* n);
        virtual ASTNode* visitInitExpr(InitExpr* ast, ASTNode* n);
        virtual ASTNode* visitLiteralExpr(LiteralExpr* ast, ASTNode* n);
        virtual ASTNode* visitLogicStmt(LogicStmt* ast, ASTNode* n);
        virtual ASTNode* visitOnceDecl(OnceDecl* ast, ASTNode* n);
        virtual ASTNode* visitOperator(Operator* ast, ASTNode* n);
        virtual ASTNode* visitOtherwiseStmt(OtherwiseStmt* ast, ASTNode* n);
        virtual ASTNode* visitParaDecl(ParaDecl* ast, ASTNode* n);
        virtual ASTNode* visitParaList(ParaList* ast, ASTNode* n);
        virtual ASTNode* visitRegressionStmt(RegressionStmt* ast, ASTNode* n);
        virtual ASTNode* visitReturnStmt(ReturnStmt* ast, ASTNode* n);
        virtual ASTNode* visitTRNode(TRNode* ast, ASTNode* n);
        virtual ASTNode* visitTRProgList(TRProgList* ast, ASTNode* n);
        virtual ASTNode* visitTRProgram(TRProgram* ast, ASTNode* n);
        virtual ASTNode* visitUnaryExpr(UnaryExpr* ast, ASTNode* n);
        virtual ASTNode* visitVarDecl(VarDecl* ast, ASTNode* n);
        virtual ASTNode* visitVarExpr(VarExpr* ast, ASTNode* n);
        // END INCLUSION POINT

    private:
        /**
         * Displays the node with stored indent and given name
         */
        inline void print_node(const ASTNode* ast, std::string name) {
            for (int i = 0; i < indent; ++i) {
                name.insert(0,"\t");
            }
            driver.debug(ast,name);
        }

    private:
        TRInterpreter& driver;
        int indent;

    };

}

#endif

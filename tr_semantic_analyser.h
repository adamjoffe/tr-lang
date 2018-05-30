#ifndef TR_SEMANTIC_ANALYSER_H
#define TR_SEMANTIC_ANALYSER_H

#include <string>

#include "AST/abstract_visitor.h"
#include "tr_interpreter.h"

#include "tr_types.h"

namespace TR {

    class TRSemanticAnalyser : public Visitor {

    public:

        /// remove default constructor
        TRSemanticAnalyser() = delete;

        /**
         * Semantic analyser driver constructor
         *
         * Constructor using a reference to the driver
         *
         * @param driver The driver object instantiating this
         * object
         */
        TRSemanticAnalyser(TRInterpreter& driver);

        /**
         * Analyses the AST
         *
         * Analyses the Abstract Syntax Tree stored by the driver
         * using the symbol table to statically check declarations
         * and types where possible
         */
        void analyse();

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
        TRInterpreter& driver;

        /// Semantic Analyser error messages by code number
        // TODO: provide a function wrapper for all semantic erroring (similar to executor one)
        const std::string error_msg[27] = {
            "[0] UNKNOWN ERROR: ",
            "[1] No start node present in TR-code, expecting: ", // TRProgram
            "[2] Variable already declared: ", // VarDecl
            "[3] Function already declared: ", // FuncDecl
            "[4] TR Node already declared: ", // TRNode
            "[5] Variable not declared before use: ", // VarExpr
            "[6] Function/TR Node not declared before use: ", // FCall
            "[7] Parameter being used as a function/TRNode: ",
            "[8] Function being used as variable: ", // VarExpr
            "[9] TR Node being used as variable: ", // VarExpr
            "[10] Variable being used as function/TR Node", // FCall
            "[11] Unknown operation for type: ", // UnaryExpr
            "[12] Unknown operation between types: ", // BinaryExpr
            "[13] Condition name already used: ", // Cond
            "[14] Achieves name not in scope: ", // RegressionStmt
            "[15] Too many arguments: ", // FCall
            "[16] Not enough arguments: ", // FCall
            "[17] Start node doesn't take any parameters: ", // TRNode
            "[18] Expecting boolean in branching statement, received: ", // IfStmt, ElifStmt, Cond
            // Below only apply to built-in variables during SA
            "[19] Can't assign void to variable: ", // AssignStmt, VarDecl
            "[20] Arguments can't be void type", // Arg
            "[21] Built-in variable type can't be changes: ", // AssignStmt
            "[22] TR Node can only be called in action list: ", // FCall
            // Below only apply to blackboard data structure
            "[23] Blackboard frame already exists: ", // BlackboardDecl
            "[24] Blackboard module doesn't exist: ", // BBCall
            "[25] Blackboard frame doesn't exist: ", // BBCall
            "[26] Blackboard function doesn't exist: " // BBCall
        };

        /// Semantic Analyser warning messages by code number
        const std::string warn_msg[3] = {
            "[0] Reserved warning: ",
            "[1] Unused value from expression statement", // ExprStmt
            "[2] Variable changing type: " // AssignStmt
        };
    };

}

#endif // TR_SEMANTIC_ANALYSER_H
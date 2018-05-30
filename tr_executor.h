#ifndef TR_EXECUTOR_H
#define TR_EXECUTOR_H

#include <sstream>
#include <string>

// attchable tools
#include "tools/tr_attachable.h"

#include "AST/abstract_visitor.h"
#include "tr_interpreter.h"

#include "tr_types.h"

#include "exe-components/exit_tr.h"
#include "exe-components/tr_runtime_exception.h"

namespace TR {

    class TRExecutor : public Visitor {

    public:

        /// remove default constructor
        TRExecutor() = delete;

        /**
         * Executor driver constructor
         *
         * Constructor using a reference to the driver
         *
         * @param driver The driver object instantiating this
         * object
         */
        TRExecutor(TRInterpreter& driver);

        /// Destructor
        ~TRExecutor();

        /**
         * Execute the AST
         *
         * Executes the Abstract Syntax Tree stored by the driver
         * using the symbol table and modifications made by the
         * semantic analyser. It performs dynamic typing when
         * required where statically typing isn't possible
         * (often for function return values)
         */
        void execute();

        /**
         * Attach profiler to exector
         *
         * Attaches the given profiler to the exector
         *
         * @param pfl Profiler to attach to executor
         */
        void attach_profiler(TRAttachable* pfl) { profiler = pfl; }

        /**
         * Attach debugger to exector
         *
         * Attaches the given debugger to the exector
         *
         * @param pfl Debugger to attach to executor
         */
        void attach_debugger(TRAttachable* dbg) { debugger = dbg; }

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

        /// Attached tool components
        TRAttachable* profiler; // TR profiler
        TRAttachable* debugger; // TR Debugger

        /// Semantic Analyser error messages by code number
        const std::string error_msg[9] = {
            "[0] UNKNOWN ERROR: ",
            "[1] Invalid TR-Lang Type", // Expr
            "[2] Invalid return type: ", // FCall
            "[3] Unknown operation for type: ", // UnaryExpr
            "[4] Unknown operation between types: ", // BinaryExpr"
            "[5] Expecting boolean in branching statement, received: ", // Cond
            "[6] Can't assign void to variable: ", // AssignStmt
            "[7] Built-in variables cannot change type: ", // AssignStmt
            "[8] Arguments can't be void type: " // Arg
        };

        /// Semantic Analyser warning messages by code number
        const std::string warn_msg[3] = {
            "[0] Reserved warning: ",
            "[1] Unused value from expression statement", // ExprStmt
            "[2] Variable changing type: " // AssignStmt
        };

        /**
         * Makes Runtime Exception
         *
         * Constructs and throws a TR Runtime Exception
         *
         * @param ast Related AST node to error to get source reference from
         * @param code Error code for this error
         * @throws TR_Runtime_Exception
         */
        inline void makeError(const ASTNode* ast, const size_t code) {
            std::ostringstream stream;
            stream << ast->loc;
            throw TR_Runtime_Exception(ast->file + ":" + stream.str() + ": - " + error_msg[code]);
        }

        /**
         * Makes Runtime Exception
         *
         * Constructs and throws a TR Runtime Exception
         *
         * @param ast Related AST node to error to get source reference from
         * @param code Error code for this error
         * @param additional Additional information to add to error
         * @throws TR_Runtime_Exception
         */
        inline void makeError(const ASTNode* ast, const size_t code, const std::string& additional) {
            std::ostringstream stream;
            stream << ast->loc;
            throw TR_Runtime_Exception(ast->file + ":" + stream.str() + ": - " + error_msg[code] + additional);
        }
    };

}

#endif
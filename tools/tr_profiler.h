#ifndef TR_PROFILER_H
#define TR_PROFILER_H

#include <iostream>

#include "tr_attachable.h"
#include "../AST/abstract_visitor.h"
#include "../tr_interpreter.h"

namespace TR {

    class TRProfiler : public Visitor, public TRAttachable {

    public:

        /// remove default constructor
        TRProfiler() = delete;

        /**
         * Semantic analyser driver stream constructor
         *
         * Constructor using a reference to the driver
         *
         * @param driver The driver object instantiating this
         * object
         * @param loc Output file location
         */
        TRProfiler(TRInterpreter& driver, std::string& loc, int yr);

        ~TRProfiler() {
            delete pout;
        }

        /**
         * Starts profiling measuring on node
         *
         * @param ast AST Node to start profiling on
         */
        void start_node(ASTNode* ast);

        /**
         * Ends profiling measuring on node
         *
         * @param ast AST Node to end profiling on
         */
        void end_node(ASTNode* ast);

        /**
         * Notify attachable before execution
         *
         * Notifies attachable before the execution of the node
         */
        void notify_before();

        /**
         * Notify attachable after execution
         *
         * Notifies attachable after the execution of the node
         */
        void notify_after();

        /**
         * Notify attachable after exiting
         *
         * Notifies attachable after the execution of the node
         */
        void notify_exit();

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
         * Prints the Profiler Statistics
         *
         * Prints the Profiler Infomration stored in the AST
         */
        void print_profile();

        /**
         * Display Profiler Stats
         *
         * Displays the profiler statistics for given AST node
         *
         * @param ast AST node to display stats of
         */
        inline void display_node(ASTNode* ast) {
            *pout << ast->src_code << " | " 
                  << ast->count << " | " 
                  << ast->exe_time << " | " 
                  << (static_cast<double>(ast->exe_time))/CLOCKS_PER_SEC << " | "
                  << ((static_cast<double>(ast->exe_time))/CLOCKS_PER_SEC / ast->count)
                  << std::endl;
        }

    private:
        TRInterpreter& driver;

        /// Output stream to write profiler to
        std::ostream* pout;

        /// yield rate of the profiler
        int yield_rate;
        /// execution counter
        int exe_counter;

        /// number of times profiler output
        int num_outputs;
    };

}

#endif

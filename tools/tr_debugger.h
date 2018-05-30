#ifndef TR_DEBUGGER_H
#define TR_DEBUGGER_H

#include <iostream>

#include "tr_attachable.h"
#include "../AST/abstract_visitor.h"
#include "../tr_interpreter.h"

namespace TR {

    class TRDebugger : public Visitor, public TRAttachable {

    public:

        /// remove default constructor
        TRDebugger() = delete;

        /**
         * Semantic analyser driver stream constructor
         *
         * Constructor using a reference to the driver
         *
         * @param driver The driver object instantiating this
         * object
         * @param loc Output file location
         */
        TRDebugger(TRInterpreter& driver, std::string& loc);

        ~TRDebugger() {
            delete dout;
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
        /// Debug symbol functions

        /**
         * Exe Cycle Output
         *
         * Outputs execution cycle in the form:
         * ncycle=<x>
         */
        inline void exe_cyles() {
            *dout << "ncycle=" << exe_counter << std::endl;
        }

        /**
         * Variable State Output
         *
         * Outputs variable states in the form:
         * vstate=<dname>[sep]<vname>[sep]<type>[sep]<val>[sep]<TR/BI>[sep]<scope>[sep]<src>
         */
        inline void variable_state(std::string& dname, std::string& vname, std::string type, 
                                    std::string val, std::string trbi, std::string scope,
                                    std::string& src) {
            *dout << "vstate=" << dname
                    << sep << vname
                    << sep << type
                    << sep << val
                    << sep << trbi
                    << sep << scope
                    << sep << src
                    << std::endl;
        }

        /**
         * New Scope Output
         *
         * Outputs new scope in the form:
         * nscope=<dname>[sep]<sname>[sep]<FD/TRD>[sep]<scope>[sep]<src>
         */
        inline void new_scope(std::string& dname, std::string& sname, std::string fdtrd,
                                std::string scope, std::string& src) {
            *dout << "nscope=" << dname
                    << sep << sname
                    << sep << fdtrd
                    << sep << scope
                    << sep << src
                    << std::endl;
        }

        /**
         * Function Return Output
         *
         * Outputs function return in the form:
         * fret=<dname>[sep]<fname>[sep]<type>[sep]<val>[sep]<TR/BI>[sep]<src>
         */
        inline void function_return(std::string& dname, std::string& fname, std::string type, 
                                    std::string val, std::string trbi, std::string& src) {
            *dout << "fret=" << dname
                    << sep << fname
                    << sep << type
                    << sep << val
                    << sep << trbi
                    << sep << src
                    << std::endl;
        }

        /**
         * Param Values Output
         *
         * Outputs param values in the form:
         * paramv=<dname>[sep]<fname>([sep]<vname>[sep]<type>[sep]<val>)*[sep]src
         */
        inline void param_values(std::string& dname, std::string& fname, std::vector<std::string>& vname, 
                                    std::vector<std::string>& type, std::vector<std::string>& val, std::string& src) {
            *dout << "paramv=" << dname
                    << sep << fname;
            for (size_t i = 0; i < vname.size() && i < type.size() && i < val.size(); ++i) {
                *dout << sep << vname[i]
                        << sep << type[i]
                        << sep << val[i];
            }
            *dout << sep << src
                    << std::endl;
        }

        /**
         * Condition/Regression Output
         *
         * Outputs condition/regression in the form:
         * cond=<dname>[sep]<cname>[sep]<rname>
         */
        inline void cond_rgr(std::string& dname, std::string cname, std::string& rname,
                                std::string& src) {
            *dout << "cond=" << dname
                    << sep << cname
                    << sep << rname
                    << sep << src
                    << std::endl;
        }

        /**
         * Exit Clause Output
         *
         * Outputs exit clause in the form:
         * exitc=<dname>[sep]<status>[sep]<msg>[sep]<src>
         */
        inline void exit_clause(std::string& dname, std::string status, std::string msg,
                                    std::string& src) {
            *dout << "exitc=" << dname
                    << sep << status
                    << sep << msg
                    << sep << src
                    << std::endl;
        }

    private:
        TRInterpreter& driver;

        /// Output stream to write debugger to
        std::ostream* dout;
        
        /// Execution counter
        int exe_counter;

        /// Scope level
        int scope_level;

        const std::string sep = "%@";

        /// Inner dummy class for passing information to visit functions
        class ASTDummy : public ASTNode {
        public:

            ASTDummy(std::string n) : name(n), ASTNode(location(), std::string()) {}

            ASTNode* visit(Visitor* v, ASTNode* n) {
                return nullptr;
            }

            std::string name;
        };

        /// Dummy nodes for passing a string to a visit function
        ASTDummy pre = ASTDummy("pre");
        ASTDummy in = ASTDummy("in");
        ASTDummy post = ASTDummy("post");
    };

}

#endif

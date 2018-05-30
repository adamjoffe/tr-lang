#ifndef TR_HIERARCHY_H
#define TR_HIERARCHY_H

#include <stack>
#include <unordered_map>
#include <unordered_set>

#include <boost/graph/adjacency_list.hpp>

#include "../AST/abstract_visitor.h"
#include "../tr_interpreter.h"

namespace TR {
    struct TRVertex {
        std::string name;
        std::string shape;
        std::string colour;

        TRVertex(std::string& n, std::string& s) : name(n), shape(s) {}
        TRVertex() {}
    };

    struct TREdge {
        std::string name;
    };

    struct TRGraph {
        std::string name;
    };
}

using Graph = boost::adjacency_list<boost::vecS, boost::setS, boost::directedS,
                    TR::TRVertex, TR::TREdge, TR::TRGraph>;

namespace TR {

    class TRHierarchy : public Visitor {

    public:

        /// remove default constructor
        TRHierarchy() = delete;

        /**
         * Semantic analyser driver constructor
         *
         * Constructor using a reference to the driver
         *
         * @param driver The driver object instantiating this
         * object
         */
        TRHierarchy(TRInterpreter& driver, std::string& oloc);

        /**
         * Prints the AST
         *
         * Prints the TR Hierarchy implied by the TR code
         */
        void print_hierarchy();

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

        /// Graph components
        // Graph
        Graph hierarchy;
        // Output location
        std::string outloc;
        // TRNode shape
        std::string nodeShape = "oval";
        // Func shape
        std::string funcShape = "rect";
        // Blackboard shape
        std::string blackboardShape = "rect";
        // TR Func colour
        std::string funcColour = "turquoise";
        // BI Func colour
        std::string bifuncColour = "violet";
        // BB Func colour
        std::string bbfuncColour = "slateblue";

        /// Data components
        // Vertex name stack
        std::stack<std::string> currNode;
        // Edge name stack
        std::stack<std::string> currCond;
        // Vertex descriptor map
        std::unordered_map<std::string, Graph::vertex_descriptor> vertmap;
        // Visited set of vertexs
        std::unordered_set<std::string> visited;
    };

}

#endif

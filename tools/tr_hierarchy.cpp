#include "tr_hierarchy.h"

#include <cstdlib>
#include <iostream>

#include <boost/graph/graphviz.hpp>

namespace TR {

    TRHierarchy::TRHierarchy(TRInterpreter& driver, std::string& oloc) : driver(driver), outloc(oloc) {}

    void TRHierarchy::print_hierarchy() {
        // visit start of program, with visitor and no optional node
        driver.start_node->visit(this,nullptr);

        // set name of the graph
        hierarchy[boost::graph_bundle].name = driver.scanner.currentFile();

        std::string fn = "structure-" + driver.scanner.currentFile();

        // check if outloc exists, otherwise make it
        driver.existAndMake(outloc);

        // create ostream for printing the graph
        std::ofstream dotfile((outloc + fn + ".dot").c_str());

        // dynamic property reader for outputing node labels
        boost::dynamic_properties dp;
        dp.property("node_id", get(&TRVertex::name, hierarchy));
        dp.property("shape", get(&TRVertex::shape, hierarchy));
        dp.property("color", get(&TRVertex::colour, hierarchy));
        dp.property("label", get(&TREdge::name, hierarchy));
        dp.property("label", boost::make_static_property_map<Graph*>(boost::get_property(hierarchy, &TRGraph::name)));

        // write graphviz dot file
        boost::write_graphviz_dp(dotfile, hierarchy, dp);

        // system call to convert dot to img file
        if (system(("dot -Tpng " + outloc + fn + ".dot -o " + outloc + fn + ".png").c_str()) != 0) {
            throw std::runtime_error("TR Hierarchy Structure Drawer failed to generate image file. Please ensure that Graphviz is installed.");
        }
    }

    /// Visitor function definitions
    // START INCLUSION POINT
    ASTNode* TRHierarchy::visitActionList(ActionList* ast, ASTNode* n) {
        ast->s->visit(this, nullptr);
        ast->al->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitActionStmt(ActionStmt* ast, ASTNode* n) {
        ast->al->visit(this, nullptr);
        ast->rgs->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitArg(Arg* ast, ASTNode* n) {
        ast->e->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitArgList(ArgList* ast, ASTNode* n) {
        ast->a->visit(this, nullptr);
        ast->al->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitAssignStmt(AssignStmt* ast, ASTNode* n) {
        ast->id->visit(this, nullptr);
        ast->e->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitBBCall(BBCall* ast, ASTNode* n) {// check for from vertex
        std::string mod = dynamic_cast<Ident&>(*(ast->mod.get())).name;
        std::string dstruct = dynamic_cast<Ident&>(*(ast->dstruct.get())).name;
        std::string func = dynamic_cast<Ident&>(*(ast->func.get())).name;
        std::string cname = "blackboard." + mod + "." + dstruct + "." + func;
        std::unordered_map<std::string, Graph::vertex_descriptor>::iterator fvit = vertmap.find(currNode.top());
        if (fvit == vertmap.end()) {
            // error
        }
        Graph::vertex_descriptor fv = fvit->second;

        // check or make to vertex
        std::unordered_map<std::string, Graph::vertex_descriptor>::iterator tvit = vertmap.find(cname);
        Graph::vertex_descriptor tv;
        if (tvit == vertmap.end()) {
            // vertex doesn't exist make a new node
            TRVertex to(cname, blackboardShape);
            to.colour = bbfuncColour;
            tv = boost::add_vertex(to, hierarchy);
            vertmap.insert(
                std::pair<std::string, Graph::vertex_descriptor>(cname,tv)
            );
        } else {
            // vertex exists, get the vertex descriptor
            tv = tvit->second;
        }

        // add edge between current top of stack and this node
        Graph::edge_descriptor e = (boost::add_edge(fv, tv, hierarchy)).first;
        hierarchy[e].name = currCond.top();
    	return nullptr;
    }

    ASTNode* TRHierarchy::visitBIVarDecl(BIVarDecl* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRHierarchy::visitBinaryExpr(BinaryExpr* ast, ASTNode* n) {
        ast->e1->visit(this, nullptr);
        ast->o->visit(this, nullptr);
        ast->e2->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitBlackboardDecl(BlackboardDecl* ast, ASTNode* n) {
    	return nullptr;
    }

    ASTNode* TRHierarchy::visitCond(Cond* ast, ASTNode* n) {

        // condition name
        std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;

        // removed expression checking since only want to not functions in the action statements

        // add name to stack
        currCond.push(vname);

        ast->as->visit(this, nullptr);

        // pop off stack
        currCond.pop();

        return nullptr;
    }

    ASTNode* TRHierarchy::visitCondStmt(CondStmt* ast, ASTNode* n) {
        if (ast->as != nullptr) {
            // add true to stack
            currCond.push("true");

            ast->as->visit(this, nullptr);

            // pop off stack
            currCond.pop();
        } else {
            ast->c->visit(this, nullptr);
            ast->cs->visit(this, nullptr);
        }
        return nullptr;
    }

    ASTNode* TRHierarchy::visitElifStmt(ElifStmt* ast, ASTNode* n) {
        ast->e->visit(this, nullptr);
        ast->s->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitElseStmt(ElseStmt* ast, ASTNode* n) {
        ast->s->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitEmptyActionList(EmptyActionList* ast, ASTNode* n) {
        return nullptr;
    }

    ASTNode* TRHierarchy::visitEmptyArgList(EmptyArgList* ast, ASTNode* n) {
        return nullptr;
    }

    ASTNode* TRHierarchy::visitEmptyParaList(EmptyParaList* ast, ASTNode* n) {
        return nullptr;
    }

    ASTNode* TRHierarchy::visitEmptyTRProgList(EmptyTRProgList* ast, ASTNode* n) {
        return nullptr;
    }

    ASTNode* TRHierarchy::visitExitStmt(ExitStmt* ast, ASTNode* n) {
        return nullptr;
    }

    ASTNode* TRHierarchy::visitExprStmt(ExprStmt* ast, ASTNode* n) {
        ast->e->visit(this,nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitFCall(FCall* ast, ASTNode* n) {

        // check if its a TRNode
        std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;
        if (ASTDecl* vdecl = driver.symtbl->retrieve(vname)) {
            if (vdecl->dt == DeclType::TR_DECL 
                    || vdecl->dt == DeclType::FUNC_DECL
                    || vdecl->dt == DeclType::BIFUNC_DECL) {

                // check for from vertex
                std::unordered_map<std::string, Graph::vertex_descriptor>::iterator fvit = vertmap.find(currNode.top());
                if (fvit == vertmap.end()) {
                    // error
                }
                Graph::vertex_descriptor fv = fvit->second;

                // check or make to vertex
                std::unordered_map<std::string, Graph::vertex_descriptor>::iterator tvit = vertmap.find(vname);
                Graph::vertex_descriptor tv;
                if (tvit == vertmap.end()) {
                    // vertex doesn't exist make a new node
                    TRVertex to;
                    if (vdecl->dt == DeclType::TR_DECL) {
                        to.name = vname;
                        to.shape = nodeShape;
                    } else {
                        to.name = vname;
                        to.shape = funcShape;
                        if (vdecl->dt == DeclType::FUNC_DECL) {
                            to.colour = funcColour;
                        } else {
                            to.colour = bifuncColour;
                        }
                    }
                    tv = boost::add_vertex(to, hierarchy);
                    vertmap.insert(
                        std::pair<std::string, Graph::vertex_descriptor>(vname,tv)
                    );
                } else {
                    // vertex exists, get the vertex descriptor
                    tv = tvit->second;
                }

                // add edge between current top of stack and this node
                Graph::edge_descriptor e = (boost::add_edge(fv, tv, hierarchy)).first;
                hierarchy[e].name = currCond.top();

                // progress down the tree using visit not call
                // don't progress if its not a TRNode, recursive or already visited
                if (vdecl->dt == DeclType::TR_DECL && currNode.top() != vname && visited.count(vname) == 0) {
                    visited.insert(vname);
                    vdecl->visit(this,nullptr);
                }
            }
        }

        return nullptr;
    }

    ASTNode* TRHierarchy::visitFuncDecl(FuncDecl* ast, ASTNode* n) {
        ast->id->visit(this, nullptr);
        ast->pl->visit(this, nullptr);
        ast->s->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitIdent(Ident* ast, ASTNode* n) {
        return nullptr;
    }

    ASTNode* TRHierarchy::visitIfStmt(IfStmt* ast, ASTNode* n) {
        ast->e->visit(this, nullptr);
        ast->s->visit(this, nullptr);
        ast->ows->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitInitExpr(InitExpr* ast, ASTNode* n) {
        ast->e->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitLiteralExpr(LiteralExpr* ast, ASTNode* n) {
        return nullptr;
    }

    ASTNode* TRHierarchy::visitLogicStmt(LogicStmt* ast, ASTNode* n) {
        ast->ifs->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitOnceDecl(OnceDecl* ast, ASTNode* n) {
        ast->al->visit(this, nullptr);
    	return nullptr;
    }

    ASTNode* TRHierarchy::visitOperator(Operator* ast, ASTNode* n) {
        return nullptr;
    }

    ASTNode* TRHierarchy::visitOtherwiseStmt(OtherwiseStmt* ast, ASTNode* n) {
        if (ast->els != nullptr) {
            ast->els->visit(this, nullptr);
        } else {
            ast->efs->visit(this, nullptr);
            ast->ows->visit(this, nullptr);
        }
        return nullptr;
    }

    ASTNode* TRHierarchy::visitParaDecl(ParaDecl* ast, ASTNode* n) {
        ast->id->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitParaList(ParaList* ast, ASTNode* n) {
        ast->pd->visit(this, nullptr);
        ast->pl->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitRegressionStmt(RegressionStmt* ast, ASTNode* n) {
        ast->id->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitReturnStmt(ReturnStmt* ast, ASTNode* n) {
        ast->e->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitTRNode(TRNode* ast, ASTNode* n) {

        std::string vname = dynamic_cast<Ident&>(*(ast->id.get())).name;

        // push onto stack
        currNode.push(vname);

        // if vertex doesn't exist make one and insert to map
        if (vertmap.find(vname) == vertmap.end()) {
            TRVertex v(vname, nodeShape);
            vertmap.insert(
                std::pair<std::string, Graph::vertex_descriptor>(vname,boost::add_vertex(v, hierarchy))
            );
        }

        // visit all conditions
        ast->cs->visit(this, nullptr);

        // pop off stack
        currNode.pop();

        return nullptr;
    }

    ASTNode* TRHierarchy::visitTRProgList(TRProgList* ast, ASTNode* n) {
        ast->d->visit(this, nullptr);
        ast->pl->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitTRProgram(TRProgram* ast, ASTNode* n) {
        ast->pl->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitUnaryExpr(UnaryExpr* ast, ASTNode* n) {
        ast->o->visit(this, nullptr);
        ast->e->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitVarDecl(VarDecl* ast, ASTNode* n) {
        ast->id->visit(this, nullptr);
        ast->e->visit(this, nullptr);
        return nullptr;
    }

    ASTNode* TRHierarchy::visitVarExpr(VarExpr* ast, ASTNode* n) {
        ast->id->visit(this, nullptr);
        return nullptr;
    }

    // END INCLUSION POINT

}
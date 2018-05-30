#ifndef LOGIC_STMT_H
#define LOGIC_STMT_H

namespace TR {

    /**
     * Logic Statement Node
     *
     * Node of logic statement, part of function declaration
     * nodes
     */
    class LogicStmt : public ASTStmt {

    public:

        /// Remove default constructor for this
        LogicStmt() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param ifsAST If statement child of this node (should be type IfStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        LogicStmt(ASTStmt* ifsAST, const location& l, const std::string& f) :
                ifs(ifsAST),
                ASTStmt(l,f) { ifsAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param ifsAST If statement child of this node (should be type IfStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        LogicStmt(ASTStmt* ifsAST, const location& l, const std::string& f, const std::string& src) :
                ifs(ifsAST),
                ASTStmt(l,f,src) { ifsAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~LogicStmt() {}

        /**
         * Visit Function
         *
         * Calls the abstracted visitor function
         * See Visitor Pattern
         *
         * @param v Pointer to the visitor object
         * @param n Optional pointer to AST node
         * @return Optionally returns a pointer to an AST node
         */
        virtual ASTNode* visit(Visitor* v, ASTNode* n);

        std::shared_ptr<ASTStmt> ifs;
    };

}

#endif
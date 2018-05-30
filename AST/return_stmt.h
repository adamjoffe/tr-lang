#ifndef RETURN_STMT_H
#define RETURN_STMT_H

namespace TR {

    /**
     * Return Statement Node
     *
     * Node of return statement, part of function declaration
     * nodes
     */
    class ReturnStmt : public ASTStmt {

    public:

        /// Remove default constructor for this
        ReturnStmt() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param eAST Expr statement child of this node (should be type ASTExpr)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        ReturnStmt(ASTExpr* eAST, const location& l, const std::string& f) :
                e(eAST),
                ASTStmt(l,f) { eAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param eAST Expr statement child of this node (should be type ASTExpr)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ReturnStmt(ASTExpr* eAST, const location& l, const std::string& f, const std::string& src) :
                e(eAST),
                ASTStmt(l,f,src) { eAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~ReturnStmt() {}

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

        std::shared_ptr<ASTExpr> e;
    };
}

#endif
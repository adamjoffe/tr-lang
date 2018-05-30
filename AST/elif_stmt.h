#ifndef ELIF_STMT_H
#define ELIF_STMT_H

namespace TR {

    /**
     * Elif Statement Node
     *
     * Node of elif statment, part of function declaration
     * nodes
     */
    class ElifStmt : public ASTStmt {

    public:

        /// Remove default construtor for this
        ElifStmt() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param eAST Expr statement child of this node (should be type ASTExpr)
         * @param sAST Expr statement child of this node (should be type ASTStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        ElifStmt(ASTExpr* eAST, ASTStmt* sAST, const location& l, const std::string& f) :
                e(eAST),
                s(sAST),
                ASTStmt(l,f) { eAST->parent = sAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param eAST Expr statement child of this node (should be type ASTExpr)
         * @param sAST Expr statement child of this node (should be type ASTStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ElifStmt(ASTExpr* eAST, ASTStmt* sAST, const location& l, const std::string& f, const std::string& src) :
                e(eAST),
                s(sAST),
                ASTStmt(l,f,src) { eAST->parent = sAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~ElifStmt() {}

        /**
         * Visit Function
         *
         * Calls the abstracted visitor function
         * See Visitor Pattern
         *
         * @param v Pointer to the visitor object
         * @param n Optional pointer to AST node
         * @return Optionally returns pointer to an AST node
         */
        virtual ASTNode* visit(Visitor* v, ASTNode* n);

        std::shared_ptr<ASTExpr> e;
        std::shared_ptr<ASTStmt> s;
    };

}

#endif
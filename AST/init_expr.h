#ifndef INIT_EXPR_H
#define INIT_EXPR_H

namespace TR {

    /**
     * Initialiser Expression Node
     *
     * Node for initialiser expression, part of variable declaration
     * nodes
     */
    class InitExpr : public ASTExpr {

    public:

        /// Remove default constructor for this
        InitExpr() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param eAST Expression child of this node (should be type ASTExpr)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        InitExpr(ASTExpr* eAST, const location& l, const std::string& f) :
                e(eAST),
                ASTExpr(l,f) { eAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param eAST Expression child of this node (should be type ASTExpr)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        InitExpr(ASTExpr* eAST, const location& l, const std::string& f, const std::string& src) :
                e(eAST),
                ASTExpr(l,f,src) { eAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~InitExpr() {}

        /**
         * Visit Function
         *
         * All nodes must implement this function
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

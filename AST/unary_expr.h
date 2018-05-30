#ifndef UNARY_EXPR_H
#define UNARY_EXPR_H

namespace TR {

    /**
     * Unary Expression Node
     *
     * Node for unary expressions, part of the general nodes
     */
    class UnaryExpr : public ASTExpr {

    public:

        /// Remove default construtor for this
        UnaryExpr() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param oAST Operator child of this node (should be type Operator)
         * @param eAST Expression child of this node (should be type ASTExpr)
         * @param l Location related token in source code
         * @param f File name of related symbol(s) in source code
         */
        UnaryExpr(ASTTerminal* oAST, ASTExpr* eAST, const location& l, const std::string& f) :
                o(oAST),
                e(eAST),
                ASTExpr(l,f) { oAST->parent = eAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param oAST Operator child of this node (should be type Operator)
         * @param eAST Expression child of this node (should be type ASTExpr)
         * @param l Location related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        UnaryExpr(ASTTerminal* oAST, ASTExpr* eAST, const location& l, const std::string& f, const std::string& src) :
                o(oAST),
                e(eAST),
                ASTExpr(l,f,src) { oAST->parent = eAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~UnaryExpr() {}

        /**
         * Visit Function
         *
         * Calls the abstracted visit function
         * See Visitor Pattern
         *
         * @param v Pointer to the visitor object
         * @param n Optional pointer to AST node
         * @return Optionally returns a pointer to an AST node
         */
        virtual ASTNode* visit(Visitor* v, ASTNode* n);

        std::shared_ptr<ASTTerminal> o;
        std::shared_ptr<ASTExpr> e;
    };

}

#endif
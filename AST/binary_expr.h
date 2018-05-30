#ifndef BINARY_EXPR_H
#define BINARY_EXPR_H

namespace TR {

    /**
     * Binary Expression Node
     *
     * Node for binary expressions, part of the general nodes
     */
    class BinaryExpr : public ASTExpr {

    public:

        /// Remove default constructor for this
        BinaryExpr() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param e1AST First expression child of this node (should be type ASTExpr)
         * @param oAST Operator child of this node (should be type Operator)
         * @param e2AST Second expression child of this node (should be type ASTExpr)
         * @param l Location related token in source code
         * @param f File name of related symbol(s) in source code
         */
        BinaryExpr(ASTExpr* e1AST, ASTTerminal* oAST, ASTExpr* e2AST, const location& l, const std::string& f) :
                e1(e1AST),
                o(oAST),
                e2(e2AST),
                ASTExpr(l,f) {
            e1AST->parent = oAST->parent = e2AST->parent = this;
        }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param e1AST First expression child of this node (should be type ASTExpr)
         * @param oAST Operator child of this node (should be type Operator)
         * @param e2AST Second expression child of this node (should be type ASTExpr)
         * @param l Location related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        BinaryExpr(ASTExpr* e1AST, ASTTerminal* oAST, ASTExpr* e2AST, const location& l, const std::string& f, const std::string& src) :
                e1(e1AST),
                o(oAST),
                e2(e2AST),
                ASTExpr(l,f,src) {
            e1AST->parent = oAST->parent = e2AST->parent = this;
        }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~BinaryExpr() {}

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

        std::shared_ptr<ASTExpr> e1;
        std::shared_ptr<ASTTerminal> o;
        std::shared_ptr<ASTExpr> e2;
    };

}

#endif
#ifndef VAR_EXPR_H
#define VAR_EXPR_H

namespace TR {

    /**
     * Variable Expression Node
     *
     * Node for variable expression, part of the general nodes
     */
    class VarExpr : public ASTExpr {

    public:

        /// Remove default constructor for this
        VarExpr() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST Id expression child of this node (should be type Ident)
         * @param l Location related token in source code
         * @param f File name of related symbol(s) in source code
         */
        VarExpr(ASTTerminal* idAST, const location& l, const std::string& f) :
                id(idAST),
                ASTExpr(l,f) { idAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST Id expression child of this node (should be type Ident)
         * @param l Location related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        VarExpr(ASTTerminal* idAST, const location& l, const std::string& f, const std::string& src) :
                id(idAST),
                ASTExpr(l,f,src) { idAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~VarExpr() {}

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

        std::shared_ptr<ASTTerminal> id;
    };


}

#endif
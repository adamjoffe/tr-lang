#ifndef ARG_H
#define ARG_H

namespace TR {

    /**
     * Arg Node
     *
     * Node for arg declarations, part of general nodes
     */
    class Arg : public ASTExpr {

    public:

        /// Remove default constructor for this
        Arg() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param eAST Expression child of this node (should be type ASTExpr)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        Arg(ASTExpr* eAST, const location& l, const std::string& f) :
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
        Arg(ASTExpr* eAST, const location& l, const std::string& f, const std::string& src) :
                e(eAST),
                ASTExpr(l,f,src) { eAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~Arg() {}

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
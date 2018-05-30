#ifndef COND_H
#define COND_H

namespace TR {

    /**
     * Cond Node
     *
     * Node of condition, part of TR Node nodes
     */
    class Cond : public ASTStmt {

    public:

        /// Remove default constructor for this
        Cond() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST Id child of this node (should be type Ident)
         * @param eAST Expression of this node (should be type ASTExpr)
         * @param asAST Action statement of this node (should be type ActionStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        Cond(ASTTerminal* idAST, ASTExpr* eAST, ASTStmt* asAST, const location& l, const std::string& f) :
                id(idAST),
                e(eAST),
                as(asAST),
                ASTStmt(l,f) {
            idAST->parent = eAST->parent = asAST->parent = this;
        }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param idAST Id child of this node (should be type Ident)
         * @param eAST Expression of this node (should be type ASTExpr)
         * @param asAST Action statement of this node (should be type ActionStmt)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        Cond(ASTTerminal* idAST, ASTExpr* eAST, ASTStmt* asAST, const location& l, const std::string& f, const std::string& src) :
                id(idAST),
                e(eAST),
                as(asAST),
                ASTStmt(l,f,src) {
            idAST->parent = eAST->parent = asAST->parent = this;
        }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~Cond() {}

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
        std::shared_ptr<ASTExpr> e;
        std::shared_ptr<ASTStmt> as;
    };

}

#endif
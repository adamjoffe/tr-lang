#ifndef ONCE_DECL_H
#define ONCE_DECL_H

namespace TR {

    /**
     * TR Node Node
     *
     * Node for TR Node, part of TR declaration nodes
     */
    class OnceDecl : public ASTDecl {

    public:

        /// Remove default constructor for this
        OnceDecl() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param alAST Action list of this node (should be type ActionList)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        OnceDecl(ASTList* alAST, const location& l, const std::string& f) :
                isComplete(false),
                al(alAST),
                ASTDecl(nullptr, DeclType::ONCE_DECL, l, f) {
            alAST->parent = this;
        }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param alAST Action list of this node (should be type ActionList)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        OnceDecl(ASTList* alAST, const location& l, const std::string& f, const std::string& src) :
                isComplete(false),
                al(alAST),
                ASTDecl(nullptr, DeclType::ONCE_DECL, l, f, src) {
            alAST->parent = this;
        }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~OnceDecl() {}

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

        bool isComplete;
        std::shared_ptr<ASTList> al;
    };

}

#endif
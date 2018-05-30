#ifndef TR_PROG_LIST_H
#define TR_PROG_LIST_H

namespace TR {

    /**
     * TR Program List
     *
     * List of high level program declarations
     */
    class TRProgList : public ASTList {

    public:

        /// Remove default constructor for this
        TRProgList() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param dAST Declarator child of this node (should be type ASTDecl)
         * @param plAST List child of this node (should be type TRProgList)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        TRProgList(ASTDecl* dAST, ASTList* plAST, const location& l, const std::string& f) :
                d(dAST),
                pl(plAST),
                ASTList(l,f) { dAST->parent = plAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param dAST Declarator child of this node (should be type ASTDecl)
         * @param plAST List child of this node (should be type TRProgList)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        TRProgList(ASTDecl* dAST, ASTList* plAST, const location& l, const std::string& f, const std::string& src) :
                d(dAST),
                pl(plAST),
                ASTList(l,f,src) { dAST->parent = plAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~TRProgList() {}

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

        /**
         * Empty Check
         *
         * Checks if this instance of the list is empty
         * Always returns false since this is a non empty implementation
         *
         * @return True if the list is empty
         */
        bool isEmpty() { return false; }

        std::shared_ptr<ASTDecl> d;
        std::shared_ptr<ASTList> pl;
    };

}

#endif

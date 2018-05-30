#ifndef ARG_LIST_H
#define ARG_LIST_H

namespace TR {

    /**
     * Arg List
     *
     * List for arguments, part of the general nodes
     */
    class ArgList : public ASTList {

    public:

        /// Remove default constructor for this
        ArgList() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param aAST Argument declaration of the child node (should be type Arg)
         * @param alAST Argument list of the child node (should be type ASTList)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        ArgList(ASTExpr* aAST, ASTList* alAST, const location& l, const std::string& f) :
                a(aAST),
                al(alAST),
                ASTList(l,f) { aAST->parent = alAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param aAST Argument declaration of the child node (should be type Arg)
         * @param alAST Argument list of the child node (should be type ASTList)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ArgList(ASTExpr* aAST, ASTList* alAST, const location& l, const std::string& f, const std::string& src) :
                a(aAST),
                al(alAST),
                ASTList(l,f,src) { aAST->parent = alAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~ArgList() {}

        /**
         * Visit Function
         *
         * Class the abstracted visitor function
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
        virtual bool isEmpty() { return false; }

        std::shared_ptr<ASTExpr> a;
        std::shared_ptr<ASTList> al;
    };

}

#endif
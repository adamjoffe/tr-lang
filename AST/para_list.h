#ifndef PARA_LIST_H
#define PARA_LIST_H

namespace TR {

    /**
     * Para List
     *
     * List for parameters, part of the general nodes
     */
    class ParaList : public ASTList {

    public:

        /// Remove default constructor for this
        ParaList() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param pdAST Parameter declaration of the child node (should be type ParaDecl)
         * @param plAST Parameter list of the child node (should be type ParaList)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        ParaList(ASTDecl* pdAST, ASTList* plAST, const location& l, const std::string& f) :
                pd(pdAST),
                pl(plAST),
                ASTList(l,f) { pdAST->parent = plAST->parent = this; }

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param pdAST Parameter declaration of the child node (should be type ParaDecl)
         * @param plAST Parameter list of the child node (should be type ParaList)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ParaList(ASTDecl* pdAST, ASTList* plAST, const location& l, const std::string& f, const std::string& src) :
                pd(pdAST),
                pl(plAST),
                ASTList(l,f,src) { pdAST->parent = plAST->parent = this; }

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~ParaList() {}

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

        std::shared_ptr<ASTDecl> pd;
        std::shared_ptr<ASTList> pl;
    };

}

#endif
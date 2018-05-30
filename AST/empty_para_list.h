#ifndef EMPTY_PARA_LIST_H
#define EMPTY_PARA_LIST_H

namespace TR {

    /**
     * Empty Parameter List
     *
     * Empty list for parameters, part of the generals
     * nodes
     */
    class EmptyParaList : public ASTList {

    public:

        /// Remove default constructor for this
        EmptyParaList() = delete;

        /**
         * Tree Constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         */
        EmptyParaList(const location& l, const std::string& f) : ASTList(l,f) {}

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        EmptyParaList(const location& l, const std::string& f, const std::string& src) : ASTList(l,f,src) {}

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~EmptyParaList() {}

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
         * Always returns true since this is an empty implementation
         *
         * @return True if the list is empty
         */
        virtual bool isEmpty() { return true; }

    };

}

#endif
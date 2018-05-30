#ifndef AST_LIST_H
#define AST_LIST_H

namespace TR {

    /**
     * Abstract List Class
     *
     * Abstract list implements nodes that have repeated syntax
     * in list form
     */
    class ASTList : public ASTNode {

    public:

        /// Remove default constructor for this
        ASTList() = delete;

        /**
         * Location constructor
         *
         * Constructs AST node with a location in the source code
         *
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         */
        ASTList(const location& l, const std::string& f) : ASTNode(l,f) {}

        /**
         * Source code constructor
         *
         * Constructs AST node with a location in the source code
         *
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ASTList(const location& l, const std::string& f, const std::string& src) : ASTNode(l,f,src) {}

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~ASTList() {}

        /**
         * Visit Function
         *
         * All nodes must implement this function
         * See Visitor Pattern
         *
         * @param v Pointer to the visitor object
         * @param n Optional pointer to AST node
         * @return Optionally returns a pointer to an AST node
         */
        virtual ASTNode* visit(Visitor* v, ASTNode* n) = 0;

        /**
         * Empty Check
         *
         * Checks if this instance of the list is empty
         * Abstract as all list implementation must implement this
         *
         * @return True if the list is empty
         */
        virtual bool isEmpty() = 0;
    };
}

#endif

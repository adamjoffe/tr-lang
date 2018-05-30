#ifndef AST_TERMINAL_H
#define AST_TERMINAL_H

namespace TR {

    /**
     * Abstract Terminal Class
     *
     * Abstract terminal implements nodes that are terminal
     * components in the program
     */
    class ASTTerminal : public ASTNode {

    public:

        /// Remove default constructor for this
        ASTTerminal() = delete;

        /**
         * Location constructor
         *
         * Constructs AST node with a location in the source code
         *
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         */
        ASTTerminal(const location& l, const std::string& f) : ASTNode(l,f) {}

        /**
         * Source code constructor
         *
         * Constructs AST node with a location in the source code
         *
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ASTTerminal(const location& l, const std::string& f, const std::string& src) : ASTNode(l,f,src) {}

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~ASTTerminal() {}

        /**
         * Visit Function
         *
         * All nodes must implement this function
         * See Visitor Pattern
         *
         * @param v Pointer to the visitor object
         * @param n Optional pointer to AST node
         * @return Optionally returns pointer to an AST node
         */
        virtual ASTNode* visit(Visitor* v, ASTNode* n) = 0;

    };

}

#endif
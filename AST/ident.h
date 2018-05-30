#ifndef IDENT_H
#define IDENT_H

#include <string>

namespace TR {

    /**
     * ID Node
     *
     * Ident node of variable, func name or tr node,
     * part of terminal nodes
     */
    class Ident : public ASTTerminal {

    public:

        /// Remove default constructor for this
        Ident() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param n Name of the Id (should be type std::string)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        Ident(const std::string& n, const location& l, const std::string& f) :
                name(n), ASTTerminal(l,f) {}

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param n Name of the Id (should be type std::string)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        Ident(const std::string& n, const location& l, const std::string& f, const std::string& src) :
                name(n), ASTTerminal(l,f,src) {}

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~Ident() {}

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
        
        const std::string name;
    };

}

#endif
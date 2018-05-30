#ifndef OPERATOR_H
#define OPERATOR_H

namespace TR {

    enum class OP { OR, AND, EQEQ, NOTEQ, NOT,
                LT, LTEQ, GT, GTEQ,
                PLUS, MINUS, MULT, DIV};

    /**
     * Operator Node
     *
     * Node for operator, part of the terminal nodes
     */
    class Operator : public ASTTerminal {

    public:

        /// Remove default constructor for this
        Operator() = delete;

        /**
         * Tree constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param op Operator enum of this node (should be type Op)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         */
        Operator(OP op, const location& l, const std::string& f) :
                o(op), ASTTerminal(l,f) {}

        /**
         * Source code constructor
         *
         * Constructs node of the tree given the child node(s)
         *
         * @param op Operator enum of this node (should be type Op)
         * @param l Location of related token in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        Operator(OP op, const location& l, const std::string& f, const std::string& src) :
                o(op), ASTTerminal(l,f,src) {}

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~Operator() {}

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

        OP o;
    };

}

#endif
#ifndef AST_EXPR_H
#define AST_EXPR_H

#include "../tr_types.h"

namespace TR {

    /**
     * Abstract Expression Class
     *
     * Abstract expression implements nodes that are an
     * expression in the program
     */
    class ASTExpr : public ASTNode {

    public:

        /// Remove default constructor for this
        ASTExpr() = delete;

        /**
         * Location Constructor
         *
         * Constructs AST node with a location in the source code
         *
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         */
        ASTExpr(const location& l, const std::string& f) :
                ASTExpr(new GVar(), l, f) {}

        /**
         * Generic Variable Constructor
         *
         * Constructs AST node with a generic variable and location
         *
         * @param v Generic variable of value
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         */
        ASTExpr(GVar* v, const location& l, const std::string& f) :
            val(v), stat_calc(false), ASTNode(l,f) {}

        /**
         * Location Source Code Constructor
         *
         * Constructs AST node with a location in the source code
         *
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ASTExpr(const location& l, const std::string& f, const std::string& src) :
                ASTExpr(new GVar(), l, f, src) {}

        /**
         * Generic Variable Source Code Constructor
         *
         * Constructs AST node with a generic variable and location
         *
         * @param v Generic variable of value
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ASTExpr(GVar* v, const location& l, const std::string& f, const std::string& src) :
            val(v), stat_calc(false), ASTNode(l,f,src) {}

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~ASTExpr() { delete val; }

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

        bool stat_calc; /// if the value has been statically calculated
        GVar* val;
    };

}

#endif
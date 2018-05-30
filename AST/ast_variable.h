#ifndef AST_VARIABLE_H
#define AST_VARIABLE_H

#include "ast_decl.h"

namespace TR {

    /**
     * Abstract Declaration Class
     *
     * Abstract declaration implements nodes that declare parts
     * of the program
     */
    class ASTVariable : public ASTDecl {

    public:

        /// Remove default constructor for this
        ASTVariable() = delete;

        /**
         * Location constructor
         *
         * Constructs AST node with a location in the source code
         *
         * @param idAST Identifier related to declaration (should be type Ident)
         * @param declT Declaration type enum of the declaration
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         */
        ASTVariable(ASTTerminal* idAST, DeclType declT, const location& l, const std::string& f) :
                ASTDecl(idAST,declT,l,f) {}

        /**
         * Source code constructor
         *
         * Constructs AST node with a location in the source code
         *
         * @param idAST Identifier related to declaration (should be type Ident)
         * @param declT Declaration type enum of the declaration
         * @param l Location of related symbol(s) in source code
         * @param f File name of related symbol(s) in source code
         * @param src Source code of related node
         */
        ASTVariable(ASTTerminal* idAST, DeclType declT, const location& l, const std::string& f, const std::string& src) :
                ASTDecl(idAST,declT,l,f,src) {}

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~ASTVariable() {}

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
         * Get Variable Value
         *
         * Provides a pointer to a GVar with the value of the variable
         * stored in this variable
         *
         * @return Pointer to GVar containing value of variable
         */
        virtual GVar* getValue() = 0;

        /**
         * Store Variable Value
         *
         * Stores a value in the variable given by a pointer to a GVar with the
         * same type as this variable.
         *
         * @param v Pointer to a GVar with value to store in this variable
         */
        virtual void storeValue(GVar* v) = 0;
    };

}

#endif
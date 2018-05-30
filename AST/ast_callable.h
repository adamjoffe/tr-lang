#ifndef AST_CALLABLE_H
#define AST_CALLABLE_H

#include "ast_decl.h"

// return value to throw
#include "../exe-components/return_v.h"

namespace TR {

    /**
     * Abstract Declaration Class
     *
     * Abstract declaration implements nodes that declare parts
     * of the program
     */
    class ASTCallable : public ASTDecl {

    public:

        /// Remove default constructor for this
        ASTCallable() = delete;

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
        ASTCallable(ASTTerminal* idAST, DeclType declT, const location& l, const std::string& f) :
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
        ASTCallable(ASTTerminal* idAST, DeclType declT, const location& l, const std::string& f, const std::string& src) :
                ASTDecl(idAST,declT,l,f,src) {}

        /**
         * Virtual destructor
         *
         * Doesn't need to delete parent
         */
        virtual ~ASTCallable() {}

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
         * Call Function
         *
         * Abstract call function to be implemented by classes
         * that inherit this. Used when calling and evaluating functions
         *
         * @param v Visitor passed to call to walk tree
         * @param n Reference to the FCall node that called
         * @throws ReturnV Return value object of callable
         */
        virtual void call(Visitor* v, ASTNode* n) = 0;

        // need both since only arity used for bi functions
        int arity = 0; /**Arity Number - number of params of this callable**/
        std::vector<ASTVariable*> params; /**list of pointers to paradecl, populated only during SA**/
    };

}

#endif
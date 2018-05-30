#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <exception>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <map>

#include "AST/ast_decl.h"
#include "AST/ast_terminal.h"
#include "tr_types.h"

namespace TR {

    /**
     * Symbol table for looking up variables and function
     * names in the TR language.
     *
     * These are either declared as part of the TR source code
     * or as part of the built-in functions/variables which
     * are called/referenced via pointers
     *
     * The symbol table will double up during execution to update
     * values of any variables used by the TR source code
     *
     * Warning: if a built-in (referencing a C++ variable from the
     * basic/supporting code base) in TR is updated, or changed
     * the change will carry through to outside TR lang due to nature
     * of pointers
     *
     */
    class SymbolTable {
    public:

        /**
         * Default constructor
         */
        SymbolTable();

        /**
         * Insert Entry
         *
         * Adds an entry to the symbol table
         *
         * @param id Id of the symbol, given as a pointer to a string
         * @param dAST Declaration for symbol (func/tr node/variable/para)
         * @return Success code if addition has been successful or not
         */
        bool insert(const std::string& id, ASTDecl* dAST);

        /**
         * Retrieve Entry
         *
         * Checks if the entry exists in the symbol table
         *
         * @param id Id of the symbol, given as a pointer to a string
         * @return Pointer to the declaration of the symbol
         */
        ASTDecl* retrieve(const std::string& id);

        /**
         * Open Scope
         *
         * Increments the scope level
         */
        void openScope();

        /**
         * Close Scope
         *
         * Decrements the scope level
         */
        void closeScope();

        /** 
         * Validates Scopes
         *
         * Checks that all scopes were closed correctly
         *
         * @return True if scope was closed correctly
         */
        bool validate();

        /// allows Debugger to generate debug symbols from the tables data structure
        std::vector< std::unordered_map< std::string, ASTDecl* > >& getTable() { return table; }

    private:
        /// map with scope level keys and values of symbol table
        /// at that scope level
        std::vector< std::unordered_map< std::string, ASTDecl* > > table;
        /// Scope level of the symbol, global == 0
        int scope_level;
    };


    class RegressionTable {
    public:

        /**
         * Default constructor
         */
        RegressionTable();

        /**
         * Insert Entry
         *
         * Adds an entry to the symbol table
         *
         * @param id Id of the symbol, given as a pointer to a string
         * @return Success code if addition has been successful or not
         */
        bool insert(const std::string& id);

        /**
         * Retrieve Entry
         *
         * Checks if the entry exists in the symbol table
         *
         * @param id Id of the symbol, given as a pointer to a string
         * @return True if it's in the table
         */
        bool retrieve(const std::string& id);

        /**
         * Reset Regression Table
         * 
         * Resets the table upon leaving the TRNode
         */
        void reset();

        /** 
         * Validates Scopes
         *
         * Checks that all scopes were closed correctly
         *
         * @return True if scope was closed correctly
         */
        bool validate();

    private:
        /// map id with bool
        //TODO: maybe set value as location and file
        std::unordered_set< std::string > table;
    };

    class ParameterTable {
    public:

        /**
         * Default constructor
         */
        ParameterTable();

        /**
         * Insert Entry
         *
         * Adds an entry to the symbol table
         *
         * @param id Id of the symbol, given as a pointer to a string
         * @return Success code if addition has been successful or not
         */
        bool insert(const std::string& id, ASTDecl* dAST);

        /**
         * Retrieve Entry
         *
         * Checks if the entry exists in the symbol table
         *
         * @param id Id of the symbol, given as a pointer to a string
         * @return Pointer to the declaration of the symbol
         */
        ASTDecl* retrieve(const std::string& id);

        /**
         * Open Scope
         *
         * Increments the scope level
         */
        void openScope();

        /**
         * Close Scope
         *
         * Decrements the scope level
         */
        void closeScope();

        /** 
         * Validates Scopes
         *
         * Checks that all scopes were closed correctly
         *
         * @return True if scope was closed correctly
         */
        bool validate();

    private:
        /// stack of parameter maps for current scope level
        /// add new parameter map frame on each time FCall is made
        std::stack< std::unordered_map< std::string, ASTDecl* > > table;
    };

}

#endif
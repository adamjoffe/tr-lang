#include "tr_symbol_table.h"

#include <iostream>

namespace TR {

    SymbolTable::SymbolTable() :
        scope_level(0) {
            table.push_back(std::unordered_map< std::string, ASTDecl* >());
        }

    bool SymbolTable::insert(const std::string& id, ASTDecl* dAST) {
        // check if id already exists at this level
        if(table[scope_level].count(id)>0) {
            return false;
        }

        // insert at this level
        table[scope_level].insert(
                std::pair<std::string,ASTDecl*>(id, dAST)
        );

        return true;
    }

    ASTDecl* SymbolTable::retrieve(const std::string& id) {
        // check if entry exists
        for (int i = scope_level; i >= 0; --i) {
            if (table[i].count(id) > 0) {
                return table[i].find(id)->second;
            }
        }
        // return nothing as not found
        return nullptr;
    }

    void SymbolTable::openScope() {
        ++scope_level;
        table.push_back(std::unordered_map< std::string, ASTDecl* >());
    }

    void SymbolTable::closeScope() {
        if (scope_level == 0) {
            throw std::runtime_error("Cannot close scope beyond global level");
        }
        table.pop_back(); // remove last element
        --scope_level;
    }

    bool SymbolTable::validate() {
        return scope_level == 0;
    }

    RegressionTable::RegressionTable() : 
        table(std::unordered_set< std::string >()) {}

    bool RegressionTable::insert(const std::string& id) {
        // check if id already exists at this level
        if (table.count(id)>0) {
            return false;
        }

        // insert at this level
        table.insert(id);

        return true;
    }

    bool RegressionTable::retrieve(const std::string& id) {
        // check if entry exists
        if (table.count(id) > 0) {
            return true;
        }
        // return nothing as not found
        return false;
    }

    void RegressionTable::reset() {
        table.clear();
    }

    bool RegressionTable::validate() {
        return table.size() == 0;
    }

    ParameterTable::ParameterTable() :
        table(std::stack< std::unordered_map< std::string, ASTDecl* > >()) {}

    bool ParameterTable::insert(const std::string& id, ASTDecl* dAST) {
        // check if id already exists at this level
        if (table.top().count(id)>0) {
            return false;
        }

        // insert in this map
        table.top().insert(
                std::pair<std::string,ASTDecl*>(id, dAST)
        );

        return true;
    }

    ASTDecl* ParameterTable::retrieve(const std::string& id) {
        // check if entry exists
        if (table.top().count(id)>0) {
            return table.top().find(id)->second;
        }
        // return nothing as not found
        return nullptr;
    }

    void ParameterTable::openScope() {
        table.push(std::unordered_map< std::string, ASTDecl* >());
    }

    void ParameterTable::closeScope() {
        table.pop();
    }

    bool ParameterTable::validate() {
        return table.size() == 0;
    }

}
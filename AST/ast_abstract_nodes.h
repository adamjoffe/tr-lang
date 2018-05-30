#ifndef AST_ABSTRACT_NODES_H
#define AST_ABSTRACT_NODES_H

// Include next level AST
#include "ast_node.h" // always first, since all aggregates this
#include "ast_expr.h"
#include "ast_list.h"
#include "ast_stmt.h"
#include "ast_terminal.h"
#include "ast_decl.h" // always after terminal, since this aggregates it
#include "ast_variable.h" // always after decl, since this aggregates it
#include "ast_callable.h" // always after decl and variable, since this aggregates it

#endif
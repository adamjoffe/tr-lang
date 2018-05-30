%skeleton "lalr1.cc"
%require "3.0"
%defines "tr_parser.h"
%define parser_class_name { TRParser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { TR }
%code requires
{
    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdint.h>
    #include "AST/abstract_visitor.h"

    namespace TR {
        class TRScanner;
        class TRInterpreter;
    }
}

%code top
{
    #include "tr_scanner.h"
    #include "tr_parser.h"
    #include "tr_interpreter.h"
    
    // Parser expects to call a function yylex, with configured params to get next token
    // So setup macro to allow that to happen
    #define yylex(scanner) scanner.get_next_token()

    // shorthand macro for getting token related file
    #define TOK_FILE scanner.currentFile()
    #define CAPTURING_SOURCE scanner.is_capturing()
}

%lex-param { TR::TRScanner& scanner }
%parse-param { TR::TRScanner& scanner }
%parse-param { TR::TRInterpreter& driver }
%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%token                  END         0   "end of file"
%token                  ERROR           "ERROR"

%token  <int>           INT             "int";
%token  <double>        DOUBLE          "double";
%token  <bool>          BOOL            "bool";
%token  <std::string>   STRING          "string";
%token  <std::string>   ID              "ID";

%token                  OR              "or"
%token                  AND             "and"
%token                  NOT             "not"
%token                  IF              "if"
%token                  ELIF            "elif"
%token                  ELSE            "else"
%token                  ACHIEVES        "achieves"
%token                  EXIT            "exit"
%token                  BLACKBOARD      "blackboard"
%token                  INIT            "init"
%token                  ONCE            "once"

%token                  VAR             "VAR"
%token                  STACK           "STACK"
%token                  MAP             "MAP"
%token                  LIST            "LIST"

%token                  INT_T           "INT"
%token                  DOUBLE_T        "DOUBLE"
%token                  BOOL_T          "BOOL"
%token                  STRING_T        "STRING"
%token                  VECTOR_T        "VECTOR"

%token                  PLUS            "+"
%token                  MINUS           "-"
%token                  MULT            "*"
%token                  DIV             "/"
%token                  LT              "<"
%token                  LTEQ            "<="
%token                  GT              ">"
%token                  GTEQ            ">="
%token                  EQEQ            "=="
%token                  NOTEQ           "!="
%token                  EQ              "="

%token                  SEMICOL         ";"
%token                  COMMA           ","
%token                  ARROW           "->"
%token                  COL             ":"
%token                  BLOCK           ":-"
%token                  DOT             "."

%token                  LCURL           "{"
%token                  RCURL           "}"
%token                  LPAREN          "("
%token                  RPAREN          ")"

/*----Grammer Tree Nodes----*/
/* Type is the top level abstract type, */
/* i.e. List/Stmt/Expr/etc              */

/* top level */
%type   <TR::ASTList*>          tr-prog-list

/* blackboard definitions */
%type  <TR::ASTDecl*>           blackboard-decl
%type  <std::string>            struct-type tr-type

/* variable definition */
%type  <TR::ASTDecl*>           var-decl
%type  <TR::ASTExpr*>           initialiser

/* function definition */
%type  <TR::ASTDecl*>           func-decl
%type  <TR::ASTStmt*>           stmt logic-stmt if-stmt otherwise-stmt
%type  <TR::ASTStmt*>           elif-stmt else-stmt return-stmt

/* TR node definition */
%type  <TR::ASTDecl*>           tr-node
%type  <TR::ASTStmt*>           cond-stmt cond action-stmt regr-stmt
%type  <TR::ASTList*>           action-list
%type  <TR::ASTStmt*>           action

/* once definition */
%type   <TR::ASTDecl*>          once-decl

/* General components */
%type   <TR::ASTTerminal*>      identifier
%type   <TR::ASTList*>          para-list-opt para-list
%type   <TR::ASTDecl*>          para-decl
%type   <TR::ASTList*>          arg-list-opt arg-list
%type   <TR::ASTExpr*>          arg
%type   <TR::ASTStmt*>          expr-stmt assign-stmt exit-stmt
%type   <TR::ASTExpr*>          expr or-expr and-expr equality-expr rel-expr
%type   <TR::ASTExpr*>          additive-expr mult-expr unary-expr primary-expr
%type   <TR::ASTExpr*>          fcall bbcall
%type   <TR::ASTExpr*>          var-expr literal-expr

/* Vector components */
%type   <TR::Vector>            vectorliteral
%type   <double>                vval vlit


/*----Grammer Node Destructors----*/
// TODO: impl this

/* define start token to "tr_program" */
%start tr-program

%%

/* Top Level */
tr-program : tr-prog-list
    {
        if (CAPTURING_SOURCE) {
            driver.ast = new TRProgram($1,@$,TOK_FILE, 
                $1->src_code);
        } else {
            driver.ast = new TRProgram($1,@$,TOK_FILE);
        }
    }

tr-prog-list : END
    {
        if (CAPTURING_SOURCE) {
            $$ = new EmptyTRProgList(@$,TOK_FILE,
                "");
        } else {
            $$ = new EmptyTRProgList(@$,TOK_FILE);
        }
    }
    
    | blackboard-decl tr-prog-list
    {
        if (CAPTURING_SOURCE) {
            $$ = new TRProgList($1, $2, @$, TOK_FILE,
                $1->src_code + "\n" + $2->src_code);
        } else {
            $$ = new TRProgList($1,$2,@$,TOK_FILE);
        }
    }

    | var-decl tr-prog-list
    {
        if (CAPTURING_SOURCE) {
            $$ = new TRProgList($1,$2,@$,TOK_FILE, 
                $1->src_code + "\n" + $2->src_code);
        } else {
            $$ = new TRProgList($1,$2,@$,TOK_FILE);
        }
    }

    | func-decl tr-prog-list
    {
        if (CAPTURING_SOURCE) {
            $$ = new TRProgList($1,$2,@$,TOK_FILE, 
                $1->src_code + "\n" + $2->src_code);
        } else {
            $$ = new TRProgList($1,$2,@$,TOK_FILE);
        }
    }

    | tr-node tr-prog-list
    {
        if (CAPTURING_SOURCE) {
            $$ = new TRProgList($1,$2,@$,TOK_FILE, 
                $1->src_code + "\n" + $2->src_code);
        } else {
            $$ = new TRProgList($1,$2,@$,TOK_FILE);
        }
    }

    | once-decl tr-prog-list
    {
        if (CAPTURING_SOURCE) {
            $$ = new TRProgList($1,$2,@$,TOK_FILE,
                $1->src_code + "\n" + $2->src_code);
        } else {
            $$ = new TRProgList($1,$2,@$,TOK_FILE);
        }
    }

/* Blackboard Definition */
blackboard-decl : INIT identifier struct-type tr-type
    {
        if (CAPTURING_SOURCE) {
            $$ = new BlackboardDecl($2,$3,$4,@$,TOK_FILE,
                $2->src_code + " " + $3 + " " + $4);
        } else {
            $$ = new BlackboardDecl($2,$3,$4,@$,TOK_FILE);
        }
    }

struct-type : VAR
    {
        $$ = "VAR";
    }

    | STACK
    {
        $$ = "STACK";
    }

    | MAP
    {
        $$ = "MAP";
    }

    | LIST
    {
        $$ = "LIST";
    }

tr-type : INT_T
    {
        $$ = "INT";
    }

    | DOUBLE_T
    {
        $$ = "DOUBLE";
    }

    | BOOL_T
    {
        $$ = "BOOL";
    }

    | STRING_T
    {
        $$ = "STRING";
    }

    | VECTOR_T
    {
        $$ = "VECTOR";
    }

/* Variable Definition */
var-decl : identifier EQ initialiser
    {
        if (CAPTURING_SOURCE) {
            $$ = new VarDecl($1,$3,@$,TOK_FILE, 
                $1->src_code + " = " + $3->src_code);
        } else {
            $$ = new VarDecl($1,$3,@$,TOK_FILE);
        }
    }

initialiser : expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new InitExpr($1,@$,TOK_FILE, 
                $1->src_code);
        } else {
            $$ = new InitExpr($1,@$,TOK_FILE);
        }
    }

/* Function Definition */
func-decl : identifier LPAREN para-list-opt RPAREN EQ stmt
    {
        if (CAPTURING_SOURCE) {
            $$ = new FuncDecl($1,$3,$6,@$,TOK_FILE,
                // function will onyl show declaration not definition
                //$1->src_code + "(" + $3->src_code + ") = \n" + $6->src_code);
                $1->src_code + "(" + $3->src_code + ") =");
        } else {
            $$ = new FuncDecl($1,$3,$6,@$,TOK_FILE);
        }
    }

stmt : logic-stmt
    {
        $$ = $1;
    }

    | return-stmt
    {
        $$ = $1;
    }

logic-stmt : if-stmt
    {
        if (CAPTURING_SOURCE) {
            $$ = new LogicStmt($1,@$,TOK_FILE,
                $1->src_code);
        } else {
            $$ = new LogicStmt($1,@$,TOK_FILE);
        }
    }

if-stmt : IF LPAREN expr RPAREN ARROW stmt otherwise-stmt
    {
        if (CAPTURING_SOURCE) {
            $$ = new IfStmt($3,$6,$7,@$,TOK_FILE,
                "if (" + $3->src_code + ") -> " + $6->src_code + "\n" + $7->src_code);
        } else {
            $$ = new IfStmt($3,$6,$7,@$,TOK_FILE);
        }
    }

otherwise-stmt : else-stmt
    {
        if (CAPTURING_SOURCE) {
            $$ = new OtherwiseStmt($1,@$,TOK_FILE,
                $1->src_code);
        } else {
            $$ = new OtherwiseStmt($1,@$,TOK_FILE);
        }
    }

    | elif-stmt otherwise-stmt
    {
        if (CAPTURING_SOURCE) {
            $$ = new OtherwiseStmt($1,$2,@$,TOK_FILE,
                $1->src_code + "\n" + $2->src_code);
        } else {
            $$ = new OtherwiseStmt($1,$2,@$,TOK_FILE);
        }
    }

elif-stmt : ELIF LPAREN expr RPAREN ARROW stmt
    {
        if (CAPTURING_SOURCE) {
            $$ = new ElifStmt($3,$6,@$,TOK_FILE,
                "elif (" + $3->src_code + ") -> " + $6->src_code);
        } else {
            $$ = new ElifStmt($3,$6,@$,TOK_FILE);
        }
    }

else-stmt : ELSE ARROW stmt
    {
        if (CAPTURING_SOURCE) {
            $$ = new ElseStmt($3,@$,TOK_FILE,
                "else -> " + $3->src_code);
        } else {
            $$ = new ElseStmt($3,@$,TOK_FILE);
        }
    }

return-stmt : expr SEMICOL
    {
        if (CAPTURING_SOURCE) {
            $$ = new ReturnStmt($1,@$,TOK_FILE,
                $1->src_code + ";");
        } else {
            $$ = new ReturnStmt($1,@$,TOK_FILE);
        }
    }

/* TR Node */
tr-node : identifier LPAREN para-list-opt RPAREN BLOCK cond-stmt
    {
        if (CAPTURING_SOURCE) {
            $$ = new TRNode($1,$3,$6,@$,TOK_FILE,
                // node will only show the declaration, not definition
                //$1->src_code + "(" + $3->src_code + ") :- \n" + $6->src_code);
                $1->src_code + "(" + $3->src_code + ") :-");
        } else {
            $$ = new TRNode($1,$3,$6,@$,TOK_FILE);
        }
    }

cond-stmt : BOOL action-stmt
    {
        // BOOL needs to be true, error if it is not
        if (!$1){
            driver.error(@1,"syntax error, unexpected \'false\', expecting \'true\'");
            return 1; // same error code as failing on input
        } else {
            if (CAPTURING_SOURCE) {
                $$ = new CondStmt($2,@$,TOK_FILE,
                    "true" + $2->src_code);
            } else {
                $$ = new CondStmt($2,@$,TOK_FILE);
            }
        }
    }

    | cond cond-stmt
    {
        if (CAPTURING_SOURCE) {
            $$ = new CondStmt($1,$2,@$,TOK_FILE,
                $1->src_code + "\n" + $2->src_code);
        } else {
            $$ = new CondStmt($1,$2,@$,TOK_FILE);
        }
    }

cond : identifier COL expr action-stmt
    {
        if (CAPTURING_SOURCE) {
            $$ = new Cond($1,$3,$4,@$,TOK_FILE,
                $1->src_code + " : " + $3->src_code + $4->src_code);
        } else {
            $$ = new Cond($1,$3,$4,@$,TOK_FILE);
        }
    }

action-stmt : ARROW action-list regr-stmt SEMICOL
    {
        if (CAPTURING_SOURCE) {
            $$ = new ActionStmt($2,$3,@$,TOK_FILE,
                " -> " + $2->src_code + "" + $3->src_code + ";");
        } else {
            $$ = new ActionStmt($2,$3,@$,TOK_FILE);
        }
    }

regr-stmt : ACHIEVES identifier
    {
        if (CAPTURING_SOURCE) {
            $$ = new RegressionStmt($2,@$,TOK_FILE,
                " achieves " + $2->src_code);
        } else {
            $$ = new RegressionStmt($2,@$,TOK_FILE);
        }
    }

action-list : action
    {
        if (CAPTURING_SOURCE) {
            $$ = new ActionList($1,new EmptyActionList(@$,TOK_FILE,""),@$,TOK_FILE,
                $1->src_code);
        } else {
            $$ = new ActionList($1,new EmptyActionList(@$,TOK_FILE),@$,TOK_FILE);
        }
    }

    | action COMMA action-list
    {
        if (CAPTURING_SOURCE) {
            $$ = new ActionList($1,$3,@$,TOK_FILE,
                $1->src_code + ", " + $3->src_code);
        } else {
            $$ = new ActionList($1,$3,@$,TOK_FILE);
        }
    }

action : expr-stmt
    {
        $$ = $1;
    }

    | assign-stmt
    {
        $$ = $1;
    }

    | exit-stmt
    {
        $$ = $1;
    }

/* Once Definition */
once-decl : ONCE LCURL action-list RCURL
    {   
        if (CAPTURING_SOURCE) {
            $$ = new OnceDecl($3,@$,TOK_FILE,
                "once {" + $3->src_code + "}");
        } else {
            $$ = new OnceDecl($3,@$,TOK_FILE);
        }
    }

/* General Components */
identifier : ID
    {
        if (CAPTURING_SOURCE) {
            $$ = new Ident($1,@$,TOK_FILE,
                $1);
        } else {
            $$ = new Ident($1,@$,TOK_FILE);
        }
    }

para-list-opt : /* empty */
    {
        if (CAPTURING_SOURCE) {
            $$ = new EmptyParaList(@$,TOK_FILE,
                "");
        } else {
            $$ = new EmptyParaList(@$,TOK_FILE);
        }
    }

    | para-list
    {
        $$ = $1;
    }

para-list : para-decl
    {
        if (CAPTURING_SOURCE) {
            $$ = new ParaList($1,new EmptyParaList(@1,TOK_FILE,""),@$,TOK_FILE,
                $1->src_code);
        } else {
            $$ = new ParaList($1,new EmptyParaList(@1,TOK_FILE),@$,TOK_FILE);
        }
    }

    | para-decl COMMA para-list
    {
        if (CAPTURING_SOURCE) {
            $$ = new ParaList($1,$3,@$,TOK_FILE,
                $1->src_code + ", " + $3->src_code);
        } else {
            $$ = new ParaList($1,$3,@$,TOK_FILE);
        }
    }

para-decl : identifier
    {
        if (CAPTURING_SOURCE) {
            $$ = new ParaDecl($1,@$,TOK_FILE,
                $1->src_code);
        } else {
            $$ = new ParaDecl($1,@$,TOK_FILE);
        }
    }

arg-list-opt : /* empty */
    {
        if (CAPTURING_SOURCE) {
            $$ = new EmptyArgList(@$,TOK_FILE,
                "");
        } else {
            $$ = new EmptyArgList(@$,TOK_FILE);
        }
    }

    | arg-list
    {
        $$ = $1;
    }

arg-list : arg
    {
        if (CAPTURING_SOURCE) {
            $$ = new ArgList($1,new EmptyArgList(@$,TOK_FILE,""),@$,TOK_FILE,
                $1->src_code);
        } else {
            $$ = new ArgList($1,new EmptyArgList(@$,TOK_FILE),@$,TOK_FILE);
        }
    }

    | arg COMMA arg-list
    {
        if (CAPTURING_SOURCE) {
            $$ = new ArgList($1,$3,@$,TOK_FILE,
                $1->src_code + ", " + $3->src_code);
        } else {
            $$ = new ArgList($1,$3,@$,TOK_FILE);
        }
    }

arg : expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new Arg($1,@$,TOK_FILE,
                $1->src_code);
        } else {
            $$ = new Arg($1,@$,TOK_FILE);
        }
    }

expr-stmt : expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new ExprStmt($1,@$,TOK_FILE,
                $1->src_code);
        } else {
            $$ = new ExprStmt($1,@$,TOK_FILE);
        }
    }

assign-stmt : identifier EQ expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new AssignStmt($1,$3,@$,TOK_FILE,
                $1->src_code + " = " + $3->src_code);
        } else {
            $$ = new AssignStmt($1,$3,@$,TOK_FILE);
        }
    }

exit-stmt : EXIT LPAREN BOOL RPAREN
    {
        if (CAPTURING_SOURCE) {
            $$ = new ExitStmt($3,@$,TOK_FILE,
                "exit(" + std::to_string($3) + ")");
        } else {
            $$ = new ExitStmt($3,@$,TOK_FILE);
        }
    }

    | EXIT LPAREN BOOL COMMA STRING RPAREN
    {
        if (CAPTURING_SOURCE) {
            $$ = new ExitStmt($3,$5,@$,TOK_FILE,
                "exit(" + std::to_string($3) + ", \'" + $5 + "\')");
        } else {
            $$ = new ExitStmt($3,$5,@$,TOK_FILE);
        }
    }

expr : or-expr
    {
        $$ = $1;
    }

or-expr : and-expr
    {
        $$ = $1;
    }

    | or-expr OR and-expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new BinaryExpr($1,new Operator(OP::OR,@2,TOK_FILE,"or"),$3,@$,TOK_FILE,
                $1->src_code + " or " + $3->src_code);
        } else {
            $$ = new BinaryExpr($1,new Operator(OP::OR,@2,TOK_FILE),$3,@$,TOK_FILE);
        }
    }

and-expr : equality-expr
    {
        $$ = $1;
    }

    | and-expr AND equality-expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new BinaryExpr($1,new Operator(OP::AND,@2,TOK_FILE,"and"),$3,@$,TOK_FILE,
                $1->src_code + " and " + $3->src_code);
        } else {
            $$ = new BinaryExpr($1,new Operator(OP::AND,@2,TOK_FILE),$3,@$,TOK_FILE);
        }
    }

equality-expr : rel-expr
    {
        $$ = $1;
    }

    | equality-expr EQEQ rel-expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new BinaryExpr($1,new Operator(OP::EQEQ,@2,TOK_FILE,"=="),$3,@$,TOK_FILE,
                $1->src_code + " == " + $3->src_code);
        } else {
            $$ = new BinaryExpr($1,new Operator(OP::EQEQ,@2,TOK_FILE),$3,@$,TOK_FILE);
        }
    }

    | equality-expr NOTEQ rel-expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new BinaryExpr($1,new Operator(OP::NOTEQ,@2,TOK_FILE,"!="),$3,@$,TOK_FILE,
                $1->src_code + " != " + $3->src_code);
        } else {
            $$ = new BinaryExpr($1,new Operator(OP::NOTEQ,@2,TOK_FILE),$3,@$,TOK_FILE);
        }
    }

rel-expr : additive-expr
    {
        $$ = $1;
    }

    | rel-expr LT additive-expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new BinaryExpr($1,new Operator(OP::LT,@2,TOK_FILE,"<"),$3,@$,TOK_FILE,
                $1->src_code + " < " + $3->src_code);
        } else {
            $$ = new BinaryExpr($1,new Operator(OP::LT,@2,TOK_FILE),$3,@$,TOK_FILE);
        }
    }

    | rel-expr LTEQ additive-expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new BinaryExpr($1,new Operator(OP::LTEQ,@2,TOK_FILE,"<="),$3,@$,TOK_FILE,
                $1->src_code + " <= " + $3->src_code);
        } else {
            $$ = new BinaryExpr($1,new Operator(OP::LTEQ,@2,TOK_FILE),$3,@$,TOK_FILE);
        }
    }

    | rel-expr GT additive-expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new BinaryExpr($1,new Operator(OP::GT,@2,TOK_FILE,">"),$3,@$,TOK_FILE,
                $1->src_code + " > " + $3->src_code);
        } else {
            $$ = new BinaryExpr($1,new Operator(OP::GT,@2,TOK_FILE),$3,@$,TOK_FILE);
        }
    }

    | rel-expr GTEQ additive-expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new BinaryExpr($1,new Operator(OP::GTEQ,@2,TOK_FILE,">="),$3,@$,TOK_FILE,
                $1->src_code + " >= " + $3->src_code);
        } else {
            $$ = new BinaryExpr($1,new Operator(OP::GTEQ,@2,TOK_FILE),$3,@$,TOK_FILE);
        }
    }

additive-expr : mult-expr
    {
        $$ = $1;
    }

    | additive-expr PLUS mult-expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new BinaryExpr($1,new Operator(OP::PLUS,@2,TOK_FILE,"+"),$3,@$,TOK_FILE,
                $1->src_code + " + " + $3->src_code);
        } else {
            $$ = new BinaryExpr($1,new Operator(OP::PLUS,@2,TOK_FILE),$3,@$,TOK_FILE);
        }
    }

    | additive-expr MINUS mult-expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new BinaryExpr($1,new Operator(OP::MINUS,@2,TOK_FILE,"-"),$3,@$,TOK_FILE,
                $1->src_code + " - " + $3->src_code);
        } else {
            $$ = new BinaryExpr($1,new Operator(OP::MINUS,@2,TOK_FILE),$3,@$,TOK_FILE);
        }
    }

mult-expr : unary-expr
    {
        $$ = $1;
    }

    | mult-expr MULT unary-expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new BinaryExpr($1,new Operator(OP::MULT,@2,TOK_FILE,"*"),$3,@$,TOK_FILE,
                $1->src_code + " * " + $3->src_code);
        } else {
            $$ = new BinaryExpr($1,new Operator(OP::MULT,@2,TOK_FILE),$3,@$,TOK_FILE);
        }
    }

    | mult-expr DIV unary-expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new BinaryExpr($1,new Operator(OP::DIV,@2,TOK_FILE,"/"),$3,@$,TOK_FILE,
                $1->src_code + " / " + $3->src_code);
        } else {
            $$ = new BinaryExpr($1,new Operator(OP::DIV,@2,TOK_FILE),$3,@$,TOK_FILE);
        }
    }

unary-expr : primary-expr
    {
        $$ = $1;
    }

    | PLUS unary-expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new UnaryExpr(new Operator(OP::PLUS,@1,TOK_FILE,"+"),$2,@$,TOK_FILE,
                "+" + $2->src_code);
        } else {
            $$ = new UnaryExpr(new Operator(OP::PLUS,@1,TOK_FILE),$2,@$,TOK_FILE);
        }
    }

    | MINUS unary-expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new UnaryExpr(new Operator(OP::MINUS,@1,TOK_FILE,"-"),$2,@$,TOK_FILE,
                "-" + $2->src_code);
        } else {
            $$ = new UnaryExpr(new Operator(OP::MINUS,@1,TOK_FILE),$2,@$,TOK_FILE);
        }
    }

    | NOT unary-expr
    {
        if (CAPTURING_SOURCE) {
            $$ = new UnaryExpr(new Operator(OP::NOT,@1,TOK_FILE,"not"),$2,@$,TOK_FILE,
                "not " + $2->src_code);
        }
            $$ = new UnaryExpr(new Operator(OP::NOT,@1,TOK_FILE),$2,@$,TOK_FILE);
    }

primary-expr : fcall
    {
        $$ = $1;
    }

    | bbcall
    {
        $$ = $1;
    }

    | var-expr
    {
        $$ = $1;
    }

    | LPAREN expr RPAREN
    {
        $$ = $2;
        if (CAPTURING_SOURCE) {
            $$->src_code = "(" + $$->src_code + ")";
        }
    }

    | literal-expr
    {
        $$ = $1;
    }

fcall : identifier LPAREN arg-list-opt RPAREN
    {
        if (CAPTURING_SOURCE) {
            $$ = new FCall($1,$3,@$,TOK_FILE,
                $1->src_code + "(" + $3->src_code + ")");
        } else {
            $$ = new FCall($1,$3,@$,TOK_FILE);
        }
    }

bbcall : BLACKBOARD DOT identifier DOT identifier DOT identifier LPAREN arg-list-opt RPAREN
    {
        if (CAPTURING_SOURCE) {
            $$ = new BBCall($3,$5,$7,$9,@$,TOK_FILE,
                "blackboard." + $3->src_code + "." + $5->src_code + 
                "." + $7->src_code + "(" + $9->src_code + ")");
        } else {
            $$ = new BBCall($3,$5,$7,$9,@$,TOK_FILE);
        }
    }

var-expr : identifier
    {
        if (CAPTURING_SOURCE) {
            $$ = new VarExpr($1,@$,TOK_FILE,
                $1->src_code);
        } else {
            $$ = new VarExpr($1,@$,TOK_FILE);
        }
    }

literal-expr : INT
    {
        if (CAPTURING_SOURCE) {
            $$ = new LiteralExpr($1,@$,TOK_FILE,
                std::to_string($1));
        } else {
            $$ = new LiteralExpr($1,@$,TOK_FILE);
        }
    }

    | DOUBLE
    {
        if (CAPTURING_SOURCE) {
            $$ = new LiteralExpr($1,@$,TOK_FILE,
                std::to_string($1));
        } else {
            $$ = new LiteralExpr($1,@$,TOK_FILE);
        }
    }

    | BOOL
    {
        if (CAPTURING_SOURCE) {
            $$ = new LiteralExpr($1,@$,TOK_FILE,
                std::to_string($1));
        } else {
            $$ = new LiteralExpr($1,@$,TOK_FILE);
        }
    }

    | STRING
    {
        if (CAPTURING_SOURCE) {
            $$ = new LiteralExpr($1,@$,TOK_FILE,
                "\'" + $1 + "\'");
        } else {
            $$ = new LiteralExpr($1,@$,TOK_FILE);
        }
    }

    | vectorliteral
    {
        if (CAPTURING_SOURCE) {
            $$ = new LiteralExpr($1,@$,TOK_FILE,
                static_cast<std::string>($1));
        } else {
            $$ = new LiteralExpr($1,@$,TOK_FILE);
        }
    }

vectorliteral : LCURL vval COMMA vval RCURL
    {
        $$ = Vector($2,$4);
    }

vval : vlit
    {
        $$ = $1;
    }

    | PLUS vval
    {
        $$ = $2;
    }

    | MINUS vval
    {
        $$ = -$2;
    }

vlit : DOUBLE
    {
        $$ = $1;
    }

    | INT
    {
        $$ = static_cast<double>($1);
    }

%%

// Parser error caller, just passes onto interpreter error function
void TR::TRParser::error(const location& loc, const std::string& msg) {
        driver.error(loc,msg);
}

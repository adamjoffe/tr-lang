// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2013 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.
// //                    "%code top" blocks.
#line 25 "tr_parser.y" // lalr1.cc:392

    #include "tr_scanner.h"
    #include "tr_parser.h"
    #include "tr_interpreter.h"
    
    // Parser expects to call a function yylex, with configured params to get next token
    // So setup macro to allow that to happen
    #define yylex(scanner) scanner.get_next_token()

    // shorthand macro for getting token related file
    #define TOK_FILE scanner.currentFile()
    #define CAPTURING_SOURCE scanner.is_capturing()

#line 48 "tr_parser.cpp" // lalr1.cc:392


// First part of user declarations.

#line 53 "tr_parser.cpp" // lalr1.cc:399

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "tr_parser.h"

// User implementation prologue.

#line 67 "tr_parser.cpp" // lalr1.cc:407


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyempty = true)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 9 "tr_parser.y" // lalr1.cc:474
namespace  TR  {
#line 153 "tr_parser.cpp" // lalr1.cc:474

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   TRParser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
   TRParser :: TRParser  (TR::TRScanner& scanner_yyarg, TR::TRInterpreter& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

   TRParser ::~ TRParser  ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
   TRParser ::by_state::by_state ()
    : state (empty)
  {}

  inline
   TRParser ::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
   TRParser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.state = empty;
  }

  inline
   TRParser ::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
   TRParser ::symbol_number_type
   TRParser ::by_state::type_get () const
  {
    return state == empty ? 0 : yystos_[state];
  }

  inline
   TRParser ::stack_symbol_type::stack_symbol_type ()
  {}


  inline
   TRParser ::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 53: // blackboard-decl
      case 56: // var-decl
      case 58: // func-decl
      case 66: // tr-node
      case 73: // once-decl
      case 77: // para-decl
        value.move< TR::ASTDecl* > (that.value);
        break;

      case 57: // initialiser
      case 80: // arg
      case 84: // expr
      case 85: // or-expr
      case 86: // and-expr
      case 87: // equality-expr
      case 88: // rel-expr
      case 89: // additive-expr
      case 90: // mult-expr
      case 91: // unary-expr
      case 92: // primary-expr
      case 93: // fcall
      case 94: // bbcall
      case 95: // var-expr
      case 96: // literal-expr
        value.move< TR::ASTExpr* > (that.value);
        break;

      case 52: // tr-prog-list
      case 71: // action-list
      case 75: // para-list-opt
      case 76: // para-list
      case 78: // arg-list-opt
      case 79: // arg-list
        value.move< TR::ASTList* > (that.value);
        break;

      case 59: // stmt
      case 60: // logic-stmt
      case 61: // if-stmt
      case 62: // otherwise-stmt
      case 63: // elif-stmt
      case 64: // else-stmt
      case 65: // return-stmt
      case 67: // cond-stmt
      case 68: // cond
      case 69: // action-stmt
      case 70: // regr-stmt
      case 72: // action
      case 81: // expr-stmt
      case 82: // assign-stmt
      case 83: // exit-stmt
        value.move< TR::ASTStmt* > (that.value);
        break;

      case 74: // identifier
        value.move< TR::ASTTerminal* > (that.value);
        break;

      case 97: // vectorliteral
        value.move< TR::Vector > (that.value);
        break;

      case 6: // "bool"
        value.move< bool > (that.value);
        break;

      case 5: // "double"
      case 98: // vval
      case 99: // vlit
        value.move< double > (that.value);
        break;

      case 4: // "int"
        value.move< int > (that.value);
        break;

      case 7: // "string"
      case 8: // "ID"
      case 54: // struct-type
      case 55: // tr-type
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty;
  }

  inline
   TRParser ::stack_symbol_type&
   TRParser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 53: // blackboard-decl
      case 56: // var-decl
      case 58: // func-decl
      case 66: // tr-node
      case 73: // once-decl
      case 77: // para-decl
        value.copy< TR::ASTDecl* > (that.value);
        break;

      case 57: // initialiser
      case 80: // arg
      case 84: // expr
      case 85: // or-expr
      case 86: // and-expr
      case 87: // equality-expr
      case 88: // rel-expr
      case 89: // additive-expr
      case 90: // mult-expr
      case 91: // unary-expr
      case 92: // primary-expr
      case 93: // fcall
      case 94: // bbcall
      case 95: // var-expr
      case 96: // literal-expr
        value.copy< TR::ASTExpr* > (that.value);
        break;

      case 52: // tr-prog-list
      case 71: // action-list
      case 75: // para-list-opt
      case 76: // para-list
      case 78: // arg-list-opt
      case 79: // arg-list
        value.copy< TR::ASTList* > (that.value);
        break;

      case 59: // stmt
      case 60: // logic-stmt
      case 61: // if-stmt
      case 62: // otherwise-stmt
      case 63: // elif-stmt
      case 64: // else-stmt
      case 65: // return-stmt
      case 67: // cond-stmt
      case 68: // cond
      case 69: // action-stmt
      case 70: // regr-stmt
      case 72: // action
      case 81: // expr-stmt
      case 82: // assign-stmt
      case 83: // exit-stmt
        value.copy< TR::ASTStmt* > (that.value);
        break;

      case 74: // identifier
        value.copy< TR::ASTTerminal* > (that.value);
        break;

      case 97: // vectorliteral
        value.copy< TR::Vector > (that.value);
        break;

      case 6: // "bool"
        value.copy< bool > (that.value);
        break;

      case 5: // "double"
      case 98: // vval
      case 99: // vlit
        value.copy< double > (that.value);
        break;

      case 4: // "int"
        value.copy< int > (that.value);
        break;

      case 7: // "string"
      case 8: // "ID"
      case 54: // struct-type
      case 55: // tr-type
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
   TRParser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   TRParser ::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
   TRParser ::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
   TRParser ::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
   TRParser ::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   TRParser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   TRParser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   TRParser ::debug_level_type
   TRParser ::debug_level () const
  {
    return yydebug_;
  }

  void
   TRParser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline  TRParser ::state_type
   TRParser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
   TRParser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
   TRParser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   TRParser ::parse ()
  {
    /// Whether yyla contains a lookahead.
    bool yyempty = true;

    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyempty)
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (scanner));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
        yyempty = false;
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Discard the token being shifted.
    yyempty = true;

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 53: // blackboard-decl
      case 56: // var-decl
      case 58: // func-decl
      case 66: // tr-node
      case 73: // once-decl
      case 77: // para-decl
        yylhs.value.build< TR::ASTDecl* > ();
        break;

      case 57: // initialiser
      case 80: // arg
      case 84: // expr
      case 85: // or-expr
      case 86: // and-expr
      case 87: // equality-expr
      case 88: // rel-expr
      case 89: // additive-expr
      case 90: // mult-expr
      case 91: // unary-expr
      case 92: // primary-expr
      case 93: // fcall
      case 94: // bbcall
      case 95: // var-expr
      case 96: // literal-expr
        yylhs.value.build< TR::ASTExpr* > ();
        break;

      case 52: // tr-prog-list
      case 71: // action-list
      case 75: // para-list-opt
      case 76: // para-list
      case 78: // arg-list-opt
      case 79: // arg-list
        yylhs.value.build< TR::ASTList* > ();
        break;

      case 59: // stmt
      case 60: // logic-stmt
      case 61: // if-stmt
      case 62: // otherwise-stmt
      case 63: // elif-stmt
      case 64: // else-stmt
      case 65: // return-stmt
      case 67: // cond-stmt
      case 68: // cond
      case 69: // action-stmt
      case 70: // regr-stmt
      case 72: // action
      case 81: // expr-stmt
      case 82: // assign-stmt
      case 83: // exit-stmt
        yylhs.value.build< TR::ASTStmt* > ();
        break;

      case 74: // identifier
        yylhs.value.build< TR::ASTTerminal* > ();
        break;

      case 97: // vectorliteral
        yylhs.value.build< TR::Vector > ();
        break;

      case 6: // "bool"
        yylhs.value.build< bool > ();
        break;

      case 5: // "double"
      case 98: // vval
      case 99: // vlit
        yylhs.value.build< double > ();
        break;

      case 4: // "int"
        yylhs.value.build< int > ();
        break;

      case 7: // "string"
      case 8: // "ID"
      case 54: // struct-type
      case 55: // tr-type
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 160 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            driver.ast = new TRProgram(yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE, 
                yystack_[0].value.as< TR::ASTList* > ()->src_code);
        } else {
            driver.ast = new TRProgram(yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE);
        }
    }
#line 778 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 3:
#line 170 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTList* > () = new EmptyTRProgList(yylhs.location,TOK_FILE,
                "");
        } else {
            yylhs.value.as< TR::ASTList* > () = new EmptyTRProgList(yylhs.location,TOK_FILE);
        }
    }
#line 791 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 4:
#line 180 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTList* > () = new TRProgList(yystack_[1].value.as< TR::ASTDecl* > (), yystack_[0].value.as< TR::ASTList* > (), yylhs.location, TOK_FILE,
                yystack_[1].value.as< TR::ASTDecl* > ()->src_code + "\n" + yystack_[0].value.as< TR::ASTList* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTList* > () = new TRProgList(yystack_[1].value.as< TR::ASTDecl* > (),yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE);
        }
    }
#line 804 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 5:
#line 190 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTList* > () = new TRProgList(yystack_[1].value.as< TR::ASTDecl* > (),yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE, 
                yystack_[1].value.as< TR::ASTDecl* > ()->src_code + "\n" + yystack_[0].value.as< TR::ASTList* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTList* > () = new TRProgList(yystack_[1].value.as< TR::ASTDecl* > (),yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE);
        }
    }
#line 817 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 6:
#line 200 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTList* > () = new TRProgList(yystack_[1].value.as< TR::ASTDecl* > (),yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE, 
                yystack_[1].value.as< TR::ASTDecl* > ()->src_code + "\n" + yystack_[0].value.as< TR::ASTList* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTList* > () = new TRProgList(yystack_[1].value.as< TR::ASTDecl* > (),yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE);
        }
    }
#line 830 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 7:
#line 210 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTList* > () = new TRProgList(yystack_[1].value.as< TR::ASTDecl* > (),yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE, 
                yystack_[1].value.as< TR::ASTDecl* > ()->src_code + "\n" + yystack_[0].value.as< TR::ASTList* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTList* > () = new TRProgList(yystack_[1].value.as< TR::ASTDecl* > (),yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE);
        }
    }
#line 843 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 8:
#line 220 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTList* > () = new TRProgList(yystack_[1].value.as< TR::ASTDecl* > (),yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE,
                yystack_[1].value.as< TR::ASTDecl* > ()->src_code + "\n" + yystack_[0].value.as< TR::ASTList* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTList* > () = new TRProgList(yystack_[1].value.as< TR::ASTDecl* > (),yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE);
        }
    }
#line 856 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 9:
#line 231 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTDecl* > () = new BlackboardDecl(yystack_[2].value.as< TR::ASTTerminal* > (),yystack_[1].value.as< std::string > (),yystack_[0].value.as< std::string > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTTerminal* > ()->src_code + " " + yystack_[1].value.as< std::string > () + " " + yystack_[0].value.as< std::string > ());
        } else {
            yylhs.value.as< TR::ASTDecl* > () = new BlackboardDecl(yystack_[2].value.as< TR::ASTTerminal* > (),yystack_[1].value.as< std::string > (),yystack_[0].value.as< std::string > (),yylhs.location,TOK_FILE);
        }
    }
#line 869 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 10:
#line 241 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< std::string > () = "VAR";
    }
#line 877 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 11:
#line 246 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< std::string > () = "STACK";
    }
#line 885 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 12:
#line 251 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< std::string > () = "MAP";
    }
#line 893 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 13:
#line 256 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< std::string > () = "LIST";
    }
#line 901 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 14:
#line 261 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< std::string > () = "INT";
    }
#line 909 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 15:
#line 266 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< std::string > () = "DOUBLE";
    }
#line 917 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 16:
#line 271 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< std::string > () = "BOOL";
    }
#line 925 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 17:
#line 276 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< std::string > () = "STRING";
    }
#line 933 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 18:
#line 281 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< std::string > () = "VECTOR";
    }
#line 941 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 19:
#line 287 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTDecl* > () = new VarDecl(yystack_[2].value.as< TR::ASTTerminal* > (),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE, 
                yystack_[2].value.as< TR::ASTTerminal* > ()->src_code + " = " + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTDecl* > () = new VarDecl(yystack_[2].value.as< TR::ASTTerminal* > (),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 954 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 20:
#line 297 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new InitExpr(yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE, 
                yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new InitExpr(yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 967 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 21:
#line 308 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTDecl* > () = new FuncDecl(yystack_[5].value.as< TR::ASTTerminal* > (),yystack_[3].value.as< TR::ASTList* > (),yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE,
                // function will onyl show declaration not definition
                //$1->src_code + "(" + $3->src_code + ") = \n" + $6->src_code);
                yystack_[5].value.as< TR::ASTTerminal* > ()->src_code + "(" + yystack_[3].value.as< TR::ASTList* > ()->src_code + ") =");
        } else {
            yylhs.value.as< TR::ASTDecl* > () = new FuncDecl(yystack_[5].value.as< TR::ASTTerminal* > (),yystack_[3].value.as< TR::ASTList* > (),yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE);
        }
    }
#line 982 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 22:
#line 320 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTStmt* > () = yystack_[0].value.as< TR::ASTStmt* > ();
    }
#line 990 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 23:
#line 325 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTStmt* > () = yystack_[0].value.as< TR::ASTStmt* > ();
    }
#line 998 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 24:
#line 330 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTStmt* > () = new LogicStmt(yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE,
                yystack_[0].value.as< TR::ASTStmt* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTStmt* > () = new LogicStmt(yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1011 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 25:
#line 340 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTStmt* > () = new IfStmt(yystack_[4].value.as< TR::ASTExpr* > (),yystack_[1].value.as< TR::ASTStmt* > (),yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE,
                "if (" + yystack_[4].value.as< TR::ASTExpr* > ()->src_code + ") -> " + yystack_[1].value.as< TR::ASTStmt* > ()->src_code + "\n" + yystack_[0].value.as< TR::ASTStmt* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTStmt* > () = new IfStmt(yystack_[4].value.as< TR::ASTExpr* > (),yystack_[1].value.as< TR::ASTStmt* > (),yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1024 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 26:
#line 350 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTStmt* > () = new OtherwiseStmt(yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE,
                yystack_[0].value.as< TR::ASTStmt* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTStmt* > () = new OtherwiseStmt(yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1037 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 27:
#line 360 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTStmt* > () = new OtherwiseStmt(yystack_[1].value.as< TR::ASTStmt* > (),yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE,
                yystack_[1].value.as< TR::ASTStmt* > ()->src_code + "\n" + yystack_[0].value.as< TR::ASTStmt* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTStmt* > () = new OtherwiseStmt(yystack_[1].value.as< TR::ASTStmt* > (),yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1050 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 28:
#line 370 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTStmt* > () = new ElifStmt(yystack_[3].value.as< TR::ASTExpr* > (),yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE,
                "elif (" + yystack_[3].value.as< TR::ASTExpr* > ()->src_code + ") -> " + yystack_[0].value.as< TR::ASTStmt* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTStmt* > () = new ElifStmt(yystack_[3].value.as< TR::ASTExpr* > (),yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1063 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 29:
#line 380 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTStmt* > () = new ElseStmt(yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE,
                "else -> " + yystack_[0].value.as< TR::ASTStmt* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTStmt* > () = new ElseStmt(yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1076 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 30:
#line 390 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTStmt* > () = new ReturnStmt(yystack_[1].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[1].value.as< TR::ASTExpr* > ()->src_code + ";");
        } else {
            yylhs.value.as< TR::ASTStmt* > () = new ReturnStmt(yystack_[1].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1089 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 31:
#line 401 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTDecl* > () = new TRNode(yystack_[5].value.as< TR::ASTTerminal* > (),yystack_[3].value.as< TR::ASTList* > (),yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE,
                // node will only show the declaration, not definition
                //$1->src_code + "(" + $3->src_code + ") :- \n" + $6->src_code);
                yystack_[5].value.as< TR::ASTTerminal* > ()->src_code + "(" + yystack_[3].value.as< TR::ASTList* > ()->src_code + ") :-");
        } else {
            yylhs.value.as< TR::ASTDecl* > () = new TRNode(yystack_[5].value.as< TR::ASTTerminal* > (),yystack_[3].value.as< TR::ASTList* > (),yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1104 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 32:
#line 413 "tr_parser.y" // lalr1.cc:847
    {
        // BOOL needs to be true, error if it is not
        if (!yystack_[1].value.as< bool > ()){
            driver.error(yystack_[1].location,"syntax error, unexpected \'false\', expecting \'true\'");
            return 1; // same error code as failing on input
        } else {
            if (CAPTURING_SOURCE) {
                yylhs.value.as< TR::ASTStmt* > () = new CondStmt(yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE,
                    "true" + yystack_[0].value.as< TR::ASTStmt* > ()->src_code);
            } else {
                yylhs.value.as< TR::ASTStmt* > () = new CondStmt(yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE);
            }
        }
    }
#line 1123 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 33:
#line 429 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTStmt* > () = new CondStmt(yystack_[1].value.as< TR::ASTStmt* > (),yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE,
                yystack_[1].value.as< TR::ASTStmt* > ()->src_code + "\n" + yystack_[0].value.as< TR::ASTStmt* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTStmt* > () = new CondStmt(yystack_[1].value.as< TR::ASTStmt* > (),yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1136 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 34:
#line 439 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTStmt* > () = new Cond(yystack_[3].value.as< TR::ASTTerminal* > (),yystack_[1].value.as< TR::ASTExpr* > (),yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE,
                yystack_[3].value.as< TR::ASTTerminal* > ()->src_code + " : " + yystack_[1].value.as< TR::ASTExpr* > ()->src_code + yystack_[0].value.as< TR::ASTStmt* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTStmt* > () = new Cond(yystack_[3].value.as< TR::ASTTerminal* > (),yystack_[1].value.as< TR::ASTExpr* > (),yystack_[0].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1149 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 35:
#line 449 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTStmt* > () = new ActionStmt(yystack_[2].value.as< TR::ASTList* > (),yystack_[1].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE,
                " -> " + yystack_[2].value.as< TR::ASTList* > ()->src_code + "" + yystack_[1].value.as< TR::ASTStmt* > ()->src_code + ";");
        } else {
            yylhs.value.as< TR::ASTStmt* > () = new ActionStmt(yystack_[2].value.as< TR::ASTList* > (),yystack_[1].value.as< TR::ASTStmt* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1162 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 36:
#line 459 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTStmt* > () = new RegressionStmt(yystack_[0].value.as< TR::ASTTerminal* > (),yylhs.location,TOK_FILE,
                " achieves " + yystack_[0].value.as< TR::ASTTerminal* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTStmt* > () = new RegressionStmt(yystack_[0].value.as< TR::ASTTerminal* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1175 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 37:
#line 469 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTList* > () = new ActionList(yystack_[0].value.as< TR::ASTStmt* > (),new EmptyActionList(yylhs.location,TOK_FILE,""),yylhs.location,TOK_FILE,
                yystack_[0].value.as< TR::ASTStmt* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTList* > () = new ActionList(yystack_[0].value.as< TR::ASTStmt* > (),new EmptyActionList(yylhs.location,TOK_FILE),yylhs.location,TOK_FILE);
        }
    }
#line 1188 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 38:
#line 479 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTList* > () = new ActionList(yystack_[2].value.as< TR::ASTStmt* > (),yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTStmt* > ()->src_code + ", " + yystack_[0].value.as< TR::ASTList* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTList* > () = new ActionList(yystack_[2].value.as< TR::ASTStmt* > (),yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1201 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 39:
#line 489 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTStmt* > () = yystack_[0].value.as< TR::ASTStmt* > ();
    }
#line 1209 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 40:
#line 494 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTStmt* > () = yystack_[0].value.as< TR::ASTStmt* > ();
    }
#line 1217 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 41:
#line 499 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTStmt* > () = yystack_[0].value.as< TR::ASTStmt* > ();
    }
#line 1225 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 42:
#line 505 "tr_parser.y" // lalr1.cc:847
    {   
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTDecl* > () = new OnceDecl(yystack_[1].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE,
                "once {" + yystack_[1].value.as< TR::ASTList* > ()->src_code + "}");
        } else {
            yylhs.value.as< TR::ASTDecl* > () = new OnceDecl(yystack_[1].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1238 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 43:
#line 516 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTTerminal* > () = new Ident(yystack_[0].value.as< std::string > (),yylhs.location,TOK_FILE,
                yystack_[0].value.as< std::string > ());
        } else {
            yylhs.value.as< TR::ASTTerminal* > () = new Ident(yystack_[0].value.as< std::string > (),yylhs.location,TOK_FILE);
        }
    }
#line 1251 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 44:
#line 526 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTList* > () = new EmptyParaList(yylhs.location,TOK_FILE,
                "");
        } else {
            yylhs.value.as< TR::ASTList* > () = new EmptyParaList(yylhs.location,TOK_FILE);
        }
    }
#line 1264 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 45:
#line 536 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTList* > () = yystack_[0].value.as< TR::ASTList* > ();
    }
#line 1272 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 46:
#line 541 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTList* > () = new ParaList(yystack_[0].value.as< TR::ASTDecl* > (),new EmptyParaList(yystack_[0].location,TOK_FILE,""),yylhs.location,TOK_FILE,
                yystack_[0].value.as< TR::ASTDecl* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTList* > () = new ParaList(yystack_[0].value.as< TR::ASTDecl* > (),new EmptyParaList(yystack_[0].location,TOK_FILE),yylhs.location,TOK_FILE);
        }
    }
#line 1285 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 47:
#line 551 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTList* > () = new ParaList(yystack_[2].value.as< TR::ASTDecl* > (),yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTDecl* > ()->src_code + ", " + yystack_[0].value.as< TR::ASTList* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTList* > () = new ParaList(yystack_[2].value.as< TR::ASTDecl* > (),yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1298 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 48:
#line 561 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTDecl* > () = new ParaDecl(yystack_[0].value.as< TR::ASTTerminal* > (),yylhs.location,TOK_FILE,
                yystack_[0].value.as< TR::ASTTerminal* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTDecl* > () = new ParaDecl(yystack_[0].value.as< TR::ASTTerminal* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1311 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 49:
#line 571 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTList* > () = new EmptyArgList(yylhs.location,TOK_FILE,
                "");
        } else {
            yylhs.value.as< TR::ASTList* > () = new EmptyArgList(yylhs.location,TOK_FILE);
        }
    }
#line 1324 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 50:
#line 581 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTList* > () = yystack_[0].value.as< TR::ASTList* > ();
    }
#line 1332 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 51:
#line 586 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTList* > () = new ArgList(yystack_[0].value.as< TR::ASTExpr* > (),new EmptyArgList(yylhs.location,TOK_FILE,""),yylhs.location,TOK_FILE,
                yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTList* > () = new ArgList(yystack_[0].value.as< TR::ASTExpr* > (),new EmptyArgList(yylhs.location,TOK_FILE),yylhs.location,TOK_FILE);
        }
    }
#line 1345 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 52:
#line 596 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTList* > () = new ArgList(yystack_[2].value.as< TR::ASTExpr* > (),yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTExpr* > ()->src_code + ", " + yystack_[0].value.as< TR::ASTList* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTList* > () = new ArgList(yystack_[2].value.as< TR::ASTExpr* > (),yystack_[0].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1358 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 53:
#line 606 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new Arg(yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new Arg(yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1371 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 54:
#line 616 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTStmt* > () = new ExprStmt(yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTStmt* > () = new ExprStmt(yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1384 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 55:
#line 626 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTStmt* > () = new AssignStmt(yystack_[2].value.as< TR::ASTTerminal* > (),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTTerminal* > ()->src_code + " = " + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTStmt* > () = new AssignStmt(yystack_[2].value.as< TR::ASTTerminal* > (),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1397 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 56:
#line 636 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTStmt* > () = new ExitStmt(yystack_[1].value.as< bool > (),yylhs.location,TOK_FILE,
                "exit(" + std::to_string(yystack_[1].value.as< bool > ()) + ")");
        } else {
            yylhs.value.as< TR::ASTStmt* > () = new ExitStmt(yystack_[1].value.as< bool > (),yylhs.location,TOK_FILE);
        }
    }
#line 1410 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 57:
#line 646 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTStmt* > () = new ExitStmt(yystack_[3].value.as< bool > (),yystack_[1].value.as< std::string > (),yylhs.location,TOK_FILE,
                "exit(" + std::to_string(yystack_[3].value.as< bool > ()) + ", \'" + yystack_[1].value.as< std::string > () + "\')");
        } else {
            yylhs.value.as< TR::ASTStmt* > () = new ExitStmt(yystack_[3].value.as< bool > (),yystack_[1].value.as< std::string > (),yylhs.location,TOK_FILE);
        }
    }
#line 1423 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 58:
#line 656 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTExpr* > () = yystack_[0].value.as< TR::ASTExpr* > ();
    }
#line 1431 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 59:
#line 661 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTExpr* > () = yystack_[0].value.as< TR::ASTExpr* > ();
    }
#line 1439 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 60:
#line 666 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::OR,yystack_[1].location,TOK_FILE,"or"),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTExpr* > ()->src_code + " or " + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::OR,yystack_[1].location,TOK_FILE),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1452 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 61:
#line 676 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTExpr* > () = yystack_[0].value.as< TR::ASTExpr* > ();
    }
#line 1460 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 62:
#line 681 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::AND,yystack_[1].location,TOK_FILE,"and"),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTExpr* > ()->src_code + " and " + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::AND,yystack_[1].location,TOK_FILE),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1473 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 63:
#line 691 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTExpr* > () = yystack_[0].value.as< TR::ASTExpr* > ();
    }
#line 1481 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 64:
#line 696 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::EQEQ,yystack_[1].location,TOK_FILE,"=="),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTExpr* > ()->src_code + " == " + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::EQEQ,yystack_[1].location,TOK_FILE),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1494 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 65:
#line 706 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::NOTEQ,yystack_[1].location,TOK_FILE,"!="),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTExpr* > ()->src_code + " != " + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::NOTEQ,yystack_[1].location,TOK_FILE),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1507 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 66:
#line 716 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTExpr* > () = yystack_[0].value.as< TR::ASTExpr* > ();
    }
#line 1515 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 67:
#line 721 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::LT,yystack_[1].location,TOK_FILE,"<"),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTExpr* > ()->src_code + " < " + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::LT,yystack_[1].location,TOK_FILE),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1528 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 68:
#line 731 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::LTEQ,yystack_[1].location,TOK_FILE,"<="),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTExpr* > ()->src_code + " <= " + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::LTEQ,yystack_[1].location,TOK_FILE),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1541 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 69:
#line 741 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::GT,yystack_[1].location,TOK_FILE,">"),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTExpr* > ()->src_code + " > " + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::GT,yystack_[1].location,TOK_FILE),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1554 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 70:
#line 751 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::GTEQ,yystack_[1].location,TOK_FILE,">="),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTExpr* > ()->src_code + " >= " + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::GTEQ,yystack_[1].location,TOK_FILE),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1567 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 71:
#line 761 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTExpr* > () = yystack_[0].value.as< TR::ASTExpr* > ();
    }
#line 1575 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 72:
#line 766 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::PLUS,yystack_[1].location,TOK_FILE,"+"),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTExpr* > ()->src_code + " + " + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::PLUS,yystack_[1].location,TOK_FILE),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1588 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 73:
#line 776 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::MINUS,yystack_[1].location,TOK_FILE,"-"),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTExpr* > ()->src_code + " - " + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::MINUS,yystack_[1].location,TOK_FILE),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1601 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 74:
#line 786 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTExpr* > () = yystack_[0].value.as< TR::ASTExpr* > ();
    }
#line 1609 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 75:
#line 791 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::MULT,yystack_[1].location,TOK_FILE,"*"),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTExpr* > ()->src_code + " * " + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::MULT,yystack_[1].location,TOK_FILE),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1622 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 76:
#line 801 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::DIV,yystack_[1].location,TOK_FILE,"/"),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                yystack_[2].value.as< TR::ASTExpr* > ()->src_code + " / " + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new BinaryExpr(yystack_[2].value.as< TR::ASTExpr* > (),new Operator(OP::DIV,yystack_[1].location,TOK_FILE),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1635 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 77:
#line 811 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTExpr* > () = yystack_[0].value.as< TR::ASTExpr* > ();
    }
#line 1643 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 78:
#line 816 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new UnaryExpr(new Operator(OP::PLUS,yystack_[1].location,TOK_FILE,"+"),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                "+" + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new UnaryExpr(new Operator(OP::PLUS,yystack_[1].location,TOK_FILE),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1656 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 79:
#line 826 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new UnaryExpr(new Operator(OP::MINUS,yystack_[1].location,TOK_FILE,"-"),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                "-" + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new UnaryExpr(new Operator(OP::MINUS,yystack_[1].location,TOK_FILE),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1669 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 80:
#line 836 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new UnaryExpr(new Operator(OP::NOT,yystack_[1].location,TOK_FILE,"not"),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE,
                "not " + yystack_[0].value.as< TR::ASTExpr* > ()->src_code);
        }
            yylhs.value.as< TR::ASTExpr* > () = new UnaryExpr(new Operator(OP::NOT,yystack_[1].location,TOK_FILE),yystack_[0].value.as< TR::ASTExpr* > (),yylhs.location,TOK_FILE);
    }
#line 1681 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 81:
#line 845 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTExpr* > () = yystack_[0].value.as< TR::ASTExpr* > ();
    }
#line 1689 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 82:
#line 850 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTExpr* > () = yystack_[0].value.as< TR::ASTExpr* > ();
    }
#line 1697 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 83:
#line 855 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTExpr* > () = yystack_[0].value.as< TR::ASTExpr* > ();
    }
#line 1705 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 84:
#line 860 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTExpr* > () = yystack_[1].value.as< TR::ASTExpr* > ();
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > ()->src_code = "(" + yylhs.value.as< TR::ASTExpr* > ()->src_code + ")";
        }
    }
#line 1716 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 85:
#line 868 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::ASTExpr* > () = yystack_[0].value.as< TR::ASTExpr* > ();
    }
#line 1724 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 86:
#line 873 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new FCall(yystack_[3].value.as< TR::ASTTerminal* > (),yystack_[1].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE,
                yystack_[3].value.as< TR::ASTTerminal* > ()->src_code + "(" + yystack_[1].value.as< TR::ASTList* > ()->src_code + ")");
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new FCall(yystack_[3].value.as< TR::ASTTerminal* > (),yystack_[1].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1737 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 87:
#line 883 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new BBCall(yystack_[7].value.as< TR::ASTTerminal* > (),yystack_[5].value.as< TR::ASTTerminal* > (),yystack_[3].value.as< TR::ASTTerminal* > (),yystack_[1].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE,
                "blackboard." + yystack_[7].value.as< TR::ASTTerminal* > ()->src_code + "." + yystack_[5].value.as< TR::ASTTerminal* > ()->src_code + 
                "." + yystack_[3].value.as< TR::ASTTerminal* > ()->src_code + "(" + yystack_[1].value.as< TR::ASTList* > ()->src_code + ")");
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new BBCall(yystack_[7].value.as< TR::ASTTerminal* > (),yystack_[5].value.as< TR::ASTTerminal* > (),yystack_[3].value.as< TR::ASTTerminal* > (),yystack_[1].value.as< TR::ASTList* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1751 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 88:
#line 894 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new VarExpr(yystack_[0].value.as< TR::ASTTerminal* > (),yylhs.location,TOK_FILE,
                yystack_[0].value.as< TR::ASTTerminal* > ()->src_code);
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new VarExpr(yystack_[0].value.as< TR::ASTTerminal* > (),yylhs.location,TOK_FILE);
        }
    }
#line 1764 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 89:
#line 904 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new LiteralExpr(yystack_[0].value.as< int > (),yylhs.location,TOK_FILE,
                std::to_string(yystack_[0].value.as< int > ()));
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new LiteralExpr(yystack_[0].value.as< int > (),yylhs.location,TOK_FILE);
        }
    }
#line 1777 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 90:
#line 914 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new LiteralExpr(yystack_[0].value.as< double > (),yylhs.location,TOK_FILE,
                std::to_string(yystack_[0].value.as< double > ()));
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new LiteralExpr(yystack_[0].value.as< double > (),yylhs.location,TOK_FILE);
        }
    }
#line 1790 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 91:
#line 924 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new LiteralExpr(yystack_[0].value.as< bool > (),yylhs.location,TOK_FILE,
                std::to_string(yystack_[0].value.as< bool > ()));
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new LiteralExpr(yystack_[0].value.as< bool > (),yylhs.location,TOK_FILE);
        }
    }
#line 1803 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 92:
#line 934 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new LiteralExpr(yystack_[0].value.as< std::string > (),yylhs.location,TOK_FILE,
                "\'" + yystack_[0].value.as< std::string > () + "\'");
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new LiteralExpr(yystack_[0].value.as< std::string > (),yylhs.location,TOK_FILE);
        }
    }
#line 1816 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 93:
#line 944 "tr_parser.y" // lalr1.cc:847
    {
        if (CAPTURING_SOURCE) {
            yylhs.value.as< TR::ASTExpr* > () = new LiteralExpr(yystack_[0].value.as< TR::Vector > (),yylhs.location,TOK_FILE,
                static_cast<std::string>(yystack_[0].value.as< TR::Vector > ()));
        } else {
            yylhs.value.as< TR::ASTExpr* > () = new LiteralExpr(yystack_[0].value.as< TR::Vector > (),yylhs.location,TOK_FILE);
        }
    }
#line 1829 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 94:
#line 954 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< TR::Vector > () = Vector(yystack_[3].value.as< double > (),yystack_[1].value.as< double > ());
    }
#line 1837 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 95:
#line 959 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< double > () = yystack_[0].value.as< double > ();
    }
#line 1845 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 96:
#line 964 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< double > () = yystack_[0].value.as< double > ();
    }
#line 1853 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 97:
#line 969 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< double > () = -yystack_[0].value.as< double > ();
    }
#line 1861 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 98:
#line 974 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< double > () = yystack_[0].value.as< double > ();
    }
#line 1869 "tr_parser.cpp" // lalr1.cc:847
    break;

  case 99:
#line 979 "tr_parser.y" // lalr1.cc:847
    {
        yylhs.value.as< double > () = static_cast<double>(yystack_[0].value.as< int > ());
    }
#line 1877 "tr_parser.cpp" // lalr1.cc:847
    break;


#line 1881 "tr_parser.cpp" // lalr1.cc:847
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state,
                                           yyempty ? yyempty_ : yyla.type_get ()));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyempty)
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyempty = true;
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyempty)
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyempty)
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
   TRParser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
   TRParser ::yysyntax_error_ (state_type yystate, symbol_number_type yytoken) const
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char  TRParser ::yypact_ninf_ = -109;

  const signed char  TRParser ::yytable_ninf_ = -1;

  const short int
   TRParser ::yypact_[] =
  {
      89,  -109,  -109,    -6,   -13,    46,  -109,    89,    89,    89,
      89,    89,   -30,    94,    15,  -109,  -109,  -109,  -109,  -109,
    -109,    76,    -6,  -109,  -109,  -109,  -109,    74,  -109,  -109,
    -109,  -109,    76,     9,     8,    76,    76,    35,    76,    19,
      21,     4,  -109,  -109,  -109,  -109,    60,    69,   -22,    92,
       0,    54,  -109,  -109,  -109,  -109,  -109,  -109,  -109,  -109,
      44,  -109,  -109,    45,  -109,    62,  -109,  -109,  -109,  -109,
    -109,  -109,  -109,   115,    -6,  -109,  -109,  -109,  -109,    35,
      35,    82,  -109,    80,  -109,    15,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      11,    -6,     7,    86,  -109,  -109,    35,  -109,  -109,  -109,
      83,  -109,    95,  -109,    69,   -22,    92,    92,     0,     0,
       0,     0,    54,    54,  -109,  -109,    30,    43,  -109,   126,
    -109,    -6,    91,  -109,    76,    97,  -109,  -109,  -109,  -109,
      99,   105,  -109,    43,   106,   101,   103,  -109,  -109,    76,
    -109,    15,  -109,  -109,    76,  -109,    -6,   104,   137,   105,
     107,   114,    -6,   117,  -109,    76,    30,  -109,  -109,   109,
      77,  -109,   112,   119,  -109,    77,  -109,    76,    30,  -109,
     113,  -109,   122,    30,  -109
  };

  const unsigned char
   TRParser ::yydefact_[] =
  {
       0,     3,    43,     0,     0,     0,     2,     0,     0,     0,
       0,     0,     0,     0,     0,     1,     4,     5,     6,     7,
       8,     0,    44,    10,    11,    12,    13,     0,    89,    90,
      91,    92,     0,     0,     0,     0,     0,     0,     0,     0,
      37,    88,    39,    40,    41,    54,    58,    59,    61,    63,
      66,    71,    74,    77,    81,    82,    83,    85,    93,    19,
      88,    20,    48,     0,    45,    46,    14,    15,    16,    17,
      18,     9,    80,     0,     0,    78,    79,    99,    98,     0,
       0,     0,    95,     0,    42,     0,     0,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    96,    97,     0,    84,    38,    55,
       0,    50,    51,    53,    60,    62,    64,    65,    67,    68,
      69,    70,    72,    73,    75,    76,     0,     0,    47,     0,
      56,     0,     0,    86,     0,     0,    21,    22,    24,    23,
       0,     0,    31,     0,     0,     0,     0,    94,    52,     0,
      30,     0,    32,    33,     0,    57,     0,     0,     0,     0,
       0,     0,     0,     0,    34,    49,     0,    36,    35,     0,
       0,    87,     0,     0,    25,     0,    26,     0,     0,    27,
       0,    29,     0,     0,    28
  };

  const signed char
   TRParser ::yypgoto_[] =
  {
    -109,  -109,   102,  -109,  -109,  -109,  -109,  -109,  -109,  -108,
    -109,  -109,    -9,  -109,  -109,  -109,  -109,    24,  -109,    10,
    -109,   -77,  -109,  -109,     3,  -109,    67,  -109,     6,    36,
    -109,  -109,  -109,  -109,   -14,  -109,    84,    85,     5,    49,
      22,   -31,  -109,  -109,  -109,  -109,  -109,  -109,   -52,  -109
  };

  const short int
   TRParser ::yydefgoto_[] =
  {
      -1,     5,     6,     7,    27,    71,     8,    59,     9,   136,
     137,   138,   174,   175,   176,   139,    10,   142,   143,   152,
     163,    39,    40,    11,    60,    63,    64,    65,   110,   111,
     112,    42,    43,    44,   140,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    81,    82
  };

  const unsigned char
   TRParser ::yytable_[] =
  {
      45,    72,     2,    12,    75,    76,    13,    61,   108,    21,
      12,    12,    12,    12,    12,    90,    91,    41,    22,    28,
      29,    30,    31,     2,    83,    62,    32,   104,   105,    96,
      97,    33,    34,    14,    28,    29,    30,    31,     2,    77,
      78,    32,   135,    86,    35,    36,    15,    34,   129,   141,
     126,     2,    87,    74,   132,   127,   130,    73,   170,    35,
      36,    37,    85,    38,    79,    80,    84,   124,   125,    88,
     181,    45,   109,   113,   158,   184,    37,   103,    38,    89,
      28,    29,    30,    31,     2,    98,    99,    32,    41,     1,
     172,   173,    87,    34,   100,   116,   117,     2,    66,    67,
      68,    69,    70,   101,    62,    35,    36,     3,     4,    16,
      17,    18,    19,    20,    23,    24,    25,    26,   122,   123,
     113,   102,    37,   106,    38,    92,    93,    94,    95,   107,
     144,   131,   133,   145,   146,   157,   134,    45,   147,   150,
     159,   118,   119,   120,   121,   149,   144,   151,   156,   154,
     155,   113,   162,   161,    41,   165,   166,   168,   171,   160,
     177,   178,   182,   180,   183,   167,   179,   153,   128,   164,
     148,   169,   114,     0,   115
  };

  const short int
   TRParser ::yycheck_[] =
  {
      14,    32,     8,     0,    35,    36,     3,    21,    85,    39,
       7,     8,     9,    10,    11,    37,    38,    14,    48,     4,
       5,     6,     7,     8,    38,    22,    11,    79,    80,    29,
      30,    16,    17,    46,     4,     5,     6,     7,     8,     4,
       5,    11,    12,    39,    29,    30,     0,    17,    41,     6,
      39,     8,    48,    45,   106,    44,    49,    48,   166,    29,
      30,    46,    41,    48,    29,    30,    47,    98,    99,     9,
     178,    85,    86,    87,   151,   183,    46,    74,    48,    10,
       4,     5,     6,     7,     8,    31,    32,    11,    85,     0,
      13,    14,    48,    17,    49,    90,    91,     8,    24,    25,
      26,    27,    28,    41,   101,    29,    30,    18,    19,     7,
       8,     9,    10,    11,    20,    21,    22,    23,    96,    97,
     134,     6,    46,    41,    48,    33,    34,    35,    36,    49,
     127,    45,    49,     7,   131,   149,    41,   151,    47,    40,
     154,    92,    93,    94,    95,    48,   143,    42,    45,    43,
      49,   165,    15,    49,   151,    48,    42,    40,    49,   156,
      48,    42,    49,   177,    42,   162,   175,   143,   101,   159,
     134,   165,    88,    -1,    89
  };

  const unsigned char
   TRParser ::yystos_[] =
  {
       0,     0,     8,    18,    19,    51,    52,    53,    56,    58,
      66,    73,    74,    74,    46,     0,    52,    52,    52,    52,
      52,    39,    48,    20,    21,    22,    23,    54,     4,     5,
       6,     7,    11,    16,    17,    29,    30,    46,    48,    71,
      72,    74,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    57,
      74,    84,    74,    75,    76,    77,    24,    25,    26,    27,
      28,    55,    91,    48,    45,    91,    91,     4,     5,    29,
      30,    98,    99,    84,    47,    41,    39,    48,     9,    10,
      37,    38,    33,    34,    35,    36,    29,    30,    31,    32,
      49,    41,     6,    74,    98,    98,    41,    49,    71,    84,
      78,    79,    80,    84,    86,    87,    88,    88,    89,    89,
      89,    89,    90,    90,    91,    91,    39,    44,    76,    41,
      49,    45,    98,    49,    41,    12,    59,    60,    61,    65,
      84,     6,    67,    68,    74,     7,    74,    47,    79,    48,
      40,    42,    69,    67,    43,    49,    45,    84,    71,    84,
      74,    49,    15,    70,    69,    48,    42,    74,    40,    78,
      59,    49,    13,    14,    62,    63,    64,    48,    42,    62,
      84,    59,    49,    42,    59
  };

  const unsigned char
   TRParser ::yyr1_[] =
  {
       0,    50,    51,    52,    52,    52,    52,    52,    52,    53,
      54,    54,    54,    54,    55,    55,    55,    55,    55,    56,
      57,    58,    59,    59,    60,    61,    62,    62,    63,    64,
      65,    66,    67,    67,    68,    69,    70,    71,    71,    72,
      72,    72,    73,    74,    75,    75,    76,    76,    77,    78,
      78,    79,    79,    80,    81,    82,    83,    83,    84,    85,
      85,    86,    86,    87,    87,    87,    88,    88,    88,    88,
      88,    89,    89,    89,    90,    90,    90,    91,    91,    91,
      91,    92,    92,    92,    92,    92,    93,    94,    95,    96,
      96,    96,    96,    96,    97,    98,    98,    98,    99,    99
  };

  const unsigned char
   TRParser ::yyr2_[] =
  {
       0,     2,     1,     1,     2,     2,     2,     2,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     6,     1,     1,     1,     7,     1,     2,     6,     3,
       2,     6,     2,     2,     4,     4,     2,     1,     3,     1,
       1,     1,     4,     1,     0,     1,     1,     3,     1,     0,
       1,     1,     3,     1,     1,     3,     4,     6,     1,     1,
       3,     1,     3,     1,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     2,     2,
       2,     1,     1,     1,     3,     1,     4,    10,     1,     1,
       1,     1,     1,     1,     5,     1,     2,     2,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const  TRParser ::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"ERROR\"", "\"int\"",
  "\"double\"", "\"bool\"", "\"string\"", "\"ID\"", "\"or\"", "\"and\"",
  "\"not\"", "\"if\"", "\"elif\"", "\"else\"", "\"achieves\"", "\"exit\"",
  "\"blackboard\"", "\"init\"", "\"once\"", "\"VAR\"", "\"STACK\"",
  "\"MAP\"", "\"LIST\"", "\"INT\"", "\"DOUBLE\"", "\"BOOL\"", "\"STRING\"",
  "\"VECTOR\"", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"<\"", "\"<=\"",
  "\">\"", "\">=\"", "\"==\"", "\"!=\"", "\"=\"", "\";\"", "\",\"",
  "\"->\"", "\":\"", "\":-\"", "\".\"", "\"{\"", "\"}\"", "\"(\"", "\")\"",
  "$accept", "tr-program", "tr-prog-list", "blackboard-decl",
  "struct-type", "tr-type", "var-decl", "initialiser", "func-decl", "stmt",
  "logic-stmt", "if-stmt", "otherwise-stmt", "elif-stmt", "else-stmt",
  "return-stmt", "tr-node", "cond-stmt", "cond", "action-stmt",
  "regr-stmt", "action-list", "action", "once-decl", "identifier",
  "para-list-opt", "para-list", "para-decl", "arg-list-opt", "arg-list",
  "arg", "expr-stmt", "assign-stmt", "exit-stmt", "expr", "or-expr",
  "and-expr", "equality-expr", "rel-expr", "additive-expr", "mult-expr",
  "unary-expr", "primary-expr", "fcall", "bbcall", "var-expr",
  "literal-expr", "vectorliteral", "vval", "vlit", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
   TRParser ::yyrline_[] =
  {
       0,   159,   159,   169,   179,   189,   199,   209,   219,   230,
     240,   245,   250,   255,   260,   265,   270,   275,   280,   286,
     296,   307,   319,   324,   329,   339,   349,   359,   369,   379,
     389,   400,   412,   428,   438,   448,   458,   468,   478,   488,
     493,   498,   504,   515,   526,   535,   540,   550,   560,   571,
     580,   585,   595,   605,   615,   625,   635,   645,   655,   660,
     665,   675,   680,   690,   695,   705,   715,   720,   730,   740,
     750,   760,   765,   775,   785,   790,   800,   810,   815,   825,
     835,   844,   849,   854,   859,   867,   872,   882,   893,   903,
     913,   923,   933,   943,   953,   958,   963,   968,   973,   978
  };

  // Print the state stack on the debug stream.
  void
   TRParser ::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
   TRParser ::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 9 "tr_parser.y" // lalr1.cc:1155
} //  TR 
#line 2383 "tr_parser.cpp" // lalr1.cc:1155
#line 983 "tr_parser.y" // lalr1.cc:1156


// Parser error caller, just passes onto interpreter error function
void TR::TRParser::error(const location& loc, const std::string& msg) {
        driver.error(loc,msg);
}

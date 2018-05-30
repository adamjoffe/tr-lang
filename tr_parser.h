// A Bison parser, made by GNU Bison 3.0.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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

/**
 ** \file tr_parser.h
 ** Define the  TR ::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_TR_PARSER_H_INCLUDED
# define YY_YY_TR_PARSER_H_INCLUDED
// //                    "%code requires" blocks.
#line 11 "tr_parser.y" // lalr1.cc:372

    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdint.h>
    #include "AST/abstract_visitor.h"

    namespace TR {
        class TRScanner;
        class TRInterpreter;
    }

#line 57 "tr_parser.h" // lalr1.cc:372

# include <cassert>
# include <vector>
# include <iostream>
# include <stdexcept>
# include <string>
# include "stack.hh"
# include "location.hh"
#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 9 "tr_parser.y" // lalr1.cc:372
namespace  TR  {
#line 133 "tr_parser.h" // lalr1.cc:372



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yytname_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytname_ (typeid (T).name ())
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytname_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytname_);
      YYASSERT (sizeof (T) <= S);
      yytname_ = typeid (T).name ();
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytname_);
      YYASSERT (sizeof (T) <= S);
      yytname_ = typeid (T).name ();
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (yytname_ == typeid (T).name ());
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (yytname_ == typeid (T).name ());
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytname_);
      YYASSERT (yytname_ == other.yytname_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytname_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const char *yytname_;
  };


  /// A Bison parser.
  class  TRParser 
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // blackboard-decl
      // var-decl
      // func-decl
      // tr-node
      // once-decl
      // para-decl
      char dummy1[sizeof(TR::ASTDecl*)];

      // initialiser
      // arg
      // expr
      // or-expr
      // and-expr
      // equality-expr
      // rel-expr
      // additive-expr
      // mult-expr
      // unary-expr
      // primary-expr
      // fcall
      // bbcall
      // var-expr
      // literal-expr
      char dummy2[sizeof(TR::ASTExpr*)];

      // tr-prog-list
      // action-list
      // para-list-opt
      // para-list
      // arg-list-opt
      // arg-list
      char dummy3[sizeof(TR::ASTList*)];

      // stmt
      // logic-stmt
      // if-stmt
      // otherwise-stmt
      // elif-stmt
      // else-stmt
      // return-stmt
      // cond-stmt
      // cond
      // action-stmt
      // regr-stmt
      // action
      // expr-stmt
      // assign-stmt
      // exit-stmt
      char dummy4[sizeof(TR::ASTStmt*)];

      // identifier
      char dummy5[sizeof(TR::ASTTerminal*)];

      // vectorliteral
      char dummy6[sizeof(TR::Vector)];

      // "bool"
      char dummy7[sizeof(bool)];

      // "double"
      // vval
      // vlit
      char dummy8[sizeof(double)];

      // "int"
      char dummy9[sizeof(int)];

      // "string"
      // "ID"
      // struct-type
      // tr-type
      char dummy10[sizeof(std::string)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        TOKEN_END = 0,
        TOKEN_ERROR = 258,
        TOKEN_INT = 259,
        TOKEN_DOUBLE = 260,
        TOKEN_BOOL = 261,
        TOKEN_STRING = 262,
        TOKEN_ID = 263,
        TOKEN_OR = 264,
        TOKEN_AND = 265,
        TOKEN_NOT = 266,
        TOKEN_IF = 267,
        TOKEN_ELIF = 268,
        TOKEN_ELSE = 269,
        TOKEN_ACHIEVES = 270,
        TOKEN_EXIT = 271,
        TOKEN_BLACKBOARD = 272,
        TOKEN_INIT = 273,
        TOKEN_ONCE = 274,
        TOKEN_VAR = 275,
        TOKEN_STACK = 276,
        TOKEN_MAP = 277,
        TOKEN_LIST = 278,
        TOKEN_INT_T = 279,
        TOKEN_DOUBLE_T = 280,
        TOKEN_BOOL_T = 281,
        TOKEN_STRING_T = 282,
        TOKEN_VECTOR_T = 283,
        TOKEN_PLUS = 284,
        TOKEN_MINUS = 285,
        TOKEN_MULT = 286,
        TOKEN_DIV = 287,
        TOKEN_LT = 288,
        TOKEN_LTEQ = 289,
        TOKEN_GT = 290,
        TOKEN_GTEQ = 291,
        TOKEN_EQEQ = 292,
        TOKEN_NOTEQ = 293,
        TOKEN_EQ = 294,
        TOKEN_SEMICOL = 295,
        TOKEN_COMMA = 296,
        TOKEN_ARROW = 297,
        TOKEN_COL = 298,
        TOKEN_BLOCK = 299,
        TOKEN_DOT = 300,
        TOKEN_LCURL = 301,
        TOKEN_RCURL = 302,
        TOKEN_LPAREN = 303,
        TOKEN_RPAREN = 304
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Internal symbol number.
    typedef int symbol_number_type;

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const TR::ASTDecl* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const TR::ASTExpr* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const TR::ASTList* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const TR::ASTStmt* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const TR::ASTTerminal* v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const TR::Vector v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const bool v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const double v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const int v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      ~basic_symbol ();

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// -1 when this symbol is empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      enum { empty = 0 };

      /// The symbol type.
      /// -1 when this symbol is empty.
      token_number_type type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_ERROR (const location_type& l);

    static inline
    symbol_type
    make_INT (const int& v, const location_type& l);

    static inline
    symbol_type
    make_DOUBLE (const double& v, const location_type& l);

    static inline
    symbol_type
    make_BOOL (const bool& v, const location_type& l);

    static inline
    symbol_type
    make_STRING (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_ID (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_OR (const location_type& l);

    static inline
    symbol_type
    make_AND (const location_type& l);

    static inline
    symbol_type
    make_NOT (const location_type& l);

    static inline
    symbol_type
    make_IF (const location_type& l);

    static inline
    symbol_type
    make_ELIF (const location_type& l);

    static inline
    symbol_type
    make_ELSE (const location_type& l);

    static inline
    symbol_type
    make_ACHIEVES (const location_type& l);

    static inline
    symbol_type
    make_EXIT (const location_type& l);

    static inline
    symbol_type
    make_BLACKBOARD (const location_type& l);

    static inline
    symbol_type
    make_INIT (const location_type& l);

    static inline
    symbol_type
    make_ONCE (const location_type& l);

    static inline
    symbol_type
    make_VAR (const location_type& l);

    static inline
    symbol_type
    make_STACK (const location_type& l);

    static inline
    symbol_type
    make_MAP (const location_type& l);

    static inline
    symbol_type
    make_LIST (const location_type& l);

    static inline
    symbol_type
    make_INT_T (const location_type& l);

    static inline
    symbol_type
    make_DOUBLE_T (const location_type& l);

    static inline
    symbol_type
    make_BOOL_T (const location_type& l);

    static inline
    symbol_type
    make_STRING_T (const location_type& l);

    static inline
    symbol_type
    make_VECTOR_T (const location_type& l);

    static inline
    symbol_type
    make_PLUS (const location_type& l);

    static inline
    symbol_type
    make_MINUS (const location_type& l);

    static inline
    symbol_type
    make_MULT (const location_type& l);

    static inline
    symbol_type
    make_DIV (const location_type& l);

    static inline
    symbol_type
    make_LT (const location_type& l);

    static inline
    symbol_type
    make_LTEQ (const location_type& l);

    static inline
    symbol_type
    make_GT (const location_type& l);

    static inline
    symbol_type
    make_GTEQ (const location_type& l);

    static inline
    symbol_type
    make_EQEQ (const location_type& l);

    static inline
    symbol_type
    make_NOTEQ (const location_type& l);

    static inline
    symbol_type
    make_EQ (const location_type& l);

    static inline
    symbol_type
    make_SEMICOL (const location_type& l);

    static inline
    symbol_type
    make_COMMA (const location_type& l);

    static inline
    symbol_type
    make_ARROW (const location_type& l);

    static inline
    symbol_type
    make_COL (const location_type& l);

    static inline
    symbol_type
    make_BLOCK (const location_type& l);

    static inline
    symbol_type
    make_DOT (const location_type& l);

    static inline
    symbol_type
    make_LCURL (const location_type& l);

    static inline
    symbol_type
    make_RCURL (const location_type& l);

    static inline
    symbol_type
    make_LPAREN (const location_type& l);

    static inline
    symbol_type
    make_RPAREN (const location_type& l);


    /// Build a parser object.
     TRParser  (TR::TRScanner& scanner_yyarg, TR::TRInterpreter& driver_yyarg);
    virtual ~ TRParser  ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
     TRParser  (const  TRParser &);
     TRParser & operator= (const  TRParser &);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yytoken   the lookahead token type, or yyempty_.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         symbol_number_type yytoken) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const signed char yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned char yytable_[];

  static const short int yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// "empty" when empty.
      symbol_number_type type_get () const;

      enum { empty = 0 };

      /// The state.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    // Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 174,     ///< Last index in yytable_.
      yynnts_ = 50,  ///< Number of nonterminal symbols.
      yyempty_ = -2,
      yyfinal_ = 15, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 50  ///< Number of tokens.
    };


    // User arguments.
    TR::TRScanner& scanner;
    TR::TRInterpreter& driver;
  };

  // Symbol number corresponding to token number t.
  inline
   TRParser ::token_number_type
   TRParser ::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
    };
    const unsigned int user_token_number_max_ = 304;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
   TRParser ::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
   TRParser ::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
   TRParser ::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 53: // blackboard-decl
      case 56: // var-decl
      case 58: // func-decl
      case 66: // tr-node
      case 73: // once-decl
      case 77: // para-decl
        value.copy< TR::ASTDecl* > (other.value);
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
        value.copy< TR::ASTExpr* > (other.value);
        break;

      case 52: // tr-prog-list
      case 71: // action-list
      case 75: // para-list-opt
      case 76: // para-list
      case 78: // arg-list-opt
      case 79: // arg-list
        value.copy< TR::ASTList* > (other.value);
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
        value.copy< TR::ASTStmt* > (other.value);
        break;

      case 74: // identifier
        value.copy< TR::ASTTerminal* > (other.value);
        break;

      case 97: // vectorliteral
        value.copy< TR::Vector > (other.value);
        break;

      case 6: // "bool"
        value.copy< bool > (other.value);
        break;

      case 5: // "double"
      case 98: // vval
      case 99: // vlit
        value.copy< double > (other.value);
        break;

      case 4: // "int"
        value.copy< int > (other.value);
        break;

      case 7: // "string"
      case 8: // "ID"
      case 54: // struct-type
      case 55: // tr-type
        value.copy< std::string > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
   TRParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 53: // blackboard-decl
      case 56: // var-decl
      case 58: // func-decl
      case 66: // tr-node
      case 73: // once-decl
      case 77: // para-decl
        value.copy< TR::ASTDecl* > (v);
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
        value.copy< TR::ASTExpr* > (v);
        break;

      case 52: // tr-prog-list
      case 71: // action-list
      case 75: // para-list-opt
      case 76: // para-list
      case 78: // arg-list-opt
      case 79: // arg-list
        value.copy< TR::ASTList* > (v);
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
        value.copy< TR::ASTStmt* > (v);
        break;

      case 74: // identifier
        value.copy< TR::ASTTerminal* > (v);
        break;

      case 97: // vectorliteral
        value.copy< TR::Vector > (v);
        break;

      case 6: // "bool"
        value.copy< bool > (v);
        break;

      case 5: // "double"
      case 98: // vval
      case 99: // vlit
        value.copy< double > (v);
        break;

      case 4: // "int"
        value.copy< int > (v);
        break;

      case 7: // "string"
      case 8: // "ID"
      case 54: // struct-type
      case 55: // tr-type
        value.copy< std::string > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
   TRParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
   TRParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const TR::ASTDecl* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   TRParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const TR::ASTExpr* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   TRParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const TR::ASTList* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   TRParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const TR::ASTStmt* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   TRParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const TR::ASTTerminal* v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   TRParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const TR::Vector v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   TRParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const bool v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   TRParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const double v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   TRParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
   TRParser ::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
   TRParser ::basic_symbol<Base>::~basic_symbol ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 53: // blackboard-decl
      case 56: // var-decl
      case 58: // func-decl
      case 66: // tr-node
      case 73: // once-decl
      case 77: // para-decl
        value.template destroy< TR::ASTDecl* > ();
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
        value.template destroy< TR::ASTExpr* > ();
        break;

      case 52: // tr-prog-list
      case 71: // action-list
      case 75: // para-list-opt
      case 76: // para-list
      case 78: // arg-list-opt
      case 79: // arg-list
        value.template destroy< TR::ASTList* > ();
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
        value.template destroy< TR::ASTStmt* > ();
        break;

      case 74: // identifier
        value.template destroy< TR::ASTTerminal* > ();
        break;

      case 97: // vectorliteral
        value.template destroy< TR::Vector > ();
        break;

      case 6: // "bool"
        value.template destroy< bool > ();
        break;

      case 5: // "double"
      case 98: // vval
      case 99: // vlit
        value.template destroy< double > ();
        break;

      case 4: // "int"
        value.template destroy< int > ();
        break;

      case 7: // "string"
      case 8: // "ID"
      case 54: // struct-type
      case 55: // tr-type
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

  }

  template <typename Base>
  inline
  void
   TRParser ::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 53: // blackboard-decl
      case 56: // var-decl
      case 58: // func-decl
      case 66: // tr-node
      case 73: // once-decl
      case 77: // para-decl
        value.move< TR::ASTDecl* > (s.value);
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
        value.move< TR::ASTExpr* > (s.value);
        break;

      case 52: // tr-prog-list
      case 71: // action-list
      case 75: // para-list-opt
      case 76: // para-list
      case 78: // arg-list-opt
      case 79: // arg-list
        value.move< TR::ASTList* > (s.value);
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
        value.move< TR::ASTStmt* > (s.value);
        break;

      case 74: // identifier
        value.move< TR::ASTTerminal* > (s.value);
        break;

      case 97: // vectorliteral
        value.move< TR::Vector > (s.value);
        break;

      case 6: // "bool"
        value.move< bool > (s.value);
        break;

      case 5: // "double"
      case 98: // vval
      case 99: // vlit
        value.move< double > (s.value);
        break;

      case 4: // "int"
        value.move< int > (s.value);
        break;

      case 7: // "string"
      case 8: // "ID"
      case 54: // struct-type
      case 55: // tr-type
        value.move< std::string > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
   TRParser ::by_type::by_type ()
     : type (empty)
  {}

  inline
   TRParser ::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
   TRParser ::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
   TRParser ::by_type::move (by_type& that)
  {
    type = that.type;
    that.type = empty;
  }

  inline
  int
   TRParser ::by_type::type_get () const
  {
    return type;
  }

  inline
   TRParser ::token_type
   TRParser ::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
   TRParser ::symbol_type
   TRParser ::make_END (const location_type& l)
  {
    return symbol_type (token::TOKEN_END, l);
  }

   TRParser ::symbol_type
   TRParser ::make_ERROR (const location_type& l)
  {
    return symbol_type (token::TOKEN_ERROR, l);
  }

   TRParser ::symbol_type
   TRParser ::make_INT (const int& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_INT, v, l);
  }

   TRParser ::symbol_type
   TRParser ::make_DOUBLE (const double& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_DOUBLE, v, l);
  }

   TRParser ::symbol_type
   TRParser ::make_BOOL (const bool& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_BOOL, v, l);
  }

   TRParser ::symbol_type
   TRParser ::make_STRING (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_STRING, v, l);
  }

   TRParser ::symbol_type
   TRParser ::make_ID (const std::string& v, const location_type& l)
  {
    return symbol_type (token::TOKEN_ID, v, l);
  }

   TRParser ::symbol_type
   TRParser ::make_OR (const location_type& l)
  {
    return symbol_type (token::TOKEN_OR, l);
  }

   TRParser ::symbol_type
   TRParser ::make_AND (const location_type& l)
  {
    return symbol_type (token::TOKEN_AND, l);
  }

   TRParser ::symbol_type
   TRParser ::make_NOT (const location_type& l)
  {
    return symbol_type (token::TOKEN_NOT, l);
  }

   TRParser ::symbol_type
   TRParser ::make_IF (const location_type& l)
  {
    return symbol_type (token::TOKEN_IF, l);
  }

   TRParser ::symbol_type
   TRParser ::make_ELIF (const location_type& l)
  {
    return symbol_type (token::TOKEN_ELIF, l);
  }

   TRParser ::symbol_type
   TRParser ::make_ELSE (const location_type& l)
  {
    return symbol_type (token::TOKEN_ELSE, l);
  }

   TRParser ::symbol_type
   TRParser ::make_ACHIEVES (const location_type& l)
  {
    return symbol_type (token::TOKEN_ACHIEVES, l);
  }

   TRParser ::symbol_type
   TRParser ::make_EXIT (const location_type& l)
  {
    return symbol_type (token::TOKEN_EXIT, l);
  }

   TRParser ::symbol_type
   TRParser ::make_BLACKBOARD (const location_type& l)
  {
    return symbol_type (token::TOKEN_BLACKBOARD, l);
  }

   TRParser ::symbol_type
   TRParser ::make_INIT (const location_type& l)
  {
    return symbol_type (token::TOKEN_INIT, l);
  }

   TRParser ::symbol_type
   TRParser ::make_ONCE (const location_type& l)
  {
    return symbol_type (token::TOKEN_ONCE, l);
  }

   TRParser ::symbol_type
   TRParser ::make_VAR (const location_type& l)
  {
    return symbol_type (token::TOKEN_VAR, l);
  }

   TRParser ::symbol_type
   TRParser ::make_STACK (const location_type& l)
  {
    return symbol_type (token::TOKEN_STACK, l);
  }

   TRParser ::symbol_type
   TRParser ::make_MAP (const location_type& l)
  {
    return symbol_type (token::TOKEN_MAP, l);
  }

   TRParser ::symbol_type
   TRParser ::make_LIST (const location_type& l)
  {
    return symbol_type (token::TOKEN_LIST, l);
  }

   TRParser ::symbol_type
   TRParser ::make_INT_T (const location_type& l)
  {
    return symbol_type (token::TOKEN_INT_T, l);
  }

   TRParser ::symbol_type
   TRParser ::make_DOUBLE_T (const location_type& l)
  {
    return symbol_type (token::TOKEN_DOUBLE_T, l);
  }

   TRParser ::symbol_type
   TRParser ::make_BOOL_T (const location_type& l)
  {
    return symbol_type (token::TOKEN_BOOL_T, l);
  }

   TRParser ::symbol_type
   TRParser ::make_STRING_T (const location_type& l)
  {
    return symbol_type (token::TOKEN_STRING_T, l);
  }

   TRParser ::symbol_type
   TRParser ::make_VECTOR_T (const location_type& l)
  {
    return symbol_type (token::TOKEN_VECTOR_T, l);
  }

   TRParser ::symbol_type
   TRParser ::make_PLUS (const location_type& l)
  {
    return symbol_type (token::TOKEN_PLUS, l);
  }

   TRParser ::symbol_type
   TRParser ::make_MINUS (const location_type& l)
  {
    return symbol_type (token::TOKEN_MINUS, l);
  }

   TRParser ::symbol_type
   TRParser ::make_MULT (const location_type& l)
  {
    return symbol_type (token::TOKEN_MULT, l);
  }

   TRParser ::symbol_type
   TRParser ::make_DIV (const location_type& l)
  {
    return symbol_type (token::TOKEN_DIV, l);
  }

   TRParser ::symbol_type
   TRParser ::make_LT (const location_type& l)
  {
    return symbol_type (token::TOKEN_LT, l);
  }

   TRParser ::symbol_type
   TRParser ::make_LTEQ (const location_type& l)
  {
    return symbol_type (token::TOKEN_LTEQ, l);
  }

   TRParser ::symbol_type
   TRParser ::make_GT (const location_type& l)
  {
    return symbol_type (token::TOKEN_GT, l);
  }

   TRParser ::symbol_type
   TRParser ::make_GTEQ (const location_type& l)
  {
    return symbol_type (token::TOKEN_GTEQ, l);
  }

   TRParser ::symbol_type
   TRParser ::make_EQEQ (const location_type& l)
  {
    return symbol_type (token::TOKEN_EQEQ, l);
  }

   TRParser ::symbol_type
   TRParser ::make_NOTEQ (const location_type& l)
  {
    return symbol_type (token::TOKEN_NOTEQ, l);
  }

   TRParser ::symbol_type
   TRParser ::make_EQ (const location_type& l)
  {
    return symbol_type (token::TOKEN_EQ, l);
  }

   TRParser ::symbol_type
   TRParser ::make_SEMICOL (const location_type& l)
  {
    return symbol_type (token::TOKEN_SEMICOL, l);
  }

   TRParser ::symbol_type
   TRParser ::make_COMMA (const location_type& l)
  {
    return symbol_type (token::TOKEN_COMMA, l);
  }

   TRParser ::symbol_type
   TRParser ::make_ARROW (const location_type& l)
  {
    return symbol_type (token::TOKEN_ARROW, l);
  }

   TRParser ::symbol_type
   TRParser ::make_COL (const location_type& l)
  {
    return symbol_type (token::TOKEN_COL, l);
  }

   TRParser ::symbol_type
   TRParser ::make_BLOCK (const location_type& l)
  {
    return symbol_type (token::TOKEN_BLOCK, l);
  }

   TRParser ::symbol_type
   TRParser ::make_DOT (const location_type& l)
  {
    return symbol_type (token::TOKEN_DOT, l);
  }

   TRParser ::symbol_type
   TRParser ::make_LCURL (const location_type& l)
  {
    return symbol_type (token::TOKEN_LCURL, l);
  }

   TRParser ::symbol_type
   TRParser ::make_RCURL (const location_type& l)
  {
    return symbol_type (token::TOKEN_RCURL, l);
  }

   TRParser ::symbol_type
   TRParser ::make_LPAREN (const location_type& l)
  {
    return symbol_type (token::TOKEN_LPAREN, l);
  }

   TRParser ::symbol_type
   TRParser ::make_RPAREN (const location_type& l)
  {
    return symbol_type (token::TOKEN_RPAREN, l);
  }


#line 9 "tr_parser.y" // lalr1.cc:372
} //  TR 
#line 1847 "tr_parser.h" // lalr1.cc:372




#endif // !YY_YY_TR_PARSER_H_INCLUDED

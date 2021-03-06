// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.

// "%code top" blocks.
#line 38 "parser.y"

    #include <iostream>
    #include <vector>
    #include "scanner.h"
    #include "parser.hpp"
    #include "interpreter.h"
    #include "location.hh"
    
    /* 注意：这里的参数由%parse-param决定, 在parser.y中被定义 */
    // yylex() arguments are defined in parser.y
    static tzzht::Parser::symbol_type yylex(tzzht::Scanner &scanner, tzzht::Interpreter &driver) {
        return scanner.get_next_token();
    }
    
    using namespace tzzht;

#line 55 "parser.cpp"




#include "parser.hpp"




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

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
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
    while (false)
# endif


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
      *yycdebug_ << '\n';                       \
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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 9 "parser.y"
namespace  tzzht  {
#line 154 "parser.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   Parser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
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
              else
                goto append;

            append:
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
   Parser :: Parser  (tzzht::Scanner &scanner_yyarg, tzzht::Interpreter &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

   Parser ::~ Parser  ()
  {}

   Parser ::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
   Parser ::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

   Parser ::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
   Parser ::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
   Parser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

   Parser ::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

   Parser ::symbol_number_type
   Parser ::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

   Parser ::stack_symbol_type::stack_symbol_type ()
  {}

   Parser ::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 23: // transition
        value.YY_MOVE_OR_COPY< int > (YY_MOVE (that.value));
        break;

      case 25: // edge
        value.YY_MOVE_OR_COPY< pair<tzzht::Proposition *, string> > (YY_MOVE (that.value));
        break;

      case 6: // STATE
      case 16: // WORD
      case 26: // state
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case 24: // edges
        value.YY_MOVE_OR_COPY< std::vector<pair<tzzht::Proposition *, string>> > (YY_MOVE (that.value));
        break;

      case 27: // proposition
        value.YY_MOVE_OR_COPY< tzzht::Proposition * > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

   Parser ::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 23: // transition
        value.move< int > (YY_MOVE (that.value));
        break;

      case 25: // edge
        value.move< pair<tzzht::Proposition *, string> > (YY_MOVE (that.value));
        break;

      case 6: // STATE
      case 16: // WORD
      case 26: // state
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case 24: // edges
        value.move< std::vector<pair<tzzht::Proposition *, string>> > (YY_MOVE (that.value));
        break;

      case 27: // proposition
        value.move< tzzht::Proposition * > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
   Parser ::stack_symbol_type&
   Parser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 23: // transition
        value.copy< int > (that.value);
        break;

      case 25: // edge
        value.copy< pair<tzzht::Proposition *, string> > (that.value);
        break;

      case 6: // STATE
      case 16: // WORD
      case 26: // state
        value.copy< std::string > (that.value);
        break;

      case 24: // edges
        value.copy< std::vector<pair<tzzht::Proposition *, string>> > (that.value);
        break;

      case 27: // proposition
        value.copy< tzzht::Proposition * > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

   Parser ::stack_symbol_type&
   Parser ::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 23: // transition
        value.move< int > (that.value);
        break;

      case 25: // edge
        value.move< pair<tzzht::Proposition *, string> > (that.value);
        break;

      case 6: // STATE
      case 16: // WORD
      case 26: // state
        value.move< std::string > (that.value);
        break;

      case 24: // edges
        value.move< std::vector<pair<tzzht::Proposition *, string>> > (that.value);
        break;

      case 27: // proposition
        value.move< tzzht::Proposition * > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
   Parser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   Parser ::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
   Parser ::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
   Parser ::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
   Parser ::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   Parser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   Parser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   Parser ::debug_level_type
   Parser ::debug_level () const
  {
    return yydebug_;
  }

  void
   Parser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

   Parser ::state_type
   Parser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
   Parser ::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
   Parser ::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
   Parser ::operator() ()
  {
    return parse ();
  }

  int
   Parser ::parse ()
  {
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

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (scanner, driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 23: // transition
        yylhs.value.emplace< int > ();
        break;

      case 25: // edge
        yylhs.value.emplace< pair<tzzht::Proposition *, string> > ();
        break;

      case 6: // STATE
      case 16: // WORD
      case 26: // state
        yylhs.value.emplace< std::string > ();
        break;

      case 24: // edges
        yylhs.value.emplace< std::vector<pair<tzzht::Proposition *, string>> > ();
        break;

      case 27: // proposition
        yylhs.value.emplace< tzzht::Proposition * > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 100 "parser.y"
                                                                {
                                                                    cout << "*** PARSER BEGIN ***" << endl;
                                                                }
#line 694 "parser.cpp"
    break;

  case 3:
#line 103 "parser.y"
                                                                    {
                                                                    cout << "*** PARSER EXIT ***" << endl;
                                                                }
#line 702 "parser.cpp"
    break;

  case 4:
#line 106 "parser.y"
                                                                {
                                                                    /* do nothing */
                                                                }
#line 710 "parser.cpp"
    break;

  case 5:
#line 109 "parser.y"
                                                                {
                                                                    /* do nothing */
                                                                }
#line 718 "parser.cpp"
    break;

  case 6:
#line 117 "parser.y"
                                                                    { 
                                                                    for(auto it = yystack_[2].value.as < std::vector<pair<tzzht::Proposition *, string>> > ().begin(); it != yystack_[2].value.as < std::vector<pair<tzzht::Proposition *, string>> > ().end(); it ++)
                                                                    {
                                                                        tzzht::Transition transition(yystack_[5].value.as < std::string > (), it->first, it->second);
                                                                        driver.m_nfa_.AddTransition(transition);
                                                                    }
                                                                }
#line 730 "parser.cpp"
    break;

  case 7:
#line 127 "parser.y"
                                                                                                { 
                                                                    yylhs.value.as < std::vector<pair<tzzht::Proposition *, string>> > ().push_back(yystack_[0].value.as < pair<tzzht::Proposition *, string> > ());
                                                                }
#line 738 "parser.cpp"
    break;

  case 8:
#line 130 "parser.y"
                                                                                        { 
                                                                    yystack_[0].value.as < std::vector<pair<tzzht::Proposition *, string>> > ().push_back(yystack_[1].value.as < pair<tzzht::Proposition *, string> > ());
                                                                    yylhs.value.as < std::vector<pair<tzzht::Proposition *, string>> > () = yystack_[0].value.as < std::vector<pair<tzzht::Proposition *, string>> > ();
                                                                }
#line 747 "parser.cpp"
    break;

  case 9:
#line 137 "parser.y"
                                                                            { 
                                                                    yylhs.value.as < pair<tzzht::Proposition *, string> > ().first = yystack_[2].value.as < tzzht::Proposition * > ();
                                                                    yylhs.value.as < pair<tzzht::Proposition *, string> > ().second = yystack_[0].value.as < std::string > ();
                                                                }
#line 756 "parser.cpp"
    break;

  case 10:
#line 144 "parser.y"
                                                                {
                                                                    yylhs.value.as < std::string > () = yystack_[0].value.as < std::string > ();
                                                                    driver.m_nfa_.AddState(yystack_[0].value.as < std::string > ());
                                                                }
#line 765 "parser.cpp"
    break;

  case 11:
#line 150 "parser.y"
                                                                            { 
                                                                    yylhs.value.as < tzzht::Proposition * > () = yystack_[1].value.as < tzzht::Proposition * > (); 
                                                                }
#line 773 "parser.cpp"
    break;

  case 12:
#line 153 "parser.y"
                                                                                    { 
                                                                    yylhs.value.as < tzzht::Proposition * > () = new tzzht::Proposition(tzzht::Proposition::OperationType::Not, yystack_[0].value.as < tzzht::Proposition * > ()); 
                                                                }
#line 781 "parser.cpp"
    break;

  case 13:
#line 156 "parser.y"
                                                                            { 
                                                                    yylhs.value.as < tzzht::Proposition * > () = new tzzht::Proposition(tzzht::Proposition::OperationType::And, yystack_[2].value.as < tzzht::Proposition * > (), yystack_[0].value.as < tzzht::Proposition * > ()); 
                                                                }
#line 789 "parser.cpp"
    break;

  case 14:
#line 159 "parser.y"
                                                                            { 
                                                                    yylhs.value.as < tzzht::Proposition * > () = new tzzht::Proposition(tzzht::Proposition::OperationType::Or, yystack_[2].value.as < tzzht::Proposition * > (), yystack_[0].value.as < tzzht::Proposition * > ()); 
                                                                }
#line 797 "parser.cpp"
    break;

  case 15:
#line 162 "parser.y"
                                                                                            { 
                                                                    yylhs.value.as < tzzht::Proposition * > () = new tzzht::Proposition(tzzht::Proposition::OperationType::Literal, yystack_[0].value.as < std::string > ());  
                                                                }
#line 805 "parser.cpp"
    break;

  case 16:
#line 165 "parser.y"
                                                                                            { 
                                                                    yylhs.value.as < tzzht::Proposition * > () = new tzzht::Proposition(tzzht::Proposition::OperationType::True);
                                                                }
#line 813 "parser.cpp"
    break;

  case 17:
#line 168 "parser.y"
                                                                                            { 
                                                                    yylhs.value.as < tzzht::Proposition * > () = new tzzht::Proposition(tzzht::Proposition::OperationType::False);
                                                                }
#line 821 "parser.cpp"
    break;


#line 825 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

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
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
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
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
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
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
   Parser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
   Parser ::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
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
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
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
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
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
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
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


  const signed char  Parser ::yypact_ninf_ = -10;

  const signed char  Parser ::yytable_ninf_ = -1;

  const signed char
   Parser ::yypact_[] =
  {
       4,   -10,    -6,     3,     4,     1,     4,   -10,   -10,     5,
      12,    17,   -10,    -1,    20,    17,    -1,    -1,   -10,   -10,
     -10,    -4,     8,   -10,    19,     0,    -1,    -1,    23,   -10,
     -10,    19,    19,   -10
  };

  const signed char
   Parser ::yydefact_[] =
  {
       2,    10,     0,     0,     2,     0,     2,     1,     4,     0,
       0,     0,     3,     0,     0,     7,     0,     0,    16,    17,
      15,     0,     0,     8,    12,     0,     0,     0,     0,     6,
      11,    14,    13,     9
  };

  const signed char
   Parser ::yypgoto_[] =
  {
     -10,    16,   -10,    15,   -10,     6,    -9
  };

  const signed char
   Parser ::yydefgoto_[] =
  {
      -1,     3,     4,    14,    15,     5,    21
  };

  const signed char
   Parser ::yytable_[] =
  {
      26,    27,    16,     7,    26,    27,     6,    24,    25,    17,
       1,    30,    11,    18,    19,    20,    28,    31,    32,     9,
       8,     2,    10,    26,    27,    12,    13,    29,    22,     1,
      23,     0,     0,     0,    33
  };

  const signed char
   Parser ::yycheck_[] =
  {
       4,     5,     3,     0,     4,     5,    12,    16,    17,    10,
       6,    11,     7,    14,    15,    16,    20,    26,    27,    18,
       4,    17,     6,     4,     5,    13,     9,    19,     8,     6,
      15,    -1,    -1,    -1,    28
  };

  const signed char
   Parser ::yystos_[] =
  {
       0,     6,    17,    22,    23,    26,    12,     0,    22,    18,
      22,     7,    13,     9,    24,    25,     3,    10,    14,    15,
      16,    27,     8,    24,    27,    27,     4,     5,    20,    19,
      11,    27,    27,    26
  };

  const signed char
   Parser ::yyr1_[] =
  {
       0,    21,    22,    22,    22,    22,    23,    24,    24,    25,
      26,    27,    27,    27,    27,    27,    27,    27
  };

  const signed char
   Parser ::yyr2_[] =
  {
       0,     2,     0,     4,     2,     1,     6,     1,     2,     4,
       1,     3,     2,     3,     3,     1,     1,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const  Parser ::yytname_[] =
  {
  "END", "error", "$undefined", "NOT", "OR", "AND", "STATE", "IF", "FI",
  "DOTS", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "TRUE", "FALSE", "WORD",
  "NEVER", "COLON", "SEMICOLON", "ARROR", "$accept", "nfa", "transition",
  "edges", "edge", "state", "proposition", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
   Parser ::yyrline_[] =
  {
       0,   100,   100,   103,   106,   109,   117,   127,   130,   137,
     144,   150,   153,   156,   159,   162,   165,   168
  };

  // Print the state stack on the debug stream.
  void
   Parser ::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
   Parser ::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 9 "parser.y"
} //  tzzht 
#line 1224 "parser.cpp"

#line 173 "parser.y"


/* Parser实现错误处理接口 */
void tzzht::Parser::error(const location &loc , const std::string &message) {
        
        // Location should be initialized inside scanner action, but is not in this example.
        // Let's grab location directly from driver class.
	// cout << "Error: " << message << endl << "Location: " << loc << endl;
	
        cout << "Error: " << message << endl << "Error location: " << driver.location() << endl;
}

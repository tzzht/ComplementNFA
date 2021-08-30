/* 这里的代码直接拷贝到生成的.cpp文件中 */
%{
	#include <iostream>
	#include <cstdlib>
	#include "scanner.h"
	#include "interpreter.h"
	#include "parser.hpp"
	#include "location.hh"

	using namespace std;

	/* flex默认的yyterminate()就是return 0, int型. 但是如果用Bison3的话, 就需要返回值是Parser::semantic_type类型, 所以这里要重新定义yyerminate() */
	#define yyterminate() tzzht::Parser::make_END(tzzht::location());

	// This will track current scanner location.
	// Action is called when length of the token is known.
	#define YY_USER_ACTION m_driver_.increaseLocation(yyleng);
	
%}

/* 使语法分析器不要添加默认规则 */
%option nodefault
/* 不使用yywrap()(在到达yyin(是文件句柄)的结束位置时, 会自动调用yywrap(). 目的是为了调整yyin的值并继续进行词法分析.) */
%option noyywrap

/* 生成c++ scanner类 */
%option c++
/* flex默认会生成的两个类, FlexLexer 和 yyFlexLexer, 后者是前者的子类(在flex自带的FlexLexer.h中定义的). 在我们写的Scanner.h中会定义一个yyFlexLexer的子类Scanner. 这条指令会让flex产生的cpp文件中定义Scanner::yylex()方法(通过#define YY_DECL int Scanner::yylex()实现)(yylex()是词法分析的主要函数)(也会定义yyFlexLexer方法(虚函数), 这个方法会报错). 但是yylex()的返回值默认是int, bison3 使用symbol_type, 需要返回值是Parser::symbol_type, 所以在scanner.h中我们#undef YY_DECL, 然后#define YY_DECL Parser::symbol_type Scanner::get_next_token(), 所以我们词法分析的主要函数就从yylex()变成了get_next_token().*/
%option yyclass="Scanner"

/* 将类yyFlexLexer更名为tzzht_FlexLexer */
%option prefix="tzzht_"

STATE           (T0|accept)_(S[0-9]+|init|all)
IF			    "if"
FI			    "fi"
DOTS			"::"
LPAREN			\(
RPAREN			\)
LBRACE			\{
RBRACE			\}
OR			    \|\|
AND			    &&
NOT			    "!"
TRUE			"true"
FALSE			"false"
WORD			[a-z][0-9]
NEVER			"never"
COLON			":"
SEMICOLON		";"
ARROR			"-> goto"
WS			    [ \r\n\t]*

%%

{STATE}         {   
                    //cout << "Scanner: state '" << yytext << "'." << endl; 
                    return tzzht::Parser::make_STATE(yytext, tzzht::location());
                }
{IF}			{   
                    //cout << "Scanner: 'if'" << endl;
                    return tzzht::Parser::make_IF(tzzht::location());
                }
{FI}			{   
                    //cout << "Scanner: 'fi'" << endl;
                    return tzzht::Parser::make_FI(tzzht::location());
                }
{DOTS}			{   
                    //cout << "Scanner: '::'" << endl;
                    return tzzht::Parser::make_DOTS(tzzht::location());
                }
{LPAREN}		{   
                    //cout << "Scanner: '('" << endl;
                    return tzzht::Parser::make_LPAREN(tzzht::location());
                }
{RPAREN}		{   
                    //cout << "Scanner: ')'" << endl;
                    return tzzht::Parser::make_RPAREN(tzzht::location());
                }
{LBRACE}		{   
                    //cout << "Scanner: '{'" << endl;
                    return tzzht::Parser::make_LBRACE(tzzht::location());
                }
{RBRACE}		{   
                    //cout << "Scanner: '}'" << endl;
                    return tzzht::Parser::make_RBRACE(tzzht::location());
                }
{OR}			{   
                    //cout << "Scanner: '||'" << endl;
                    return tzzht::Parser::make_OR(tzzht::location());
                }
{AND}			{   
                    //cout << "Scanner: '&&'" << endl;
                    return tzzht::Parser::make_AND(tzzht::location());
                }
{NOT}			{   
                    //cout << "Scanner: '!'" << endl;
                    return tzzht::Parser::make_NOT(tzzht::location());
                }
{TRUE}			{   
                    //cout << "Scanner: 'true'" << endl;
                    return tzzht::Parser::make_TRUE(tzzht::location());
                }
{FALSE}		    {   
                    //cout << "Scanner: 'false'" << endl;
                    return tzzht::Parser::make_FALSE(tzzht::location());
                }
{WORD}			{   
                    //cout << "Scanner: ' << yytext << '" << endl;
                    return tzzht::Parser::make_WORD(yytext, tzzht::location());
                }
{NEVER}		    {   
                    //cout << "Scanner: 'never'" << endl;
                    return tzzht::Parser::make_NEVER(tzzht::location());
                }
{COLON}		    {   
                    //cout << "Scanner: ':'" << endl;
                    return tzzht::Parser::make_COLON(tzzht::location());
                }
{SEMICOLON}		{   
                    //cout << "Scanner: ';'" << endl;
                    return tzzht::Parser::make_SEMICOLON(tzzht::location());
                }
{ARROR}		    {   
                    //cout << "Scanner: '-> goto'" << endl;
                    return tzzht::Parser::make_ARROR(tzzht::location());
                }
{WS}      		{ /* ignored */ }
    .           { 
                    cout << "Scanner: unknown character '" << yytext << "'" << endl; 
                }
            
<<EOF>>         {   
                    return yyterminate();   
                }


%%

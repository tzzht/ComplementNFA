/* 使用指令％skeleton "lalr1.cc"选择C++解析器的骨架 */
%skeleton "lalr1.cc"
/* 指定bison的版本 */
%require "3.0"
/* 生成各种头文件  location.hh position.hh  parser.hpp */
%defines

/* 声明命名空间与下面声明的类名结合使用 tzzht::Parser:: */
%define api.namespace { tzzht }
%define parser_class_name { Parser }

%define api.token.constructor
/* 使得类型与token定义可以使用各种复杂的结构与类型 */
%define api.value.type variant
/* 开启断言功能 */
%define parse.assert


/* 这里的代码直接拷贝到.hpp文件中, requires中的内容会放在YYLTYPE与YYSTPYPE定义前 */
%code requires
{
    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdint.h>
    #include "nfa.h"

    using namespace std;

    namespace tzzht {
        class Scanner;
        class Interpreter;
    }
}

/* 这里的代码直接拷贝到生成的.cpp文件中, 靠近头部的地方 */
%code top
{
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
}

/*定义parser传给scanner的参数*/
%lex-param { tzzht::Scanner &scanner }
%lex-param { tzzht::Interpreter &driver }

/*定义driver传给parser的参数*/
%parse-param { tzzht::Scanner &scanner }
%parse-param { tzzht::Interpreter &driver }

%locations
%define parse.trace
/*详细显示错误信息*/
%define parse.error verbose

/* 通过tzzht::Parser::make_XXX(loc)给token添加前缀 */
%define api.token.prefix {TOKEN_}

%token END 0 //end of file
%token NOT
%token OR
%token AND
%token <std::string> STATE
%token IF
%token FI
%token DOTS
%token LPAREN
%token RPAREN
%token LBRACE
%token RBRACE
%token TRUE
%token FALSE
%token <std::string> WORD
%token NEVER
%token COLON
%token SEMICOLON
%token ARROR

%type <int> transition
%type <std::vector<pair<tzzht::Proposition *, string>>> edges 
%type <pair<tzzht::Proposition *, string>> edge
%type <tzzht::Proposition *> proposition
%type <std::string> state

%start nfa

%%
nfa:                                                            {
                                                                    cout << "*** PARSER BEGIN ***" << endl;
                                                                }	
    |   NEVER LBRACE nfa RBRACE		                            {
                                                                    cout << "*** PARSER EXIT ***" << endl;
                                                                }
    |   transition nfa                                          {
                                                                    /* do nothing */
                                                                }
    |   transition                                              {
                                                                    /* do nothing */
                                                                }
    ;



transition:
	    state COLON IF edges FI SEMICOLON 	                    { 
                                                                    for(auto it = $4.begin(); it != $4.end(); it ++)
                                                                    {
                                                                        tzzht::Transition transition($1, it->first, it->second);
                                                                        driver.m_nfa_.AddTransition(transition);
                                                                    }
                                                                }
	;

edges:
	    edge							                        { 
                                                                    $$.push_back($1);
                                                                }  
	|   edge edges						                        { 
                                                                    $2.push_back($1);
                                                                    $$ = $2;
                                                                }
	;

edge:
	    DOTS proposition ARROR state 		                    { 
                                                                    $$.first = $2;
                                                                    $$.second = $4;
                                                                }
	;
	
state:
        STATE                                                   {
                                                                    $$ = $1;
                                                                    driver.m_nfa_.AddState($1);
                                                                }

proposition:
	    LPAREN proposition RPAREN			                    { 
                                                                    $$ = $2; 
                                                                }
	|   NOT proposition				                            { 
                                                                    $$ = new tzzht::Proposition(tzzht::Proposition::OperationType::Not, $2); 
                                                                }  
	|   proposition AND proposition			                    { 
                                                                    $$ = new tzzht::Proposition(tzzht::Proposition::OperationType::And, $1, $3); 
                                                                }
	|   proposition OR proposition			                    { 
                                                                    $$ = new tzzht::Proposition(tzzht::Proposition::OperationType::Or, $1, $3); 
                                                                }
	|   WORD						                            { 
                                                                    $$ = new tzzht::Proposition(tzzht::Proposition::OperationType::Literal, $1);  
                                                                }
	|   TRUE						                            { 
                                                                    $$ = new tzzht::Proposition(tzzht::Proposition::OperationType::True);
                                                                }
	|   FALSE						                            { 
                                                                    $$ = new tzzht::Proposition(tzzht::Proposition::OperationType::False);
                                                                }
	;
    
%%

/* Parser实现错误处理接口 */
void tzzht::Parser::error(const location &loc , const std::string &message) {
        
        // Location should be initialized inside scanner action, but is not in this example.
        // Let's grab location directly from driver class.
	// cout << "Error: " << message << endl << "Location: " << loc << endl;
	
        cout << "Error: " << message << endl << "Error location: " << driver.location() << endl;
}

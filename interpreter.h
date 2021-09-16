#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>

#include "scanner.h"

#include "parser.hpp"

#include "nfa.h"

namespace tzzht {

// forward declare
class Nfa;

Proposition* PropositionDisjunction(Proposition *proposition_left, Proposition *proposition_right);

class Interpreter
{
public:
    Interpreter();
    
    /* 调用parser, 成功返回0, 失败返回1 */
    int parse();
    
    void ComplementNfa();
    void ConvertNfaToStateFormula();
    void CalStateFormula();
    void ConvertStateFormulaToNfa();
    void PrintNfa(){
        m_nfa_.PrintNfa();
    }
    void PrintComplementNfa()
    {
        m_complement_nfa_.PrintNfa();
    }
    /**
     * This is needed so that Scanner and Parser can call some
     * methods that we want to keep hidden from the end user.
     */
    friend class Parser;
    friend class Scanner;
    
private:
    // Used internally by Scanner YY_USER_ACTION to update location indicator
    void increaseLocation(unsigned int loc);
    
    // Used to get last Scanner location. Used in error messages.
    unsigned int location() const;
    
private:
    Scanner m_scanner_;
    Parser m_parser_;
    Nfa m_nfa_;
    Nfa m_complement_nfa_;
    StateFormula m_state_formula_;
    unsigned int m_location_;          // Used by scanner
};

}

#endif // INTERPRETER_H

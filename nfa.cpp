#include "nfa.h"

#include <iostream>
#include <sstream>

using namespace tzzht;


Proposition::Proposition() :
    m_atomic_()
{
    m_left_ = NULL;
    m_right_ = NULL;
}
Proposition::Proposition(const OperationType operation)
{
    m_left_ = NULL;
    m_right_ = NULL;
    switch (operation)
    {
    case True:
    case False:
        m_operation_ = operation;
        break;
    default:
        std::cout << "Build Proposition error! Expect True/False. Input operation is: " << operation << std::endl;
        break;
    }
}

Proposition::Proposition(const OperationType operation, const std::string atomic)
{
    m_left_ = NULL;
    m_right_ = NULL;
    switch (operation)
    {
    case Literal:
        m_operation_ = operation;
        m_atomic_ = atomic;
        break;
    
    default:
        std::cout << "Build Proposition error! Expect Literal. Input operation is: " << operation << std::endl;
        break;
    }
}

Proposition::Proposition(const OperationType operation, Proposition *left)
{
    m_left_ = NULL;
    m_right_ = NULL;
    switch (operation)
    {
    case Not:
        m_operation_ = operation;
        m_left_ = left;
        break;
    
    default:
        std::cout << "Build Proposition error! Expect Not. Input operation is: " << operation << std::endl;
        break;
    }
}

Proposition::Proposition(const OperationType operation, Proposition *left, Proposition *right)
{
    m_left_ = NULL;
    m_right_ = NULL;
    switch (operation)
    {
    case Or:
    case And:
        m_operation_ = operation;
        m_left_ = left;
        m_right_ = right;
        break;

    default:
        std::cout << "Build Proposition error! Expect Not. Input operation is: " << operation << std::endl;
        break;
    }
}

Proposition::~Proposition()
{

}

std::string Proposition::str() const 
{
    std::stringstream ts;
    ts << '(';
    switch (m_operation_)
    {
    case True:
        ts << "True";
        break;
    case False:
        ts << "False";
        break;
    case Not:
        ts << "!";
        ts << (*m_left_).str();
        break;
    case Or:
        ts << (*m_left_).str();
        ts << "||";
        ts << (*m_right_).str();
        break;
    case And:
        ts << (*m_left_).str();
        ts << "&&";
        ts << (*m_right_).str();
        break;
    case Literal:
        ts << m_atomic_;
        break;
    default:
        ts.clear();
        ts << "Print proposition error!";
        break;
    }
    ts << ')';
    
    return ts.str();
}


std::string StateSet::StateSetStr() const
{
        std::stringstream ts;
        std::string statesetstr;
        for(auto it = m_state_set_.begin(); it != m_state_set_.end(); it ++)
        {
            statesetstr = statesetstr + (*it);
        }
        ts << statesetstr;
        return ts.str();

}


Transition::Transition():
    m_start_state_name_(),
    m_proposition_(),
    m_end_state_name_()
{}

Transition::Transition(std::string start_state_name, Proposition *proposition, std::string end_state_name)
{
    m_start_state_name_ = start_state_name;
    m_proposition_ = proposition;
    m_end_state_name_ = end_state_name;
}

Transition::Transition(StateSet state_set, Proposition *proposition, StateSet end_state_set)
{
    std::set<std::string> s1 = state_set.GetStateSet();
    std::set<std::string> s2 = end_state_set.GetStateSet();

    for(auto it_of_s1 = s1.begin(); it_of_s1 != s1.end(); it_of_s1 ++)
    {
        m_start_state_name_ = m_start_state_name_ + "!" + *it_of_s1;
    }
    m_proposition_ = proposition;
    for(auto it_of_s2 = s2.begin(); it_of_s2 != s2.end(); it_of_s2 ++)
    {
        m_end_state_name_ = m_end_state_name_ + "!" + *it_of_s2;
    }
}

void Transition::PrintTransition() const
{
    std::cout << StartStateNameStr() << " --- " << PropositionStr() << " ---> " << EndStateNameStr() << std::endl;
}

Proposition* Transition::GetProposition() const 
{
    return m_proposition_;
}

std::string Transition::StartStateNameStr() const 
{
    std::stringstream ts;
    ts << m_start_state_name_;
    return ts.str();
}

std::string Transition::PropositionStr() const
{
    std::stringstream ts;
    ts << m_proposition_->str();
    return ts.str();
}
std::string Transition::EndStateNameStr() const
{
    std::stringstream ts;
    ts << m_end_state_name_;
    return ts.str();
}


Transition::~Transition(){}


Nfa::Nfa():
    m_state_set_(),
    m_transition_set_(),
    m_init_state_(),
    m_acc_state_set_()
{}

Nfa::~Nfa(){}

bool Nfa::IsAccState(std::string state_name)
{
    return m_acc_state_set_.find(state_name) != m_acc_state_set_.end();
}

void Nfa::AddState(std::string state_name, StateType state_type)
{
    m_state_set_.insert(state_name);
    switch (state_type)
    {
    case InitState:
        m_init_state_ = state_name;
        break;
    case NormalState:
        break;
    case AccState:
        m_acc_state_set_.insert(state_name);
        break;
    default:
        break;
    }
}

void Nfa::AddComplementState(StateSet state_set, StateType state_type)
{
    std::string state_name;
    std::set<std::string> getstateset = state_set.GetStateSet();
    for(auto it = getstateset.begin(); it != getstateset.end(); it ++)
    {
        state_name = state_name + "!" + (*it);
    }
    m_state_set_.insert(state_name);
    switch (state_type)
    {
    case InitState:
        m_init_state_ = state_name;
        break;
    case NormalState:
        break;
    case AccState:
        m_acc_state_set_.insert(state_name);
        break;
    default:
        break;
    }
}


void Nfa::AddTransition(Transition transition)
{
    m_transition_set_.insert(transition);
}

std::vector<Transition> Nfa::GetTransitionOfAState(std::string state_name) const
{
    std::vector<Transition> ret;
    for(auto it = m_transition_set_.begin(); it != m_transition_set_.end(); it ++)
    {
        if(it->StartStateNameStr() == state_name) ret.push_back(*it);
    }
    return ret;
}

std::string Nfa::GetInitState() const
{
    return m_init_state_;
}

std::set<std::string> Nfa::GetAllStates() const
{
    return m_state_set_;
}

std::set<std::string> Nfa::GetAccStates() const
{
    return m_acc_state_set_;
}


void Nfa::PrintNfa() const
{
    for(auto it_of_m_state_set_ = m_state_set_.begin(); it_of_m_state_set_ != m_state_set_.end(); it_of_m_state_set_ ++)
    {
        std::cout << *it_of_m_state_set_ << std::endl;
        std::vector<Transition> transitions;
        transitions = GetTransitionOfAState(*it_of_m_state_set_);
        for(auto it_of_transitions = transitions.begin(); it_of_transitions != transitions.end(); it_of_transitions ++)
        {
            std::cout << "    ";
            it_of_transitions->PrintTransition();
        }
    }

    std::cout << "InitState: " << m_init_state_ << std::endl;
    std::cout << "AccStates: " << std::endl;
    std::cout << "    ";
    for(auto it = m_acc_state_set_.begin(); it != m_acc_state_set_.end(); it ++)
    {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

}

Clause::Clause() :
    m_proposition_(),
    m_state_set_()
{}


Clause::Clause(Proposition *proposition, StateSet states)
{
    m_proposition_ = proposition;
    m_state_set_ = states;
}

void Clause::PrintClause() const 
{
    std::cout << m_proposition_->str() << ' ' << m_state_set_.StateSetStr() << std::endl;
}

Clause::~Clause(){}


/* 暴力做法 */
void StateSet::StateSetIntersection(StateSet state_set_left, StateSet state_set_right)
{
    m_state_set_.clear();
    std::set<std::string> left = state_set_left.GetStateSet();
    std::set<std::string> right = state_set_right.GetStateSet();
    if(left.size() == 1 && *(left.begin()) == "tt")
    {
        m_state_set_ = right;
        return;
    }
    if(right.size() == 1 && *(right.begin()) == "tt")
    {
        m_state_set_ = left;
        return;
    }
    for(auto it_of_left = left.begin(); it_of_left != left.end(); it_of_left ++)
    {
        m_state_set_.insert(*it_of_left);
    }
    for(auto it_of_right = right.begin(); it_of_right != right.end(); it_of_right ++)
    {
        m_state_set_.insert(*it_of_right);
    }
}


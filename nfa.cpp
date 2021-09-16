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

std::string Proposition::operationtypestr() const
{
    std::stringstream ts;
    switch (m_operation_)
    {
    case True:
        ts << "True";
        break;
    case False:
        ts << "False";
        break;
    case Not:
        ts << "Not";
        break;
    case Or:
        ts << "Or";
        break;
    case And:
        ts << "And";
        break;
    case Literal:
        ts << "Literal";
        break;
    default:
        break;
    }
    return ts.str();
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
        if(m_state_set_.size() == 1 && *(m_state_set_.begin()) == "tt")
        {
            ts << "tt";
            return ts.str();
        }
        //std::cout << "s1" << std::endl;
        for(auto it = m_state_set_.begin(); it != m_state_set_.end(); it ++)
        {
            //std::cout << *it << std::endl;
            statesetstr += "!" + (*it);
        }
        //std::cout << "statesetstr: " << statesetstr << std::endl;
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

    if(state_set.GetStateSetSize() == 1 && *(state_set.GetStateSet().begin()) == "tt")
    {
        m_start_state_name_ = "tt";
    }
    else
    {
        for(auto it_of_s1 = s1.begin(); it_of_s1 != s1.end(); it_of_s1 ++)
        {
            m_start_state_name_ = m_start_state_name_ + "!" + *it_of_s1;
        }
    }
    
    m_proposition_ = proposition;

    if(end_state_set.GetStateSetSize() == 1 && *(end_state_set.GetStateSet().begin()) == "tt")
    {
        m_end_state_name_ = "tt";
    }
    else
    {
        for(auto it_of_s2 = s2.begin(); it_of_s2 != s2.end(); it_of_s2 ++)
        {
            m_end_state_name_ = m_end_state_name_ + "!" + *it_of_s2;
        }
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


/* 插入状态, 根据状态的名字判断它是否是初始状态或接收状态 */
void Nfa::AddState(std::string state_name)
{
    //std::cout << "Adding state: " << state_name << std::endl;
    
    m_state_set_.insert(state_name);

    StateType state_type;
    if(state_name.find("init") != std::string::npos && state_name.find("acc") != std::string::npos)
    {
        state_type = InitAndAccState;
    }
    else if(state_name.find("init") != std::string::npos)
    {
        state_type = InitState;
    }
    else if(state_name.find("acc") != std::string::npos)
    {
        state_type = AccState;
    }
    else
    {
        state_type = NormalState;
    }

    //std::cout << "StateType: " << state_type << std::endl;

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
    case InitAndAccState:
        m_init_state_ = state_name;
        m_acc_state_set_.insert(state_name);
    default:
        break;
    }
}


void Nfa::AddComplementState(StateSet state_set)
{
    /*
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
    */
   std::set<std::string> stateset = state_set.GetStateSet();
   if(stateset.size() == 1 && *(stateset.begin()) == "tt")
   {
       m_state_set_.insert("tt");
       return;
   } 
   if(stateset.size() == 1 && (*(stateset.begin())).find("init") != std::string::npos)
   {
       m_state_set_.insert("!" + *(stateset.begin()));
       m_init_state_ = "!" + *(stateset.begin());
   }

   bool is_acc_state = true;
   std::string state_name;
   for(auto it = stateset.begin(); it != stateset.end(); it ++)
   {
       state_name += "!" + *it;
       if((*it).find("acc") != std::string::npos)
       {
           is_acc_state = false;
       }
   }

   m_state_set_.insert(state_name);
   if(is_acc_state == true)
   {
       m_acc_state_set_.insert(state_name);
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
    std::cout << std::endl << std::endl;

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

std::vector<Clause> StateFormula::ConvertCNFToDNF(std::vector<std::vector<Clause>> clause_intersection)
{
    // std::cout << "ConvertCNFToDNF" << std::endl;
    // for(auto iti = clause_intersection.begin(); iti != clause_intersection.end(); iti ++)
    // {
    //     for(auto itj = iti->begin(); itj != iti->end(); itj ++)
    //     {
    //         itj->PrintClause();
    //     }
    // }
    while(clause_intersection.size() != 1)
    {
        std::vector<Clause> clause_union_1;
        std::vector<Clause> clause_union_2;
        std::vector<Clause> clause_union_res;
        clause_union_1 = clause_intersection.back();
        clause_intersection.pop_back();
        clause_union_2 = clause_intersection.back();
        clause_intersection.pop_back();

        // for(auto it = clause_union_1.begin(); it != clause_union_1.end(); it ++)
        // {
        //     it->PrintClause();
        // }

        // distribute intersection over union
        for(auto it_of_clause_union_1 = clause_union_1.begin(); it_of_clause_union_1 != clause_union_1.end(); it_of_clause_union_1 ++)
        {
            for(auto it_of_clause_union_2 = clause_union_2.begin(); it_of_clause_union_2 != clause_union_2.end(); it_of_clause_union_2 ++)
            {
                
                //Proposition *proposition_disjunction = PropositionDisjunction(it_of_clause_union_1->GetProposition(), it_of_clause_union_2->GetProposition());
                Proposition *proposition_disjunction = new Proposition(Proposition::OperationType::And, it_of_clause_union_1->GetProposition(), it_of_clause_union_2->GetProposition());
                StateSet state_set_intersection;
                
                state_set_intersection.StateSetIntersection(it_of_clause_union_1->GetStateSet(), it_of_clause_union_2->GetStateSet());
                Clause tmp_clause(proposition_disjunction, state_set_intersection);
                
                clause_union_res.push_back(tmp_clause);
            }
        }

        // for(auto it = clause_union_res.begin(); it != clause_union_res.end(); it ++)
        // {
        //     it->PrintClause();
        // }

        clause_intersection.push_back(clause_union_res);
    }

    std::vector<Clause> clause_union = clause_intersection.back();
    std::vector<Clause> clause_ret;


    // 处理多个stateformula的stateset相同的情况(把它们或起来)
    std::set<StateSet> unique_stateset;
    for(auto it = clause_union.begin(); it != clause_union.end(); it ++)
    {
        unique_stateset.insert(it->GetStateSet());
    }

    // for(auto it = unique_stateset.begin(); it != unique_stateset.end(); it ++)
    // {
    //     it->PrintStateSet();
    // }

    for(auto iti = unique_stateset.begin(); iti != unique_stateset.end(); iti ++)
    {
        Clause tmp_clause;
        StateSet tmp_stateset = *iti;
        for(auto itj = clause_union.begin(); itj != clause_union.end(); itj ++)
        {
            if(tmp_stateset == itj->GetStateSet())
            {
                //std::cout << 111 << std::endl;
                Proposition* tmp_proposition;
                if(tmp_clause.GetProposition() == NULL)
                {
                    tmp_proposition = itj->GetProposition();
                }
                else
                {
                    tmp_proposition = new Proposition(Proposition::OperationType::Or, tmp_clause.GetProposition(), itj->GetProposition());
                }
                tmp_clause = Clause(tmp_proposition, tmp_stateset);
            }
        }
        //tmp_clause.PrintClause();
        clause_ret.push_back(tmp_clause);
    }

    // std::cout << "ConvertCNFToDNF" << std::endl;
    // for(auto it = clause_ret.begin(); it != clause_ret.end(); it ++)
    // {
    //     it->PrintClause();
    // }

    return clause_ret;
}

/* 给定状态集合和它们的转移, 计算出该状态集合的StateFormula */
void StateFormula::InsertStateFormula(StateSet state_set, std::vector<Transition> transitions) // to be done
{
    // std::cout << state_set.StateSetStr() << std::endl;
    // for(auto it = transitions.begin(); it != transitions.end(); it ++)
    // {
    //     it->PrintTransition();
    // }
    std::vector<std::vector<Clause>> clause_intersection;
    for(auto it_of_transitions = transitions.begin(); it_of_transitions != transitions.end(); it_of_transitions ++)
    {
        // debug
        //it_of_transitions->PrintTransition();
        Proposition *proposition = it_of_transitions->GetProposition();
        StateSet end_state_set(it_of_transitions->EndStateNameStr());
        Proposition *proposition_not = new Proposition(Proposition::OperationType::Not, proposition);
        StateSet end_state_set_tt("tt");
        
        std::vector<Clause> clause_union;
        
        clause_union.push_back(Clause(proposition_not, end_state_set_tt));
        clause_union.push_back(Clause(proposition, end_state_set));

        // debug
        //clause_union[0].PrintClause();
        //clause_union[1].PrintClause();

        clause_intersection.push_back(clause_union);
    }
    m_state_formulas_[state_set] = ConvertCNFToDNF(clause_intersection);
}

void StateFormula::CalStateFormula()
{
    //还未计算的状态
    std::set<StateSet> not_yet_caled;

    for(auto iti = m_state_formulas_.begin(); iti != m_state_formulas_.end(); iti ++)
    {
        std::vector<Clause> tmp_clause = iti->second;
        for(auto itj = tmp_clause.begin(); itj != tmp_clause.end(); itj ++)
        {
            auto tmp_stateset = itj->GetStateSet();
            if(m_state_formulas_.find(tmp_stateset) == m_state_formulas_.end())
            {
                not_yet_caled.insert(tmp_stateset);
            }
        }
    }

    while(!not_yet_caled.empty())
    {
        StateSet not_yet_caled_stateset = *(not_yet_caled.begin());
        not_yet_caled.erase(not_yet_caled_stateset);
        std::set<std::string> state_set = not_yet_caled_stateset.GetStateSet();
        std::vector<std::vector<Clause>> clause_intersection;
        std::vector<Clause> clause_union;
        for(auto it = state_set.begin(); it != state_set.end(); it ++)
        {
            clause_intersection.push_back(m_state_formulas_ [StateSet(*it)]);
        }
        clause_union = ConvertCNFToDNF(clause_intersection);
        for(auto it = clause_union.begin(); it != clause_union.end(); it ++)
        {
            auto tmp_state_set = it->GetStateSet();
            if(m_state_formulas_.find(tmp_state_set) == m_state_formulas_.end())
            {
                not_yet_caled.insert(tmp_state_set);
            }
        }
        m_state_formulas_[not_yet_caled_stateset] = clause_union;
    }
    m_state_formulas_.erase(StateSet("tt"));
}

void StateFormula::PrintStateFormula() const
{
    for(auto iti = m_state_formulas_.begin(); iti != m_state_formulas_.end(); iti ++)
    {
        
        StateSet state_set = iti->first;
        //std::cout << "StateSetSize: " << state_set.GetStateSetSize() << std::endl;
        std::vector<Clause> clauses_vec = iti->second;
        //std::cout << "vector size: " << clauses_vec.size() << std::endl;
        std::cout << "L(" << state_set.StateSetStr() << ") = " << std::endl;
        for(auto itj = clauses_vec.begin(); itj != clauses_vec.end(); itj ++)
        {
            //std::cout << 11 << std::endl;
            //std::cout << std::endl << itj->GetProposition()->operationtypestr() << std::endl;
            if(itj == clauses_vec.begin()) std::cout << "      {" << itj->GetProposition()->str();
            else std::cout << "union {" << itj->GetProposition()->str();
            std::cout << "} . L(" << itj->GetStateSet().StateSetStr() << ") " << std::endl;
        }
        std::cout << std::endl;
    }
}
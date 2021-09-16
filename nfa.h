#ifndef NFA_H
#define NFA_H

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include <set>
#include <map>


namespace tzzht {




class Proposition {
public:
    enum OperationType
    {
        //调用enum的无参构造函数m_operation()会将m_operation_初始为零. 所以这里从1开始避免歧义
        True = 1,
        False,
        Not,
        Or,
        And,
        Literal
    };
    Proposition();
    Proposition(const OperationType operation);
    Proposition(const OperationType operation, const std::string atomic);
    Proposition(const OperationType operation, Proposition *left);
    Proposition(const OperationType operation, Proposition *left, Proposition *right);
    ~Proposition();
    std::string operationtypestr() const;
    std::string str() const;
private:
    OperationType m_operation_;
    std::string m_atomic_;
    Proposition *m_left_;
    Proposition *m_right_;
};



class StateSet {
public:
    StateSet() : m_state_set_(){};
    StateSet(std::string state){
        std::set<std::string> state_set;
        state_set.insert(state);
        m_state_set_ = state_set;
    }
    StateSet(std::set<std::string> state_set){
        m_state_set_ = state_set;
    }

    std::set<std::string> GetStateSet() const {
        return m_state_set_;
    }

    std::set<std::string>::size_type GetStateSetSize() const {
        return m_state_set_.size();
    }

    std::string StateSetStr() const;

    void PrintStateSet() const{
        std::cout << StateSetStr() << std::endl;
    }

    void AddState(std::string state) {
        m_state_set_.insert(state);
    }

    // 清空m_state_set_, 然后赋值为state_set_left和state_set_right的交集
    void StateSetIntersection(StateSet state_set_left, StateSet state_set_right);

    ~StateSet(){};

    /* 重载<运算符 */
    bool operator < (const StateSet & right)const   
    {
        // std::set<std::string> right_state_set = right.GetStateSet();
        // if(GetStateSetSize() == right_state_set.size())
        // {
        //     for(auto itl = m_state_set_.begin(), itr = right_state_set.begin(); itl != m_state_set_.end() && itr != right_state_set.end(); itl ++, itr ++)
        //     {
        //         if(*itl != *itr) return *itl < *itr;
        //     }
        //     return false;
        // }
        // else
        // {
        //     return GetStateSetSize() < right.GetStateSetSize();
        // } 
        return StateSetStr() < right.StateSetStr();

    }

    bool operator == (const StateSet & right)const
    {
        // bool tmp = StateSetStr() == right.StateSetStr();
        // std::cout << StateSetStr() << " == " << right.StateSetStr() << " " << tmp << std::endl;
        return StateSetStr() == right.StateSetStr();
    }

private:
    std::set<std::string> m_state_set_;
};

class Transition {
public:
    Transition();
    Transition(std::string start_state_name, Proposition *proposition, std::string end_state_name);
    Transition(StateSet state_set, Proposition *proposition, StateSet end_state_set);
    ~Transition();

    void PrintTransition() const;
    Proposition* GetProposition() const;
    std::string StartStateNameStr() const;
    std::string PropositionStr() const;
    std::string EndStateNameStr() const;

    /* 重载<运算符 */
    bool operator < (const Transition & right)const   
    {
        if(m_start_state_name_ == right.m_start_state_name_)
        {
            if(m_proposition_ == right.m_proposition_)
            {
                if(m_end_state_name_ == right.m_end_state_name_)
                {
                    /* 需要完全弱序, 当相等时应该返回false */
                    return false;
                }
                else
                {
                    return m_end_state_name_ < right.m_end_state_name_;
                }
            }
            else
            {
                return m_proposition_ < right.m_proposition_;
            }
        }
        else
        {
            return m_start_state_name_ < right.m_start_state_name_;
        }
    }



private:
    std::string m_start_state_name_;
    Proposition *m_proposition_;
    std::string m_end_state_name_;

};



class Nfa {
public:
    enum StateType{
        InitState,
        NormalState,
        AccState,
        InitAndAccState
    };
    Nfa();
    ~Nfa();
    void AddState(std::string state_name);
    void AddComplementState(StateSet state_set);
    void AddTransition(Transition transition);
    bool IsAccState(std::string state_name);
    std::string GetInitState() const;
    std::set<std::string> GetAllStates() const;
    std::set<std::string> GetAccStates() const;
    void PrintNfa() const;
    std::vector<Transition> GetTransitionOfAState(std::string state_name) const;
private:
    std::set<std::string> m_state_set_;
    std::set<Transition> m_transition_set_;
    std::string m_init_state_;
    std::set<std::string> m_acc_state_set_;

};




class Clause {
public:
    Clause();
    Clause(Proposition* proposition, StateSet states);
    Proposition* GetProposition() const {
        return m_proposition_;
    }
    StateSet GetStateSet() const {
        return m_state_set_;
    }
    void PrintClause() const;
    ~Clause();
private:
    Proposition *m_proposition_;
    StateSet m_state_set_;
};


class StateFormula {
public:
    StateFormula() : 
        m_state_formulas_()
    {}
    ~StateFormula(){}
    std::map<StateSet, std::vector<Clause>> GetStateFormulas() const{
        return m_state_formulas_;
    }
    void InsertStateFormula(StateSet state_set, std::vector<Transition> transitions);
    void CalStateFormula();
    void PrintStateFormula() const;
    std::vector<Clause> ConvertCNFToDNF(std::vector<std::vector<Clause>> clause_intersection);
private:
    std::map<StateSet, std::vector<Clause>> m_state_formulas_;
};


}

#endif //NFA_H
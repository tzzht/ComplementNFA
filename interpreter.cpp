#include "interpreter.h"
#include "nfa.h"
#include <sstream>

using namespace tzzht;


Proposition* PropositionDisjunction(Proposition *proposition_left, Proposition *proposition_right)
{
    return new Proposition(Proposition::OperationType::And, proposition_left, proposition_right);
}

/* 构造函数, 使用初始化列表 */
Interpreter::Interpreter() :
    m_scanner_(*this),
    m_parser_(m_scanner_, *this),
    m_nfa_(),
    m_complement_nfa_(),
    m_location_(0)
{}

void Interpreter::ComplementNfa() {

    std::string init_state = m_nfa_.GetInitState();
    StateSet init_state_set;
    init_state_set.AddState(init_state);
    StateSet tt_state_set;
    tt_state_set.AddState("tt");
    //加入初始节点和tt节点
    m_complement_nfa_.AddComplementState(init_state_set, Nfa::StateType::InitState);
    m_complement_nfa_.AddComplementState(tt_state_set, Nfa::StateType::NormalState);
    m_complement_nfa_.AddTransition(Transition(tt_state_set, new Proposition(Proposition::OperationType::True), tt_state_set));

    //还未计算的状态
    std::set<StateSet> not_yet_caled;
    //已经计算的状态
    std::set<StateSet> caled;


    
    not_yet_caled.insert(init_state_set);

    while(not_yet_caled.empty() == false)
    {
        // 拿出还未计算的一个state_set
        StateSet state_set = *(not_yet_caled.begin());
        //cout << state_set.StateSetStr() << endl;
        not_yet_caled.erase(state_set);
        caled.insert(state_set);

        // 存储转换成的State Formula
        std::vector<std::vector<Clause>> clause_intersection;

        std::set<std::string> getstateset = state_set.GetStateSet();
        // 不能用下面的代码, 会出错
        // for(auto it_of_state_set = state_set.GetStateSet().begin(); it_of_state_set != state_set.GetStateSet().end(); it_of_state_set ++)
        for(auto it_of_state_set = getstateset.begin(); it_of_state_set != getstateset.end(); it_of_state_set ++)
        {
            std::vector<Transition> transitions;
            transitions = m_nfa_.GetTransitionOfAState(*it_of_state_set);


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

        }
        


        // 化简成我们需要的形式
        while(clause_intersection.size() != 1)
        {
            
            std::vector<Clause> clause_union_1;
            std::vector<Clause> clause_union_2;
            std::vector<Clause> clause_union_res;
            clause_union_1 = clause_intersection.back();
            clause_intersection.pop_back();
            clause_union_2 = clause_intersection.back();
            clause_intersection.pop_back();


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
            clause_intersection.push_back(clause_union_res);
        }


        std::vector<Clause> clause_union = clause_intersection.back();
        

        
        // 根据化简出的形式添加转移和状态
        for(auto it_of_clause_union = clause_union.begin(); it_of_clause_union != clause_union.end(); it_of_clause_union ++)
        {
            StateSet end_state_set = it_of_clause_union->GetStateSet();
            Proposition *end_proposition = it_of_clause_union->GetProposition();

            m_complement_nfa_.AddTransition(Transition(state_set, end_proposition, end_state_set));
  
            //如果这个state_set没有被计算过, 就插入到未计算的集合中
            if(caled.find(end_state_set) == caled.end() && end_state_set.StateSetStr() != "tt") not_yet_caled.insert(end_state_set);
        }


        Nfa::StateType state_type;
        bool flag = true;

        for(auto it = getstateset.begin(); it != getstateset.end(); it ++)
        {
            if(m_nfa_.IsAccState(*it)) flag = false;
        }

        if(flag == true) state_type = Nfa::StateType::AccState;
        else state_type = Nfa::StateType::NormalState;
        m_complement_nfa_.AddComplementState(state_set, state_type);
    }
}
int Interpreter::parse() {
    m_location_ = 0;
    /* Run the syntactic analysis, and return 0 on success, 1 otherwise. Both routines are equivalent, operator() being more C++ish. */
    return m_parser_.parse();
}


void Interpreter::increaseLocation(unsigned int loc) {
    m_location_ += loc;
    //cout << "increaseLocation(): " << loc << ", total = " << m_location_ << endl;
}

unsigned int Interpreter::location() const {
    return m_location_;
}  

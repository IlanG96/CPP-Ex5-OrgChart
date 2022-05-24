#include "OrgChart.hpp"
#include <iostream>
#include<string>
#include<vector>
#include <bits/stdc++.h>
using namespace std;

namespace ariel{
/**
 * @brief Construct a new Node:: Node object
 * 
 * @param other - The node you want to copy from
 */
Node::Node(const Node * other){
    if(other != nullptr) {
        this->role_name = other->role_name;
        this->subordinate=other->subordinate;
        this->node_level=other->getlevel();
    }
}

/**
 * @brief return a ptr to the role name;
 * 
 * @return string* 
 */
string* Node::getrole_p(){
    string *p=&role_name;
    return p;
}

Node* Node::Find(const string &role){
    if (this->getrole()==role)
    {
        return this;
    }
    
    Node * ans = nullptr;
        for (auto it = this->subordinate.begin();it != this->subordinate.end();++it)
        {
            ans=(*it)->Find(role);
            if (ans!=nullptr)
            {
                return ans;
            }
            
        }
        return ans; 
}
/************************END NODE CLASS************************************/

/**
 * @brief Construct a new Org Chart (Copy Constructor)
 * 
 */
OrgChart::OrgChart(OrgChart &other){
    this->head=other.head;
    this->level_or_rev_list=other.level_or_rev_list;
    this->pre_list=other.pre_list;
}

OrgChart &OrgChart::add_root(const string& role){
    if (this->head==nullptr){
        this->head = new Node(role,0);
    }
    else{
        this->head->setrole(role);}

    cout<<"[+]"<<role<<" is added as the new head!"<<endl;
    return *this;   
}

OrgChart &OrgChart::add_sub(const std::string& boss_role,const std::string& sub_role){
    if (this->head==nullptr){
        throw runtime_error("Empty tree");
    }
    Node * p=this->head->Find(boss_role);
    if (p==nullptr)
    {
        throw runtime_error("Cant find the parent you are searching for");
    }
    // if(boss_role==sub_role){
    //     throw runtime_error("father and son you entered are the same");
    // }
    // for (auto* element : p->subordinate)
    // {
    //     if(element->getrole()==sub_role){
    //         throw runtime_error("This role is already in the Chart");}
    // } 
    Node *new_role=new Node(sub_role,p->getlevel()+1);
    p->get_subordinate().push_back(new_role);
    cout<<"[+]"<<sub_role << " is added as the new child of "<<boss_role<<endl;
    return *this;

}


void OrgChart::level_or_reverse_order(bool revrese_flag){
    this->level_or_rev_list.clear();
    if (this->head==nullptr){
        return;}
    queue<Node *> q;  // Create a queue
    q.push(this->head); // Enqueue root
    while (!q.empty())
    {
            // Dequeue an item from queue and print it
            Node * curr_node=q.front();
            this->level_or_rev_list.push_back(curr_node);
            q.pop();
            // Enqueue all children of the dequeued item
            if(!revrese_flag){
                for (auto* child : curr_node->get_subordinate()){
                    q.push(child);}
            }
            else{
                //reverse iterator for reverse order
                for (vector<Node*>::reverse_iterator revrese_child = curr_node->get_subordinate().rbegin(); revrese_child != curr_node->get_subordinate().rend(); ++revrese_child ) {
                    q.push(*revrese_child);
                }
            }           
        }
        // the root is still the root in the vector so reverse the order in the vector for reverse order.
        if(revrese_flag){
                reverse(this->level_or_rev_list.begin(), this->level_or_rev_list.end());
        }
        //last item in the vector is nullptr for the end function  
        this->level_or_rev_list.push_back(nullptr);
}

void OrgChart::start_preorder(){
    if (this->head==nullptr){
        return;}
    pre_list.clear();
    stack<Node*> Stack;
    Stack.push(this->head);

    while (!Stack.empty()) {
        Node* curr_node = Stack.top();
        // store the key in preorder vector(visited list)
        pre_list.push_back(curr_node);
        Stack.pop();
        // Push all of the child nodes of temp into
        // the stack from right to left.
        for (vector<Node*>::reverse_iterator revrese_child = curr_node->get_subordinate().rbegin(); revrese_child != curr_node->get_subordinate().rend(); ++revrese_child ){
            Stack.push(*revrese_child);}
        
    }
    this->pre_list.push_back(nullptr); 
}

OrgChart::Iterator OrgChart::begin_level_order(){
    if(this->head==nullptr){
        throw runtime_error("chart is empty!");
    }
    level_or_reverse_order(false);
    return Iterator(0,level_or_rev_list);
}

OrgChart::Iterator OrgChart::end_level_order(){
    if(this->head==nullptr){
        throw runtime_error("chart is empty!");
    }    
    vector<Node*> end_vec;
    end_vec.push_back(nullptr);
    return Iterator(end_vec.size()-1,end_vec);
}

OrgChart::Iterator OrgChart::begin(){
    return begin_level_order();
}

OrgChart::Iterator OrgChart::end(){
    return end_level_order();
}

OrgChart::Iterator OrgChart::begin_reverse_order(){
    if(this->head==nullptr){
        throw runtime_error("chart is empty!");
    }    
    level_or_reverse_order(true);
    return Iterator(0,level_or_rev_list);
}

OrgChart::Iterator OrgChart::reverse_order(){
    return end_level_order();
}

OrgChart::Iterator OrgChart::begin_preorder(){
    if(this->head==nullptr){
        throw runtime_error("chart is empty!");
    }    
    start_preorder();
    return Iterator(0,pre_list);    
}

OrgChart::Iterator OrgChart::end_preorder(){
    return end_level_order();
}


ostream &operator<<(std::ostream &COUT, OrgChart& org){
    if(org.head==nullptr){
        throw runtime_error("empty tree");
    }
    int lvl=0;
    org.level_or_reverse_order(false);
    for (uint i = 0; i < org.level_or_rev_list.size()-1; i++)
    {
        if(org.level_or_rev_list.at(i)->getlevel()==lvl){
            COUT<<org.level_or_rev_list.at(i)->getrole()<<"  ";
        }
        else{
            COUT<<"(Level "<<lvl<<")"<<"\n";
            lvl++;
            i-=1;
            
        }
    }
    COUT<<"(Level "<<lvl<<")"<<"\n";
    return COUT;
}

}

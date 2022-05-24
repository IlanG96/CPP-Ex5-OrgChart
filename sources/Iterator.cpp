#include "OrgChart.hpp"
#include <iostream>
#include<string>
#include<vector>
#include <bits/stdc++.h>
using namespace std;

namespace ariel{


OrgChart::Iterator::Iterator(uint ind,vector<Node*> &order){
        this->order_vec=move(order);
        this->index=ind;    
}

OrgChart::Iterator::Iterator(OrgChart::Iterator &it2){
    this->index=it2.index;
    this->order_vec=it2.order_vec;
}

string OrgChart::Iterator::operator*(){
    if(this->index>=this->order_vec.size()-1){
        throw out_of_range("The iterator is out of range");
    }
   return this->order_vec.at(index)->getrole(); 
}

OrgChart::Iterator& OrgChart::Iterator::operator++(){
    if(this->index>=this->order_vec.size()-1){
        throw out_of_range("The iterator is out of range");
    }
    this->index++;
    return *this;
}

OrgChart::Iterator OrgChart::Iterator::operator++(int){
    if(this->index>=this->order_vec.size()-1){
        throw out_of_range("The iterator is out of range");
    }    
    Iterator it=*this;
    ++this->index;
    return it;
    }

OrgChart::Iterator& OrgChart::Iterator::operator--(){
    if(this->index<0){
        throw out_of_range("The iterator is out of range");
        }    
    this->index--;
    return *this;
    }

OrgChart::Iterator OrgChart::Iterator::operator--(int){
    if(this->index<0){
        throw out_of_range("The iterator is out of range");
    }        
    Iterator it=*this;
    --this->index;
    return it;
}

string *OrgChart::Iterator::operator->(){
    return this->order_vec.at(index)->getrole_p();
}

bool OrgChart::Iterator::operator==(Iterator const &it2)const {
    // cout<<"this:  "<<this->order_vec.at(this->get_index())<<"   Other:  "<<it2.order_vec.at(it2.get_index())<<endl;
    return ((this->order_vec.at(this->get_index())) == (it2.order_vec.at(it2.get_index())));

}

bool OrgChart::Iterator::operator!=(const Iterator& other)const{
    return !(other==*this);
}  

}
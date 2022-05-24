#pragma once
#include <iostream>
#include<string>
#include<vector>
namespace ariel{


class Node
    {
        std::string role_name;
        int node_level;
        std::vector<Node*> subordinate;
        public:
            Node(const std::string& role,int level):role_name(role),node_level(level){}
            Node(const Node* other);

            /**
             * @brief Getters
             */
            int getlevel()const{return node_level;}
            std::string getrole()const{return role_name;}
            std::string* getrole_p();
            std::vector<Node*> &get_subordinate(){return subordinate;}
            int size()const{return this->role_name.size();}
            //********************

            /**
             * @brief Setters
             * 
             * @param level 
             */
            void setlevel(const int level){this->node_level=level;}
            void setrole(const std::string &role){this->role_name=role;}
            //*************

            /**
             * @brief Function that find the role you are searching for in the tree
             * 
             * @param role - role name
             * @return Node* - the role you search for.
             */
            Node* Find(const std::string &role);

    };


class OrgChart
{
    public:
    /**
     * @brief Iterator Class for OrgChart
     * 
     */
    class Iterator : public std::iterator<std::input_iterator_tag, Node*>
    {
    private:
        uint index;
        std::vector<Node*> order_vec; 
    public:
        /**
         * @brief Construct a new Iterator object
         */
        Iterator(uint ind, std::vector<Node*> &order);
        Iterator(Iterator &it2);
        ~Iterator(){}
        Iterator(Iterator &&) = default; // move constructor
        /***************************************/
        
        /**
         * @brief Operators
         */
        std::string operator*();
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        std::string* operator->();
        bool operator == (Iterator const &it2) const;
        bool operator!=(const Iterator& other)const;
        Iterator &operator = (Iterator const &it2);
        Iterator& operator=(Iterator&&) = default;// move assigemnt operator
        /************************************/

        /**
         * @brief Getter
         */
        std::vector<Node*> &get_order(){return order_vec;}
        uint get_index()const{return this->index;}            
    };
    //End of class Iterator


private:
    Node * head;
        std::vector<Node*> level_or_rev_list;
        std::vector<Node*> pre_list;
public:
    /**
     * @brief Constructors
     * 
     */
    OrgChart(/* args */){head=nullptr;} //deafult 
    ~OrgChart(){} //destructor
    OrgChart(OrgChart &other); //copy
    OrgChart(OrgChart &&) = default; // move constructor
    //*******************************************/

    /**
     * @brief Add a root to the OrgChart.
     * if there's already a root change it.
     * 
     * @param role - new root
     * @return OrgChart& - refefence to the orgchart
     */
    OrgChart &add_root(const std::string& role);


    /**
     * @brief Add a child to the org tree.
     * first it find the father and then it add the child to the father children list.
     * @param boss_role - father
     * @param sub_role - child
     * @return OrgChart& - refefence to the orgchart
     */
    OrgChart &add_sub(const std::string& boss_role,const std::string& sub_role);
    
    /**
     * @brief Operators
     */
    OrgChart& operator=(OrgChart const&);
    OrgChart& operator=(OrgChart&&) = default;// move assigemnt operator
    friend std::ostream &operator<<(std::ostream &COUT, OrgChart& org);

    /**
     * @brief Main idea of the code is from geeksforgeeks
     * with a flag added for reverse order.
     * 
     * @param revrese_flag - True REVERSE ORDER
     *                       False Level Order
    */
    void level_or_reverse_order(bool revrese_flag);

    /**
     * @brief Main idea of the code is from geeksforgeeks
     * using a stack to create the preorder tree.
     * 
     */
    void start_preorder();

    /**
     * @brief Begin and end iterators
     */
    Iterator begin();
    Iterator end();
    Iterator begin_preorder();
    Iterator end_preorder();
    Iterator begin_reverse_order();
    Iterator reverse_order();
    Iterator begin_level_order();
    Iterator end_level_order();
    //*****************/

};
}

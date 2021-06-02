#pragma once 
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <queue>
#include <vector>



namespace ariel{

template<typename T>
class BinaryTree{

private:
    

struct Node{
    T value;
    Node* left_child;
    Node* right_child;
    //Node* parent;

    Node():left_child(nullptr),right_child(nullptr){}

    Node(const T& val,Node* lc=nullptr,Node* rc=nullptr):value(val),left_child(lc),right_child(rc){}

    Node(Node* other):Node(other->value){}

    // ~Node(){
    //     //if(this!=nullptr){
    //     if(left_child!=nullptr){delete left_child;}
    //     if(right_child!=nullptr){delete right_child;}
    //     }
    //}    
};




//fields

Node* root;
std::vector<Node*> nodes;


void add_node(const T& val,Node* n);

Node* get_root(){
    return root;
}
//return the node with the given value 
Node* get_node(const T& val){
    if(root!=nullptr&&root->value==val){return root;}
    if(root->left_child!=nullptr&&root->left_child->value==val){return root->left_child;}
    if(root->right_child!=nullptr&&root->right_child->value==val){return root->right_child;}
    for(auto n : nodes){
        if(n->value==val){
            return n;
        }
    }
    return nullptr;
}

//deep copy the tree
void copy(Node* to,const Node* from){
    if(from->left_child!=nullptr){//if the node isnt null copy to value to the given root
        to->left_child = new Node(from->left_child->value);
        nodes.push_back(to->left_child);
        // nodes.push_front(to->left_child);
        copy(to->left_child,from->left_child);
    }
    if(from->right_child!=nullptr){
        to->right_child = new Node(from->right_child->value);
        nodes.push_back(to->right_child);
        // nodes.push_front(to->right_child);
        copy(to->right_child,from->right_child);
    }
}
//return the index of the node in the nodes list if the node isnt in the tree return -1
int get_index(const T& val){
    int index=0;
    for(auto n:nodes){
        if(n->value==val){
            return index;
        }
        index++;
    }
    return -1;
}

//remove the nodes in the tree
void remove_tree_recursive(Node* node){
    if(node!=nullptr){
    remove_tree_recursive(node->left_child);
    remove_tree_recursive(node->right_child);
    // if(get_node(node->value)!=nullptr){
    //     nodes.erase(nodes.begin()+get_index(node->value));
    // }
    delete node;
    }
}




public:


    class iteratorInorder{

    private:
    Node* root;
    Node* current_ptr;
    std::queue<Node*> que;

    public:
    

    iteratorInorder(Node* ptr=nullptr,Node* r=nullptr):current_ptr(ptr),root(r){}
   // iteratorInorder();
    // ~iteratorInorder(){
    //     while(!que.empty()){
    //         que.pop();
    //     }
    //     // root =nullptr;
    //     // current_ptr=nullptr;
    // }

    void inorder(Node* n){
        if(n==nullptr){return ; }
        inorder(n->left_child);
        que.push(n);
        inorder(n->right_child);

    }

    void pop_queue(){
        que.pop();
    }
    Node* queue_front(){
        return que.front();
    }
    

    T& operator*(){
        if(current_ptr==nullptr){throw std::out_of_range("No such node");}
        return (current_ptr->value);
    }
    //
    const T& operator*()const{
        if(current_ptr==nullptr){throw std::out_of_range("No such node");}
        return (current_ptr->value);
    }
    //
    iteratorInorder& operator++() {
       

        if(que.size()==0){
            current_ptr=nullptr;
            return *this;
        }
        // if(first){
        //     que.pop();
        //     first=false;
        //     return *this;
        // }
        current_ptr=que.front();
        que.pop();
      
        return *this;
    }
    //
     iteratorInorder operator++(int){
        const iteratorInorder it = *this;
        if(que.size()==0){
            
            current_ptr = nullptr;
            return it; 
        }
        // if(first){
        //     que.pop();
        //     first=false;
        //     return it;
        // }
        
        current_ptr=que.front();
        que.pop();
        
        return it;
    }
    bool operator==(const iteratorInorder& other)const{
        return current_ptr==other.current_ptr;
    }
    bool operator!=(const iteratorInorder& other)const {
        return !this->operator==(other);
    }

    T* operator->(){
        return &current_ptr->value;
    }

    void set_curr(Node* c ){
        current_ptr=c;
    }

};

//iteratorPreorder


class iteratorPreorder{

    private:
    Node* root;
    Node* current_ptr;
    std::queue<Node*> que;

    public:
       

    iteratorPreorder(Node* ptr=nullptr,Node* r=nullptr):current_ptr(ptr),root(r){}

    // ~iteratorPreorder(){
    //     while(!que.empty()){
    //         que.pop();
    //     }
    //     // root =nullptr;
    //     // current_ptr=nullptr;
    // }

    void preorder(Node* n){
        if(n==nullptr){return ; }
        que.push(n);
        preorder(n->left_child);
        preorder(n->right_child);
    }

    void pop_queue(){
        que.pop();
    }
    Node* queue_front(){
        return que.front();
    }


    T& operator*(){
        return (current_ptr->value);
    }

    const T& operator*()const{
        return (current_ptr->value);
    }
    //
    iteratorPreorder& operator++() {

        if(que.size()==0){
            current_ptr=nullptr;
            return *this;
        }
        current_ptr=que.front();
        que.pop();
      
        return *this;
    }
    iteratorPreorder operator++(int){
        const iteratorPreorder it = *this;
        if(que.size()==0){
            current_ptr = nullptr;
            return it;
        }
        current_ptr=que.front();
        que.pop();
        return it;
    }
    bool operator==(const iteratorPreorder& other)const{
        return current_ptr==other.current_ptr;
    }
    bool operator!=(const iteratorPreorder& other)const {
        return !this->operator==(other);
    }

    T* operator->(){
        return &current_ptr->value;
    }

    void set_curr(Node* c ){
        current_ptr=c;
    }

};


class iteratorPostorder{

    private:
    Node* root;
    Node* current_ptr;
    std::queue<Node*> que;

    public:
    
    

    iteratorPostorder(Node* ptr=nullptr,Node* r=nullptr):current_ptr(ptr),root(r){}

    // ~iteratorPostorder(){
    //     while(!que.empty()){
    //         que.pop();
    //     }
    //     // root =nullptr;
    //     // current_ptr=nullptr;
    // }
    
    void postorder(Node* n){
        if(n==nullptr){return ; }
        postorder(n->left_child);
        postorder(n->right_child);
        que.push(n);
        

    }
    void pop_queue(){
        que.pop();
    }
    Node* queue_front(){
        return que.front();
    }
    

    T& operator*(){
        return (current_ptr->value);
    }
    //
    const T& operator*()const{
        return (current_ptr->value);
    }
    //
    iteratorPostorder& operator++() {
        
        if(que.size()==0){
            current_ptr=nullptr;
            return *this;
        }
        
        current_ptr=que.front();
        que.pop();

        return *this;
    }
    iteratorPostorder operator++(int){
        const iteratorPostorder it = *this;
        if(que.size()==0){
            current_ptr = nullptr;
            return it;
        }
        current_ptr= que.front();
        que.pop();
        return it;
    }
    bool operator==(const iteratorPostorder& other)const{
        return current_ptr==other.current_ptr;
    }
    bool operator!=(const iteratorPostorder& other)const {
        return !this->operator==(other);
    }

    T* operator->(){
        return &current_ptr->value;
    }


    void set_curr(Node* c ){
        current_ptr=c;
    }

};

//end of iterators
    BinaryTree();
    BinaryTree(const BinaryTree<T>& other);
    BinaryTree(BinaryTree<T>&& other)noexcept;
    ~BinaryTree();

    BinaryTree& add_root(const T& val);

    BinaryTree& add_left(const T& obj,const T& obj_sun);

    BinaryTree& add_right(const T& obj,const T& obj_sun);

    iteratorInorder begin();

    iteratorInorder end();

    iteratorPreorder begin_preorder();

    iteratorPreorder end_preorder();

    iteratorInorder begin_inorder();

    iteratorInorder end_inorder();

    iteratorPostorder begin_postorder();

    iteratorPostorder end_postorder();

    BinaryTree& operator= (const BinaryTree& other);

    BinaryTree& operator= (BinaryTree&& other)noexcept;

    
   
    friend std::ostream& operator<< (std::ostream& os,const BinaryTree<T>& bt){
        for(auto n : bt.nodes){
            os<<n->value<<",";
        }
        
        return os;
    }
};




template <typename T>
void BinaryTree<T>::add_node(const T& val,Node* n){
    BinaryTree<T>::nodes[val]=n;
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::add_root(const T& val){
    if(root==nullptr){
    root=new Node(val);
    nodes.push_back(root);
    }
    else{
        (get_node(root->value))->value=val;
    }
    return *this;
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::add_left(const T& obj,const T& obj_sun){
    if(root==nullptr){throw std::out_of_range("This tree does not have root");}
    Node* parent = get_node(obj);
    if(parent==nullptr){throw std::out_of_range("No such value ");}
        if(parent->left_child==nullptr){
            parent->left_child = new Node(obj_sun);
            nodes.push_back(parent->left_child);
        }
        else{
            parent->left_child->value=obj_sun;
        }
    
    return *this;
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::add_right(const T& obj,const T& obj_sun){
    if(root==nullptr){throw std::out_of_range("This tree does not have root");}
    Node* parent = get_node(obj);
    if(parent==nullptr){throw std::out_of_range("No such value ");}
    
        if(parent->right_child==nullptr){
            parent->right_child = new Node(obj_sun);
            nodes.push_back(parent->right_child);
        }
        else{
            parent->right_child->value=obj_sun;
        }
    
    return *this;
}

template <typename T>
BinaryTree<T>::BinaryTree():root(nullptr){}

template <typename T>
BinaryTree<T>::~BinaryTree(){
    if(root!=nullptr){
    remove_tree_recursive(root);
    }
    nodes.clear();
    
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other):BinaryTree(){
   
    root = new Node(other.root->value);
    nodes.push_back(root);
    copy(root,other.root);
   
    
}

template<typename T>
BinaryTree<T>::BinaryTree(BinaryTree<T>&& other)noexcept{
    root=other.root;
    other.root=nullptr;

}


template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& other){
    if(this==&other){
        return *this;
    }
    if(root!=nullptr){
        delete root;
        nodes.clear();
    }
    root = new Node(other.root->value);
    nodes.push_back(root);

    copy(root,other.root);
    return *this;
}
template<typename T>
BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree<T>&& other)noexcept{
    if(root!=nullptr){
        delete root;
    }
    root=other.root;
    other.root=nullptr;
    
}


template <typename T>
typename BinaryTree<T>::iteratorInorder BinaryTree<T>::begin(){
    if(root==nullptr){return iteratorInorder{nullptr};}
   
    iteratorInorder it(root,root);
    
    //curr_ptr=root;
    it.inorder(root);
    it.set_curr(it.queue_front());
    it.pop_queue(); 
    return it;
}

template <typename T>
typename BinaryTree<T>::iteratorInorder BinaryTree<T>::end(){
    return iteratorInorder{nullptr,nullptr};
}

template <typename T>
typename BinaryTree<T>::iteratorPreorder BinaryTree<T>::begin_preorder(){
    if(root==nullptr){return iteratorPreorder{nullptr};}
    iteratorPreorder it(root,root);
    it.preorder(root);
    it.set_curr(it.queue_front());
    it.pop_queue(); 
    return it;
}

template <typename T>
typename BinaryTree<T>::iteratorPreorder BinaryTree<T>::end_preorder(){
    return iteratorPreorder{nullptr};
}

template <typename T>
typename BinaryTree<T>::iteratorInorder BinaryTree<T>::begin_inorder(){
    
    if(root==nullptr){return iteratorInorder{nullptr};}
   
    iteratorInorder it(root,root);
    it.inorder(root);
    it.set_curr(it.queue_front());
    it.pop_queue(); 
   
    
    return it;
}

template <typename T>
typename BinaryTree<T>::iteratorInorder BinaryTree<T>::end_inorder(){
    return iteratorInorder{nullptr};
}

template <typename T>
typename BinaryTree<T>::iteratorPostorder BinaryTree<T>::begin_postorder(){
    if(root==nullptr){return iteratorPostorder{nullptr};}
    
    iteratorPostorder it(root,root);
    it.postorder(root);
    it.set_curr(it.queue_front());
    it.pop_queue(); 
    
    return it;
}

template <typename T>
typename BinaryTree<T>::iteratorPostorder BinaryTree<T>::end_postorder(){
    return iteratorPostorder{nullptr};
}


}


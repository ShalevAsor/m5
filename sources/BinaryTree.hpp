#pragma once 
#include <iostream>
#include <sstream>
#include <fstream>



namespace ariel{

template<typename T>
class BinaryTree{

private:

struct Node{
    T value;
    Node* left_child;
    Node* right_child;
    Node* parent;

    Node(const T& val):value(val){}
};




//fields
Node* curr_ptr;


public:

    class iterator{

    private:

    Node* current_ptr;

    public:

    iterator(Node* ptr=nullptr):current_ptr(ptr){}

    T& operator*(){
        return (current_ptr->value);
    }
    iterator& operator++() {
        current_ptr=current_ptr->right_child;
        return *this;
    }
    iterator& operator++(int){
        iterator temp =*this;
        current_ptr=current_ptr->right_child;
        return temp;
    }
    bool operator==(const iterator& other)const{
        return current_ptr==other.current_ptr;
    }
    bool operator!=(const iterator& other)const {
        return !this->operator==(other);
    }

    T* operator->(){
        return &current_ptr->value;
    }
    

};
    BinaryTree();

    BinaryTree& add_root(const T& val);

    BinaryTree& add_left(const T& obj,const T& obj_sun);

    BinaryTree& add_right(const T& obj,const T& obj_sun);

    iterator begin();

    iterator end();

    iterator begin_preorder();

    iterator end_preorder();

    iterator begin_inorder();

    iterator end_inorder();

    iterator begin_postorder();

    iterator end_postorder();

    
   // template <typename T>
    friend std::ostream& operator<< (std::ostream& os,const BinaryTree<T>& bt){
        
        return os;
    }
    


};

template <typename T>
BinaryTree<T>& BinaryTree<T>::add_root(const T& val){
    curr_ptr=new Node(val);
    return *this;
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::add_left(const T& obj,const T& obj_sun){
    return *this;
}

template <typename T>
BinaryTree<T>& BinaryTree<T>::add_right(const T& obj,const T& obj_sun){
    return *this;
}

template <typename T>
BinaryTree<T>::BinaryTree():curr_ptr(nullptr){}

template <typename T>
typename BinaryTree<T>::iterator BinaryTree<T>::begin(){
    return iterator{curr_ptr};
}

template <typename T>
typename BinaryTree<T>::iterator BinaryTree<T>::end(){
    return iterator{nullptr};
}

template <typename T>
typename BinaryTree<T>::iterator BinaryTree<T>::begin_preorder(){
    return iterator{curr_ptr};
}

template <typename T>
typename BinaryTree<T>::iterator BinaryTree<T>::end_preorder(){
    return iterator{nullptr};
}

template <typename T>
typename BinaryTree<T>::iterator BinaryTree<T>::begin_inorder(){
    return iterator{curr_ptr};
}

template <typename T>
typename BinaryTree<T>::iterator BinaryTree<T>::end_inorder(){
    return iterator{nullptr};
}

template <typename T>
typename BinaryTree<T>::iterator BinaryTree<T>::begin_postorder(){
    return iterator{curr_ptr};
}

template <typename T>
typename BinaryTree<T>::iterator BinaryTree<T>::end_postorder(){
    return iterator{nullptr};
}


}



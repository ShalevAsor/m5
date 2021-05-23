#include <iostream>
#include "sources/BinaryTree.hpp"
#include "doctest.h"
#include <random>

using namespace std;
using namespace ariel;


    

/**
 * This test verify that add_root allows to set a new root in a empty tree 
 * also that if there is already root in this tree the value will change 
 * also examine edge cases 
 */
TEST_CASE("add_root"){
    {
    //init empty tree
    CHECK_NOTHROW(BinaryTree<int> a);
    //init the tree to work with integers
    BinaryTree<int> t1;
    //set the root to 1
    CHECK_NOTHROW(t1.add_root(1));
    //check the value of the root
    int root_val=*t1.begin_preorder();
    CHECK(root_val==1);//the root should be 1 
    //set new value to the root
    CHECK_NOTHROW(t1.add_root(2));
    CHECK(2==*t1.begin_preorder());
    CHECK_NOTHROW(t1.add_root(3).add_root(4).add_root(5));//root value = 5
    CHECK(5==*t1.begin_preorder());
    }
    {
    //same operation for string -make sure that the BinaryTree is genery
    CHECK_NOTHROW(BinaryTree<string> a);
    //init the tree to work with integers
    BinaryTree<string> t1;
    //set the root to 1
    CHECK_NOTHROW(t1.add_root("a"));
    //check the value of the root
    string root_val=*t1.begin_preorder();
    CHECK(root_val=="a");//the root should be 1 
    //set new value to the root
    CHECK_NOTHROW(t1.add_root("b"));
    CHECK("b"==*t1.begin_preorder());
    CHECK_NOTHROW(t1.add_root("c").add_root("d").add_root("e"));//root value = 5
    CHECK("e"==*t1.begin_preorder());
    }
 

}
/**
 * This test verify that add_left allows to add a new value to the left child of the given data in the tree
 * if there is already left child to this data , then the new value will inserted instend of the old value 
 */
TEST_CASE("add_left"){
{
    BinaryTree<int> tree;
    //the tree is empty
    CHECK_THROWS(tree.add_left(1,2));//no root-should throw exception
    tree.add_root(1);
    CHECK_NOTHROW(tree.add_left(1,2));
    CHECK(*tree.begin_inorder()==2);//2 is the left child of the root
    //set new value to the root left child 
    CHECK_NOTHROW(tree.add_left(1,3));
    CHECK(*tree.begin_inorder()==3);//3 is the left child of the root
    CHECK_THROWS(tree.add_left(5,4));//there is no node with the value 5 in this tree
    CHECK_NOTHROW(tree.add_left(3,4).add_left(4,5).add_left(5,6));//added 3 left childs 
    CHECK(*tree.begin_inorder()==6);
    CHECK_NOTHROW(tree.add_right(1,3));//add right child to the root with the value 3 
    CHECK_NOTHROW(tree.add_left(3,15));// should not throw exception even there are two node with the value 3 
}
    //same opration for string
{
    BinaryTree<string> tree;
    //the tree is empty
    CHECK_THROWS(tree.add_left("1","2"));//no root-should throw exception
    tree.add_root("1");
    CHECK_NOTHROW(tree.add_left("1","2"));
    CHECK(*tree.begin_inorder()=="2");//2 is the left child of the root
    //set new value to the root left child 
    CHECK_NOTHROW(tree.add_left("1","3"));
    CHECK(*tree.begin_inorder()=="3");//3 is the left child of the root
    CHECK_THROWS(tree.add_left("5","4"));//there is no node with the value 5 in this tree
    CHECK_NOTHROW(tree.add_left("3","4").add_left("4","5").add_left("5","6"));//added 3 left childs 
    CHECK(*tree.begin_inorder()=="6");
    CHECK_NOTHROW(tree.add_right("1","3"));//add right child to the root with the value 3 
    CHECK_NOTHROW(tree.add_left("3","15"));// should not throw exception even there are two node with the value 3 
}
    
}



/**
 * This test verify that add_right allows to add a new value to the right child of the given data in the tree
 * if there is already right child to this data , then the new value will inserted instend of the old value 
 */
TEST_CASE("add_right"){
{
    BinaryTree<int> tree;
    //the tree is empty
    CHECK_THROWS(tree.add_right(1,2));//no root-should throw exception
    tree.add_root(1);
    CHECK_NOTHROW(tree.add_right(1,2));
   
    //set new value to the root right child 
    CHECK_NOTHROW(tree.add_right(1,3));
    
    CHECK_THROWS(tree.add_right(5,4));//there is no node with the value 5 in this tree
    CHECK_NOTHROW(tree.add_right(3,4).add_right(4,5).add_right(5,6));//added 3 right childs 
    CHECK_NOTHROW(tree.add_left(1,3));//add left child to the root 
    CHECK_NOTHROW(tree.add_right(3,18));//should not throw exception even there are two node with the value 3 

}
    //same opration for string
{
    BinaryTree<string> tree;
    //the tree is empty
    CHECK_THROWS(tree.add_right("1","2"));//no root-should throw exception
    tree.add_root("1");
    CHECK_NOTHROW(tree.add_right("1","2"));
    
    //set new value to the root right child 
    CHECK_NOTHROW(tree.add_right("1","3"));
   
    CHECK_THROWS(tree.add_right("5","4"));//there is no node with the value 5 in this tree
    CHECK_NOTHROW(tree.add_right("3","4").add_right("4","5").add_right("5","6"));//added 3 right childs 
    CHECK_NOTHROW(tree.add_left("1","3"));//add left child to the root 
    CHECK_NOTHROW(tree.add_right("3","18"));//should not throw exception even there are two node with the value 3   
}
    
}

/**
 * This test verify that inorder iterator itreate trough the elements in the tree in the correct order
 * also test the iterator with/without root
 */
TEST_CASE("inorder -iterator"){
{
    BinaryTree<string> tree;
    CHECK_NOTHROW(tree.add_root("1").add_left("1","2").add_right("1","3"));
    /**current tree:
     *    1
     *   / \
     *  2   3
     */      
    //for each should work inorder
    string for_each_val;
    for(const string& val:tree){
        CHECK_NOTHROW(for_each_val+=val);
    }
    CHECK("213"==for_each_val);
    CHECK_NOTHROW(tree.add_right("3","4").add_left("3","5"));
    /**current tree:
     *    1
     *   / \
     *  2   3
     *     / \
     *    5   4
     */ 
    string iterator_val; 
    for(auto it=tree.begin_inorder();it!=tree.end_inorder();++it){
        CHECK_NOTHROW(iterator_val+=*it);
    }
    CHECK("21534"==iterator_val);

    CHECK_NOTHROW(tree.add_left("2","6").add_left("2","2"));
    /**current tree:
     *         1
     *        / \
     *      2    3
     *     / \   / \
     *    6   2 5   4
     */ 
    iterator_val="";
    for(auto it=tree.begin_inorder();it!=tree.end_inorder();++it){
        CHECK_NOTHROW(iterator_val+=*it);
    }
    CHECK("6221534"==iterator_val);
    iterator_val="";
    //for each should return the same results
     for(const string& val:tree){
        CHECK_NOTHROW(for_each_val+=val);
    }
    CHECK("6221534"==iterator_val);

}
{
    //init new tree
    BinaryTree<string> t1;
    CHECK(t1.begin_inorder()==t1.end_inorder());//the tree is empty so begin should be equal to end
    CHECK_NOTHROW(t1.add_root("root"));
    CHECK(t1.begin_inorder()!=t1.end_inorder());//now the begin and the end arent equals   
}
}

/**
 * This test verify that preorder iterator itreate trough the elements in the tree in the correct order
 * also test the iterator with/without root
 */
TEST_CASE("preorder -iterator"){
{
    BinaryTree<string> tree;
    CHECK_NOTHROW(tree.add_root("1").add_left("1","2").add_right("1","3"));
    /**current tree:
     *    1
     *   / \
     *  2   3
     */      
    
    string iterator_val;
    for(auto it=tree.begin_preorder();it!=tree.end_preorder();++it){
        CHECK_NOTHROW(iterator_val+=*it);
    }
    CHECK("123"==iterator_val);
    CHECK_NOTHROW(tree.add_right("3","4").add_left("3","5"));
    /**current tree:
     *    1
     *   / \
     *  2   3
     *     / \
     *    5   4
     */ 
    iterator_val=""; 
    for(auto it=tree.begin_preorder();it!=tree.end_preorder();++it){
        CHECK_NOTHROW(iterator_val+=*it);
    }
    CHECK("12354"==iterator_val);

    CHECK_NOTHROW(tree.add_left("2","6").add_left("2","2"));
    /**current tree:
     *         1
     *        / \
     *      2    3
     *     / \   / \
     *    6   2 5   4
     */ 
    iterator_val="";
    for(auto it=tree.begin_preorder();it!=tree.end_preorder();++it){
        CHECK_NOTHROW(iterator_val+=*it);
    }
    CHECK("1262354"==iterator_val);
}
{
    //init new tree
    BinaryTree<string> t1;
    CHECK(t1.begin_preorder()==t1.end_preorder());//the tree is empty so begin should be equal to end
    CHECK_NOTHROW(t1.add_root("root"));
    CHECK(t1.begin_preorder()!=t1.end_preorder());//now the begin and the end arent equals
    
}

}

/**
 * This test verify that postorder iterator itreate trough the elements in the tree in the correct order
 * also test the iterator with/without root
 */
TEST_CASE("postorder -iterator"){
{
    BinaryTree<string> tree;
    CHECK_NOTHROW(tree.add_root("1").add_left("1","2").add_right("1","3"));
    /**current tree:
     *    1
     *   / \
     *  2   3
     */      
    
    string iterator_val;
    for(auto it=tree.begin_postorder();it!=tree.end_postorder();++it){
        CHECK_NOTHROW(iterator_val+=*it);
    }
    CHECK("231"==iterator_val);
    CHECK_NOTHROW(tree.add_right("3","4").add_left("3","5"));
    /**current tree:
     *    1
     *   / \
     *  2   3
     *     / \
     *    5   4
     */ 
    iterator_val=""; 
    for(auto it=tree.begin_postorder();it!=tree.end_postorder();++it){
        CHECK_NOTHROW(iterator_val+=*it);
    }
    CHECK("23541"==iterator_val);

    CHECK_NOTHROW(tree.add_left("2","6").add_left("2","2"));
    /**current tree:
     *         1
     *        / \
     *      2    3
     *     / \   / \
     *    6   2 5   4
     */ 
    iterator_val="";
    for(auto it=tree.begin_postorder();it!=tree.end_postorder();++it){
        CHECK_NOTHROW(iterator_val+=*it);
    }
    CHECK("6225431"==iterator_val);
}
{
    //init new tree
    BinaryTree<string> t1;
    CHECK(t1.begin_postorder()==t1.end_postorder());//the tree is empty so begin should be equal to end
    CHECK_NOTHROW(t1.add_root("root"));
    CHECK(t1.begin_postorder()!=t1.end_postorder());//now the begin and the end arent equals
    
}

}


struct Person{
    string _name;
    int _id;
    Person(string name,int id):_name(name),_id(id){}
};
/**
 * simple test to verify the BinaryTree can work with Objects
 * 
 */
TEST_CASE("BinaryTree<Object> "){
{
    //add person to the root
    BinaryTree<Person> bt;
    CHECK_NOTHROW(bt.add_root(Person("Avi",313)));
    Person p1("Eli",333);
    CHECK_NOTHROW(bt.add_root(p1));
    //add left and right child 
    CHECK_NOTHROW(bt.add_right(p1,Person("Matan",414)).add_left(p1,Person("Zipi",444)));
    //iterator 
    //inorder
    string names;
    for(const Person& p:bt){
        CHECK_NOTHROW(names+=p._name);
    }
    CHECK(names=="ZipiAviMatan");
    names="";
    for(auto it=bt.begin_postorder();it!=bt.end_postorder();++it){
        names+=it->_name;
    }
    CHECK("ZipiMatanAvi"==names);
    names="";

    for(auto it=bt.begin_preorder();it!=bt.end_preorder();++it){
        names+=it->_name;
    }
    CHECK("AviZipiMatan"==names);

}
}
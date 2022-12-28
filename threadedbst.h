//
// Created by Ali Ibrahim, Vitaliy Karpinskiy, & Younes Lahrichi on 12/6/2021.
//
// ThreadedBST: a normal BST but with the addition of leftover right pointers
// pointing to their inorder successor. This allows for an iterative, inorder
// traversal. The functionalities of a ThreadedBST has the constructor
// take in a number to which then the tree is filled with values from
// 1 to the given number, a copy method, constructor, and assignment
// operator overload, inorder traversal and ostream overload, contains,
// retrieve, getCount, getHeight, isEmpty, clear, and lastly removeEvens,
// a method that removes all evens values from the ThreadedBST.
// 
// TNode: the nodes to which make up the ThreadedBST. has a left and right
// child and a isThread method which dictates whether the right pointer
// is a child or a thread.

#ifndef ASS5_THREADEDBST_H
#define ASS5_THREADEDBST_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class TNode {
  friend class ThreadedBST;
  private:
    int item;
    TNode* left = nullptr;  
    TNode* right = nullptr; 
    bool isThread = false;

    //constructs a TNode with a given value
    explicit TNode(int item = 0);
  public:
    //returns the given item of a TNode.
    int getItem() const;

    //returns the left child of a TNode.
    TNode* getLeft() const;

    //returns the right child or thread of a TNode.
    TNode* getRight() const;

    //returns true if the TNode right pointer is a thread or
    //right child, true if thread, false if child.
    bool getIsThread() const;
};

class ThreadedBST {

  //returns an ostream filled with the output of all the ThreadedBST value.
  friend ostream& operator<<(ostream &out, const ThreadedBST& threadBST);
  
  private:
    TNode* root = nullptr;
    int maxValue;
    int count = 0;

    //a helper method of the indorderTraversal, contains, retrieve, copy,
    //and ostream overload methods, finds the starting point of the
    //thread traversal given a strarting node.
    TNode* getThreadStart(TNode* startNode) const;

    //a helper method of the remove method, takes in a node to
    //rmeoved and its parent and decides which remove to
    //call to remove the node from the tree.
    void deleteNode(TNode* remove, TNode* parent = nullptr);

    //helper method of the bothChildRemove method, finds the
    //lowest value in a subtree given its starting node.
    TNode* findMin(TNode* start);

    //a helper method for removeEvens, finds and
    //removes a given number from the ThreadedBST
    void remove(const int& target);

    //a helper method to build the a balanced tree given
    //a inorder vector of its nodes.
    TNode* buildTree(vector<TNode*> nodes, int start, int end);

    int findHeight(TNode* curr) const;

    //a helper method of the deleteNode method, removes and restructrues
    //the ThreadedBST in the case that the node the be removed has no children.
    void noChildRemove(TNode* remove, TNode* parent);

    //a helper method of the deleteNode method, removes and restructrues
    //the ThreadedBST in the case that the node the be removed has one,
    //left child.
    void leftChildOnlyRemove(TNode* remove, TNode* parent);
    
    //a helper method of the deleteNode method, removes and restructrues
    //the ThreadedBST in the case that the node the be removed has one,
    //right child.
    void rightChildOnlyRemove(TNode* remove, TNode* parent);
    
    //a helper method of the deleteNode method, removes and restructrues
    //the ThreadedBST in the case that the node the be removed has two kids.
    void bothChildRemove(TNode* remove, TNode* parent);

    //a helper method of the clear method, recursively
    //frees up memory being taken up by each indiviual
    //node in the ThreadedBST.
    void eraseTNodes(TNode* curr);

  public:
  
    //sets a ThreadedBST to a deep copy of another
    //ThreadedBST, duplicating its entire tree structure.
    ThreadedBST& copy(const ThreadedBST& threadBST);

    //sets a ThreadedBST to a deep copy of another
    //ThreadedBST, duplicating its entire tree structure.
    ThreadedBST& operator=(const ThreadedBST& threadBST);

    //constructs a balanced and complete ThreadedBST
    //with values from 1 to maxValue and sets the
    //appropiate threads of its nodes.
    explicit ThreadedBST(int maxValue = 0);

    //constructs a deep copy of another ThreadedBST,
    //duplicating its entire tree structure.
    ThreadedBST(const ThreadedBST& threadBST);

    //frees up all memory taken by the ThreadedBST.
    virtual ~ThreadedBST();

    //returns true if the ThreadedBST is empty, false if not.
    bool isEmpty() const;

    //a helper method to find the height of a ThreadedBST,
    //returns the largest height found in the ThreadedBST.
    int getHeight() const;

    //returns the number of nodes in the ThreadedBST
    int getCount() const;

    //removes all even numbers from the ThreadedBST
    void removeEvens();

    //frees up all memory being used by the ThreadedBST.
    void clear();

    //retrieves the node in the ThreadedBST that has the value equal
    //to the given value, returns nullptr if node is not found
    TNode* retrieve(const int& anEntry) const;

    //returns true if a node with a value equal to the given
    //value is in the ThreadedBST, false if not
    bool contains(const int& anEntry) const;

    //returns a vector containing the TNodes found in the
    //ThreadedBST via iterative inorder traversal.
    vector<TNode*> inorderTraverse() const;
};

#endif
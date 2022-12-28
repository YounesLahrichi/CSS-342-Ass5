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

#include "threadedbst.h"

//returns the given item of a TNode.
int TNode::getItem() const {
  return item;
}

//returns the left child of a TNode.
TNode* TNode::getLeft() const {
  return left;
}

//returns the right child or thread of a TNode.
TNode* TNode::getRight() const {
  return right;
}

//returns true if the TNode right pointer is a thread or
//right child, true if thread, false if child.
bool TNode::getIsThread() const {
  return isThread;
}

//constructs a TNode with a given value
TNode::TNode(int item) : item{item} {}

//constructs a balanced and complete ThreadedBST
//with values from 1 to maxValue and sets the
//appropiate threads of its nodes.
ThreadedBST::ThreadedBST(int maxValue) {
  this->maxValue = maxValue;
  vector<TNode*> tree;
  for (int i = 0; i < maxValue; i++) {
    tree.push_back(new TNode(i + 1));
  }
  count = maxValue;
  root = buildTree(tree, 0, maxValue);
  for (int i = 0; i < maxValue - 1; i++) {
    if (tree[i]->right == nullptr) {
      tree[i]->isThread = true;
      tree[i]->right = tree[i + 1];
    }
  }   
}

//constructs a deep copy of another ThreadedBST,
//duplicating its entire tree structure.
ThreadedBST::ThreadedBST(const ThreadedBST& threadBST) {
  copy(threadBST);
}

//sets a ThreadedBST to a deep copy of another
//ThreadedBST, duplicating its entire tree structure.
ThreadedBST& ThreadedBST::copy(const ThreadedBST& threadBST) {
  clear();
  count = threadBST.count;
  maxValue = threadBST.maxValue;
  root = nullptr;
  if (!threadBST.isEmpty()) {
    vector<TNode*> nodes;
    TNode* traverseNode = getThreadStart(threadBST.root);
    while (traverseNode != nullptr) {
      nodes.push_back(new TNode(traverseNode->item));
      traverseNode = traverseNode->isThread ?
       traverseNode->right : getThreadStart(traverseNode->right);
    }
    root = buildTree(nodes, 0, maxValue);
    for (int i = 0; i < nodes.size() - 1; i++) {
      if (nodes[i]->right == nullptr) {
        nodes[i]->isThread = true;
        nodes[i]->right = nodes[i + 1];
      }
    }
  }
  return *this;
}

//sets a ThreadedBST to a deep copy of another
//ThreadedBST, duplicating its entire tree structure.
ThreadedBST& ThreadedBST::operator=(const ThreadedBST& threadBST) {
  return copy(threadBST);
}

//a helper method to build the a balanced tree given
//a inorder vector of its nodes.
TNode* ThreadedBST::buildTree(vector<TNode*> nodes, int start, int end) {
  if (start < end) {
    int mid = (start + end) / 2;
    nodes[mid]->left = buildTree(nodes, start, mid);
    nodes[mid]->right = buildTree(nodes, mid + 1, end);
    return nodes[mid];
  }
  return nullptr;
}

//frees up all memory taken by the ThreadedBST.
ThreadedBST::~ThreadedBST() {
  clear();
}

//returns true if the ThreadedBST is empty, false if not.
bool ThreadedBST::isEmpty() const {
  return count == 0;
}

//return the height of the ThreadedBST.
int ThreadedBST::getHeight() const {
  if (isEmpty()) {
    return 0;
  }
  return findHeight(root);
}

//a helper method to find the height of a ThreadedBST,
//returns the largest height found in the ThreadedBST
int ThreadedBST::findHeight(TNode* curr) const {
  if (curr != nullptr) {
    int left = findHeight(curr->left);
    int right = curr->isThread ? 0 : findHeight(curr->right);
    return 1 + max(left, right);
  }
  return 0;
}

//returns the number of nodes in the ThreadedBST
int ThreadedBST::getCount() const {
  return count;
}

//removes all even numbers from the ThreadedBST
void ThreadedBST::removeEvens() {
  for (int i = 2; i <= maxValue; i += 2) {
    remove(i);
  }
  if (maxValue % 2 == 0) {
    maxValue--;
  }
}

//a helper method for removeEvens, finds and
//removes a given number from the ThreadedBST
void ThreadedBST::remove(const int& target) {
  if (!isEmpty()) {
    TNode* rmvParent = nullptr;
    TNode* rmv = root;
    while (rmv != nullptr) {
      if (rmv->item == target) {
        deleteNode(rmv, rmvParent);
        break;
      } else if (target < rmv->item) {
        rmvParent = rmv;
        rmv = rmv->left;
      } else {
        rmvParent = rmv;
        rmv = rmv->right;
      }
    }
  }
}

//a helper method of the deleteNode method, removes and restructrues
//the ThreadedBST in the case that the node the be removed has two kids.
void ThreadedBST::bothChildRemove(TNode* remove, TNode* parent) {
  TNode* minParent = findMin(remove->right);
  if (minParent->left == nullptr) {
    remove->item = minParent->item;
    deleteNode(minParent, remove);  
  } else {
    remove->item = minParent->left->item;
    deleteNode(minParent->left, minParent);
  }
}

//a helper method of the deleteNode method, removes and restructrues
//the ThreadedBST in the case that the node the be removed has one, left child.
void ThreadedBST::leftChildOnlyRemove(TNode* remove, TNode* parent) {
  if (parent == nullptr) {
    root = remove->left;
    if (root->isThread) {
      root->right = nullptr;
      root->isThread = false;
    }
  } else {
    parent->left = remove->left;
    remove->left->right = parent;
    remove->right = nullptr;
  }
  remove->left = nullptr;
  delete remove;
}

//a helper method of the deleteNode method, removes and restructrues the
// ThreadedBST in the case that the node the be removed has one, right child.
void ThreadedBST::rightChildOnlyRemove(TNode* remove, TNode* parent) {
  if (parent == nullptr) {
    root = remove->right; 
  } else if (parent->left == remove) {
    parent->left = remove->right;
  } else {
    parent->right = remove->right;
  }
  remove->right = nullptr;
  delete remove;
}

//a helper method of the deleteNode method, removes and restructrues
//the ThreadedBST in the case that the node the be removed has no children.
void ThreadedBST::noChildRemove(TNode* remove, TNode* parent) {
  if (parent == nullptr) {
      root = nullptr;
      delete remove;
  } else {
    if (parent->left == remove) {
      parent->left = nullptr;
    } else {
      if (remove->isThread) {
        parent->right = remove->right;  
        parent->isThread = true;
      } else {
        parent->right = nullptr;
      }
    }
    remove->left = nullptr;
    remove->right = nullptr;
    delete remove;
  }
}

//a helper method of the remove method, takes in a node to
//rmeoved and its parent and decides which remove to
//call to remove the node from the tree.
void ThreadedBST::deleteNode(TNode* remove, TNode* parent) {
  if (remove->left != nullptr && (remove->right != nullptr
   && !remove->isThread)) {
    bothChildRemove(remove, parent);
  } else if (remove->left != nullptr) {
    leftChildOnlyRemove(remove, parent);
  } else if (remove->right != nullptr && !remove->isThread) {
    rightChildOnlyRemove(remove, parent);
  } else {
    noChildRemove(remove, parent);
  }
}

//helper method of the bothChildRemove method, finds the
//lowest value in a subtree given its starting node.
TNode* ThreadedBST::findMin(TNode* start) {
  TNode* curr = start;
  if (curr->left == nullptr) {
    return curr;
  }
  while (curr->left->left != nullptr) {
    curr = curr->left;
  }
  return curr; 
}

//frees up all memory being used by the ThreadedBST.
void ThreadedBST::clear() {
  eraseTNodes(root);
}

//a helper method of the clear method, recursively
//frees up memory being taken up by each indiviual
//node in the ThreadedBST.
void ThreadedBST::eraseTNodes(TNode* curr) {
  if (curr != nullptr) {
    eraseTNodes(curr->left);
    if (!curr->isThread) {
      eraseTNodes(curr->right);
    }
    curr->left = nullptr;
    curr->right = nullptr;
    delete curr;
  }
}

//retrieves the node in the ThreadedBST that has the value equal
//to the given value, returns nullptr if node is not found
TNode* ThreadedBST::retrieve(const int& anEntry) const {
  if (isEmpty()) {
    return nullptr;
  }
  TNode* traverseNode = getThreadStart(root);
  while (traverseNode != nullptr) {
    if (traverseNode->item == anEntry) {
      return traverseNode;
    }
    traverseNode = traverseNode->isThread ?
     traverseNode->right : getThreadStart(traverseNode->right);
  }
  return nullptr;
}

//returns true if a node with a value equal to the given
//value is in the ThreadedBST, false if not
bool ThreadedBST::contains(const int& anEntry) const {
  if (isEmpty()) {
    return false;
  }
  TNode* traverseNode = getThreadStart(root);
  while (traverseNode != nullptr) {
    if (traverseNode->item == anEntry) {
      return true;
    }
    traverseNode = traverseNode->isThread ?
     traverseNode->right : getThreadStart(traverseNode->right);
  }
  return false;
}

//a helper method of the indorderTraversal, contains, retrieve, copy,
//and ostream overload methods, finds the starting point of the
//thread traversal given a strarting node.
TNode* ThreadedBST::getThreadStart(TNode* startNode) const {
  TNode* start = startNode;
  if (startNode == nullptr) {
    return nullptr;
  } 
  while (start->left != nullptr) {
    start = start->left;
  }
  return start;
}

//returns a vector containing the TNodes found in the
//ThreadedBST via iterative inorder traversal.
vector<TNode*> ThreadedBST::inorderTraverse() const {
  vector<TNode*> nodes;
  if (isEmpty()) {
    return nodes;
  }
  TNode* traverseNode = getThreadStart(root);
  while (traverseNode != nullptr) {
    nodes.push_back(traverseNode);
    traverseNode = traverseNode->isThread ?
     traverseNode->right : getThreadStart(traverseNode->right);
  }
  return nodes;
}

//returns an ostream filled with the output of all the ThreadedBST value.
ostream& operator<<(ostream &out, const ThreadedBST& threadBST) {
  if (threadBST.isEmpty()) {
    return out << "Empty Binary Search Tree." << endl;
  }
  TNode* traverseNode = threadBST.getThreadStart(threadBST.root);
  while (traverseNode != nullptr) {
    out << traverseNode->getItem() << ", ";
    traverseNode = traverseNode->getIsThread() ?
     traverseNode->getRight() :
      threadBST.getThreadStart(traverseNode->getRight());
  }
  return out;
}


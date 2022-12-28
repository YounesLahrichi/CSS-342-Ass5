//
// Created by Ali Ibrahim, Vitaliy Karpinskiy, & Younes Lahrichi on 12/6/2021.
//
//Runs test for methods and operator overload in the ThreadedBST class

#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include "threadedbst.h"

using namespace std;

/* runs tests to cover:
    - normal constructor 
    - copy constructor 
    - removeEvens
    - cout printing
*/
void testCopyConstructor() {
  string result = "";
  string noEvenResult = "";
  stringstream t1Results;
  stringstream t2Results;
  for (int i = 1; i <= 150; i++) {
    if (i % 2 > 0) {
      noEvenResult += to_string(i) + ", ";
    }
    result += to_string(i) + ", ";
    ThreadedBST t1(i);
    ThreadedBST t2(t1);
    t2.removeEvens();
    t1Results << t1;
    t2Results << t2;
    assert(t1Results.str() == result);
    assert(t2Results.str() == noEvenResult);
    t1Results.str("");
    t2Results.str("");
  }
}

/* runs tests to cover:
    - normal constructor 
    - copy method
    - removeEvens method
    - inorderTraverse method
    - retrieve method
    - contains method
*/
void testInOrderTraversal() {
  vector<int> result;
  vector<int> noEvenResult;
  for (int i = 1; i <= 50; i++) {
    if (i % 2 > 0) {
      noEvenResult.push_back(i);
    }
    result.push_back(i);
    ThreadedBST t1(i);
    ThreadedBST t2;
    t2.copy(t1);
    t2.removeEvens();
    vector<TNode*> outcome = t1.inorderTraverse();
    vector<TNode*> outcomeNoEvens = t2.inorderTraverse();
    for (int j = 0; j < result.size(); j++) {
      assert(t1.contains(result[j]));
      assert(t1.retrieve(result[j])->getItem() == result[j]);
      assert(outcome[j]->getItem() == result[j]);
    }
    for (int j = 0; j < noEvenResult.size(); j++) {
      assert(t2.contains(noEvenResult[j]));
      assert(t2.retrieve(noEvenResult[j])->getItem() == noEvenResult[j]);
      assert(outcomeNoEvens[j]->getItem() == noEvenResult[j]);
    }
  }
}

/* runs tests to cover:
    - normal constructor 
    - assignment operator 
    - removeEvens
    - cout printing
*/
void testAssignmentOperator() {
  string result = "";
  string noEvenResult = "";
  stringstream t1Results;
  stringstream t2Results;
  for (int i = 1; i <= 100; i++) {
    if (i % 2 > 0) {
      noEvenResult += to_string(i) + ", ";
    }
    result += to_string(i) + ", ";
    ThreadedBST t1(i);
    ThreadedBST t2;
    t2 = t1;
    t2.removeEvens();
    t1Results << t1;
    t2Results << t2;
    assert(t1Results.str() == result);
    assert(t2Results.str() == noEvenResult);
    t1Results.str("");
    t2Results.str("");
  }
}

/* runs tests to cover:
    - normal constructor 
    - getLength
*/
void testGetLength() {
  ThreadedBST t1(1);
  assert(t1.getHeight() == 1);
  ThreadedBST t2(2);
  assert(t2.getHeight() == 2);
  ThreadedBST t3(5);
  assert(t3.getHeight() == 3);
}

/* runs tests to cover:
    - normal constructor 
    - getCount
*/
void testGetCount() {
  int correctCount = 0;
  for (int i = 1; i <= 50; i++) {
    correctCount++;
    ThreadedBST t1(i);
    assert(t1.getCount() == correctCount);
  }
}

/* runs tests to cover:
    - empty constructor 
    - getCount
    - getLength
    - copy constructor
    - assignment operator
    - ostream operator
*/
void testEmptyTree() {
  ThreadedBST t1;
  assert(t1.getCount() == 0);
  assert(t1.getHeight() == 0);
  assert(t1.isEmpty());
  ThreadedBST t2;
  t2 = t1;
  assert(t2.getCount() == 0);
  assert(t2.getHeight() == 0);
  assert(t2.isEmpty());
  ThreadedBST t3(t1);
  assert(t3.getCount() == 0);
  assert(t3.getHeight() == 0);
  assert(t3.isEmpty());
}

//runs all tests
int main() { 
  testCopyConstructor();
  cout << "copy constructor tests: successfull" << endl;
  testAssignmentOperator();
  cout << "assignment operator tests: successfull" << endl;
  testEmptyTree();
  cout << "empty tree tests: successfull" << endl;
  testGetCount();
  cout << "getCount tests: successfull" << endl;
  testGetLength();
  cout << "getHeight tests: successfull" << endl;
  testInOrderTraversal();
  cout << "inorderTraverse tests: successfull" << endl;
  cout << "---------------------------------------------" << endl;
  cout << "NOTE: various other smaller functionalities" << endl <<
   "were tested in the above tests, look at the method" << endl <<
    "test comments to see what other functionalities were" << endl <<
     "tested in the test methods." << endl;
  cout << "---------------------------------------------" << endl;
  cout << "all tests successfull!" << endl;
  return 0;
} 


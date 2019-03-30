//--------------------------------bintree.h--------------------------------
//Johnathan Hewit
//Created: 01/20/2019
//Modified: 01/28/2019
//---------------------------------------------------------------------------
//Purpose: Header file for BinTree, a Binary Search Tree. It uses a separate
//         object class called NodeData to hold its data, and a struct called
//         Node for each node in the Binary Tree.
//---------------------------------------------------------------------------
//Notes: Assumption: NodeData provides proper data checking and overloads
//       appropriate operators for comparison.
//---------------------------------------------------------------------------
#ifndef BINTREE_H
#define BINTREE_H
#include <iostream>
#include "nodedata.h"
using namespace std;

class BinTree
{
public:
  //Constructors
  BinTree();
  BinTree(BinTree &bin);
  ~BinTree();

  //Getters
  int getHeight(const NodeData &target) const;
  bool retrieve(const NodeData &target, NodeData* &location) const;
  bool isEmpty() const;
  void displaySideways() const;

  //Setters
  bool insert(NodeData* data);
  void makeEmpty();
  void bstreeToArray(NodeData* array[]);
  void arrayToBSTree(NodeData* array[]);

  //Operator Overloads
  //Assignment
  BinTree& operator=(const BinTree &bin);
  //Equality
  bool operator==(const BinTree &bin) const;
  bool operator!=(const BinTree &bin) const;
  //Output
  friend ostream& operator<<(ostream &print, const BinTree &bin);

private:
  struct Node
  {
    NodeData* data;
    Node* left;
    Node* right;
  };
  Node* root;

  //Private and Helper Functions
  int findHeight(Node* root, const NodeData &target) const;
  void inOrderPrint(Node* root, ostream &print) const;
  void copyTree(Node*& newRoot, Node* oldRoot);
  void emptyTree(Node* &root);
  bool findEquality(Node* root, Node* otherRoot) const;
  int treeToArray(Node* root, NodeData* array[], int& index);
  void arrayToTree(Node* &root, NodeData* array[], int low, int high);
  void sideways(Node* root, int level) const;
  bool findData(Node* root, const NodeData target, NodeData* &location, Node* &nodeLocation) const;
};

#endif

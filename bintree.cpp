//--------------------------------bintree.cpp--------------------------------
//Johnathan Hewit
//Created: 01/20/2019
//Modified: 01/28/2019
//---------------------------------------------------------------------------
//Purpose: Implementation file for BinTree, a Binary Search Tree. It uses a
//         separate object class called NodeData to hold its data, and a
//         struct called Node for each node in the Binary Tree.
//---------------------------------------------------------------------------
//Notes: Assumption: NodeData provides proper data checking and overloads
//       appropriate operators for comparison.
//---------------------------------------------------------------------------
#include <iostream>
#include "bintree.h"
using namespace std;

//-------------------------------BinTree-------------------------------------
//Description: Empty Constructor - set default values.
//---------------------------------------------------------------------------
BinTree::BinTree()
{
  this->root = nullptr;
} //end of BinTree

//------------------------------BinTree(bin)---------------------------------
//Description: Copy constructor - calls copyTree helper to copy the BST.
//---------------------------------------------------------------------------
BinTree::BinTree(BinTree &bin)
{
  this->root = nullptr;
  copyTree(this->root, bin.root);
} //end of BinTree(bin)

//--------------------------------~BinTree-----------------------------------
//Description: Destructor - calls makeEmpty helper to empty tree.
//---------------------------------------------------------------------------
BinTree::~BinTree()
{
  if (!isEmpty())
  {
    makeEmpty();
  }
} //end of ~BinTree

//--------------------------------retrieve-----------------------------------
//Description: Searches for, and assigns if located, the desired target value
//             in the BST. Returns true if found, false if not. Calls findData
//             helper.
//---------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData &target, NodeData* &location) const
{
  if (isEmpty()) //If the BST is empty, return false.
  {
    return false;
  }
  Node* nodeLocation; //Node for the node location of the target NodeData
  bool found = findData(root, target, location, nodeLocation); //Otherwise, call
  if (!found)                                                  //call the helper
  {                                                            //function to find
    return false;
  }
  return true;
} //end of retrieve

//--------------------------------findData-----------------------------------
//Description: Recursive elper function to locate specified NodeData and identify
//             the Node it's at. Returns true if found, false if not.
//---------------------------------------------------------------------------
bool BinTree::findData(Node* root, const NodeData target, NodeData* &location, Node* &nodeLocation) const
{
  if (root == nullptr) //Base case: If the node is empty, it's not in BST
  {
    return false;
  }
  else if (target == *root->data) //If target is found, set the node location,
  {                               //and the NodeData value, and return true
    location = root->data;
    nodeLocation = root;
    return true;
  }
  else if (target < *root->data) //If the node's value is larger than the target
  {                              //then go left
    return findData(root->left, target, location, nodeLocation);
  }
  else //Otherwise, go right
  {
    return findData(root->right, target, location, nodeLocation);
  }
} //end of findData

//-------------------------------getHeight-----------------------------------
//Description: Public function to find the height of the specified NodeData.
//             Calls findHeight helper function for calculation.
//---------------------------------------------------------------------------
int BinTree::getHeight(const NodeData &target) const
{
  if (isEmpty()) //If the BST is empty, per definition, the height is 0
  {
    return 0;
  }
  NodeData *location;
  if (!retrieve(target, location)) //If the NodeData isn't found, return 0
  {
    return 0;
  }
  Node* nodeLocation;
  findData(this->root, target, location, nodeLocation);
  return findHeight(nodeLocation, target);
} //end of getHeight

//-------------------------------findHeight----------------------------------
//Description: Recursive helper function to calculate the height of the
//             specified node.
//---------------------------------------------------------------------------
int BinTree::findHeight(Node* root, const NodeData &target) const
{
  if (root == nullptr) //Base Case: If reached an empty node, return 0
  {
    return 0;
  }
  int leftSide = findHeight(root->left, target);
  int rightSide = findHeight(root->right, target);
  if (leftSide > rightSide) //Determine which side is "taller", then return height
  {
    return leftSide + 1; //Add the 1 for the starting node, and return the value
  }                      //for the taller side
  else
  {
    return rightSide + 1;
  }
} //end of findHeight

//-------------------------------isEmpty-------------------------------------
//Description: Determines if the BST is empty, returns true is yes, false if no.
//---------------------------------------------------------------------------
bool BinTree::isEmpty() const
{
  return (this->root == nullptr);
} //end of isEmpty

//--------------------------------insert-------------------------------------
//Description: Inserts NodeData object into the BST in the correct location
//             if it does not already exist. Does so by iterations instead
//             of recursion.
//---------------------------------------------------------------------------
bool BinTree::insert(NodeData* data)
{
  Node* newNode = new Node; //Allocate memory for the new node to be inserted
  newNode->data = data;     //and assign it the NodeData being passed in
  newNode->left = nullptr;
  newNode->right = nullptr; //Initialize left and right pointers to nullptr
  if (isEmpty())
  {
    this->root = newNode; //If the BST is empty, insert the node at the root
  }
  else
  {
    Node* current = root;  //Create a node pointer to traverse from the root
    bool inserted = false; //Flag indicating whether or not the node is inserted
    while (!inserted) //Keep going through the BST until the node is inserted
    {
      if (*current->data == *data) //If the NodeData is in the BST, do not insert
      {
        delete newNode; //And delete the node created
        newNode = nullptr;
        return false;
      }
      else if (*current->data > *data) //If the NodeData is less than the current node
      {
        if (current->left == nullptr) //We've reached a leaf, and we can insert
        {
          current->left = newNode;
          inserted = true;
        }
        else //Otherwise, we continue going left
        {
          current = current->left;
        }
      }
      else //Otherwise, the NodeData is greater than the current node
      {
        if (current->right == nullptr) //We've reached a leaf, and we can insert
        {
          current->right = newNode;
          inserted = true;
        }
        else //Otherwise, we continue going left
        {
          current = current->right;
        }
      }
    }
  }
  return true; //If we've made it here, then the Node was inserted successfully
} //end of insert

//-----------------------------bstreeToArray---------------------------------
//Description: Public function for converting the BST into an array, preserving
//             the in-order ordering of the BST. Calls the treeToArray helper.
//---------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* array[])
{
  int index = 0; //Set first index of the array
  treeToArray(root, array, index); //Call helper, then empty the BST once
  emptyTree(root);                 //conversion is finished
} //end of bstreeToArray

//-------------------------------treeToArray---------------------------------
//Description: Recursive helper function for converting the BST into an array,
//             preserving the in-order ordering of the BST.
//---------------------------------------------------------------------------
int BinTree::treeToArray(Node* root, NodeData* array[], int& index)
{
  if (root == nullptr) //Base case: If the node is empty, go back
  {
    return 0;
  }
  else //Otherwise, recursively insert the node into the next index in the array
  {    //using in-order traversal
    treeToArray(root->left, array, index); //In-order; go down left side first
    array[index] = root->data; //Assign node value to the current index in array
    root->data = nullptr; //Cut the data in the node to avoid duplications
    index++; //Increment the index
    treeToArray(root->right, array, index); //Lastly, go down the right side
  }
} //end of treeToArray

//-----------------------------arrayToBSTree---------------------------------
//Description: Public function to convert an incoming array into a balanced
//             BST. Calls helper arrayToTree.
//---------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* array[])
{
  int high, low; //Estblish variables for the indexes of the array
  high = low = 0;
  for (int i = 0; i < 100; i++) //Determine largest index in the array by looping
  {                             //over maximum size. Assumption: MAX_SIZE = 100;
    if (array[i] != nullptr)
    {
      high++;
    }
  }
  arrayToTree(this->root, array, low, high - 1); //Call helper function to convert
} //end of arrayToBSTree                         //to BST

//-------------------------------arrayToTree---------------------------------
//Description: Recursive helper function to convert given array of NodeData
//             into a BST.
//---------------------------------------------------------------------------
void BinTree::arrayToTree(Node* &root, NodeData* array[], int low, int high)
{
  if (high < low) //Base Case: If high is less than low, the function has gone
  {               //through entire array, or incorrect value for indexes
    root == nullptr;
  }
  else
  {
    int rootIndex = (low + high) / 2;    //Formula for the index of the array that
    NodeData* newData = array[rootIndex];//will be the root for the BST
    insert(newData); //Estblish new node with data of the array, then pass to insert
    arrayToTree(root->left, array, low, rootIndex - 1); //In-order: go left in BST
    arrayToTree(root->right, array, rootIndex + 1, high);//then right, going through
  }                                                     //elements in array
} //end of arrayToTree

//-------------------------------makeEmpty-----------------------------------
//Description: Public function for emptying the BST, which removes all nodes
//             and NodeData from the BST. Calls the emptyTree helper.
//---------------------------------------------------------------------------
void BinTree::makeEmpty()
{
  emptyTree(root);
} //end of makeEmpty

//--------------------------------emptyTree----------------------------------
//Description: Recursive helper function for emptying the BST, which removes
//             all nodes and NodeData from the BST. Uses Post-Order traversal
//             to delete NodeData in each leaf, then going up to the node.
//---------------------------------------------------------------------------
void BinTree::emptyTree(Node* &root)
{
  if (root == nullptr) //Base case: If the node is empty, go back
  {
    return;
  }
  else //Otherwise, traverse the BST is post-order so that the children are
  {    //deleted before the parent nodes
    emptyTree(root->left); //Post-order: traverse left, then right, then the node
    emptyTree(root->right);
    delete root->data; //Delete data first, then the node
    root->data = nullptr; //Assign each to a nullptr once deleted
    delete root;
    root = nullptr;
  }
} //end of emptyTree

//-------------------------------operator=-----------------------------------
//Description: Operator overload for assignment. Sets the current BinTree
//             to the incoming BinTree. Calls the helper copyTree.
//---------------------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree &bin)
{
  if (*this == bin) //If the BSTs are the same, return the same BST
  {
    return *this;
  }
  else //Otherwise, deep copy the incoming BST
  {
    emptyTree(this->root); //Begin to emptying current BinTree
    copyTree(this->root, bin.root); //Then call helper to individually deep copy
    return *this;                   //each Node and NodeData and return new BST
  }
} //end of operator=

//---------------------------------copyTree----------------------------------
//Description: Recursive helper function for deep copying Nodes and NodeData
//             of another BinTree.
//---------------------------------------------------------------------------
void BinTree::copyTree(Node* &newRoot, Node* oldRoot)
{
  if (oldRoot == nullptr) //If the copying from Node is empty, set the new Node
  {                       //to empty
    newRoot = nullptr;
  }
  else //Otherwise, deep copy the node and its data by creating a new Node and
  {    //NodeData
    newRoot = new Node; //Allocate memory for new Node, and set the data
    NodeData *newData = new NodeData(*oldRoot->data); //Allocate memory for NodeData
    newRoot->data = newData; //Set the new Node's data value to the copying NodeData
    copyTree(newRoot->left, oldRoot->left); //In-Order: traverse left, then right
    copyTree(newRoot->right, oldRoot->right);
  }
} //end of copyTree

//-------------------------------operator==----------------------------------
//Description: Operator overload for determining equality. Returns true if
//             the two BinTrees are the same, and false if not. Calls
//             helper findEquality.
//---------------------------------------------------------------------------
bool BinTree::operator==(const BinTree &bin) const
{
  if (isEmpty() && bin.isEmpty()) //If they're both empty, they are the same
  {
    return true;
  }
  else //Otherwise, call helper function to determine equality by comparing
  {    //nodes and their data
    return findEquality(this->root, bin.root);
  }
} //end of operator==

//-------------------------------operator!=----------------------------------
//Description: Operator overload for determining equality. Returns false if
//             the two BinTrees are the same, and true if not. Calls helper
//             findEquality.
//---------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree &bin) const
{
  return !(*this == bin); //Use equality operator to determine inequality
} //end of operator!=

//------------------------------findEquality---------------------------------
//Description: Recursive helper function to determine equality of two BinTrees
//             by checking each Node and its NodeData.
//---------------------------------------------------------------------------
bool BinTree::findEquality(Node* root, Node* otherRoot) const
{
  if ((root != nullptr && otherRoot != nullptr) && (*root->data == *otherRoot->data))
  { //Base case 1: If the node is not empty and the NodeData is the same, they are the same
    return true;
  }
  if ((root == nullptr) || (otherRoot == nullptr))
  { //Base case 2: If either of them are empty, they are different
    return false;
  } //Return true if the last leaf's NodeData matches after recursive calls, false if not
  return (*root->data == *otherRoot->data) && findEquality(root->left, otherRoot->left) && findEquality(root->right, otherRoot->right);
} //end of findEquality

//-------------------------------operator<<----------------------------------
//Description: Operator overload for printing to the console. Calls helper
//             inOrderPrint.
//---------------------------------------------------------------------------
ostream& operator<<(ostream &print, const BinTree &bin)
{
  bin.inOrderPrint(bin.root, print); //Call recursive helper
  print << endl; //Go to a new line after printing per instructions
  return print;
} //end of operator<<

//-------------------------------inOrderPrint--------------------------------
//Description: Recursive helper function to print each value in the BST using
//             in-order traversal.
//---------------------------------------------------------------------------
void BinTree::inOrderPrint(Node* root, ostream &print) const
{
  if (root == nullptr) //Base case: If node is empty, go back
  {
    return;
  }
  inOrderPrint(root->left, print); //In-order: Go left until out of leftward Nodes
  print << *root->data << " "; //Then print the Node
  inOrderPrint(root->right, print); //Then go right
} //end of inOrderPrint

//------------------------------displaySideways------------------------------
//Description: Public function to display the BST as if viewing it from the
//             side; hard coded displaying to standard output. Calls helper
//             sideways.
//---------------------------------------------------------------------------
void BinTree::displaySideways() const
{
  sideways(root, 0);
} //end of displaySideways

//--------------------------------sideways-----------------------------------
//Description: Recursive helper function for displaying the BST sideways.
//---------------------------------------------------------------------------
void BinTree::sideways(Node* current, int level) const
{
  if (current != nullptr)
  {
    level++;
    sideways(current->right, level);
    for (int i = level; i >= 0; i--)
    {
      cout << "    "; //Indent for readability
    }
    cout << *current->data << endl; //Display information of the NodeData
    sideways(current->left, level);
  }
} //end of sideways

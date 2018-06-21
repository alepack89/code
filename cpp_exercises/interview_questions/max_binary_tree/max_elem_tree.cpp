/*
* Problem: Maximum Binary Tree
* Given an input array of values, create and display a tree with the following rules
*   - The root is the maximum nunber in the array
*   - The left subtree is the maximum tree constructed from the sub-array on the left of the maximum value
*   - The right subtree is the maximum tree constructed from the sub-array on the right of the maximum value
*
* e.g. Array = [0, -1, 5, 3, 9, 2, 6]
* Output:
*             9
*         /      \
*        5        6
*      /   \     /
*     0     3   2
*      \
*       -1
*
* Note: The tree need not to be displayed vertically
*/

//Include standard library
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

//Include node implementation
#include "node.hpp"

//Import everything from standard namespace
using namespace std;

//Creates the tree from the input array
template<typename IterType>
auto createTreeFromArray(IterType begin, IterType end)
{
  //Get value type
  using ValueType   = typename iterator_traits<IterType>::value_type;
  using NodeType    = TreeNode<ValueType>;
  using NodePtrType = unique_ptr<NodeType>;

  //Check if input range is valid
  if (distance(begin, end) <= 0)
    return NodePtrType(nullptr);

  //Get maximum value inside the array
  IterType maxValIter = max_element(begin, end);
  
  //Create new node containing max element
  NodePtrType newNode = make_unique<NodeType>(*maxValIter);

  //Add left and right subtrees
  newNode->left  = createTreeFromArray(begin, maxValIter);
  newNode->right = createTreeFromArray(next(maxValIter), end);

  //Return created node
  return newNode;
}

//Displays the input tree from left to right on the console
template<typename ValueType>
void displayTree(const unique_ptr<TreeNode<ValueType>>& tree, int level = 0, const string& prefix = "")
{
  //Check if tree is empty
  if (tree == nullptr)
    return;

  //Display right subtree
  displayTree(tree->right, level + 1, "/");

  //Write current node
  cout << string(level, '\t') << prefix << ' ' << tree->val << endl;

  //Display left subtree
  displayTree(tree->left, level + 1, "\\");
}

//Main methods
int main(int argc, char* argv[])
{
  //Define input array
  vector<double> inArray = { 0, -1, 5, 3, 9, 2, 6, 3, 15, 1, 10, -2, 8, 12, -6 };

  //Create tree from array
  unique_ptr<TreeNode<double>> root = createTreeFromArray(cbegin(inArray), cend(inArray));

  //Display tree
  displayTree(root);

  //Code exited normally 
  return 0;
}
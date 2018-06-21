#ifndef _MAX_ELEM_TREE_NODE_H
#define _MAX_ELEM_TREE_NODE_H

/*
* Tree node implementation
*/

//Include standard library
#include <cstdlib>
#include <memory>

//Class representing a generic tree node
//containing a numerical value
template<typename DType>
class TreeNode 
{
  //--------------------------------
  //Properties

  public:

    DType val;

    std::unique_ptr<TreeNode> left;
    std::unique_ptr<TreeNode> right;

  //--------------------------------
  //Constructors and destructors

  public:

    //Default constructor
    TreeNode()
      : val{}
    {
    }

    //Instantiates a node having the specified value 
    template<typename T>
    TreeNode(T&& inVal)
      : val{ std::forward<T>(inVal) }
    {
    }

    //Copy and move constructors
    //Note: node can be moved only
    TreeNode(const TreeNode& inNode) = delete;
    TreeNode(TreeNode&& inNode)      = default;

    //Destructor
    ~TreeNode() = default;

  //--------------------------------
  //Operators 

  public:

    //Copy and move assignment operators
    //Note: node can be moved only
    TreeNode& operator= (const TreeNode& inNode) = delete;
    TreeNode& operator= (TreeNode&& inNode)      = default;
};

#endif
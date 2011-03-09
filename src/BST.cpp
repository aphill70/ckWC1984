#include "../inc/BST.h"
#include <iostream>
using namespace std;

//!  No-arg constructor.  Initializes an empty BST
BST::BST(): size(0), root(0)
{
  return;
}


//!  Copy constructor.  Makes a complete copy of its argument
BST::BST(const BST & other)
{
  root = ReCopy(other.root);
  size = other.size;
}


//!  Destructor
BST::~BST()
{
  Free(root);
}

void BST::Free(BSTNode * p)
{
  size = 0;
  if(p != NULL)
  {


    Free(p->left);
    Free(p->right);
    delete p;
    p = NULL;
  }
root = NULL;
}

BSTNode * BST::ReCopy(BSTNode * p)
{ 
  BSTNode * np;
  
  if(p == NULL)
    return NULL;
  else
  {
    np = new BSTNode(p->value);
    np->left = ReCopy(p->left);
    np->right = ReCopy(p->right);
    
    return np;    
  }
  
}


//!  Assignment operator.  Makes a complete copy of its argument
//!  @return Reference to oneself
BST& BST::operator =(const BST & other)
{
    if (this != &other) {
         Free(root);
         root = ReCopy(other.root);
	 size = other.size;
    }
    return *this;
}


//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
//!  @note This is useful for BST clients that need to traverse the tree.)
BSTNode * BST::GetRoot()const
{
  return root;
}


//!  @return true if the BST is empty, or false if the BST is not empty
bool BST::IsEmpty() const
{
  return (size == 0);
}


//!  Removes all values from the BST
void BST::Clear()
{
  Free(root);
}


//!  @return the number of values in the BST
int BST::GetSize() const
{
  return size;
}


//!  Inserts value v into the BST
//!
//!  @param v The new value being inserted
//!
//!  @return a pointer to the newly inserted node, or NULL if v was already
//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
BSTNode * BST::Insert(const std::string & v)
{
  
  BSTNode * newNode = new BSTNode(v);
  
  if(root == NULL)
    root = newNode;
  else if(v.compare(root->value) < 0)
    if(root->left == NULL)
      root->left = newNode;
    else
      return ReInsert(v, root->left, newNode);
  else if(v.compare(root->value) > 0)
    if(root->right == NULL)
      root->right = newNode;
    else
      return ReInsert(v, root->right, newNode);
  else
  {
    delete newNode;
    newNode = NULL;
    return NULL;
  }
  size++;
  return newNode;
}

BSTNode * BST::ReInsert(const std::string & v, BSTNode * p, BSTNode * nn)
{
  
  if(v.compare(p->value) < 0)
    if(p->left == NULL)
      p->left = nn;
    else
    return ReInsert(v, p->left, nn);
  else if(v.compare(p->value) > 0)
  {
    if(p->right == NULL)
      p->right = nn;
    else
      return ReInsert(v, p->right, nn);
  }
    else
    {
      delete nn;
      nn = NULL;
      return NULL;
    }
  size++;
  return nn;
}

//!  Searches the tree for value v
//!
//!  @param v The new value being searched for
//!
//!  @return a pointer to the node containing v, or NULL if v is not in the tree
BSTNode * BST::Find(const std::string & v) const
{
  BSTNode * p = root;
  
  while(p != NULL)
  {
    if(p->GetValue().compare(v) > 0)
      p = p->left;
    else if(p->GetValue().compare(v) < 0)
      p = p->right;
    else
      return p;
  }
  
  return NULL;
}


//! @NOTE: YOU ARE NOT REQUIRED TO IMPLEMENT THE Remove METHOD BELOW
//!        (BUT YOU CAN IF YOU WANT TO)
//!
//!  Removes value v from the tree
//!
//!  @param v The value being removed from the tree
//!
//!  @return true if v was removed from the tree, or false if v was not in the tree
//bool Remove(const std::string & v);

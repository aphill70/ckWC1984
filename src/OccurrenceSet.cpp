#include "OccurrenceSet.h"
using namespace std;

//!  No-arg constructor.  Initializes an empty OccurrenceSet
OccurrenceSet::OccurrenceSet(): size(0), root(0)
{
  return;
}


//!  Copy constructor.  Makes a complete copy of its argument
OccurrenceSet::OccurrenceSet(const OccurrenceSet & other)
{
  root = ReCopy(other.root);
  size = other.size;
}

//!  Destructor
OccurrenceSet::~OccurrenceSet()
{
  Free(root);
}

void OccurrenceSet::setValue(std::string word){
  value = word;
}

void OccurrenceSet::Free(OccurrenceNode * p)
{
  size = 0;
  if(p != NULL){
    Free(p->left);
    Free(p->right);
    delete p;
    p = NULL;
  }
root = NULL;
}

OccurrenceNode * OccurrenceSet::ReCopy(OccurrenceNode * p)
{ 
  OccurrenceNode * np;
  
  if(p == NULL)
    return NULL;
  else
  {
    np = new OccurrenceNode(p->value);
    np->left = ReCopy(p->left);
    np->right = ReCopy(p->right);
    
    return np;    
  }
  
}


//!  Assignment operator.  Makes a complete copy of its argument
//!  @return Reference to oneself
OccurrenceSet& OccurrenceSet::operator =(const OccurrenceSet & other)
{
    if (this != &other) {
         Free(root);
         root = ReCopy(other.root);
	 size = other.size;
    }
    return *this;
}


//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
//!  @note This is useful for OccurrenceSet clients that need to traverse the tree.)
OccurrenceNode * OccurrenceSet::GetRoot()const
{
  return root;
}


//!  @return true if the OccurrenceSet is empty, or false if the OccurrenceSet is not empty
bool OccurrenceSet::IsEmpty() const
{
  return (size == 0);
}


//!  Removes all values from the OccurrenceSet
void OccurrenceSet::Clear()
{
  Free(root);
}


//!  @return the number of values in the OccurrenceSet
int OccurrenceSet::GetSize() const
{
  return size;
}


//!  Inserts value v into the OccurrenceSet
//!
//!  @param v The new value being inserted
//!
//!  @return a pointer to the newly inserted node, or NULL if v was already
//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
OccurrenceNode * OccurrenceSet::Insert(const std::string & v)
{
  
  OccurrenceNode * newNode = new OccurrenceNode(v);
  
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
    root->count++;
    delete newNode;
    newNode = NULL;
    return NULL;
  }
  size++;
  return newNode;
}

OccurrenceNode * OccurrenceSet::ReInsert(const std::string & v, OccurrenceNode * p, OccurrenceNode * nn)
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
      p->count++;
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
OccurrenceNode * OccurrenceSet::Find(const std::string & v) const
{
  OccurrenceNode * p = root;
  
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

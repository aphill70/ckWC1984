#ifndef OCCURRENCESET_H
#define OCCURRENCESET_H

#include <string>
#include <iostream>


//!  OccurrenceNode implements a binary search tree node
class OccurrenceNode {

  friend class OccurrenceSet;   //!< OccurrenceSet can access private members of OccurrenceNode


public:

//!  Constructor
OccurrenceNode(const std::string & v) :
count(1), value(v), left(NULL), right(NULL) {
}

//! Copy Constructor
OccurrenceNode(const OccurrenceNode & other) : 
count(other.count), value(other.value),left(other.left),right(other.right){
}

const int & getCount(){
  return count;
}

//!  Read-only public methods for use by clients of the OccurrenceSet class
const std::string & GetValue() const{
  return value;
}

OccurrenceNode * GetLeft()const{
  return left;
}

OccurrenceNode * GetRight()const{
  return right;
}

//! Assignment operator 
OccurrenceNode & operator=(const OccurrenceNode & other){
  if(this!=&other){
    value=other.value;
    left=other.left;
    right=other.right;
  }
return *this;
}
	

private:
  int count;
  std::string value;  //!< value stored in the node

OccurrenceNode * left;     //!< pointer to the node's left child

OccurrenceNode * right;    //!< pointer to the node's right child
};

//!  OccurrenceSet implements a binary search tree
class OccurrenceSet {

public:

//!  No-arg constructor.  Initializes an empty OccurrenceSet
OccurrenceSet();

//!  Copy constructor.  MGetValue()akes a complete copy of its argument
OccurrenceSet(const OccurrenceSet & other);

//!  Destructor
~OccurrenceSet();

//!  Assignment operator.  Makes a complete copy of its argument
//!  @return Reference to oneself
OccurrenceSet& operator =(const OccurrenceSet & other);

//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
//!  @note This is useful for OccurrenceSet clients that need to traverse the tree.)
OccurrenceNode * GetRoot()const;

//!  @return true if the OccurrenceSet is empty, or false if the OccurrenceSet is not empty
bool IsEmpty() const;

//!  Removes all values from the OccurrenceSet
void Clear();

//!  @return the number of values in the OccurrenceSet
int GetSize() const;

//!  Inserts value v into the OccurrenceSet
//!  
//!  @param v The new value being inserted
//!
//!  @return a pointer to the newly inserted node, or NULL if v was already
//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
OccurrenceNode * Insert(const std::string & v);

//!  Searches the tree for value v
//!  
//!  @param v The new value being searched for
//!
//!  @return a pointer to the node containing v, or NULL if v is not in the tree
OccurrenceNode * Find(const std::string & v) const;

//! @NOTE: YOU ARE NOT REQUIRED TO IMPLEMENT THE Remove METHOD BELOW
//!        (BUT YOU CAN IF YOU WANT TO)
//!
//!  Removes value v from the tree
//!  
//!  @param v The value being removed from the tree
//!
//!  @return true if v was removed from the tree, or false if v was not in the tree
//bool Remove(const std::string & v);

void setValue(std::string word);

private:
  std::string value;
  int size;
  OccurrenceNode * root;

  
  OccurrenceNode * ReCopy(OccurrenceNode * p);
  OccurrenceNode * ReInsert(const std::string & v, OccurrenceNode * p, OccurrenceNode * nn);
  void Free(OccurrenceNode * p);
};


#endif

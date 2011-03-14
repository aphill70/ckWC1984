#include "KeyWordIndex.h"
#include <iostream>
using namespace std;

//!  No-arg constructor.  Initializes an empty KeyWordIndex
KeyWordIndex::KeyWordIndex(): size(0), root(0), iterator(NULL), iteratorsize(0){
  return;
}


//!  Copy constructor.  Makes a complete copy of its argument
KeyWordIndex::KeyWordIndex(const KeyWordIndex & other){
  root = ReCopy(other.root);
  size = other.size;
}


//!  Destructor
KeyWordIndex::~KeyWordIndex(){
  Free(root);
}

void KeyWordIndex::Free(KeyWordNode * p){
  size = 0;
  if(p != NULL){
    Free(p->left);
    Free(p->right);
    delete p;
    p = NULL;
  }
  root = NULL;
  delete [] iterator;
  iterator = NULL;
}

KeyWordNode * KeyWordIndex::ReCopy(KeyWordNode * p){ 
  KeyWordNode * np;
  
  if(p == NULL)
    return NULL;
  else{
    np = new KeyWordNode(p->value);
    np->left = ReCopy(p->left);
    np->right = ReCopy(p->right);
    
    return np;    
  }
  
}


//!  Assignment operator.  Makes a complete copy of its argument
//!  @return Reference to oneself
KeyWordIndex& KeyWordIndex::operator =(const KeyWordIndex & other){
    if (this != &other){
         Free(root);
         root = ReCopy(other.root);
	 size = other.size;
    }
    return *this;
}


//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
//!  @note This is useful for KeyWordIndex clients that need to traverse the tree.)
KeyWordNode * KeyWordIndex::GetRoot()const{
  return root;
}


//!  @return true if the KeyWordIndex is empty, or false if the KeyWordIndex is not empty
bool KeyWordIndex::IsEmpty() const{
  return (size == 0);
}


//!  Removes all values from the KeyWordIndex
void KeyWordIndex::Clear(){
  Free(root);
}


//!  @return the number of values in the KeyWordIndex
int KeyWordIndex::GetSize() const{
  return size;
}


//!  Inserts value v into the KeyWordIndex
//!
//!  @param v The new value being inserted
//!
//!  @return a pointer to the newly inserted node, or NULL if v was already
//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
KeyWordNode * KeyWordIndex::Insert(const std::string & v, const std::string & s){
  KeyWordNode * newNode = new KeyWordNode(v);
  
  if(root == NULL){
    root = newNode;
    root->set->Insert(s);
    
  }else if(v.compare(root->value) < 0)
    if(root->left == NULL){
      root->left = newNode;
      root->left->set->Insert(s);
    }else
      return ReInsert(v, root->left, newNode, s);
  else if(v.compare(root->value) > 0)
    if(root->right == NULL){
      root->right = newNode;
      root->right->set->Insert(s);
    }else
      return ReInsert(v, root->right, newNode, s);
  else{
    root->set->Insert(s);
    delete newNode;
    newNode = NULL;
    return NULL;
  }
  size++;
  return newNode;
}

KeyWordNode * KeyWordIndex::ReInsert(const std::string & v, 
				     KeyWordNode * p, 
				     KeyWordNode * nn, 
				     const std::string s){
  
  if(v.compare(p->value) < 0)
    if(p->left == NULL){
      p->left = nn;
      p->left->set->Insert(s);
    }else
    return ReInsert(v, p->left, nn, s);
  else if(v.compare(p->value) > 0){
    if(p->right == NULL){
      p->right = nn;
      p->right->set->Insert(s);
    }else
      return ReInsert(v, p->right, nn, s);
  }else{
      p->set->Insert(s);
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
KeyWordNode * KeyWordIndex::Find(const std::string & v) const{
  KeyWordNode * p = root;
  
  while(p != NULL){
    if(p->GetValue().compare(v) > 0)
      p = p->left;
    else if(p->GetValue().compare(v) < 0)
      p = p->right;
    else
      return p;
  }
  
  return NULL;
}

//!
//!
//!
//!
//!
//!
void KeyWordIndex::KeyWordIteratorInit(){
  iteratorsize = 0;
  iterator = new KeyWordNode*[size];
  
  if(root != NULL)
  TreeTraversal(root, iterator);
  
  iteratorsize = 0;
  
}

void KeyWordIndex::TreeTraversal(KeyWordNode * p, KeyWordNode * container[]){
  if(p->left != 0)
    TreeTraversal(p->left, container);
  
    container[iteratorsize++] = p;
  if(p->right != 0)
    TreeTraversal(p->right, container);
}

bool KeyWordIndex::KeyWordIteratorHasNext(){
  return (iteratorsize < size);
}

KeyWordNode * KeyWordIndex::KeyWordIteratorNext(){
  return iterator[iteratorsize++];
}
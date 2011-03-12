#include "PageHistory.h"
using namespace std;

//!  No-arg constructor.  Initializes an empty PageHistory
PageHistory::PageHistory(): size(0), root(0)
{
  return;
}


//!  Copy constructor.  Makes a complete copy of its argument
PageHistory::PageHistory(const PageHistory & other)
{
  root = ReCopy(other.root);
  size = other.size;
}


//!  Destructor
PageHistory::~PageHistory()
{
  Free(root);
}

void PageHistory::Free(PageHistoryNode * p)
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

PageHistoryNode * PageHistory::ReCopy(PageHistoryNode * p)
{ 
  PageHistoryNode * np;
  
  if(p == NULL)
    return NULL;
  else
  {
    np = new PageHistoryNode(p->value);
    np->left = ReCopy(p->left);
    np->right = ReCopy(p->right);
    
    return np;    
  }
  
}


//!  Assignment operator.  Makes a complete copy of its argument
//!  @return Reference to oneself
PageHistory& PageHistory::operator =(const PageHistory & other)
{
    if (this != &other) {
         Free(root);
         root = ReCopy(other.root);
	 size = other.size;
    }
    return *this;
}


//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
//!  @note This is useful for PageHistory clients that need to traverse the tree.)
PageHistoryNode * PageHistory::GetRoot()const
{
  return root;
}


//!  @return true if the PageHistory is empty, or false if the PageHistory is not empty
bool PageHistory::IsEmpty() const
{
  return (size == 0);
}


//!  Removes all values from the PageHistory
void PageHistory::Clear()
{
  Free(root);
}


//!  @return the number of values in the PageHistory
int PageHistory::GetSize() const
{
  return size;
}


//!  Inserts value v into the PageHistory
//!
//!  @param v The new value being inserted
//!
//!  @return a pointer to the newly inserted node, or NULL if v was already
//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
PageHistoryNode * PageHistory::Insert(Page * v)
{
  
  PageHistoryNode * newNode = new PageHistoryNode(v);
  
  if(root == NULL)
    root = newNode;
  else if(v->getUrl()->getShortUrl().compare(root->value->getUrl()->getShortUrl()) < 0)
    if(root->left == NULL)
      root->left = newNode;
    else
      return ReInsert(v, root->left, newNode);
  else if(v->getUrl()->getShortUrl().compare(root->value->getUrl()->getShortUrl()) > 0)	  	  
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

PageHistoryNode * PageHistory::ReInsert(Page* v, PageHistoryNode* p, PageHistoryNode* nn)
{
  
  if(v->getUrl()->getShortUrl().compare(p->value->getUrl()->getShortUrl()) < 0)
    if(p->left == NULL)
      p->left = nn;
    else
    return ReInsert(v, p->left, nn);
  else if(v->getUrl()->getShortUrl().compare(p->value->getUrl()->getShortUrl()) > 0)
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
PageHistoryNode * PageHistory::Find(Page * v) const
{
  PageHistoryNode * p = root;
  
  while(p != NULL)
  {
    if(p->GetValue()->getUrl()->getShortUrl().compare(v->getUrl()->getShortUrl()) > 0)
      p = p->left;
    else if(p->GetValue()->getUrl()->getShortUrl().compare(v->getUrl()->getShortUrl()) < 0)
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

void PageHistory::IteratorInit(){
  iteratorsize = 0;
  iterator = new Page*[size];
  
  if(root != NULL)
  TreeTraversal(root, iterator);
  
  iteratorsize = 0;
  
}

void PageHistory::TreeTraversal(PageHistoryNode* p, Page * container[]){
  if(p->left != 0)
    TreeTraversal(p->left, container);
  
    container[iteratorsize++] = p->value;
  if(p->right != 0)
    TreeTraversal(p->right, container);
}

bool PageHistory::HasNext(){
  return (iteratorsize < size);
}

Page * PageHistory::Next(){
  return iterator[iteratorsize++];
}

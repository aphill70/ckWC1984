#include "../inc/PageQueue.h"
#include <iostream>
using namespace std;

//!  No-arg constructor.  Initializes an empty linked list
PageQueue::PageQueue(): first(0), last(0), size(0)
{
  return;
}


//!  Copy constructor.  Makes a complete copy of its argument
PageQueue::PageQueue(const PageQueue & other)
{  
  Init(other);
}

void PageQueue::Init(const PageQueue & other)
{
  if(other.first == NULL) 
  {
    first = last = NULL;
    size = 0;
    return;
  }
  
  
  PageNode * CopyNode = other.first;
  
  PageNode * MyPrevNode = 0;
  PageNode * MyCopyNode;
  while(CopyNode != NULL)
  {
    
    if(MyPrevNode == 0)
    {
      MyCopyNode = new PageNode(CopyNode->GetValue(), CopyNode->prev, CopyNode->next);
      first = MyCopyNode;
    }
    
    if(MyCopyNode->next != NULL)
      MyCopyNode->next = new PageNode(MyCopyNode->next->value, MyCopyNode, MyCopyNode->next->next);
      
      MyPrevNode = MyCopyNode;
      
      MyCopyNode = MyCopyNode->next;
      if(MyCopyNode != NULL)
	MyCopyNode->prev = MyPrevNode;
      
      CopyNode = CopyNode->next;
  }
  last = MyPrevNode;
  size = other.size;
}

void PageQueue::Free() 
{
  PageNode * n = first;
  PageNode * t;
  
  while(n != 0)
  {
    if(n->next != 0)
      t = n->next;
    else
      t = 0;
    
    delete n;
    n = t;
  }
  
  first = 0;
  last = 0;
  size = 0;
  
}

//!  Destructor
PageQueue::~PageQueue(){
  Free();
}


//! Assignment operator.  Makes a complete copy of its argument
//! @return A reference to oneself
PageQueue& PageQueue::operator =(const PageQueue & other){
    if (this != &other) {
        Free();
        Init(other);
    }
    return *this;
}


//!  @return true if the list is empty, or false if the list is not empty
bool PageQueue::IsEmpty() const
{
  return (size == 0);
}

//!  Removes all values from the list
void PageQueue::Clear()
{
  Free();
}


//!  @return the number of values in the list
int PageQueue::GetSize() const
{
  return size;
}



//!  @return a pointer to the first node in the list, or NULL if the list is empty
PageNode * PageQueue::GetFirst()const
{
  return first;
}



//!  @returns a pointer to the last node in the list, or NULL if the list is empty
PageNode * PageQueue::GetLast()const
{
  return last;
}


//!  Inserts value v into the list after node n
//!
//!  @param v The new value being inserted
//!  @param n A node that is already in the list after which the new node should
//!      be inserted.
//!      If n is NULL, the new node should be inserted at the beginning of the list.
//!
//!  @return a pointer to the newly inserted node
PageNode * PageQueue::Insert(Page * v, PageNode * n)
{
  PageNode * p;
  
    if(first == NULL)
    {
	first = new PageNode(v, 0, 0);
	last = first;
	size++;
	return first;
    }else if(n == NULL)
    {
     p = first;
     
     first = new PageNode(v, 0, p);
     p->prev = first;
     size++;
     return first;
    }else if(n == last)
    {
      PageNode * nn = new PageNode(v, n, n->next);
      last->next = nn;
      last = nn;
      size++;
      return nn;
    }else
    {

    PageNode * nn = new PageNode(v, n, n->next);
   
    if(n->next != NULL)
      n->next->prev = nn;
    n->next = nn;
    
    size++;
    return nn;
    }
  
}


//! Searches for the first occurrence of value v that appears in the list
//!   after node n
//!
//!  @param v The value being searched for
//!  @param n The node in the list after which the search should begin.
//!      If n is NULL, the list should be searched from the beginning.
//!
//!  @return a pointer to the node containing v, or NULL if v is not found
PageNode * PageQueue::Find(Page * v, PageNode * n) const
{
    PageNode * currentNode;
    
    if(n == NULL)
      currentNode = first;
    else
      currentNode = n->next;
      
    while(currentNode != NULL)
    {
      if(v->getUrl()->getShortUrl() == n->GetValue()->getUrl()->getShortUrl())
	return currentNode;
      
      currentNode = currentNode->next;
    }
    return currentNode;    
}


//!  Removes node n from the list
//!
//!  @param n The node being removed from the list
void PageQueue::Remove(PageNode * n)
{
  PageNode * next;
  PageNode * prev;
  
  if(n == NULL)
    return;
  
  if(size == 1)
  {
    last = 0;
    first = 0;
  }else
  {
    if(n->next != NULL)
      next = n->next;
    else
    {
      next = 0;
      last = n->prev;
    }
    
    if(n->prev != NULL)
      prev = n->prev;
    else
    {
      prev = 0;
      first = n->next;
    }
    if(next != 0)
      next->prev = prev;
    if(prev != 0)
      prev->next = next;
    
  }
    
   delete n;
   n = NULL;
    size--;
}

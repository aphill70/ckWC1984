#ifndef CS240_PageHistory_H
#define CS240_PageHistory_H

#include <string>

#include "Page.h"

//!  PageHistoryNode implements a binary search tree node
class PageHistoryNode {
		friend class PageHistory;   //!< PageHistory can access private members of PageHistoryNode
	
	public:
	
		//!  Constructor
		PageHistoryNode(Page * v) :
		  value(v), left(NULL), right(NULL)
		{
		}
		
		//! Copy Constructor
		PageHistoryNode(const PageHistoryNode & other) : 
		  value(other.value),left(other.left),right(other.right)
		{
		}
		
		~PageHistoryNode(){
		  delete value; 
		  value = NULL;
		}
	
		//!  Read-only public methods for use by clients of the PageHistory class
		Page * GetValue() const
		{
		  return value;
		}
	
		
	
		PageHistoryNode * GetLeft()const
		{
		  return left;
		}
	
	
		PageHistoryNode * GetRight()const
		{
		  return right;
		}
		
		//! Assignment operator 
		PageHistoryNode & operator=(const PageHistoryNode & other)
		{
			if(this!=&other)
			{
				value=other.value;
				left=other.left;
				right=other.right;
			}
			
			return *this;
		}
	
	private:
		Page * value;  //!< value stored in the node
		PageHistoryNode * left;     //!< pointer to the node's left child
		PageHistoryNode * right;    //!< pointer to the node's right child
};


//!  PageHistory implements a binary search tree
class PageHistory {
	
	public:
	
		//!  No-arg constructor.  Initializes an empty PageHistory
		PageHistory();
	
	
		//!  Copy constructor.  MGetValue()akes a complete copy of its argument
		PageHistory(const PageHistory & other);
	
	
		//!  Destructor
		~PageHistory();
	
	
		//!  Assignment operator.  Makes a complete copy of its argument
		//!  @return Reference to oneself
		PageHistory& operator =(const PageHistory & other);
	
	
		//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
		//!  @note This is useful for PageHistory clients that need to traverse the tree.)
		PageHistoryNode * GetRoot()const;
	
	
		//!  @return true if the PageHistory is empty, or false if the PageHistory is not empty
		bool IsEmpty() const;
	
	
		//!  Removes all values from the PageHistory
		void Clear();
	
	
		//!  @return the number of values in the PageHistory
		int GetSize() const;
	
	
		//!  Inserts value v into the PageHistory
		//!  
		//!  @param v The new value being inserted
		//!
		//!  @return a pointer to the newly inserted node, or NULL if v was already
		//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
		PageHistoryNode * Insert(Page * v);
	
	
		//!  Searches the tree for value v
		//!  
		//!  @param v The new value being searched for
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not in the tree
		PageHistoryNode * Find(Page * v) const;
	
	
		//! @NOTE: YOU ARE NOT REQUIRED TO IMPLEMENT THE Remove METHOD BELOW
		//!        (BUT YOU CAN IF YOU WANT TO)
		//!
		//!  Removes value v from the tree
		//!  
		//!  @param v The value being removed from the tree
		//!
		//!  @return true if v was removed from the tree, or false if v was not in the tree
		//bool Remove(Page * v);
	
	private:
	  PageHistoryNode * ReInsert(Page * v, PageHistoryNode * p, PageHistoryNode * nn);
	  void Free(PageHistoryNode * p);
	  PageHistoryNode * ReCopy(PageHistoryNode * p);

	  int size;
	  PageHistoryNode * root;
};


#endif

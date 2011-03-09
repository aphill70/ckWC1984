#ifndef CS240_LINKED_LIST_H
#define CS240_LINKED_LIST_H

#include <string>

//! PageNode implements a doubly-linked list node
class PageNode {
		friend class PageQueue;  //!< PageQueue can access private members of PageNode
	public:
	
		//!  Constructor
		PageNode(const std::string & v, PageNode * p, PageNode * n) :
		  value(v), prev(p), next(n)
		{
		}
		
		//! Copy Constructor 
		PageNode(const PageNode & other) : 
		   value(other.value),prev(other.prev),next(other.next)
		{
		}
	
		//!  Read-only public methods for use by clients of the PageQueue class
		const std::string & GetValue() const
		{
		  return value;
		}
	
	
		PageNode * GetPrevious()const
		{
		  return prev;
		}
	
	
		PageNode * GetNext()const
		{
		  return next;
		}
		
		//! Assignment operator 
		PageNode & operator=(const PageNode & other)
		{
			if(this!=&other)
			{
				value=other.value;
				prev=other.prev;
				next=other.next;
			}
			return *this;
		}
	
	private:
		std::string value;        //!< value stored in the node
		PageNode * prev;            //!< pointer to previous node in the list
		PageNode * next;            //!< pointer to next node in the list
};


//! PageQueue implements a doubly-linked list
class PageQueue
{
	public:
	
		//!  No-arg constructor.  Initializes an empty linked list
		PageQueue();
	
	
		//!  Copy constructor.  Makes a complete copy of its argument
		PageQueue(const PageQueue & other);
	

		//!  Destructor
		~PageQueue();
	
	
		//! Assignment operator.  Makes a complete copy of its argument
		//! @return A reference to oneself
		PageQueue& operator =(const PageQueue & other);
	
	
		//!  @return true if the list is empty, or false if the list is not empty
		bool IsEmpty() const;
	
	
		//!  Removes all values from the list
		void Clear();
	
	
		//!  @return the number of values in the list
		int GetSize() const;
	
	
	
		//!  @return a pointer to the first node in the list, or NULL if the list is empty
		PageNode * GetFirst()const;
	
	
	
		//!  @returns a pointer to the last node in the list, or NULL if the list is empty
		PageNode * GetLast()const;
	
	
		//!  Inserts value v into the list after node n
		//!  
		//!  @param v The new value being inserted
		//!  @param n A node that is already in the list after which the new node should 
		//!      be inserted.
		//!      If n is NULL, the new node should be inserted at the beginning of the list.
		//!
		//!  @return a pointer to the newly inserted node
		PageNode * Insert(const std::string & v, PageNode * n);
	
	
		//! Searches for the first occurrence of value v that appears in the list 
		//!   after node n
		//!   
		//!  @param v The value being searched for
		//!  @param n The node in the list after which the search should begin.
		//!      If n is NULL, the list should be searched from the beginning.
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not found
		PageNode * Find(const std::string & v, PageNode * n) const;
	
	
		//!  Removes node n from the list
		//!  
		//!  @param n The node being removed from the list
		void Remove(PageNode * n);
	
	private:
	  PageNode * first; 
	  PageNode * last;
	  int size;

	  void Init(const PageQueue & other);
	  void Free();

  
};


#endif


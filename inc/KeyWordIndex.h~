#ifndef KEYWORDINDEX_H
#define KEYWORDINDEX_H

#include <string>

#include "OccurrenceSet.h"


//!  KeyWordNode implements a binary search tree node
class KeyWordNode {
		friend class KeyWordIndex;   //!< KeyWordIndex can access private members of KeyWordNode
	
	public:
		KeyWordNode(): value(""), left(NULL), right(NULL){
		  set = new OccurrenceSet();
		}
	
		//!  Constructor
		KeyWordNode(const std::string & v) :
		  value(v), left(NULL), right(NULL)
		{
		  set = new OccurrenceSet();
		}
		
		//! Copy Constructor
		KeyWordNode(const KeyWordNode & other) : 
		  value(other.value),left(other.left),right(other.right),set(other.set)
		{
		}
		
	
		//!  Read-only public methods for use by clients of the KeyWordIndex class
		const std::string & GetValue() const
		{
		  return value;
		}

		~KeyWordNode(){
		  delete set;
		}
	
		KeyWordNode * GetLeft()const
		{
		  return left;
		}
	
	
		KeyWordNode * GetRight()const
		{
		  return right;
		}
		
		OccurrenceSet * GetSet()const{
		  return set;
		}
		
		//! Assignment operator 
		KeyWordNode & operator=(const KeyWordNode & other)
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
		std::string value;  //!< value stored in the node
		KeyWordNode * left;     //!< pointer to the node's left child
		KeyWordNode * right;    //!< pointer to the node's right child
		OccurrenceSet * set;
};


//!  KeyWordIndex implements a binary search tree
class KeyWordIndex {
	
	public:
	
		//!  No-arg constructor.  Initializes an empty KeyWordIndex
		KeyWordIndex();
	
	
		//!  Copy constructor.  MGetValue()akes a complete copy of its argument
		KeyWordIndex(const KeyWordIndex & other);
	
	
		//!  Destructor
		~KeyWordIndex();
	
	
		//!  Assignment operator.  Makes a complete copy of its argument
		//!  @return Reference to oneself
		KeyWordIndex& operator =(const KeyWordIndex & other);
	
	
		//!  @return a pointer to the root node of the tree, or NULL if the tree is empty.
		//!  @note This is useful for KeyWordIndex clients that need to traverse the tree.)
		KeyWordNode * GetRoot()const;
	
	
		//!  @return true if the KeyWordIndex is empty, or false if the KeyWordIndex is not empty
		bool IsEmpty() const;
	
	
		//!  Removes all values from the KeyWordIndex
		void Clear();
	
	
		//!  @return the number of values in the KeyWordIndex
		int GetSize() const;
	
	
		//!  Inserts value v into the KeyWordIndex
		//!  
		//!  @param v The new value being inserted
		//!
		//!  @return a pointer to the newly inserted node, or NULL if v was already
		//!          in the tree (i.e., NULL is used to indicate a duplicate insertion)
		KeyWordNode * Insert(const std::string& v, const std::string& s);
	
	
		//!  Searches the tree for value v
		//!  
		//!  @param v The new value being searched for
		//!
		//!  @return a pointer to the node containing v, or NULL if v is not in the tree
		KeyWordNode * Find(const std::string & v) const;
	
	
		//! @NOTE: YOU ARE NOT REQUIRED TO IMPLEMENT THE Remove METHOD BELOW
		//!        (BUT YOU CAN IF YOU WANT TO)
		//!
		//!  Removes value v from the tree
		//!  
		//!  @param v The value being removed from the tree
		//!
		//!  @return true if v was removed from the tree, or false if v was not in the tree
		//bool Remove(const std::string & v);
		
		void KeyWordIteratorInit();
		
		bool KeyWordIteratorHasNext();
		
		KeyWordNode * KeyWordIteratorNext();
	
	private:
	  void TreeTraversal(KeyWordNode* p, KeyWordNode* container[]);
	  KeyWordNode * ReInsert(const std::string& v, KeyWordNode* p, KeyWordNode* nn, const std::string s);
	  void Free(KeyWordNode * p);
	  KeyWordNode * ReCopy(KeyWordNode * p);

	  int size;
	  KeyWordNode * root;
	  
	  KeyWordNode ** iterator;
	  int iteratorsize;
};


#endif



#include "LinkedList.h"  // Header file
#include "Node.h"
//#include "PrecondViolatedExcep.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
  
using namespace std;

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(NULL), itemCount(0)
{
}  // end default constructor

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList) : itemCount(aList.itemCount)
{
   Node<ItemType>* origChainPtr = aList.headPtr;  // Points to nodes in original chain

   if (origChainPtr == NULL)
      headPtr = NULL;  // Original list is empty
   else
   {
      // Copy first node
      headPtr = new Node<ItemType>();
      headPtr->setItem(origChainPtr->getItem());
      
      // Copy remaining nodes
      Node<ItemType>* newChainPtr = headPtr;      // Points to last node in new chain
      origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer
      while (origChainPtr != NULL)
      {
         // Get next item from original chain
         ItemType nextItem = origChainPtr->getItem();
         
         // Create a new node containing the next item 
         Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);  
         
         // Link new node to end of new chain
         newChainPtr->setNext(newNodePtr); 
         
         // Advance pointer to new last node      
         newChainPtr = newChainPtr->getNext();
         
         // Advance original-chain pointer
         origChainPtr = origChainPtr->getNext();
      }  // end while
      
      newChainPtr->setNext(NULL);              // Flag end of chain
   }  // end if
}  // end copy constructor

template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
   clear();
}  // end destructor

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
   return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
   return itemCount;
}  // end getLength

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
   bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
   if (ableToInsert)
   {
      Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);  
      if (newPosition == 1)
      {
         newNodePtr->setNext(headPtr); 
         headPtr = newNodePtr;
      }
      else
      {
         Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);
         newNodePtr->setNext(prevPtr->getNext()); 
         prevPtr->setNext(newNodePtr);
      }  // end if
      itemCount++; 
   }  // end if
   return ableToInsert;
}  // end inser

/*
template<class ItemType>
void LinkedList<ItemType>::remove(int position)
{
	   bool ableToNull = (position >= 1) && (position <= itemCount);
	   if (ableToNull)
	   {
		  Node<ItemType>* nodePtr = getNodeAt(position);
		  nodePtr->setItem(NULL);
	   }  // end if
	

}  // end remove
*/
template<class ItemType>
bool LinkedList<ItemType>::deletion(int position)
{
	   bool ableToRemove = (position >= 1) && (position <= itemCount);
	   if (ableToRemove)
	   {
		  Node<ItemType>* curPtr = NULL;
		  if (position == 1)
		  {
			 curPtr = headPtr; // Save pointer to node
			 headPtr = headPtr->getNext();
		  }
		  else
		  {
			 Node<ItemType>* prevPtr = getNodeAt(position - 1);
			 curPtr = prevPtr->getNext();
			 prevPtr->setNext(curPtr->getNext());
		  }  // end if
	  
		  curPtr->setNext(NULL);
		  delete curPtr;
		  curPtr = NULL;
		  itemCount--; 
	  
 // Decrease count of entries
   }  // end if
   
   return ableToRemove;
}  // end remove



template<class ItemType>
void LinkedList<ItemType>::clear()
{
   while (!isEmpty())
      remove(1);
}  // end clear



template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const//const throw(PrecondViolatedExcep)
{
   bool ableToGet = (position > 0) && (position <= itemCount);
   if (ableToGet)
   {
      Node<ItemType>* nodePtr = getNodeAt(position);
      return nodePtr->getItem();
   }
   else
   {
	   return ItemType();
	   //throw(PrecondViolatedExcep(message)); 
   }  // end if
}  // end getEntr
template<class ItemType>
void LinkedList<ItemType>::replace(int position, const ItemType& newEntry)// throw(PrecondViolatedExcep)
{
   bool ableToSet = (position >= 1) && (position <= itemCount);
   if (ableToSet)
   {
      Node<ItemType>* nodePtr = getNodeAt(position);
      nodePtr->setItem(newEntry);
   }
   else
   {
      string message = "replace() called with an invalid position.";
      //throw(PrecondViolatedExcep(message)); 
   }  // end if
}  // end replace

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const
{
   // Debugging check of precondition
   assert( (position >= 1) && (position <= itemCount) );
   
   // Count from the beginning of the chain
   Node<ItemType>* curPtr = headPtr;
   for (int skip = 1; skip < position; skip++)
      curPtr = curPtr->getNext();
      
   return curPtr;
}  // end getNodeAt
//  End of implementation file.

template<class ItemType>
int LinkedList<ItemType>::getItemCount() const
{
	return itemCount;
}

template<class ItemType>
ItemType LinkedList<ItemType>::displayList()
{
	for (int i = 0; i > itemCount; i++)
	{
		Node<ItemType>* nodePtr = getNodeAt(i);
		return nodePtr->getItem();
	}
}
template<class ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::operator = (const LinkedList<ItemType>& rhs) 
{
    LinkedList<ItemType> temp(rhs);
    swap(temp.headPtr, headPtr);
    return *this;
}

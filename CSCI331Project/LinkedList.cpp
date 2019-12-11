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

//! LinkedList default constructor
/*!
    Sets headptr to null and itemCount to 0.
*/
template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(NULL), itemCount(0)
{
}  // end default constructor

//! LinkedList constructor
/*!
    A copy constructor with one argumet passed, aList. 
    \param aLsit a refrence to a list
*/
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

//! LinkedList deconstructor
/*!
    A deconstructor to clear a LinkedList
*/
template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
   clear();
}  // end destructor

//! Memebr function to check if a LinkedList is empty
/*!
    Checks and returns a boolean value if the list is true or not
    \return itemCount == 0 returns 1 if the LinkedList is empty, 0 otherwise.
*/
template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
   return itemCount == 0;
}  // end isEmpty

//! Member function to get the length of the LinkedList
/*!
    \return itemCount the length (count of items)  of the LinkedList
*/
template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
   return itemCount;
}  // end getLength

//! Memebr function to insert a new item into a  Node of a LinkedList
/*!
    \param newPosition a node position to insert a item into
    \param newEntry a reference to an item of itemType to be inserted into 
           the Node.
    \return ableToInsert if newEntry can be inserted into the Node at newPosition
    \pre newPosition >= 1
    \pre newPosition <= itemCount + 1
*/
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

//! Member function for deletion of a Node
/*!
    \param position the position of te Node to be removed
    \return ableToRemove returns true if the Node is a valid Node.
    \pre To be a valid Node to remove, psition >= 1 and position <= itemCount
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

//! Memebr Fucntion to clear a LinkedList
/*!
    Removes 1 Node at a time while the LinkedList is not Empty
*/
template<class ItemType>
void LinkedList<ItemType>::clear()
{
   while (!isEmpty())
      deletion(1);
}  // end clear

//! Memebr function to get (return) an entry at a position
/*!
    \param position the position of a Node to return anItem
    \return nodePtr->getItem() an item at the position, position.
    \pre position > 0 and position <= itemCount
*/
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

//! Member function to replace an item at a position
/*!
    \param position the position of the Node whos item will be replaced
    \param newEntry the new entery to replace the old entry of a Node
*/
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


//! Locates a specified node in this linked list.
/*!
    \pre  position is the number of the desired node. position >= 1 and 
	  position <= itemCount.
    \post  The node is found and a pointer to it is returned.
    \param position  The number of the node to locate.
    \return  A pointer to the node at the given position.
*/
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

//! Member function to get the item count
/*! 
    /return itemCount the count of items in the LinkedList
*/
template<class ItemType>
int LinkedList<ItemType>::getItemCount() const
{
	return itemCount;
}

//! Member function to display the list
/*!
    Displays the list by returing one Node item at a time
    \return nodePtr->getItem() an item at a node
*/
template<class ItemType>
ItemType LinkedList<ItemType>::displayList()
{
	for (int i = 0; i > itemCount; i++)
	{
		Node<ItemType>* nodePtr = getNodeAt(i);
		return nodePtr->getItem();
	}
	return;
}

//! operator function =
/*!
    \param rhs referance to a LinkedList
    \return *this a pointer to the LinkedList
*/
template<class ItemType>
LinkedList<ItemType>& LinkedList<ItemType>::operator = (const LinkedList<ItemType>& rhs) 
{
    LinkedList<ItemType> temp(rhs);
    swap(temp.headPtr, headPtr);
    return *this;
}

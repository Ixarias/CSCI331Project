

#ifndef LINKED_LIST_
#define LINKED_LIST_

#include "ListInterface.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

template<class ItemType>
class LinkedList : public ListInterface<ItemType>
{
private:
   Node<ItemType>* headPtr; // Pointer to first node in the chain;
   // (contains the first entry in the list)
   int itemCount; // Current count of list items
   // Locates a specified node in this linked list.
   // @pre  position is the number of the desired node;
   //       position >= 1 and position <= itemCount.
   // @post  The node is found and a pointer to it is returned.
   // @param position  The number of the node to locate.
   // @return  A pointer to the node at the given position.
   Node<ItemType>* getNodeAt(int position) const;
   
public:
   LinkedList();
   LinkedList(const LinkedList<ItemType>& aList);
   virtual ~LinkedList();

   
   bool isEmpty() const;
   int getLength() const;
   bool insert(int newPosition, const ItemType& newEntry);
   //void remove(int position);
   bool deletion(int position);
   void clear();
   int getItemCount() const;
   LinkedList<ItemType>& operator = (const LinkedList<ItemType>& rhs);

   /** @throw PrecondViolatedExcep if position < 1 or 
                                      position > getLength(). */
   ItemType getEntry(int position) const; 

   /** @throw PrecondViolatedExcep if position < 1 or 
                                      position > getLength(). */
   void replace(int position, const ItemType &newEntry); 

   ItemType displayList();



}; // end LinkedList

//#include "LinkedList.cpp"
#endif 

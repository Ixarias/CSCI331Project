/***************************************************************************//**
* \class Node Node.h "Node.h"
* \brief This is Node class for linked list.
*
* This class is to create a node that is used in linked list class. The Node 
* will store a template ItemType, item and a Node pointer of item type, next.
*******************************************************************************/
#ifndef NODE_
#define NODE_

template<class ItemType>
class Node
{
private:
   ItemType        item; // A data item
   Node<ItemType>* next; // Pointer to next node
   
public:      
   Node();
   Node(const ItemType& anItem);
   Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
   void setItem(const ItemType& anItem);
   void setNext(Node<ItemType>* nextNodePtr);
   ItemType getItem() const ;
   Node<ItemType>* getNext() const ;
}; // end Node

//#include "Node.cpp"
#endif

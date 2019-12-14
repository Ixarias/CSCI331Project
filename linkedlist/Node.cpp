#include "Node.h"
using namespace std;

//! Node default constructor.
/*!
   Default constructor assiging next as NULLPTR
*/
template<class ItemType>
Node<ItemType>::Node() : next(nullptr)
{
} // end default constructor

//! Node constructor
/*!
    Taking one argument to assign to item and assigns next to null pointer.
    \param anItem a constant reference to an item of itemtype
*/
template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{
} // end constructor

//! Node constructor
/*!
    Taking two arguments. The first to assign to item and the other assigns next 
    to argument.
    \param anItem a constant reference to an item of itemtype
    \param nextNodePtr a pointer to the next node
*/
template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) :
	item(anItem), next(nextNodePtr)
{
} // end constructor

//! Member function taking one argument to set the memebr item
/*!
    \param anItem to be reference to by item
*/
template<class ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
	item = anItem;
} // end setItem

//! Member function taking one argument, a pointer to a Node.
/*!
    /param nextNodePtr a point to a Node, the next Node in a linked list
*/
template<class ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
	next = nextNodePtr;
} // end setNext

//! Member function returning an item.
/*!
    /return the item of itemType
*/
template<class ItemType>
ItemType Node<ItemType>::getItem() const
{
	return item;
} // end getItem

//! Memebr funtion to get the pointer to the next Node.
/*!
    /return a pointer to the next node.
*/
template<class ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
	return next;
} // end getNext

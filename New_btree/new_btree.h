/*****B+ Tree*****/
#ifndef _BPTree
#define _BPTree

using namespace std;
template <class T>
class BPTree
{
	private:
	class Node
	{
		bool IS_LEAF;
		T *key;
		int size;
		Node** ptr;
	public:
		Node();
	};
	Node *root;
	void insertInternal(T &x,Node<T>*,Node<T>*);
	void removeInternal(T &x,Node<T>*,Node<T>*);
	Node<T>* findParent(Node<T>*,Node<T>*);
public:
	BPTree();
    ~BPTree();
	void search(T x);
	void insert(T &x);
	void remove(T &x);
	void display(Node<T>*);
	Node<T>* getRoot();
	void cleanUp(Node<T>*);
};
#include "new_btree.cpp"
#endif
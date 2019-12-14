/*****B+ Tree*****/
#ifndef _BPTree
#define _BPTree

using namespace std;
template <class T>
class BPTree
{
    public:
	class Node
	{
		bool IS_LEAF;
		T *key;
		int size;
		Node** ptr;
		Node();
	};
	BPTree();
    ~BPTree();
	void search(T x);
	void insert(T &x);
	void remove(T &x);
	void display(Node*);
	Node* getRoot();
	void cleanUp(Node*);

	private:
	class Node *root;
	void insertInternal(T &x,Node*,Node*);
	void removeInternal(T &x,Node*,Node*);
	class Node* findParent(Node*,Node*);
};
#include "new_btree.cpp"
#endif
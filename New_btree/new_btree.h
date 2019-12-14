/*****B+ Tree*****/
#ifndef _BPTree
#define _BPTree

class BPTree;

using namespace std;

    template <class T>
	class Node
	{
		bool IS_LEAF;
		T *key;
		int size;
		Node** ptr;
        friend class BPTree;

        public:
		    Node();
	};

template <class T>
class BPTree
{
    public:
	BPTree();
    ~BPTree();
	void search(T x);
	void insert(T &x);
	void remove(T &x);
	void display(Node*);
	Node* getRoot();
	void cleanUp(Node*);

	private:
	Node *root;
	void insertInternal(T &x,Node*,Node*);
	void removeInternal(T &x,Node*,Node*);
	Node* findParent(Node*,Node*);
};
#include "new_btree.cpp"
#endif
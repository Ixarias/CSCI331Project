/*****B+ Tree*****/
#include "new_btree.cpp"
using namespace std;
class BPTree
{
	private:
	class Node
	{
		bool IS_LEAF;
		int *key, size;
		Node** ptr;
		friend class BPTree;
	public:
		Node();
	};
	Node *root;
	void insertInternal(int,Node*,Node*);
	void removeInternal(int,Node*,Node*);
	Node* findParent(Node*,Node*);
public:
	BPTree();
	void search(int);
	void insert(int);
	void remove(int);
	void display(Node*);
	Node* getRoot();
	void cleanUp(Node*);
	~BPTree();
};
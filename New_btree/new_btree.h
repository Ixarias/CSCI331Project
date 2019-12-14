/*****B+ Tree*****/
#include "new_btree.cpp"
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
		Node* ptr;
		friend class BPTree;
	public:
		Node();
	};
	Node *root;
	void insertInternal(T,Node*,Node*);
	void removeInternal(T,Node*,Node*);
	Node* findParent(Node*,Node*);
public:
	BPTree();
	void search(T);
	void insert(T);
	void remove(T);
	void display(Node*);
	Node* getRoot();
	void cleanUp(Node*);
	~BPTree();
};
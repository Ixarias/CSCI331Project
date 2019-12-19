#include <vector>
#include <string>

//#include "btreeSSstring.h"

NodeS::NodeS()
{
	//dynamic memory allocation
	key = new SecKeySS<int>[MAX];
	ptr = new NodeS * [MAX + 1];
}
BPTreeS::BPTreeS()
{
	root = NULL;
}
void BPTreeS::addDataToKey(string s, int rrn)
{
	vector<int> dup = search(s);
	SecKeySS<string> = sk;
	sk.setData(s);
	if (!(dup.empty()))(
		remove(sk);
	)
	dup.push_back(rrn);
	sk.setDuplicates(dup);
	insert(sk);

}
vector<int> BPTreeS::search(SecKeySS<string> x)
{
	//search logic
	vector<int> results;
	if (root == NULL)
	{
		return results;
	}
	else
	{
		NodeS* cursor = root;
		//in the following while loop, cursor will travel to the leaf NodeS possibly consisting the key
		while (cursor->IS_LEAF == false)
		{
			for (int i = 0; i < cursor->size; i++)
			{
				if (x < cursor->key[i])
				{
					cursor = cursor->ptr[i];
					break;
				}
				if (i == cursor->size - 1)
				{
					cursor = cursor->ptr[i + 1];
					break;
				}
			}
		}
		//in the following for loop, we search for the key if it exists
		for (int i = 0; i < cursor->size; i++)
		{
			if (cursor->key[i] == x)
			{
				return cursor->key[i].getDuplicates();
			}
		}
		return results;
	}
}

vector<int> BPTreeS::search(string x)
{
	//search logic
	vector<int> results;
	if (root == NULL)
	{
		return results;
	}
	else
	{
		NodeS* cursor = root;
		//in the following while loop, cursor will travel to the leaf NodeS possibly consisting the key
		while (cursor->IS_LEAF == false)
		{
			for (int i = 0; i < cursor->size; i++)
			{
				if (x < cursor->key[i])
				{
					cursor = cursor->ptr[i];
					break;
				}
				if (i == cursor->size - 1)
				{
					cursor = cursor->ptr[i + 1];
					break;
				}
			}
		}
		//in the following for loop, we search for the key if it exists
		for (int i = 0; i < cursor->size; i++)
		{
			if (cursor->key[i] == x)
			{
				return cursor->key[i].getDuplicates();
			}
		}
		return results;
	}
}
void BPTreeS::insert(SecKeySS<string> x)
{
	//insert logic
	if (root == NULL)
	{
		root = new NodeS;
		root->key[0] = x;
		root->IS_LEAF = true;
		root->size = 1;
		cout << "Created root\nInserted " << x << " successfully\n";
	}
	else
	{
		NodeS* cursor = root;
		NodeS* parent;
		//in the following while loop, cursor will will travel to the leaf NodeS possibly consisting the key
		while (cursor->IS_LEAF == false)
		{
			parent = cursor;
			for (int i = 0; i < cursor->size; i++)
			{
				if (x < cursor->key[i])
				{
					cursor = cursor->ptr[i];
					break;
				}
				if (i == cursor->size - 1)
				{
					cursor = cursor->ptr[i + 1];
					break;
				}
			}
		}
		//now cursor is the leaf NodeS in which we'll insert the new key
		if (cursor->size < MAX)
		{
			//if cursor is not full
			//find the correct position for new key
			int i = 0;
			while (x > cursor->key[i] && i < cursor->size) i++;
			//make space for new key
			for (int j = cursor->size; j > i; j--)
			{
				cursor->key[j] = cursor->key[j - 1];
			}
			cursor->key[i] = x;
			cursor->size++;
			cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
			cursor->ptr[cursor->size - 1] = NULL;
			cout << "Inserted " << x << " successfully\n";
		}
		else
		{
			cout << "Inserted " << x << " successfully\n";
			cout << "Overflow in leaf NodeS!\nSplitting leaf NodeS\n";
			//overflow condition
			//create new leaf NodeS
			NodeS* newLeaf = new NodeS;
			//create a virtual NodeS and insert x into it
			SecKeySS<string> virtualNodeS[MAX + 1];
			for (int i = 0; i < MAX; i++)
			{
				virtualNodeS[i] = cursor->key[i];
			}
			int i = 0, j;
			while (x > virtualNodeS[i] && i < MAX) i++;
			//make space for new key
			for (int j = MAX + 1; j > i; j--)
			{
				virtualNodeS[j] = virtualNodeS[j - 1];
			}
			virtualNodeS[i] = x;
			newLeaf->IS_LEAF = true;
			//split the cursor into two leaf NodeSs
			cursor->size = (MAX + 1) / 2;
			newLeaf->size = MAX + 1 - (MAX + 1) / 2;
			//make cursor point to new leaf NodeS
			cursor->ptr[cursor->size] = newLeaf;
			//make new leaf NodeS point to the next leaf NodeS
			newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
			cursor->ptr[MAX] = NULL;
			//now give elements to new leaf NodeSs
			for (i = 0; i < cursor->size; i++)
			{
				cursor->key[i] = virtualNodeS[i];
			}
			for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++)
			{
				newLeaf->key[i] = virtualNodeS[j];
			}
			//modify the parent
			if (cursor == root)
			{
				//if cursor is a root NodeS, we create a new root
				NodeS* newRoot = new NodeS;
				newRoot->key[0] = newLeaf->key[0];
				newRoot->ptr[0] = cursor;
				newRoot->ptr[1] = newLeaf;
				newRoot->IS_LEAF = false;
				newRoot->size = 1;
				root = newRoot;
				cout << "Created new root\n";
			}
			else
			{
				//insert new key in parent NodeS
				insertInternal(newLeaf->key[0], parent, newLeaf);
			}
		}
	}
}
void BPTreeS::insertInternal(SecKeySS<string> x, NodeS* cursor, NodeS* child)
{
	if (cursor->size < MAX)
	{
		//if cursor is not full
		//find the correct position for new key
		int i = 0;
		while (x > cursor->key[i] && i < cursor->size) i++;
		//make space for new key
		for (int j = cursor->size; j > i; j--)
		{
			cursor->key[j] = cursor->key[j - 1];
		}//make space for new pointer
		for (int j = cursor->size + 1; j > i + 1; j--)
		{
			cursor->ptr[j] = cursor->ptr[j - 1];
		}
		cursor->key[i] = x;
		cursor->size++;
		cursor->ptr[i + 1] = child;
		cout << "Inserted key in an Internal NodeS successfully\n";
	}
	else
	{
		cout << "Inserted key in an Internal NodeS successfully\n";
		cout << "Overflow in internal NodeS!\nSplitting internal NodeS\n";
		//if overflow in internal NodeS
		//create new internal NodeS
		NodeS* newInternal = new NodeS;
		//create virtual Internal NodeS;
		SecKeySS<string> virtualKey[MAX + 1];
		NodeS* virtualPtr[MAX + 2];
		for (int i = 0; i < MAX; i++)
		{
			virtualKey[i] = cursor->key[i];
		}
		for (int i = 0; i < MAX + 1; i++)
		{
			virtualPtr[i] = cursor->ptr[i];
		}
		int i = 0, j;
		while (x > virtualKey[i] && i < MAX) i++;
		//make space for new key
		for (j = MAX + 1; j > i; j--)
		{
			virtualKey[j] = virtualKey[j - 1];
		}
		virtualKey[i] = x;
		//make space for new ptr
		for (j = MAX + 2; j > i + 1; j--)
		{
			virtualPtr[j] = virtualPtr[j - 1];
		}
		virtualPtr[i + 1] = child;
		newInternal->IS_LEAF = false;
		//split cursor into two NodeSs
		cursor->size = (MAX + 1) / 2;
		newInternal->size = MAX - (MAX + 1) / 2;
		//give elements and pointers to the new NodeS
		for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++)
		{
			newInternal->key[i] = virtualKey[j];
		}
		for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++)
		{
			newInternal->ptr[i] = virtualPtr[j];
		}
		// m = cursor->key[cursor->size]
		if (cursor == root)
		{
			//if cursor is a root NodeS, we create a new root
			NodeS* newRoot = new NodeS;
			newRoot->key[0] = cursor->key[cursor->size];
			newRoot->ptr[0] = cursor;
			newRoot->ptr[1] = newInternal;
			newRoot->IS_LEAF = false;
			newRoot->size = 1;
			root = newRoot;
			cout << "Created new root\n";
		}
		else
		{
			//recursion
			//find depth first search to find parent of cursor
			insertInternal(cursor->key[cursor->size], findParent(root, cursor), cursor);
		}
	}
}
NodeS* BPTreeS::findParent(NodeS* cursor, NodeS* child)
{
	//finds parent using depth first traversal and ignores leaf NodeSs as they cannot be parents
	//also ignores second last level because we will never find parent of a leaf NodeS during insertion using this function
	NodeS* parent;
	if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF)
	{
		return NULL;
	}
	for (int i = 0; i < cursor->size + 1; i++)
	{
		if (cursor->ptr[i] == child)
		{
			parent = cursor;
			return parent;
		}
		else
		{
			parent = findParent(cursor->ptr[i], child);
		}
	}
	return parent;
}
void BPTreeS::remove(SecKeySS<string> x)
{
	//delete logic
	if (root == NULL)
	{
		cout << "Tree empty\n";
	}
	else
	{
		NodeS* cursor = root;
		NodeS* parent;
		int leftSibling, rightSibling;
		//in the following while loop, cursor will will travel to the leaf NodeS possibly consisting the key
		while (cursor->IS_LEAF == false)
		{
			for (int i = 0; i < cursor->size; i++)
			{
				parent = cursor;
				leftSibling = i - 1; //leftSibling is the index of left sibling in the parent NodeS
				rightSibling = i + 1; //rightSibling is the index of right sibling in the parent NodeS
				if (x < cursor->key[i])
				{
					cursor = cursor->ptr[i];
					break;
				}
				if (i == cursor->size - 1)
				{
					leftSibling = i;
					rightSibling = i + 2;
					cursor = cursor->ptr[i + 1];
					break;
				}
			}
		}
		//in the following for loop, we search for the key if it exists
		bool found = false;
		int pos;
		for (pos = 0; pos < cursor->size; pos++)
		{
			if (cursor->key[pos] == x)
			{
				found = true;
				break;
			}
		}
		if (!found)//if key does not exist in that leaf NodeS
		{
			cout << "Not found\n";
			return;
		}
		//deleting the key
		for (int i = pos; i < cursor->size; i++)
		{
			cursor->key[i] = cursor->key[i + 1];
		}
		cursor->size--;
		if (cursor == root)//if it is root NodeS, then make all pointers NULL
		{
			cout << "Deleted " << x << " from leaf NodeS successfully\n";
			for (int i = 0; i < MAX + 1; i++)
			{
				cursor->ptr[i] = NULL;
			}
			if (cursor->size == 0)//if all keys are deleted
			{
				cout << "Tree died\n";
				delete[] cursor->key;
				delete[] cursor->ptr;
				delete cursor;
				root = NULL;
			}
			return;
		}
		cursor->ptr[cursor->size] = cursor->ptr[cursor->size + 1];
		cursor->ptr[cursor->size + 1] = NULL;
		cout << "Deleted " << x << " from leaf NodeS successfully\n";
		if (cursor->size >= (MAX + 1) / 2)//no underflow
		{
			return;
		}
		cout << "Underflow in leaf NodeS!\n";
		//underflow condition
		//first we try to transfer a key from sibling NodeS
		//check if left sibling exists
		if (leftSibling >= 0)
		{
			NodeS* leftNodeS = parent->ptr[leftSibling];
			//check if it is possible to transfer
			if (leftNodeS->size >= (MAX + 1) / 2 + 1)
			{
				//make space for transfer
				for (int i = cursor->size; i > 0; i--)
				{
					cursor->key[i] = cursor->key[i - 1];
				}
				//shift pointer to next leaf
				cursor->size++;
				cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
				cursor->ptr[cursor->size - 1] = NULL;
				//transfer
				cursor->key[0] = leftNodeS->key[leftNodeS->size - 1];
				//shift pointer of leftsibling
				leftNodeS->size--;
				leftNodeS->ptr[leftNodeS->size] = cursor;
				leftNodeS->ptr[leftNodeS->size + 1] = NULL;
				//update parent
				parent->key[leftSibling] = cursor->key[0];
				cout << "Transferred " << cursor->key[0] << " from left sibling of leaf NodeS\n";
				return;
			}
		}
		if (rightSibling <= parent->size)//chech if right sibling exist
		{
			NodeS* rightNodeS = parent->ptr[rightSibling];
			//check if it is possible to transfer
			if (rightNodeS->size >= (MAX + 1) / 2 + 1)
			{
				//shift pointer to next leaf
				cursor->size++;
				cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
				cursor->ptr[cursor->size - 1] = NULL;
				//transfer
				cursor->key[cursor->size - 1] = rightNodeS->key[0];
				//shift pointer of rightsibling
				rightNodeS->size--;
				rightNodeS->ptr[rightNodeS->size] = rightNodeS->ptr[rightNodeS->size + 1];
				rightNodeS->ptr[rightNodeS->size + 1] = NULL;
				//shift conent of right sibling
				for (int i = 0; i < rightNodeS->size; i++)
				{
					rightNodeS->key[i] = rightNodeS->key[i + 1];
				}
				//update parent
				parent->key[rightSibling - 1] = rightNodeS->key[0];
				cout << "Transferred " << cursor->key[cursor->size - 1] << " from right sibling of leaf NodeS\n";
				return;
			}
		}
		//must merge and delete a NodeS
		if (leftSibling >= 0)//if left sibling exist
		{
			NodeS* leftNodeS = parent->ptr[leftSibling];
			// transfer all keys to leftsibling and then transfer pointer to next leaf NodeS
			for (int i = leftNodeS->size, j = 0; j < cursor->size; i++, j++)
			{
				leftNodeS->key[i] = cursor->key[j];
			}
			leftNodeS->ptr[leftNodeS->size] = NULL;
			leftNodeS->size += cursor->size;
			leftNodeS->ptr[leftNodeS->size] = cursor->ptr[cursor->size];
			cout << "Merging two leaf NodeSs\n";
			removeInternal(parent->key[leftSibling], parent, cursor);// delete parent NodeS key
			delete[] cursor->key;
			delete[] cursor->ptr;
			delete cursor;
		}
		else if (rightSibling <= parent->size)//if right sibling exist
		{
			NodeS* rightNodeS = parent->ptr[rightSibling];
			// transfer all keys to cursor and then transfer pointer to next leaf NodeS
			for (int i = cursor->size, j = 0; j < rightNodeS->size; i++, j++)
			{
				cursor->key[i] = rightNodeS->key[j];
			}
			cursor->ptr[cursor->size] = NULL;
			cursor->size += rightNodeS->size;
			cursor->ptr[cursor->size] = rightNodeS->ptr[rightNodeS->size];
			cout << "Merging two leaf NodeSs\n";
			removeInternal(parent->key[leftSibling + 1], parent, rightNodeS);// delete parent NodeS key
			delete[] rightNodeS->key;
			delete[] rightNodeS->ptr;
			delete rightNodeS;
		}
	}
}
void BPTreeS::removeInternal(SecKeySS<string> x, NodeS* cursor, NodeS* child)
{
	//deleting the key x first
	//checking if key from root is to be deleted
	if (cursor == root)
	{
		if (cursor->size == 1)//if only one key is left, change root
		{
			if (cursor->ptr[1] == child)
			{
				delete[] child->key;
				delete[] child->ptr;
				delete child;
				root = cursor->ptr[0];
				delete[] cursor->key;
				delete[] cursor->ptr;
				delete cursor;
				cout << "Changed root NodeS\n";
				return;
			}
			else if (cursor->ptr[0] == child)
			{
				delete[] child->key;
				delete[] child->ptr;
				delete child;
				root = cursor->ptr[1];
				delete[] cursor->key;
				delete[] cursor->ptr;
				delete cursor;
				cout << "Changed root NodeS\n";
				return;
			}
		}
	}
	int pos;
	for (pos = 0; pos < cursor->size; pos++)
	{
		if (cursor->key[pos] == x)
		{
			break;
		}
	}
	for (int i = pos; i < cursor->size; i++)
	{
		cursor->key[i] = cursor->key[i + 1];
	}
	//now deleting the pointer child
	for (pos = 0; pos < cursor->size + 1; pos++)
	{
		if (cursor->ptr[pos] == child)
		{
			break;
		}
	}
	for (int i = pos; i < cursor->size + 1; i++)
	{
		cursor->ptr[i] = cursor->ptr[i + 1];
	}
	cursor->size--;
	if (cursor->size >= (MAX + 1) / 2 - 1)//no underflow
	{
		cout << "Deleted " << x << " from internal NodeS successfully\n";
		return;
	}
	cout << "Underflow in internal NodeS!\n";
	//underflow, try to transfer first
	NodeS* parent = findParent(root, cursor);
	int leftSibling, rightSibling;
	//finding left n right sibling of cursor
	for (pos = 0; pos < parent->size + 1; pos++)
	{
		if (parent->ptr[pos] == cursor)
		{
			leftSibling = pos - 1;
			rightSibling = pos + 1;
			break;
		}
	}
	//try to transfer
	if (leftSibling >= 0)//if left sibling exists
	{
		NodeS* leftNodeS = parent->ptr[leftSibling];
		//check if it is possible to transfer
		if (leftNodeS->size >= (MAX + 1) / 2)
		{
			//make space for transfer of key
			for (int i = cursor->size; i > 0; i--)
			{
				cursor->key[i] = cursor->key[i - 1];
			}
			//transfer key from left sibling through parent
			cursor->key[0] = parent->key[leftSibling];
			parent->key[leftSibling] = leftNodeS->key[leftNodeS->size - 1];
			//transfer last pointer from leftNodeS to cursor
			//make space for transfer of ptr
			for (int i = cursor->size + 1; i > 0; i--)
			{
				cursor->ptr[i] = cursor->ptr[i - 1];
			}
			//transfer ptr
			cursor->ptr[0] = leftNodeS->ptr[leftNodeS->size];
			cursor->size++;
			leftNodeS->size--;
			cout << "Transferred " << cursor->key[0] << " from left sibling of internal NodeS\n";
			return;
		}
	}
	if (rightSibling <= parent->size)//check if right sibling exist
	{
		NodeS* rightNodeS = parent->ptr[rightSibling];
		//check if it is possible to transfer
		if (rightNodeS->size >= (MAX + 1) / 2)
		{
			//transfer key from right sibling through parent
			cursor->key[cursor->size] = parent->key[pos];
			parent->key[pos] = rightNodeS->key[0];
			for (int i = 0; i < rightNodeS->size - 1; i++)
			{
				rightNodeS->key[i] = rightNodeS->key[i + 1];
			}
			//transfer first pointer from rightNodeS to cursor
			//transfer ptr
			cursor->ptr[cursor->size + 1] = rightNodeS->ptr[0];
			for (int i = 0; i < rightNodeS->size; ++i)
			{
				rightNodeS->ptr[i] = rightNodeS->ptr[i + 1];
			}
			cursor->size++;
			rightNodeS->size--;
			cout << "Transferred " << cursor->key[0] << " from right sibling of internal NodeS\n";
			return;
		}
	}
	//transfer wasnt posssible hence do merging
	if (leftSibling >= 0)
	{
		//leftNodeS + parent key + cursor
		NodeS* leftNodeS = parent->ptr[leftSibling];
		leftNodeS->key[leftNodeS->size] = parent->key[leftSibling];
		for (int i = leftNodeS->size + 1, j = 0; j < cursor->size; j++)
		{
			leftNodeS->key[i] = cursor->key[j];
		}
		for (int i = leftNodeS->size + 1, j = 0; j < cursor->size; j++)
		{
			leftNodeS->ptr[i] = cursor->ptr[j];
			cursor->ptr[j] = NULL;
		}
		leftNodeS->size += cursor->size + 1;
		cursor->size = 0;
		//delete cursor
		removeInternal(parent->key[leftSibling], parent, cursor);
		cout << "Merged with left sibling\n";

	}
	else if (rightSibling <= parent->size)
	{
		//cursor + parent key + rightNodeS
		NodeS* rightNodeS = parent->ptr[rightSibling];
		cursor->key[cursor->size] = parent->key[leftSibling];
		for (int i = cursor->size + 1, j = 0; j < rightNodeS->size; j++)
		{
			cursor->key[i] = rightNodeS->key[j];
		}
		for (int i = cursor->size + 1, j = 0; j < rightNodeS->size; j++)
		{
			cursor->ptr[i] = rightNodeS->ptr[j];
			rightNodeS->ptr[j] = NULL;
		}
		cursor->size += rightNodeS->size + 1;
		rightNodeS->size = 0;
		//delete cursor
		removeInternal(parent->key[leftSibling], parent, rightNodeS);
		cout << "Merged with right sibling\n";
	}
}
void BPTreeS::display(NodeS* cursor)
{
	//depth first display
	if (cursor != NULL)
	{
		for (int i = 0; i < cursor->size; i++)
		{
			cout << cursor->key[i] << " ";
		}
		cout << "\n";
		if (cursor->IS_LEAF != true)
		{
			for (int i = 0; i < cursor->size + 1; i++)
			{
				display(cursor->ptr[i]);
			}
		}
	}
}
NodeS* BPTreeS::getRoot()
{
	return root;
}
void BPTreeS::cleanUp(NodeS* cursor)
{
	//clean up logic
	if (cursor != NULL)
	{
		if (cursor->IS_LEAF != true)
		{
			for (int i = 0; i < cursor->size + 1; i++)
			{
				cleanUp(cursor->ptr[i]);
			}
		}
		for (int i = 0; i < cursor->size; i++)
		{
			cout << "Deleted key from memory: " << cursor->key[i] << "\n";
		}
		delete[] cursor->key;
		delete[] cursor->ptr;
		delete cursor;
	}
}
BPTreeS::~BPTreeS()
{
	//calling cleanUp routine
	cleanUp(root);
}
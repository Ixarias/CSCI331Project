#include <vector>


//#include "btreeSSint.h"

NodeI::NodeI()
{
	//dynamic memory allocation
	key = new SecKeySS<int>[MAX];
	ptr = new NodeI * [MAX + 1];
}
BPTreeI::BPTreeI()
{
	root = NULL;
}

void BPTreeI::addDataToKey(int s, int rrn) {
	vector<int> dup = search(s);
	SecKeySS<int> = sk;
	sk.setData(s);
	if (!(dup.empty()))(
		remove(sk);
	)
	dup.push_back(rrn);
	sk.setDuplicates(dup);
	insert(sk);
}

vector<int> BPTreeI::search(SecKeySS<int> x)
{
	//search logic
	vector<int> results;
	if (root == NULL)
	{
		return results;
	}
	else
	{
		NodeI* cursor = root;
		//in the following while loop, cursor will travel to the leaf NodeI possibly consisting the key
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
vector<int> BPTreeI::search(int x)
{
	//search logic
	vector<int> results;
	if (root == NULL)
	{
		return results;
	}
	else
	{
		NodeI* cursor = root;
		//in the following while loop, cursor will travel to the leaf NodeI possibly consisting the key
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
void BPTreeI::insert(SecKeySS<int> x)
{
	//insert logic
	if (root == NULL)
	{
		root = new NodeI;
		root->key[0] = x;
		root->IS_LEAF = true;
		root->size = 1;
		cout << "Created root\nInserted " << x << " successfully\n";
	}
	else
	{
		NodeI* cursor = root;
		NodeI* parent;
		//in the following while loop, cursor will will travel to the leaf NodeI possibly consisting the key
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
		//now cursor is the leaf NodeI in which we'll insert the new key
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
			cout << "Overflow in leaf NodeI!\nSplitting leaf NodeI\n";
			//overflow condition
			//create new leaf NodeI
			NodeI* newLeaf = new NodeI;
			//create a virtual NodeI and insert x into it
			SecKeySS<int> virtualNodeI[MAX + 1];
			for (int i = 0; i < MAX; i++)
			{
				virtualNodeI[i] = cursor->key[i];
			}
			int i = 0, j;
			while (x > virtualNodeI[i] && i < MAX) i++;
			//make space for new key
			for (int j = MAX + 1; j > i; j--)
			{
				virtualNodeI[j] = virtualNodeI[j - 1];
			}
			virtualNodeI[i] = x;
			newLeaf->IS_LEAF = true;
			//split the cursor into two leaf NodeIs
			cursor->size = (MAX + 1) / 2;
			newLeaf->size = MAX + 1 - (MAX + 1) / 2;
			//make cursor point to new leaf NodeI
			cursor->ptr[cursor->size] = newLeaf;
			//make new leaf NodeI point to the next leaf NodeI
			newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
			cursor->ptr[MAX] = NULL;
			//now give elements to new leaf NodeIs
			for (i = 0; i < cursor->size; i++)
			{
				cursor->key[i] = virtualNodeI[i];
			}
			for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++)
			{
				newLeaf->key[i] = virtualNodeI[j];
			}
			//modify the parent
			if (cursor == root)
			{
				//if cursor is a root NodeI, we create a new root
				NodeI* newRoot = new NodeI;
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
				//insert new key in parent NodeI
				insertInternal(newLeaf->key[0], parent, newLeaf);
			}
		}
	}
}
void BPTreeI::insertInternal(SecKeySS<int> x, NodeI* cursor, NodeI* child)
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
		cout << "Inserted key in an Internal NodeI successfully\n";
	}
	else
	{
		cout << "Inserted key in an Internal NodeI successfully\n";
		cout << "Overflow in internal NodeI!\nSplitting internal NodeI\n";
		//if overflow in internal NodeI
		//create new internal NodeI
		NodeI* newInternal = new NodeI;
		//create virtual Internal NodeI;
		SecKeySS<int> virtualKey[MAX + 1];
		NodeI* virtualPtr[MAX + 2];
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
		//split cursor into two NodeIs
		cursor->size = (MAX + 1) / 2;
		newInternal->size = MAX - (MAX + 1) / 2;
		//give elements and pointers to the new NodeI
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
			//if cursor is a root NodeI, we create a new root
			NodeI* newRoot = new NodeI;
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
NodeI* BPTreeI::findParent(NodeI* cursor, NodeI* child)
{
	//finds parent using depth first traversal and ignores leaf NodeIs as they cannot be parents
	//also ignores second last level because we will never find parent of a leaf NodeI during insertion using this function
	NodeI* parent;
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
void BPTreeI::remove(SecKeySS<int> x)
{
	//delete logic
	if (root == NULL)
	{
		cout << "Tree empty\n";
	}
	else
	{
		NodeI* cursor = root;
		NodeI* parent;
		int leftSibling, rightSibling;
		//in the following while loop, cursor will will travel to the leaf NodeI possibly consisting the key
		while (cursor->IS_LEAF == false)
		{
			for (int i = 0; i < cursor->size; i++)
			{
				parent = cursor;
				leftSibling = i - 1; //leftSibling is the index of left sibling in the parent NodeI
				rightSibling = i + 1; //rightSibling is the index of right sibling in the parent NodeI
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
		if (!found)//if key does not exist in that leaf NodeI
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
		if (cursor == root)//if it is root NodeI, then make all pointers NULL
		{
			cout << "Deleted " << x << " from leaf NodeI successfully\n";
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
		cout << "Deleted " << x << " from leaf NodeI successfully\n";
		if (cursor->size >= (MAX + 1) / 2)//no underflow
		{
			return;
		}
		cout << "Underflow in leaf NodeI!\n";
		//underflow condition
		//first we try to transfer a key from sibling NodeI
		//check if left sibling exists
		if (leftSibling >= 0)
		{
			NodeI* leftNodeI = parent->ptr[leftSibling];
			//check if it is possible to transfer
			if (leftNodeI->size >= (MAX + 1) / 2 + 1)
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
				cursor->key[0] = leftNodeI->key[leftNodeI->size - 1];
				//shift pointer of leftsibling
				leftNodeI->size--;
				leftNodeI->ptr[leftNodeI->size] = cursor;
				leftNodeI->ptr[leftNodeI->size + 1] = NULL;
				//update parent
				parent->key[leftSibling] = cursor->key[0];
				cout << "Transferred " << cursor->key[0] << " from left sibling of leaf NodeI\n";
				return;
			}
		}
		if (rightSibling <= parent->size)//chech if right sibling exist
		{
			NodeI* rightNodeI = parent->ptr[rightSibling];
			//check if it is possible to transfer
			if (rightNodeI->size >= (MAX + 1) / 2 + 1)
			{
				//shift pointer to next leaf
				cursor->size++;
				cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
				cursor->ptr[cursor->size - 1] = NULL;
				//transfer
				cursor->key[cursor->size - 1] = rightNodeI->key[0];
				//shift pointer of rightsibling
				rightNodeI->size--;
				rightNodeI->ptr[rightNodeI->size] = rightNodeI->ptr[rightNodeI->size + 1];
				rightNodeI->ptr[rightNodeI->size + 1] = NULL;
				//shift conent of right sibling
				for (int i = 0; i < rightNodeI->size; i++)
				{
					rightNodeI->key[i] = rightNodeI->key[i + 1];
				}
				//update parent
				parent->key[rightSibling - 1] = rightNodeI->key[0];
				cout << "Transferred " << cursor->key[cursor->size - 1] << " from right sibling of leaf NodeI\n";
				return;
			}
		}
		//must merge and delete a NodeI
		if (leftSibling >= 0)//if left sibling exist
		{
			NodeI* leftNodeI = parent->ptr[leftSibling];
			// transfer all keys to leftsibling and then transfer pointer to next leaf NodeI
			for (int i = leftNodeI->size, j = 0; j < cursor->size; i++, j++)
			{
				leftNodeI->key[i] = cursor->key[j];
			}
			leftNodeI->ptr[leftNodeI->size] = NULL;
			leftNodeI->size += cursor->size;
			leftNodeI->ptr[leftNodeI->size] = cursor->ptr[cursor->size];
			cout << "Merging two leaf NodeIs\n";
			removeInternal(parent->key[leftSibling], parent, cursor);// delete parent NodeI key
			delete[] cursor->key;
			delete[] cursor->ptr;
			delete cursor;
		}
		else if (rightSibling <= parent->size)//if right sibling exist
		{
			NodeI* rightNodeI = parent->ptr[rightSibling];
			// transfer all keys to cursor and then transfer pointer to next leaf NodeI
			for (int i = cursor->size, j = 0; j < rightNodeI->size; i++, j++)
			{
				cursor->key[i] = rightNodeI->key[j];
			}
			cursor->ptr[cursor->size] = NULL;
			cursor->size += rightNodeI->size;
			cursor->ptr[cursor->size] = rightNodeI->ptr[rightNodeI->size];
			cout << "Merging two leaf NodeIs\n";
			removeInternal(parent->key[leftSibling + 1], parent, rightNodeI);// delete parent NodeI key
			delete[] rightNodeI->key;
			delete[] rightNodeI->ptr;
			delete rightNodeI;
		}
	}
}
void BPTreeI::removeInternal(SecKeySS<int> x, NodeI* cursor, NodeI* child)
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
				cout << "Changed root NodeI\n";
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
				cout << "Changed root NodeI\n";
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
		cout << "Deleted " << x << " from internal NodeI successfully\n";
		return;
	}
	cout << "Underflow in internal NodeI!\n";
	//underflow, try to transfer first
	NodeI* parent = findParent(root, cursor);
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
		NodeI* leftNodeI = parent->ptr[leftSibling];
		//check if it is possible to transfer
		if (leftNodeI->size >= (MAX + 1) / 2)
		{
			//make space for transfer of key
			for (int i = cursor->size; i > 0; i--)
			{
				cursor->key[i] = cursor->key[i - 1];
			}
			//transfer key from left sibling through parent
			cursor->key[0] = parent->key[leftSibling];
			parent->key[leftSibling] = leftNodeI->key[leftNodeI->size - 1];
			//transfer last pointer from leftNodeI to cursor
			//make space for transfer of ptr
			for (int i = cursor->size + 1; i > 0; i--)
			{
				cursor->ptr[i] = cursor->ptr[i - 1];
			}
			//transfer ptr
			cursor->ptr[0] = leftNodeI->ptr[leftNodeI->size];
			cursor->size++;
			leftNodeI->size--;
			cout << "Transferred " << cursor->key[0] << " from left sibling of internal NodeI\n";
			return;
		}
	}
	if (rightSibling <= parent->size)//check if right sibling exist
	{
		NodeI* rightNodeI = parent->ptr[rightSibling];
		//check if it is possible to transfer
		if (rightNodeI->size >= (MAX + 1) / 2)
		{
			//transfer key from right sibling through parent
			cursor->key[cursor->size] = parent->key[pos];
			parent->key[pos] = rightNodeI->key[0];
			for (int i = 0; i < rightNodeI->size - 1; i++)
			{
				rightNodeI->key[i] = rightNodeI->key[i + 1];
			}
			//transfer first pointer from rightNodeI to cursor
			//transfer ptr
			cursor->ptr[cursor->size + 1] = rightNodeI->ptr[0];
			for (int i = 0; i < rightNodeI->size; ++i)
			{
				rightNodeI->ptr[i] = rightNodeI->ptr[i + 1];
			}
			cursor->size++;
			rightNodeI->size--;
			cout << "Transferred " << cursor->key[0] << " from right sibling of internal NodeI\n";
			return;
		}
	}
	//transfer wasnt posssible hence do merging
	if (leftSibling >= 0)
	{
		//leftNodeI + parent key + cursor
		NodeI* leftNodeI = parent->ptr[leftSibling];
		leftNodeI->key[leftNodeI->size] = parent->key[leftSibling];
		for (int i = leftNodeI->size + 1, j = 0; j < cursor->size; j++)
		{
			leftNodeI->key[i] = cursor->key[j];
		}
		for (int i = leftNodeI->size + 1, j = 0; j < cursor->size; j++)
		{
			leftNodeI->ptr[i] = cursor->ptr[j];
			cursor->ptr[j] = NULL;
		}
		leftNodeI->size += cursor->size + 1;
		cursor->size = 0;
		//delete cursor
		removeInternal(parent->key[leftSibling], parent, cursor);
		cout << "Merged with left sibling\n";

	}
	else if (rightSibling <= parent->size)
	{
		//cursor + parent key + rightNodeI
		NodeI* rightNodeI = parent->ptr[rightSibling];
		cursor->key[cursor->size] = parent->key[leftSibling];
		for (int i = cursor->size + 1, j = 0; j < rightNodeI->size; j++)
		{
			cursor->key[i] = rightNodeI->key[j];
		}
		for (int i = cursor->size + 1, j = 0; j < rightNodeI->size; j++)
		{
			cursor->ptr[i] = rightNodeI->ptr[j];
			rightNodeI->ptr[j] = NULL;
		}
		cursor->size += rightNodeI->size + 1;
		rightNodeI->size = 0;
		//delete cursor
		removeInternal(parent->key[leftSibling], parent, rightNodeI);
		cout << "Merged with right sibling\n";
	}
}*/
void BPTreeI::display(NodeI* cursor)
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
NodeI* BPTreeI::getRoot()
{
	return root;
}
void BPTreeI::cleanUp(NodeI* cursor)
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
BPTreeI::~BPTreeI()
{
	//calling cleanUp routine
	cleanUp(root);
}
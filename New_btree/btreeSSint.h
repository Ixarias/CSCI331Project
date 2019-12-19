/*****B+ Tree*****/
#ifndef _BPTREESSI
#define _BPTREESSI

#include "SecKeySS.h"

//class BPTreeI;

using namespace std;

	class NodeI
	{
		bool IS_LEAF;
		SecKeySS<int> *key;
		int size;
		NodeI** ptr;
        friend class BPTreeI;

        public:
			//! Insert a string for the place into a specific position
			/*!
			\param s a string to insert
			\param rrn relative record number
			*/
		    NodeI();
	};


class BPTreeI
{
    public:
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	BPTreeI();
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
    ~BPTreeI();
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	vector<int> search(int x);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	vector<int> search(SecKeySS<int> x);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	void addDataToKey(int s, int rrn);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	void insert(SecKeySS<int> x);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	void remove(SecKeySS<int> x);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	void display(NodeI*);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	NodeI* getRoot();
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	void cleanUp(NodeI*);

	private:
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	NodeI *root;
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	void insertInternal(SecKeySS<int> x,NodeI*,NodeI*);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	void removeInternal(SecKeySS<int> x,NodeI*,NodeI*);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	NodeI* findParent(NodeI*,NodeI*);
}
#include "btreeSSint.cpp"
#endif
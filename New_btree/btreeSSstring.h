/*****B+ Tree*****/
#ifndef _BPTREESSS
#define _BPTREESSS

#include <string>
#include "SecKeySS.h"

//class BPTreeS;

using namespace std;

   
	class NodeS
	{
		bool IS_LEAF;
		string *key;
		int size;
		NodeS** ptr;
        friend class BPTreeS;

        public:
		    NodeS();
	};


class BPTreeS
{
    public:
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	BPTreeS();
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
    ~BPTreeS();
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	vector<int> search(SecKeySS<string> x);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	vector<int> search(string x);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	void insert(SecKeySS<string> x);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	void addDataToKey(string s, int rrn);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	void remove(SecKeySS<string> x);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	void display(NodeS*);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	NodeS* getRoot();
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	void cleanUp(NodeS*);

	private:
	NodeS *root;
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	void insertInternal(SecKeySS<string> x,NodeS*,NodeS*);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	void removeInternal(SecKeySS<string> x,NodeS*,NodeS*);
	//! Insert a string for the place into a specific position
	/*!
		\param s a string to insert
		\param rrn relative record number
	*/
	NodeS* findParent(NodeS*,NodeS*);
};
#include "btreeSSstring.cpp"
#endif
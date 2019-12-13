/** \class SSClass  SSClass.h "SSClass.h"

    \brief LinkedList integration for blocks, records, and fields 
    \authors Jordan Bremer, Melvin Schmid, ..., ..., ...

   Sequence Set class:  
     -- allows for insert and deletion of linked list
     -- populates secondary keys
     -- allows for searching of said linked list
     -- ability to return city, state, county, lattitude, longitude, zip, and
   lower and upper indicies 
     -- ability to input a txt file and populate it's contents 
  
   Implementation and assumptions:
     -- size defaults are listed towards the top of the program
     -- array/vector elements are initialized to zero
*/


#ifndef SSCLASS_
#define SSCLASS_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "LinkedList.h"
#include "Node.h"
#include "SecKeySS.h"
#include "ListInterface.h"
#include <limits>

using namespace std;

/** \brief NUMSECKEYS The numebr of section keys */
const int NUMSECKEYS = 6;

/** \brief ZIPSIZE The size of the zip code */
const int ZIPSIZE = 6;

/** \brief PLACESIZE The size of the place (city) */ 
const int PLACESIZE = 31;

/** \brief STATESIZE The size of the sate letters */
const int STATESIZE = 2;

/** \brief COUNTYSIZE The size of letters for the county */
const int COUNTYSIZE = 36;

/** \brief LATSIZE The size of the Lattatude */
const int LATSIZE = 9;

/** \brief LONSIZE The size (including sign) of the longitude */
const int LONSIZE = 10;
 
const int ZIPOFFSET = 0;
const int PLACEOFFSET = ZIPSIZE - 1;
const int STATEOFFSET = PLACEOFFSET + PLACESIZE;
const int COUNTYOFFSET = STATEOFFSET + STATESIZE;
const int LATOFFSET = COUNTYOFFSET + COUNTYSIZE;
const int LONOFFSET = LATOFFSET + LATSIZE;
const int CHARINLINE = LONOFFSET + LONSIZE;

class SSClass
{
private:
	unsigned numLinesIndex;
	unsigned numRecords;
	int nextEmpty;
	//int will be the zipcode location (RRN) The first LinkedList is a list of different sec key values
	LinkedList<SecKeySS<int>> secKeyZip;
	LinkedList<SecKeySS<string>> secKeyPlace;
	LinkedList<SecKeySS<string>> secKeyState;
	LinkedList<SecKeySS<string>> secKeyCounty;
	LinkedList<SecKeySS<int>> secKeyLat;
	LinkedList<SecKeySS<int>> secKeyLon;
	fstream indexFile;
	//fstream blockRecordFile;
	
	//! Inserts the zip code feild
	/*!
	    \param s a string of the zipcode digtis
	    \param rrn relative record number
	*/
	void insertZip(string s, int rrn);
	
	//! Insert a string for the place into a specific position
	/*! 
	    \param s a string to insert
	    \param rrn relative record number
	*/
	void insertPlace(string s, int rrn);
	
	//! Inserts a string for the state into the LinkedList
	/*!
	    \param s a string contating the two state letters
	    \param rrn relative record number
	*/
	void insertState(string s, int rrn);
	
	//! Inserts a string for the county into the LinkedList
	/*!
	    \param s a string containing the county 
	    \param rrn relative record number
	*/
	void insertCounty(string s, int rrn);
	
	//! Inserts latatude as a string int the LinkedList
	/*!
	    \param s a string containing the latatude
	    \param rrn relative record number
	*/
	void insertLat(string s, int rrn);
	
	//! Inserts the longitude into the LinkeList
	/*! 
	    \param s a string containing the longitude including sign
	    \param rrn relative record number
	*/
	void insertLon(string s, int rrn);
	

	//get functions take the entire line for a record and return the specified data member
	//! Takes the entire line for a record and returns feild zip
	/*!
	    \param s a string of a record
	    \return zip code as a string (use stoi(getzip()) for int)
	*/
	string getZip(string s);	

	//! Takes the entire line for a record and returns feild place
	/*!
	    \param s a string of a record
	    \return place as a string
	*/
	string getPlace(string s);

	//! Takes the entire line for a record and returns feild palce
	/*!
	    \param s a string of a record
	    \return state  as a string
	*/
	string getState(string s);

	//! Takes the entire line for a record and returns feild state
	/*!
	    \param s a string of a record
	    \return state as a string
	*/
	string getCounty(string s);

	//! Takes the entire line for a record and returns latitude
	/*!
	    \param s a string of a record
	    \return lattitude as a string (use stoi(getLat()) for int)
	*/
	string getLat(string s);

	//! Takes the entire line for a record and returns feild longitude
	/*!
	    \param s a string of a record
	    \return longitude as a string (use stoi(getLon()) for int)
	*/
	string getLon(string s);
	
	//! Goes to a line in a file
	/*!
	    \param file the file 
	    \param num the number of line to goto in the file
	*/
	void goToLine(fstream& file, unsigned num);

	//! Goes to data

	/*!
	    \param file
	*/
	void goToData(fstream& file);
	//bool replace(string s);
	//bool delete(int position);

	//! Create the string needed when removing a record
	/*!
	    \param next and int for the next line
	    \return a string for the recored
	*/
	string createUnusedLine(int next); //creates the string needed when removing a record

	//! populates data from a text file
	void populate(); //populates data from text file

public:
	//! Default constructor
	SSClass();

	//! Constructor
	SSClass(const SSClass& ss);
	
	//! Deconstructor
	~SSClass();

	//! Check if numRecords is 0
	/*!
	     \return  returns false if empty, otherwise returns true
	*/
	bool isEmpty() { return numRecords == 0; };

	//! Opens external file
	/*!
	    \param input string
	    \pre  data file
	    \return true if file location exists, otherwise returns false
	*/
	bool openFile(string input);
	/*---------------------------------------------------------------------------
	   Creates external file
	   Preconditions:   data file
	   Postconditions:  returns true if file location exists, otherwise returns false */
	//bool createIndexFile();
	/*---------------------------------------------------------------------------
	   Creates external file
	   Preconditions:   data file
	   Postconditions:  returns true if file location exists, otherwise returns false */
	//bool createBlockRecordFile();
	   
	//! inserts line by line into data
	/*!
	    \param s a string to insert
	*/
	void insert(string s);
	
	//! Searches for record 
	/*!
	    \param s strign to search for
	    \parm fieldNum the field in whitch to search
	    \return vector of results
	*/
	vector<int> search(string s, unsigned fieldNum);

	//! Searches directionly (N, S, W, E)
	/*!
	    \param state the state to search "MN" for example
	    \param direction (N, S, W, E)
	    \return the line contating the soght after direction 
	*/
	int directionalSearch(string state, char direction);
	
	//! Fills secondary key vector
	/*! 
	    \param rrn and integer refring to the line to get
	    \return string containging the contents of the line
	*/	
	string returnLine(int rrn);
};


#endif

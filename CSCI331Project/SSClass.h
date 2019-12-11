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
	    \param state the state to search
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

/*---------------------------------------------------------------------------
	Opens file
	Preconditions:   File needs to be created
	Postconditions:  None
*/
bool SSClass::openFile(string input) { //input is a file name
	indexFile.open(input);
	nextEmpty = -1;
	return (indexFile.is_open());

}
/*---------------------------------------------------------------------------
	Creates index
	Preconditions:   None
	Postconditions:  Object indexFile can be used
*/
/*
bool SSClass::createIndexFile() {
	indexFile.open("index.txt");
	return indexFile.is_open();
}
*/
/*---------------------------------------------------------------------------
	Creates block record file
	Preconditions:   None
	Postconditions:  None
*/
/*
bool SSClass::createBlockRecordFile() {
	blockRecordFile.open("blockRecord.txt");
	return blockRecord.is_open();
}
*/
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:  None
*/
SSClass::SSClass() {
	numRecords = 0;
	openFile("us_postal_codes.txt");
}
SSClass::SSClass(const SSClass& ss) {
	numLinesIndex = ss.numLinesIndex;
	numRecords = ss.numRecords;
	nextEmpty = ss.nextEmpty;
	secKeyZip = ss.secKeyZip;
	secKeyPlace= ss.secKeyPlace;
	secKeyState = ss.secKeyState;
	secKeyCounty = ss.secKeyCounty;
	secKeyLat = ss.secKeyLat;
	secKeyLon = ss.secKeyLon;
	openFile("us_postal_codes.txt");
}
SSClass::~SSClass(){
	secKeyZip.clear();
	secKeyPlace.clear();
	secKeyState.clear();
	secKeyCounty.clear();
	secKeyLat.clear();
	secKeyLon.clear();
	indexFile.close();
	//blockRecord.close();
}

/*! Insertion of records into both the index file as well as the linkedlist
    of linkedlists
    /param s string to be inserted
*/
void SSClass::insert(string s) {
	if (nextEmpty == -1) {
		goToLine(indexFile, numLinesIndex);
		indexFile << "\n" << s;
		insertZip(getZip(s), numLinesIndex);
		insertPlace(getPlace(s), numLinesIndex);
		insertState(getState(s), numLinesIndex);
		insertCounty(getCounty(s), numLinesIndex);
		insertLat(getLat(s), numLinesIndex);
		insertLon(getLon(s), numLinesIndex);
		numLinesIndex++;
		return;
	}
	goToLine(indexFile, nextEmpty);
	//replace(s, nextEmpty);
	insertZip(getZip(s), nextEmpty);
	insertPlace(getPlace(s), nextEmpty);
	insertState(getState(s), nextEmpty);
	insertCounty(getCounty(s), nextEmpty);
	insertLat(getLat(s), nextEmpty);
	insertLon(getLon(s), nextEmpty);
}

string SSClass::returnLine(int rrn) {
	string returnVal;
	goToLine(indexFile, rrn);
	getline(indexFile, returnVal);
	return returnVal;
}


vector<int> SSClass::search(string s, unsigned fieldNum) {
	typedef SecKeySS<string> secCopy;
	int i;
	vector<int> results;
	switch (fieldNum) {
	case 1:
	{
		for (i = 1; (i < (secKeyZip.getItemCount() + 1)) && (secKeyZip.getEntry(i).getData() < stoi(s)); i++);
		if (secKeyZip.getEntry(i).getData() == stoi(s)) {
			LinkedList<int> toCopy = LinkedList<int>(secKeyZip.getEntry(i).getDuplicates());
			for (int j = 1; j < (toCopy.getItemCount() + 1); j++) {
				results.push_back(toCopy.getEntry(j));
			}
		}
	}
	break;
	case 2:
	{
		for(i = 1; (i < (secKeyPlace.getItemCount() + 1)) && (secKeyPlace.getEntry(i).getData() < s); i++);
		if ((secKeyPlace.getEntry(i).getData()) == (s)) {
			LinkedList<string> toCopy = LinkedList<string>(secKeyPlace.getEntry(i).getDuplicates());
			for (int j = 1; j < (toCopy.getItemCount() + 1); j++) {
				// stoi toCopy.getEntry returns string
				results.push_back(stoi(toCopy.getEntry(j)));
			}
		}
	}
	break;
	case 3:
	{
		for (i = 1; (i < (secKeyState.getItemCount() + 1)) && (secKeyState.getEntry(i).getData() < s); i++);
		if ((secKeyState.getEntry(i).getData()) == (s)) {
			LinkedList<string> toCopy = LinkedList<string>(secKeyState.getEntry(i).getDuplicates());
			for (int j = 1; j < (toCopy.getItemCount() + 1); j++) {
				// stoi toCopy.getEntry returns string
				results.push_back(stoi(toCopy.getEntry(j)));
			}
		}
	}
	break;
	case 4:
	{
		for (i = 1; (i < (secKeyCounty.getItemCount() + 1)) && (secKeyCounty.getEntry(i).getData() < s); i++);
		if ((secKeyCounty.getEntry(i).getData()) == (s)) {
			LinkedList<string> toCopy = LinkedList<string>(secKeyCounty.getEntry(i).getDuplicates());
			for (int j = 1; j < (toCopy.getItemCount() + 1); j++) {
				// stoi toCopy.getEntry returns string
				results.push_back(stoi(toCopy.getEntry(j)));
			}
		}
	}
	break;
	case 5:
	{
		for (i = 1; (i < (secKeyLat.getItemCount() + 1)) && (secKeyLat.getEntry(i).getData() < stoi(s)); i++);
		if (secKeyLat.getEntry(i).getData() == static_cast<int>(stod(s))) {
			LinkedList<int> toCopy = LinkedList<int>(secKeyLat.getEntry(i).getDuplicates());
			for (int j = 1; j < (toCopy.getItemCount() + 1); j++) {
				results.push_back(toCopy.getEntry(j));
			}
		}
	}
	break;
	case 6:
	{
		for (i = 1; (i < (secKeyLon.getItemCount() + 1)) && (secKeyLon.getEntry(i).getData() < stoi(s)); i++);
		if (secKeyLon.getEntry(i).getData() == static_cast<int>(stod(s))) {
			LinkedList<int> toCopy = LinkedList<int>(secKeyLon.getEntry(i).getDuplicates());
			for (int j = 1; j < (toCopy.getItemCount() + 1); j++) {
				results.push_back(toCopy.getEntry(j));
			}
		}
	}
	break;
	}
	return results;
}

int SSClass::directionalSearch(string stateS, char direction) {
	direction = toupper(direction);
	int i = 1;
	int returnIndex = -1;
	double highOrLow;
	vector<int> state = search(stateS, 3);
	switch (direction) {
	case 'N':
	{
		returnIndex = state[0];
		highOrLow = stod(getLat(returnLine(state[0])));
		for (i; i < state.size(); i++) {
			if (highOrLow < stod(getLat(returnLine(state[i])))) {
				highOrLow = stod(getLat(returnLine(state[i])));
				returnIndex = i;
			}

		}
	}
	break;
	case 'E':
	{
		returnIndex = state[0];
		highOrLow = stod(getLon(returnLine(state[0])));
		for (i; i < state.size(); i++) {
			if (highOrLow < stod(getLon(returnLine(state[i])))) {
				highOrLow = stod(getLon(returnLine(state[i])));
				returnIndex = i;
			}
		}
		
	}
	break;
	case 'S':
	{
		returnIndex = state[0];
		highOrLow = stod(getLat(returnLine(state[0])));
		for (i; i < state.size(); i++) {
			if (highOrLow > stod(getLat(returnLine(state[i])))) {
				highOrLow = stod(getLat(returnLine(state[i])));
				returnIndex = i;
			}
		}
		break;
	}
	case 'W':
	{
		returnIndex = state[0];
		highOrLow = stod(getLon(returnLine(state[0])));
		for (i; i < state.size(); i++) {
			if (highOrLow > stod(getLon(returnLine(state[i])))) {
				highOrLow = stod(getLon(returnLine(state[i])));
				returnIndex = i;
			}
		}

	}
	break;
	}
	return returnIndex;

}

//get value at index in getEntry(index)         insert is insert(index)   
void SSClass::insertZip(string st, int rrn) {				 //no sec key matching -> create new one....    match found -> insert at index 1
	int index;
	int s = stoi(st);
	SecKeySS<int> secCopy;
	LinkedList<int> copyDup;
		int i;
	for (i = 1; (i < (secKeyZip.getItemCount() + 1)) && (secKeyZip.getEntry(i).getData() < s); i++);
	if (secKeyZip.getEntry(i).getData() == s) {
		secCopy = secKeyZip.getEntry(i);
		copyDup = LinkedList<int>(secCopy.getDuplicates());
		copyDup.insert(1, rrn);
		secCopy.setDuplicates(copyDup);
		secKeyZip.replace(i, secCopy);
		return;
	}
	copyDup.insert(1, rrn);
	secCopy.setDuplicates(copyDup);
	secCopy.setData(s);
	secKeyZip.insert(i, secCopy);

}

void SSClass::insertPlace(string s, int rrn) {
	int index;
	SecKeySS<string> secCopy;
	LinkedList<string> copyDup;
		int i;
	for (i = 1; (i < (secKeyPlace.getItemCount() + 1)) && (secKeyPlace.getEntry(i).getData() < s); i++);
	if (secKeyPlace.getEntry(i).getData() == s) {
		secCopy = secKeyPlace.getEntry(i);
		copyDup = LinkedList<string>(secCopy.getDuplicates());
		copyDup.insert(1, to_string(rrn), 1);
		secCopy.setDuplicates(copyDup);
		secKeyPlace.replace(i, secCopy);
		return;
	}
	copyDup.insert(1, to_string(rrn), 1);
	secCopy.setDuplicates(copyDup);
	secCopy.setData(getPlace(s));
	secKeyPlace.insert(i, secCopy);
}

void SSClass::insertState(string s, int rrn) {
	int index;
	SecKeySS<string> secCopy;
	LinkedList<string> copyDup;
		int i;
	for (i = 1; (i < (secKeyState.getItemCount() + 1)) && (secKeyState.getEntry(i).getData() < s); i++);
	if (secKeyState.getEntry(i).getData() == s) {
		secCopy = secKeyState.getEntry(i);
		copyDup = LinkedList<string>(secCopy.getDuplicates());
		copyDup.insert(1, to_string(rrn), 1);
		secCopy.setDuplicates(copyDup);
		secKeyState.replace(i, secCopy);
		return;
	}
	copyDup.insert(1, to_string(rrn), 1);
	secCopy.setDuplicates(copyDup);
	secCopy.setData(getState(s));
	secKeyState.insert(i, secCopy);
}

void SSClass::insertCounty(string s, int rrn) {
	int index;
	SecKeySS<string> secCopy;
	LinkedList<string> copyDup;
		int i;
	for (i = 1; (i < (secKeyCounty.getItemCount() + 1)) && (secKeyCounty.getEntry(i).getData() < s); i++);
	if (secKeyCounty.getEntry(i).getData() == s) {
		secCopy = secKeyCounty.getEntry(i);
		copyDup = LinkedList<string>(secCopy.getDuplicates());
		copyDup.insert(1, to_string(rrn), 1);
		secCopy.setDuplicates(copyDup);
		secKeyCounty.replace(i, secCopy);
		return;
	}
	copyDup.insert(1, to_string(rrn), 1);
	secCopy.setDuplicates(copyDup);
	secCopy.setData(getCounty(s));
	secKeyCounty.insert(i, secCopy);
}

void SSClass::insertLat(string st, int rrn) {
	int index;
	int s = static_cast<int>(stod(st));
	SecKeySS<int> secCopy;
	LinkedList<int> copyDup;
		int i;
	for (i = 1; (i < (secKeyLat.getItemCount() + 1)) && (secKeyLat.getEntry(i).getData() < s); i++);
	if (secKeyLat.getEntry(i).getData() == s) {
		secCopy = secKeyLat.getEntry(i);
		copyDup = LinkedList<int>(secCopy.getDuplicates());
		copyDup.insert(1, rrn);
		secCopy.setDuplicates(copyDup);
		secKeyLat.replace(i, secCopy);
		return;
	}
	copyDup.insert(1, rrn);
	secCopy.setDuplicates(copyDup);
	secCopy.setData(static_cast<int>(stod(st)));
	secKeyLat.insert(i, secCopy);
}

void SSClass::insertLon(string st, int rrn) {
	int index;
	int s = static_cast<int>(stod(st));
	SecKeySS<int> secCopy;
	LinkedList<int> copyDup;
		int i;
	for (i = 1; (i < (secKeyLon.getItemCount() + 1)) && (secKeyLon.getEntry(i).getData() < s); i++);
	if (secKeyLon.getEntry(i).getData() == s) {
		secCopy = secKeyLon.getEntry(i);
		copyDup = LinkedList<int>(secCopy.getDuplicates());
		copyDup.insert(1, rrn);
		secCopy.setDuplicates(copyDup);
		secKeyLon.replace(i, secCopy);
		return;
	}
	copyDup.insert(1, rrn);
	secCopy.setDuplicates(copyDup);
	secCopy.setData(static_cast<int>(stod(st)));
	secKeyLon.insert(i, secCopy);
}

void SSClass::goToLine(fstream& file, unsigned num) {
	goToData(file); //beginning of our data file
	for (int i = 0; i < num - 1; ++i) {
		file.ignore(1000, '\n'); //ignore one line
	}
	//return file;
}

void SSClass::goToData(fstream& file) { //puts cursor at the beginning of the data portion of the txt file
	file.seekg(ios::beg);
	string in;
	getline(file, in);
	while (in != "ENDOFHDR")
		getline(file, in);
}

string SSClass::getZip(string s) { //use stoi(getzip(s)); to return int value
	string returnValue;
	for (int i = 0; i < ZIPSIZE; i++)
		returnValue[i] = s[ZIPOFFSET + i];
	return returnValue;
}

string SSClass::getPlace(string s) {
	string returnvalue;
	for (int i = 0; i < PLACESIZE; i++)
		returnvalue[i] = s[PLACEOFFSET + i];
	return returnvalue;
}

string SSClass::getState(string s) {
	string returnvalue;
	for (int i = 0; i < STATESIZE; i++)
		returnvalue[i] = s[STATEOFFSET + i];
	return returnvalue;
}

string SSClass::getCounty(string s) {
	string returnvalue;
	for (int i = 0; i < COUNTYSIZE; i++)
		returnvalue[i] = s[COUNTYOFFSET + i];
	return returnvalue;
}

string SSClass::getLat(string s) { //use stod(getlat(s)); to return double value
	string returnvalue;
	for (int i = 0; i < LATSIZE; i++)
		returnvalue[i] = s[LATOFFSET + i];
	return returnvalue;
}

string SSClass::getLon(string s) { //use stod(getLon(s)); to return double value
	string returnValue;
	for (int i = 0; i < LONSIZE; i++)
		returnValue[i] = s[LONOFFSET + i];
	return returnValue;
}

string SSClass::createUnusedLine(int next) { //pass in the integer value of the next empty line
	string unusedLine = to_string(next);
	int i;
	for (i = unusedLine.size(); i < CHARINLINE; i++) {
		unusedLine += " ";
	}
	return unusedLine;
}

/*
bool SSClass::replace(string s, int line) { // To be able to replace a line in a text file, you have to write everything to a new file, with the updated line, then delete the previous file 
	goToLine(indexFile, line);				// and rename the temperary file
	string strReplace;
	getline(indexFile, strReplace);
	string strNew = s;
	ofstream fileout("temp_file.txt"); //Temporary file
	if (!fileout)
		return false;

	string strTemp;
	indexFile.seekg(ios::beg);
	while (strTemp = indexFile.getline())
	{
		if (strTemp == strReplace) {
			strTemp = strNew;
		}
		fileout << "\n";
		for (int i = 0; i < ZIPSIZE; i++) { //use this for zip since there may be leading whitespace
			fileout << strTemp[i];
			strTemp[i] = ' ';
		}
		fileout << strTemp;
	}
	remove(indexFile);
	rename("temp_file.txt", "us_postal_codes.txt");
	close(fileout);
	openFile("us_postal_codes.txt");
	return true;
}
}
*/

void SSClass::populate() {
	goToData(indexFile);
	string line;
	while (!indexFile.eof()) {
		getline(indexFile, line);
		insert(line);
	}
}

#endif

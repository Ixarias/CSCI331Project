
#ifndef SSCLASS_
#define SSCLASS_

//---------------------------------------------------------------------------
// SSClass.h
// LinkedList integration for blocks, records, and fields 
// Authors: Jordan Bremer, ..., ..., ..., ...
//---------------------------------------------------------------------------
// Sequence Set class:  
//   -- allows for insert and deletion of linked list
//   -- populates secondary keys
//   -- allows for searching of said linked list
//   -- ability to return city, state, county, lattitude, longitude, zip, and
// lower and upper indicies 
//   -- ability to input a txt file and populate it's contents 
//
// Implementation and assumptions:
//   -- size defaults are listed towards the top of the program
//   -- array/vector elements are initialized to zero
//---------------------------------------------------------------------------


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "LinkedList.h"
#include "Node.h"
#include "SecKeySS.h"
#include "ListInterface.h"

using namespace std;

const int NUMSECKEYS = 6;
const int ZIPSIZE = 6;
const int PLACESIZE = 31;
const int STATESIZE = 2;
const int COUNTYSIZE = 36;
const int LATSIZE = 9;
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
	LinkedList<SecKeySS> secKeyZip;
	LinkedList<SecKeySS> secKeyPlace;
	LinkedList<SecKeySS> secKeyState;
	LinkedList<SecKeySS> secKeyCounty;
	LinkedList<SecKeySS> secKeyLat;
	LinkedList<SecKeySS> secKeyLon;
	fstream indexFile;
	//fstream blockRecordFile;
	void insertZip(string s, int rrn);
	void insertPlace(string s, int rrn);
	void insertState(string s, int rrn);
	void insertCounty(string s, int rrn);
	void insertLat(string s, int rrn);
	void insertLon(string s, int rrn);
	//get functions take the entire line for a record and return the specified data member
	string getZip(string s);
	string getPlace(string s);
	string getState(string s);
	string getCounty(string s);
	string getLat(string s);
	string getLon(string s);
	void goToLine(fstream& file, unsigned num);
	void goToData(fstream& file);
	//bool replace(string s);
	//bool delete(int position);
	string createUnusedLine(int next); //creates the string needed when removing a record
	void populate(); //populates data from text file

public:
	/*---------------------------------------------------------------------------
	   Default constructor
	   Preconditions:   None
	   Postconditions:  */
	SSClass();
	SSClass(const SSClass& ss);
	/*---------------------------------------------------------------------------
	   Default destructor
	   Preconditions:   None
	   Postconditions:  */
	~SSClass();
	/*---------------------------------------------------------------------------
	   Check if numRecords is 0
	   Preconditions:   None
	   Postconditions:  returns false if empty, otherwise returns true */
	bool isEmpty() { return numRecords == 0; };
	/*---------------------------------------------------------------------------
	   Opens external file
	   Preconditions:   data file
	   Postconditions:  returns true if file location exists, otherwise returns false*/
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
	/*---------------------------------------------------------------------------
	   inserts line by line into data
	   Preconditions:   None
	   Postconditions:  */
	void insert(string s);
	//---------------------------------------------------------------------------
	// Searches for record 
	// Preconditions:   None
	// Postconditions: 
	vector<int> search(string s, unsigned fieldNum);

	int directionalSearch(string state, char direction);
	/*---------------------------------------------------------------------------
	   Fills secondary key vector
	   Preconditions:   None
	   Postconditions: */
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
/*---------------------------------------------------------------------------
	Insertion of records into both the index file as well as the linkedlist
	of linkedlists
	Preconditions:   String that you want to have inserted
	Postconditions:  None
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
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
string SSClass::returnLine(int rrn) {
	string returnVal;
	goToLine(indexFile, rrn);
	getline(indexFile, returnVal);
	return returnVal;
}


vector<int> SSClass::search(string s, unsigned fieldNum) {
	SecKeySS secCopy;
	int i;
	vector<int> results;
	switch (fieldNum) {
	case 1:
	{
		for (i = 1; (i < (secKeyZip.getItemCount() + 1)) && (secKeyZip.getEntry(i).getData() < s); i++);
		if (stoi(secKeyZip.getEntry(i).getData()) == stoi(s)) {
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
			LinkedList<int> toCopy = LinkedList<int>(secKeyPlace.getEntry(i).getDuplicates());
			for (int j = 1; j < (toCopy.getItemCount() + 1); j++) {
				results.push_back(toCopy.getEntry(j));
			}
		}
	}
	break;
	case 3:
	{
		for (i = 1; (i < (secKeyState.getItemCount() + 1)) && (secKeyState.getEntry(i).getData() < s); i++);
		if ((secKeyState.getEntry(i).getData()) == (s)) {
			LinkedList<int> toCopy = LinkedList<int>(secKeyState.getEntry(i).getDuplicates());
			for (int j = 1; j < (toCopy.getItemCount() + 1); j++) {
				results.push_back(toCopy.getEntry(j));
			}
		}
	}
	break;
	case 4:
	{
		for (i = 1; (i < (secKeyCounty.getItemCount() + 1)) && (secKeyCounty.getEntry(i).getData() < s); i++);
		if ((secKeyCounty.getEntry(i).getData()) == (s)) {
			LinkedList<int> toCopy = LinkedList<int>(secKeyCounty.getEntry(i).getDuplicates());
			for (int j = 1; j < (toCopy.getItemCount() + 1); j++) {
				results.push_back(toCopy.getEntry(j));
			}
		}
	}
	break;
	case 5:
	{
		for (i = 1; (i < (secKeyLat.getItemCount() + 1)) && (secKeyLat.getEntry(i).getData() < s); i++);
		if (stoi(secKeyLat.getEntry(i).getData()) == static_cast<int>(stod(s))) {
			LinkedList<int> toCopy = LinkedList<int>(secKeyLat.getEntry(i).getDuplicates());
			for (int j = 1; j < (toCopy.getItemCount() + 1); j++) {
				results.push_back(toCopy.getEntry(j));
			}
		}
	}
	break;
	case 6:
	{
		for (i = 1; (i < (secKeyLon.getItemCount() + 1)) && (secKeyLon.getEntry(i).getData() < s); i++);
		if (stoi(secKeyLon.getEntry(i).getData()) == static_cast<int>(stod(s))) {
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
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
//get value at index in getEntry(index)         insert is insert(index)   
void SSClass::insertZip(string s, int rrn) {				 //no sec key matching -> create new one....    match found -> insert at index 1
	int index;
	SecKeySS secCopy;
	LinkedList<int> copyDup;
		int i;
	for (i = 1; (i < (secKeyZip.getItemCount() + 1)) && (secKeyZip.getEntry(i).getData() < s); i++);
	if (stoi(secKeyZip.getEntry(i).getData()) == stoi(s)) {
		secCopy = secKeyZip.getEntry(i);
		copyDup = LinkedList<int>(secCopy.getDuplicates());
		copyDup.insert(1, rrn);
		secCopy.setDuplicates(copyDup);
		secKeyZip.replace(i, secCopy);
		return;
	}
	copyDup.insert(1, rrn);
	secCopy.setDuplicates(copyDup);
	secCopy.setData(getZip(s));
	secKeyZip.insert(i, secCopy);

}
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
void SSClass::insertPlace(string s, int rrn) {
	int index;
	SecKeySS secCopy;
	LinkedList<int> copyDup;
		int i;
	for (i = 1; (i < (secKeyPlace.getItemCount() + 1)) && (secKeyPlace.getEntry(i).getData() < s); i++);
	if (secKeyPlace.getEntry(i).getData() == s) {
		secCopy = secKeyPlace.getEntry(i);
		copyDup = LinkedList<int>(secCopy.getDuplicates());
		copyDup.insert(1, rrn);
		secCopy.setDuplicates(copyDup);
		secKeyPlace.replace(i, secCopy);
		return;
	}
	copyDup.insert(1, rrn);
	secCopy.setDuplicates(copyDup);
	secCopy.setData(getPlace(s));
	secKeyPlace.insert(i, secCopy);
}
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
void SSClass::insertState(string s, int rrn) {
	int index;
	SecKeySS secCopy;
	LinkedList<int> copyDup;
		int i;
	for (i = 1; (i < (secKeyState.getItemCount() + 1)) && (secKeyState.getEntry(i).getData() < s); i++);
	if (secKeyState.getEntry(i).getData() == s) {
		secCopy = secKeyState.getEntry(i);
		copyDup = LinkedList<int>(secCopy.getDuplicates());
		copyDup.insert(1, rrn);
		secCopy.setDuplicates(copyDup);
		secKeyState.replace(i, secCopy);
		return;
	}
	copyDup.insert(1, rrn);
	secCopy.setDuplicates(copyDup);
	secCopy.setData(getState(s));
	secKeyState.insert(i, secCopy);
}
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
void SSClass::insertCounty(string s, int rrn) {
	int index;
	SecKeySS secCopy;
	LinkedList<int> copyDup;
		int i;
	for (i = 1; (i < (secKeyCounty.getItemCount() + 1)) && (secKeyCounty.getEntry(i).getData() < s); i++);
	if (secKeyCounty.getEntry(i).getData() == s) {
		secCopy = secKeyCounty.getEntry(i);
		copyDup = LinkedList<int>(secCopy.getDuplicates());
		copyDup.insert(1, rrn);
		secCopy.setDuplicates(copyDup);
		secKeyCounty.replace(i, secCopy);
		return;
	}
	copyDup.insert(1, rrn);
	secCopy.setDuplicates(copyDup);
	secCopy.setData(getCounty(s));
	secKeyCounty.insert(i, secCopy);
}
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
void SSClass::insertLat(string s, int rrn) {
	int index;
	SecKeySS secCopy;
	LinkedList<int> copyDup;
		int i;
	for (i = 1; (i < (secKeyLat.getItemCount() + 1)) && (secKeyLat.getEntry(i).getData() < s); i++);
	if (stoi(secKeyLat.getEntry(i).getData()) == static_cast<int>(stod(s))) {
		secCopy = secKeyLat.getEntry(i);
		copyDup = LinkedList<int>(secCopy.getDuplicates());
		copyDup.insert(1, rrn);
		secCopy.setDuplicates(copyDup);
		secKeyLat.replace(i, secCopy);
		return;
	}
	copyDup.insert(1, rrn);
	secCopy.setDuplicates(copyDup);
	secCopy.setData(to_string(static_cast<int>(stod(getLat(s)))));
	secKeyLat.insert(i, secCopy);
}
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
void SSClass::insertLon(string s, int rrn) {
	int index;
	SecKeySS secCopy;
	LinkedList<int> copyDup;
		int i;
	for (i = 1; (i < (secKeyLon.getItemCount() + 1)) && (secKeyLon.getEntry(i).getData() < s); i++);
	if (stoi(secKeyLon.getEntry(i).getData()) == static_cast<int>(stod(s))) {
		secCopy = secKeyLon.getEntry(i);
		copyDup = LinkedList<int>(secCopy.getDuplicates());
		copyDup.insert(1, rrn);
		secCopy.setDuplicates(copyDup);
		secKeyLon.replace(i, secCopy);
		return;
	}
	copyDup.insert(1, rrn);
	secCopy.setDuplicates(copyDup);
	secCopy.setData(to_string(static_cast<int>(stod(getLon(s)))));
	secKeyLon.insert(i, secCopy);
}
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
void SSClass::goToLine(fstream& file, unsigned num) {
	goToData(file); //beginning of our data file
	for (int i = 0; i < num - 1; ++i) {
		file.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	//return file;
}
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
void SSClass::goToData(fstream& file) { //puts cursor at the beginning of the data portion of the txt file
	file.seekg(ios::beg);
	string in;
	getline(file, in);
	while (in != "ENDOFHDR")
		getline(file, in);
}
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
string SSClass::getZip(string s) { //use stoi(getZip(s)); to return int value
	string returnValue;
	for (int i = 0; i < ZIPSIZE; i++)
		returnValue[i] = s[ZIPOFFSET + i];
	return returnValue;
}
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
string SSClass::getPlace(string s) {
	string returnValue;
	for (int i = 0; i < PLACESIZE; i++)
		returnValue[i] = s[PLACEOFFSET + i];
	return returnValue;
}
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
string SSClass::getState(string s) {
	string returnValue;
	for (int i = 0; i < STATESIZE; i++)
		returnValue[i] = s[STATEOFFSET + i];
	return returnValue;
}
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
string SSClass::getCounty(string s) {
	string returnValue;
	for (int i = 0; i < COUNTYSIZE; i++)
		returnValue[i] = s[COUNTYOFFSET + i];
	return returnValue;
}
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
string SSClass::getLat(string s) { //use stod(getLat(s)); to return double value
	string returnValue;
	for (int i = 0; i < LATSIZE; i++)
		returnValue[i] = s[LATOFFSET + i];
	return returnValue;
}

/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
string SSClass::getLon(string s) { //use stod(getLon(s)); to return double value
	string returnValue;
	for (int i = 0; i < LONSIZE; i++)
		returnValue[i] = s[LONOFFSET + i];
	return returnValue;
}

/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
string SSClass::createUnusedLine(int next) { //pass in the integer value of the next empty line
	string unusedLine = to_string(next);
	int i;
	for (i = unusedLine.size(); i < CHARINLINE; i++) {
		unusedLine += " ";
	}
	return unusedLine;
}
/*---------------------------------------------------------------------------
	Default constructor
	Preconditions:   None
	Postconditions:
*/
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
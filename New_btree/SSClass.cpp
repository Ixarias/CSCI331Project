#include "SSClass.h"
using namespace std;
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
	indexFile.close();
	//blockRecord.close();
}

/*! Insertion of records into both the index file as well as the linkedlist
    of linkedlists
    /param s string to be inserted
*/
void SSClass::insert(string s) {
	int ne;
	if (nextEmpty == -1) {
		goToLine(indexFile, numRecords);
		indexFile << "\n" << s;
		insertZip(getZip(s), numRecords);
		insertPlace(getPlace(s), numRecords);
		insertState(getState(s), numRecords);
		insertCounty(getCounty(s), numRecords);
		insertLat(getLat(s), numRecords);
		insertLon(getLon(s), numRecords);
		numLinesIndex++;
		return;
	}
	goToLine(indexFile, nextEmpty);
	indexFile >> ne;
	replace(s, nextEmpty);
	insertZip(getZip(s), nextEmpty);
	insertPlace(getPlace(s), nextEmpty);
	insertState(getState(s), nextEmpty);
	insertCounty(getCounty(s), nextEmpty);
	insertLat(getLat(s), nextEmpty);
	insertLon(getLon(s), nextEmpty);
	nextEmpty = ne;
	
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
		results = secKeyZip.search(stoi(s));
	}
	break;
	case 2:
	{
		results = secKeyPlace.search(s);
	}
	break;
	case 3:
	{
		results = secKeyState.search(s);
	}
	break;
	case 4:
	{
		results = secKeyCounty.search(s);
	}
	break;
	case 5:
	{
		results = secKeyLat.search(stoi(s));
	}
	break;
	case 6:
	{
		results = secKeyLon.search(stoi(s));
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
	switch (direction) { //This is a linear search since inserts are not in order.
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
void SSClass::insertZip(string st, int rrn) {	//no sec key matching -> create new one....    match found -> insert at index 1
	int s = stoi(st);
	secKeyZip.addDataToKey(s, rrn);
}

void SSClass::insertPlace(string s, int rrn) {
	secKeyPlace.addDataToKey(s, rrn);
}

void SSClass::insertState(string s, int rrn) {
	secKeyState.addDataToKey(s, rrn);
}

void SSClass::insertCounty(string s, int rrn) {
	secKeyCounty.addDataToKey(s, rrn);
}

void SSClass::insertLat(string st, int rrn) {
	int s = static_cast<int>(stod(st));
	secKeyLat.addDataToKey(s, rrn);
}

void SSClass::insertLon(string st, int rrn) {
	int s = static_cast<int>(stod(st));
	secKeyLon.addDataToKey(s, rrn);
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

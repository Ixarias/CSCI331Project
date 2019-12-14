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
		secKeyZip.Search(stoi(s),1);
	}
	break;
	case 2:
	{
		
	}
	break;
	case 3:
	{
		
	}
	break;
	case 4:
	{
		
	}
	break;
	case 5:
	{
		
	}
	break;
	case 6:
	{
		
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
		copyDup.insert(1, to_string(rrn));
		secCopy.setDuplicates(copyDup);
		secKeyPlace.replace(i, secCopy);
		return;
	}
	copyDup.insert(1, to_string(rrn));
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
		copyDup.insert(1, to_string(rrn));
		secCopy.setDuplicates(copyDup);
		secKeyState.replace(i, secCopy);
		return;
	}
	copyDup.insert(1, to_string(rrn));
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
		copyDup.insert(1, to_string(rrn));
		secCopy.setDuplicates(copyDup);
		secKeyCounty.replace(i, secCopy);
		return;
	}
	copyDup.insert(1, to_string(rrn));
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

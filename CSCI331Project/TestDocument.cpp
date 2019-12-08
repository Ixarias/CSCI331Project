#include <fstream>
#include <iostream>
#include "SSClass.h"

#include "LinkedList.h"
#include "LinkedList.cpp"
#include "Node.h"
#include "Node.cpp"
#include "SecKeySS.h"

using namespace std;

int main(int argc, char* argv[]){
	//LinkedList<string> list;
	SSClass sequence;
	string state;
	char direction;
	string tempS;

	// command line args: insert, remove, modify, display record, display field in record, verify
	if (argc == 1) {
		cout << "Operations are  as follows:\n" << "-help for information\n" << "-o for opening data file\n" << "-i for insert\n" << "-r for remove\n" << "-m for modify\n"
			<< "-dr for display recrod\n" << "-dfr for display field in record\n" << "-v for verify\n" << "-t to run test sequence\n" << "-s enter state, enter direction (N,E,S,W)\n";
	}
	else {
		for (int i = 1; i < argc; i++) {
			string newArgv = argv[i];

			if (newArgv == "-o") {
				//sequence.openFile(argv[i++]);
			}
			else if (newArgv == "-i") {
				//list.insert(unused, argv[i++]);
			}
			else if (newArgv == "-r") {
				//search function 
				//list.remove(position, used, unused);
			}
			else if (newArgv == "-m") {
			
			}
			else if (newArgv == "-dr") {

			}
			else if (newArgv == "-drf") {

			}
			else if (newArgv == "-v") {

			}
			else if (newArgv == "-t") {

			}
			else if (newArgv == "-s") {
				state = argv[i++];
				tempS = argv[i++];
				direction = tempS[0];
				tempS = sequence.returnLine(sequence.directionalSearch(state, direction));
				cout << tempS;
			}
			else if (newArgv == "-help") {
				cout << "Operations are  as follows:\n" << "-help for information\n" << "-i for insert\n" << "-r for remove\n" << "-m for modify\n"
					<< "-dr for display recrod\n" << "-dfr for display field in record\n" << "-v for verify\n" << "-t to run test sequence";
			}
			else {
				cout << "Operations are  as follows:\n" << "-help for information\n" << "-i for insert\n" << "-r for remove\n" << "-m for modify\n"
					<< "-dr for display recrod\n" << "-dfr for display field in record\n" << "-v for verify\n" << "-t to run test sequence";
			}
		}
	}

	  return 0;
}

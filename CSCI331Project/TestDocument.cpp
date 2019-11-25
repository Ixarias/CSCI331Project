#include <fstream>
#include <iostream>
#include "SSClass.h"
#include "LinkedList.h"

using namespace std;

int main(int argc, char** argv[]){
	LinkedList<string> list;
	SSClass sequence;
	unsigned used;
	unsigned unused;
	unsigned endOfHeader


	// command line args: insert, remove, modify, display record, display field in record, verify
	if (argc == 1) {
		cout << "Operations are  as follows:\n" << "-help for information\n" << "-o for opening data file\n" << "-i for insert\n" << "-r for remove\n" << "-m for modify\n"
			<< "-dr for display recrod\n" << "-dfr for display field in record\n" << "-v for verify\n" << "-t to run test sequence";
	}
	else {
		for (int i = 1; i < argc; i++) {
			string newArgv = argv[i];

				if (newArgv == "-o") {
					sequence.openFile(argv[i++]);
				}
				else if (newArgv == "-i"){
					list.insert(unused, argv[i++]);
				}
				else if (newArgv == "-r"){
					//search function 
					list.remove(//position, used, unused);
				}
				else if (newArgv == "-m"){
					list.replace(position, fieldNumber, )
				}
				else if (newArgv == "-dr"){

				}
				else if (newArgv == "-drf"){

				}
				else if (newArgv == "-v"){

				}
				else if (newArgv == "-t"){

				}
				else if (newArgv == "-help"){
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




				/*
					  char str[100];
					  if(sclass.openFile(argv[i++])){
						  ifstream in(argv[i++]);
						  unsigned increment = 0;
						  while(in) {
							in.getline(str, 100);  // delim defaults to '\n'
							if(str == "End of header"){
							increment += 1;
							endOfHeader = 1;
							}
							list.insert(increment, str);
							}
					  in.close();
					  }
					  else{
						cout << "The file entered does not exist";
					  }
					  
					  */
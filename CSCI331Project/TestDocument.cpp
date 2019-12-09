#include <fstream>
#include <iostream>
#include "SSClass.h"

#include "LinkedList.h"
#include "LinkedList.cpp"
#include "Node.h"
#include "Node.cpp"
#include "SecKeySS.h"

using namespace std;

// Function prototype for menu
void menu(uint8_t &);

int main()
{
	
	uint8_t menuSelection = 9;	// allocates the memory for menu selection, and innitile to 0 to display menu

	cout << "\n\nWelcome to CSCI 331 SS Class Program: " << endl;	// welcom message

	// do while loop to call menu after every selection, and display menu when selection is 0
	do
	{
		if(menuSelection == 9)
		{
			//Menu that will be displayed to the user.
			cout << endl << endl;
			cout << "*********************************************************" << endl;
			cout << "*                           Menu\t\t\t*" << endl;
			cout << "*\t0. \tMenu  \t\t\t\t\t*" << endl;
			cout << "*\t1. \tOpen file\t\t\t*" << endl;
			cout << "*\t2. \tInsert  \t\t\t\t\t*" << endl;
			cout << "*\t3. \tRemove \t\t\t\t\t**" << endl;
			cout << "*\t4. \tModify \t\t\t\t\t**" << endl;
			cout << "*\t5. \tDisplay recrod \t\t\t\t\t**" << endl;
			cout << "*\t6. \tDisplay feild in recrod\t\t\t\t\t*" << endl;
			cout << "*\t7. \tVerify \t\t\t\t\t*" << endl;
			cout << "*\t8. \tRun Test Sequence\t\t\t\t\t*" << endl;
			cout << "*\t9. \tSearch state \t\t\t\t\t*" << endl;
			cout << "*\t10. \tQuit\t\t\t\t\t*" << endl;			
			cout << "*********************************************************" << endl;
			cout << endl << endl;
		}
		
		menu(menuSelection);	// Calls menu function and passes menu selection

	}while(menuSelection != 10 );	// if selection is 10 quit the program

	cout << "Thank you for using SS Class program. Have a great day!!\n" << endl;	//good bye message

	return 0;
}

void menu(uint8_t &menuSelection)
{
	string file_name;	// allocates memory for file name
	char direction;

	cout << "Menu Selection: ";		// message to user	
	cin >> menuSelection;			// takes in user input for menuSelection
	cout << endl;					

	switch(menuSelection)
	{
		case 0: 
				break;

		case 1: cout << "Enter a file name: ";
				cin >> file_name; cout << endl;
				//sequence.openFile(file_name); // TODO should param be a string or char* []?
				break;
		
		case 2: cout << "Insert: ";
				//cin >> temp; cout << endl;
				//list.insert();	// TODO add param(s)
				break;
		
		case 3: cout << "remove: ";
				//cin >> temp; cout << endl;
				//list.remove();	// TODO add param(s)
				break;

		case 4: // TODO call modify function
				break;

		case 5: // TODO call Display recrod function
				break;

		case 6: // TODO call Display feild in recrod function
				break;

		case 7: // TODO call Verify function
				break;

		case 8: // TODO call Run Test Sequence function
				break;

		case 9: // TODO call Search state function
				cout << "enter direction N, E, S, or W: ";
				cin >> direction; cout << endl;

				if (direction == 'N' || direction == 'S' || direction == 'E' || direction == 'W')
				{
					// TODO call state search function
				}

				else
				{
					cout << direction << " is not a valid response. please try again. " << endl;
				}
				break;

		case 10: // quit
				break;

		default: cout << "****Please make a valid menu selection. ****" << endl << endl; 
				break;
	}
}
/*	//LinkedList<string> list;
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
*/

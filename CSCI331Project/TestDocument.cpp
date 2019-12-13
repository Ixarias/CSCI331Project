#ifndef INCLUDE
#define INCLUDE

#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

#endif

#include "SSClass.h"

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
	SSClass sequence;
	string file_name;	// allocates memory for file name
	char direction;
	char state;
	string zipCode;
	vector<int> rrnVector;

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
			cout << "Display field in record\n";
			cout << "What is the zip code you would like to know the state and place name of?:";
			cin >> zipCode;
			cout << endl;
//			rrnVector = sequence.search(zipCode, 1);
//			for (int i = 0; i < rrnVector.size(); i++) {
//				cout << sequence.returnLine(rrnVector[i]);
//			}

				break;

		case 7: // TODO call Verify function
				break;

		case 8: // TODO call Run Test Sequence function
				break;

		case 9: // TODO call Search state function
				cout << "enter direction N, E, S, or W: ";
				cin >> direction; cout << endl;
				cout << "enter state";
				cin >> state; cout << endl;

				if (direction == 'N' || direction == 'S' || direction == 'E' || direction == 'W')
				{
//					cout << sequence.returnLine(sequence.directionalSearch(string(1, state), direction));
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

/*
 *Author:    VenkataSaiAbhishek Thurlapati
 *Compiler:  Code Blocks G++
 *Date:      1/23/17
 *Purpose:	 The purpose of the program is to determine
 *Purpose:	 if the user entered employee ID exists within the file and
 *Purpose:	 to calculate the wage of that employee
 */

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>
#include <iomanip>

using namespace std;

//declares all the functions
int getData(int ID[], int rate[]);
int linearSearch(int ID[], int userID, int employNum);
int promptID(int userID, int NUM_RANGE);
int promptHrs(int userHrs);

int main() {

	//Variables
	int ID[1000];
	int rate[1000];
	int userID = 0;
	int userHrs = 0;
	int NUM_RANGE = 999999;
	int comparisons = 0;

	//calls get data method and stores the employ nums in a variable
	int employNum = getData(ID, rate);

	//Displays the actual number of employs
	cout << "Actual Number of employees: " << employNum << endl;
	cout << "---------------------------------" << endl;

	//Calls the methods to prompt the user ID and the Hours and does input validation
	userID = promptID(userID, NUM_RANGE);

	//if user id == 0, then program ends and displays that program ends
	if (userID == 0) {

		cout << "Program Ended.";
		return 0;
	}

	//calls method to prompt  for hours
	userHrs = promptHrs(userHrs);

	//While loop to run the program until user Ends the program with 0
	while (userID != 0) {

		//calls data to get the comparisons and stores it in a variable
		comparisons = linearSearch(ID, userID, employNum);

		//displays user entered values
		cout << "ID = " << userID << " Hours = " << userHrs << endl << endl;

		//if statement to determine if the employee was found or not
		if (comparisons == -1) {
			//displays that employee was not found
			cout << "Employ Not Found." << endl;
			cout << "It took " << employNum << " comparisons." << endl;

			//Calls the methods to prompt the user ID and the Hours and does input validation
			userID = promptID(userID, NUM_RANGE);
			if (userID == 0) {
				cout << "Program Ended.";
				return 0;
			}

			//calls method to prompt  for hours
			userHrs = promptHrs(userHrs);
		} else {
			//displays the employee id, rate, hrs worked, and wages
			cout << "Employee " << userID << ", rate = "
					<< rate[comparisons - 1] << ", hours = " << userHrs
					<< ", wage = " << (rate[comparisons - 1] * userHrs) << endl;
			cout << "It took " << comparisons << " comparisons" << endl;

			//Calls the methods to prompt the user ID and the Hours and does input validation
			userID = promptID(userID, NUM_RANGE);
			if (userID == 0) {
				cout << "Program Ended.";
				return 0;
			}

			//calls method to prompt  for hours
			userHrs = promptHrs(userHrs);
		}
	}

	return 0;
}

//This method takes in a ID array and a rate array and
//reads the IDs and the hrs from the file an puts them in parallel arrays
//It return the actual number of employees
int getData(int ID[], int rate[]) {
	//declares file object
	fstream file("employeeFile.txt", ios::in | ios::out);
	string line;

	if (file.is_open()) {

		int linenum = 0;

		//while loop to go through the file till it ends
		while (!file.eof()) {
			//goes to next line
			getline(file, line);

			//for loop to go through the file to read each ID and and Rate value
			//and put them in their respective arrays
			for (int i = 0; i < 5; i++) {
				ID[i + linenum * 5] = atoi(line.substr(i * 15, 8).c_str());
				rate[i + linenum * 5] = atoi(line.substr(i * 15 + 8 + 3, 2).c_str());

			}

			//increments line# by 1
			++linenum;

		}

		//closes the file
		file.close();

		//returns the actual number of employees
		return linenum * 5;

	}

	//displays that file has not opened properly
	cout << "File not opened successfully." << endl;
	return -1;
}

//function that takes in the array of employee IDs, the userID, and the actual number of employees
//to perform a linear search through the array to see if userID is in the file
int linearSearch(int ID[], int userID, int employNum) {

	int i = 0;

	//for loop to go through the array
	for (i = 0; i < employNum; i++) {
		if (ID[i] == userID) {
			return i + 1;
		}
	}

	return -1;
}

//function that takes in the userHrs and prompts the user and performs input validation
int promptHrs(int userHrs) {
	//prompts user for the an employee ID and number of hours worked
	cout << "Input the number of hours: ";
	cin >> userHrs;

	//while loop to determine if the user's input is valid
	while (userHrs < 0) {
		cout << "Invalid entry. Hours must be greater than 0. Please reenter: ";
		cin >> userHrs;
	}

	return userHrs;
}

//function that takes in the userID and the num_range to do input validation and prompt for the user ID
int promptID(int userID, int NUM_RANGE) {
	//prompts user for the an employee ID and number of hours worked
	cout << "\nInput employee's ID, 0 to quit: ";
	cin >> userID;

	//while loop to determine if the user's input is valid
	while (userID < 0 || userID > NUM_RANGE) {
		cout
				<< "Invalid entry. ID must be between 1 and 999999. Please reenter: ";
		cin >> userID;
	}

	return userID;
}



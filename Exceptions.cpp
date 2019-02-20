// Author: Alexander Jenkins
// ID: 9884664
// The .cpp file for Exception.h, all except the templates exception handling definitions are here

#include"Exceptions.h"
#include"Functions.h"
#include<fstream>
#undef max

// Definition for the exception NotYesorNo, checks the user inputs only y or n
Exceptions::NotYesorNo::NotYesorNo(char &ch, istream &is) throw() {
	cerr << "ERROR: The value entered is not an option." << endl; // Display the error message
	while (!(ch == 'n' || ch == 'y')) { // While the input still fails
		cout << "Please enter either y/n: " << endl;
		is.clear(); // clears the input stream
		is.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores what is in the input stream up to a new line
		is >> ch; // input a new value
		cout << endl;
	}
}

// Definition for the exception DateFailure, checks the user inputs the date stamp in the correct format
Exceptions::DateFailure::DateFailure(string &date, istream &is) throw() {
		cerr << "ERROR: The date you have entered must be in the past and of format DD/MM/YYYY." << endl;
		cout << "Please try again: ";
		is.clear(); // clears the input stream
		is.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores what is in the input stream up to a new line
		is >> date; // input a new value 
		adding_measurement_functions::check_date_UI(date); // check the date
}


// Definition for the exception DateFailure, for the input file stream, checks correct date, if not clear the stream
Exceptions::DateFailure::DateFailure(ifstream &fs, int &line_num) throw() {
	cerr << "ERROR: The date on line " << line_num <<" is not in the past and of the format DD/MM/YYYY." << endl;
	cout << "Skipping the line and continuing." << endl;
	fs.clear(); // Clear the stream
	fs.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore what is left in the stream until a new line
	cout << endl;
}

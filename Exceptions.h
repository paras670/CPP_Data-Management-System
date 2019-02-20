// Author: Alexander Jenkins
// ID: 9884664
// A .h file to declare my own exceptions by inheriting from the exception class and declaring new parameterised constructors

#ifndef EXCEPTION_INCLUDE
#define EXCEPTION_INCLUDE

#include<exception>
#include<iostream>
#include<typeinfo>
#include<iomanip>
#include<limits>
#include<string>

using namespace std;

namespace Exceptions {
	// Define a namespace for all the exceptions, used to define the template classes in the same header file

	template <class NIR> class NotInRange : exception {
		// A template class for a new exception that checks if the value is in the range provided, derived from exception
	public:
		// Parameterised constructor which will take a value and check if it lies within the lower and upper limits provided
		NotInRange(NIR &val, const NIR &lower, const NIR &upper) throw(); // Deals with user input
	};


	template <class TF> class TypeFailure : exception {
		// A template class for a new exception which will check the value inputted is of the correct type
	public:
		TypeFailure(TF &val, istream &is) throw(); // Deal with user input
		TypeFailure(TF &val, ifstream &fs, int &line_num) throw(); // Overloading the TypeFailure parameterised constructor to deal with file input
	};

	class NotYesorNo : exception {
		// A class derived from exception, which will check if the user inputs y or n for yes or no
	public:
		NotYesorNo(char &ch, istream &is) throw(); // Deal with user input
	};

	class DateFailure : exception {
		// A class derived from exception, which will check if the date is inputted in the format DD/MM/YYYY
	public:
		DateFailure(string &date, istream &is) throw(); // Deal with user input
		DateFailure(ifstream &fs, int &line_num) throw(); // Overloading to deal with file input
	};
}

//// Exception definitions ////

using namespace Exceptions;

template <class NIR> NotInRange<NIR>::NotInRange(NIR &val, const NIR &lower, const NIR &upper) throw() {
	cerr << "ERROR: The value entered is not in the range required." << endl; // Display the error message
	cout << "Please enter a value in the range " << lower << " to " << upper << ": ";
	while (val < lower || val > upper) { // While still not in the range
		// A try catch statement to catch the exception for the wrong type of value required
		try {
			cin >> val; // User inputs a new value
			if (cin.fail()) {
				throw TypeFailure<NIR>(val, cin); // Throw the type failure exception if the input is of the wrong type
			}
		}
		catch (TypeFailure<NIR>) { // Catch the wrong type failure exception
		}
		cout << endl;
	}
}

template <class TF> TypeFailure<TF>::TypeFailure(TF &val, istream &is) throw() { // For user input
	cerr << "ERROR: The value entered is not of the correct type." << endl; // Display the error message
	while (!(is.good())) { // While the input still fails
		cout << "Please enter a value of type " << typeid(TF).name() << ": "; // Display the specific type required
		is.clear(); // clears the input stream
		is.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores what is in the input stream up to a new line
		is >> val; // input a new value 
		cout << endl;
	}

}

template <class TF> TypeFailure<TF>::TypeFailure(TF &value, ifstream &fs, int &line_num) throw() { // For file input
	cerr << "ERROR: There is a value entered at line " << line_num << " which is of the wrong type." << endl;
	cout << "Should be of type " << typeid(TF).name() <<". Skipping the line and continuing." << endl;
	fs.clear(); // Clear the stream
	fs.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore what is left in the stream until a new line
	cout << endl;
}
#endif

// Author: Alexander Jenkins
// ID: 9884664
// A .h file for the functions used in the program

#ifndef FUNCTIONS_INCLUDE
#define FUNCTIONS_INCLUDE

#include<string>
#include"Exceptions.h"
#include<Windows.h>
#include<Shlwapi.h>
#include"Measurement.h"
#include"Experiment.h"
#include<fstream>
#include<memory>

using namespace std;

// A namespace for the different types of functions, helping for legibility and remembering
namespace adding_measurement_functions {

	// A function to check the user inputted date and return it if correct format (DD/MM/YYYY) 
	const string check_date_UI(string new_date); // UI = User input, this function will not continue until the user corrects for any mistakes

	// A function to check the date read in from a file, returns true if date is of the correct format (DD/MM/YYYY) 
	const bool check_date_FI(string new_date); // FI = File input, will continue a mistake is identified, but displaying an error message

	const string working_directory(); // A function to return a string for the working directory which the user is in

	shared_ptr<Measurement> add_meas_type_manually(const int &type_chosen); // A function to take the option number on the add measurement menu and return a pointer of the Measurement abstract class

}

namespace exception_handling_functions {
	// A template function to check that the option is of the right type within a vector specified for any vector 
	template <class T> void option_check(int &option, const vector<T> &possible_options);
}

// Definition of option_check
template <class T> void exception_handling_functions::option_check<T>(int &option, const vector<T> &possible_options) {
	// A template function which will check if option is in the range of the vector of possible options
	// Crucial difference between this table option check and menu option
	try {
		try {
			cin >> option;
			if (cin.fail()) { throw TypeFailure<int>(option, cin); } // Throw TypeFailure exception, check initially the value inputted is the right type
			if ((option < 1) || (option > possible_options.size())) { throw NotInRange<int>(option, 1, possible_options.size()); } // Throw not in range exception
		}
		catch (TypeFailure<int>) {
			// Catch the type failure exception. Check also in the range needed, if not throw an exception NotInRange to be caught by the outer catch statement
			if ((option < 1) || (option > possible_options.size())) { throw NotInRange<int>(option, 1, possible_options.size()); }
		}
		catch (NotInRange<int>) {
			// Catch the not in range exception
		}
	}
	catch (NotInRange<int>) {} // Catch the thrown exception from within the typeFailure catch
	cout << endl;
}


#endif

// Author: Alexander Jenkins
// ID: 9884664
// A .h file for the functions used in the program

#include"Functions.h"
#include"Exceptions.h"
#include"Interface.h"
#pragma comment(lib, "shlwapi.lib") // Include the shlawpi.lib, prevents linking errors when finding the directory
#undef max

// Function definitions for the adding_measurement_functions namespace

const string adding_measurement_functions::check_date_UI(string new_date) {
	// A function to take a string, split it up based on day/month/year and check each is ok 
	try {
		if (!(new_date.size() == 10)) { throw DateFailure(new_date, cin); } // If the wrong number of characters are entered throw

		// Check that the date is of the correct format
		const string delimiter = "/";
		string::iterator start_days = new_date.begin(); // iterator at beginning of string
		size_t finish_days = new_date.find(delimiter); // gives position of first occurrence of delimiter
		if (finish_days == new_date.npos) {
			throw DateFailure(new_date, cin); // "/" does not exist in the string
		}
		else {
			string day = new_date.substr(0, finish_days); // Extracts month part from date string 
			if (!(isdigit(day[0]) || isdigit(day[1])) || day.size() > 2) { throw DateFailure(new_date, cin); }
			int day_int = stoi(day); // Now we know they're both digits, convert to integer
			// Check the days are of the allowed form, allow only 31 days
			if (day_int < 1 || day_int > 31) { throw DateFailure(new_date, cin); } // No days larger than 31
		}

		// Day part of date has been successfully tested
		new_date = new_date.substr(finish_days + 1); // Removes the day part from the date string

		string::iterator start_month = new_date.begin(); // iterator at beginning of string
		size_t finish_month = new_date.find(delimiter); // gives position of first occurrence of delimiter
		if (finish_month == new_date.npos) {
			throw DateFailure(new_date, cin); // "/" does not exist in the string
		}
		else {
			string month = new_date.substr(0, finish_month); // Extracts month part from date string 
			if (!(isdigit(month[0]) || isdigit(month[1]) || month.size() > 2)) { throw DateFailure(new_date, cin); }
			int month_int = stoi(month); // Now we know they're both digits, convert to integer
			// Check the months are of the allowed form, allow only 12 months
			if (month_int < 1 || month_int > 12) { throw DateFailure(new_date, cin); }
		}

		// Month part of date has been successfully tested
		new_date = new_date.substr(finish_month + 1); // Removes the month part from the date string

		string year = new_date.substr(0, new_date.size()); // Extracts month part from date string 
		if (!(isdigit(year[0]) || isdigit(year[1]) || isdigit(year[2]) || isdigit(year[3])) || year.size() > 4) { throw DateFailure(new_date, cin); }
		int year_int = stoi(year); // Now we know they're all digits, convert to integer
		// Check the year is of the allowed form YYYY
		if (year_int < 0 || year_int > 2018) { throw DateFailure(new_date, cin); } // Ensure the year is not greater than this year, not possible

		// The date has been successfully tested if it makes it to this point, return the checked date
		return new_date;
	}
	catch (DateFailure) { return new_date; }
}

const bool adding_measurement_functions::check_date_FI(string new_date) {

	if (!(new_date.size() == 10)) { return false; } // If the wrong number of characters are entered throw

	// Check that the date is of the correct format
	const string delimiter = "/";
	string::iterator start_days = new_date.begin(); // iterator at beginning of string
	size_t finish_days = new_date.find(delimiter); // gives position of first occurrence of delimiter
	if (finish_days == new_date.npos) {
		throw DateFailure(new_date, cin); // "/" does not exist in the string
	}
	else {
		string day = new_date.substr(0, finish_days); // Extracts month part from date string 
		if (!(isdigit(day[0]) || isdigit(day[1])) || day.size() > 2) { return false; }
		int day_int = stoi(day); // Now we know they're both digits, convert to integer
		// Check the days are of the allowed form, allow only 31 days
		if (day_int < 1 || day_int > 31) { return false; } // No days larger than 31
	}

	// Day part of date has been successfully tested
	new_date = new_date.substr(finish_days + 1); // Removes the day part from the date string

	string::iterator start_month = new_date.begin(); // iterator at beginning of string
	size_t finish_month = new_date.find(delimiter); // gives position of first occurrence of delimiter
	if (finish_month == new_date.npos) {
		throw DateFailure(new_date, cin); // "/" does not exist in the string
	}
	else {
		string month = new_date.substr(0, finish_month); // Extracts month part from date string 
		if (!(isdigit(month[0]) || isdigit(month[1]) || month.size() > 2)) { return false; }
		int month_int = stoi(month); // Now we know they're both digits, convert to integer
		// Check the months are of the allowed form, allow only 12 months
		if (month_int < 1 || month_int > 12) { return false; }
	}

	// Month part of date has been successfully tested
	new_date = new_date.substr(finish_month + 1); // Removes the month part from the date string

	string year = new_date.substr(0, new_date.size()); // Extracts month part from date string 
	if (!(isdigit(year[0]) || isdigit(year[1]) || isdigit(year[2]) || isdigit(year[3])) || year.size() > 4) { return false; }
	int year_int = stoi(year); // Now we know they're all digits, convert to integer
	// Check the year is of the allowed form YYYY
	if (year_int < 0 || year_int > 2018) { return false; } // Ensure the year is not greater than this year, not possible

	// The date has been successfully tested if it makes it to this point, return true
	return true;
}

const string adding_measurement_functions::working_directory() {
	char path[MAX_PATH] = ""; // Define the character array path, of length MAX_PATH
	GetCurrentDirectoryA(MAX_PATH, path); 
	PathAddBackslashA(path);
	return path; // Return the working directory
}

shared_ptr<Measurement> adding_measurement_functions::add_meas_type_manually(const int &type_chosen) {
	// Will take the option number in the add measurement menu
	// Returns a shared_ptr to the base class

	// The values needed to construct the measurement
	string new_date;
	double new_value, new_error, new_syst_error;

	string option_string; // A string relating the option number to the type of measurement 
	// Assign the option string its value, used for displaying type specific outputs
	if (type_chosen == 1) { option_string = "LENGTH"; }
	else if (type_chosen == 2) { option_string = "TIME"; }
	else if (type_chosen == 3) { option_string = "MASS"; }
	else if (type_chosen == 4) { option_string = "AMOUNT"; }
	else if (type_chosen == 5) { option_string = "CURRENT"; }
	else { option_string = "TEMPERATURE"; }

	cout << "Please insert a date stamp for the "<<option_string<<" (DD/MM/YYYY):" << endl; // User inputs a date stamp
	cin >> new_date; // Set new_date from the user input
	check_date_UI(new_date); // Check the date using the check_date function

	cout << "Please insert a VALUE for the "<< option_string<<": "; // User input for the value
	try {
		cin >> new_value;
		if (cin.fail()) { throw TypeFailure<double>(new_value, cin); } // Ensure the value is of type double
	}
	catch (TypeFailure<double>) {}
	cout << endl;

	cout << "Please insert an ERROR for the " << option_string << ": "; // User input for the values error
	try {
		cin >> new_error;
		if (cin.fail()) { throw TypeFailure<double>(new_error, cin); } // Ensure double type
	}
	catch (TypeFailure<double>) {}
	cout << endl;

	cout << "Please insert a SYSTEMATIC ERROR for the " << option_string << " (if none enter 0): "; // User input for the systematic error
	try {
		cin >> new_syst_error;
		if (cin.fail()) { throw TypeFailure<double>(new_syst_error, cin); } // Ensure double type
	}
	catch (TypeFailure<double>) {}
	cout << endl;


	// Return the shared pointer creater for a new objects initialised by the passed arguments
	if (type_chosen == 1) { return make_shared<Length>(new_date, new_value, new_error, new_syst_error); }
	else if (type_chosen == 2) { return make_shared<Time>(new_date, new_value, new_error, new_syst_error); }
	else if (type_chosen == 3) { return make_shared<Mass>(new_date, new_value, new_error, new_syst_error); }
	else if (type_chosen == 4) { return make_shared<Amount>(new_date, new_value, new_error, new_syst_error); }
	else if (type_chosen == 5) { return make_shared<Current>(new_date, new_value, new_error, new_syst_error); }
	else { return make_shared<Temperature>(new_date, new_value, new_error, new_syst_error); }
}

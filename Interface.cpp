// Author: Alexander Jenkins
// ID: 9884664
// The .cpp file for Interface.h

#include "Interface.h"

// MENU CLASS DEFINITIONS

Menu::Menu(string new_title, vector<string> new_options) { // Parameterised constructor
	title = new_title; // Set the title of the menu 
	options = new_options; // Set the options of the menu

	// Add an exit program option to the main menu
	if (title == "MAIN MENU") { options.push_back("EXIT PROGRAM"); }
	else {
		// If not on the main menu, ensure the last option is to return to the previous menu
		options.push_back("RETURN TO PREVIOUS MENU"); 
	}
}

Menu::~Menu(){
	cout << "Menu deleted from memory." << endl; // Destructor called
}

const vector<string> Menu::get_all_options() { return options; }

ostream & operator<<(ostream &os, const Menu &m) {
	// A friend of the Menu class, to overload the << insertion operator, to output menus

	int option_num{ 1 }; // Define option_num, to assign a number to each option

	os << endl;
	os << "\t\t * * * * * * * * * * * * * * * * * * * * * * \t\t" << endl;
	os << "\t\t                                             \t\t" << endl;
	os << "\t\t  \t  | " << m.title << " |" << endl;
	os << "\t\t                                             \t\t" << endl;
	// Iterate over the vector of options, printing them in order of input
	for (auto iterator = m.options.begin(); iterator != m.options.end(); ++iterator) {
		os << "\t\t  \t  [" << option_num << "] " << *iterator << endl;
		option_num++; // Add 1 to the option number upon every iteration
	}
	os << "\t\t                                             \t\t" << endl;
	os << "\t\t * * * * * * * * * * * * * * * * * * * * * * \t\t" << endl;
	os << endl;

	return os;
}



// TABLE CLASS DEFINITIONS

// Parameterised constructor
Table::Table(string new_title, vector<shared_ptr<Measurement>> new_measurements) {
	title = new_title; // Set the title of the table, will be the name of the experiment
	measurements = new_measurements; // Set the measurements the table will contain
}

// Destructor
Table::~Table() {
	cout << "Table Deleted from memory." << endl;
}

// Overload the insertion operator for tables
ostream & operator<<(ostream&os, const Table &t) {
	// Overload the << insertion operator, to output tables
	
	// Define formatting functions to correctly display the table, setting the sizes of each column
	const int key_size{ 4 }, meas_size{ 12 }, units_size{ 6 }, date_size{ 11 }; // Key for a measurement, measurement type, units and date column sizes
	const int val_size{ 13 }, err_size{ 13 }, syst_err_size{ 15 }; // Value, error and systematic error column sizes
	const int table_size = key_size + meas_size + units_size + date_size + val_size + err_size + syst_err_size + 2; // The total table width (+2 for the sides added)
	int key{ 1 }; // A key for each measurement, used for user deleting and modifying measurements
	os << left; // Set the allignment to the left

	// Output the table
	os << t.title << endl;
	os << setfill('_') << setw(table_size) << "." << setw(1) << "." << endl; // Print the top of the table
	os << setfill(' ') << setw(key_size) << "|Key" << setw(meas_size) << "|Measurement" << setw(units_size) << "|Units" << setw(date_size) << "|Date" << setw(val_size) << "|Value" << setw(err_size) << "|Error" << setw(syst_err_size) << "|Systematic Error" << setw(1) << "|" << endl; // Print the table headings
	for (auto iter_info = t.measurements.begin(); iter_info != t.measurements.end(); ++iter_info) { // Iterate over the vector of measurements given for the table
		os << setfill('-') << setw(key_size) << "|" << setw(meas_size) << "|" << setw(units_size) << "|" << setw(date_size) << "|" << setw(val_size) << "|" << setw(err_size) << "|" << setw(syst_err_size + 2) << "|" << setw(1) << "|" << endl; // Print the measurement information within a box
		os << setfill(' ') << "|" << setw(key_size -1) << key << "|" << setw(meas_size - 1) << (*iter_info)->name() << "|" << setw(units_size - 1) << (*iter_info)->units() << "|" << setw(date_size - 1) << (*iter_info)->get_date() << "|" << setw(val_size - 1) << (*iter_info)->get_value() << "|" << setw(err_size - 1) << (*iter_info)->get_error() << "|" << setw(syst_err_size + 1) << (*iter_info)->get_syst_error() << "|" << endl;
		key++; // Add one to the key
	}
	os << setfill('-') << setw(table_size) << "." << setw(1) << "." << endl; // Print the bottom of the table

	return os;
}


// Table_Combined_Error CLASS DEFINITIONS

// Inherit the parameterised constructor from Table class
Table_Combined_Error::Table_Combined_Error(string new_title, vector<shared_ptr<Measurement>> new_measurements) : Table::Table(new_title, new_measurements) {}

// Destructor
Table_Combined_Error::~Table_Combined_Error() {}

// Overload the insertion operator for tables without a systematic error (used when the combined error has been used)
ostream & operator<<(ostream&os, const Table_Combined_Error &t) {
	// Overload the << insertion operator, to output tables without a combined error

	// Define formatting functions to correctly display the table, setting the sizes of each column
	const int meas_size{ 17 }, units_size{ 6 }, date_size{ 11 }; // Measurement type, units and date column sizes
	const int val_size{ 15 }, err_size{ 15 }; // Value and combined error column sizes
	const int table_size = meas_size + units_size + date_size + val_size + err_size; // The total table width (+2 for the sides added)

	os << left; // Set the allignment to the left

	// Output the table
	os << t.title << " with combined errors." << endl;
	os << setfill('_') << setw(table_size) << "." << setw(1) << "." << endl; // Print the top of the table
	os << setfill(' ') << setw(meas_size) << "|Measurement Type" << setw(units_size) << "|Units" << setw(date_size) << "|Date" << setw(val_size) << "|Value" << setw(err_size) << "|Combined Error" << setw(1) << "|" << endl; // Print the table headings, now changed to combined error
	for (auto iter_info = t.measurements.begin(); iter_info != t.measurements.end(); ++iter_info) { // Iterate over the vector of measurements given for the table
		os << setfill('-') << setw(meas_size) << "|" << setw(units_size) << "|" << setw(date_size) << "|" << setw(val_size) << "|" << setw(err_size) << "|" << setw(1) << "|" << endl; // Print the measurement information within a box, now only up to the combined error 
		os << setfill(' ') << "|" << setw(meas_size - 1) << (*iter_info)->name() << "|" << setw(units_size - 1) << (*iter_info)->units() << "|" << setw(date_size - 1) << (*iter_info)->get_date() << "|" << setw(val_size - 1) << (*iter_info)->get_value() << "|" << setw(err_size - 1) << (*iter_info)->combine_error() << "|" << endl;
	}
	os << setfill('-') << setw(table_size) << "." << setw(1) << "." << endl; // Print the bottom of the table

	return os;
}
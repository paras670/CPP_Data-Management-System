// Author: Alexander Jenkins
// ID: 9884664
// This file is the definitions for the declarations made in 'Experiment.h', includes all the functionality of each experiment

#include"Experiment.h"
#include"Exceptions.h"
#include"Interface.h"
#include"Functions.h"
#include<fstream>
#include<cmath>

#undef max // Undefine max

Experiment::Experiment(){
	measurements.clear();
}

Experiment::Experiment(string new_name) {
	name = new_name; // Set the value for the name of the experiment
	measurements.clear(); // Ensure the measurements are cleared
}

Experiment::~Experiment(){
	measurements.clear();
	cout << "Experiment deleted from memory." << endl;
}



const void Experiment::add_measurements() {

	// Create an add measurement menu
	vector<string> add_measurment;
	// Push back the options onto the vector of options
	add_measurment.push_back("LENGTH"); // option 1 (element 0 + 1)
	add_measurment.push_back("TIME"); // option 2
	add_measurment.push_back("MASS"); // option 3
	add_measurment.push_back("AMOUNT"); // option 4
	add_measurment.push_back("CURRENT"); // option 5
	add_measurment.push_back("TEMPERATURE"); // option 6
	Menu add_measurment_menu("ADD A MEASUREMENT", add_measurment);

	int option_add_meas;
	do {
		cout << add_measurment_menu << endl; // Display the menu
		cout << "Please enter an option: "; // Enter an option

		// Exception handling
		exception_handling_functions::option_check(option_add_meas, add_measurment_menu.get_all_options()); // Check the input

		switch (option_add_meas) {
		case 1:
			// Adding length measurements
			how_to_add_meas(option_add_meas); // Display the adding measurements by file or by manual input menu
			break;

		case 2:
			// Adding time measurements
			how_to_add_meas(option_add_meas);
			break;

		case 3:
			// Adding mass measurements
			how_to_add_meas(option_add_meas);
			break;

		case 4:
			// Adding amount measurements
			how_to_add_meas(option_add_meas);
			break;

		case 5:
			// Adding current measurements
			how_to_add_meas(option_add_meas);
			break;

		case 6:
			// Adding temperature measurements
			how_to_add_meas(option_add_meas);
			break;

		case 7:
			cout << "\t\t ==========================================" << endl;
			cout << "\t\t       Returning to the previous menu.     " << endl;
			cout << "\t\t ==========================================" << endl;
			break;

		default:
			cout << "Please enter a value between 1 and " << add_measurment.size() + 1 << "." << endl;
			break;

		}
	} while (option_add_meas != 7); // While not returning to the main menu, display the add measurement menu again
}

const void Experiment::how_to_add_meas(const int type_chosen) {
	// A void function which will display and deal with a menu for adding a measurement either by file or manually

	string option_string, options_units; // A string relating the option number to the type of measurement and its units

										 // Assign the option string its value, used for displaying type specific outputs
	if (type_chosen == 1) { option_string = "LENGTH"; options_units = "METERS"; }
	else if (type_chosen == 2) { option_string = "TIME"; options_units = "SECONDS"; }
	else if (type_chosen == 3) { option_string = "MASS"; options_units = "KILOGRAMS"; }
	else if (type_chosen == 4) { option_string = "AMOUNT"; options_units = "MOLES"; }
	else if (type_chosen == 5) { option_string = "CURRENT"; options_units = "AMPS"; }
	else { option_string = "TEMPERATURE"; options_units = "KELVIN"; }

	// Create an add measurement by file or manually menu
	vector<string> fileORman;
	fileORman.push_back("INPUT FROM FILE");
	fileORman.push_back("INPUT MANUALLY");
	Menu fileORman_menu("ADD A MEASUREMENT", fileORman);

	cout << "You have chosen to add a " << option_string << " measurement." << endl;
	cout << "Please ensure you use the SI unit of " << options_units << "." << endl;
	cout << endl;

	int option_fileORman; // Define option as an integer
	do {
		cout << fileORman_menu << endl; // Display the menu
		cout << "Please enter an option: "; // Enter an option

		// Exception handling
		exception_handling_functions::option_check(option_fileORman, fileORman_menu.get_all_options()); // Check the input

		switch (option_fileORman) {
		case 1:
			// The user has chosen to add measurements manually
			add_meas_file(type_chosen); // Call the add_meas_file experiment member function to add measurements by reading from a chosen file, for the time
			break;

		case 2:
			// The user has chosen to add measurements manually
			add_meas_manually(type_chosen); // Call the add_meas_manually experiment member function to add measurements manually (user input), for the time option number
			break;

		case 3:
			cout << "\t\t ==========================================" << endl;
			cout << "\t\t       Returning to the previous menu.     " << endl;
			cout << "\t\t ==========================================" << endl;
			break;

		default:
			cout << "Please enter a value between 1 and " << fileORman.size() + 1 << "." << endl;
			break;
		}
	} while (option_fileORman != 3);
}

const void Experiment::add_meas_manually(const int type_chosen) {
	// A function to add measurements manually, will store measurements in the experiment and also keep adding if required

	string option_string; // A string relating the option number to the type of measurement 
	// Assign the option string its value, used for displaying type specific outputs
	if (type_chosen == 1) { option_string = "LENGTH"; }
	else if (type_chosen == 2) { option_string = "TIME"; }
	else if (type_chosen == 3) { option_string = "MASS"; }
	else if (type_chosen == 4) { option_string = "AMOUNT"; }
	else if (type_chosen == 5) { option_string = "CURRENT"; }
	else { option_string = "TEMPERATURE"; }

	cout << "You have chosen to manually input your " << option_string << " measurements." << endl;
	cout << endl;

	bool add_again_bool(true);
	do {
		// Add the measurement to the measurement vector in the experiment
		measurements.push_back(adding_measurement_functions::add_meas_type_manually(type_chosen)); // Pushback the constructed Time measurement

		cout << "\t\t ==========================================" << endl;
		cout << "\t\t            Measurement added.             " << endl;
		cout << "\t\t ==========================================" << endl;
		cout << endl;

		cout << "Would you like to add another "<<option_string<<" measurement? (y/n)" << endl;
		char add_again_option;
		try {
			cin >> add_again_option;
			if (cin.fail()) { throw TypeFailure<char>(add_again_option, cin); }
			if (!(add_again_option == 'n' || add_again_option == 'y')) { throw NotYesorNo(add_again_option, cin); }
		}
		catch (TypeFailure<char>) {}
		catch (NotYesorNo) {}
		cout << endl;

		if (add_again_option == 'n') { add_again_bool = false; } // If the user does not want to add another length measurement, exit do while loop

	} while (add_again_bool);

	cout << "\t\t ===========================================" << endl;
	cout << "\t\t             Measurement/s saved            " << endl;
	cout << "\t\t ===========================================" << endl;
	cout << "\t\t    Returning to the add measurement menu." << endl;
	cout << "\t\t ===========================================" << endl;
}

const void Experiment::add_meas_file(const int type_chosen){
	// A function to add a measurements from a file

	ifstream input_file; // Define input file to read data into
	string file_name; // Define the file name to be read in
	int line_num{ 0 }; // Initialise the line number for the lines read in for a file
	bool return_to_prev(false); // Initialise return_to_prev as false, when true shall return to the main menu
	bool try_again_bool(true); // Initialise the try again bool as true

	string option_string; // A string relating the option number to the type of measurement 
	// Assign the option string its value, used for displaying type specific outputs
	if (type_chosen == 1) { option_string = "LENGTH"; }
	else if (type_chosen == 2) { option_string = "TIME"; }
	else if (type_chosen == 3) { option_string = "MASS"; }
	else if (type_chosen == 4) { option_string = "AMOUNT"; }
	else if (type_chosen == 5) { option_string = "CURRENT"; }
	else { option_string = "TEMPERATURE"; }

	// Input from file
	cout << "You have chosen to input your "<< option_string<<" measurements from a file." << endl;
	cout << endl;
	cout << "================================================================================" << endl;
	cout << "  Before starting please ensure your files are saved in the working directory:  " << endl;
	cout << " \t " << adding_measurement_functions::working_directory() << endl; // Output the users working directory
	cout << endl;
	cout << "   Please save your " << option_string << " measurements as a TAB DELIMITED .TXT FILE, i.e." << endl;
	cout << "            DD/MM/YYYY      VALUE      ERROR      SYST_ERROR(if any).           " << endl;
	cout << endl;
	cout << " NOTE TO THE MARKER: Example file saved as 'test.txt'" << endl;
	cout << "================================================================================" << endl;

	// Ask user for the name of the file to be opened
	do {
		cout << "Please enter the name of the file you want to be opened:" << endl;
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> file_name;

		input_file.open(file_name); // Open file 
		cout << endl;

		// Notify user that the file has successfully been opened
		if (input_file.good()) { cout << "The file '" << file_name << "' has been opened successfully." << endl; try_again_bool = false; cout << endl; }
		else { // Notify the user that there is no file with this name in the directory
			cerr << "Error: There is no file named '" << file_name << "' in the directory." << endl; // Display error message
			cout << "Would you like to try again (y/n): "; // Give the option to input the file name again else return to the previous menu
			char try_again_option;
			try {
				cin >> try_again_option; // User input
				if (cin.fail()) { throw TypeFailure<char>(try_again_option, cin); } // If the input is not of type character, retry
				if (!(try_again_option == 'n' || try_again_option == 'y')) { throw NotYesorNo(try_again_option, cin); } // If the input is not y or n retry
			}
			catch (TypeFailure<char>) {} // Catch these thrown exceptions
			catch (NotYesorNo) {}
			cout << endl;

			if (try_again_option == 'n') { return_to_prev = true; try_again_bool = false; } // Add 1 to N_break. If the user doesn't wish to try again, break and return to the previous menu
		}
	} while (try_again_bool); // Loops while the user wishes to try and input the file again

	if (return_to_prev == true) {
		// If the user wants to return to the previous menu, break the code
		cout << "\t\t ===========================================" << endl;
		cout << "\t\t   Returning to the add measurement menu." << endl;
		cout << "\t\t ===========================================" << endl;
		return;
	}

	// Alert the user that reading from the file has begun
	cout << "\t\t ===========================================" << endl;
	cout << "\t\t              Reading has begun.            " << endl;
	cout << "\t\t ===========================================" << endl;
	cout << endl;
	cout << "\t\t ================ Error log ================" << endl;
	cout << endl;

	// Begin reading from file
	while (input_file.good() && !input_file.eof()) {

		// Parameters defined to be set from the file line
		string new_date;
		double new_value, new_error, new_syst_error;
		bool valid_date(true);

		try {
			if (input_file.peek() == '\n') {
				// The next line is empty
				new_syst_error = 0;
				input_file.clear(); // Clear the stream
				input_file.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			line_num++; // Add one to the line number

			input_file >> new_date;
			if (new_date.empty()) { break; } // If there is no date, then either file is empty or at the end of the file, break the loop
			if (adding_measurement_functions::check_date_FI(new_date) == false) { throw DateFailure(input_file, line_num); } // Check the date is of the right format

			input_file >> new_value; // check if of type double if not throw an exception
			if (!input_file.good()) { throw TypeFailure<double>(new_value, input_file, line_num); }

			input_file >> new_error; // check if of type double if not throw an exception
			if (!input_file.good()) { throw TypeFailure<double>(new_error, input_file, line_num); }

			if (input_file.peek() == '\n') {
				new_syst_error = 0; // No systematic error given, set equal to zero
				input_file.clear(); // Clear the stream
				input_file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore what is left in the stream until the next line

				// Pushback the relevant type of measurement on the vector of measurements, without a systematic error
				if (type_chosen == 1) { measurements.push_back(make_shared<Length>(new_date, new_value, new_error, new_syst_error)); }
				else if (type_chosen == 2) { measurements.push_back(make_shared<Time>(new_date, new_value, new_error, new_syst_error)); }
				else if (type_chosen == 3) { measurements.push_back(make_shared<Mass>(new_date, new_value, new_error, new_syst_error)); }
				else if (type_chosen == 4) { measurements.push_back(make_shared<Amount>(new_date, new_value, new_error, new_syst_error)); }
				else if (type_chosen == 5) { measurements.push_back(make_shared<Current>(new_date, new_value, new_error, new_syst_error)); }
				else { measurements.push_back(make_shared<Temperature>(new_date, new_value, new_error, new_syst_error)); }
			}
			else {
				input_file >> new_syst_error; // check if of type double if not throw an exception
				if (!input_file.good()) { throw TypeFailure<double>(new_syst_error, input_file, line_num); }

				input_file.clear(); // Clear the stream
				input_file.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore what is left in the stream until the next line

				// Pushback the relevant type of measurement on the vector of measurements
				if (type_chosen == 1) { measurements.push_back(make_shared<Length>(new_date, new_value, new_error, new_syst_error)); }
				else if (type_chosen == 2) { measurements.push_back(make_shared<Time>(new_date, new_value, new_error, new_syst_error)); }
				else if (type_chosen == 3) { measurements.push_back(make_shared<Mass>(new_date, new_value, new_error, new_syst_error)); }
				else if (type_chosen == 4) { measurements.push_back(make_shared<Amount>(new_date, new_value, new_error, new_syst_error)); }
				else if (type_chosen == 5) { measurements.push_back(make_shared<Current>(new_date, new_value, new_error, new_syst_error)); }
				else { measurements.push_back(make_shared<Temperature>(new_date, new_value, new_error, new_syst_error)); }
			}
		}
		catch (TypeFailure<double>) {}
		catch (DateFailure) {}
	}

	line_num = 0; // Reset to zero when done reading in lines
	input_file.clear(); input_file.close(); // clear and close the file 

	// If the user wants to return to the previous menu, break the code
	cout << "\t\t ===========================================" << endl;
	cout << "\t\t               Reading complete.            " << endl;
	cout << "\t\t ===========================================" << endl;
	cout << "\t\t        Measurement/s from file saved.      " << endl;
	cout << "\t\t ===========================================" << endl;
	cout << "\t\t   Returning to the add measurement menu." << endl;
	cout << "\t\t ===========================================" << endl;
}



const void Experiment::view_measurements() {

	// Create a view experiment menu
	vector<string> view_experiment_info;

	// Push back the options onto the vector of options
	view_experiment_info.push_back("VIEW ALL"); // option 1 (element 0 + 1)
	view_experiment_info.push_back("VIEW BY TYPE"); // option 2
	view_experiment_info.push_back("VIEW BY DATE"); // option 3
	Menu view_experiment_menu("VIEW MEASUREMENTS", view_experiment_info);

	int option_view_experiment{ 0 };
	do {

		// Firstly check the vector of measurements has content
		if (measurements.size() < 1) { // If there is no measurements return to the previous menu
			cout << endl;
			cerr << "ERROR: No measurements added." << endl;
			cout << "You need to enter measurements before you wish to view them." << endl;
			cout << endl;
			option_view_experiment = 4; // Set the value to 6, to return to the previous menu
		}

		// Exception handling
		if (option_view_experiment != 4) { // If the value is zero, there are measurements contained in the experiment, can progress

			cout << view_experiment_menu << endl; // Display the menu
			cout << "Please enter an option: "; // Enter an option
			exception_handling_functions::option_check(option_view_experiment, view_experiment_menu.get_all_options()); // Check the input
		}

		switch (option_view_experiment) {
		case 1:
			// Display all measurements
			cout << "\t\t ==========================================" << endl;
			cout << "\t\t           Viewing all measurements.       " << endl;
			cout << "\t\t ==========================================" << endl;
			cout << endl << endl;
			cout << Table("Table of all measurements", measurements) << endl; // Display the table of all measurements
			cout << endl;

			break;

		case 2:
			// View measurements by type
			search_which_type(); // Display a menu for the what types are availible and then search for them
			break;

		case 3:
			// View measurements by date 
			search_dates(); // Call the search dates function
			break;

		case 4:
			cout << "\t\t ==========================================" << endl;
			cout << "\t\t       Returning to the previous menu.     " << endl;
			cout << "\t\t ==========================================" << endl;
			break;

		default:
			cout << "Please enter a value between 1 and " << view_experiment_info.size() + 1 << "." << endl;
			break;

		}
	} while (option_view_experiment != 4); // While not returning to the main menu, display the add measurement menu again
}

const void Experiment::search_dates() {

	bool try_again_bool(true); // Create a boolean value to retry searching for a date
	string search_date; // Create a string to hold the searched date
	vector<shared_ptr<Measurement>> date_searched_measurements; // Create a vector of pointers to abstract base class measurement to hold the measurements with the date searched

	do {
		// User inputs a new date to be searched
		cout << endl;
		cout << "Please insert a date stamp (DD/MM/YYYY): "; // User inputs a date stamp
		cin >> search_date; // Set date_search from the user input
		adding_measurement_functions::check_date_UI(search_date); // Check the date using the check_date function
		cout << endl;

		int position{ 0 }; // Define position a counter to get the vector element of measurements when the date is found
		for (auto iter_date = measurements.begin(); iter_date != measurements.end(); ++iter_date) { // Iterate over the vector of measurements given for the table
			if ((*iter_date)->get_date() == search_date) {
				date_searched_measurements.push_back(measurements[position]); // Pushback the measurements made on this date 
			}
			position++; // Add one to the position of the measurement counter
		}

		if (date_searched_measurements.size() < 1) {
			cerr << "ERROR: No measurements found in this experiment with the date stamp: " << search_date << "." << endl;
			cout << "Would you like to search for another date? (y/n): "; // Give the option to input the file name again else return to the previous menu
			char try_again_option;
			try {
				cin >> try_again_option; // User input
				if (cin.fail()) { throw TypeFailure<char>(try_again_option, cin); } // If the input is not of type character, retry
				if (!(try_again_option == 'n' || try_again_option == 'y')) { throw NotYesorNo(try_again_option, cin); } // If the input is not y or n retry
			}
			catch (TypeFailure<char>) {} // Catch these thrown exceptions
			catch (NotYesorNo) {}

			if (try_again_option == 'n') { try_again_bool = false; }
		}
		else { try_again_bool = false; } // Exit the loop if all good

	} while (try_again_bool);

	cout << "\t\t ==========================================" << endl;
	cout << "\t\t        Viewing measurements by date.      " << endl;
	cout << "\t\t ==========================================" << endl;
	cout << endl << endl;

	string title = "All " + search_date + " measurements"; // Create a title for the table
	cout << Table(title, date_searched_measurements) << endl; // Display the table of measurements with the date searched
	cout << endl;
}

const void Experiment::search_types(string search_type) {

	vector<shared_ptr<Measurement>> type_searched_measurements; // Create a vector of pointers to abstract base class measurement to hold the measurements with the type searched

	int position{ 0 }; // Define position a counter to get the vector element of measurements when the date is found
	for (auto iter_date = measurements.begin(); iter_date != measurements.end(); ++iter_date) { // Iterate over the vector of measurements given for the table
		if ((*iter_date)->name() == search_type) {
			type_searched_measurements.push_back(measurements[position]); // Pushback the measurements made of the type desired 
		}
		position++; // Add one to the position of the measurement counter
	}

	if (type_searched_measurements.size() < 1) {
		cerr << "ERROR: No measurements found in this experiment of the type: " << search_type << "." << endl;
		return; // No measurements with the type searched have been located, return
	}

	cout << "\t\t ==========================================" << endl;
	cout << "\t\t        Viewing measurements by type.      " << endl;
	cout << "\t\t ==========================================" << endl;
	cout << endl << endl;

	string title = "A table of " + search_type + " measurements"; // Create a title for the table
	cout << Table(title, type_searched_measurements) << endl; // Display the table of measurements with the type searched
	cout << endl;
}

const void Experiment::search_which_type() {
	// A function which will display a menu displaying the possible types to search

	// Create an add measurement menu
	vector<string> view_type_meas;
	// Push back the options onto the vector of options
	view_type_meas.push_back("LENGTH"); // option 1 (element 0 + 1)
	view_type_meas.push_back("TIME"); // option 2
	view_type_meas.push_back("MASS"); // option 3
	view_type_meas.push_back("AMOUNT"); // option 4
	view_type_meas.push_back("CURRENT"); // option 5
	view_type_meas.push_back("TEMPERATURE"); // option 6
	Menu view_type_meas_menu("VIEW A TYPE", view_type_meas);

	int option_view_type;
	do {
		cout << view_type_meas_menu << endl; // Display the menu
		cout << "Please enter an option: "; // Enter an option
		cout << endl;

		// Exception handling
		exception_handling_functions::option_check(option_view_type, view_type_meas_menu.get_all_options()); // Check the input

		switch (option_view_type) {
		case 1:
			// View only length measurements
			search_types("Length"); // Call the search types function
			break;

		case 2:
			// View only time measurements
			search_types("Time"); // Call the search types function
			break;

		case 3:
			// View only mass measurements
			search_types("Mass"); // Call the search types function
			break;

		case 4:
			// View only amount measurements
			search_types("Amount"); // Call the search types function
			break;

		case 5:
			// View only current measurements
			search_types("Current"); // Call the search types function
			break;

		case 6:
			// View only temperature measurements
			search_types("Temperature"); // Call the search types function
			break;

		case 7:
			cout << "\t\t ==========================================" << endl;
			cout << "\t\t       Returning to the previous menu.     " << endl;
			cout << "\t\t ==========================================" << endl;
			break;

		default:
			cout << "Please enter a value between 1 and " << view_type_meas.size() + 1 << "." << endl;
			break;

		}
	} while (option_view_type != 7); // While not returning to the main menu, display the add measurement menu again
}


const void Experiment::ModifyOrDelete() {

	// Create an add measurement by file or manually menu
	vector<string> ModifyOrDelete;
	ModifyOrDelete.push_back("MODIFY A MEASUREMENT");
	ModifyOrDelete.push_back("DELETE A MEASUREMENT");
	Menu ModifyOrDelete_menu("MODIFY OR DELETE", ModifyOrDelete);

	int option_modordel; // Define option as an integer
	do {
		cout << ModifyOrDelete_menu << endl; // Display the menu
		cout << "Please enter an option: "; // Enter an option

		// Exception handling
		exception_handling_functions::option_check(option_modordel, ModifyOrDelete_menu.get_all_options()); // Check the input

		switch (option_modordel) {
		case 1:
			// The user has chosen to modify a measurement
			modify_measurements();
			break;

		case 2:
			// The user has chosen delete a measurement
			delete_measurements();
			break;

		case 3:
			cout << "\t\t ==========================================" << endl;
			cout << "\t\t       Returning to the previous menu.     " << endl;
			cout << "\t\t ==========================================" << endl;
			break;

		default:
			cout << "Please enter a value between 1 and " << ModifyOrDelete.size() + 1 << "." << endl;
			break;
		}
	} while (option_modordel != 3);






}


const void Experiment::delete_measurements() {
	// A function which will delete a measurement specified by the user 

	// Create a delete experiment menu
	vector<string> delete_measurements;

	// Push back the options onto the vector of options
	delete_measurements.push_back("DELETE SPECIFIC"); // option 1 (element 0 + 1)
	delete_measurements.push_back("DELETE BY TYPE"); // option 2
	delete_measurements.push_back("DELETE BY DATE"); // option 3
	Menu delete_measurements_menu("DELETE MEASUREMENTS", delete_measurements);

	int option_delete_experiment{ 0 };
	do {

		// Firstly check the vector of measurements has content
		if (measurements.size() < 1) { // If there is no measurements return to the previous menu
			cout << endl;
			cerr << "ERROR: No measurements added." << endl;
			cout << "You need to enter measurements before you wish to delete them." << endl;
			cout << endl;
			option_delete_experiment = 4; // Set the value to 4, to return to the previous menu
		}

		// Exception handling
		if (option_delete_experiment != 4) { // If the value is zero, there are measurements contained in the experiment, can progress
			cout << delete_measurements_menu << endl; // Display the menu
			cout << "Please enter an option: "; // Enter an option
			exception_handling_functions::option_check(option_delete_experiment, delete_measurements_menu.get_all_options()); // Check the input
		}
			
		switch (option_delete_experiment) {
		case 1:
			// Display a specific measurement
			delete_specific(); // Delete a specific measurement function called
			break;

		case 2:
			// Delete measurements by type
			delete_which_type(); // Display a menu for the what types are availible and then search for them
			break;

		case 3:
			// Delete measurements by date 
			delete_dates(); // Call the delete dates function
			break;

		case 4:
			cout << "\t\t ==========================================" << endl;
			cout << "\t\t       Returning to the previous menu.     " << endl;
			cout << "\t\t ==========================================" << endl;
			break;

		default:
			cout << "Please enter a value between 1 and " << delete_measurements.size() + 1 << "." << endl;
			break;

		}
	} while (option_delete_experiment != 4); // While not returning to the main menu, display the add measurement menu again
}

const void Experiment::delete_specific() {
	// A function to delete a specific measurement 

	cout << "\t\t ==========================================" << endl;
	cout << "\t\t        Delete a specific measurement.     " << endl;
	cout << "\t\t ==========================================" << endl;
	cout << endl << endl;
	cout << Table("Table of all measurements", measurements) << endl; // Display the table of all measurements
	cout << endl;
	cout << "Please enter the 'key' of the measurement you would like to delete: ";

	int key_for_deletion; // Define a key for an experiment which the user would like to delete
	exception_handling_functions::option_check(key_for_deletion, measurements); // Checks that the key_for_deletion lies within the range of the measurements in the table 

	cout << endl;

	vector<shared_ptr<Measurement>> key_searched_measurements; // Create a vector of pointers to abstract base class measurement to hold the measurements with the key searched
	key_searched_measurements.push_back(measurements[key_for_deletion - 1]);

	string title = "You have selected to delete the following measurement: "; // Display the title
	cout << Table(title, key_searched_measurements) << endl; // Display the table of measurements with the type searched
	cout << endl;

	cout << "Are you sure you would like to delete this measurement? (y/n): "; // Doubel check that the user wants to delete the measurement they've selected
	cout << endl;

	char try_again_option;
	try {
		cin >> try_again_option; // User input
		if (cin.fail()) { throw TypeFailure<char>(try_again_option, cin); } // If the input is not of type character, retry
		if (!(try_again_option == 'n' || try_again_option == 'y')) { throw NotYesorNo(try_again_option, cin); } // If the input is not y or n retry
	}
	catch (TypeFailure<char>) {} // Catch these thrown exceptions
	catch (NotYesorNo) {}

	if (try_again_option == 'y') {
		measurements.erase(measurements.begin() + key_for_deletion - 1); // Erase the measurement from the vector

		cout << "\t\t ==========================================" << endl;
		cout << "\t\t            Measurement deleted.           " << endl;
		cout << "\t\t ==========================================" << endl;
		cout << endl;
	}
	else {
		cout << "\t\t ==========================================" << endl;
		cout << "\t\t          Measurement not deleted.         " << endl;
		cout << "\t\t ==========================================" << endl;
		cout << endl;
	}
}

const void Experiment::delete_which_type() {
	// A function which will display a menu displaying the possible types to search

	// Create an add measurement menu
	vector<string> delete_type_meas;
	// Push back the options onto the vector of options
	delete_type_meas.push_back("LENGTH"); // option 1 (element 0 + 1)
	delete_type_meas.push_back("TIME"); // option 2
	delete_type_meas.push_back("MASS"); // option 3
	delete_type_meas.push_back("AMOUNT"); // option 4
	delete_type_meas.push_back("CURRENT"); // option 5
	delete_type_meas.push_back("TEMPERATURE"); // option 6
	Menu delete_type_meas_menu("DELETE A TYPE", delete_type_meas);

	int option_delete_type;
	do {
		cout << delete_type_meas_menu << endl; // Display the menu
		cout << "Please enter an option: "; // Enter an option
		cout << endl;

		// Exception handling
		exception_handling_functions::option_check(option_delete_type, delete_type_meas_menu.get_all_options()); // Check the input

		switch (option_delete_type) {
		case 1:
			// View only length measurements
			delete_types("Length"); // Call the search types function
			break;

		case 2:
			// View only time measurements
			delete_types("Time"); // Call the search types function
			break;

		case 3:
			// View only mass measurements
			delete_types("Mass"); // Call the search types function
			break;

		case 4:
			// View only amount measurements
			delete_types("Amount"); // Call the search types function
			break;

		case 5:
			// View only current measurements
			delete_types("Current"); // Call the search types function
			break;

		case 6:
			// View only temperature measurements
			delete_types("Temperature"); // Call the search types function
			break;

		case 7:
			cout << "\t\t ==========================================" << endl;
			cout << "\t\t       Returning to the previous menu.     " << endl;
			cout << "\t\t ==========================================" << endl;
			break;

		default:
			cout << "Please enter a value between 1 and " << delete_type_meas.size() + 1 << "." << endl;
			break;

		}
	} while (option_delete_type != 7); // While not returning to the main menu, display the add measurement menu again
}

const void Experiment::delete_types(string search_type) {

	vector<shared_ptr<Measurement>> delete_type_measurements; // A vector of pointers to abstract base class measurement to hold the measurements with the type to delete
	vector<shared_ptr<Measurement>> new_measurements; // A vector of pointers to abstract base class measurement to hold the measurements with the type deleted

	int position{ 0 }; // Define position a counter to get the vector element of measurements when the type is found
	for (auto iter_date = measurements.begin(); iter_date != measurements.end(); ++iter_date) { // Iterate over the vector of measurements given for the table
		if ((*iter_date)->name() == search_type) {
			delete_type_measurements.push_back(measurements[position]); // Pushback the measurements made of the type desired 
		}
		position++; // Add one to the position of the measurement counter
	}

	if (delete_type_measurements.size() < 1) {
		cerr << "ERROR: No measurements found in this experiment of the type: " << search_type << "." << endl;
		return; // No measurements with the type searched have been located, return
	}

	// Display the table of measurements which the user wants to delete
	string title = search_type + " measurements to be deleted."; // Create a title for the table
	cout << Table(title, delete_type_measurements) << endl; // Display the table of measurements with the type searched
	cout << endl;
	cout << "Are you sure you would like to delete these measurements? (y/n): "; // Double check that the user wants to delete the measurement they've selected

	char try_again_option;
	try {
		cin >> try_again_option; // User input
		if (cin.fail()) { throw TypeFailure<char>(try_again_option, cin); } // If the input is not of type character, retry
		if (!(try_again_option == 'n' || try_again_option == 'y')) { throw NotYesorNo(try_again_option, cin); } // If the input is not y or n retry
	}
	catch (TypeFailure<char>) {} // Catch these thrown exceptions
	catch (NotYesorNo) {}

	if (try_again_option == 'y') {
		position = 0;
		// Iterate through the vector of measurements, if the type is not equal to the one we would like to delete, push it back to a vector of new measurements
		for (auto iter_date = measurements.begin(); iter_date != measurements.end(); ++iter_date) { // Iterate over the vector of measurements given for the table
			if ((*iter_date)->name() != search_type) {
				new_measurements.push_back(measurements[position]);
			} // Erase the measurement from the vector
			position++; // Add one to the position of the measurement counter
		}

		measurements = new_measurements; // Make the measurements vector = to the new_measurements vector, with the type the user specified deleted 
		// Measurements are deleted
		cout << endl;
		cout << "\t\t ==========================================" << endl;
		cout << "\t\t           Measurement/s deleted.          " << endl;
		cout << "\t\t ==========================================" << endl;
		cout << endl;
	}
	else {
		// Measurements not deleted
		cout << endl;
		cout << "\t\t ==========================================" << endl;
		cout << "\t\t          Measurements not deleted.        " << endl;
		cout << "\t\t ==========================================" << endl;
		cout << endl;
	}
}

const void Experiment::delete_dates() {

	bool try_again_bool(true); // Create a boolean value to retry searching for a date to delete
	string delete_date; // Create a string to hold the searched date
	vector<shared_ptr<Measurement>> date_deleted_measurements; // Create a vector of pointers to abstract base class measurement to hold the measurements with the date searched
	vector<shared_ptr<Measurement>> new_measurements; // A vector of pointers to abstract base class measurement to hold the measurements with the type deleted

	do {
		// User inputs a new date to be searched
		cout << endl;
		cout << "Please insert a date stamp of measurements you would like to delete (DD/MM/YYYY): "; // User inputs a date stamp
		cin >> delete_date; // Set date_search from the user input
		adding_measurement_functions::check_date_UI(delete_date); // Check the date using the check_date function
		cout << endl;

		int position{ 0 }; // Define position a counter to get the vector element of measurements when the date is found
		for (auto iter_date = measurements.begin(); iter_date != measurements.end(); ++iter_date) { // Iterate over the vector of measurements given for the table
			if ((*iter_date)->get_date() == delete_date) {
				date_deleted_measurements.push_back(measurements[position]); // Pushback the measurements made on this date 
			}
			position++; // Add one to the position of the measurement counter
		}

		if (date_deleted_measurements.size() < 1) {
			cerr << "ERROR: No measurements found in this experiment with the date stamp: " << delete_date << "." << endl;
			cout << "Would you like to search for another date to delete? (y/n): "; // Give the option to input the file name again else return to the previous menu
			char try_again_option;
			try {
				cin >> try_again_option; // User input
				if (cin.fail()) { throw TypeFailure<char>(try_again_option, cin); } // If the input is not of type character, retry
				if (!(try_again_option == 'n' || try_again_option == 'y')) { throw NotYesorNo(try_again_option, cin); } // If the input is not y or n retry
			}
			catch (TypeFailure<char>) {} // Catch these thrown exceptions
			catch (NotYesorNo) {}

			if (try_again_option == 'n') { // Returning to previous menu
				cout << endl;
				cout << "\t\t ==========================================" << endl;
				cout << "\t\t         Returning to previous menu.       " << endl;
				cout << "\t\t ==========================================" << endl;
				cout << endl;
				return; }
		}
		else { try_again_bool = false; } // Exit the loop if all good

	} while (try_again_bool);

	// Display the table of measurements which the user wants to delete
	string title = delete_date + " measurements to be deleted."; // Create a title for the table
	cout << Table(title, date_deleted_measurements) << endl; // Display the table of measurements with the type searched
	cout << endl;
	cout << "Are you sure you would like to delete these measurements? (y/n): "; // Double check that the user wants to delete the measurement they've selected

	char try_again_option;
	try {
		cin >> try_again_option; // User input
		if (cin.fail()) { throw TypeFailure<char>(try_again_option, cin); } // If the input is not of type character, retry
		if (!(try_again_option == 'n' || try_again_option == 'y')) { throw NotYesorNo(try_again_option, cin); } // If the input is not y or n retry
	}
	catch (TypeFailure<char>) {} // Catch these thrown exceptions
	catch (NotYesorNo) {}

	if (try_again_option == 'y') {

		int position{ 0 };
		// Iterate through the vector of measurements, if the date is not equal to the one we would like to delete, push it back to a vector of new measurements
		for (auto iter_date = measurements.begin(); iter_date != measurements.end(); ++iter_date) { // Iterate over the vector of measurements given for the table
			if ((*iter_date)->get_date() != delete_date) {
				new_measurements.push_back(measurements[position]);
			} // Erase the measurement from the vector
			position++; // Add one to the position of the measurement counter
		}
		measurements = new_measurements; // Make the measurements vector = to the new_measurements vector, with the date the user specified deleted 
	
		// Measurements are deleted
		cout << endl;
		cout << "\t\t ==========================================" << endl;
		cout << "\t\t           Measurement/s deleted.          " << endl;
		cout << "\t\t ==========================================" << endl;
		cout << endl;
	}
	else {
		// Measurements not deleted
		cout << endl;
		cout << "\t\t ==========================================" << endl;
		cout << "\t\t          Measurements not deleted.        " << endl;
		cout << "\t\t ==========================================" << endl;
		cout << endl;
	}
}



const void Experiment::modify_measurements() {
	// A function to modify measurements 
	// Will locate the measurement the user would like to modify, delete it and then replace with a new thing



	
	cout << "\t\t ==========================================" << endl;
	cout << "\t\t        Modify a specific measurement.     " << endl;
	cout << "\t\t ==========================================" << endl;
	cout << endl << endl;
	cout << Table("Table of all measurements", measurements) << endl; // Display the table of all measurements
	cout << endl;
	cout << "Please enter the 'key' of the measurement you would like to modify: ";

	int key_for_modification; // Define a key for an experiment which the user would like to delete
	exception_handling_functions::option_check(key_for_modification, measurements); // Checks that the key_for_deletion lies within the range of the measurements in the table 

	cout << endl;

	vector<shared_ptr<Measurement>> key_searched_measurements; // Create a vector of pointers to abstract base class measurement to hold the measurements with the key searched
	key_searched_measurements.push_back(measurements[key_for_modification - 1]);

	string title = "You have selected to modify the following measurement: "; // Display the title
	cout << Table(title, key_searched_measurements) << endl; // Display the table of measurements with the type searched
	cout << endl;

	cout << "Are you sure you would like to modify this measurement? (y/n): "; // Doubel check that the user wants to delete the measurement they've selected
	cout << endl;

	char try_again_option;
	try {
		cin >> try_again_option; // User input
		if (cin.fail()) { throw TypeFailure<char>(try_again_option, cin); } // If the input is not of type character, retry
		if (!(try_again_option == 'n' || try_again_option == 'y')) { throw NotYesorNo(try_again_option, cin); } // If the input is not y or n retry
	}
	catch (TypeFailure<char>) {} // Catch these thrown exceptions
	catch (NotYesorNo) {}

	if (try_again_option == 'y') {

		string type_name = (measurements[key_for_modification - 1])->name(); // Find the ID of the measurement that the user wishes to modify
		int type_num;
		// Find the type number associated with this, to use the add measurement type manually function
		if (type_name == "Length") { type_num = 1; }
		else if (type_name == "Time") { type_num = 2; }
		else if (type_name == "Mass") { type_num = 3; }
		else if (type_name == "Amount") { type_num = 4; }
		else if (type_name == "Current") { type_num = 5; }
		else { type_num = 6; }

		// Over write the previous measurement with a new one
		(measurements[key_for_modification - 1]) = adding_measurement_functions::add_meas_type_manually(type_num);

		cout << "\t\t ==========================================" << endl;
		cout << "\t\t            Measurement modified.          " << endl;
		cout << "\t\t ==========================================" << endl;
		cout << endl;
	}
	else {
		cout << "\t\t ==========================================" << endl;
		cout << "\t\t          Measurement not modified.        " << endl;
		cout << "\t\t ==========================================" << endl;
		cout << endl;
	}
}

const void Experiment::experiment_report(const int sig_fig){

	// Create a vector of measurements for all the different types, to print seperate tables for all of them
	vector<shared_ptr<Measurement>> length_measurements, time_measurements, mass_measurements, amount_measurements, current_measurements, temperature_measurements;

	cout << "================================================================================" << endl;
	cout << "================================================================================" << endl;
	cout << endl;
	cout << "\t\t ==========================================" << endl;
	cout << "\t\t         Report: " << name << endl; // Experiment report title
	cout << "\t\t ==========================================" << endl;
	cout << endl;

	cout.precision(sig_fig); // Set the precision of all the values to be what the user desires

	int position{ 0 }; // Define position a counter to get the vector element of measurements when the a specific type of measurement is found
	// Iterate through the measurements, seperate based on type
	for (auto iter_date = measurements.begin(); iter_date != measurements.end(); ++iter_date) { // Iterate over the vector of measurements given for the table
		if ((*iter_date)->name() == "Length") {
			length_measurements.push_back(measurements[position]); // Pushback the length measurements to its own vector of measurements
		}
		else if ((*iter_date)->name() == "Time") {
			time_measurements.push_back(measurements[position]); // Do the same for the other types of measurements
		}
		else if ((*iter_date)->name() == "Mass") {
			mass_measurements.push_back(measurements[position]);  
		}
		else if ((*iter_date)->name() == "Amount") {
			amount_measurements.push_back(measurements[position]); 
		}
		else if ((*iter_date)->name() == "Current") {
			current_measurements.push_back(measurements[position]);
		}
		else if ((*iter_date)->name() == "Temperature") {
			temperature_measurements.push_back(measurements[position]);
		}
		position++; // Add one to the position of the measurement counter
	}

	if (length_measurements.size() > 0) {
		cout << endl;
		string title = "All Length Measurements"; // Create a title for the table
		cout << Table_Combined_Error(title, length_measurements) << endl; // Display the table of all length measurments
		cout << endl;
		measurement_analysis(length_measurements); // Analyse the data in the table and state underneath the table
	}
	if (time_measurements.size() > 0) {
		cout << endl;
		string title = "All Time Measurements"; // Create a title for the table
		cout << Table_Combined_Error(title, time_measurements) << endl; // Table of time measurements
		cout << endl;
		measurement_analysis(time_measurements);
	}
	if (mass_measurements.size() > 0) {
		cout << endl;
		string title = "All Mass Measurements"; // Create a title for the table
		cout << Table_Combined_Error(title, mass_measurements) << endl; // Table of mass measurements
		cout << endl;
		measurement_analysis(mass_measurements);
	}
	if (amount_measurements.size() > 0) {
		cout << endl;
		string title = "All Amount Measurements"; // Create a title for the table
		cout << Table_Combined_Error(title, amount_measurements) << endl; // Table of amounts
		cout << endl;
		measurement_analysis(amount_measurements);
	}
	if (current_measurements.size() > 0) {
		cout << endl;
		string title = "All Current Measurements"; // Create a title for the table
		cout << Table_Combined_Error(title, current_measurements) << endl; // Current measurement table
		cout << endl;
		measurement_analysis(current_measurements);
	}
	if (temperature_measurements.size() > 0) {
		cout << endl;
		string title = "All Temperature Measurements"; // Create a title for the table
		cout << Table_Combined_Error(title, temperature_measurements) << endl; // Table of temperatures
		cout << endl;
		measurement_analysis(temperature_measurements);
	}

	cout << endl;
	cout << "\t\t ==========================================" << endl;
	cout << "\t\t             End of the report.            " << endl;
	cout << "\t\t ==========================================" << endl;
	cout << "================================================================================" << endl;
	cout << "================================================================================" << endl;
	cout << endl;
	system("pause");
	cout << endl;
	cout << "\t\t ==========================================" << endl;
	cout << "\t\t        Returning to the previous menu.    " << endl;
	cout << "\t\t ==========================================" << endl;
	cout << endl;
}

const void Experiment::measurement_analysis(vector<shared_ptr<Measurement>> meas_to_analyse) {
	// A function which will take a vector of measurements to analyse them and output them
	// This function works is called only in the case where the measurements to analyse are of the same type
	// Will calculate the weighted mean, standard deviation and variance


	// Weighted mean calculation
	// Calculate the weighted mean of the measurements
	double sum_numerator{ 0 }; // Sum numerator = value / error^2
	double sum_denominator{ 0 }; // Sum denominator = 1 / error^2
	string units; // A string to hold the units 
	int num_of_non_zero_weights{ 0 }; // An integer for the number of weights

	// Iterate over the vector of measurements given for the table, to calculate the mean of these measurements
	for (auto iter_calc = meas_to_analyse.begin(); iter_calc != meas_to_analyse.end(); ++iter_calc) {
		sum_numerator += ((*iter_calc)->get_value()) / (pow((*iter_calc)->combine_error(), 2));
		if ((*iter_calc)->get_value() != 0) {
			sum_denominator += 1 / pow((*iter_calc)->combine_error(), 2);
			num_of_non_zero_weights++;
		}
		units = (*iter_calc)->units(); // Get the units of the measurements
	}
	double weighted_mean = sum_numerator / sum_denominator; // Calculate the weighted mean
	double weighted_mean_error = 1 / sum_denominator; // Error on the weighted mean


	// Weighted standard deviation calculation
	double N = meas_to_analyse.size(); // N is the number of values
	double M = num_of_non_zero_weights; // M is the number of non-zero weights
	double sum_numerator2{ 0 }; // Holds the sum in the numerator of the stand. dev calculation
	double sum_denominator2{ 0 }; // Holds the sum in the denominator of the stand. dev calc
	
	// Iterate over the measurements to calculate the standard deviation and error
	for (auto iter_calc = meas_to_analyse.begin(); iter_calc != meas_to_analyse.end(); ++iter_calc) {
		sum_numerator2 += pow(((*iter_calc)->get_value()-weighted_mean),2) / (pow((*iter_calc)->combine_error(), 2));
		if ((*iter_calc)->get_value() != 0) {
			sum_denominator2 += 1 / pow((*iter_calc)->combine_error(), 2);
		}
		units = (*iter_calc)->units(); // Get the units of the measurements
	}
	double weighted_standard_deviation = sqrt(sum_numerator2 / ((M - 1) / M)*sum_denominator2); // Sub into the equation

	// The standard error is the standard deviation divided by the sqrt(number of values)
	double weighted_standard_error = weighted_standard_deviation / sqrt(N); 

	// Show the values obtained in analysis
	cout << "\t\t ==========================================" << endl;
	cout << "\t\t                 Analysis:                 " << endl;
	cout << "\t\t ------------------------------------------" << endl;
	cout << "\t\t  Weighted mean = " << weighted_mean << " (+/-) " << weighted_mean_error << " " << units << endl; // Show the weighted mean
	cout << "\t\t  Weighted standard deviation = " << weighted_standard_deviation << " " << units << endl;
	cout << "\t\t  Weighted standard error = " << weighted_standard_error << " " << units << endl;
	cout << "\t\t ==========================================" << endl;
	cout << endl;

}
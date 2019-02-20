// Author: Alexander Jenkins
// ID: 9884664
// The .cpp file for Journal.h

#include "Journal.h"
#include"Functions.h"

Journal::Journal(){}

Journal::~Journal(){
	cout << "Journal deleted from memory." << endl;
}

const void Journal::start_message() {
	// Display the programs name: Your Journal
	cout << "Welcome to your..." << endl;
	cout << "                                                                   ,," << endl;
	cout << "          `7MMF'                                                 `7MM" << endl;
	cout << "            MM                                                     MM" << endl;
	cout << "            MM  ,pW^Wq.`7MM  `7MM  `7Mb,od8 `7MMpMMMb.   ,6^Yb.    MM" << endl;
	cout << "            MM 6W'   `Wb MM    MM    MM' '*   MM    MM  8)   MM    MM" << endl;
	cout << "            MM 8M     M8 MM    MM    MM       MM    MM   ,pm9MM    MM" << endl;
	cout << "       (O)  MM YA.   ,A9 MM    MM    MM       MM    MM  8M   MM    MM" << endl;
	cout << "        Ymmm9   `Ybmd9'  `Mbod^YML..JMML.   .JMML  JMML.`Moo9^Yo..JMML." << endl;
	cout << endl;
	cout << endl;
	cout << "\t     In your Journal you can: " << endl;
	cout << "\t     - Create and manage your own experiments!" << endl;
	cout << "\t     - Add, delete, view and modify your own measurements!" << endl;
	cout << "\t     - Import measurements manually or from a file!" << endl;
	cout << "\t     - Generate an experiment report with the data analysed!" << endl;
	cout << endl;
	cout << endl;
	cout << "\t\t ===========================================" << endl;
	cout << "\t\t     Are you ready to begin your Journal?   " << endl;
	cout << "\t\t ===========================================" << endl;
	cout << endl;

}

const void Journal::add_experiment() {
	// Create a menu 
	cout << endl;
	cout << "\t\t ===========================================" << endl;
	cout << "\t\t              Add an experiment.            " << endl;
	cout << "\t\t ===========================================" << endl;
	cout << endl;

	string experiment_name; // A string to hold the experiments name
	bool try_again(false); // A bool to re-input the experiments name if there are two with the same name

	do {
		try_again = false; // Re-initialise the try again as false if the user inputs wrong

		// Ask the user what they would like to call the experiment
		cout << "Please name your experiment: ";
		
		cin.clear();
		getline(cin, experiment_name); // Get the line which the user inputs

		// Iterate through the first element of the map, if there are two experiments with the same name ask to retry
		for (auto &iter_check_key : Experiments) {
			if (experiment_name == iter_check_key.first) { // Check the experiment name doesn't already exist in the map, if it does try again
				cerr << "ERROR: You cannot have two experiments with the same name in your journal." << endl;
				cout << endl;
				try_again = true;
			} 
		}

	} while (try_again == true);

	// Add the experiment and it's name to the journals map
	Experiments.insert(pair<string, unique_ptr<Experiment>>(experiment_name, make_unique<Experiment>(experiment_name)));

	cout << endl;
	cout << "\t\t ===========================================" << endl;
	cout << "\t\t       Experiment added to your journal.    " << endl;
	cout << "\t\t ===========================================" << endl;
	cout << endl;
	cout << "\t\t ===========================================" << endl;
	cout << "\t\t     Add measurements to your experiment.   " << endl;
	cout << "\t\t ===========================================" << endl;
	cout << endl;

	// Now can use the key of the map to add measurements of the experiment
	(Experiments[experiment_name])->add_measurements();
	// Experiment added
}

const void Journal::delete_experiment() {

	// Firstly check there are experiments to view
	if (Experiments.size() == 0) {
		cerr << "ERROR: There are no experiments in your journal to delete." << endl;
		cout << "Please add an experiment first." << endl;

		cout << endl;
		cout << "\t\t ===========================================" << endl;
		cout << "\t\t          Returning to previous menu.       " << endl;
		cout << "\t\t ===========================================" << endl;
		cout << endl;
		return;
	}



	// Display a menu of all experiments names
	vector<string> all_experiments; // Create a vector of the experiment names to display a menu

	// Iterate through the first element of the map and display as a menu
	for (auto &iter_add_options : Experiments) {
		all_experiments.push_back(iter_add_options.first); // Add the name of the experiment to the menu
	}

	Menu delete_experiment_menu("DELETE AN EXPERIMENT", all_experiments);
	cout << delete_experiment_menu << endl;
	cout << "Please enter an option: "; // Enter an option

	int option_delete; // The option for the experiment the user wishes to delete
	exception_handling_functions::option_check(option_delete, delete_experiment_menu.get_all_options()); // Exception handling to check the option is within the limits of the menu

	int return_option = delete_experiment_menu.get_all_options().size(); // A value to hold the last option, to return to a previous menu
	if (option_delete == return_option) {
		return; // If the user wants to return to the previous menu
	}

	// Define a new string to hold the experiment name the user wishes to delete
	string option_delete_name = all_experiments[option_delete - 1];

	cout << "Are you sure you would like to delete the '" << option_delete_name << "' experiment? (y/n)" << endl;

	char sure_delete; // Double check the user would like to delete the experiment
	// Check that the date is one of the options given 'y' or 'n', if not, try again
	try {
		cin >> sure_delete;
		if (cin.fail()) { throw TypeFailure<char>(sure_delete, cin); }
		if (!(sure_delete == 'n' || sure_delete == 'y')) { throw NotYesorNo(sure_delete, cin); }
	}
	catch (TypeFailure<char>) {}
	catch (NotYesorNo) {}
	cout << endl;

	if (sure_delete == 'y') {
		// If yes delete the experiment from the journal

		Experiments.erase(option_delete_name); // Erase the experiment from the journal

		cout << endl;
		cout << "\t\t ===========================================" << endl;
		cout << "\t\t              Experiment deleted.           " << endl;
		cout << "\t\t ===========================================" << endl;
		cout << endl;
	}
	else {
		// Do not delete the experiment
		cout << endl;
		cout << "\t\t ===========================================" << endl;
		cout << "\t\t           Experiment not deleted.          " << endl;
		cout << "\t\t ===========================================" << endl;
		cout << endl;
	}
}

const void Journal::view_experiment() {

	// Firstly check there are experiments to view
	if (Experiments.size() == 0) {
		cerr << "ERROR: There are no experiments in your journal to view." << endl;
		cout << "Please add an experiment first." << endl;

		cout << endl;
		cout << "\t\t ===========================================" << endl;
		cout << "\t\t          Returning to previous menu.       " << endl;
		cout << "\t\t ===========================================" << endl;
		cout << endl;
		return;
	}

	// Display a menu of all experiments names
	vector<string> all_experiments; // Create a vector of the experiment names to display a menu

	// Iterate through the first element of the map and display as a menu
	for (auto &iter_add_options : Experiments) {
		all_experiments.push_back(iter_add_options.first); // Add the name of the experiment to the menu
	}
	
	// Print the menu
	Menu view_experiment_menu("VIEW AN EXPERIMENT", all_experiments);
	cout << view_experiment_menu << endl;

	cout << "Please enter an option: "; // Enter an option
	int option_view; // The option for the experiment the user wishes to delete
	exception_handling_functions::option_check(option_view, view_experiment_menu.get_all_options()); // Exception handling to check the option is within the limits of the menu

	int return_option = view_experiment_menu.get_all_options().size(); // A value to hold the last option, to return to a previous menu
	if (option_view == return_option) {
		return; // If the user wants to return to the previous menu
	}

	// Define a new string to hold the experiment name the user wishes to view
	string option_view_name = all_experiments[option_view - 1];

	(Experiments[option_view_name])->view_measurements(); // View the measurements for the experiment, using the name of the experiment as the key
}

const void Journal::modify_experiment() {

	// Firstly check there are experiments to modify
	if (Experiments.size() == 0) {
		cerr << "ERROR: There are no experiments in your journal to modify." << endl;
		cout << "Please add an experiment first." << endl;

		cout << endl;
		cout << "\t\t ===========================================" << endl;
		cout << "\t\t          Returning to previous menu.       " << endl;
		cout << "\t\t ===========================================" << endl;
		cout << endl;
		return;
	}

	// Display a menu of all experiments names
	vector<string> all_experiments; // Create a vector of the experiment names to display a menu

	// Iterate through the first element of the map and display as a menu
	for (auto &iter_add_options : Experiments) {
		all_experiments.push_back(iter_add_options.first); // Add the name of the experiment to the menu
	}

	// Print the menu
	Menu modify_experiment_menu("MODIFY AN EXPERIMENT", all_experiments);
	cout << modify_experiment_menu << endl;
	cout << "Please enter an option: "; // Enter an option

	int option_modify; // The option for the experiment the user wishes to modify
	exception_handling_functions::option_check(option_modify, modify_experiment_menu.get_all_options()); // Exception handling to check the option is within the limits of the menu

	int return_option = modify_experiment_menu.get_all_options().size(); // A value to hold the last option, to return to a previous menu
	if (option_modify == return_option) {
		return; // If the user wants to return to the previous menu
	}

	// Define a new string to hold the experiment name the user wishes to modify
	string option_modify_name = all_experiments[option_modify - 1];

	(Experiments[option_modify_name])->ModifyOrDelete(); // View the measurements for the experiment, using the name of the experiment as the key

}

const void Journal::generate_report() {
	// Firstly check there are experiments to modify
	if (Experiments.size() == 0) {
		cerr << "ERROR: There are no experiments in your journal to modify." << endl;
		cout << "Please add an experiment first." << endl;

		cout << endl;
		cout << "\t\t ===========================================" << endl;
		cout << "\t\t          Returning to previous menu.       " << endl;
		cout << "\t\t ===========================================" << endl;
		cout << endl;
		return;
	}

	// Display a menu of all experiments names
	vector<string> all_experiments; // Create a vector of the experiment names to display a menu

	// Iterate through the first element of the map and display as a menu
	for (auto &iter_add_options : Experiments) {
		all_experiments.push_back(iter_add_options.first); // Add the name of the experiment to the menu
	}

	// Print the menu
	Menu generate_report_menu("GENERATE A REPORT", all_experiments);
	cout << generate_report_menu << endl;
	cout << "Please enter an option: "; // Enter an option

	int option_report; // The option for the experiment the user wishes to modify
	exception_handling_functions::option_check(option_report, generate_report_menu.get_all_options()); // Exception handling to check the option is within the limits of the menu

	int return_option = generate_report_menu.get_all_options().size(); // A value to hold the last option, to return to a previous menu
	if (option_report == return_option) {
		return; // If the user wants to return to the previous menu
	}

	// Define a new string to hold the experiment name the user wishes to generate a report for
	string option_report_name = all_experiments[option_report - 1];

	cout << endl;
	cout << "Please enter the number of significant figures you would like to use (1-10): " << endl; // Set the precision of the report
	int sig_fig; // An integer for the user inputted significant figures
	try {
		try {
			cin >> sig_fig;
			if (cin.fail()) { throw TypeFailure<int>(sig_fig, cin); } // Throw TypeFailure exception, check initially the value inputted is the right type
			if ((sig_fig < 1) || (sig_fig > 10)) { throw NotInRange<int>(sig_fig, 1, 10); } // Throw not in range exception
		}
		catch (TypeFailure<int>) {
			// Catch the type failure exception. Check also in the range needed, if not throw an exception NotInRange to be caught by the outer catch statement
			if ((sig_fig < 1) || (sig_fig > 10)) { throw NotInRange<int>(sig_fig, 1, 10); }
		}
		catch (NotInRange<int>) {
			// Catch the not in range exception
		}
	}
	catch (NotInRange<int>) {} // Catch the thrown exception from within the typeFailure catch
	cout << endl;
	(Experiments[option_report_name])->experiment_report(sig_fig); // View the measurements for the experiment, using the name of the experiment as the key

}

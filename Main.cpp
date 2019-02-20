// Author: Alexander Jenkins
// ID: 9884664
// The main program, includes the creating of the journal, start up message and main menu functionalities

#include"Measurement.h"
#include"Experiment.h"
#include"Interface.h"
#include"Exceptions.h"
#include"Journal.h"
#include"Functions.h"
#undef max

int main() {

	// Create an add measurement menu
	vector<string> main_options;
	// Push back the options onto the vector of options
	main_options.push_back("ADD AN EXPERIMENT"); // option 1 (element 0 + 1)
	main_options.push_back("DELETE AN EXPERIMENT"); // option 2
	main_options.push_back("VIEW AN EXPERIMENT"); // option 3
	main_options.push_back("MODIFY AN EXPERIMENT"); // option 4
	main_options.push_back("GENERATE A REPORT"); // option 5
	Menu main_menu("MAIN MENU", main_options);

	// Create the journal to store all the users experiments in
	Journal journal;
	journal.start_message(); // Display the start up message 
	system("pause");

	int option_main{ 0 };
	do {

		cout << main_menu << endl; // Display the menu
		cout << "Please enter an option: "; // Enter an option

		// Exception handling
		exception_handling_functions::option_check(option_main, main_menu.get_all_options()); // Check the input
		cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (option_main) {
		case 1:
			// The user wishes to add an experiment, return this function
			journal.add_experiment();
			break;

		case 2:
			// The user wishes to delete an experiment, return this function
			journal.delete_experiment();
			break;

		case 3:
			// The user wishes to view an experiment, return this function
			journal.view_experiment();
			break;

		case 4:
			// The user wishes to modify an experiment, return this function
			journal.modify_experiment();
			break;

		case 5:
			// The user wishes to generate an experimental report, return this function
			journal.generate_report();
			break;

		case 6:
			cout << "\t\t ==========================================" << endl;
			cout << "\t\t          Terminating the program.         " << endl;
			cout << "\t\t ==========================================" << endl;
			cout << "\t\t                 Goodbye!                  " << endl;
			cout << "\t\t ==========================================" << endl;
			cout << endl;
			break;

		default: // Set a default menu
			cout << "Please enter a value between 1 and " << main_options.size() + 1 << "." << endl;
			break;

		}
	} while (option_main != 6); // While not returning to the main menu, display the add measurement menu again


	return 0;
}

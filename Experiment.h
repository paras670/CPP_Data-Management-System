// Author: Alexander Jenkins
// ID: 9884664
// This file is for the Experiment class and its declarations

#ifndef EXPERIMENT_INCLUDE
#define EXPERIMENT_INCLUDE

#include"Measurement.h"
#include<vector>
#include<memory>
#include<iostream>

using namespace std;

class Experiment{
private:
	string name; // A string for the name of the experiment
	vector<shared_ptr<Measurement>> measurements; // A vector pairing together a type of measurement and the name of the measurement
public:
	Experiment(); // Default constructor
	Experiment(string new_name); // Parameterised constructor
	~Experiment(); // Destructor

	// Member functions to add measurements
	const void add_measurements(); // Display the menu for which measurement type to add
		const void add_meas_manually(const int type_chosen); // Adding measurements manually
		const void add_meas_file(const int type_chosen); // Adding measurements from a file
		const void how_to_add_meas(const int type_chosen); // A menu displaying the options on how to add a measurement

	// A member function to display the modify or delete menu
		const void ModifyOrDelete();

	// Member function to delete measurements
	const void delete_measurements(); // A function to delete measurements 
		const void delete_specific(); // A function to delete a specific measurement
		const void delete_dates(); // A function to delete a specific date measurement
		const void delete_which_type(); // A function to delete a specific type of measurement
		const void delete_types(string search_type); // A function to delete all measurements of a specific type

	// Member function to modify measurements
	const void modify_measurements(); // A function to modify existing measurements

	// Generate a report
	const void experiment_report(const int sig_fig); // A function to generate a report for an experiment, takes the number of significant figures as parameters
		const void measurement_analysis(vector<shared_ptr<Measurement>> meas_to_analyse); // A function to output the measurments analysed

	// Member functions to view measurements
	const void view_measurements(); // View the measurements in different ways
		const void search_dates(); // Search for a specific date in the measurements and display them
		const void search_types(string search_type); // Search for a specific type in the measurements and display them
		const void search_which_type(); // Searching the measurements by type
};

#endif
// Author: Alexander Jenkins
// ID: 9884664
// The Journal header file, includes all the declarations of the journals functionality (used in main.cpp)

#ifndef JOURNAL_INCLUDE
#define JOURNAL_INCLUDE

#include"Experiment.h"
#include"Interface.h"
#include<map>

class Journal{
	// A class for the journal in which experiments and measurements are contained in a map
private:
	// Create a map which contains a key (the experiments name) and a unique pointer to an experiment
	map<string, unique_ptr<Experiment>> Experiments; 
public:
	Journal(); // Default constructor
	~Journal(); // Destructor

	const void start_message(); // A function to display the startup message 
	const void add_experiment(); // A function to add an experiment
	const void delete_experiment(); // A function to delete an experiment
	const void view_experiment(); // A function to view experiments
	const void modify_experiment(); // A function to modify an experiment
	const void generate_report(); // A function to generate a report, including analysis
	
};


#endif
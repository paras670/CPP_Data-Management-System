// Author: Alexander Jenkins
// ID: 9884664
// The header file for the menu and table class interfaces 

#ifndef INTERFACE_INCLUDE
#define INTERFACE_INCLUDE

#include<iostream>
#include<string>
#include<vector>
#include"Measurement.h"
#include<memory>

using namespace std;

class Menu {
	// A class for the menu of the user interface
private:
	string title; // A string containing the title of the menu
	vector<string> options; // A vector of strings containing each of the menu's options
public:

	// Allow for the user to possibly add options (e.g. name of experiments and measurement menus)
	Menu(string new_title, vector<string> new_options); // Parameterised constructor
	~Menu(); // Destructor

	// A function to return all of the menus options
	const vector<string> get_all_options();

	// Friend of the class
	friend ostream & operator<<(ostream&os, const Menu &m); // Overload the operator<< for a menu
};


class Table {
	// A class for the table of measurements for an experiment
protected:
	// Made protected so the derived class Table_noSE can access them
	string title; // A string containing the title of the table
	vector<shared_ptr<Measurement>> measurements; // A vector of pointers to the measurement abstract base class
public:
	// Parameterised constructor
	Table(string new_title, vector<shared_ptr<Measurement>> new_measurements); // Allow for the user to add measurements to a table
	~Table(); // Destructor

	// Friend of the class
	friend ostream & operator<<(ostream&os, const Table &t); // Overload the operator<< for a table
};


class Table_Combined_Error : public Table {
	// A derived class for a table with a combined error, i.e. no systematic error 
public:
	// Parameterised constructor
	Table_Combined_Error(string new_title, vector<shared_ptr<Measurement>> new_measurements); // Allow for the user to add measurements to a table
	~Table_Combined_Error(); // Destructor

	// Friend of the class
	friend ostream & operator<<(ostream&os, const Table_Combined_Error &t); // Overload the operator<< for a table


};
#endif
// Author: Alexander Jenkins
// Student ID: 9884664
// A .h file containing the Measurement abstract base class and different types of measurement

#ifndef MEASUREMENT_INCLUDE // A header guard to ensure this header file is included only once
#define MEASUREMENT_INCLUDE

#include<string>
#include<vector>
#include<cmath>
#include<iostream>
#include<iomanip>

using namespace std;

class Measurement {
	// An abstract base class for a measurement
	// Contains two purely virtual functions, to return the name of the measurement and another to return the units
protected:
	string date; // A string for the date the measurement was taken
	double value, error, syst_error; // Value, error and systematic error of the measurement taken
public:
	Measurement(); // Default constructor
	Measurement(string new_date, double new_value, double new_error, double new_syst_error); // Parameterised constructor

	virtual ~Measurement(); // Virtual destructor for a measurement

	// Accessor functions
	const string get_date(); // Return the date of the measurement
	const double get_value(); // Return the value of measured
	const double get_error(); // Return the error measured
	const double get_syst_error(); // Return the systematic error for the measurement
	const double combine_error(); // Combine the error for the measurement, replace the error with the combined error

	virtual const string name() = 0; // A purely virtual function for the name of the measurement
	virtual const string units() = 0; // A purely virtual function for the units of the measurement

};

class Length : public Measurement {
	// A class for Length, which is a measurement with name 'Length' and units 'm'
	// The protected member data and accessor functions are inherited from the Measurement abstract base class
public:

	// Default constructor
	Length(); 

	// Inherit the parameterised constructor from Measurement
	Length(string new_date, double new_value, double new_error, double new_syst_error);

	// Destructor
	~Length();

	// Accessors
	const string name(); // Override the name to 'Length'
	const string units(); // Override the units to 'm'
};

class Time : public Measurement {
	// A class for Time, a type of measurement
public:

	// Default constructor
	Time();

	// Parameterised constructors
	Time(string new_date, double new_value, double new_error, double new_syst_error);

	// Destructor
	~Time();

	// Accessors
	const string name();
	const string units();
};

class Mass : public Measurement {
	// A class for Mass, a type of measurement

public:

	// Default constructor
	Mass();

	// Parameterised constructors
	Mass(string new_date, double new_value, double new_error, double new_syst_error);

	// Destructor
	~Mass();

	// Accessors
	const string name();
	const string units();
};

class Amount : public Measurement {
	// A class for Amount, a type of measurement

public:

	// Default constructor
	Amount();

	// Parameterised constructor
	Amount(string new_date, double new_value, double new_error, double new_syst_error);

	// Destructor
	~Amount();

	// Accessors
	const string name();
	const string units();
};

class Current : public Measurement {
	// A class for Current, a type of measurement

public:

	// Default constructor
	Current();

	// Parameterised constructor
	Current(string new_date, double new_value, double new_error, double new_syst_error);

	// Destructor
	~Current();

	// Accessors
	const string name();
	const string units();
};

class Temperature : public Measurement {
	// A class for Temperature, a type of measurement
private:
protected:
public:

	// Default constructor
	Temperature();

	// Parameterised constructor
	Temperature(string new_date, double new_value, double new_error, double new_syst_error);

	// Destructor
	~Temperature();

	// Accessors
	const string name();
	const string units();
};

#endif // Included the header file only once
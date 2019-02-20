// Author: Alexander Jenkins
// ID: 9884664
// The .cpp file for Measurement.h

#include"Measurement.h"
#include"Functions.h"

//// MEASUREMENT FUNCTION DEFINITIONS ////

Measurement::Measurement() {
	date = "";
	value = 0;
	error = 0;
	syst_error = 0;
}

Measurement::Measurement(string new_date, double new_value, double new_error, double new_syst_error) {
	date = new_date;
	value = new_value;
	error = new_error;
	syst_error = new_syst_error;
}

Measurement::~Measurement() {
	cout << "Measurement deleted from memory." << endl; // Aware the user that there measurement has been deleted
}

const string Measurement::get_date() { return date; }
const double Measurement::get_value() { return value; } 
const double Measurement::get_error() { return error; }
const double Measurement::get_syst_error() { return syst_error; }

const double Measurement::combine_error() {
	// Combine the errors, returning a double
	double combined_error = sqrt(pow(error, 2) + pow(syst_error, 2)); // Combine the error in quadrature
	return combined_error;
}

//// LENGTH FUNCTION DEFINITIONS ////

// Default constructor
Length::Length() : Measurement::Measurement(){}

// Parameterised constructors
Length::Length(string new_date, double new_value, double new_error, double new_syst_error) : Measurement::Measurement(new_date, new_value, new_error, new_syst_error) {}

// Destructor
Length::~Length(){}

// Accessors
const string Length::name() { return "Length"; }
const string Length::units() { return "m"; } // The SI unit of Meters



//// TIME FUNCTION DEFINITIONS ////

// Default constructor
Time::Time() : Measurement::Measurement() {}

// Parameterised constructors
Time::Time(string new_date, double new_value, double new_error, double new_syst_error) : Measurement::Measurement(new_date, new_value, new_error, new_syst_error) {}

// Destructor
Time::~Time() {}

// Accessors
const string Time::name() { return "Time"; }
const string Time::units() { return "s"; } // The SI unit of Seconds


//// MASS FUNCTION DEFINITIONS ////

// Default constructor
Mass::Mass() : Measurement::Measurement() {}

// Parameterised constructors
Mass::Mass(string new_date, double new_value, double new_error, double new_syst_error) : Measurement::Measurement(new_date, new_value, new_error, new_syst_error) {}

// Destructor
Mass::~Mass() {}

// Accessors
const string Mass::name() { return "Mass"; }
const string Mass::units() { return "Kg"; } // The SI unit of Kilograms



//// AMMOUNT FUNCTION DEFINITIONS ////

// Default constructor
Amount::Amount() : Measurement::Measurement() {}

// Parameterised constructors
Amount::Amount(string new_date, double new_value, double new_error, double new_syst_error) : Measurement::Measurement(new_date, new_value, new_error, new_syst_error) {}

// Destructor
Amount::~Amount() {}

// Accessors
const string Amount::name() { return "Ammount"; }
const string Amount::units() { return "Mol"; } // The SI unit of Moles



//// CURRENT FUNCTION DEFINITIONS ////

// Default constructor
Current::Current() : Measurement::Measurement() {}

// Parameterised constructors
Current::Current(string new_date, double new_value, double new_error, double new_syst_error) : Measurement::Measurement(new_date, new_value, new_error, new_syst_error) {}

// Destructor
Current::~Current() {}

// Accessors
const string Current::name() { return "Current"; }
const string Current::units() { return "A"; } // The SI unit of Amps



//// TEMPERATURE FUNCTION DEFINITIONS ////

// Default constructor
Temperature::Temperature() : Measurement::Measurement() {}

// Parameterised constructors
Temperature::Temperature(string new_date, double new_value, double new_error, double new_syst_error) : Measurement::Measurement(new_date, new_value, new_error, new_syst_error) {}

// Destructor
Temperature::~Temperature() {}

// Accessors
const string Temperature::name() { return "Temperature"; }
const string Temperature::units() { return "K"; } // The SI unit of Kelvin
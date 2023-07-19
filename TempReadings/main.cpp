#include "../std_lib_facilities.h"
#include "reading.h"
#include "store_temps.h"

// Exercises 2., 3. and 4. from chapter §10, Programming : principles and practice using C++, Bjarne Stroustrup.
// 1. Program reads temeprature readings from user and creates raw_temps.txt.
// 2. Program reads the data from raw_temps.txt into a vector and then calculates the mean and median
//    temperatures with 2 functions.
// 3. It automatically converts Fahrenheit readings to Celsius.

double get_mean(const vector<Reading>& readings)
{
	double sum{};
	for (const Reading& r : readings)
		sum += r.temperature;
	return sum / readings.size();
}

double get_median(const vector<Reading>& readings)
{
	vector<Reading> temp = readings;
	sort(temp.begin(), temp.end(), [](Reading a, Reading b) { return a.temperature > b.temperature; });
	
	int size{ (int)temp.size() };
	if (size % 2)
		return temp[((size + 1) / 2) - 1].temperature;
	else
		return ((double)temp[(size / 2) - 1].temperature + temp[size / 2].temperature) / 2;
}

int main()
try 
{
	store_temps();

	ifstream ifs{ "raw_temps.txt" };
	if (!ifs)
		error("file opening failed");

	vector<Reading> readings{read_temps(ifs)};
	cout << "Mean: " << get_mean(readings) << '\n' << "Median: " << get_median(readings) << '\n';
	write_temps(cout, readings);
}
catch (exception& e)
{
	cerr << "Error: " << e.what();
}
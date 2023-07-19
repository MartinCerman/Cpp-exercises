#include "../std_lib_facilities.h"
#include "reading.h"

void store_temps()
try
{
	cout << "Enter temperature readings separated by a space or an enter.\n"
		<< "Use \"hour temperature unit\" format ('f' for Fahrenheit or 'c' for Celsius), end reading with '"
		<< reading_terminator << "':\n";
	vector<Reading> readings{ read_temps(cin, reading_terminator) };

	ofstream ofs{ "raw_temps.txt" };
	write_temps(ofs, readings);
}
catch (exception& e)
{
	cerr << e.what();
}
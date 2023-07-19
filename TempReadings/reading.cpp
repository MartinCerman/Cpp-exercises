#include "../std_lib_facilities.h"
#include "reading.h"

vector<Reading> read_temps(istream& is, char terminator)
{
	vector<Reading> temp;
	Reading reading{};
	while (is >> reading.hour >> reading.temperature >> reading.unit)
	{
		if (reading.unit == 'f')
		{
			reading.temperature = (reading.temperature - 32) * double(5) / 9;
			reading.unit = 'c';
		}
		temp.push_back(reading);
	}
	if (is.eof())
		return temp;
	if (is.fail())
	{
		is.clear();
		char ch{};
		is >> ch;
		if (ch == terminator)
			return temp;
		else
		{
			is.unget();
			is.clear(std::ios_base::failbit);
			error("failed reading");
		}
	}
	if (is.bad())
		error("bad reading");
}

void write_temps(ostream& os, const vector<Reading>& readings)
{
	for (const Reading& r : readings)
		os << r.hour << ' ' << r.temperature << ' ' << r.unit << '\n';
}

#pragma once

constexpr char reading_terminator = '*';

struct Reading
{
	int hour;
	double temperature;
	char unit;
};

// Reads a series of Readings, convert from Fahrenheit to Celsius is it reads
vector<Reading> read_temps(istream& is, char terminator = reading_terminator);
// Writes a series of Readings.
void write_temps(ostream& os, const vector<Reading>& readings);

void store_temps();
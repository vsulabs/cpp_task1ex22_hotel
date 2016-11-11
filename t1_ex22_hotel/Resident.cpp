#include "Resident.h"
#include <iostream>
using namespace std;

Resident::Resident(string fio, int idN, const myDates& b, const myDates& e) : FullName(fio) {
	if (idN <= 0)
		throw invalid_argument("для номера введены некорректные значения");
	number = idN;
	if (b < e) {
		Begin = myDates(b);
		End = myDates(e);
	}
	else {
		Begin = myDates(e);
		End = myDates(b);
	}
	days_in_number = myDates::daysBetween(b, e);
}

Resident::Resident(string fio, int idN, int y, int m, int d, int time) : FullName(fio)
{
	if (idN <= 0 || time < 1)
		throw invalid_argument("для номера введены некорректные значения");
	number = idN;
	Begin = myDates(y, m, d);
	End = myDates(Begin + time);
	
	days_in_number = time;
}

string Resident::toString() const {
	string res = 
		"fullName \t: \t" + get_fullName() + "\r\n"+
		"Номер \t\t: \t" + to_string(number) + "\r\n"+
		"Dates \t\t: \t" + Begin.toString() + " - " + End.toString();
	return res;
}

void Resident::CopyBy(const Resident& other) {
	FullName = other.get_fullName();
	Begin = other.Begin;
	End = other.End;
	number = other.number;
	days_in_number = other.days_in_number;
}
void Resident::Print() const {
	cout << "  FullName\t:\t" + get_fullName() << endl;
	cout << "  NumberID\t:\t" + to_string(number) << endl;
	cout << "  Dates\t\t:\t" + Begin.toString() + " - " + End.toString() << endl;
}

Resident::~Resident()
{
}


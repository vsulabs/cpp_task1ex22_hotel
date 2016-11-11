#include "myDates.h"
#include <iostream>

using namespace std;

myDates::myDates(int d, int m, int y) {	// конструктор, может служить конструктором без параметров
	if (d < MinDay || d > MaxDay || m < MinMonth || m > MaxMonth || y < MinYear || y > MaxYear)
		throw invalid_argument("некорректные значени€");
	day = d;
	month = m;
	year = y;
}
// копирование с помощью начальной инициализации. ѕредполагаетс€, что уже созданный экземпл€р проходил проверку на корректность данных
myDates::myDates(const myDates& other) : year(other.year), month(other.month), day(other.day) { }

myDates::myDates(std::string& dataStr)
{
	if (dataStr.length() != date_size - 1)
		throw invalid_argument("строка имеет неверный формат");
	dataStr[date_size - 1] = '\0';

	bool isOkNumber =
		(*(dataStr.begin() + 2) == '.') && (*(dataStr.begin() + 5) == '.') ||
		(*(dataStr.begin() + 2) == ',') && (*(dataStr.begin() + 5) == ',') ||
		(*(dataStr.begin() + 2) == '/') && (*(dataStr.begin() + 5) == '/');

	string::iterator it = dataStr.begin();
	for (; it != dataStr.end() && isOkNumber; ++it) {
		if (dataStr.begin() + 2 != it && dataStr.begin() + 5 != it)
			isOkNumber = ((*it) <= '9') && ((*it) >= '0');
	}

	if (!isOkNumber || dataStr.begin() + 10 != it)
		throw invalid_argument("строка имеет неверный формат");

	string::size_type sz;

	day = stoi(dataStr, &sz);
	dataStr = dataStr.substr(sz + 1);
	month = stoi(dataStr, &sz);
	dataStr = dataStr.substr(sz + 1);
	year = stoi(dataStr, &sz);	
}

void myDates::copy_by(const myDates& other) {
	day = other.day;
	month = other.month;
	year = other.year;
}
myDates& myDates::operator=(const myDates& other) {
	if (*this != other) {
		day = other.day;
		month = other.month;
		year = other.year;
	}
	return *this;
}

bool myDates::operator ==(const myDates& other) const {
	return (day == other.day && month == other.month && year == other.year);
}
bool myDates::operator !=(const myDates& other) const {
	return (day != other.day || month != other.month || year != other.year);
}
bool myDates::operator >(const myDates& other) const {
	return (
		(year > other.year) ||
		(year == other.year && month > other.month) ||
		(year == other.year && month == other.month && day > other.day));
}
bool myDates::operator <(const myDates& other) const {
	return 
		(year < other.year) ||
		(year == other.year && month < other.month) ||
		(year == other.year && month == other.month && day < other.day);
}
bool myDates::operator >=(const myDates& other) const {
	return 
		(day == other.day && month == other.month && year == other.year) || (
		(year > other.year) ||
		(year == other.year && month > other.month) ||
		(year == other.year && month == other.month && day > other.day));
}


bool myDates::operator <=(const myDates& other) const {
	return 
		(day == other.day || month == other.month || year == other.year) || (
		(year < other.year) ||
		(year == other.year && month < other.month) ||
		(year == other.year && month == other.month && day < other.day));
}

myDates myDates::operator + (int days) const {
	myDates tmp;
	tmp.year = year + days / DaysPerYear;
	days %= DaysPerYear;
	tmp.month = month + days / DaysPerMonth;
	days %= DaysPerMonth;
	tmp.day = day + days;
	return *this;
}

myDates myDates::operator+ (const myDates& other) const {
	myDates tmp(*this);
	tmp = tmp + myDates::daysBetween(*this, other);
	return tmp;
}

std::ostream& myDates::operator << (std::ostream& output) const {
	output << endl << "Day: " << day << ". Month: " << month << ". Year: " << year << endl;
	return output;
}
std::istream& myDates::operator >> (std::istream& input) {
	cout << "введите год, мес€ц, день" << endl;
	input >> year >> month >> day;
	return input;
}

int myDates::daysBetween(const myDates& begin, const myDates& end) {
	int res = (end.year - begin.year) * DaysPerYear + (end.month - begin.month) * DaysPerMonth + (end.day - begin.day) + 1;
	if (res < 0)
		res = -res;
	return res;
}

std::string myDates::toString() const {
	return std::to_string(day) + "." + to_string(month) + "." + to_string(year);
}

void myDates::print() const {
	cout << "Day: " << day << ". Month: " << month << ". Year: " << year << endl;
}
void myDates::printFormat() const {
	cout << day << "." << month << "." << year << endl;
}
void myDates::days_correct(myDates & begin, myDates & end) {
	if (end < begin) {
		myDates tmp = myDates(begin);
		begin = myDates(end);
		end = myDates(tmp);
	}
}

bool myDates::dates_crossed(const myDates& fixedBegin, const myDates& fixedEnd, const myDates& in, const myDates& out){
	return !(
		in < fixedBegin &&
		out < fixedBegin ||
		in > fixedEnd &&
		out > fixedBegin); 
}

myDates::~myDates() { }

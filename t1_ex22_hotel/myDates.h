#pragma once
#include <string>

static const int MaxYear = 2020;
static const int MaxMonth = 12;
static const int MaxDay = 31;

static const int MinYear = 1950;
static const int MinMonth = 1;
static const int MinDay = 1;

static const int DaysPerYear = 365;
static const int DaysPerMonth = 31;

static const int date_size = 11;

class myDates		// ����
{
	int day;		// ����
	int month;		// �����
	int year;		// ���	
public:
	// �����������, ����� ������� ������������� ��� ����������
	myDates(
		int d = MinDay, 
		int m = MinMonth, 
		int y = MinYear );	
	myDates(const myDates& other);					// ����������� �����������
	myDates(std::string& dataStr);					// ������� �� ������
	
	void copy_by(const myDates& other);

	int getDay()			const { return day; }	// �������� ������� � ���� ����
	int getMonth()			const { return month; }	// �������� ������� � ���� �����
	int getYear()			const { return year; }	// �������� ������� � ���� ���

	void print()			const ;					// ������� �� ����� ������� ���� � ��������� ����
	void printFormat()		const ;					// ������� �� ����� ������� ���� � ������� ��.��.����.
	
	myDates& operator =(const myDates& other);		// �������� ������������ ������������ ������������ 

	// ��������� ���������

	bool operator ==(const myDates& other) const;
	bool operator !=(const myDates& other) const;
	bool operator > (const myDates& other) const;
	bool operator < (const myDates& other) const;
	bool operator >=(const myDates& other) const;
	bool operator <=(const myDates& other) const;

	myDates operator + (int days) const;
	myDates operator + (const myDates& other) const;

	// ������������� ��������� �����-������
	std::ostream& operator << (std::ostream& output) const;
	std::istream& operator >> (std::istream& input);
	
	std::string toString()	const;			// ���������� ���� � ���� ������
	
	// fixedBegin � fixedOut - ��������, �� ��������� � ������� �������� ��������
	// ���������� 1, ���� �������� ��� in out ������������ � ���������� fixedBegin, fixedEnd
	// ���������� 0, ���� �� ���� in ��� ���� out �� �������� � �������� fixedBegin, fixedEnd
	static bool dates_crossed(
		const myDates& fixedBegin, 
		const myDates& fixedEnd, 
		const myDates& in,
		const myDates& out);
	// ������� ���������� ���� ����� ����� ������
	static int daysBetween(
		const myDates& begin, 
		const myDates& end); 
	// ������ ������� �������� begin � end, ���� end ������ ��� begin
	static void days_correct(
		myDates& begin,
		myDates& end);
	~myDates();

};

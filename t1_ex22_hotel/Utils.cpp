#include "Utils.h"
#include <iostream>
using namespace std;

void Write(std::string str) {
	cout << str << endl;
}
void Write(std::string str, int count) {
	cout << str;
	for (int i = 0; i < count; ++i)
		cout << endl;
}

int InputInt(string message)
{
	char s[max_size];
	char *str;
	bool isOkNumber = true;
	int res;
	Write(message);
	do {
		if (!isOkNumber)
			cout << "bad input, try again!" << endl;
		cout << "--> ";

		cin.getline(s, max_size);
		//gets(s);
		isOkNumber = true;
		s[max_size - 1] = '\0';

		str = s;
		if (s[0] == '-' || s[0] == '+')
			str++;
		if (*str == '\0')
			isOkNumber = false;
		for (; *str != '\0' && isOkNumber; str++)
			isOkNumber = isOkNumber && (*str >= '0' && *str <= '9');
	} while (!isOkNumber);
	res = atoi(s);
	return res;
}

int InputUMax(string message, int max)
{
	int res;
	Write(message);
	do {
		cout << 0 << " < input <= " << max;
		res = InputInt();
	} while (res <= 0 || res > max);	
	return res;
}

RoomStatus InputRoomStatus()
{
	cout << "������� ������ ������ �� 2 �� 5" << endl << 
		"(������, ��������, �������� � ���� ��������������)" << endl;
	int res = InputInt();
	if (res < 2)
		res = 2;
	else if (res > 5)
		res = 5;
	
	switch (res)
	{
	case 2:
		return rs_economy;
	case 4:
		return rs_halflux;
	case 5:
		return rs_lux;
	default:
		return rs_standart;
	}	
}

bool InputUVal(string message, int& val)
{
	char s[max_size];
	char *str;
		
	cout << message << endl;
	cout << "--> ";

	cin.getline(s, max_size);
	
	bool isOkNumber = true;
	s[max_size - 1] = '\0';

	str = s;
	if (s[0] == '+')
		str++;
	if (*str == '\0')
		isOkNumber = false;
	for (; *str != '\0' && isOkNumber; str++)
		isOkNumber = isOkNumber && (*str >= '0' && *str <= '9');
	if (!isOkNumber)
		return false;

	val = atoi(s);
	return true;
}

bool InputFullName(string& fullName)
{
	cout << "������� ���" << endl;
	cout << "--> ";

	getline(cin, fullName);
	if (fullName.length() == 0)
		return false;
	DelSpaces(fullName);
	
	
	for (string::iterator it = fullName.begin(); it != fullName.end() - 1; ++it)
		if ((*it) == ' ' && (*(it + 1) == ' '))
			fullName.erase(it);
	return true;
}

bool InputDates(myDates& date, std::string message) {
	string s;
	if (message != "")
		Write(message + "\r\n");
	cout << "������ ����: ��.��.����" << endl;
	cout << MinDay << "\t< �� <\t" << MaxDay << endl;
	cout << MinMonth << "\t< �� <\t" << MaxMonth << endl;
	cout << MinYear << "\t<����<\t" << MaxYear << endl;
	cout << "--> ";
	getline(cin, s);
	
	DelSpaces(s);
		 
	if (s.length() != date_size - 1)
		return false;
	s[date_size - 1] = '\0';
	bool isOkNumber;
	isOkNumber =
		(*(s.begin() + 2) == '.') && (*(s.begin() + 5) == '.') ||
		(*(s.begin() + 2) == ',') && (*(s.begin() + 5) == ',') ||
		(*(s.begin() + 2) == '/') && (*(s.begin() + 5) == '/');

	string::iterator it = s.begin();
	for (; it != s.end() && isOkNumber; ++it) 
		if (s.begin() + 2 != it && s.begin() + 5 != it)
			isOkNumber = ((*it) <= '9') && ((*it) >= '0');
	
	if (!isOkNumber || s.begin() + 10 != it)
		return false;

	int d, m, y;
	string::size_type sz;

	d = stoi(s, &sz);
	s = s.substr(sz + 1);
	m = stoi(s, &sz);
	s = s.substr(sz + 1);
	y = stoi(s, &sz);
	
	date = myDates(d, m, y);
	return true;
}

HotelNumber InputHotelNumber(int currentID) {
	if (currentID < 0) {
		int id;
		if (!InputUVal("������� ID ������: ", id))
			throw exception("����������� ������ id ������������ ������");
		currentID = id;
	}
	int rooms = InputUMax("������� ����� ������", maxRooms);
	int sleepingAreas = InputUMax("������� ����� �������� ����", maxSleep);
	RoomStatus status = InputRoomStatus();

	return HotelNumber(rooms, status, currentID, sleepingAreas);
}

Resident InputResident() {
	int id;
	if (!InputUVal("������� ����� �������: ", id))
		throw exception("����������� ������ id ������");

	string fullName;
	if (!InputFullName(fullName))
		throw exception();

	myDates beginDate, endDate;
	if (!InputDates(beginDate))
		throw exception("����������� ������� ����");
	if (!InputDates(endDate))
		throw exception("������������ ���� ������� �� ������");
	myDates::days_correct(beginDate, endDate);
	return Resident(fullName, id, beginDate, endDate);
}

Visit InputVisit() {
	try {
		Resident resident = InputResident();		
		HotelNumber number = InputHotelNumber();
		return Visit(&resident, &number);
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
		throw exception("������ �����");
	}	
}

bool yes_or_no(string message) {
	cout << message << endl;
	cout << "1 - yes, 0 - no" << endl << endl;
	int k;
	bool errorInput = false;
	do {
		if (errorInput)
			cout << "������������ ����, ���������!" << endl;
		k = InputInt();
		errorInput = k < 0 || k > 1;
	} while (errorInput);
	return k == 1;
}

void Trim(std::string &str) {
	const auto strBegin = str.find_first_not_of(" \t");
	if (strBegin != std::string::npos) {
		const auto strEnd = str.find_last_not_of(" \t");
		const auto strRange = strEnd - strBegin + 1;
		str = str.substr(strBegin, strRange);
	}
	else
		return;
	/*	str = "";
	if (str.length() == 0)
		return;*/
	std::string result = "";
	result += static_cast<unsigned char>(str.at(0));
	for (unsigned int i = 1; i < str.length(); i++)
		if (*(str.begin() + i - 1) != ' ')
			result += static_cast<unsigned char>(tolower(str.at(i)));
		else
			result += static_cast<unsigned char>(str.at(i));
		
	str = result;
}
void DelSpaces(std::string &str)
{
	std::string result = "";
	Trim(str);
	unsigned i = 0;
	while (i < str.length()) {
		while (str[i] != ' ' && i < str.length()) {
			result.push_back(str[i]);
			i++;
		}
		if (str[i] == ' ' && i < str.length())
			result.push_back(' ');
		while (str[i] == ' ' && i < str.length())
			i++;
	} // while
	str = result;
}

void task_number_add(Hotel& hotel)
{
	hotel.print_all_id();
	try {
		HotelNumber num = InputHotelNumber();
		if (!hotel.add_number(new HotelNumber(num)))
			cout << "! Attention: ����� ����� ��� ����������" << endl << endl;
		else {
			cout << "���������� ������ �������" << endl;
			if (yes_or_no("����������� ������� �������� ����?"))
				hotel.print_numbers();
		}
	}
	catch (const std::invalid_argument& e) {
		cerr << e.what() << endl;
	}
	catch (const std::exception& e) {
		cerr << e.what() << endl;
	}
}

void task_number_delete(Hotel& hotel)
{
	hotel.print_all_id();
	int id = InputInt("������� id �������, ������� ������� �������");
	if (hotel.delete_number(id)) {
		cout << "����� ������ �� ��������� �����." << endl;
		if (yes_or_no("����������� ������� �������� ����?"))
			hotel.print_numbers();
	}
	else {
		cout << "�� ������� ������� ������� �� ��������� ID." << endl;
	}
}
void task_number_edit(Hotel& hotel)
{
	int id;
	if (!InputUVal("������� id ������", id)) {
		cout << "id ������ �����������" << endl;
		return;
	}
	try {
		HotelNumber num = InputHotelNumber(id);
		if (!hotel.edit_number(id, num))
			cout << "�� ������� ��������������� ����� � id = " << id << endl;
		else {
			cout << "�������������� ������ �������" << endl;
			if (yes_or_no("����������� ������� �������� ����?"))
				hotel.print_numbers();
		}
	}
	catch (const std::exception& e) {
		cerr << e.what();
	}
}
void task_visit_add(Hotel& hotel)
{
	hotel.print_all_id();
	try {
		Resident guest = InputResident();
		if (!hotel.add(new Resident(guest)))
			Write("�� ������� �������� ���������");
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
	}
}
void task_visit_delete(Hotel& hotel)
{
	hotel.print_all_id();
	int id;
	if (!InputUVal("������� id ������:", id)) {
		Write("id ������ �����������");
		return;;
	}
	myDates begin;
	if (!InputDates(begin, "������� ���� ���������:")) {
		cout << "���� ������� �������" << endl;
		return;;
	}
	if (hotel.delete_visit(id, begin))
		cout << "�������� ������ �������" << endl;
	else
		cout << "�� ������� ���������� �������� �� ��������� ������ ������" << endl;
}

void task_visit_edit(Hotel& hotel)
{
	hotel.print_all_id();
	try {
		Resident guest = InputResident();
		int id;
		if (!InputUVal("������� id ������", id)) {
			Write("id ������ �����������");
			return;;
		}

		myDates begin;
		if (!InputDates(begin, "������� ���� ���������: ")) {
			cout << "���� ������� �������" << endl;
			return;;
		}
		if (hotel.edit(id, begin, guest)) {
			cout << "�������������� ������ �������" << endl;
		}
		else {
			cout << "�� ������� ���������� ��������������" << endl;
		}
	}
	catch (const invalid_argument& e) {
		cerr << e.what() << endl;
	}
	catch (const exception& e){
		cerr << e.what() << endl;
	}
}

void task_search_sleeps(Hotel& hotel)
{
	Write("������� �������� ��� ��� ������ ��������� �������:");
	myDates begin;
	if (!InputDates(begin)) {
		cout << "���� ������� �������" << endl;
		return;;
	}
	myDates end;
	if (!InputDates(end)) {
		cout << "���� ������� �������" << endl;
		return;;
	}
	myDates::days_correct(begin, end);
	int sleeps;
	if (!InputUVal("�������, ����� ���������� �������� ���� ����������:", sleeps)) {
		Write("������������ ����");
		return;;
	}

	set<int> nums;
	hotel.SearchBySleeps(nums, sleeps, begin, end);
	if (nums.size() == 0)
		Write("�� ������� ����� ������");
	else {
		std::cout << "��������� ������ �� ������ ���� �� ���������� ��������: " << std::endl;
		for (set<int>::iterator it = nums.begin(); it != nums.end(); ++it)
			std::cout << "id - " << (*it) << endl;
	}
	cout << endl;
	nums.clear();
}
void task_search_cost(Hotel& hotel)
{
	Write("������� �������� ��� ��� ������ ��������� �������:");
	myDates begin;
	if (!InputDates(begin)) {
		cout << "���� ������� �������" << endl;
		return;;
	}
	myDates end;
	if (!InputDates(end)) {
		cout << "���� ������� �������" << endl;
		return;;
	}
	myDates::days_correct(begin, end);
	int top;
	if (!InputUVal("������� ������� ������� �� ��������� �� ��������� ������:", top)) {
		Write("������������ ����");
		return;;
	}
	int low = 0;
	if (yes_or_no("������ �� ������� ������ �������?"))
		if (!InputUVal("������� ������ ����� ��������� �� ��������� ������:", low)) {
			Write("������������ ����");
			low = 0;
		}
	set<int> nums;
	hotel.SearchByPrice(nums, begin, end, top, low);
	if (nums.size() == 0)
		Write("�� ������� ����� ������");
	else {
		std::cout << "��������� ������ �� ������ ���� �� ���������� ��������: " << std::endl;
		for (set<int>::iterator it = nums.begin(); it != nums.end(); ++it)
			std::cout << "id - " << (*it) << endl; // << "\t\t" << (*it).second << std::endl;
	}
	cout << endl;
	nums.clear();
}
void task_data_numbers(Hotel& hotel)
{
	int top;
	if (!InputUVal("Top N. ������� N:", top)) {
		Write("������������ ����");
		return;;
	}
	Profit_numbers nums;
	hotel.top_numbers(nums, top);

	if (nums.size() == 0)
		Write("�� ������� ����� ������");
	else {
		std::cout << "��� " << top << " ����� ���������� �������: " << std::endl;
		int i = 1;
		for (Profit_numbers::iterator it = nums.begin(); it != nums.end(); ++it, ++i)
			std::cout << "#" << i << ".\t" << "����� " <<
			(*it).first->get_ID() << endl << "\t" << "�������: " << "\t" <<
			(*it).second << endl << endl;
	}
	cout << endl;
	while (nums.size() > 0) {
		delete nums.back().first;
		nums.pop_back();
	}
}

void task_data_resident(Hotel& hotel)
{
	int top;
	if (!InputUVal("Top N. ������� N:", top)) {
		Write("������������ ����");
		return;;
	}
	Profit_fullnames names;
	hotel.top_residents(names, top);

	if (names.size() == 0)
		Write("�� ������� ����� �����������");
	else {
		std::cout << "��� " << top << " ����� ���������� �����������: " << std::endl;
		int i = 1;
		for (Profit_fullnames::iterator it = names.begin(); it != names.end(); ++it, ++i)
			std::cout << "#" << i << ".\t" << (*it).first << "\r\n" <<
			"\t" << "������� �� �������: " << (*it).second << endl << endl;
	}
	cout << endl;
	names.clear();
}

void task_data_by_name(Hotel& hotel)
{
	string fname;
	if (!InputFullName(fname)) {
		cout << "������� ������� �������" << endl;
		return;
	}
	vector<Resident* > names;
	hotel.all_visits_by_name(names, fname);
	if (names.size() == 0)
		Write("�� ������� ����� ����� ��������");
	else {
		int i = 1;
		cout << endl << ">>> ��������� ����� " << fname << ":" << endl << endl;
		for (vector<Resident* >::iterator it = names.begin(); it != names.end(); ++it) {
			cout << "# " << i << "." << endl << "�������: " << (*it)->get_number_id() << endl;
			cout << "���� ������ � �������:" << endl;
			(*it)->get_begin().printFormat();
			(*it)->get_end().printFormat();
		}
		while (names.size() > 0) {
			delete names.back();
			names.pop_back();
		}
	}
}
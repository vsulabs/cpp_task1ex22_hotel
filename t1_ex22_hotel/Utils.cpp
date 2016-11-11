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
	cout << "Введите статус номера от 2 до 5" << endl << 
		"(эконом, стандарт, полулюкс и люкс соответственно)" << endl;
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
	cout << "Введите ФИО" << endl;
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
	cout << "Формат даты: дд.мм.гггг" << endl;
	cout << MinDay << "\t< дд <\t" << MaxDay << endl;
	cout << MinMonth << "\t< мм <\t" << MaxMonth << endl;
	cout << MinYear << "\t<гггг<\t" << MaxYear << endl;
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
		if (!InputUVal("Введите ID номера: ", id))
			throw exception("Некорректно введен id гостиничного номера");
		currentID = id;
	}
	int rooms = InputUMax("Введите число комнат", maxRooms);
	int sleepingAreas = InputUMax("Введите число спальных мест", maxSleep);
	RoomStatus status = InputRoomStatus();

	return HotelNumber(rooms, status, currentID, sleepingAreas);
}

Resident InputResident() {
	int id;
	if (!InputUVal("Введите номер комнаты: ", id))
		throw exception("некорректно введен id номера");

	string fullName;
	if (!InputFullName(fullName))
		throw exception();

	myDates beginDate, endDate;
	if (!InputDates(beginDate))
		throw exception("некорректно введена дата");
	if (!InputDates(endDate))
		throw exception("некорректная дата отбытия из номера");
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
		throw exception("ошибка ввода");
	}	
}

bool yes_or_no(string message) {
	cout << message << endl;
	cout << "1 - yes, 0 - no" << endl << endl;
	int k;
	bool errorInput = false;
	do {
		if (errorInput)
			cout << "Некорректный ввод, повторите!" << endl;
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
			cout << "! Attention: Такой номер уже существует" << endl << endl;
		else {
			cout << "Добавление прошло успешно" << endl;
			if (yes_or_no("Распечатать текущий номерной фонд?"))
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
	int id = InputInt("Введите id комнаты, которую следует удалить");
	if (hotel.delete_number(id)) {
		cout << "Номер удален из номерного фонда." << endl;
		if (yes_or_no("Распечатать текущий номерной фонд?"))
			hotel.print_numbers();
	}
	else {
		cout << "Не удалось удалить комнату по заданному ID." << endl;
	}
}
void task_number_edit(Hotel& hotel)
{
	int id;
	if (!InputUVal("Введите id номера", id)) {
		cout << "id введен некорректно" << endl;
		return;
	}
	try {
		HotelNumber num = InputHotelNumber(id);
		if (!hotel.edit_number(id, num))
			cout << "Не удалось отредактировать номер с id = " << id << endl;
		else {
			cout << "Редактирование прошло успешно" << endl;
			if (yes_or_no("Распечатать текущий номерной фонд?"))
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
			Write("Не удалось добавить посещение");
	}
	catch (const exception& e) {
		cerr << e.what() << endl;
	}
}
void task_visit_delete(Hotel& hotel)
{
	hotel.print_all_id();
	int id;
	if (!InputUVal("Введите id номера:", id)) {
		Write("id введен некорректно");
		return;;
	}
	myDates begin;
	if (!InputDates(begin, "Введите дату заселения:")) {
		cout << "дата введена неверно" << endl;
		return;;
	}
	if (hotel.delete_visit(id, begin))
		cout << "удаление прошло успешно" << endl;
	else
		cout << "не удалось произвести удаление по заданному набору данных" << endl;
}

void task_visit_edit(Hotel& hotel)
{
	hotel.print_all_id();
	try {
		Resident guest = InputResident();
		int id;
		if (!InputUVal("Введите id номера", id)) {
			Write("id введен некорректно");
			return;;
		}

		myDates begin;
		if (!InputDates(begin, "Введите дату заселения: ")) {
			cout << "дата введена неверно" << endl;
			return;;
		}
		if (hotel.edit(id, begin, guest)) {
			cout << "Редактирование прошло успешно" << endl;
		}
		else {
			cout << "не удалось произвести редактирования" << endl;
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
	Write("Введите диапазон дат для поиска свободных номеров:");
	myDates begin;
	if (!InputDates(begin)) {
		cout << "дата введена неверно" << endl;
		return;;
	}
	myDates end;
	if (!InputDates(end)) {
		cout << "дата введена неверно" << endl;
		return;;
	}
	myDates::days_correct(begin, end);
	int sleeps;
	if (!InputUVal("Введите, какое количество спальных мест необходимо:", sleeps)) {
		Write("Некорректный ввод");
		return;;
	}

	set<int> nums;
	hotel.SearchBySleeps(nums, sleeps, begin, end);
	if (nums.size() == 0)
		Write("Не удалось найти номера");
	else {
		std::cout << "Свободные номера на данные даты по указанному критерию: " << std::endl;
		for (set<int>::iterator it = nums.begin(); it != nums.end(); ++it)
			std::cout << "id - " << (*it) << endl;
	}
	cout << endl;
	nums.clear();
}
void task_search_cost(Hotel& hotel)
{
	Write("Введите диапазон дат для поиска свободных номеров:");
	myDates begin;
	if (!InputDates(begin)) {
		cout << "дата введена неверно" << endl;
		return;;
	}
	myDates end;
	if (!InputDates(end)) {
		cout << "дата введена неверно" << endl;
		return;;
	}
	myDates::days_correct(begin, end);
	int top;
	if (!InputUVal("Введите верхнюю границу по стоимости за указанный период:", top)) {
		Write("Некорректный ввод");
		return;;
	}
	int low = 0;
	if (yes_or_no("Хотите ли указать нижнюю границу?"))
		if (!InputUVal("Введите нижний порог стоимости за указанный период:", low)) {
			Write("Некорректный ввод");
			low = 0;
		}
	set<int> nums;
	hotel.SearchByPrice(nums, begin, end, top, low);
	if (nums.size() == 0)
		Write("Не удалось найти номера");
	else {
		std::cout << "Свободные номера на данные даты по указанному критерию: " << std::endl;
		for (set<int>::iterator it = nums.begin(); it != nums.end(); ++it)
			std::cout << "id - " << (*it) << endl; // << "\t\t" << (*it).second << std::endl;
	}
	cout << endl;
	nums.clear();
}
void task_data_numbers(Hotel& hotel)
{
	int top;
	if (!InputUVal("Top N. Введите N:", top)) {
		Write("Некорректный ввод");
		return;;
	}
	Profit_numbers nums;
	hotel.top_numbers(nums, top);

	if (nums.size() == 0)
		Write("Не удалось найти номера");
	else {
		std::cout << "Топ " << top << " самых прибыльных номеров: " << std::endl;
		int i = 1;
		for (Profit_numbers::iterator it = nums.begin(); it != nums.end(); ++it, ++i)
			std::cout << "#" << i << ".\t" << "номер " <<
			(*it).first->get_ID() << endl << "\t" << "прибыль: " << "\t" <<
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
	if (!InputUVal("Top N. Введите N:", top)) {
		Write("Некорректный ввод");
		return;;
	}
	Profit_fullnames names;
	hotel.top_residents(names, top);

	if (names.size() == 0)
		Write("Не удалось найти постояльцев");
	else {
		std::cout << "Топ " << top << " самых прибыльных посетителей: " << std::endl;
		int i = 1;
		for (Profit_fullnames::iterator it = names.begin(); it != names.end(); ++it, ++i)
			std::cout << "#" << i << ".\t" << (*it).first << "\r\n" <<
			"\t" << "Прибыль от клиента: " << (*it).second << endl << endl;
	}
	cout << endl;
	names.clear();
}

void task_data_by_name(Hotel& hotel)
{
	string fname;
	if (!InputFullName(fname)) {
		cout << "неверно введена фамилия" << endl;
		return;
	}
	vector<Resident* > names;
	hotel.all_visits_by_name(names, fname);
	if (names.size() == 0)
		Write("не удалось найти такие значения");
	else {
		int i = 1;
		cout << endl << ">>> Посещения гостя " << fname << ":" << endl << endl;
		for (vector<Resident* >::iterator it = names.begin(); it != names.end(); ++it) {
			cout << "# " << i << "." << endl << "Комната: " << (*it)->get_number_id() << endl;
			cout << "Даты въезда и отъезда:" << endl;
			(*it)->get_begin().printFormat();
			(*it)->get_end().printFormat();
		}
		while (names.size() > 0) {
			delete names.back();
			names.pop_back();
		}
	}
}
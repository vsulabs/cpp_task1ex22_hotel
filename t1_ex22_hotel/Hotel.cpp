#include "Hotel.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

void Hotel::print_all() const 
{
	for (vector<HotelNumber*>::const_iterator it = Apartments.begin(); it != Apartments.end(); ++it) {
		cout << "-Информация о номере " << (*it)->get_ID() << endl;
		(*it)->print();
		cout << endl << ">> Постояльцы номера: " << (*it)->get_ID() << endl << endl;
		for (auto pairs = Visits.begin(); pairs != Visits.end(); ++pairs) 
			if ((*it)->get_ID() == (*pairs).first->get_number_id()) {
				(*pairs).first->Print();
				cout << endl << endl;
			}
		cout << endl << "<< <<" << endl << endl;
	}
}

void Hotel::print_numbers() const 
{
	cout << endl << "**********************" << endl << endl;
	for (vector<HotelNumber*>::const_iterator it = Apartments.begin(); it != Apartments.end(); ++it) {
		(*it)->print();
		cout << endl << endl;
	}
	cout << "**********************" << endl << endl;
}

void Hotel::print_all_id() const 
{
	cout << "Отель содержит комнаты под следующими номерами:" << endl;
	for (set<int>::const_iterator it = IDs.begin(); it != IDs.end(); ++it)
		cout << "id : " << *it << endl;
}


Hotel::~Hotel() 
{
	clear();
}

bool Hotel::add_number(HotelNumber* number) 
{
	if (!(IDs.find(number->get_ID()) == IDs.end() )) {
		delete number;
		return false; // если уже существует комната с таким номером, false
	}
	Apartments.push_back(number);
	IDs.insert(number->get_ID());
	return true;
}

bool Hotel::add(Resident* resident)  
{
	if (resident == nullptr)
		throw exception_ptr();

	// проверяем, есть ли указанный для заселения номер в номерном фонде
	if (IDs.find(resident->get_number_id()) == IDs.end()) { // если нет, выход из процедуы
		delete resident;
		return false;
	}
	
	// запрещаем заселение больше чем на 10 лет
	if (resident->get_days() > myDates::daysBetween(myDates(1, 1, MinYear), myDates(1, 1, MinYear + 10))) { 
		delete resident;
		return false;
	}

	bool isOkRoom = true;
	for (int i = 0; (inDates.begin() + i) != inDates.end() && isOkRoom; ++i) {
		// Комната продолжает нам подходить, если это не она была занята в проверяемые даты
		// или если она, но даты не пересекаются
		isOkRoom = 
				resident->get_number_id() != (Visits.begin() + i)->second->get_ID()  || (
				
				resident->get_begin() < **(inDates.begin() + i) &&
				resident->get_end() < **(inDates.begin() + i) ||
				resident->get_begin() > **(outDate.begin() + i) &&
				resident->get_end() > **(outDate.begin() + i) );
	}

	if (!isOkRoom) {
		delete resident;
		return false;
	}
	Visit visit;
			
	visit.first = resident;
	for (auto it = Apartments.begin(); it != Apartments.end(); ++it)
		if ((*it)->get_ID() == resident->get_number_id())
			visit.second = new HotelNumber(**(it));
			
	Visits.push_back(visit);
	inDates.push_back(new myDates(resident->get_begin()));
	outDate.push_back(new myDates(resident->get_end()));
	
	return true;
}

bool Hotel::edit_number(int id, const HotelNumber& number) 
{
	if (IDs.find(id) == IDs.end())
		return false;

	// сначала меняем всю информацию о самих номерах
	for (vector<HotelNumber*>::iterator it = Apartments.begin(); it != Apartments.end(); ++it) 
		if (id == (*it)->get_ID()) {
			(*it)->CopyBy(number, id); // процедура копирования из вспомогательной структуры
			break;
		}
	// затем ищем все упоминания номера в посещениях и редактируем всю информацию там
	for (vector<Visit>::iterator it = Visits.begin(); it != Visits.end(); ++it) 
		if (id == (*it).second->get_ID()) 
			(*it).second->CopyBy(number, id); // процедура копирования из вспомогательной структуры
	return true; 
}

bool Hotel::edit(int id, myDates begin, const Resident& resident) 
{
	if (IDs.find(id) == IDs.end())
		return false;
	
	auto it = Visits.begin();
	for (; it != Visits.end(); ++it) {
		// проверяем, есть ли посещение такой комнаты в такое время
		if ((*it).second->get_ID() == id &&
			(*it).first->get_begin() == begin) {
			
			for (int i = 0; (Visits.begin() + i) != Visits.end(); ++i) {
				// Если не выполняется, что 
				// сравниваемое посещение не является посещением интересующего нас номера,
				// или же что желаемые даты не пересекаются со сравниваемыми датами
				// выходим из цикла
				if (id == (Visits.begin() + i)->second->get_ID() &&
					begin == (Visits.begin() + i)->first->get_begin())
					continue;
				if (!	((resident.get_number_id() != (Visits.begin() + i)->second->get_ID()) || (
					resident.get_begin() < **(inDates.begin() + i) &&
					resident.get_end() < **(inDates.begin() + i) ||
					resident.get_begin() > **(outDate.begin() + i) &&
					resident.get_end() > **(outDate.begin() + i))
					))
				return false;
			} // for (сравнение дат посещений)
			break; 
		} // if (нужное нам посещение нужного номера в нужную дату по нужной фио)
	} // for (ищем посещение, которое требуется отредактировать
	if (it == Visits.end())
		return  false;
	
	/*it = Visits.begin();
	for (; it != Visits.end(); ++it)
		if ((*it).second->get_ID() == id &&
			(*it).first->get_begin() == begin)
			break;*/
	int i = 0;
	for (; Visits.begin() + i != it; )
		++i;
	(*(inDates.begin() + i))->copy_by(resident.get_begin());
	(*(outDate.begin() + i))->copy_by(resident.get_end());
	(*it).first->CopyBy(resident);
	return true;
}

bool Hotel::delete_number(int id) 
{
	if (IDs.find(id) == IDs.end())
		return false;
		
	vector<HotelNumber*>::iterator it = Apartments.begin();			
	while (it != Apartments.end() && (*it)->get_ID() != id)
		++it;
	if (it == Apartments.end())
		return false;
		
	for (int i = 0; Visits.size() > 0 && Visits.begin() + i != Visits.end();) {
		if (Visits[i].second->get_ID() != (*it)->get_ID())
		{
			++i;
			continue;
		}

		delete Visits.at(i).first;
		delete Visits.at(i).second;
		Visits.erase(Visits.begin() + i);

		delete inDates.at(i);
		delete outDate.at(i);
		inDates.erase(inDates.begin() + i);
		outDate.erase(outDate.begin() + i);
		
		i = 0;
	} // for
	IDs.erase(IDs.find(id));
	delete *it;
	Apartments.erase(it);
	return true;		
}

bool Hotel::delete_visit(int id, const myDates & begin) 
{
	if (IDs.find(id) == IDs.end())
		return false;

	for (auto it = Visits.begin(); it != Visits.end(); ++it) {
		if ((*it).second->get_ID() == id && (*it).first->get_begin() == begin) {
			delete((*it).first);
			delete((*it).second);
			Visits.erase(it);
			break;
		}
	}
	return true;
}

void Hotel::clear_visits() 
{	
	while (inDates.size() > 0){
		delete inDates.back();
		inDates.pop_back();
	}
	while (outDate.size() > 0){
		delete outDate.back();
		outDate.pop_back();
	}
	while (Visits.size() > 0) {
		delete Visits.back().second;
		delete Visits.back().first;
		Visits.pop_back();
	}
}

void Hotel::clear() 
{
	clear_visits();
	while (Apartments.size() > 0){
		delete Apartments.back();
		Apartments.pop_back();
	}
	IDs.clear();
}


void Hotel::SearchBySleeps(set<int>& res, int sleeps, myDates begin, myDates end) 
{
	res.clear();
	bool okRoom;
	myDates::days_correct(begin, end);

	for (vector<HotelNumber*>::iterator it = Apartments.begin(); it != Apartments.end(); ++it) {
		okRoom = (*it)->get_sleepingAreas() == sleeps;
		for (int i = 0; (inDates.begin() + i) != inDates.end() && okRoom; ++i)
			okRoom = (*it)->get_ID() != (Visits.begin() + i)->second->get_ID() ||
			(
			begin < **(inDates.begin() + i) && end < **(inDates.begin() + i) ||
			begin > **(outDate.begin() + i) && end > **(outDate.begin() + i)
			)
			;
		if (okRoom)
			res.insert((*it)->get_ID());
	}
}

void Hotel::SearchByPrice(set<int>& res, myDates begin, myDates end, int maxPrice, int minPrice) 
{
	if (minPrice < 0)
		minPrice = 0;
	if (maxPrice < 0)
		maxPrice = 0;
	if (minPrice > maxPrice)
		swap(minPrice, maxPrice);
	
	res.clear();
	bool okRoom;
	myDates::days_correct(begin, end);

	for (vector<HotelNumber*>::iterator it = Apartments.begin(); it != Apartments.end(); ++it) {
		okRoom = (*it)->Rent(begin, end) >= minPrice && (*it)->Rent(begin, end) <= maxPrice;
		for (int i = 0; (inDates.begin() + i) != inDates.end() && okRoom; ++i)
			okRoom = 
			(*it)->get_ID() != (Visits.begin() + i)->second->get_ID() ||
			(
			begin < **(inDates.begin() + i) && end < **(inDates.begin() + i) ||
			begin > **(outDate.begin() + i) && end > **(outDate.begin() + i)
			);
		if (okRoom)
			res.insert((*it)->get_ID());
	}
}


void Hotel::all_visits_by_name(vector<Resident* >& res, string fio) 
{
	while (res.size() > 0) {
		delete res.back();
		res.pop_back();
	}
	for (auto it = Visits.begin(); it != Visits.end(); ++it)
		if ((*it).first->get_fullName() == fio)
			res.push_back(new Resident(*(it->first)));
}


template <typename T1, typename T2>
struct left_more_by_second_param 
{
	typedef pair<T1, T2> type;
	bool operator() (type const& a, type const& b) const {
		return a.second > b.second;
	}
};

void Hotel::top_numbers(Profit_numbers& res, int n) 
{
	while (res.size() > 0) {
		delete res.back().first;
		res.pop_back();
	}
	
	map<int, int> nums;
	set<int> vote;
	for (auto it = Visits.begin(); it != Visits.end(); ++it) {
		nums[(*it).first->get_number_id()] +=
			(*it).second->Rent((*it).first->get_begin(), (*it).first->get_end());
		vote.insert((*it).first->get_number_id());
	}	
	for (auto a: Apartments) {
		if (vote.find(a->get_ID()) == vote.end())
			nums[a->get_ID()] = 0;
	}

	vector<pair<int, int>> mapcopy(nums.begin(), nums.end());
	sort(mapcopy.begin(), mapcopy.end(), left_more_by_second_param<int, int>());
		
	int i = 0;
	for (auto it = mapcopy.begin(); it != mapcopy.end() && i < n; ++it, ++i) {
		for (vector<HotelNumber*>::iterator num = Apartments.begin(); num != Apartments.end(); ++num)
			if ((*num)->get_ID() == (it)->first) {
				pair<HotelNumber*, int> tmp(new HotelNumber(**num), (*it).second);
				res.push_back(tmp);
			}
		// Если сказано вывести топ n, но последние значения этого топа совпадают, 
		// то выводим их пока не найдется следующее или не закончится массив посещений
		if (i + 1 == n && it + 1 != mapcopy.end() && (*(it + 1)).second == (*it).second && (*it).second != 0)
			++n;
	}
}

void Hotel::top_residents(Profit_fullnames& res, int n) 
{
	res.clear();
	map<string, int> fullnames;
	
	for (auto it = Visits.begin(); it != Visits.end(); ++it) {
		fullnames[(*it).first->get_fullName()] += 
			(*it).second->Rent((*it).first->get_begin(), (*it).first->get_end());
	}
		
	vector<pair<string, int> > mapcopy(fullnames.begin(), fullnames.end());
	sort(mapcopy.begin(), mapcopy.end(), left_more_by_second_param<string, int>());

	int i = 0;
	for (auto it = mapcopy.begin(); it != mapcopy.end() && i < n; ++it, ++i) {
		pair<string, int> tmp((*it).first, (*it).second);
		res.push_back(tmp);
		
		// Если сказано вывести топ n, но последние значения этого топа совпадают, 
		// то выводим их пока не найдется следующее или не закончится массив посещений
		if (i + 1 == n && it + 1 != mapcopy.end() && (*(it + 1)).second == (*it).second && (*it).second != 0)
			++n;
	}
}


bool Hotel::load_from_file(string fName) 
{
	//std::ifstream infile(fName, std::fstream::binary);
	ifstream infile;
	string tmp_string;
	string::size_type sz;
		
	clear();
	
	bool OkReading = true;
	infile.open(fName);
	
	while (!infile.eof() && OkReading) // To get you all the lines.
	{
		try {
			getline(infile, tmp_string); // Saves the line in tmp_string
			if (tmp_string == "*") {
				break;
			}
			getline(infile, tmp_string); // Saves the line in tmp_string
			tmp_string = tmp_string.substr(tmp_string.find(':') + 2);
			int rooms = stoi(tmp_string, &sz);

			getline(infile, tmp_string); // Saves the line in tmp_string
			tmp_string = tmp_string.substr(tmp_string.find(':') + 2);
			int status = stoi(tmp_string, &sz);

			getline(infile, tmp_string); // Saves the line in tmp_string
			tmp_string = tmp_string.substr(tmp_string.find(':') + 2);
			int id = stoi(tmp_string, &sz);

			getline(infile, tmp_string); // Saves the line in tmp_string
			tmp_string = tmp_string.substr(tmp_string.find(':') + 2);
			int sleeps = stoi(tmp_string, &sz);
			try {
				HotelNumber number = HotelNumber(rooms, status, id, sleeps);
				add_number(new HotelNumber(rooms, status, id, sleeps));
			}
			catch (const std::invalid_argument& e) {
				std::cerr << e.what();
				OkReading = false;
			}
		}
		catch (const std::out_of_range& e) {
			cerr << e.what();
			OkReading = false;
		}
	}

	if (!OkReading) {
		clear();
		infile.close();
		return false;
	}

	while (!infile.eof()) // To get you all the lines.
	{
		try {
			getline(infile, tmp_string); // Saves the line in tmp_string
			if (tmp_string == "*") {
				break;
			}

			getline(infile, tmp_string); // Saves the line in tmp_string
			string fullName = tmp_string.substr(tmp_string.find(':') + 2);

			getline(infile, tmp_string); // Saves the line in tmp_string
			tmp_string = tmp_string.substr(tmp_string.find(':') + 2);
			int id = stoi(tmp_string, &sz);
			
			getline(infile, tmp_string); // Saves the line in tmp_string
			tmp_string = tmp_string.substr(tmp_string.find(':') + 2);
			myDates b = myDates(tmp_string);

			getline(infile, tmp_string); // Saves the line in tmp_string
			tmp_string = tmp_string.substr(tmp_string.find(':') + 2);
			myDates e = myDates(tmp_string);

			try {
				Resident Res = Resident(fullName, id, b, e);
				add(new Resident(Res));
			}
			catch (const std::invalid_argument& ex) {
				cerr << ex.what();
				infile.close();
				return false;
			}
		}
		catch (const std::out_of_range& ex) {
			cerr << ex.what();
			infile.close();
			return false;
		}
	}
	infile.close();
	return true;
}


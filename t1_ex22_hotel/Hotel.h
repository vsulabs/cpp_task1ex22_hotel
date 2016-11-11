#pragma once

#include <vector>
#include <set>
#include "Resident.h"
#include "HotelNumber.h"
#include <map>

typedef std::pair<Resident*, HotelNumber*> Visit;
typedef std::vector<std::pair<std::string, int>> Profit_fullnames; // каждой фамилии ставим в соответствие прибыльность
typedef std::vector<std::pair<HotelNumber* , int>> Profit_numbers; // каждому номеру ставим в соответствие прибыльность

class Hotel
{
	std::string fileName = "src/Plaza.txt"; 

	std::vector<HotelNumber*> Apartments;
	std::set<int> IDs;				// множество id, которые уже присвоены каким-то гостичным номера. 
	
	std::vector<Visit> Visits;
	
	std::vector<myDates* > inDates;
	std::vector<myDates* > outDate;
public:
	bool add_number(HotelNumber* number);	// добавление номера, если номера с таким id не существует
	bool add(Resident* resident);			// добавление посещения

	bool edit_number(int id, const HotelNumber& number);
	bool edit(int id, myDates begin, const Resident& resident);

	bool delete_number(int id);
	bool delete_visit(int id, const myDates& begin);
	
	void clear_visits();
	void clear();

	void						SearchBySleeps(std::set<int>& res, int sleeps, myDates begin, myDates end);
	void						SearchByPrice(std::set<int>& res, myDates begin, myDates end, int maxPrice, int minPrice = 0);
	
	void						top_numbers(Profit_numbers& res, int n);
	void						top_residents(Profit_fullnames& res, int n);
	void						all_visits_by_name(std::vector<Resident* >& res, std::string fio);

	void print_all()			const;
	void print_numbers()		const ;
	void print_all_id()			const;

	bool						load_from_file(std::string fName);
	std::string					file_name() const { return fileName; }
	~Hotel();
};


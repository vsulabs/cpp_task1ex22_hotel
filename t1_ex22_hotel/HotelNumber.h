#pragma once

#include <string>
#include"myDates.h"

enum RoomStatus {			// класс номера в отеле
	rs_economy = 2,			// эконом	- 2
	rs_standart,			// стандарт - 3
	rs_halflux,				// полулюкс - 4
	rs_lux					// люкс		- 5
};

static const int maxRooms = 10;
static const int maxSleep = 20;

class HotelNumber {
	int rooms;				// число комнат (влияет на стоимость номера)
	RoomStatus status;		// класс номера (влияет на стоимость номера)
	int numberID;			// номер комнаты (должен быть уникальным)

	int sleepingAreas;		// число спальных мест 
	int cost;				// 500 * rooms + 1200 * status
public:
	// Конструктор для номера гостиницы. 
	HotelNumber(
		int aRooms, 
		RoomStatus aStatus, 
		int aNumberID, 
		int aSleepingAreas); 
	HotelNumber(
		int aRooms,
		int aStatus,
		int aNumberID,
		int aSleepingAreas);
	HotelNumber(const HotelNumber& other);			// конструктор копирования

	void				print()					const; // метод печатает все данные о номере
	std::string			toString()				const;

	int					get_rooms()				const { return rooms; };
	int					get_ID()				const { return numberID; };
	int					get_sleepingAreas()		const { return sleepingAreas; };
	RoomStatus			get_status()			const { return status; };
	int					get_cost()				const { return cost; } ;

	
	void CopyBy(const HotelNumber& other, int newID);
	int Rent(const myDates& begin, const myDates& end) const;

	~HotelNumber();
};


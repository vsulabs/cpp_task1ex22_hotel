#pragma once

#include <string>
#include"myDates.h"

enum RoomStatus {			// ����� ������ � �����
	rs_economy = 2,			// ������	- 2
	rs_standart,			// �������� - 3
	rs_halflux,				// �������� - 4
	rs_lux					// ����		- 5
};

static const int maxRooms = 10;
static const int maxSleep = 20;

class HotelNumber {
	int rooms;				// ����� ������ (������ �� ��������� ������)
	RoomStatus status;		// ����� ������ (������ �� ��������� ������)
	int numberID;			// ����� ������� (������ ���� ����������)

	int sleepingAreas;		// ����� �������� ���� 
	int cost;				// 500 * rooms + 1200 * status
public:
	// ����������� ��� ������ ���������. 
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
	HotelNumber(const HotelNumber& other);			// ����������� �����������

	void				print()					const; // ����� �������� ��� ������ � ������
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


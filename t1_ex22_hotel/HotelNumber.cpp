#include "HotelNumber.h"
#include <iostream>

HotelNumber::HotelNumber(int aRooms, RoomStatus aStatus, int aNumberID, int aSleepingAreas) 
{	
	if (aRooms <= 0 || aSleepingAreas <= 0 || aNumberID <= 0 ||
		aRooms > maxRooms || aSleepingAreas > maxSleep)
		throw std::invalid_argument("��� ������ ������� ������������ �������� \r\n");
	
	sleepingAreas = aSleepingAreas;
	numberID = aNumberID;
	rooms = aRooms;

	if (aStatus < rs_economy)
		status = rs_economy;
	else if (aStatus > rs_lux)
		status = rs_lux;
	else
		status = aStatus;

	cost = 500 * rooms + 1200 * status; // ������������ ��������� ���������� �� ����	
}

HotelNumber::HotelNumber(int aRooms, int aStatus, int aNumberID, int aSleepingAreas)
{
	if (aRooms <= 0 || aSleepingAreas <= 0 || aNumberID <= 0 ||
		aRooms > maxRooms || aSleepingAreas > maxSleep)
		throw std::invalid_argument("��� ������ ������� ������������ �������� \r\n");

	sleepingAreas = aSleepingAreas;
	numberID = aNumberID;
	rooms = aRooms;
	if (aStatus <= 2)
		status = rs_economy;
	else if (aStatus >= 5)
		status = rs_lux;
	else
		switch (aStatus)
		{
		case 3:
			status = rs_standart;
			break;
		case 4:
			status = rs_halflux;
			break;
		}
	
	cost = 500 * rooms + 1200 * status; // ������������ ��������� ���������� �� ����	
}

HotelNumber::HotelNumber(const HotelNumber & other)
{
	status = other.status;
	sleepingAreas = other.sleepingAreas;
	rooms = other.rooms;
	numberID = other.get_ID();

	cost = other.cost;
}

void HotelNumber::print() const {
	std::cout << "id \t\t: \t " << numberID << std::endl;
	std::cout << "����� ������	: \t " << rooms << std::endl;
	std::cout << "�������� ����	: \t " << sleepingAreas << std::endl;
	std::cout << "���� �� �����	: \t " << cost << std::endl;
	std::cout << "������		: \t ";
	switch (status) 
	{
	case rs_economy:
		std::cout << "������";
		break;
	case rs_standart:
		std::cout << "��������";
		break;
	case rs_halflux:
		std::cout << "��������";
		break;
	case rs_lux:
		std::cout << "����";
		break;
	default:
		std::cout << "�� ��������";
		break;
	}
	std::cout << std::endl;
}

std::string HotelNumber::toString() const
{
	std::string tmp;
	switch (status)
	{
	case rs_economy:
		tmp = "������";
		break;
	case rs_standart:
		tmp = "��������";
		break;
	case rs_halflux:
		tmp = "��������";
		break;
	case rs_lux:
		tmp = "����";
		break;
	default:
		tmp = "�� ��������";
		break;
	}
	std::string res =
		"id	\t\t: \t\t" + std::to_string(numberID) + "\r\n" +
		"����� ������	: \t\t" + std::to_string(rooms) + "\r\n" +
		"�������� ����	: \t\t" + std::to_string(sleepingAreas) + "\r\n" +
		"���� �� �����	: \t\t" + std::to_string(rooms) + "\r\n" +
		"������:		: \t\t" + tmp + "\r\n";
	return res;
}


void HotelNumber::CopyBy(const HotelNumber& other, int newID) {
	status = other.status;
	sleepingAreas = other.sleepingAreas;
	rooms = other.rooms;
	numberID = newID;

	cost = other.cost;
}

int HotelNumber::Rent(const myDates& begin, const myDates& end) const {
	return myDates::daysBetween(begin, end) * cost;
}

HotelNumber::~HotelNumber()
{

}

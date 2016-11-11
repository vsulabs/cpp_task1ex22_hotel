#pragma once
#include "myDates.h"

class Resident
{
	std::string		FullName;			// ��� ���������� (����������)
	myDates 		Begin;				// ���� ���������
	myDates 		End;				// ���� �������

	int				days_in_number;		// ���������� ����, ����������� �� ����� ������. �������������� ����� ��������� �� ������ ����� ���������
	int				number;				// ���������� �� ����� 
public:
	// �����������, ����������� ��������� ���������: ������ ���; ����� � �����; ���� �������� � �������.
	Resident(std::string fio, int idN, const myDates& b, const myDates& e);
	
	// �����������, ����������� ��������� ���������: ������ ���; ����� � �����; ���� �������� � ����� ����������
	Resident( 
		std::string fio,
		int idN,
		int y = 1950, int m = 1, int d = 1,
		int range = 1
		);

	std::string			get_fullName()	const { return FullName; }			// ������ � ������ ���������� � ������� ���������� 
	myDates				get_begin()		const { return Begin; }				// ������ � ������ ���������� � ���� ���������
	myDates				get_end()		const { return End; }				// ������ � ������ ���������� � ���� �������
	int					get_days()		const { return days_in_number; }	// ������ � ������ ���������� �� �������� ��������� ������
	int					get_number_id()	const { return number; }			// ������ � ������ ���������� � ���������� ������

	void				CopyBy(const Resident& oher);
	std::string			toString()		const;
	void				Print()			const;
	

	~Resident();
};


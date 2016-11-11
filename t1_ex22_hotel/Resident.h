#pragma once
#include "myDates.h"

class Resident
{
	std::string		FullName;			// фио посетителя (постояльца)
	myDates 		Begin;				// дата заселения
	myDates 		End;				// дата отъезда

	int				days_in_number;		// Количество дней, проведенных во время визита. рентабельность будет считаться на основе этого параметра
	int				number;				// занимаемый им номер 
public:
	// конструктор, принимающий следующие параметры: строку ФИО; номер в отеле; даты прибытия и отбытия.
	Resident(std::string fio, int idN, const myDates& b, const myDates& e);
	
	// конструктор, принимающий следующие параметры: строку ФИО; номер в отеле; Дату прибытия и время прибывания
	Resident( 
		std::string fio,
		int idN,
		int y = 1950, int m = 1, int d = 1,
		int range = 1
		);

	std::string			get_fullName()	const { return FullName; }			// доступ к чтению информации о фамилии постояльца 
	myDates				get_begin()		const { return Begin; }				// доступ к чтению информации о дате заселения
	myDates				get_end()		const { return End; }				// доступ к чтению информации о дате отъезда
	int					get_days()		const { return days_in_number; }	// доступ к чтению информации об итоговой стоимости визита
	int					get_number_id()	const { return number; }			// доступ к чтению информации о занимаемом номере

	void				CopyBy(const Resident& oher);
	std::string			toString()		const;
	void				Print()			const;
	

	~Resident();
};


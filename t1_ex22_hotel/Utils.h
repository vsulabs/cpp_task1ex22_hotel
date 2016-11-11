#pragma once
#include "Hotel.h"

static const int max_size = 256;

int				InputInt(std::string message = "");
int				InputUMax(std::string message, int max);
bool			InputUVal(std::string message, int& val);
bool			InputFullName(std::string& fullName);
bool			InputDates(myDates& date, std::string message = "");
RoomStatus		InputRoomStatus();
HotelNumber		InputHotelNumber(int currentID = -1);
Resident		InputResident();
Visit			InputVisit();

void			Trim(std::string &str);
void			DelSpaces(std::string &str);

void			Write(std::string str); 
void			Write(std::string str, int count);

bool			yes_or_no(std::string message);

/*Task Utils*/

void	task_number_add		(Hotel& hotel);
void	task_number_delete	(Hotel& hotel);
void	task_number_edit	(Hotel& hotel);
void	task_visit_add		(Hotel& hotel);
void	task_visit_delete	(Hotel& hotel);
void	task_visit_edit		(Hotel& hotel);
void	task_search_sleeps	(Hotel& hotel);
void	task_search_cost	(Hotel& hotel);
void	task_data_numbers	(Hotel& hotel);
void	task_data_resident	(Hotel& hotel);
void	task_data_by_name	(Hotel& hotel);
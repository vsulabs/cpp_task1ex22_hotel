#include "Task.h"
#include <iostream>
using namespace std;

void Run() {
	Hotel Plaza;

	int menu_mark;
	do {
		PrintMenu(tw_main);
		menu_mark = Select(tw_main);
		
		int task_mark;
		switch (menu_mark)
		{
		case 1: // numbers
			PrintMenu(tw_numbers);
			task_mark = Select(tw_numbers);
			NumbersTask(task_mark, Plaza);
			break;
		case 2: // visits
			PrintMenu(tw_visits);
			task_mark = Select(tw_visits);
			VisitTask(task_mark, Plaza);
			break;
		case 3: // data
			PrintMenu(tw_data);
			task_mark = Select(tw_data);
			DataTask(task_mark, Plaza);
			break;
		case 4: // search
			PrintMenu(tw_search);
			task_mark = Select(tw_search);
			SearchTask(task_mark, Plaza);
			break;
		case 5: // print
			Plaza.print_all();
			break;
		case 6: // load from file
			if (Plaza.load_from_file(Plaza.file_name()))
				Plaza.print_all();
			else
				Write("данные загружены не полностью");
			break;
		case 7: // clear
			PrintMenu(tw_clear);
			task_mark = Select(tw_clear);
			ClearTask(task_mark, Plaza);
			break;
		} // switch
		
		//if (!yes_or_no(continue_task_question)) 			
			//menu_mark = 0;
	} while (menu_mark != 0);
	Write("Программа завершила работу");
}

int Select(TypeWorking type)
{
	int k;
	int max;
	switch (type)
	{	
	case tw_numbers:
		max = 4;
		break;
	case tw_data:
	case tw_visits:	
		max = 3;
		break;
	case tw_clear:
	case tw_search:
		max = 2;
		break;
	default:
		max = MainMenuMax;
	}
	bool errorInput = false;
	do {
		if (errorInput)
			Write("Некорректный ввод, повторите!");
		k = InputInt();
		errorInput = k < 0 || k > max;
	} while (errorInput);
	cout << endl;
	return k;
}

void PrintMenu(TypeWorking type)
{
	Write(differ, 2);
	if (type == tw_main)
		Write(main_menu);
	else
		Write(sub_menu);
	switch (type)
	{
	case tw_main:
		Write(main_menu1);
		Write(main_menu2);
		Write(main_menu3);
		Write(main_menu4);
		Write(main_menu5);
		Write(main_menu6);
		Write(main_menu7);
		break;
	case tw_numbers:
		Write(menu_numbers_1);
		Write(menu_numbers_2);
		Write(menu_numbers_3);
		Write(menu_numbers_4);
		break;
	case tw_visits:
		Write(menu_visit_1);
		Write(menu_visit_2);
		Write(menu_visit_3);
		break;
	case tw_search:
		Write(menu_search_1);
		Write(menu_search_2);
		break;
	case tw_data:
		Write(menu_data_1);
		Write(menu_data_2);
		Write(menu_data_3);
		break;
	case tw_clear:
		Write(menu_clear_1);
		Write(menu_clear_2);
		break;
	}
	Write(menu_exit);
}


void NumbersTask(int t, Hotel & hotel)
{
	switch (t)
	{
	case 1: {// add
		task_number_add(hotel);
		break;
	}
	case 2: {// del
		task_number_delete(hotel);
		break;
	}
	case 3: {// edit
		task_number_edit(hotel);
		break;
	}
	case 4: {
		hotel.print_numbers();
		hotel.print_all_id();
		break;
	}
	}
}

void VisitTask(int t, Hotel & hotel)
{
	switch (t)
	{
	case 1: { // add
		task_visit_add(hotel);
		break;
	} // case 1
	case 2: {// del
		task_visit_delete(hotel);
		break;
	} // case 2
	case 3: { // edit
		task_visit_edit(hotel);
		break;
	} // case 3
	} // switch
}

void SearchTask(int t, Hotel & hotel)
{
	switch (t)
	{
	case 1: { // sleeps
		task_search_sleeps(hotel);
		break;
	} // case 1
	case 2: { // cost
		task_search_cost(hotel);
		break;
	} // case 2
	} // switch
}

void DataTask(int t, Hotel & hotel)
{
	switch (t)
	{
	case 1: { // номера
		task_data_numbers(hotel);
		break;
	}
	case 2: { // постояльцы
		task_data_resident(hotel);
		break;
	}
	case 3: { // все посещения по фио
		task_data_by_name(hotel);
		break;
	}
	
	} // switch
}

void ClearTask(int t, Hotel& hotel){
	switch (t)
	{
	case 1:
		hotel.clear_visits();
		break;
	case 2:
		hotel.clear();
		break;
	default:
		break;
	}
}


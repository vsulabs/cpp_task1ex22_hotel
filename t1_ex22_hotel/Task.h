#pragma once

#include "Utils.h"

enum TypeWorking {
	tw_main,
	tw_numbers,
	tw_visits,
	tw_search,
	tw_data,
	tw_clear
};

static const int MainMenuMax = 7;

void	Run();
int		Select(TypeWorking type);
void	PrintMenu(TypeWorking type);

void	NumbersTask(int t, Hotel& hotel);
void	VisitTask(int t, Hotel& hotel);
void	SearchTask(int t, Hotel& hotel);
void	DataTask(int t, Hotel& hotel);
void	ClearTask(int t, Hotel& hotel);

static std::string menu_exit		("0 - Выход");
static std::string please_input		("-> ");
static std::string differ			("______________________________________");

static std::string main_menu		("\t- Main menu - ");
static std::string sub_menu			("\t- Sub menu - ");

static std::string main_menu1		("1 - Работа с номерным фондом ...");
static std::string main_menu2		("2 - Работа с посещениями отеля ...");
static std::string main_menu3		("3 - Получить статистику ...");
static std::string main_menu4		("4 - Поиск свободных комнат ...");
static std::string main_menu5		("5 - Показать все посещения по номерам ...");
static std::string main_menu6		("6 - Загрузить данные из файла");
static std::string main_menu7		("7 - Очистка данные ...");

static std::string menu_numbers_1	("1 - Добавить номер отеля");
static std::string menu_numbers_2	("2 - Удалить номер отеля");
static std::string menu_numbers_3	("3 - Редактировать номер отеля");
static std::string menu_numbers_4	("4 - Показать все номера");

static std::string menu_visit_1		("1 - Добавить посещение");
static std::string menu_visit_2		("2 - Удалить посещение");
static std::string menu_visit_3		("3 - Редактировать посещение");

static std::string menu_search_1	("1 - По числу спальных мест");
static std::string menu_search_2	("2 - По цене");

static std::string menu_data_1		("1 - Самые прибыльные номера");
static std::string menu_data_2		("2 - Самые прибыльные постояльцы");
static std::string menu_data_3		("3 - Все посещения по фио");

static std::string menu_clear_1		("1 - Очистить информацию о посещениях");
static std::string menu_clear_2		("2 - Очистить номерной фонд (потеряется информация о посещениях)");

static std::string 
continue_task_question				("\r\nПродолжить работу программы?");


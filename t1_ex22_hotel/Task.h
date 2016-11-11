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

static std::string menu_exit		("0 - �����");
static std::string please_input		("-> ");
static std::string differ			("______________________________________");

static std::string main_menu		("\t- Main menu - ");
static std::string sub_menu			("\t- Sub menu - ");

static std::string main_menu1		("1 - ������ � �������� ������ ...");
static std::string main_menu2		("2 - ������ � ����������� ����� ...");
static std::string main_menu3		("3 - �������� ���������� ...");
static std::string main_menu4		("4 - ����� ��������� ������ ...");
static std::string main_menu5		("5 - �������� ��� ��������� �� ������� ...");
static std::string main_menu6		("6 - ��������� ������ �� �����");
static std::string main_menu7		("7 - ������� ������ ...");

static std::string menu_numbers_1	("1 - �������� ����� �����");
static std::string menu_numbers_2	("2 - ������� ����� �����");
static std::string menu_numbers_3	("3 - ������������� ����� �����");
static std::string menu_numbers_4	("4 - �������� ��� ������");

static std::string menu_visit_1		("1 - �������� ���������");
static std::string menu_visit_2		("2 - ������� ���������");
static std::string menu_visit_3		("3 - ������������� ���������");

static std::string menu_search_1	("1 - �� ����� �������� ����");
static std::string menu_search_2	("2 - �� ����");

static std::string menu_data_1		("1 - ����� ���������� ������");
static std::string menu_data_2		("2 - ����� ���������� ����������");
static std::string menu_data_3		("3 - ��� ��������� �� ���");

static std::string menu_clear_1		("1 - �������� ���������� � ����������");
static std::string menu_clear_2		("2 - �������� �������� ���� (���������� ���������� � ����������)");

static std::string 
continue_task_question				("\r\n���������� ������ ���������?");


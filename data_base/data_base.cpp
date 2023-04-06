#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include "data_base.h"
using namespace std;

int main() {
	ClearAllData(TEMP_FILE_NAME);
	HideCursor(1);

	int quit = 0;
	int option = 1;
	int type = 0;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	SetFullscrn();

	ReadAllData();
	//AddSomeData();

	while (quit == 0) {
		MainMenu(option);
		HideCursor(1);

		
		option = GetOption(option, 1);

		if (option == -10) {
			quit = 1;
		} else if (option == -1) {
			type = GetType("Какие данные вы хотите просмотреть?");

			if (type != -10) {
				PrintAllData(type);
			} 
			
			option = -option;
		} else if (option == -2) {
			type = GetType("Какие данные вы хотите просмотреть?");

			if (type != -10) {
				GetEdit(type);
			}

			option = -option;
		} else if (option == -3) {
			HideCursor(0);
			StudentSearch();
			HideCursor(1);

			option = -option;
		} 
	}

	system("cls");

	exit(0);
	return 0;
}

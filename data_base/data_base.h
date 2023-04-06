#include "structs.h"
using namespace std;

//the file in which all the data is stored
const char* FILE_NAME = "data.bin";
const char* TEMP_FILE_NAME = "temp.bin";

//for the interface
const char* separating_line = "==================================================================================================================================================================================================================";
const char* empty_line = "                                                                                                                                                                                                                  ";

//вектор юнитов, чтобы можно было считывать хуйню, не открывая при этом файл заново каждый раз
vector<Unit> StudVect;
vector<Unit> GrpVect;
vector<Unit> DptVect;
vector<Unit> UniVect;

vector<vector<Unit>> MainVect = { StudVect, GrpVect, DptVect, UniVect };
int amount = 0;

//terminal size
int terminal_width = 211;
int terminal_height = 57;


//to identify file cursor position
int pos = 0;


//to control interface output
int current_line = 1;


//sets the cursor in a particular position
void SetCursor(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


//makes the text centered
void PrintCenteredText(const char* string, int y) {
	int i = 0, len = 0;
	while (string[i] != '\0') {
		len += 1;
		++i;
	}

	//centering text
	SetCursor(terminal_width - (terminal_width / 2) - (len / 2), y);

	for (int i = 0; i < len; ++i) {
		cout << string[i];
	}

	cout << endl;
}


//defining the common struct, from which program saves/reads/stores data
void Color(int x) {
	if (x >= 0 && x <= 15)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
	else
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


//makes the cursor invisible
void HideCursor(int mode) {  
	CONSOLE_CURSOR_INFO cursor;
	if (mode == 1) {
		cursor.bVisible = FALSE;
	} else {
		cursor.bVisible = TRUE;
	}
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}


//sets terminal to fullscreen
void SetFullscrn() {  
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}


//waits for user input.... idk
void Confirm(int y) {
	short confirm = 0;
	PrintCenteredText("Нажмите Enter, чтобы продолжить...", y);
	while (confirm != 13) {
		confirm = _getch();
	}
}


//saves struct data in the file
void WriteData(Unit db1, const char* file_name, int& offset) {
	FILE* file;
	file = fopen(file_name, "rb+");

	//finds the pos -> writes PogChamp
	fseek(file, offset, SEEK_SET);
	fwrite(&db1, sizeof(Unit), 1, file);
	offset = ftell(file);

	fclose(file);
}


//reads the data from the file
int ReadData(Unit* db1, const char* file_name) {
	FILE* file;
	file = fopen(file_name, "rb");
	fseek(file, pos, SEEK_SET);

	//read only if theres something to read
	if (fread(db1, sizeof(Unit), 1, file)) {
		pos = ftell(file);
		fclose(file);
		return 1;
	}
	else {
		pos = ftell(file);
		fclose(file);
		return 0;
	}

	fclose(file);
}


//clears all the data contained in the file
void ClearAllData(const char* file_name) {
	FILE* file;
	file = fopen(file_name, "wb+");
	fclose(file);
	int len = 0;
	

	if (file_name == FILE_NAME) {
		//clearing the vector
		for (int i = 0; i < MainVect.size(); ++i) {
			len = MainVect[i].size();
			for (int j = 0; j < len; ++j) {
				MainVect[i].pop_back();
			}
		}
	}
}


//reads the data before starting the program in order to get some essential info
void ReadAllData() {
	pos = 0;
	FILE* file;
	file = fopen(FILE_NAME, "rb");
	Unit* smth = new Unit;

	while (ReadData(smth, FILE_NAME)) {
		//да простит меня бог
		MainVect[(smth->Type) - 1].push_back(*smth);
	}

	amount = MainVect[0].size() + MainVect[1].size() + MainVect[2].size() + MainVect[3].size();

	free(smth);
	pos = ftell(file);
	fclose(file);
}


//rewrites all the data
void WriteAllData() {
	Unit* smth = new Unit;
	pos = 0;
	int tmp_pos = 0;
	int counter = 0;
	FILE* file = fopen(FILE_NAME, "rb+");
	fseek(file, pos, SEEK_SET);

	//pos = 0
	while (ReadData(smth, FILE_NAME)) {
		if (smth->Data != "DELETED") {
			WriteData(*smth, TEMP_FILE_NAME, tmp_pos);
		} 
	}

	fclose(file);
	//ТЕПЕРЬ работает верно
	ClearAllData(FILE_NAME);
	pos = 0;

	FILE* temp_file = fopen(TEMP_FILE_NAME, "rb+");
	fseek(temp_file, 0, SEEK_SET);

	while (ReadData(smth, TEMP_FILE_NAME)) {
		pos -= sizeof(Unit);
		MainVect[(smth->Type) - 1].push_back(*smth);
		WriteData(*smth, FILE_NAME, pos);
	}

	amount = MainVect[0].size() + MainVect[1].size() + MainVect[2].size() + MainVect[3].size();

	ClearAllData(TEMP_FILE_NAME);
	fclose(temp_file);
	free(smth);
}



void PrintStatic(int type) {
	SetCursor(1, 1);
	cout << "ID";

	SetCursor(35, 1);
	if (type == 1) {
		cout << "Основа обучения";
	} else if (type == 2) {
		cout << "Номер группы";
	} else if (type == 3) {
		cout << "Название факультета";
	} else {
		cout << "Имя ВУЗа";
	}
	
	SetCursor(105, 1);
	if (type == 1) {
		cout << "Имя студента";
	} else if (type == 2) {
		cout << "Имя старосты";
	} else if (type == 3) {
		cout << "Имя декана";
	} else {
		cout << "Имя ректора";
	}
	

	SetCursor(70, 1);
	if (type == 1) {
		cout << "Фамилия студента";
	} else if (type == 2) {
		cout << "Фамилия старосты";
	} else if (type == 3) {
		cout << "Фамилия декана";
	} else {
		cout << "Фамилия ректора";
	}

	SetCursor(140, 1);
	if (type == 1) {
		cout << "Отчество студента";
	} else if (type == 2) {
		cout << "Отчество старосты";
	} else if (type == 3) {
		cout << "Отчество декана";
	} else {
		cout << "Отчество ректора";
	}

	SetCursor(175, 1);
	if (type == 1) {
		cout << "Группа";
	} else if (type == 2) {
		cout << "Факультет";
	} else if (type == 3) {
		cout << "Университет";
	} else {
		cout << "Город";
	}

	PrintCenteredText(separating_line, 2);
	
}



void PrintData(int y, Unit self) {
	SetCursor(1, y);
	cout << self.Num;

	SetCursor(35, y);
	cout << self.Data;

	SetCursor(70, y);
	cout << self.Name_2;

	SetCursor(105, y);
	cout << self.Name_1;

	SetCursor(140, y);
	cout << self.Name_3;

	SetCursor(175, y);
	cout << self.Apex;
}

void InputData(int y, Unit* smth, int mode) {
	//mode = 1 - Num опр. автоматически
	//mode = 2 - Num опр. вручную

	SetCursor(0, y);
	cout << empty_line;

	if (mode == 1) {
		SetCursor(1, y);
		cout << smth->Num;
	} else {
		SetCursor(1, y);
		cout << "Поиск элемента: ";
	}
	

	SetCursor(35, y);
	cin >> smth->Data;

	SetCursor(70, y);
	cin >> smth->Name_2;

	SetCursor(105, y);
	cin >> smth->Name_1;

	SetCursor(140, y);
	cin >> smth->Name_3;

	SetCursor(175, y);
	cin >> smth->Apex;
}

int StudCompare(Unit* smth, Unit* item) {
	int var_1 = 0;
	int var_2 = 0;


	if (smth->Name_1 != "/") {
		++var_1;
		if (smth->Name_1 == item->Name_1) {
			++var_2;
		}
	}

	if (smth->Name_2 != "/") {
		++var_1;
		if (smth->Name_2 == item->Name_2) {
			++var_2;
		}
	}

	if (smth->Name_3 != "/") {
		++var_1;
		if (smth->Name_3 == item->Name_3) {
			++var_2;
		}
	}

	if (smth->Data != "/") {
		++var_1;
		if (smth->Data == item->Data) {
			++var_2;
		}
	}

	if (smth->Apex != "/") {
		++var_1;
		if (smth->Apex == item->Apex) {
			++var_2;
		}
	}

	if (var_1 == var_2) {
		return 1;
	} else {
		return 0;
	}
}

//searches for the key in the file data -> if found, returns True
int StudentSearch() {
	system("cls");

	current_line = 3;
	pos = 0;
	Unit* smth = new Unit;
	Unit* item = new Unit;
	FILE* file;
	file = fopen(FILE_NAME, "rb");
	
	PrintStatic(1);

	PrintCenteredText(separating_line, 4);

	Color(4);
	PrintCenteredText("Введите данные для поиска: / - Не искать по данному полю", 5);
	InputData(3, smth, 2);
	Color(7);
	

	system("cls");

	while (ReadData(item, FILE_NAME)) {
		

		if (StudCompare(smth, item) && (item->Type == 1)) {
			
			PrintData(current_line, *item);
			PrintCenteredText(separating_line, current_line + 1);
			

			fclose(file);
			current_line += 2;
		}
	}
	PrintStatic(1);
	if (current_line == 3) {
		Color(4);
		PrintCenteredText("Таких элементов не найдено...", current_line);
		Color(7);
	}
	Confirm(current_line + 1);

	system("cls");
	fclose(file);
	free(smth);
	free(item);
	return 0;

}


//takes an ID and corrects the data
void EditData(int type, int num) {
	pos = 0;
	string new_data;
	int the_pos, line;
	Unit* smth = new Unit;

	FILE* file;
	file = fopen(FILE_NAME, "rb+");

	line = 2 * num + 1;

	while (ReadData(smth, FILE_NAME)) {
		if (smth->Type == type && smth->Num == num) {
			InputData(line, smth, 1);

			pos -= sizeof(Unit);
			WriteData(*smth, FILE_NAME, pos);
			break;
		}
	}

	fclose(file);
	free(smth);
}


int DeleteCheck(int type, string Data) {
	if (type == 1) {
		return 0;
	}
	int len = MainVect[type - 2].size();
	for (int i = 0; i < len; ++i) {
		if (MainVect[type - 2][i].Apex == Data) {
			if (type == 2) {
				PrintCenteredText("Сперва удалите всех студентов группы...", current_line + 3);
			} else if (type == 3) {
				PrintCenteredText("Сперва удалите все группы факультета...", current_line + 3);
			} else if (type == 4) {
				PrintCenteredText("Сперва удалите все факультеты университета...", current_line + 3);
			}
			Confirm(current_line + 5);
			return 1;
		}
	}
	return 0;
}


//takes an ID and deletes the data
void DeleteData(int type, int num) {
	pos = 0;
	int len = 0, cnt = 0, fl = 0;
	Unit* smth = new Unit;

	FILE* file;
	file = fopen(FILE_NAME, "rb+");

	vector<string> deleted_data;



	while (ReadData(smth, FILE_NAME)) {
		if (smth->Type == type && smth->Num == num) {
			if (DeleteCheck(type, smth->Data)) {
				fl = 1;
			} else {
				smth->Data = "DELETED";
				pos -= sizeof(Unit);
				WriteData(*smth, FILE_NAME, pos);
			}
			
		} 
		
		if (smth->Num > num && fl == 0 && smth->Type == type) {
			smth->Num -= 1;
			smth->ID -= 1;
			pos -= sizeof(Unit);
			WriteData(*smth, FILE_NAME, pos);
		}
	}
	free(smth);
	fclose(file);


}


//changes the option value 
int GetOption(int option, int mode) {
	int max;
	if (mode == 1) {
		max = 3;
	} else {
		max = 4;
	}
	
	char input = _getch();

	if (input >= 49 && input <= 56) {
		return input - '0';
		//escape    
	} else if (input == 27) {
		return -10;
	} else if (input == 13) {
		if (option >= 1 && option <= max) {
			return -option;
		}
		//стрелка вниз
	} else if (input == 'H' + 8) {
		option += 1;
		if (option > max) {
			option = 1;
		}
		return option;
		//стрелка вверх
	} else if (input == 'H') {
		option -= 1;
		if (option < 1) {
			option = max;
		}
		return option;
	} else {
		return option;
	}
	
}

//перемещение по эдиту
int GetEditCursor(int cursor, int type) {
	char input = _getch();
	int max = 0;

	max = MainVect[type - 1].size();

	if (input >= 49 && input <= 51) {
		return -(input - '0');
		//escape    
	}
	else if (input == 27) {
		return -10;
	}
	else if (input == 'H' + 8) {
		cursor += 1;
		if (cursor > max) {
			cursor = 1;
		}
		return cursor;
		//стрелка вверх
	}
	else if (input == 'H') {
		cursor -= 1;
		if (cursor < 1) {
			cursor = max;
		}
		return cursor;
	}
	else {
		return cursor;
	}

}



void TypeMenu(const char* header, int option) {
	current_line = 1;

	while (current_line < terminal_height) {
		if (current_line == 1) {
			PrintCenteredText(" Выберите элементы базы данных ", current_line);
		}
		else if (current_line > 1 && current_line < 4) {
			PrintCenteredText(separating_line, current_line);
		}
		else if (current_line == 19) {
			PrintCenteredText(header, current_line);
		}
		else if (current_line == 20) {
			if (option == 1) {
				Color(3);
				PrintCenteredText("-> 1 - Студенты <-", current_line);
				Color(7);
			}
			else {
				PrintCenteredText("   1 - Студенты   ", current_line);
			}
		}
		else if (current_line == 21) {
			if (option == 2) {
				Color(3);
				PrintCenteredText("-> 2 - Группы <-", current_line);
				Color(7);
			}
			else {
				PrintCenteredText("   2 - Группы   ", current_line);
			}
		}
		else if (current_line == 22) {
			if (option == 3) {
				Color(3);
				PrintCenteredText("-> 3 - Факультеты <-", current_line);
				Color(7);
			}
			else {
				PrintCenteredText("   3 - Факультеты   ", current_line);
			}
		}
		else if (current_line == 23) {
			if (option == 4) {
				Color(3);
				PrintCenteredText("-> 4 - Университеты <-", current_line);
				Color(7);
			}
			else {
				PrintCenteredText("   4 - Университеты   ", current_line);
			}
		}
		++current_line;
	}
}



int GetType(const char* header) {
	system("cls");
	int quit = 0;
	int option = 1;

	while (quit == 0) {
		TypeMenu(header, option);
		option = GetOption(option, 2);

		if (option == -10) {
			quit = 1;
			system("cls");
			return option;
		}
		else if (option == -1) {
			return 1;
		}
		else if (option == -2) {
			return 2;
		}
		else if (option == -3) {
			return 3;
		}
		else if (option == -4) {
			return 4;
		}
	}

	current_line = 0;

}


//prints all the data, stored in the file
void PrintAllData(int type) {
	system("cls");
	current_line = 3;
	pos = 0;

	int i = 0;
	int quit = 0;
	Unit* smth = new Unit;
	FILE* file;
	file = fopen(FILE_NAME, "rb");

	PrintStatic(type);

	if (amount != 0) {
		while (i < MainVect[type - 1].size()) {
			PrintData(current_line, MainVect[type - 1][i]);
			PrintCenteredText(separating_line, current_line + 1);
			current_line += 2;
			++i;
		}
	} else {
		PrintCenteredText("Таких данных не существует", current_line);
	}

	cout << "Размер базы данных: " << amount * sizeof(Unit) << " байт" << endl;
	Confirm(current_line + 3);

	free(smth);
	fclose(file);

	current_line = 1;
	system("cls");
}



void EditMenu(int cursor, int type) {
	current_line = 3;

	int cntr = 0, quit = 0, i = 0;

	Unit* smth = new Unit;
	FILE* file;
	file = fopen(FILE_NAME, "rb");

	PrintStatic(type);
	

	while (i < MainVect[type - 1].size()) {
		if (cursor == MainVect[type - 1][i].Num) {
			Color(3);
		}
		PrintData(current_line, MainVect[type - 1][i]);
		Color(7);
		PrintCenteredText(separating_line, current_line + 1);
		current_line += 2;
		++i;
	}

	PrintCenteredText("1 - Добавить данные, 2 - Удалить данные, 3 - Редактировать данные", current_line + 1);
	
	

	fclose(file);
	free(smth);
}


//creates a struct -> uploads it to a file
void CreateUnit(int type) {
	Unit *item = new Unit;
	int success = 1;
	++amount;

	//заполнение хуеты
	item->Type = type;

	item->ID = amount;

	item->Num = MainVect[type - 1].size() + 1;

	PrintCenteredText(separating_line, current_line + 1);
	PrintCenteredText("Введите новые данные....", current_line + 2);

	InputData(current_line, item, 1);

	MainVect[type - 1].push_back(*item);
	WriteData(*item, FILE_NAME, pos);

	//ReadAllData();
	free(item);
}

//переименовать (получаю меню редактирования)
void GetEdit(int type) {
	system("cls");
	int quit = 0;
	int cursor = 1;
	int num = 0;
	
	while (quit == 0) {
		num = cursor;
		EditMenu(cursor, type);
		cursor = GetEditCursor(cursor, type);
		
		if (cursor == -10) {
			quit = 1;
		} else if (cursor == -1) {
			HideCursor(0);
			CreateUnit(type);
			HideCursor(1);
			
			cursor = 1;
			system("cls");
		} else if (cursor == -2) {
			DeleteData(type, num);
			WriteAllData();

			cursor = 1;
			system("cls");
		} else if (cursor == -3) {
			HideCursor(0);
			EditData(type, num);
			WriteAllData();
			HideCursor(1);

			cursor = 1;
			system("cls");
		}

		SetCursor(0, 0);
	}

	system("cls");
}

//main menu -_-
void MainMenu(int option) {
	int current_line = 1;
	
	while (current_line < terminal_height) {
		if (current_line == 1) {
			PrintCenteredText("       Добро Пожаловать!       ", current_line);
		} else if (current_line > 1 && current_line < 4) {
			PrintCenteredText(separating_line, current_line);
		} else if (current_line == 20) {
			if (option == 1) {
				Color(3);
				PrintCenteredText("-> 1 - Вывести всю базу данных на экран <-", current_line);
				Color(7);
			} else {
				PrintCenteredText("   1 - Вывести всю базу данных на экран   ", current_line);
			}
		} else if (current_line == 21) {
			if (option == 2) {
				Color(3);
				PrintCenteredText("-> 2 - Добавить/Удалить/Отредактировать элемент базы данных <-", current_line);
				Color(7);
			} else {
				PrintCenteredText("   2 - Добавить/Удалить/Отредактировать элемент базы данных   ", current_line);
			}
		} else if (current_line == 22) {
			if (option == 3) {
				Color(3);
				PrintCenteredText("-> 3 - Найти элемент в базе данных <-", current_line);
				Color(7);
			} else {
				PrintCenteredText("   3 - Найти элемент в базе данных   ", current_line);
			}
		} else if (current_line == 24) {
			PrintCenteredText("Esc - Выйти из программы", current_line);
		}

		++current_line;
	}

	SetCursor(0, 0);
}

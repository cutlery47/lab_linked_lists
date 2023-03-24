#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <fstream>
#include <conio.h>
using namespace std;

//the file in which all the data is stored
const char* FILE_NAME = "data.bin";

//amounts[0] - amount of universities
//amounts[1] - amount of departments
//amounts[2] - amount of groups
//amounts[3] - amount of students
vector<int> amounts = { 0, 0, 0, 0 };
int full_amount = 0;

//to identify file cursor position
long pos = 0;

//defining the common struct, from which program saves/reads/stores data
struct Unit {
	int Type = 0; //to identify type
	int ID = 0; //to identify its index in the file
	int Num = 0; //to identify its index number within its DataType
	string Data = "data"; // 1 - University ... 2 - Faculty ... 3 - Group ... 4 - Student 
	string Name_1 = "name_1"; 
	string Name_2 = "name_2";
	string Name_3 = "name_3";
	string Apex = "____";

	void PrintData() {
		cout << "ID: " << ID << endl;
		cout << "Type: " << Type << endl;
		cout << "N: " << Num << endl;
		cout << "Data: " << Data << endl;
		cout << "Name_1: " << Name_1 << endl;
		cout << "Name_2: " << Name_2 << endl;
		cout << "Name_3: " << Name_3 << endl;
		cout << "Apex: " << Apex << endl << endl;
	}

};

//waits for user input.... idk
void confirm() {
	short confirm = 0;
	printf("===================================\n");
	printf("Нажмите Enter, чтобы продолжить...\n");
	while (confirm != 13) {
		confirm = _getch();
	}
}

//saves struct data in the file
void WriteData(Unit db1) {
	FILE* file;
	file = fopen(FILE_NAME, "rb+");

	//finds the pos -> writes PogChamp
	fseek(file, pos, SEEK_SET);
	fwrite(&db1, sizeof(Unit), 1, file);
	pos = ftell(file);

	fclose(file);
}

//reads the data from the file
int ReadData(Unit* db1) {
	FILE* file;
	file = fopen(FILE_NAME, "rb");
	fseek(file, pos, SEEK_SET);

	//read only if theres something to read
	if (fread(db1, sizeof(Unit), 1, file)) {
		pos = ftell(file);
		fclose(file);
		return 1;
	} else {
		pos = ftell(file);
		fclose(file);
		return 0;
	} 

	fclose(file);
}

//resaves all the data
void WriteAllData() {
	pos = 0;
	FILE* file;
	file = fopen(FILE_NAME, "rb+");
	fseek(file, pos, SEEK_SET);

	Unit* smth = new Unit;

	while (ReadData(smth)) {
		if (smth->Data != "DELETED") {
			pos -= sizeof(Unit);
			WriteData(*smth);
		}
	}

	fclose(file);
	free(smth);
}

//reads the data before starting the program in order to get some essential info
void ReadAllData() {
	pos = 0;
	FILE* file;
	file = fopen(FILE_NAME, "rb");
	Unit* smth = new Unit;

	while(ReadData(smth)) {
		switch (smth -> Type) {
		case 1:
			++amounts[0];
			smth -> Num = amounts[0];
		case 2:
			++amounts[1];
			smth -> Num = amounts[1];
		case 3:
			++amounts[2];
			smth -> Num = amounts[2];
		case 4:
			++amounts[3];
			smth -> Num = amounts[3];
		}
	}

	full_amount = amounts[0] + amounts[1] + amounts[2] + amounts[3];

	pos = ftell(file);
	fclose(file);
}

//clears all the data contained in the file
void ClearAllData() {
	FILE* file;
	file = fopen(FILE_NAME, "wb+");
	fclose(file);

	//cleaning a$$
	amounts = { 0, 0, 0, 0 };
	full_amount = 0;
}

//prints all the data, stored in the file
void PrintAllData() {
	pos = 0;
	Unit* smth = new Unit;
	FILE* file;
	file = fopen(FILE_NAME, "rb");

	while (ReadData(smth)) {
		(*smth).PrintData();
	}

	free(smth);
	fclose(file);

	cout << "The Database size = " << pos << " bytes" << endl;

}

//creates a struct -> uploads it to a file
void CreateUnit() {
	Unit item;
	int success = 1;
	++full_amount;
	
	item.ID = full_amount;

	cout << "Type: ";
	cin >> item.Type;
	
	//increases some values according to the ID
	switch (item.Type) {
	case 1:
		++amounts[0];
		item.Num = amounts[0];
	case 2:
		++amounts[1];
		item.Num = amounts[1];
	case 3:
		++amounts[2];
		item.Num = amounts[2];
	case 4:
		++amounts[3];
		item.Num = amounts[3];
	}

	cout << "Data: ";
	cin >> item.Data;

	cout << "Name_1: ";
	cin >> item.Name_1;

	cout << "Name_2: ";
	cin >> item.Name_2;

	cout << "Name_3: ";
	cin >> item.Name_3;

	cout << "Apex: ";
	cin >> item.Apex;

	WriteData(item);
}

//manually adding some data
void AddSomeData() {
	int flag = 1;
	do {
		CreateUnit();
		cout << "Continue: ";
		cin >> flag;
		cout << endl;
	} while (flag == 1);
}

//searches for the key in the file data -> if found, returns True
int DataSearch(string key) {
	pos = 0;
	Unit* smth = new Unit;
	FILE* file;
	file = fopen(FILE_NAME, "rb");


	while (ReadData(smth)) {
		if (key == smth->Data || key == smth->Name_1 || key == smth->Name_2 || key == smth->Name_3) {
			fclose(file);
			free(smth);
			return 1;
		}
	}

	fclose(file);
	free(smth);
	return 0;
	
}

//takes an ID and corrects the data
void EditData(int id) {
	pos = 0;
	string new_data;
	int the_pos;
	Unit* smth = new Unit;
	
	FILE* file;
	file = fopen(FILE_NAME, "rb+");


	while (ReadData(smth)) {
		if (smth -> ID == id) {
			(*smth).PrintData();
			cout << "Enter new data... (" << pos << ")" << endl;
			
			cin >> new_data;
			pos -= sizeof(Unit);
			the_pos = pos;

			cout << endl << pos << endl;
			ReadData(smth);
			smth->Data = new_data;

			pos = the_pos;
			WriteData(*smth);
			
			break;
		}
	}

	fclose(file);
	free(smth);
}

//takes an ID and deletes the data
void DeleteData(int id) {
	pos = 0;

	Unit* smth = new Unit;
	int counter = 1;
	FILE* file;
	file = fopen(FILE_NAME, "rb+");

	while (ReadData(smth)) {
		if (counter >= id) {
			if (counter == full_amount) {
				pos -= sizeof(Unit);
				smth->Data = "DELETED";
				WriteData(*smth);
			} else {
				pos -= 2 * sizeof(Unit);
				smth->ID = counter - 1;
				WriteData(*smth);
				pos += sizeof(Unit);
			}
		}

		++counter;
	}
	fclose(file);


}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ReadAllData();
	
	AddSomeData();
	
	cout << "--------------------------------------------" << endl;
	DeleteData(3);
	WriteAllData();
	cout << "--------------------------------------------" << endl;

	PrintAllData();
	ClearAllData();

	exit(0);
	return 0;
}



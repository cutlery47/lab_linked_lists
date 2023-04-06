#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include "diff.h"
using namespace std;

int main(int argc, char* argv[]) {
    system("cls");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    HideCursor();

    char el;
    int cntr = 0;
    int length_1 = 0, length_2 = 0;
    int height_1 = 0, height_2 = 0;
    int error_1 = 0, error_2 = 0;
    fstream file;

    error_1 = InputCheck(argc, argv);

    if (error_1 == 1) {
        system("cls");
        return 0;
    }
    
    error_2 = FormatCheck(argv[1], argv[2], sizeof(argv[1]) + 1, sizeof(argv[2]) + 1);
    
    if (error_2 == 1) {
        system("cls");
        return 0;
    }

    length_1 = GetFileLen(argv[1], length_1);
    length_2 = GetFileLen(argv[2], length_2);

    height_1 = GetFileHeight(argv[1], height_1);
    height_2 = GetFileHeight(argv[2], height_2);

    char* string_1 = new char[length_1 + 1];
    char* string_2 = new char[length_2 + 1];

    string_1 = FileToString(argv[1], string_1);
    string_2 = FileToString(argv[2], string_2);

    int **matrix = LCS_Matrix(string_1, string_2, length_1, length_2);
    int result_len = matrix[length_1][length_2];
    char* result = LCS_String(string_1, string_2, matrix, result_len, length_1, length_2);

    MainMenu(argv[1], argv[2], string_1, string_2, result, length_1, length_2, result_len, height_1, height_2);
   
    system("cls");
    return 0;
}
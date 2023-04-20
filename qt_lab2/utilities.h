#ifndef UTILITIES_H
#define UTILITIES_H

#include <QString>
#include <vector>
#include <iostream>


//заполнение студента
extern QString student;
extern int gender;
extern int group;
extern QString txt_group;
extern bool allowed;

//таблица
extern std::vector<QString> subjects;
extern std::vector<QString> grades;

#endif // UTILITIES_H

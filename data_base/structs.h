using namespace std;

struct Unit {
	int Type = 0; 
	int ID = 0; 
	int Num = 0; 

	string Data = "data"; 
	string Name_1 = "name_1";
	string Name_2 = "name_2";
	string Name_3 = "name_3";
	string Apex = "____";
};

struct Student {

	int StudId;

	string FirstName;
	string Surname;
	string FamilyName;
	

	string Group;
	string AddInfo;	
};

struct Group {

	vector<Student> Students; //всех студентов сюда

	int GroupID;
	
	string HeadName;
	string HeadSurname;
	string HeadFamilyName;

	string Faculty;
	string AddInfo;

};

struct Department {

	vector<Group> Groups; //все группы сюда

	int DptID;

	string HeadName;
	string HeadSurname;
	string HeadFamilyName;

	string University;
	string AddInfo;

};

struct University {

	vector<Department> Departments; //все факультеты сюда

	int UniID;

	string HeadName;
	string HeadSurname;
	string HeadFamilyName;

	string City;
	string AddInfo;
};

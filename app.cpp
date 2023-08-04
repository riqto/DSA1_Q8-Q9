#include	<iostream>
#include	<cstdlib> 
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"

using namespace std;
int choice;

//bool ReadFile(string, List *);
//bool DeleteRecord(List *, char *);
//bool Display(List*, int, int);
//bool InsertBook(string, List *);
//bool SearchStudent(List *, char *id, LibStudent &);
//bool computeAndDisplayStatistics(List *);
//bool printStuWithSameBook(List *, char *);
bool displayWarnedStudent(List *, List *, List *);
int menu();
int calculateTotalFine(Date);
int toJulianDay(int, int, int);
int calculateDueDay(Date);


int main() {
	
	List* list1 = new List();
	List* type1 = new List(),
		* type2 = new List();

	//menu
	do {
		menu();

		switch (choice) {

		case 1:
			cout << "\n\n\nREAD FILE\n\n\n";
			//ReadFile(file1, list1)
			break;

		case 2:
			cout << "\n\n\nDELETE STUDENT RECORD\n\n";
			//DeleteRecord(list1, id)
			break;

		case 3:
			cout << "\n\n\nSEARCH STUDENT\n\n";
			//SearchStudent(list1, id, stu)
			break;

		case 4:
			cout << "\n\n\nINSERT BOOK\n\n";
			//InsertBook(file2, list1)
			break;

		case 5:
			cout << "\n\n\nDISPLAY OUTPUT\n\n\n";
			//Display(list1, source, detail)
			break;

		case 6:
			//computeAndDisplayStatistics(list1);
			break;
		case 7:
			//printStuWithSameBook(list1, callNum);
			break;
		case 8:
			displayWarnedStudent(list1, type1, type2);
			break;

		case 9:
			break;

		default:
			cout << "\n\n\nInvalid Choice. Please Choose the Task Again.\n\n\n";
		}

	} while (choice != 9);

	cout << "\n\n";
	system("pause");
	return 0;
}

int menu() {

	cout << "Menu\n\n";

	cout << "1. Read file.\n";
	cout << "2. Delete record.\n";
	cout << "3. Search student.\n";
	cout << "4. Insert book.\n";
	cout << "5. Display output\n";
	cout << "6. Compute and Display Statistics\n";
	cout << "7. Student with Same Book\n";
	cout << "8. Diplay Warned Student\n";
	cout << "9. Exit.\n";
	cout << "Enter your choice: ";
	cin >> choice;

	return choice;
}

/*
bool ReadFile(string filename, List* list) {

}

bool DeleteRecord(List* list, char* id) {
	
}

bool InsertBook(string filename, List* list) {
	
}

bool Display(List* list, int source, int detail) {

}

bool computeAndDisplayStatistics(List* list) {

}

bool printStuWithSameBook(List* list, char* callNum) {

}
*/


bool displayWarnedStudent(List* list, List* type1, List* type2) {

	Node* cur = list->head;

	if (cur == NULL) {
		cout << "\n\nList is an empty list.\n\n";
		return false;
	}

	if (cur->item.totalbook == 0) {
		cout << "\n\nNo book insert to the student.\n\n";
		return false;
	}

	while (cur != NULL) {

		int type1_bookoverdue = 0;
		int type2_bookoverdue = 0;

		for (int i = 0; i < cur->item.totalbook; i++) {

			//type1
			int dueDay = calculateDueDay(cur->item.book[i].due);

			if (dueDay >= 10)
				type1_bookoverdue++;

			if (type1_bookoverdue > 2) {
				type1->insert(cur->item);
				Node* tmp = type1->head;
				tmp->item.print(cout);
			}

			//type2
			if (dueDay > 0)
				type2_bookoverdue++;

			if (cur->item.total_fine > 50 && type2_bookoverdue == cur->item.totalbook) {
				type2->insert(cur->item);
				Node* tmp = type2->head;
				tmp->item.print(cout);
			}

		}
		cur = cur->next;
	}
	return true;
}

int calculateTotalFine(Date dueDate) {

	//current date is 29/3/2020
	//one day delayed - RM0.50
	int dueDay = calculateDueDay(dueDate);

	if (dueDay > 0)
		return dueDay * 0.5;
	else
		return dueDay = 0;

}

int calculateDueDay(Date duedate) {

	//current date is 29/3/2020
	//one day delayed - RM0.50
	int currentyear = 2020;
	int currentmonth = 3;
	int currentday = 29;

	int duedate_julianDay = toJulianDay(duedate.year, duedate.month, duedate.day);
	int currentdate_julianDay = toJulianDay(currentyear, currentmonth, currentday);

	int dueDay = currentdate_julianDay - duedate_julianDay;
	
	return dueDay;

}

int toJulianDay(int year, int month, int day) { //the format of julian day

	int a = (14 - month) / 12;
	int y = year + 4800 - a;
	int m = month + 12 * a - 3;
	return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;

}

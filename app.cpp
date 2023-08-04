#include	<iostream>
#include	<cstdlib> 
#include	<cstdio>
#include    <fstream>
#include    <string>
#include	"List.h"
#include    "LibStudent.h"
#include    "LibBook.h"

#define _CRT_SECURE_NO_WARNINGS

using namespace std;
int choice;

bool ReadFile(string, List *);
bool DeleteRecord(List *, char *);
bool Display(List*, int, int);
bool InsertBook(string, List *);
bool SearchStudent(List *, char *id, LibStudent &);
//bool computeAndDisplayStatistics(List *);
//bool printStuWithSameBook(List *, char *);
bool displayWarnedStudent(List *, List *, List *);
int menu();
int calculateTotalFine(Date);
int toJulianDay(int, int, int);
int calculateDueDay(Date);
void removeUnderscore(char*);
char* mystrtok(char*, char);


int main() {

	string file1 = "student.txt", file2 = "book.txt";
	List* list1 = new List();
	LibStudent stu;
	char* id = stu.id; //*id = first adress value of stu.id
	int source, detail;
	//char* callNum;
	List* type1 = new List(),
		* type2 = new List();

	//menu
	do {
		menu();

		switch (choice) {

		case 1:
			cout << "\n\n\nREAD FILE\n\n\n";
			if (ReadFile(file1, list1))
				cout << "\n" << list1->count << " records have been successfully read.\n\n\n";
			break;

		case 2:
			cout << "\n\n\nDELETE STUDENT RECORD\n\n";
			if (DeleteRecord(list1, id))
				cout << "\n\nRecord has been successfully deleted.\n\n\n";
			else
				cout << "\n\nID cannot found in list.\n\n\n";
			break;

		case 3:
			cout << "\n\n\nSEARCH STUDENT\n\n";
			if (SearchStudent(list1, id, stu)) {
				stu.print(cout);
				cout << "\n\n\n";
			}
			else
				cout << "\n\nID cannot found in list.\n\n\n";
			break;

		case 4:
			cout << "\n\n\nINSERT BOOK\n\n";
			if (InsertBook(file2, list1))
				cout << "\n\nBooks inserted successfully to student list.\n\n";
			break;

		case 5:
			cout << "\n\n\nDISPLAY OUTPUT\n\n\n";

			cout << "Where do you want to display the output (1 - File / 2 - Screen): ";
			cin >> source;

			cout << "\n";

			cout << "Do you want to display book list for every student (1 - YES / 2 - NO): ";
			cin >> detail;

			if (Display(list1, source, detail))
				cout << "Successfully display output\n\n\n";
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

bool ReadFile(string filename, List* list) {

	ifstream in(filename);
	LibStudent stu;
	char s[200];

	if (!in.is_open()) {
		cout << "\n\n\nFail to open file " << filename << "!\n\n\n";
		return false;
	}
	
	else {
		while (!in.eof()) {
			for (int sk = 0; sk < 3; sk++)
				in >> s;
			in >> stu.id;

			for (int sk = 0; sk < 2; sk++)
				in >> s;
			in.ignore();
			in.getline(stu.name, 30);

			for (int sk = 0; sk < 2; sk++)
				in >> s;
			in >> stu.course;

			for (int sk = 0; sk < 3; sk++)
				in >> s;
			in >> stu.phone_no;

			Node* cur = list->head; //Node type change to Struct type, point to node's head
			bool foundDuplicate = false;
			while (cur != NULL) {
				if (stu.compareName2(cur->item)){ //check redundant
					printf("\n\nFound Duplicate Record.\n");
					foundDuplicate = true; //redundant record won't insert
					printf("<Ignored>\n");
					break;
				}
				cur = cur->next;
			}
			if (!foundDuplicate) {
				if (list->insert(stu));
					//stu.print(cout);
				else {
					printf("\n\n\nCannot Insert from Node.\n\n\n");
					return false;
				}
			}
		}
		in.close();
		return true;
	}


}

bool DeleteRecord(List* list, char* id) {

	cout << "\n\n\nExisting Student ID:\n";
	Node* cur = list->head;

	while (cur != NULL) {
		cout << cur->item.name << "\t\t" << cur->item.id << endl;
		cur = cur->next;
	}
	cout << "Please input a student ID to delete his/her information: ";
	cin >> id;

	cur = list->head;
	int dlCount = 1;

	while (cur != NULL) {
		if (strcmp(id, cur->item.id) == 0) {
			list->remove(dlCount);
			return true;
		}
		cur = cur->next;
		dlCount++;
	}
	return false;
}


bool SearchStudent(List* list, char* id, LibStudent& stu) {

	cout << "\n\n\nExisting Student ID:\n";
	Node* cur = list->head;

	while (cur != NULL) {
		cout << cur->item.name << "\t\t" << cur->item.id << endl;
		cur = cur->next;
	}
	cout << "Please input a student ID to search for his/her information: ";
	cin >> id;

	cur = list->head;
	int srCount = 1;

	while (cur != NULL) {
		if (strcmp(id, cur->item.id) == 0) {
			list->get(srCount, stu);
			return true;
		}
		cur = cur->next;
		srCount++;
	}
	return false;

}

char* mystrtok(char* n, char s) { //n - authorName ; s - '/'

	static char* input = NULL;

	if (n != NULL)
		input = n;

	if (input == NULL)
		return NULL;

	char* result = new char[strlen(input) + 1]; //create a new char array to store into author array
	int i;

	for (i = 0; input[i] != '\0'; i++) {
		if (input[i] != s)
			result[i] = input[i];
		else {
			result[i] = '\0';
			input = input + i + 1; //input position updated
			return result;
		}
	}

	result[i] = '\0';
	input = NULL;
	return result;

}

bool InsertBook(string filename, List* list) {

	ifstream in(filename);
	LibBook bk;
	LibStudent stu;
	Date dt1, dt2;
	char authorName[50];
	int p; //each book's authors position

	if (!in) {
		cout << "Fail to open file " << filename << "!\n\n\n";
		return false;
	}

	else {
		while (in >> stu.id) {

			in >> authorName;
			removeUnderscore(authorName); //replace underscore to empty space

			p = 0;
			bk.author[p] = mystrtok(authorName, '/');

			while (bk.author[p] != NULL) {
				p++;
				bk.author[p] = mystrtok(NULL, '/');
			}

			in >> bk.title;
			removeUnderscore(bk.title); //replace underscore to empty space


			in >> bk.publisher;

			in >> bk.ISBN;

			in >> bk.yearPublished;

			in >> bk.callNum;

			in >> dt1.day;

			in.ignore(dt1.day, '/');
			in >> dt1.month;

			in.ignore(dt1.month, '/');
			in >> dt1.year;

			in >> dt2.day;
			
			in.ignore(dt2.day, '/');
			in >> dt2.month;

			in.ignore(dt2.month, '/');
			in >> dt2.year;


			Node* cur = list->head;
			while (cur != NULL) {
				if (strcmp(cur->item.id, stu.id) == 0) {

					int i;

					i = cur->item.totalbook;

					cur->item.book[i] = bk;
					cur->item.book[i].borrow = dt1;
					cur->item.book[i].due = dt2;
					cur->item.book[i].fine = calculateTotalFine(dt2);

					cur->item.total_fine += cur->item.book[i].fine;

					cur->item.print(cout);
					cout << "\nBOOK" << cur->item.totalbook+1 << "\n\n";
					cur->item.book[i].print(cout);

					cur->item.totalbook++;
					break;


				}
				cur = cur->next;
			}
			
		}
		in.close();


	}
	return true;

}

void removeUnderscore(char* title) {
	
	int titlelen = strlen(title);

	for (int i = 0; i < titlelen; i++) {

		if (title[i] == '_')
			title[i] = ' ';
	}

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

bool Display(List* list, int source, int detail) {

	Node* cur;
	int countstd = 1;

	if (source == 2) {

		if (detail == 1) {

			cur = list->head;
			while (cur != NULL) {
				cout << "\nSTUDENT " << countstd << "\n";
				cur->item.print(cout);
				cout << "\n\nBOOK LIST: \n";
				for (int j = 0; j < cur->item.totalbook; j++) {
					cout << "\nBook " << j + 1 << "\n\n";
					cur->item.book[j].print(cout);
				}
				cur = cur->next;
				countstd++;
				cout << "\n\n*****************************************************************************\n\n";
			}
			return true;
		}

		else if (detail == 2) {
			cur = list->head;
			while (cur != NULL) {
				cout << "\nSTUDENT " << countstd << "\n";
				cur->item.print(cout);
				cur = cur->next;
				countstd++;
				cout << "\n\n*****************************************************************************\n\n";
			}
			return true;
		}

		else {
			cout << "Invalid input.\n\n\n";
			return false;
		}

	}

	else if (source == 1) {

		if (detail == 1) {

			ofstream out1("student_booklist.txt");

			cur = list->head;
			while (cur != NULL) {

				out1 << "\nSTUDENT " << countstd;
				cur->item.print(out1);

				out1 << "BOOK LIST:\n\n";
				for (int j = 0; j < cur->item.totalbook; j++) {
					out1 << "\nBook " << j + 1 << "\n\n";
					cur->item.book[j].print(out1);
				}
				cur = cur->next;
				countstd++;
				out1 << "\n*****************************************************************************\n";

			}
			out1.close();
			cout << "\n\n\nSuccessfully display output to student_booklist.txt\n\n\n";
			return true;
		}

		else if (detail == 2) {

			ofstream out2("student_info.txt");

			cur = list->head;
			while (cur != NULL) {
				out2 << "\nSTUDENT " << countstd;
				cur->item.print(out2);
				cur = cur->next;
				countstd++;
				out2 << "\n*****************************************************************************\n";
			}
			out2.close();
			cout << "\n\n\nSuccessfully display output to student_info.txt\n\n\n";
			return true;
		}

		else {
			cout << "Invalid input.\n\n\n";
			return false;
		}

	}

	else {
		cout << "Invalid input.\n\n\n";
		return false;
	}
}

/*
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
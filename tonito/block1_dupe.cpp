#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include "Dupe_header.h"

using namespace std;

int main()
{
    string file_name, delete_file, last_name, first_name, student_number, middle;
    int answer; 

    do
    {
        cout << "STUDENT REGISTRATION BLOCK" << endl;
        cout << "What Would You Like to do?" << endl;

        cout << "Type 1 if you would like to add a student" << endl;
        cout << "Type 2 if you would like to show all students" << endl;
        cout << "Type 3 if you would like to display a specific student's information" << endl;
        cout << "Type 4 if you would like to delete a specific student" << endl;
        cin >> answer;
        cin.ignore();
    }
    while (answer > 4 || answer < 1);

    switch (answer) {
        case 1:
            add_student();
            break;
        case 2:
            show_all();
            break;
        case 3:
            cout << "Type the exact file name of the student you would like to display (Format: LastName_FirstName.txt)" << endl;
            getline(cin, file_name);
            show_student(file_name);
            break;
        case 4:
            cout << "Type the last name of the student you want to delete" << endl;
            getline(cin, last_name);

            cout << "Type the first name of the student you want to delete" << endl;
            getline(cin, first_name);

            cout << "Type the middle initial of the student you want to delete (Type '1' if there is none)" << endl;
            getline(cin, middle);

            cout << "Type the student number of the student you want to delete (Format: 23-xx)" << endl;
            getline(cin, student_number);

            delete_student(last_name, first_name, middle, student_number);
            break;
    }

    return 0;
}
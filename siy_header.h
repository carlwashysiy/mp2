#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <limits>
#include <sstream>
#include <stdio.h>
#include <ctype.h>

using namespace std;

string student_info[20][9];

int student_count = 0;
int *pntr = &student_count;

class Student_info
{
public:
    Student_info(string s, string gn, string mi, string hn, string sn, string sub, string b, string c, string n)
    {
        surname = s;
        given_name = gn;
        middle_initial = mi;
        house_number = hn;
        street_name = sn;
        subdivision = sub;
        barangay = b;
        city = c;
        number = n;

        filename = surname + "_" + given_name + ".txt";

        if (middle_initial == "")
        {
            fullname = surname + ", " + given_name;
        }
        else
            fullname = surname + ", " + given_name + " " + middle_initial + '.';
    };

    void Create_File()
    {
        fstream indiv;
        indiv.open(filename, ios::out);
        if (indiv.is_open())
        {
            indiv << fullname << endl;
            indiv << house_number << " " << street_name << " " << subdivision << " " << barangay << " " << city << endl;
            indiv << number << endl;
            indiv.close();
        }
        else
            cout << "Unable to open file.";
    };

    void Student_List()
    {
        fstream compile;
        compile.open("Student List.txt", ios::app);
        if (compile.is_open())
        {
            compile << fullname << endl;
            compile.close();
        }
        else
            cout << "Unable to open file.";
    };

    void Make_Student_Number()
    {
        ifstream myFile("Student List.txt");
        if (myFile.is_open())
        {
            while (!myFile.eof())
            {
                getline(myFile, line);
                array[loop] = line;
                loop++;
            }
            myFile.close();
        }
        else
            cout << "Unable to open file.";

        string add_number;

        if (loop - 1 < 10)
        {
            add_number = "0" + to_string(loop - 1);
        }

        else
        {
            add_number = to_string(loop - 1);
        }

        student_number = "23-" + add_number + " ";

        fstream add_student_number;
        add_student_number.open(filename, ios::app);
        if (add_student_number.is_open())
        {
            add_student_number << student_number;
            add_student_number.close();
        }
        else
            cout << "Unable to open file.";
    };

    void New_File()
    {
        fstream newfile;
        newfile.open("Student List.txt", ios::out);
        if (newfile.is_open())
        {
            if (loop > 2)
            {
                for (int i = 0; i < loop - 2; i++)
                {
                    newfile << array[i] << endl;
                }
                newfile << student_number << "" << fullname << endl;
            }
            else
                newfile << student_number << "" << fullname << endl;
            newfile.close();
        }
        else
            cout << "Unable to open file.";
    }

private:
    string surname;
    string given_name;
    string middle_initial;
    string house_number;
    string street_name;
    string subdivision;
    string barangay;
    string city;
    string number;
    string filename;
    string fullname;
    string student_number;
    string line;
    string array[20];
    int loop = 0;
};

class Display
{
public:
    Display(string fn)
    {
        filename = fn;
    };

    int Display_File()
    {
        ifstream File(filename);
        if (File.is_open())
        {
            while (!File.eof())
            {
                getline(File, lines);
                students[loop] = lines;
                loop++;
            }
            File.close();
        }
        else
        {
            cout << "Unable to open file.";
            return 1;
        }

        for (int i = 0; i < loop; i++)
        {
            cout << students[i] << endl;
        }
        return 0;
    };

private:
    string filename;
    int number = 0;
    int loop = 0;
    string lines;
    string students[20];
};

bool input_validation(string data)
{
    bool valid = false;
    for (int i = 0; i < data.length(); i++)
    {
        if (isalpha(data[i]))
        {
            valid = true;
        }
        else
            return false;
    }
    return true;
}

// Function for Adding Students to the Database
int add_student()
{
    // Declaration of Variables to be used in Getting The Student's Information;
    char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    bool valid_middle, valid_number = false;
    bool tempv_number = true;

    if (student_count > 20)
    {
        cout << "Max amount of students has been reached!";
        return 1;
    }

    cout << "STUDENT INFORMATION" << endl;
    cout << "Please Fill out the Following Fields:" << endl;
    cout << "STUDENT NAME" << endl;

    // Asking the User to Input the Student's Information
    do
    {
        cout << "Surname: ";
        getline(cin, student_info[*pntr][0]);
    } while (input_validation(student_info[*pntr][0]) == false);

    do
    {
        cout << "Given Name: ";
        getline(cin, student_info[*pntr][1]);
    } while (input_validation(student_info[*pntr][1]) == false);

    do
    {
        cout << "Middle Initial (If you do not have one type 1): ";
        getline(cin, student_info[*pntr][2]);

        // Makes sure the Middle Initial is Upper Case
        for (int i = 0; i < student_info[*pntr][2].length(); i++)
        {
            toupper(student_info[*pntr][2][i]);
        }

        // If 1 is Typed, Nothing will be Displayed
        if (student_info[*pntr][2] == "1")
        {
            student_info[*pntr][2] = "";
            valid_middle = true;
        }

        else if (student_info[*pntr][2].length() <= 2)
        {
            valid_middle = true;
        }

        else
            valid_middle = false;
    } while (valid_middle == false);

    cout << "STUDENT ADDRESS" << endl;

    cout << "House Number: ";
    getline(cin, student_info[*pntr][3]);

    do
    {
        cout << "Street Name (If you don't have one, type 1): ";
        getline(cin, student_info[*pntr][4]);
    } while (input_validation(student_info[*pntr][4]) == false || student_info[*pntr][4] == "1");

    if (student_info[*pntr][4] == "1")
    {
        student_info[*pntr][4] = "";
    }

    do
    {
        cout << "Subdivision/Building Name (If you don't have one, type 1): ";
        getline(cin, student_info[*pntr][5]);
    } while (input_validation(student_info[*pntr][5]) == false || student_info[*pntr][5] == "1");

    if (student_info[*pntr][5] == "1")
    {
        student_info[*pntr][5] = "";
    }

    do
    {
        cout << "Barangay Name: ";
        getline(cin, student_info[*pntr][6]);
    } while (input_validation(student_info[*pntr][6]) == false);

    do
    {
        cout << "City/Municipality: ";
        getline(cin, student_info[*pntr][7]);
    } while (input_validation(student_info[*pntr][7]) == false);

    // The Loop will keep Occuring Until An 11-Digit Phone Number is Typed
    do
    {
        cout << "Phone Number (Please follow the format 09xxxxxxxxx): ";
        getline(cin, student_info[*pntr][8]);

        if (student_info[*pntr][8].length() == 11)
        {

            if (student_info[*pntr][8][0] == '0')
            {

                if (student_info[*pntr][8][1] == '9')
                {

                    for (int i = 2; i < 11; i++)
                    {

                        for (int j = 0; j < 10; j++)
                        {
                            if (student_info[*pntr][8][i] == numbers[j])
                            {
                                valid_number = true;
                                break;
                            }
                        }

                        if (valid_number == false)
                        {
                            break;
                        }
                    }
                }
            }
        }
    } while (valid_number == false);

    Student_info student(student_info[*pntr][0], student_info[*pntr][1], student_info[*pntr][2], student_info[*pntr][3], student_info[*pntr][4], student_info[*pntr][5], student_info[*pntr][6], student_info[*pntr][7], student_info[*pntr][8]);

    student.Create_File();
    student.Student_List();
    student.Make_Student_Number();
    student.New_File();

    // Increases the Student Count for the Next Student to be Registered
    *pntr++;
    return 0;
}

// Function for Displaying All the Students in the Terminal
void show_all()
{
    string filename = "Student List.txt";
    Display student_list(filename);
    student_list.Display_File();
}

// Function for Displaying a Specific File's Information in the Terminal
void show_student(string filename)
{
    Display student_file(filename);
    student_file.Display_File();
}

// Function to Remove Student File and from Database
int delete_student(string last, string first, string middle, string number)
{
    string file = last + "_" + first + ".txt";
    string stringToRemove;

    if (middle == "1")
    {
        string stringToRemove = number + "  " + last + ", " + first;
    }
    else
        string stringToRemove = number + "  " + last + ", " + first + " " + middle + ".";

    string filename = "Student List.txt";

    ifstream input(filename);
    ofstream temp("temp.txt");

    if (!input.is_open() || !temp.is_open())
    {
        cerr << "Error opening files." << endl;
        return 1;
    }

    string line;
    bool found = false;

    // Loops through file to copy the lines to the temp file that aren't the student to be removed and omit copying the removed student
    while (getline(input, line))
    {
        if (line.find(stringToRemove) == string::npos)
        {
            temp << line << endl;
        }

        else
        {
            found = true;
        }
    }
//Student List.txt
    input.close();
    temp.close();

    // Checks if the original file was removed and the temp file was properly renamed
    if (found == true)
    {

        if (remove(filename.c_str()) != 0)
        {
            cerr << "Could not delete original file" << endl;
            return 1;
        }
        if (rename("temp.txt", filename.c_str()) != 0)
        {
            cerr << "Could not create new file" << endl;
            return 1;
        }

        // Removes the Deleted Student's File
        remove(file.c_str());
        cout << "Student Info: '" << stringToRemove << "' has been removed from the database" << endl;
    }

    // Checks if the student is in the database
    else if (found == false)
    {
        cout << "Sorry, this student is not in our database.\n\n";
        remove("temp.txt");
    }

    return 0;
}

void block1(bool&MenuResetButton)
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
    } while (answer > 4 || answer < 1);

    switch (answer)
    {
    case 1:
        add_student();
        cout << "Student successfully registered!\n\n";
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
    MenuResetButton = true;
}

void inputVal(int &Input, int UpperLim, int LowerLim, string Message)
{
    while (!(cin >> Input) || Input > UpperLim || Input < LowerLim)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "!!Bad data!!";
        cout << Message;
    }
    return;
}
void MoveOnConfirm()
{
    cout << "Press any key then [enter] to continue: ";
    string confirm;
    cin >> confirm;
}
class Parent
{
public:
    Parent(string N, string A, int CN, string EN)
    {
        Name = N;
        Address = A;
        ContactNumber = CN;
        EmployeeNumber = EN;
    }
    void GetName()
    {
        string FullName, FirstName, LastName, MiddleInitial;
        cout << "[Teacher's Full Name:]" << endl
             << "Input Last Name: ";
        cin.ignore();
        getline(cin, LastName);
        cout << "Input Given Name: ";
        getline(cin, FirstName);
        cout << "Input Middle Initial (press [enter] if none): ";
        getline(cin, MiddleInitial);
        FullName = LastName + ", " + FirstName + " " + MiddleInitial;
        Name = FullName;
        FileName = LastName + "_" + FirstName + ".txt";
    }
    void AssignNum()
    {
        int EmployeeNum = 1;
        EmployeeNumber = "01-00" + to_string(EmployeeNum);
        fstream Teach;
        string line;
        Teach.open("Teacher List.txt", ios::in);
        if (Teach.is_open())
        {
            while (getline(Teach, line))
            {
                while (line.find(EmployeeNumber) != string::npos)
                {
                    EmployeeNum++;
                    EmployeeNumber = "01-00" + to_string(EmployeeNum);
                }
            }
            Teach.close();
        }
    }
    void PrintInfo()
    {
        cout << Name << endl
             << Address << endl
             << ContactNumber;
    }
    void ViewFile(string FileName)
    {
        fstream File;
        File.open(FileName, ios ::in);
        {
            if (!File.is_open())
            {
                cout << "\n[File Not Found] \nBack to main menu...\n\n"
                     << endl;
                MoveOnConfirm();
            }
            else
            {
                string line;
                while (getline(File, line))
                {
                    cout << line << '\n';
                }
                cout << endl;
                File.close();
            }
        }
    }

protected:
    string Name;
    string Address;
    int ContactNumber;
    string EmployeeNumber;
    string FileName;
    bool FileExist;
};

class Teacher : public Parent
{
public:
    Teacher(string N, string A, int CN, string EN, string S) : Parent(N, A, CN, EN)
    {
        Name = N;
        Address = A;
        ContactNumber = CN;
        EmployeeNumber = EN;
        Subject = S;
    }
    void GetSubject()
    {
        int choice = 1;
        string SubjectChoice[10][2]{
            {"[1] Programming", "Programming"},
            {"[2] Drafting", "Drafting"},
            {"[3] Data Analysis", "Data Analysis"},
            {"[4] Circuits 1", "Circuits 1"},
            {"[5] Circuits 2", "Circuits 2"},
            {"[6] OOP", "OOP"},
            {"[7] Electronics 1", "Electronics 1"},
            {"[8] Electronics 2", "Electronics 2"},
            {"[9] Logic Circuits", "Logic Circuits"},
            {"[10] Microprocessors", "Microprocessors"}};
        string SubjectList[10];
        cout << "[Teacher's Subjects:]" << endl;
        cout << "List of subjects:" << endl
             << endl;
        for (int k = 0; k < 10; k++)
        {
            cout << SubjectChoice[k][0] << endl;
        }
        cout << "[0] End Subject Selection" << endl;

        cout << "\n!!please enter the number of the subject one by one!!" << endl
             << "!!enter [0] after subject selection!!" << endl;
        int i = 0;
        while (choice != 0)
        {
            cout << "\n\nEnter number of choice: ";
            inputVal(choice, 10, 0, " Enter number between [0-10] only: ");
            string SubjChoice;
            cout << "You have chosen: ";
            int j = choice - 1;
            cout << SubjectChoice[j - 1][2];
            SubjChoice = SubjectChoice[j][1];

            SubjectList[i] = SubjChoice;
            i++;
        }

        cout << "[0] End Subject Selection\n\n"
             << "You have input [0] and thus have excited subject selection. " << endl;

        for (int j = 0; j < i - 1; j++)
        {
            Subject = Subject + ", " + SubjectList[j];
        }
    }
    void GetInfo()
    {
        // Get Name
        GetName();
        fstream IndivFile;
        IndivFile.open(FileName);
        {
            if (IndivFile.is_open())
            {
                cout << "!!error!! Teacher already in the database" << endl;
                IndivFile.close();
                cout << "\nBack to main menu...\n\nPress any key then [enter] to continue: ";
                string confirm;
                cin >> confirm;
                FileExist = true;
    
                return;
            }
        }

        // Get Address
        string HouseNum, Street, SubdBldg, Brgy, City;
        cout << "[Teacher's Full Address:]" << endl
             << "Input House Number: ";
        cin.ignore();
        getline(cin, HouseNum);
        cout << "Input Street Name and/or number: ";
        getline(cin, Street);
        cout << "Input Building/Subdivision (press [enter] if none): ";
        getline(cin, SubdBldg);
        cout << "Input Barangay: ";
        getline(cin, Brgy);
        cout << "Input City/Municipality: ";
        getline(cin, City);
        Address = HouseNum + " " + Street + " " + SubdBldg + " " + Brgy + " " + City;
        // Contact Number
        cout << "[Teacher's Mobile Number:]" << endl
             << "Input Contact Number: ";
        while (!(cin >> ContactNumber))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "!!Bad data!!";
            cout << " Enter number only" << endl;
            cout << "Input Mobile Number: ";
        }
        // Subject
        GetSubject();
        // Assign Number
        AssignNum();
        // Add to Files
        IndivFile.open(FileName, ios ::out);
        {
            if (!IndivFile.is_open())
            {
                cout << "error encountered in opening Indiv file" << endl;
            }
            else
            {
                IndivFile << Name << endl;
                IndivFile << Address << endl;
                IndivFile << "0" << ContactNumber << endl;
                IndivFile << "Employee# " << EmployeeNumber << endl;
                IndivFile << "Subjects: " << Subject << endl;
                IndivFile.close();
            }
        }
        fstream TeacherFile;
        TeacherFile.open("Teacher List.txt", ios ::app);
        {
            if (!TeacherFile.is_open())
            {
                cout << "error encountered in opening All teacher file" << endl;
            }
            else
            {
                TeacherFile << EmployeeNumber << " ";
                TeacherFile << Name << endl;
                TeacherFile.close();
            }
        }
        cout << Name << endl;
        cout << Address << endl;
        cout << "0" << ContactNumber << endl;
        cout << "Employee# " << EmployeeNumber << endl;
        cout << "Subjects: " << Subject << endl
             << endl;
        MoveOnConfirm();
    }
    void ViewTeacher()
    {
        int choice;
        cout << "Doing #2 process - View teacher list\n"
             << endl
             << endl;
        cout << "[View Teacher Database]" << endl
             << "What would you like to do?" << endl
             << endl
             << "[1] View Full Teacher list" << endl
             << "[2] View Individual Teacher file" << endl
             << endl
             << "[Please enter the number of your desired choice]: ";
        inputVal(choice, 2, 1, " Please enter a number between [1-2]: ");

        if (choice == 1)
        {
            
            cout << "[1] View Full Teacher list\n"
                 << endl;
            cout << "Full Teacher Database: " << endl
                 << endl;
            ViewFile("Teacher List.txt");
            MoveOnConfirm();
        }
        else if (choice == 2)
        {
            

            cout << "[2] View Individual Teacher File\n"
                 << endl;
            GetName();
            fstream IndivFile;
            IndivFile.open(FileName);
            {
                if (IndivFile.is_open())
                {
                    IndivFile.close();
                    cout << "Individual File on " << FileName << endl
                         << endl;
                    ViewFile(FileName);
                    MoveOnConfirm();
                }
                else
                {
                    cout << "Individual File on [" << FileName << "] Not Found!" << endl
                         << endl;
                    MoveOnConfirm();
                }
            }
        }
    }
    void DeleteTeacher()
    {
        cout << "Doing #3 process - Delete Teacher File\n\n\n";
        cout << "[3] Delete Teacher File\n"
             << endl;
        string FullName, FirstName, LastName, MiddleInitial;
        cout << "[Teacher's Full Name:]" << endl
             << "Input Last Name: ";
        cin.ignore();
        getline(cin, LastName);
        cout << "Input Given Name: ";
        getline(cin, FirstName);
        cout << "Input Middle Initial (press [enter] if none): ";
        getline(cin, MiddleInitial);
        FullName = LastName + ", " + FirstName + " " + MiddleInitial;
        Name = FullName;
        FileName = LastName + "_" + FirstName + ".txt";
        fstream IndivFile;
        IndivFile.open(FileName);
        {
            if (IndivFile.is_open())
            {
                IndivFile.close();
                cout << "Individual File on " << FileName << endl
                     << endl;
                ViewFile(FileName);
                MoveOnConfirm();
            }
            else
            {
                cout << "Individual File on [" << FileName << "] Not Found!" << endl
                     << endl;
                MoveOnConfirm();
            }
        }
        cout << "\nAre you sure you want to delete " << FileName << "'s file [y/n]?: ";
        string confirm;
        cin >> confirm;
        while (confirm != "y" && confirm != "n" && confirm != "Y" && confirm != "N")
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "!!Bad data!!";
            cout << "Enter [y/n] only: ";
            cin >> confirm;
        }
        if (confirm == "y" || confirm == "Y")
        {

            cout << "Doing #3 process - Delete Teacher File\n\n\n";
            // delete indiv file
            remove(FileName.c_str());
            fstream Indiv;
            Indiv.open(FileName.c_str());
            if (Indiv.is_open())
            {
                cout << "!! Error !! Personal File Failed to Delete..." << endl;
                cout << "Back to main menu..." << endl
                     << endl;
                MoveOnConfirm();
                return;
                Indiv.close();
            }
            else
            {
                cout << "Personal File Succesfully Deleted..." << endl
                     << endl;
            }
            // delete line from teacher file
            string TeacherName = LastName + ", " + FirstName;
            fstream temp;
            fstream Teach;
            temp.open("TempTeacherList.txt", ios ::out);
            Teach.open("Teacher List.txt", ios::in);
            if (temp.is_open() || Teach.is_open())
            {
                string line;
                while (getline(Teach, line))
                {
                    if (line.find(TeacherName) == string::npos)
                    {
                        temp << line << "\n";
                    }
                }

                temp.close();
                Teach.close();

                remove("Teacher List.txt");
                rename("TempTeacherList.txt", "Teacher List.txt");
                cout << "\nTeacher deleted successfully in All teacher file...\n\n";
                MoveOnConfirm();
                return;
            }
            else
            {
                cout << "!! Error unable to open files !!" << endl;
                cout << "\n[File Not Found] \nBack to main menu...\n"
                     << endl;
                MoveOnConfirm();
                return;
            }
            return;
        }
        else
        {
            cout << "\nDeletion Terminated... \n\nBack to main menu...\n"
                 << endl;
            MoveOnConfirm();
            return;
        }
    }

private:
    string Subject;
};
void AskChoice(int &choice)
{
    cout << "Welcome to [School]'s Teacher Database..." << endl
         << "What would you like to do?" << endl
         << endl
         << "[1] Input a teacher" << endl
         << "[2] View teacher database" << endl
         << "[3] Delete a teacher" << endl
         << "[4] Exit" << endl
         << endl
         << "[Please enter the number of your desired choice]: ";
    inputVal(choice, 4, 1, "Please enter a number between [1-4]: ");
    return;
}
void TeacherMenu(bool&MenuResetButton)
{
    int choice = 0;
    string N, A, S, EN;
    int CN;
    Teacher A1(N, A, CN, EN, S);
    while (choice != 4)
    {
        AskChoice(choice);
        // Execute number choice
        if (choice == 1)
        {

            A1.GetInfo();
        }
        else if (choice == 2)
        {

            A1.ViewTeacher();
        }
        else if (choice == 3)
        {

            A1.DeleteTeacher();
        }
    }
    cout << endl
         << "Exiting Teacher Menu" << endl;
    MenuResetButton = true;
    return;
}

//declaring functions so that the classes can use them
void incompleteDetails(bool&resetbutton,string classNameTXT[20],int enlistedClasses);
void inputval(string&yn);
void displayClass(string classNameTXT[20],int enlistedClasses);
void fileScan(bool&MainResetButton,string(&classNames)[20],string(&classNameTXT)[20],string(&studentClassList)[5][100],
int maxNumOfClasses,int&enlistedClasses);

class ClassContents //parent class 
{
    protected: //initial details 
        string subject;
        string section;
        string dayslot;
        string timeslot;
    public:
        //constructor
        ClassContents(){};
        ClassContents(string sbj, string s, string ds, string ts)
        {
            subject=sbj;
            section=s;
            dayslot=ds;
            timeslot=ts;
        }

        // displays subjects to be chosen
        void displaySubjects(string subjects[10], const int numberofsubjects)
        {
            cout << "----------------------------------------------------------------" << endl;
            cout << "Here is the list of available subjects: " << endl
                 << "" << endl;
            for (int i = 0; i < numberofsubjects; i++)
            {
                cout << i + 1 << ". " << subjects[i] << endl;
            }
            return;
        }

        // prompts user to choose a subject
        void ChooseSubject(string &Subject, string subjects[10])
        {
            string yn;
            int chosenSubject;
            do
            {
                cout << "----------------------------------------------------------------" << endl;
                cout << "Please enter the number of your chosen subject from the list: ";
                cin >> chosenSubject;
                // makes sure user only inputs number from 1-10
                while (cin.fail() == true || cin.peek() != '\n' || (chosenSubject > 10 || chosenSubject < 1))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a number from 1-10: ";
                    cin >> chosenSubject;
                }
                cout << "You have chosen: " << subjects[chosenSubject - 1];
                cout << "\nIs this correct? Y/N: "; // verification
                cin >> yn;
                inputval(yn); // makes sure user only inputs y or n
            } while (yn == "n" || yn == "N");
            Subject = subjects[chosenSubject - 1];
            subject = Subject;
            // exits if user enters "Y"
            return;
        }

        // displays sections to be chosen
        void displaySections(string Subject,string sections[2], const int numberofsections)
        {
            cout << "----------------------------------------------------------------" << endl;
            cout << "Here's the list of sections for your " << Subject << " class: " << endl
                 << "" << endl;
            for (int i = 0; i < numberofsections; i++)
            {
                cout << i + 1 << ". " << sections[i] << endl;
            }
            return;
        }

        // prompts user to choose a section
        void ChooseSection(bool &resetbutton, string &Section, string Subject, string sections[2])
        {
            int chosenSection;
            string yn;
            do
            {
                cout << "----------------------------------------------------------------" << endl;
                cout << "Please enter the number of your chosen section from the list: ";
                cin >> chosenSection;
                // makes sure user only inputs 1 or 2
                while (cin.fail() == true || cin.peek() != '\n' || (chosenSection > 2 || chosenSection < 1))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a number from 1-2: ";
                    cin >> chosenSection;
                }
                cout << "You have chosen: " << sections[chosenSection - 1];
                cout << "\nIs this correct? Y/N: ";
                cin >> yn;
                inputval(yn);
            } while (yn == "n" || yn == "N"); // loops until user enters "Y"
            Section = sections[chosenSection - 1];
            section = Section;
            // exits once user enters "Y"

            // checking if class is enlisted already
            fstream checkClassList("Class List.txt", ios::in);
            bool classEnlistedAlready = false;
            string classNamesCheck = Subject + " " + Section;
            if (checkClassList.is_open())
            {
                string line;
                while (getline(checkClassList, line))
                {
                    if (line == classNamesCheck) // if class is found in list
                    {
                        classEnlistedAlready = true;
                        break;
                    }
                }
                checkClassList.close();
            }
            if (classEnlistedAlready == true)
            {
                cout << "\nClass is already enlisted!" << endl;
                resetbutton = true; // return function and back to main menu
                return;
            }
            return; // if class is not enlisted, continue
        }

        // displays days to be chosen
        void displayDays(string Subject,string dayslots[8], const int numberofdays)
        {
            cout << "----------------------------------------------------------------" << endl;
            cout << "Here's the list of day slots for your " << Subject << " class: " << endl
                 << "" << endl;
            for (int i = 0; i < numberofdays; i++)
            {
                cout << i + 1 << ". " << dayslots[i] << endl;
            }
            return;
        }

        // prompts user to choose day slot
        void ChooseDay(int &chosenDaySlot, string &DaySlot, string dayslots[2])
        {
            string yn;
            do
            {
                cout << "----------------------------------------------------------------" << endl;
                cout << "Please enter the number of your chosen day slot from the list: ";
                cin >> chosenDaySlot;
                // makes sure user only inputs a number from 1-8
                while (cin.fail() == true || cin.peek() != '\n' || (chosenDaySlot > 8 || chosenDaySlot < 1))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please enter a number from 1-8: ";
                    cin >> chosenDaySlot;
                }
                cout << "You have chosen: " << dayslots[chosenDaySlot - 1];
                cout << "\nIs this correct? Y/N: ";
                cin >> yn;
                inputval(yn);
            } while (yn == "n" || yn == "N");
            DaySlot = dayslots[chosenDaySlot - 1];
            dayslot = DaySlot;
            return;
        }

        // if user chose 1 day per week
        void displayTimeSlots(int chosenDaySlot, string Subject, string timeslots[2][6])
        {
            cout << "----------------------------------------------------------------" << endl;
            cout << "Here's the list of time slots for your " << Subject << " class: " << endl
                 << "" << endl;
            if (chosenDaySlot == 1 || chosenDaySlot == 2) // twice a week schedule MTh, TF
            {
                for (int i = 0; i < 6; i++)
                {
                    cout << i + 1 << ". " << timeslots[0][i] << endl;
                }
                return;
            }
            else // once a week schedule M, T, W, Th, F, S
            {
                for (int i = 0; i < 3; i++)
                {
                    cout << i + 1 << ". " << timeslots[1][i] << endl;
                }
                return;
            }
        }

        // prompt user to choose time slot
        void ChooseTime(int chosenDaySlot, string &TimeSlot, string timeslots[2][6])
        {
            string yn;
            int onceAweek = 1;
            int chosenTimeSlot;
            do
            {
                cout << "----------------------------------------------------------------" << endl;
                cout << "Please enter the number of your chosen time slot from the list: ";
                cin >> chosenTimeSlot;
                if (chosenDaySlot == 1 || chosenDaySlot == 2) // twice a week schedule MTh, TF
                {
                    // makes sure user only inputs a number from 1-6
                    while (cin.fail() == true || cin.peek() != '\n' || (chosenTimeSlot > 6 || chosenTimeSlot < 1))
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Please enter a number from 1-6: ";
                        cin >> chosenTimeSlot;
                    }
                    cout << "You have chosen: " << timeslots[0][chosenTimeSlot - 1];
                    cout << "\nIs this correct? Y/N: ";
                    cin >> yn;
                    inputval(yn);
                    onceAweek = 0; // twice a week schedule
                }
                else // once a week schedule M, T, W, Th, F, S
                {
                    // makes sure user only inputs a number from 1-3
                    while (cin.fail() == true || cin.peek() != '\n' || (chosenTimeSlot > 3 || chosenTimeSlot < 1))
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Please enter a number from 1-3: ";
                        cin >> chosenTimeSlot;
                    }
                    cout << "You have chosen: " << timeslots[1][chosenTimeSlot - 1];
                    cout << "\nIs this correct? Y/N: ";
                    cin >> yn;
                    inputval(yn);
                }
            } while (yn == "n" || yn == "N");
            TimeSlot = timeslots[onceAweek][chosenTimeSlot - 1];
            timeslot = TimeSlot;
            return;
        }

        //creating new class file with initial details
        void createNewClassFile(string classNames[20],string(&classNameTXT)[20],
        const int maxNumOfClasses,int&enlistedClasses)
        {
            enlistedClasses=0;
            for (int i=0; i<maxNumOfClasses; i++)
            {
                if (!classNames[i].empty()) //checking how many elements in array are not empty
                {
                    enlistedClasses++;
                }
            }
            classNameTXT[enlistedClasses]=subject+"_"+section+".txt";
            fstream newClass(classNameTXT[enlistedClasses], ios::out);
            if (newClass.is_open())
            {
                //printing initial class details into file
                newClass <<"Subject: "<<subject<<endl;
                newClass <<"Days: "<<dayslot<<endl;
                newClass <<"Time: "<<timeslot<<endl;
                newClass <<"Section name: "<<section<<endl;
                newClass.close();
            }
            fstream classFiles("Class Files List.txt",ios::app);//append new class in Class List Files.txt
            if (classFiles.is_open())
            {
                classFiles <<classNameTXT[enlistedClasses]<<endl;
                classFiles.close();
            }
            return;
        }
};  

class TeacherClass:public ClassContents //child class for teacher
{
    private:
        string teacher;
    public:
        //constructor
        TeacherClass(string sbj, string s, string ds, string ts):ClassContents(sbj,s,ds,ts){}
        //constructor
        void setTeacher(string t)
        {
            teacher=t;
        }

        // prompts user to assign teacher
        void assigningTeacher(bool &resetbutton, bool &teacherRegistered, bool &subjectNotListed,
                              string Subject, string &teacherFullNameA)
        {
            string yn, teacherLastName, teacherGivenName, teacherMiddleInitial, teacherFullNameB, teacherLastGivenName,
                employeeNumber, teacherDetails;
            do
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nPlease enter the teacher's employee number." << endl;
                cout << "Employee Number: 01-";
                getline(cin, employeeNumber);
                cout << "The employee number is: 01-" << employeeNumber << endl;
                cout << "Is this correct? Y/N: ";
                cin >> yn;
                inputval(yn);
            } while (yn == "n" || yn == "N");
            do
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter the teacher's name: " << endl;
                cout << "Last name: ";
                getline(cin, teacherLastName);
                cout << "Given name: ";
                getline(cin, teacherGivenName);
                cout << "Middle Initial: ";
                getline(cin, teacherMiddleInitial);
                teacherFullNameA = teacherGivenName + " " + teacherMiddleInitial + " " + teacherLastName;
                cout << "The teacher's name is: " << teacherFullNameA << endl;
                cout << "Is this correct? Y/N: ";
                cin >> yn;
                inputval(yn);
            } while (yn == "n" || yn == "N");

            // checking if teacher is registered in Teacher List.txt
            teacherFullNameB = teacherLastName + ", " + teacherGivenName + " " + teacherMiddleInitial;
            teacherDetails = "01-" + employeeNumber + " " + teacherFullNameB;
            fstream checkTeacherList("Teacher List.txt", ios::in);
            teacherRegistered = false;
            if (checkTeacherList.is_open())
            {
                string line;
                while (getline(checkTeacherList, line))
                {
                    if (line == teacherDetails)
                    {
                        teacherRegistered = true;
                    }
                }
                checkTeacherList.close();
            }

            // checking if teacher has subject listed in file
            if (teacherRegistered)
            {
                subjectNotListed = false;
                teacherLastGivenName = teacherLastName + "_" + teacherGivenName + ".txt";
                fstream checkTeacherFile(teacherLastGivenName, ios::in);
                if (checkTeacherFile.is_open())
                {
                    for (int i = 1; i < 5; i++)
                    {
                        string dummy;
                        getline(checkTeacherFile, dummy);
                    }
                    // starting at the fifth line
                    string checkSubjects;
                    if (getline(checkTeacherFile, checkSubjects))
                    {
                        // .find will return npos if subject is not found
                        if (checkSubjects.find(Subject) == string::npos)
                        {
                            cout << "\nSubject is not listed in teacher's information." << endl;
                            subjectNotListed = true;
                            resetbutton = true;
                        }
                    }
                    checkTeacherFile.close();
                }
            }

            // teacher is not registered
            else
            {
                cout << "\nTeacher not found in database! Please check your spelling or make sure that the teacher is registered." << endl;
                resetbutton = true;
                return;
            }
        }
        //appending teacher to class file
        void appendteacher(bool subjectNotListed,bool teacherRegistered,string classNameTXT[20],int enlistedClasses)
        {
            //teacher is registered
            if (!subjectNotListed&&teacherRegistered)
            {
                fstream appendTeacher(classNameTXT[enlistedClasses], ios::app); //appending teacher to class file
                if (appendTeacher.is_open())
                {
                    appendTeacher <<"Teacher: "<<teacher<<endl;
                    cout <<"\nTeacher successfully enlisted."<<endl;
                    appendTeacher.close();
                }
                return;
            }  
        }
};

class Student:public ClassContents //child class for students
{
    private:
        string student;
    public:
        //constructor
        Student(string sbj,string s,string ds, string ts):ClassContents(sbj,s,ds,ts){}
        //constructor
        void setStudent(string s)
        {
            student=s;
        }

        // prompts user to enlist student
        void enlistStudent(bool &resetbutton, bool &studentRegistered, bool &studentEnlistedAlready, bool &conflictingSchedule,
                           string Subject, string DaySlot, string TimeSlot, string &studentDetails, const int maxNumOfStudents,
                           string studentClassList[5][100])
        {
            string yn, studentLastName, studentGivenName, studentMiddleInitial, studentFullName, studentNumber;
            do
            {
                cout << "\nPlease enter the student number." << endl;
                cout << "Student Number: 23-";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, studentNumber);
                cout << "The student number is: 23-" << studentNumber << endl;
                cout << "Is this correct? Y/N: ";
                cin >> yn;
                inputval(yn);
            } while (yn == "n" || yn == "N");

            do
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nPlease enter the student's name: " << endl;
                cout << "Last name: ";
                getline(cin, studentLastName);
                cout << "Given name: ";
                getline(cin, studentGivenName);
                cout << "Middle Initial: ";
                getline(cin, studentMiddleInitial);
                studentFullName = studentLastName + ", " + studentGivenName + " " + studentMiddleInitial;
                cout << "The student's name is: " << studentFullName << endl;
                cout << "Is this correct? Y/N: ";
                cin >> yn;
                inputval(yn);
            } while (yn == "n" || yn == "N");

            // checking if student is registered in Student List.txt
            studentDetails = "23-" + studentNumber + " " + studentFullName;
            fstream checkStudentList("Student List.txt", ios::in);
            studentRegistered = false;
            studentEnlistedAlready = false;
            conflictingSchedule = false;
            if (checkStudentList.is_open())
            {
                string line;
                while (getline(checkStudentList, line))
                {
                    if (line == studentDetails)
                    {
                        studentRegistered = true;
                    }
                }
                checkStudentList.close();
            }

            if (studentRegistered == true)
            {
                cout << "Student found in database." << endl;
                // checking array if student is enlisted in subject with same or different section
                for (int i = 0; i < maxNumOfStudents; i++)
                {
                    if (studentClassList[0][i] == studentDetails && studentClassList[1][i] == Subject)
                    {
                        cout << "\nStudent is already enlisted in this subject!";
                        studentEnlistedAlready = true;
                        break;
                    }
                }
                if (!studentEnlistedAlready)
                {
                    // checking for conflicting schedule
                    for (int i = 0; i < maxNumOfStudents; i++)
                    {
                        if (studentClassList[0][i] == studentDetails && studentClassList[3][i] == DaySlot && studentClassList[4][i] == TimeSlot)
                        {
                            cout << "\nConflicting schedule! Student is already in a class with the same day and time.";
                            conflictingSchedule = true;
                            break;
                        }
                    }
                }
            }
            if (studentRegistered == false)
            {
                cout << "\nStudent not found in database! Please check your spelling or make sure that the student is registered." << endl;
            }
        }

        //appending students to class file
        void appendstudent(bool&resetbutton,bool&enlistagain,bool studentRegistered,bool studentEnlistedAlready,
        bool conflictingSchedule,string Subject,string Section,string(&classNames)[20],string(&classNameTXT)[20],
        string(&studentClassList)[5][100],const int maxNumOfClasses,int&enlistedClasses)
        {
            bool placeholder;
            //updating arrays
            fileScan(placeholder,classNames,classNameTXT,studentClassList,maxNumOfClasses,enlistedClasses); 
            int linecount=0;
            int studentcount=0;
            //checking if there are students inside the class file already
            fstream checkappendStudent(classNameTXT[enlistedClasses], ios::in); 
            if (checkappendStudent.is_open())
            {
                string line;
                while (getline(checkappendStudent,line))
                {
                    linecount++; //checking how many lines in class file
                }
                studentcount=linecount-5;
                checkappendStudent.close();
            }
            else cout <<"file not open"<<endl;
    
            if (studentRegistered&&!studentEnlistedAlready&&!conflictingSchedule)
            {
                //appending student to class
                fstream appendstudent(classNameTXT[enlistedClasses], ios::app); 
                appendstudent.close();
                appendstudent.open(classNameTXT[enlistedClasses], ios::app);
                if (appendstudent.is_open())
                {
                    if (linecount<6) //no students enlisted yet
                    {
                        appendstudent <<"Students: "<<endl;
                        appendstudent <<"1. "<<student<<endl;
                        cout <<"\nStudent successfully added."<<endl;
                        studentcount++;
                    }
                    else if (linecount>6) //there are already enlisted students
                    {
                        studentcount=linecount-6;
                        appendstudent <<studentcount+1<<". "<<student<<endl;
                        cout <<"\nStudent successfully added."<<endl;
                    }
                    appendstudent.close();
                }
                else cout <<"FILE NOT OPEN"<<endl;

                //listing student and class in separate file
                fstream appendingStudent("Student-Class List.txt",ios::app);
                if (appendingStudent.is_open())
                {
                    appendingStudent <<student<<endl;
                    appendingStudent <<subject<<endl;
                    appendingStudent <<section<<endl;
                    appendingStudent <<dayslot<<endl;
                    appendingStudent <<timeslot<<endl;
                    appendingStudent.close();
                }
                //updating arrays after appending
                fileScan(placeholder,classNames,classNameTXT,studentClassList,maxNumOfClasses,enlistedClasses); 
            }

            cout <<"\nWould you like to enlist another student to the class? Y/N: ";
            string yn;
            cin >>yn;
            inputval(yn);
            //no more enlisting students if user enters "N"
            if (yn=="n"||yn=="N")
            {
                //no enlisted students
                if (studentcount==0) 
                {
                    cout <<"\nClass details INCOMPLETE. Deleting file..."<<endl<<""<<endl;
                    incompleteDetails(resetbutton,classNameTXT,enlistedClasses); //delete file
                    return;
                }
                //atleast 1 enlisted student
                fstream appendClassList("Class List.txt",ios::app); 
                //checking number of enlisted classes in class list
                enlistedClasses=0;
                for (int i=0; i<maxNumOfClasses; i++)
                {
                    if (!classNames[i].empty())
                    {
                        enlistedClasses++;
                    }
                }
                //adding class to Class List.txt
                classNames[enlistedClasses]=Subject+" "+Section;
                if (appendClassList.is_open())
                {
                    appendClassList <<classNames[enlistedClasses]<<endl; //append class in class list
                    appendClassList.close();
                }
                cout <<"\nClass has successfully been enlisted!"<<endl;
                displayClass(classNameTXT,enlistedClasses);
                resetbutton=true;
                return; //back to main menu after appending class to class list
            }
            //enlisting another student if user enters "Y"
            else{
                enlistagain=true;
                return;
            }
        }
};

//updating arrays by assigning each line of the file to an element
void fileScan(bool&MainResetButton,
string(&classNames)[20],string(&classNameTXT)[20],string(&studentClassList)[5][100],
int maxNumOfClasses,int&enlistedClasses) 
{
    fstream readingClassList("Class List.txt",ios::in);
    if (readingClassList.is_open())
    {
        string line;
        int i=0;
        do
        {
            getline(readingClassList,line);
            {
                classNames[i]=line; //puts class names in an array
                i++;
            }
        }while(!readingClassList.eof());
        readingClassList.close();
    }

    fstream readingClassListFiles("Class Files List.txt",ios::in);
    if (readingClassListFiles.is_open())
    {
        string line;
        int i=0;
        do
        {
            getline(readingClassListFiles,line);
            {
                classNameTXT[i]=line; //puts class file names in an array
                i++;
            }
        }while(!readingClassListFiles.eof());
        readingClassListFiles.close();
    }

    fstream readingStudentClassList("Student-Class List.txt",ios::in);
    if (readingStudentClassList.is_open())
    {
        string line;
        int i=0;
        do 
        {
            getline(readingStudentClassList,line);
            {
                studentClassList[0][i]=line; //student
            }
            getline(readingStudentClassList,line);
            {
                studentClassList[1][i]=line; //subject
            }
            getline(readingStudentClassList,line);
            {
                studentClassList[2][i]=line; //section
            }
            getline(readingStudentClassList,line);
            {
                studentClassList[3][i]=line; //day
            }
            getline(readingStudentClassList,line);
            {
                studentClassList[4][i]=line; //time
            }
            i++;
        }while(!readingStudentClassList.eof());
        readingStudentClassList.close();
    }
    enlistedClasses=0;
    for (int i=0; i<maxNumOfClasses; i++)
    {
        if (!classNames[i].empty()) //checks how many elements in array is not empty
        {
            enlistedClasses++;
        }
    }
    if (enlistedClasses<1) //no classes enlisted yet
    {
        MainResetButton=true;
        return;
    }
}

void inputval(string&yn) //makes sure user only inputs y or n
{
    while(cin.fail()==true||cin.peek()!='\n'||yn!="Y"&&yn!="N"&&yn!="y"&&yn!="n")
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout <<"Please type Y if Yes and N if No: ";
        cin >>yn;
    }
}

void inputvalpath(int&path) //makes sure user only inputs 1 2 or 3
{
    while(cin.fail()==true||cin.peek()!='\n'||(path>3||path<1))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout <<"Please only enter the number of your choice: ";
        cin >>path;
    }
}

// prints out contents of a class file
void displayClass(string classNameTXT[20],int enlistedClasses) 
{
    cout <<"\nHere are the details of the class: "<<endl;
    cout <<"----------------------------------------------------------------"<<endl;
    fstream showClass(classNameTXT[enlistedClasses], ios::in);
    if (showClass.is_open())
    {
        string line;
        while (getline(showClass,line))
        {
            cout <<line<<endl;
        }
        showClass.close();
    }
    cout <<"----------------------------------------------------------------"<<endl;
    return;
}

//if no teacher or no student enlisted
void incompleteDetails(bool&resetbutton,string classNameTXT[20],int enlistedClasses) 
{
    remove(classNameTXT[enlistedClasses].c_str()); //deletes file from directory
    fstream deleteFile("Class Files List.txt",ios::in); //removes file name from Class Files List.txt
    int i=0;
    string temp[20];
    if (deleteFile.is_open())
    {
        string line;
        while (getline(deleteFile,line))//places class files in temp array
        {
            temp[i]=line;
            i++;
        }
        deleteFile.close();
    }
    deleteFile.open("Class Files List.txt",ios::out|ios::trunc);
    if (deleteFile.is_open())
    {
        //trunc automatically clears file

        if (i==1) //if only 1 class in list
        {
            deleteFile.close();
            resetbutton=true;
            return;
        }
        for (int j=0; j<i-1; j++) //if more than 1 class in list
        {
            deleteFile <<temp[j]<<endl; //gets lines, then leaves out last line
        }
        deleteFile.close(); 
    }
        
    resetbutton=true;
    return; //back to main menu after deleting class file
}




//prompts user to choose which class to view
void ChooseClassView(int chosenClassView,string classNames[20],string classNameTXT[20],
const int maxNumOfClasses,int&enlistedClasses) 
{
    enlistedClasses=0;
    for (int i=0; i<maxNumOfClasses; i++)
    {
        if (!classNames[i].empty())
        {
            enlistedClasses++; //updates how many enlisted classes
        }
    }
    string yn;
    do 
    {
        cout <<"----------------------------------------------------------------"<<endl;
        cout <<"Please enter the number of the class you wish to view: ";
        cin >>chosenClassView;
        //makes sure user only enters valid number
        while(cin.fail()==true||cin.peek()!='\n'||(chosenClassView>enlistedClasses||chosenClassView<1))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Please enter a number from 1-"<<enlistedClasses<<": ";
            cin>>chosenClassView;
        }
        cout <<"You have chosen: "<<classNames[chosenClassView-1];
        cout <<"\nIs this correct? Y/N: ";
        cin>>yn;
        inputval(yn);
    }while (yn=="n"||yn=="N");

    //displaying class details
    cout <<"\nHere are the details of the class: "<<endl;
    cout <<"----------------------------------------------------------------"<<endl;
    fstream viewClass (classNameTXT[chosenClassView-1],ios::in);
    if (viewClass.is_open())
    {
        string line;
        while (getline(viewClass,line))
        {
            cout <<line<<endl; //prints class details line by line
        }
        viewClass.close();
    }
    cout <<"----------------------------------------------------------------"<<endl;
    return;
}

//updates Class Files List.txt, Class List.txt, and Student-Class List.txt
void updateTextFiles(string classNames[20],string classNameTXT[20],string studentClassList[5][100],
const int maxNumOfStudents,int enlistedClasses) 
{
    ofstream checkClassList("Class List.txt");
    ofstream classFilesList("Class Files List.txt");
    ofstream studentclassList("Student-Class List.txt");

    //pasting arrays onto txt files
    for (int i=0; i<enlistedClasses; i++)
    {
        checkClassList <<classNames[i]<<endl; 
        classFilesList <<classNameTXT[i]<<endl;
    }

    int studentsubjectsection=0;
    for (int i=0; i<maxNumOfStudents; i++)
    {
        if (!studentClassList[0][i].empty())
        {
            studentsubjectsection++;
        }
    }

    for (int i=0; i<studentsubjectsection; i++)
    {
        studentclassList <<studentClassList[0][i]<<endl;
        studentclassList <<studentClassList[1][i]<<endl;
        studentclassList <<studentClassList[2][i]<<endl;
        studentclassList <<studentClassList[3][i]<<endl;
        studentclassList <<studentClassList[4][i]<<endl;
    }
    checkClassList.close();
    classFilesList.close();
    studentclassList.close();
    return;
}

//prompts user to choose a class to delete
void ChooseClassDelete(int chosenClassDelete,
string(&classNames)[20],string(&classNameTXT)[20],string(&studentClassList)[5][100],
const int maxNumOfClasses,const int maxNumOfStudents,int&enlistedClasses) 
{
    enlistedClasses=0;
    for (int i=0; i<maxNumOfClasses; i++)
    {
        if (!classNames[i].empty())
        {
            enlistedClasses++; //updates number of enlisted classes
        }
    }
    string yn;
    do 
    {
        cout <<"----------------------------------------------------------------"<<endl;
        cout <<"Please enter the number of the class you wish to delete: ";
        cin >>chosenClassDelete;
        //makes sure user enters valid number
        while(cin.fail()==true||cin.peek()!='\n'||(chosenClassDelete>enlistedClasses||chosenClassDelete<1))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Please enter a number from 1-"<<enlistedClasses<<": ";
            cin>>chosenClassDelete;
        }
        cout <<"You have chosen: "<<classNames[chosenClassDelete-1];
        cout <<"\nIs this correct? Y/N: ";
        cin>>yn;
        inputval(yn);
    }while (yn=="n"||yn=="N");

    //deleting
    cout <<"\nDeleting file..."<<endl;

    //updating studentClassList array
    string DeleteClass=classNames[chosenClassDelete-1];
    istringstream iss(DeleteClass);
    string deleteSubject,deleteSubjectA,deleteSubjectB,deleteSection;
    int wordCount=0;
    while (iss >>DeleteClass)
    {
        wordCount++; //checking if subject has 1 or 2 words
    }
    
    iss.clear(); 
    iss.seekg(0);
    if (wordCount==2) //subject is 1 word
    {
        iss >>deleteSubject; //first word is subject
        iss >>deleteSection; //second word is section
    }
    if (wordCount==3) //subject is 2 words
    {
        iss >>deleteSubjectA; //first and second word is subject
        iss >>deleteSubjectB;
        iss >>deleteSection; //third word is section
        deleteSubject=deleteSubjectA +" "+ deleteSubjectB; //combine first and second word
    }
    int studentsInClass=0;    

    //counting how many students enlisted in class
    for (int i=0; i<maxNumOfStudents; i++)
    {
        if(studentClassList[1][i]==deleteSubject&&studentClassList[2][i]==deleteSection)
        {    
            studentsInClass++;
        }
    }

    //updating the array
    for (int i=0; i<studentsInClass; i++)
    {
        for (int j=0; j<maxNumOfStudents; j++)
        {
            if(studentClassList[1][j]==deleteSubject&&studentClassList[2][j]==deleteSection)
            {     
                //deleting the element by replacing it by moving all elements up          
                for (int k=j; k<maxNumOfStudents-1; k++)
                {
                    studentClassList[0][k]=studentClassList[0][k+1];
                    studentClassList[1][k]=studentClassList[1][k+1];
                    studentClassList[2][k]=studentClassList[2][k+1];
                    studentClassList[3][k]=studentClassList[3][k+1];
                    studentClassList[4][k]=studentClassList[4][k+1];
                }
                studentClassList[0][maxNumOfStudents-1]="";
                studentClassList[1][maxNumOfStudents-1]="";
                studentClassList[2][maxNumOfStudents-1]="";
                studentClassList[3][maxNumOfStudents-1]="";
                studentClassList[4][maxNumOfStudents-1]="";
                //clearing last element of array
            }
        }
    }
    remove(classNameTXT[chosenClassDelete-1].c_str()); //delete class file from directory
    //updating the arrays
    for (int i=chosenClassDelete-1; i<enlistedClasses-1; i++) 
    {
        classNames[i]=classNames[i+1]; //moves up all elements of array
        classNameTXT[i]=classNameTXT[i+1]; 
    }
    classNames[enlistedClasses-1]=""; 
    classNameTXT[enlistedClasses-1]=""; //clears the last element

    enlistedClasses--;
    updateTextFiles(classNames,classNameTXT,studentClassList,maxNumOfStudents,enlistedClasses); 
    //update class list after updating arrays

    cout <<"Class successfully deleted!"<<endl;
    return;
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//PATH 1
void creatingNewClass(bool&MainResetButton,
string(&classNames)[20],string(&classNameTXT)[20],string(&studentClassList)[5][100],
const int maxNumOfClasses,const int maxNumOfStudents,int&enlistedClasses)
{
    //declaring important variables
    int chosenDaySlot;
    string Subject, Section, DaySlot, TimeSlot,teacherFullNameA,studentDetails;
    const int numberofsubjects=10;
    string subjects[numberofsubjects]={"Programming", "Drafting", "Data Analysis",
                                   "Circuits 1", "OOP", "Circuits 2", 
                                   "Electronics 1","Electronics 2", 
                                   "Logic Circuits", "Microprocessors"};
    const int numberofsections=2;
    string sections[numberofsections]={"A","B"};
    const int numberofdays=8;
    string dayslots[numberofdays]={"MTh", "TF", "M", "T", "W", "Th", "F", "S"};
    string timeslots[2][6]= //2D array for time slots
    {
        {"8:00-9:30", "9:30-11:00","11:00-12:30","12:30-2:00", "2:00-3:30", "3:30-5:00"},//1 and a half hour time slots
        {"8:00-11:00","11:00-2:00", "2:00-5:00"} //3 hour time slots
    };
    MainResetButton=false;
    ClassContents newclass(Subject, Section, DaySlot, TimeSlot);
    //display and choose subject
    newclass.displaySubjects(subjects,numberofsubjects);
    newclass.ChooseSubject(Subject,subjects);

    //display and choose section
    newclass.displaySections(Subject, sections, numberofsections);
    newclass.ChooseSection(MainResetButton, Section, Subject, sections);
    if (MainResetButton) //if class is aleady enlisted
    {
        return; //back to main menu
    }
    //display and choose day slot
    newclass.displayDays(Subject, dayslots, numberofdays);
    newclass.ChooseDay(chosenDaySlot, DaySlot, dayslots);

    //display and choose time slot
    newclass.displayTimeSlots(chosenDaySlot, Subject, timeslots);
    newclass.ChooseTime(chosenDaySlot, TimeSlot, timeslots);

    //create new class file and display contents of file
    newclass.createNewClassFile(classNames,classNameTXT,maxNumOfClasses,enlistedClasses);
    displayClass(classNameTXT,enlistedClasses);

    //adding teacher
    bool reset=false;
    string yn;
    do 
    {
        reset=false;
        cout <<"\nWould you like to assign a teacher to the class? Y/N: ";
        cin>>yn;
        inputval(yn);
        if (yn=="n"||yn=="N") //no teacher assigned
        {
            cout <<"\nClass details INCOMPLETE. Deleting file..."<<endl<<""<<endl;
            incompleteDetails(MainResetButton,classNameTXT,enlistedClasses); //delete file
            return;
        }
        else //assigning teacher
        {
            bool teacherRegistered,subjectNotListed;
            TeacherClass tchr(Subject,Section,DaySlot,TimeSlot);
            tchr.assigningTeacher(reset,teacherRegistered,subjectNotListed,Subject,teacherFullNameA); 
            //includes the process of checking if teacher is in database
            tchr.setTeacher(teacherFullNameA);
            tchr.appendteacher(subjectNotListed,teacherRegistered,classNameTXT,enlistedClasses);
        }
    }while(reset==true);
    // display updated version of class with teacher included
    displayClass(classNameTXT,enlistedClasses); 

    //adding students
    cout <<"\nWould you like to enlist a student to the class? Y/N: ";
    cin>>yn;
    inputval(yn);
    
    //no
    if (yn=="n"||yn=="N")
    {
        cout <<"\nClass details INCOMPLETE. Deleting file..."<<endl<<""<<endl;
        incompleteDetails(MainResetButton,classNameTXT,enlistedClasses); //delete file
        return;
    }

    //yes
    bool enlistagain,studentRegistered,studentEnlistedAlready=false,conflictingSchedule=false;
    do
    {
        enlistagain=false;
        bool resetbutton=false;
        //includes process of checking if student is in database 
        Student stdnt(Subject,Section,DaySlot,TimeSlot);
        stdnt.enlistStudent(resetbutton,studentRegistered,studentEnlistedAlready,conflictingSchedule,
        Subject,DaySlot,TimeSlot,studentDetails,maxNumOfStudents,studentClassList); 
        stdnt.setStudent(studentDetails);
        stdnt.appendstudent(resetbutton,enlistagain,studentRegistered,studentEnlistedAlready,conflictingSchedule,
        Subject,Section,classNames,classNameTXT,studentClassList,maxNumOfClasses,enlistedClasses);
        if (resetbutton==true) //if user is done enlisting students
        {
            MainResetButton=true;
            return; //back to main menu after enlisting students
        }
    }while (enlistagain==true); //if user is not done enlisting students
}



///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//PATH 2
void viewDeleteClasses(bool&MainResetButton,
string(&classNames)[20],string(&classNameTXT)[20],string(&studentClassList)[5][100],
const int maxNumofClasses,const int maxNumOfStudents,int&enlistedClasses)
{
    //declaring important variables
    int chosenClassView, chosenClassDelete;
    
    //if no classes are found in the class list after calling fileScan()
    if (MainResetButton==true)
    {
        cout <<"\nNo classes enlisted yet!"<<endl;
        return;
    }
    cout <<"----------------------------------------------------------------"<<endl;
    cout <<"Option 1: View details of a class"<<endl;
    cout <<"Option 2: Delete a class"<<endl;
    cout <<"Option 3: Return to menu of Class Registration System "<<endl;
    cout <<"\nPlease enter the number of your choice: ";
    int option;
    cin >>option;
    inputvalpath(option); //makes sure user only inputs 1 2 or 3

    switch(option)
    {
        case 1: //view details of a class
            cout <<"\nHere is the list of enlisted classes: "<<endl;
            cout <<"----------------------------------------------------------------"<<endl;
            {
                fstream displayClassList ("Class List.txt", ios::in);
                if (displayClassList.is_open())
                {
                    int i=1;
                    string line;
                    while (getline(displayClassList,line))
                    {
                        cout <<i<<". "<<line<<endl; //displays contents of class list
                        i++;
                    } 
                    displayClassList.close();
                }
            }
            //prompt user to choose class to view
            ChooseClassView(chosenClassView,classNames,classNameTXT,maxNumofClasses,enlistedClasses); 
            MainResetButton=true; //back to main menu after displaying class details
            return;

        case 2: //delete a class
            cout <<"\nHere is the list of enlisted classes: "<<endl;
            cout <<"----------------------------------------------------------------"<<endl;
            {
                fstream displayClassList ("Class List.txt", ios::in);
                if (displayClassList.is_open())
                {
                    int i=1;
                    string line;
                    while (getline(displayClassList,line))
                    {
                        cout <<i<<". "<<line<<endl; //displays contents of class list
                        i++;
                    } 
                    displayClassList.close();
                }
            }
            //prompt user to choose class to delete
            ChooseClassDelete(chosenClassDelete,classNames,classNameTXT,studentClassList,
            maxNumofClasses,maxNumOfStudents,enlistedClasses); 
            MainResetButton=true; //back to main menu after deleting class
            return;

        case 3: //return to main menu
            MainResetButton=true; 
            return;
    }   
}

void ClassRegistrationSystem(bool&MenuResetButton)
{
    const int maxNumOfClasses=20;
    const int maxNumOfStudents=100;
    const int StudentSubjectSectionDayslotTimeslot=5;
    string classNames[maxNumOfClasses];//array for names of each class
    string classNameTXT[maxNumOfClasses];//array for txt file names of each class
    //array for checking if student is enlisted in class with different section or if conflicting schedule
    string studentClassList[StudentSubjectSectionDayslotTimeslot][maxNumOfStudents];
    int enlistedClasses=0;
    bool MainResetButton;
    int chosenpath; //create new class or edit class
    do
    {
        MainResetButton=false;
        //displaying options
        cout <<"----------------------------------------------------------------"<<endl;
        cout <<"This is the menu for the Class Registration System. What do you wish to do?:"<<endl;
        cout <<"1 - Create a new class."<<endl;
        cout <<"2 - View/Delete existing classes."<<endl;
        cout <<"3 - Return to main menu."<<endl;
        cout <<"----------------------------------------------------------------"<<endl;
        cout <<"Please enter the number of your choice: ";
        cin >>chosenpath;
        inputvalpath(chosenpath);
        switch (chosenpath)//user wants to create a new class
        {
            case 1: //create a new class
                bool placeholder; //placeholder just to pass in function
                //update arrays
                fileScan(placeholder,classNames,classNameTXT,studentClassList,maxNumOfClasses,enlistedClasses); 
                creatingNewClass(MainResetButton,classNames,classNameTXT,studentClassList,
                maxNumOfClasses,maxNumOfStudents,enlistedClasses);
                //MainResetButton always returns true for path 1, loops function
                break;
            case 2: //view or delete classes      
                //update arrays
                fileScan(MainResetButton,classNames,classNameTXT,studentClassList,maxNumOfClasses,enlistedClasses); 
                viewDeleteClasses(MainResetButton,classNames,classNameTXT,studentClassList,
                maxNumOfClasses,maxNumOfStudents,enlistedClasses); 
                //MainResetButton always returns true for path 2, loops function
                break;
            case 3:
                //return to main menu if user inputs 3       
                cout <<"\nReturning to main menu..."<<endl;
                MenuResetButton=true;
                return;     
        }      
    }while (MainResetButton==true); //will always loop until user takes path 3
}

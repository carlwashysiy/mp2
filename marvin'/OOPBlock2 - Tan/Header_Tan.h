#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

void inputVal(int& Input, int UpperLim, int LowerLim, string Message){
while (!(cin >> Input) || Input>UpperLim || Input<LowerLim) {
        cin.clear();
        cin.ignore (1000, '\n');
        cout << "!!Bad data!!";
        cout << Message;
}return;}
void MoveOnConfirm (){
    cout << "Press any key then [enter] to continue: ";
    string confirm; cin >> confirm; system("cls");
}
class Parent {
public:
    Parent(string N, string A, int CN, string EN){
        Name = N;
        Address = A;
        ContactNumber = CN;
        EmployeeNumber = EN;
    }
    void GetName(){
            string FullName, FirstName, LastName, MiddleInitial;
            cout << "[Teacher's Full Name:]" << endl
                << "Input Last Name: ";
            cin.sync();
            getline(cin, LastName);
            cout << "Input Given Name: ";
            getline(cin, FirstName);
            cout << "Input Middle Initial (press [enter] if none): ";
            getline(cin, MiddleInitial);
            FullName = LastName + ", " + FirstName + " " + MiddleInitial;
            Name = FullName;
            FileName = LastName + "_" + FirstName + ".txt";
            system("cls");
    }
    void AssignNum (){
        int EmployeeNum = 1;
        EmployeeNumber = "01-00" + to_string(EmployeeNum);
        fstream Teach;
        string line;
        Teach.open("Teacher List.txt", ios:: in);
            if (Teach.is_open()) {
                    while (getline(Teach, line)) {
                    while (line.find(EmployeeNumber) != string::npos) {
                    EmployeeNum++;
                    EmployeeNumber = "01-00" + to_string(EmployeeNum);
                        }
                    }
                    Teach.close();
            }
    }
    void PrintInfo(){
    system("cls");
    cout << Name << endl << Address << endl << ContactNumber;
    }
    void ViewFile(string FileName){
        fstream File;
        File.open(FileName, ios :: in);{
        if (!File.is_open()){
            cout << "\n[File Not Found] \nBack to main menu...\n\n" << endl;
            MoveOnConfirm();
        }else{
            string line;
            while (getline (File,line)) {
            cout << line << '\n';
            } cout << endl;
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

class Teacher : public Parent {
public:
    Teacher(string N, string A, int CN, string EN, string S): Parent (N,A,CN,EN){
        Name = N;
        Address = A;
        ContactNumber = CN;
        EmployeeNumber = EN;
        Subject = S;

    }
    void GetSubject (){
        int choice = 1;
        string SubjectChoice [10][2] {
        {"[1] Programming", "Programming" },
        {"[2] Drafting", "Drafting"},
        {"[3] Data Analysis", "Data Analysis"},
        {"[4] Circuits 1", "Circuits 1"},
        {"[5] Circuits 2", "Circuits 2"},
        {"[6] OOP", "OOP"},
        {"[7] Electronics 1", "Electronics 1"},
        {"[8] Electronics 2","Electronics 2"},
        {"[9] Logic Circuits", "Logic Circuits"},
        {"[10] Microprocessors", "Microprocessors"}};
        string SubjectList[10];
        system("cls");
        cout << "[Teacher's Subjects:]" << endl;
        cout << "List of subjects:"<< endl << endl;
        for (int k = 0; k<10; k++){
            cout << SubjectChoice [k][0] << endl;
        }
        cout << "[0] End Subject Selection" << endl;

        cout << "\n!!please enter the number of the subject one by one!!" << endl
        << "!!enter [0] after subject selection!!" << endl;
        int i= 0;
        while (choice != 0){
            cout << "\n\nEnter number of choice: ";
            inputVal(choice, 10 , 0 , " Enter number between [0-10] only: ");
            string SubjChoice;
            cout << "You have chosen: ";
                int j = choice -1;
                cout << SubjectChoice[j-1][2];
                SubjChoice = SubjectChoice[j][1];

            SubjectList[i] = SubjChoice;
            i++;
        }

            cout << "[0] End Subject Selection\n\n"
            << "You have input [0] and thus have excited subject selection. " << endl;

        for (int j = 0; j<i-1; j++){
            Subject = Subject + ", " + SubjectList[j];
        }
    }
     void GetInfo (){
        //Get Name
        GetName();
        fstream IndivFile;
        IndivFile.open(FileName);{
        if (IndivFile.is_open()){
            cout << "!!error!! Teacher already in the database" << endl;
            IndivFile.close();
            cout << "\nBack to main menu...\n\nPress any key then [enter] to continue: ";
            string confirm;
            cin >> confirm;
            FileExist = true;
            system("cls");
            return;}}

        //Get Address
            string HouseNum, Street, SubdBldg, Brgy, City;
            cout << "[Teacher's Full Address:]" << endl
            << "Input House Number: ";
            cin.sync();
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
            system("cls");
        //Contact Number
            cout << "[Teacher's Mobile Number:]" << endl
            << "Input Contact Number: ";
            while (!(cin >> ContactNumber)) {
                cin.clear();
                cin.ignore (1000, '\n');
                cout << "!!Bad data!!";
                cout << " Enter number only" << endl;
                cout << "Input Mobile Number: ";
            }
        //Subject
        GetSubject();
        //Assign Number
        AssignNum();
        // Add to Files
        IndivFile.open(FileName, ios :: out);{
        if (!IndivFile.is_open()){
            cout << "error encountered in opening Indiv file" << endl;
        }else{
            IndivFile << Name << endl;
            IndivFile << Address << endl;
            IndivFile << "0" << ContactNumber << endl;
            IndivFile << "Employee# " << EmployeeNumber << endl;
            IndivFile << "Subjects: " << Subject << endl;
            IndivFile.close();
            }
        }
        fstream TeacherFile;
        TeacherFile.open("Teacher List.txt", ios :: app);{
            if (!TeacherFile.is_open()){
            cout << "error encountered in opening All teacher file" << endl;
        }else{
            TeacherFile << EmployeeNumber << " ";
            TeacherFile << Name << endl;
            TeacherFile.close();
        }
    }
    system("cls");
        cout << Name << endl;
        cout << Address << endl;
        cout << "0" << ContactNumber << endl;
        cout << "Employee# " << EmployeeNumber << endl;
        cout << "Subjects: " << Subject << endl << endl;
    MoveOnConfirm();
    }
    void ViewTeacher (){
    int choice;
    cout << "Doing #2 process - View teacher list\n" << endl << endl;
    cout << "[View Teacher Database]" << endl
    << "What would you like to do?"<< endl << endl
    << "[1] View Full Teacher list" << endl
    << "[2] View Individual Teacher file" << endl << endl
    << "[Please enter the number of your desired choice]: ";
    inputVal(choice, 2 , 1 ,  " Please enter a number between [1-2]: ");

    if (choice == 1){
        system("cls");
        cout << "[1] View Full Teacher list\n" << endl;
        cout << "Full Teacher Database: "<< endl << endl;
        ViewFile("Teacher List.txt");
        MoveOnConfirm();
            }
        else if (choice == 2){
        system("cls");

        cout << "[2] View Individual Teacher File\n" << endl;
        GetName();
        fstream IndivFile;
        IndivFile.open(FileName);{
        if (IndivFile.is_open()){
            IndivFile.close();
            cout << "Individual File on " << FileName << endl << endl;
            ViewFile(FileName);
            MoveOnConfirm();
        } else {
            cout << "Individual File on [" << FileName <<"] Not Found!" << endl << endl;
            MoveOnConfirm();
        }
    }
}
}
    void DeleteTeacher (){
    cout << "Doing #3 process - Delete Teacher File\n\n\n";
        cout << "[3] Delete Teacher File\n" << endl;
        string FullName, FirstName, LastName, MiddleInitial;
            cout << "[Teacher's Full Name:]" << endl
                << "Input Last Name: ";
            cin.sync();
            getline(cin, LastName);
            cout << "Input Given Name: ";
            getline(cin, FirstName);
            cout << "Input Middle Initial (press [enter] if none): ";
            getline(cin, MiddleInitial);
            FullName = LastName + ", " + FirstName + " " + MiddleInitial;
            Name = FullName;
            FileName = LastName + "_" + FirstName + ".txt";
            system("cls");
        fstream IndivFile;
        IndivFile.open(FileName);{
        if (IndivFile.is_open()){
            IndivFile.close();
            cout << "Individual File on " << FileName << endl << endl;
            ViewFile(FileName);
            MoveOnConfirm();
        } else {
            cout << "Individual File on [" << FileName <<"] Not Found!" << endl << endl;
            MoveOnConfirm();
        }
    }
        cout << "\nAre you sure you want to delete " << FileName <<"'s file [y/n]?: ";
        string confirm;
        cin >> confirm;
        while ( confirm != "y" && confirm != "n" && confirm != "Y" && confirm != "N") {
            cin.clear();
            cin.ignore (1000, '\n');
            cout << "!!Bad data!!";
            cout << "Enter [y/n] only: ";
            cin >> confirm;
        }
        if (confirm == "y" || confirm == "Y"){
            system ("cls");
            cout << "Doing #3 process - Delete Teacher File\n\n\n";
            // delete indiv file
            remove(FileName.c_str());
            fstream Indiv;
            Indiv.open(FileName.c_str());
            if (Indiv.is_open()){
                cout << "!! Error !! Personal File Failed to Delete..." << endl;
                cout << "Back to main menu..."<< endl << endl;
                MoveOnConfirm();
                return;
                Indiv.close();
            } else {
                cout << "Personal File Succesfully Deleted..." << endl << endl;
            }
            // delete line from teacher file
            string TeacherName = LastName + ", " + FirstName;
            fstream temp;
            fstream Teach;
            temp.open("TempTeacherList.txt", ios :: out);
            Teach.open("Teacher List.txt", ios:: in);
            if (temp.is_open() || Teach.is_open()) {
                    string line;
                    while (getline(Teach, line)) {
                    if (line.find(TeacherName) == string::npos) {
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
                } else {
                    cout << "!! Error unable to open files !!" << endl;
                    cout << "\n[File Not Found] \nBack to main menu...\n" << endl;
                    MoveOnConfirm();
                    return;
                }
            return;
        }
        else {
            cout << "\nDeletion Terminated... \n\nBack to main menu...\n" << endl;
            MoveOnConfirm();
            return;
    }
    }
private:
    string Subject;
};
void AskChoice (int& choice){
    cout << "Welcome to [School]'s Teacher Database..." << endl
    << "What would you like to do?"<< endl << endl
    << "[1] Input a teacher" << endl
    << "[2] View teacher database" << endl
    << "[3] Delete a teacher" << endl
    << "[4] Exit" << endl << endl
    << "[Please enter the number of your desired choice]: ";
    inputVal(choice, 4 , 1 , "Please enter a number between [1-4]: ");
    return;}
void TeacherMenu (){
    int choice = 0;
    string N, A, S, EN;
    int CN;
    Teacher A1 (N,A,CN,EN,S);
    while (choice != 4) {
    AskChoice (choice);
    //Execute number choice
    if (choice == 1){
        system("cls");
        A1.GetInfo();
        }
    else if (choice == 2){
        system("cls");
        A1.ViewTeacher();
        }
    else if (choice == 3){
        system("cls");
        A1.DeleteTeacher();

        }
    }
    cout << endl << "Exiting Teacher Menu" << endl;

}

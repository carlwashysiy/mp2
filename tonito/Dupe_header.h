#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <sstream> 
#include <ctype.h>

using namespace std;

string student_info [20][9];

int student_count = 0;
int *pntr = &student_count;

class Student_info {
    public:
        Student_info(string s, string gn, string mi, string hn, string sn, string sub, string b, string c, string n){
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
            fullname = surname + ", " + given_name + " " + middle_initial + '.'; 
        };

        void Create_File(){
            fstream indiv;
            indiv.open (filename, ios::out);
            if (indiv.is_open()) {
                indiv << fullname << endl;
                indiv << house_number << " " << street_name << " " << subdivision << " " << barangay << " " << city << endl;
                indiv << number << endl;
                indiv.close();
            }
            else cout << "Unable to open file.";
        };

        void Student_List(){
            fstream compile;
            compile.open ("Student List.txt", ios::app);
            if (compile.is_open()) {
                compile << fullname << endl;
                compile.close();
            }
            else cout << "Unable to open file.";
        };

        void Make_Student_Number(){
            ifstream myFile ("Student List.txt");
            if (myFile.is_open()) {
            while (! myFile.eof()) {
                getline(myFile,line);
                array[loop] = line;
                loop++;
            }
            myFile.close();
            }
            else cout << "Unable to open file.";

            string add_number;

            if (loop - 1 < 10){
                add_number = "0" + to_string(loop - 1);
            }

            else {
                add_number = to_string(loop - 1);
            } 

            student_number = "23-" + add_number + " ";
        
            fstream add_student_number;
            add_student_number.open (filename, ios::app);
            if (add_student_number.is_open()) {
                add_student_number << student_number;
                add_student_number.close();
            }
            else cout << "Unable to open file.";
        };

        void New_File(){
            fstream newfile;
            newfile.open ("Student List.txt", ios::out);
            if (newfile.is_open()) {
                if (loop > 2){
                    for (int i = 0; i < loop - 2; i++){
                        newfile << array[i] << endl; 
                    }
                    newfile << student_number << " " << fullname << endl;
                }
                else newfile << student_number << " " << fullname << endl;
                newfile.close();
            }
            else cout << "Unable to open file.";
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

class Display{
    public:
        Display(string fn){
            filename = fn;
        };

        int Display_File (){
            ifstream File (filename);
            if (File.is_open()) {
                while (! File.eof()) {
                    getline(File, lines);
                    students [loop] = lines;
                    loop++;
                }
                File.close();
            }
            else{
                cout << "Unable to open file.";
                return 1;
            }

            for (int i = 0; i < loop; i++){
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
        if (isalpha(data[i])){
            valid = true;
        }
        else return false;
    }
    return true;
}

//Function for Adding Students to the Database
int add_student()
{
    //Declaration of Variables to be used in Getting The Student's Information;
    char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}; 
    bool valid_middle, valid_number = false;
    bool tempv_number = true;
    
    if (student_count > 20){
        cout << "Max amount of students has been reached!";
        return 1;
    }

    cout << "STUDENT INFORMATION" << endl;
    cout << "Please Fill out the Following Fields:" << endl;
    cout << "STUDENT NAME" << endl;

    //Asking the User to Input the Student's Information
    do
    {
        cout << "Surname: ";
        getline (cin, student_info[*pntr][0]);
    }
    while (input_validation(student_info[*pntr][0]) == false);

    do
    {
        cout << "Given Name: ";
        getline (cin, student_info[*pntr][1]);
    }
    while (input_validation(student_info[*pntr][1]) == false);

    do
    {
        cout << "Middle Initial (If you do not have one type 1): ";
        getline (cin, student_info[*pntr][2]);

        //Makes sure the Middle Initial is Upper Case
        for (int i = 0; i < student_info[*pntr][2].length(); i++){
            toupper(student_info[*pntr][2][i]);
        }
        
        //If 1 is Typed, Nothing will be Displayed
        if (student_info[*pntr][2] == "1"){
            student_info[*pntr][2] = "";
            valid_middle = true;
        }

        else if (student_info[*pntr][2].length() <= 2){
            valid_middle = true;
        }

        else valid_middle = false;
    }
    while (valid_middle == false);

    cout << "STUDENT ADDRESS" << endl;

    cout << "House Number: ";
    getline (cin, student_info[*pntr][3]);

    do
    {
        cout << "Street Name (If you don't have one, type 1): ";
        getline (cin, student_info[*pntr][4]);
    } 
    while (input_validation(student_info[*pntr][4]) == false || student_info[*pntr][4] == "1");
    
    if (student_info[*pntr][4] == "1"){
        student_info[*pntr][4] = "";
    }

    do
    {
        cout << "Subdivision/Building Name (If you don't have one, type 1): ";
        getline (cin, student_info[*pntr][5]);
    }
    while (input_validation(student_info[*pntr][5]) == false || student_info[*pntr][5] == "1");

    if (student_info[*pntr][5] == "1"){
        student_info[*pntr][5] = "";
    }

    do 
    {
        cout << "Barangay Name: ";
        getline (cin, student_info[*pntr][6]);
    }
    while (input_validation(student_info[*pntr][6]) == false);

    do
    {
        cout << "City/Municipality: ";
        getline (cin, student_info[*pntr][7]);
    }
    while (input_validation(student_info[*pntr][7]) == false);

    //The Loop will keep Occuring Until An 11-Digit Phone Number is Typed
    do
    {
        cout << "Phone Number (Please follow the format 09xxxxxxxxx): ";
        getline(cin, student_info[*pntr][8]);

        if (student_info[*pntr][8].length() == 11){

            if (student_info[*pntr][8][0] == '0'){
                
                if (student_info[*pntr][8][1] == '9'){
                    
                    for (int i = 2; i < 11; i++){
                        
                        for (int j = 0; j < 10; j++){
                            if (student_info[*pntr][8][i] == numbers[j]){
                                valid_number = true;
                                break;
                            }
                        }
                        
                        if (valid_number == false){
                            break;
                        }
                    }
                }
            }
        }
    }
    while(valid_number == false);

    Student_info student(student_info[*pntr][0], student_info[*pntr][1], student_info[*pntr][2], student_info[*pntr][3], student_info[*pntr][4], student_info[*pntr][5], student_info[*pntr][6], student_info[*pntr][7], student_info[*pntr][8]);
    
    student.Create_File();
    student.Student_List();
    student.Make_Student_Number();
    student.New_File();

    //Increases the Student Count for the Next Student to be Registered
    *pntr++;
    return 0;
}

//Function for Displaying All the Students in the Terminal
void show_all()
{
    string filename = "Student List.txt";
    Display student_list(filename);
    student_list.Display_File();
}

//Function for Displaying a Specific File's Information in the Terminal
void show_student(string filename)
{
    Display student_file(filename);
    student_file.Display_File();
}

//Function to Remove Student File and from Database
int delete_student(string last, string first, string middle, string number)
{
    string file = last + "_" + first + ".txt";

    if (middle == "1")
    {
        middle == "";
    }
    string stringToRemove = number + "  " + last + ", " + first + " " + middle + ".";
    string filename = "Student List.txt";

    ifstream input(filename);
    ofstream temp("temp.txt");

    if (!input.is_open() || !temp.is_open()) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    string line;
    bool found = false;

    //Loops through file to copy the lines to the temp file that aren't the student to be removed and omit copying the removed student
    while (getline(input, line)) {
        if (line.find(stringToRemove) == string::npos) {
            temp << line << endl;
        } 
        
        else {
            found = true;
        }
    }

    input.close();
    temp.close();

    //Checks if the original file was removed and the temp file was properly renamed
    if (found == true) {

        if (remove(filename.c_str()) != 0) {
            cerr << "Could not delete original file" << endl;
            return 1;
        }
        if (rename("temp.txt", filename.c_str()) != 0) {
            cerr << "Could not create new file" << endl;
            return 1;
        }

        //Removes the Deleted Student's File
        remove(file.c_str());
        cout << "Student Info: '" << stringToRemove << "' has been removed from the database" << endl;
    } 

    //Checks if the student is in the database
    else if (found == false) {
        cout << "Sorry, this student is not in our database.";
        remove("temp.txt");
    }

    return 0;
}


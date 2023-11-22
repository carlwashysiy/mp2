#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>

using namespace std;

//declaring functions so that the classes can use them
void incompleteDetails(bool&resetbutton,string classNameTXT[20],int&enlistedClasses);
void inputval(string&yn);
void displayClass(string classNameTXT[20],int&enlistedClasses);
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

        //creating new class file with initial details
        void createNewClassFile(string(&classNames)[20],string(&classNameTXT)[20],
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

class Teacher:public ClassContents //child class for teacher
{
    private:
        string teacher;
    public:
        //constructor
        Teacher(string sbj, string s, string ds, string ts):ClassContents(sbj,s,ds,ts){}
        //constructor
        void setTeacher(string t)
        {
            teacher=t;
        }

        //appending teacher to class file
        void appendteacher(bool subjectNotListed,bool teacherRegistered,string(&classNameTXT)[20],int&enlistedClasses)
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
                else cout <<"   FILE NOT OPEN"<<endl;

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

//displays subjects to be chosen
void displaySubjects(string subjects[10],const int numberofsubjects) 
{
    cout <<"----------------------------------------------------------------"<<endl;
    cout<<"Here is the list of available subjects: "<<endl<<""<<endl;
    for (int i=0; i<numberofsubjects; i++)
    {
        cout <<i+1<<". "<<subjects[i]<<endl;
    }
    return;
}

//prompts user to choose a subject
void ChooseSubject(int&chosenSubject,string&Subject,string subjects[10]) 
{
    string yn;
    do 
    {
        cout <<"----------------------------------------------------------------"<<endl;
        cout<<"Please enter the number of your chosen subject from the list: ";
        cin>> chosenSubject;
        //makes sure user only inputs number from 1-10
        while(cin.fail()==true||cin.peek()!='\n'||(chosenSubject>10||chosenSubject<1))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Please enter a number from 1-10: ";
            cin>>chosenSubject;
        }
        cout <<"You have chosen: "<<subjects[chosenSubject-1];
        cout <<"\nIs this correct? Y/N: "; //verification
        cin>>yn;
        inputval(yn); //makes sure user only inputs y or n
   }while (yn=="n"||yn=="N");
   Subject=subjects[chosenSubject-1];
   //exits if user enters "Y"
   return;
}

//displays sections to be chosen
void displaySections(int chosenSubject,string subjects[10],string sections[2],const int numberofsections)
{
    cout <<"----------------------------------------------------------------"<<endl;
    cout <<"Here's the list of sections for your "<<subjects[chosenSubject-1]<<" class: "<<endl<<""<<endl;
    for (int i=0; i<numberofsections; i++)
    {
        cout <<i+1<<". "<<sections[i]<<endl;
    }
    return;
}

//prompts user to choose a section
void ChooseSection(bool&resetbutton,int&chosenSection,string&Section,string Subject,string sections[2]) 
{
    string yn;
    do 
    {
        cout <<"----------------------------------------------------------------"<<endl;
        cout<<"Please enter the number of your chosen section from the list: ";
        cin>> chosenSection;
        //makes sure user only inputs 1 or 2
        while(cin.fail()==true||cin.peek()!='\n'||(chosenSection>2||chosenSection<1))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Please enter a number from 1-2: ";
            cin>>chosenSection;
        }
        cout <<"You have chosen: "<<sections[chosenSection-1];
        cout <<"\nIs this correct? Y/N: ";
        cin>>yn;
        inputval(yn);
    }while (yn=="n"||yn=="N");//loops until user enters "Y"
    Section=sections[chosenSection-1];
    //exits once user enters "Y"

    //checking if class is enlisted already
    fstream checkClassList("Class List.txt",ios::in);
    bool classEnlistedAlready=false;
    string classNamesCheck=Subject+" "+Section;
    if (checkClassList.is_open())
    {
        string line;
        while (getline(checkClassList,line))
        {
            if (line==classNamesCheck) //if class is found in list
            {
                classEnlistedAlready=true;
                break;
            }
        } 
        checkClassList.close();
    }
    if (classEnlistedAlready==true)
    {
        cout <<"\nClass is already enlisted!"<<endl;
        resetbutton=true; //return function and back to main menu
        return;
    }
    return; //if class is not enlisted, continue
}


//displays days to be chosen
void displayDays(int chosenSubject,string subjects[10],string dayslots[8],const int numberofdays) 
{
    cout <<"----------------------------------------------------------------"<<endl;
    cout <<"Here's the list of day slots for your "<<subjects[chosenSubject-1]<<" class: "<<endl<<""<<endl;
    for (int i=0; i<numberofdays; i++)
    {
        cout <<i+1<<". "<<dayslots[i]<<endl;
    }
    return;
}

//prompts user to choose day slot
void ChooseDay(int&chosenDaySlot,string&DaySlot,string dayslots[2])
{
    string yn;
    do 
    {
        cout <<"----------------------------------------------------------------"<<endl;
        cout<<"Please enter the number of your chosen day slot from the list: ";
        cin>> chosenDaySlot;
        //makes sure user only inputs a number from 1-8
        while(cin.fail()==true||cin.peek()!='\n'||(chosenDaySlot>8||chosenDaySlot<1))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Please enter a number from 1-8: ";
            cin>>chosenDaySlot;
        }
        cout <<"You have chosen: "<<dayslots[chosenDaySlot-1];
        cout <<"\nIs this correct? Y/N: ";
        cin>>yn;
        inputval(yn);
    }while (yn=="n"||yn=="N");
    DaySlot=dayslots[chosenDaySlot-1];
    return;
}

//if user chose 1 day per week
void displayTimeSlots(int chosenDaySlot, int chosenSubject,string subjects[10],string timeslots[2][6]) 
{
    cout <<"----------------------------------------------------------------"<<endl;
    cout <<"Here's the list of time slots for your "<<subjects[chosenSubject-1]<<" class: "<<endl<<""<<endl;
    if (chosenDaySlot==1||chosenDaySlot==2) //twice a week schedule MTh, TF
    {
        for (int i=0; i<6; i++)
        {
            cout <<i+1<<". "<<timeslots[0][i]<<endl;
        }
        return;
    }
    else //once a week schedule M, T, W, Th, F, S
    {
        for (int i=0; i<3; i++)
        {
            cout <<i+1<<". "<<timeslots[1][i]<<endl;
        }
        return;
    }
}

//prompt user to choose time slot
void ChooseTime(int&chosenTimeSlot,int chosenDaySlot,string&TimeSlot,string timeslots[2][6]) 
{
    string yn;
    int onceAweek=1;
    do
    {
        cout <<"----------------------------------------------------------------"<<endl;
        cout<<"Please enter the number of your chosen time slot from the list: ";
        cin>> chosenTimeSlot;
        if (chosenDaySlot==1||chosenDaySlot==2) //twice a week schedule MTh, TF
        {
            //makes sure user only inputs a number from 1-6
            while(cin.fail()==true||cin.peek()!='\n'||(chosenTimeSlot>6||chosenTimeSlot<1))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Please enter a number from 1-6: ";
                cin>>chosenTimeSlot;
            }
            cout <<"You have chosen: "<<timeslots[0][chosenTimeSlot-1];
            cout <<"\nIs this correct? Y/N: ";
            cin>>yn;
            inputval(yn);
            onceAweek=0; //twice a week schedule
        }
        else //once a week schedule M, T, W, Th, F, S
        {
            //makes sure user only inputs a number from 1-3
            while(cin.fail()==true||cin.peek()!='\n'||(chosenTimeSlot>3||chosenTimeSlot<1))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"Please enter a number from 1-3: ";
                cin>>chosenTimeSlot;
            }
            cout <<"You have chosen: "<<timeslots[1][chosenTimeSlot-1];
            cout <<"\nIs this correct? Y/N: ";
            cin>>yn;
            inputval(yn);
        }
    }while(yn=="n"||yn=="N");
    TimeSlot=timeslots[onceAweek][chosenTimeSlot-1];
    return;
}

void displayClass(string classNameTXT[20],int&enlistedClasses) //prints out contents of a class file
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
void incompleteDetails(bool&resetbutton,string classNameTXT[20],int&enlistedClasses) 
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

void assigningTeacher(bool&resetbutton,bool&teacherRegistered,bool&subjectNotListed,
string Subject,string&teacherFullNameA) //prompts user to assign teacher
{
    string yn,teacherLastName,teacherGivenName,teacherMiddleInitial,teacherFullNameB,teacherLastGivenName,
    employeeNumber,teacherDetails;
    do 
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout <<"\nPlease enter the teacher's employee number."<<endl;
        cout <<"Employee Number: 01-";
        getline(cin,employeeNumber);
        cout <<"The employee number is: 01-"<<employeeNumber<<endl;
        cout <<"Is this correct? Y/N: ";
        cin >>yn;
        inputval(yn);  
    }while (yn=="n"||yn=="N");
    do 
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout <<"Please enter the teacher's name: "<<endl;
        cout <<"Last name: ";
        getline(cin,teacherLastName);
        cout <<"Given name: ";
        getline(cin,teacherGivenName);
        cout <<"Middle Initial: ";
        getline(cin,teacherMiddleInitial);
        teacherFullNameA=teacherGivenName +" "+ teacherMiddleInitial +" "+ teacherLastName;
        cout <<"The teacher's name is: "<<teacherFullNameA<<endl;
        cout <<"Is this correct? Y/N: ";
        cin >>yn;
        inputval(yn);  
    }while (yn=="n"||yn=="N");

    //checking if teacher is registered in Teacher List.txt
    teacherFullNameB=teacherLastName+", "+teacherGivenName+" "+teacherMiddleInitial;
    teacherDetails="01-"+employeeNumber+" "+teacherFullNameB;
    fstream checkTeacherList ("Teacher List.txt",ios::in);
    teacherRegistered=false;
    if (checkTeacherList.is_open())
    {
        string line;
        while(getline(checkTeacherList,line))
        {
            if (line==teacherDetails)
            {
                teacherRegistered=true;
            }
        }
        checkTeacherList.close();
    }

    //checking if teacher has subject listed in file
    if (teacherRegistered)
    {
        subjectNotListed=false;
        teacherLastGivenName=teacherLastName+"_"+teacherGivenName+".txt";
        fstream checkTeacherFile(teacherLastGivenName,ios::in);
        if (checkTeacherFile.is_open())
        {
            for (int i=1;i<5;i++)
            {
                string dummy;
                getline(checkTeacherFile,dummy);
            }
            //starting at the fifth line
            string checkSubjects;
            if(getline(checkTeacherFile,checkSubjects))
            {
                // .find will return npos if subject is not found
                if(checkSubjects.find(Subject)==string::npos)
                {
                    cout <<"\nSubject is not listed in teacher's information."<<endl;
                    subjectNotListed=true;
                    resetbutton=true;
                }
            }
            checkTeacherFile.close();
        }
    }

    //teacher is not registered
    else
    {
        cout <<"\nTeacher is not registered in database!"<<endl;
        resetbutton=true;
        return;
    }  
}

//prompts user to enlist student
void enlistStudent(bool&resetbutton, bool&studentRegistered,bool&studentEnlistedAlready,bool&conflictingSchedule,
string Subject, string DaySlot, string TimeSlot,string&studentDetails,const int maxNumOfStudents,
string(&studentClassList)[5][100]) 
{
    string yn,studentLastName,studentGivenName,studentMiddleInitial,studentFullName,studentNumber;
    do 
    {
        cout <<"\nPlease enter the student number."<<endl;
        cout <<"Student Number: 23-";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin,studentNumber);
        cout <<"The student number is: 23-"<<studentNumber<<endl;
        cout <<"Is this correct? Y/N: ";
        cin >>yn;
        inputval(yn);
    }while(yn=="n"||yn=="N");

    do 
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout <<"\nPlease enter the student's name: "<<endl;
        cout <<"Last name: ";
        getline(cin,studentLastName);
        cout <<"Given name: ";
        getline(cin,studentGivenName);
        cout <<"Middle Initial: ";
        getline(cin,studentMiddleInitial);
        studentFullName=studentLastName+", "+studentGivenName+" "+studentMiddleInitial;
        cout <<"The student's name is: "<<studentFullName<<endl;
        cout <<"Is this correct? Y/N: ";
        cin >>yn;
        inputval(yn);
    }while (yn=="n"||yn=="N");
    
    //checking if student is registered in Student List.txt
    studentDetails="23-"+studentNumber+" "+studentFullName;
    fstream checkStudentList ("Student List.txt",ios::in);
    studentRegistered=false;
    if (checkStudentList.is_open())
    {
        string line;
        while(getline(checkStudentList,line))
        {
            if (line==studentDetails)
            {
                studentRegistered=true;
            }
        }
        checkStudentList.close();
    }

    if (studentRegistered==true)
    {
        //checking array if student is enlisted in subject with same or different section
        for (int i=0; i<maxNumOfStudents; i++)
        {
            if (studentClassList[0][i]==studentDetails&&studentClassList[1][i]==Subject)
            {
                cout <<"\nStudent is already enlisted in this subject!";
                studentEnlistedAlready=true;
                break;                    
            }
        }
        if (!studentEnlistedAlready)
        {
            for (int i=0; i<maxNumOfStudents; i++)
            {
                if (studentClassList[0][i]==studentDetails&&studentClassList[3][i]==DaySlot&&studentClassList[4][i]==TimeSlot)
                {
                    cout <<"\nConflicting schedule! Student is already in a class with the same day and time.";
                    conflictingSchedule=true;
                    break;                    
                }
            }  
        }
    }
    if (studentRegistered==false)
    {
        cout <<"\nStudent is not registered in database!"<<endl;
    }
}

//prompts user to choose which class to view
void ChooseClassView(int&chosenClassView,string classNames[20],string classNameTXT[20],
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
void updateTextFiles(string(&classNames)[20],string(&classNameTXT)[20],string(&studentClassList)[5][100],
const int maxNumOfStudents,int&enlistedClasses) 
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
void ChooseClassDelete(int&chosenClassDelete,
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
    int chosenSubject, chosenDaySlot, chosenTimeSlot, chosenSection;
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
    //display and choose subject
    displaySubjects(subjects,numberofsubjects);
    ChooseSubject(chosenSubject,Subject,subjects);

    //display and choose section
    displaySections(chosenSubject,subjects,sections,numberofsections);
    ChooseSection(MainResetButton,chosenSection,Section,Subject,sections);
    if (MainResetButton) //if class is aleady enlisted
    {
        return; //back to main menu
    }
    //display and choose day slot
    displayDays(chosenSubject,subjects,dayslots,numberofdays);
    ChooseDay(chosenDaySlot,DaySlot,dayslots);

    //display and choose time slot
    displayTimeSlots(chosenDaySlot,chosenSubject,subjects,timeslots);
    ChooseTime(chosenTimeSlot,chosenDaySlot,TimeSlot,timeslots);
    ClassContents newclass(Subject,Section,DaySlot,TimeSlot);

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
            assigningTeacher(reset,teacherRegistered,subjectNotListed,Subject,teacherFullNameA); 
            //includes the process of checking if teacher is in database
            Teacher tchr(Subject,Section,DaySlot,TimeSlot);
            tchr.setTeacher(teacherFullNameA);
            tchr.appendteacher(subjectNotListed,teacherRegistered,classNameTXT,enlistedClasses);
        }
    }while(reset==true);
    displayClass(classNameTXT,enlistedClasses); //display updated version of class with teacher included

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
        enlistStudent(resetbutton,studentRegistered,studentEnlistedAlready,conflictingSchedule,
        Subject,DaySlot,TimeSlot,studentDetails,maxNumOfStudents,studentClassList); 
        Student stdnt(Subject,Section,DaySlot,TimeSlot);
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
    cout <<"Option 3: Return to main menu"<<endl;
    cout <<"\nPlease enter the number of your choice: ";
    int option;
    cin >>option;
    inputvalpath(option); //makes sure user only inputs 1 2 or 3

    if (option==1)//view details of a class
    {
        cout <<"\nHere is the list of enlisted classes: "<<endl;
        cout <<"----------------------------------------------------------------"<<endl;
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
        //prompt user to choose class to view
        ChooseClassView(chosenClassView,classNames,classNameTXT,maxNumofClasses,enlistedClasses); 
        MainResetButton=true; //back to main menu after displaying class details
        return;
    }

    else if (option==2)//delete a class
    {
        cout <<"\nHere is the list of enlisted classes: "<<endl;
        cout <<"----------------------------------------------------------------"<<endl;
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
        //prompt user to choose class to delete
        ChooseClassDelete(chosenClassDelete,classNames,classNameTXT,studentClassList,
        maxNumofClasses,maxNumOfStudents,enlistedClasses); 
        MainResetButton=true; //back to main menu after deleting class
        return;
    }
    else //Option 3
    {  
        MainResetButton=true; //return to main menu
        return;
    }
}

void ClassRegistrationSystem()
{
    const int maxNumOfClasses=20;
    const int maxNumOfStudents=100;
    const int StudentSubjectSectionDayslotTimeslot=5;
    string classNames[maxNumOfClasses];//array for names of each class
    string classNameTXT[maxNumOfClasses];//array for txt file names of each class
    //array for checking if student is enlisted in class with different section or if conflicting schedule
    string studentClassList[StudentSubjectSectionDayslotTimeslot][maxNumOfStudents];
    int enlistedClasses=0;
    bool MainResetButton=false; //if it remains false, 
    int chosenpath; //create new class or edit class
    do
    {
        MainResetButton=false;
        //displaying options
        cout <<"----------------------------------------------------------------"<<endl;
        cout <<"This is the main menu. What do you wish to do?:"<<endl;
        cout <<"1 - Create a new class."<<endl;
        cout <<"2 - View/Delete existing classes."<<endl;
        cout <<"3 - Exit the program."<<endl;
        cout <<"----------------------------------------------------------------"<<endl;
        cout <<"Please enter the number of your choice: ";
        cin >>chosenpath;
        inputvalpath(chosenpath);
        if (chosenpath==1)//user wants to create a new class
        {
            bool placeholder; //placeholder just to pass in function
            //update arrays
            fileScan(placeholder,classNames,classNameTXT,studentClassList,maxNumOfClasses,enlistedClasses); 
            creatingNewClass(MainResetButton,classNames,classNameTXT,studentClassList,
            maxNumOfClasses,maxNumOfStudents,enlistedClasses);
            //MainResetButton always returns true for path 1, loops function
        }
        else if(chosenpath==2)//user wants to view classes
        {
            //update arrays
            fileScan(MainResetButton,classNames,classNameTXT,studentClassList,maxNumOfClasses,enlistedClasses); 
            viewDeleteClasses(MainResetButton,classNames,classNameTXT,studentClassList,
            maxNumOfClasses,maxNumOfStudents,enlistedClasses); 
            //MainResetButton always returns true for path 2, loops function
        }
        else //exit the program if user inputs 3
        {
            cout <<"\nThank you and goodbye."<<endl;
            return; //MainResetButton is still false, program exits
        }
    }while (MainResetButton==true); //will always loop until user takes path 3
}

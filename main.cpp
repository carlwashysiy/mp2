#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "siy_header.h"
using namespace std;

void ClassRegistrationSystem()
{
    bool MainResetButton=false; //if it remains false, program exits
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
            fileScan(placeholder); //updates arrays
            creatingNewClass(MainResetButton); //MainResetButton always returns true for path 1, loops function
        }
        else if(chosenpath==2)//user wants to view classes
        {
            fileScan(MainResetButton); //updates arrays
            viewDeleteClasses(MainResetButton); //MainResetButton always returns true for path 2, loops function
        }
        else //exit the program if user inputs 3
        {
            cout <<"\nThank you and goodbye."<<endl;
            return; //MainResetButton is still false, program exits
        }
    }while (MainResetButton==true); //will always loop until user takes path 3
}

int main()
{
    ClassRegistrationSystem(); 
    //can add Block 1 Student Registration System and Block 2 Teacher Registration System
}
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "siy_header.h"
using namespace std;

int main()
{
    bool MenuResetButton;
    int block;
    do 
    {
        MenuResetButton=false;
        cout <<"----------------------------------------------------------------"<<endl;
        cout <<"This is the main menu. What do you wish to do?:"<<endl;
        cout <<"1 - Student Registration System."<<endl;
        cout <<"2 - Teacher Registration System."<<endl;
        cout <<"3 - Class Registration System."<<endl;
        cout <<"4 - Exit the program."<<endl;
        cout <<"----------------------------------------------------------------"<<endl;
        cout <<"Please enter the number of your choice: ";
        cin >>block;
        switch(block)
        {
            case 1:
                block1(MenuResetButton);
                break;
            case 2:
                TeacherMenu(MenuResetButton);
                break;
            case 3:
                ClassRegistrationSystem(MenuResetButton);
                break;
            case 4:
                cout <<"\nThank you and goodbye."<<endl;
                break;
        } 
    }while (MenuResetButton==true); //will always loop until user enters 4
}
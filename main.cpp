// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT4L 
// Names: Loi Xinyi | Lam Yuet Xin |  Mischelle Thanusha Julius 
// IDs: 1211102975 | MEMBER_ID_2  | 1211101153
// Emails: 1211102975@student.mmu.edu.my | MEMBER_EMAIL_2 |
// Phones: 0174886183 | 0176308285 | 01135632032
// ********************************************************* 


#include "helper.h"
#include "helper.cpp"
#include <cstdlib>
#include <ctime> 
#include <iostream>
#include <iomanip>
#include "AVZ.hpp"
using namespace std;

int getColumnCount();

int getRowCount();

int main()
{
	cout << "Assignment (Part 1)" << endl;
     cout << "Let's Get Started!" << endl;
     char yn ='n';

     cout<<"Default Game Setting"<< endl;
     cout<<"-----------------"<< endl;

    avz::Gameboard gb = avz::Gameboard(3, 19);
	
	avz::Alien alien = avz::Alien(gb);
	gb.placeAlien(alien,gb.getColumnCount()/2,gb.getRowCount()/2);
	avz::Control control(gb,alien);
    // cout<<"Board Rows:"<< getRowCount<<endl;
    // cout<<"Board Columns:"<< getColumnCount<<endl;
     //cout<<"Zombie Count:"<<getZombieCount<< endl;
    // cout<<endl;
     cout<<"Do you wish to change the game settings (y/n)?=>";
     cin >> yn;
    
    //srand(1);
	srand(time(0));
	
	int rowCount;
        int columnCount;
        int zombieCount;
		
	std::cout << std::endl;
	if(yn =='N' ||yn =='n')
    {
        control.work();
    }
	//gb.show();
     if(yn =='Y' ||yn =='y')
    {
       
     cout<<"Board Setting"<< endl;
     cout<<"-----------------"<< endl;
 
        cout<<"Enter row =>";
        cin>>rowCount;
        while (rowCount % 2 == 0)
        {
            cout<<"Please enter an odd number"<<endl;
            cout<<"Enter row =>";
            cin>>rowCount;
        }
            cout<<"Enter column =>";
            cin>>columnCount;
            while (columnCount % 2 == 0)
        {
            cout<<"Please enter an odd number"<<endl;
            cout<<"Enter column =>";
            cin>>columnCount;
        }
            cout<<endl;
            cout<<"Zombie Setting"<< endl;
            cout<<"-----------------"<< endl;
            cout<<"Enter number of zombie =>";
            cin>>zombieCount;
            cout<<endl;
            cout<<"Setting Updated."<< endl;
            cout<<"Press any key to continue . . ."<< endl;
            control.work();

       }


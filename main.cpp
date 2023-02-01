// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT4L 
// Names: Loi Xinyi | Lam Yuet Xin |  Mischelle Thanusha Julius 
// IDs: 1211102975 | 1211101775  | 1211101153
// Emails: 1211102975@student.mmu.edu.my |1211101775@student.mmu.edu.my |1211101153@student.mmu.edu.my
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


int main()
{
	cout << "Assignment (Part 1)" << endl;
     cout << "Let's Get Started!" << endl;
     char yn ;

     cout<<"Default Game Setting"<< endl;
     cout<<"-----------------"<< endl;

    avz::Gameboard gb = avz::Gameboard(5, 9);
    // cout<<"Board Rows:"<< getRowCount<<endl;
    // cout<<"Board Columns:"<< getColumnCount<<endl;
     //cout<<"Zombie Count:"<<getZombieCount<< endl;
    // cout<<endl;
     cout<<"Do you wish to change the game settings (y/n)?=>";
     cin >> yn;
    
    //srand(1);
	srand(time(0));
	    int x;
        int y;
        int z;
		
	std::cout << std::endl;
	if(yn =='N' ||yn =='n')
    {
        avz::Gameboard gb = avz::Gameboard(5, 9);
	
	    avz::Alien alien = avz::Alien(gb);
	    gb.placeAlien(alien,gb.getColumnCount()/2,gb.getRowCount()/2);
	    avz::Control control(gb,alien);
        control.work();
    }
	//gb.show();
     if(yn =='Y' ||yn =='y')
    {
       
     cout<<"Board Setting"<< endl;
     cout<<"-----------------"<< endl;
 
        cout<<"Enter row =>";
        cin>>x;
        while (x % 2 == 0)
        {
            cout<<"Please enter an odd number"<<endl;
            cout<<"Enter row =>";
            cin>>x;
        }
            cout<<"Enter column =>";
            cin>>y;
            while (y % 2 == 0)
        {
            cout<<"Please enter an odd number"<<endl;
            cout<<"Enter column =>";
            cin>>y;
        }
            cout<<endl;
            cout<<"Zombie Setting"<< endl;
            cout<<"-----------------"<< endl;
            cout<<"Enter number of zombie =>";
            cin>>z;
            cout<<endl;
            cout<<"Setting Updated."<< endl;
            cout<<"Press any key to continue . . ."<< endl;

            avz::Gameboard gb = avz::Gameboard(x,y);
	
	        avz::Alien alien = avz::Alien(gb);
	        gb.placeAlien(alien,gb.getColumnCount()/2,gb.getRowCount()/2);
	        avz::Control control(gb,alien);
            control.work();
             

       }

    
}



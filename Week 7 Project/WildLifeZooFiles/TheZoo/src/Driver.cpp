/*
 * Driver.cpp
 *
 *  Created on: Oct 17, 2020
 *      Author: 1698549_snhu
 */
#include "TheZoo.h"

/************MAIN****************/
int main()
{
   int userSelect;
   TheZoo zoo;

   cout << "***********************************************************************************************" << endl;
   cout << "READ ME:" << endl;
   cout << "1 - [Generate Data] creates a text file and allows user input." << endl;
   cout << "2 - [Load Animal Data] loads data from file--must be used before displaying data." << endl;
   cout << "3 - [Display Animal Data] displays file contents in tabular format." << endl;
   cout << "4 - [Add Record] must be used to add additional content after text file is created." << endl;
   cout << "5 - [Delete Record] removes an entire record using full track number(including zeroes) OR name." << endl;
   cout << "6 - [Save Animal Data] saves modified data into latest file creation." << endl;
   cout << "7 - [Exit Program] exits program as expected." << endl;
   cout << "***********************************************************************************************" << endl;

   zoo.DisplayMenu();

   cin >> userSelect;
   while(userSelect > 0 && userSelect < 8) {
      if(cin.fail()) {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         cout << "Invalid input" << endl;
         cin >> userSelect;
      }

      if(!cin.fail()) {
         zoo.ProcessMenu(userSelect);
         break;
      }
   }

   zoo.~TheZoo();

   return 0;
}



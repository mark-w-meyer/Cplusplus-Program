/*
 * TheZoo.h
 *
 *  Created on: Oct 11, 2020
 *      Author: 1698549_snhu
 */

#ifndef WILDLIFEZOOFILES_THEZOO_SRC_THEZOO_H_
#define WILDLIFEZOOFILES_THEZOO_SRC_THEZOO_H_

#include <iostream>   // Used for input/output
#include <vector>     // Used for vectors
#include <jni.h>      // Used to implement Java
#include <fstream>    // Used to read contents of file
#include <string>     // Used to manipulate strings such as string to integer conversions
#include <limits>     // Used for exception handling
#include <exception>  // Used for exception handling
#include <iomanip>    // Used to set column widths and fill zeroes
#include <algorithm>  // Uses find and min functions
#include <iterator>   // Uses iterator to search vector for elements
using namespace std;

class TheZoo {
   public:
      //Default Constructor
      TheZoo();
      //Destructor
      ~TheZoo();
      //Functions
      string InputTrim(string t_userIn, int t_dataLen);
      void   GenerateData();
      void   LoadDataFromFile();
      void   SaveDataToFile();
      void   AddAnimal();
      void   RemoveAnimal();
      void   PrintZooTableHeader();
      void   PrintZooTableRows();
      void   DisplayMenu();
      void   ProcessMenu(int t_menuNum);
   protected:
      vector<string> animalRecord;
};

#endif /* WILDLIFEZOOFILES_THEZOO_SRC_THEZOO_H_ */

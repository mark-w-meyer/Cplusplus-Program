#include "TheZoo.h"

// Default Constructor
TheZoo::TheZoo() {
}
// Destructor
TheZoo::~TheZoo(){
}

vector<string> animalRecord {};          // Vector for storing animal records

// Struct containing length of columns for data table
struct DataLen { int trackLen = 7,       // Note that trackLen had to be changed from 6 to 7 to align with behavior of Java class despite instruction in project guide for allowed length of 6, Java prints 6 zeroes
                     nameLen = 14,       // Structs used to track store column widths
                     typeLen = 14,
                     subtypeLen = 14,
                     eggLen = 14,
                     nurseLen = 14; };


/*-------------FUNCTIONS----------------*/
void TheZoo::GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=U:/Week 7 Project/WildLifeZooFiles/TheZoo";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialisation options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

// Loads data from file (generated by JNI) into vector
void TheZoo::LoadDataFromFile()
{
   string data;

   ifstream fileReader;
   fileReader.open("zoodata.txt");

   if (fileReader.fail()){
      cout << "Could not open file zoodata.txt." << "\n";
   }

   animalRecord.clear();

   while (fileReader >> data) {
      animalRecord.push_back(data);
   }

   fileReader.close();
}

// Saves vector to file
void TheZoo::SaveDataToFile()
{
   ofstream saveToFile("zoodata.txt");

   for(vector<string>::iterator i = animalRecord.begin(); i != animalRecord.end(); i++) {
         saveToFile << *i << " ";
   }
   cout << "Save successfully completed" << endl;
}

// Trims user input before being stored in vector, serves as preparation for easier data table formatting
string TheZoo::InputTrim(string t_userIn, int t_dataLen) {
   int strRuler;
   int newStrRuler;
   int fillRuler;

   strRuler = t_userIn.length();                 // Stores length of string
   // Trims string from start of string to length of whichever is shorter, the original string or the max characters allowed
   t_userIn = t_userIn.substr(0, min(strRuler, t_dataLen));
   // Updates ruler to new trimmed length
   newStrRuler = t_userIn.length();
   // Uses updated ruler to measure how many zeroes are needed to fill in front of track number
   if(t_dataLen == 7){
      if(newStrRuler < 7) {
         fillRuler = t_dataLen - newStrRuler;    // Stores number of zeroes needed to fill
         string zeroes(fillRuler, '0');          // Creates string of zeroes
         t_userIn = zeroes.append(t_userIn);     // Concats track number to the end of zeroes
      }
   }
   // Returns trimmed string
   return t_userIn;
}

// Adds an animal to vector with user input that is pre-trimmed before adding to vector for easy output to table
void TheZoo::AddAnimal()
{
   int     inputToInt;
   string  userInput;               // Stores user input
   DataLen columnLen;               // Struct of column widths, used to trim user input in case it exceeds max allowed in column
    try{
         cout << ("Track Number: ") << endl;
         cin >> userInput;
         inputToInt = stoi(userInput);
         while (inputToInt < 1 || inputToInt > 9999999){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number from 1 to 9999999:" << endl;
            cin >> userInput;
            inputToInt = stoi(userInput);
         }

         animalRecord.push_back(InputTrim(userInput, columnLen.trackLen));

         cout << ("Enter Animal Name: ") << endl;
         cin >> userInput;
         animalRecord.push_back(InputTrim(userInput, columnLen.nameLen));

         cout << ("Enter Animal Type: ") << endl;
         cin >> userInput;
         animalRecord.push_back(InputTrim(userInput, columnLen.typeLen));

         cout << ("Enter Animal Sub-type: ") << endl;
         cin >> userInput;
         animalRecord.push_back(InputTrim(userInput, columnLen.subtypeLen));

         cout << ("Enter Number of Eggs: ") << endl;
         cin >> userInput;
         animalRecord.push_back(InputTrim(userInput, columnLen.eggLen));

         cout << ("Enter 1 if Nursing, 0 if not: ") << endl;
         cin >> userInput;
         inputToInt = stoi(userInput);
         while (inputToInt != 1 && inputToInt != 0){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter '1' for nursing, '0' if not:" << endl;
            cin >> userInput;
            inputToInt = stoi(userInput);
         }
         animalRecord.push_back(InputTrim(userInput, columnLen.nurseLen));

         cout << "Are you sure you want to add record: " << endl;
         cout << "Enter '1' to confirm and save, Enter '2' to cancel and return to menu: " << endl;

         cin >> userInput;
         if(userInput == "1"){        // If user confirms, add range of elements to vector, save to file, clear vector, return to menu
            cout << "Animal successfully added" << endl;
            SaveDataToFile();
            animalRecord.clear();
         }
         else if(userInput == "2"){  // If user cancels, clear the vector, return to main menu
            animalRecord.clear();
         }

    }catch(const exception & e) {
       cerr << e.what() << endl;
    }
   cout << endl << endl;
}

// Removes an animal from vector
void TheZoo::RemoveAnimal()
{
   string deleteStr;
   int    userInt;
   int    deleteInt;
   int    recIndex;
   bool   loopExit = true;

   LoadDataFromFile();

   vector<string>::iterator first = animalRecord.begin();
   vector<string>::iterator last = animalRecord.end();
   vector<string>::iterator iter;

   try{
      do{
         // Gets a string from user to delete in the form of either track number or name
         cout << "Enter '1' to delete by track number, Enter '2' to delete by name" << endl;
         cin >> userInt;

         if(userInt == 1){
            cout << "Please enter a track number(including zeroes):" << endl;
            cin >> deleteInt;
            // Creates an iterator to search through vector loaded from file for user input and identifies index of that string in vector
            iter = find(first, last, to_string(deleteInt));
         }
         else if(userInt == 2){
            cout << "Please enter a name:" << endl;
            cin >> deleteStr;
            // Creates an iterator to search through vector loaded from file for user input and identifies index of that string in vector
            iter = find(first, last, deleteStr);
         }
         else {
            deleteStr = "exit";    // Exits the do/while
            break;
         }

         recIndex = distance(first, iter);
         // If string is found and string contains numbers, erase elements from index to next five elements
         if (iter != last && isdigit(deleteInt)){
            cout << "Record Found" << endl;
            cout << "Are you sure you want to delete record: " << deleteInt << endl;
            cout << "Enter '1' to confirm and save, Enter '2' to cancel and return to menu: " << endl;

            cin >> userInt;
            if(userInt == 1){        // If user confirms, erase range of elements in vector, save to file, clear vector, break from loop to return to menu
               animalRecord.erase(first + recIndex, first + recIndex + 6);
               cout << "Animal successfully deleted" << endl;
               SaveDataToFile();
               animalRecord.clear();
               break;
            }
            else if(userInt == 2){  // If user cancels, clear the vector, break from loop to return to main menu
               animalRecord.clear();
               break;
            }
            loopExit = false;
         } // If string is found and string is not numbers, erase the elements from before the name(track number) to five elements after(since name is second element of record)
         else if (iter != last && deleteStr != "exit") {
            cout << "Record Found" << endl;
            cout << "Are you sure you want to delete record: " << deleteStr << endl;
            cout << "Enter '1' to confirm and save, Enter '2' to cancel and return to menu: " << endl;
            cin >> userInt;

            if(userInt == 1){
               animalRecord.erase(first + recIndex - 1, first + recIndex + 5);
               cout << "Animal successfully deleted" << endl;
               SaveDataToFile();
               animalRecord.clear();
               break;
            }
            else if(userInt == 2){
               animalRecord.clear();
               break;
            }
            loopExit = false;
         }
         else {
            if(deleteStr == "exit"){
               cout << "Returning to Main Menu" << endl;
               loopExit = true;
            }
            else{
               // Else let user know the record was not found
               cout << "Record Not Found" << endl;
               loopExit = false;
            }
         }
      } while(!loopExit);
   }catch(const exception & e) {
      cerr << e.what() << endl;
   }
   return;
}

// Prints the header for the data table along with headings
void TheZoo::PrintZooTableHeader(){
   cout << " ------------------------------------------------------------------------------------------------" << endl;
   cout << "| Track #       |";
   cout << " Name          |";
   cout << " Type          |";
   cout << " Sub-Type      |";
   cout << " Eggs          |";
   cout << " Nurse          |";
   cout << endl;
   cout << " ------------------------------------------------------------------------------------------------" << endl;
}

// Uses loop to print all vector elements in tabular format
void TheZoo::PrintZooTableRows(){
   int dataSize;

   for(size_t i = 0; i < animalRecord.size(); i++){
      dataSize = 16 - animalRecord[i].length();   // Tracks how many spaces are needed to fill the rest of the column using size of data in vector
      cout << "| " << animalRecord[i] << right << setw(dataSize) << setfill(' ');   // Aligns text with column heading towards left and fills the rest with spaces
      if (((i + 1) % 6) == 0) {    // Only adds the pipe and new line if more than one record
         cout << "|" << endl << " ------------------------------------------------------------------------------------------------" << endl;
      }
   }
}

// Prints user menu and prompts for menu option entry
void TheZoo::DisplayMenu()
{
     cout << endl;
     cout << "********************************" << endl;
     cout << "*   Wildlife Zoo Action Menu   *" << endl;
     cout << "*                              *" << endl;
     cout << "*   1 - Generate Data          *" << endl;
     cout << "*   2 - Load Animal Data       *" << endl;
     cout << "*   3 - Display Animal Data    *" << endl;
     cout << "*   4 - Add Record             *" << endl;
     cout << "*   5 - Delete Record          *" << endl;
     cout << "*   6 - Save Animal Data       *" << endl;
     cout << "*   7 - Exit Program           *" << endl;
     cout << "********************************" << endl;
     cout << endl;
     cout << "Please select a menu option:" << endl;
}

// Processes menu options with switch
void TheZoo::ProcessMenu(int t_menuNum) {

   try {
      do {
         while(t_menuNum > 0 && t_menuNum < 8) {
            if(!cin.fail()) {
               switch(t_menuNum){
                  case 1:
                     GenerateData();
                     LoadDataFromFile();
                     break;
                  case 2:
                     LoadDataFromFile();
                     cout << "Load complete" << endl;
                     break;
                  case 3:
                     PrintZooTableHeader();
                     PrintZooTableRows();
                     break;
                  case 4:
                     AddAnimal();
                     break;
                  case 5:
                     RemoveAnimal();
                     break;
                  case 6:
                     SaveDataToFile();
                     break;
                  case 7:
                     cout << "Exiting Program, Goodbye." << endl;
                     exit(0);
                     break;
                  default:
                     t_menuNum = 7;
                     cout << "Exiting Program, Goodbye." << endl;
                     break;
                  }
               break;
            }
            else {
               cin.clear();
               cin.ignore(INT_MAX);
               cout << "Program ended unexpectedly, Goodbye.";
               t_menuNum = 7;
               break;
            }
         }
         if (t_menuNum != 7) {
           DisplayMenu();
           cin >> t_menuNum;
         }
      }while(t_menuNum != 7);
   }catch(const exception & e) {
      cerr << e.what() << endl;
  }
}



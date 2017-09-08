// MIS.h
// Drew Caltagirone
// Anthony Awaida
// Roberto Chavez
// CMPS 109

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>


using namespace std;

class MISMembers {
   public: 
      // The lines in the input file
      vector<string> lines;

      // Number of Parameters in instruction
      vector<string> para;

      // Lines for Output and error file
      vector<string> outVec;
      vector<string> errVec;

      // Helper Variables for instructions
      int pcount, NUMERIC, MultNUMERIC, j, temp, check, digitCheck, NorR; 
      double REAL, MultREAL;
      string STRING, errFile, outFile;
      char CHAR;
      bool quoteCheck; // Helps determine whitespace within a String

      // Containers for Variables
      map<string, double> doubleVar; // contains all the REAL VARS
      map<string, int> intVar;  // constains all NUMERIC VARS
      map<string, string> stringVar; // contains all the string VARS
      map<string, char> charVar;  // contains all the char VARS
      map<string, int> labelVar; // contans all the Labels

      
      // Method to reset private variables after instruction
      void reset();

      MISMembers(vector<string>& lines); // constructor 
      
      void virtual VAR(int i); // Creates VARS

      void virtual addLabel(int i, int j); // Adds Label to Label map

      void virtual errors(); // To print syntax errors regarding Instructions in MISMain.cpp

      virtual ~MISMembers(); // destructor 

}; 

class ADD {
   public:
   
      ADD(); // Constructor
   
      void virtual DoTask(MISMembers* Instance, int i); // Perform the ADD instruction 

      virtual ~ADD(); // Destructor
};


class SUB {
   public:
      SUB(); // Constructor
   
      void virtual DoTask(MISMembers* Instance, int i); // Perform the SUB instruction
      
      virtual ~SUB(); // Destructor
};

class MULT {
   public:
      MULT(); // Constructor
   
      void virtual DoTask(MISMembers* Instance, int i); // Perform the MULT instruction

      virtual ~MULT(); // Destructor
};

class DIV {
   public:
      DIV(); // Constructor
   
      void virtual DoTask(MISMembers* Instance, int i); // Perform the DIV instruction

      virtual ~DIV(); // Destructor
};

class JMP {
   public:
      JMP(); // Constructor
   
      int virtual DoTask(MISMembers* Instance, int i, int j); 

      virtual ~JMP(); // Destructor

};

class JMPZ {
   public:
      JMPZ(); // Constructor
   
      int virtual DoTask(MISMembers* Instance, int i, int j); 

      virtual ~JMPZ(); // Destructor

};

class JMPNZ {
   public:
      JMPNZ(); // Constructor
   
      int virtual DoTask(MISMembers* Instance, int i, int j); 

      virtual ~JMPNZ(); // Destructor

};

class JMPGT {
   public:
      JMPGT(); // Constructor
   
      int virtual DoTask(MISMembers* Instance, int i, int j); 

      virtual ~JMPGT(); // Destructor

};

class JMPLT {
   public:
      JMPLT(); // Constructor
   
      int virtual DoTask(MISMembers* Instance, int i, int j); 

      virtual ~JMPLT(); // Destructor

};

class JMPGTE {
   public:
      JMPGTE(); // Constructor
   
      int virtual DoTask(MISMembers* Instance, int i, int j); 

      virtual ~JMPGTE(); // Destructor

};

class JMPLTE {
   public:
      JMPLTE(); // Constructor
   
      int virtual DoTask(MISMembers* Instance, int i, int j); 

      virtual ~JMPLTE(); // Destructor
};

class ASSIGN {
   public:
      ASSIGN(); // Constructor

      void virtual DoTask(MISMembers* Instance, int i); // Perform the ASSIGN instruction

      virtual ~ASSIGN(); // Destructor
};

class OUT {
   public:
      OUT(); // Constructor

      void virtual DoTask(MISMembers* Instance, int i); // Perform the OUT instruction

      virtual ~OUT(); // Destructor
};
class SLEEP {
   public:
      SLEEP(); // Constructor

      void virtual DoTask(MISMembers* Instance, int i);

      virtual ~SLEEP(); // Destructor
};
class GET_STR_CHAR {
   public:
      GET_STR_CHAR();

      void virtual DoTask(MISMembers* Instance, int i);

      virtual ~GET_STR_CHAR();
};
class SET_STR_CHAR {
   public:
      SET_STR_CHAR();

      void virtual DoTask(MISMembers* Instance, int i);

      virtual ~SET_STR_CHAR();

};
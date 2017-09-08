// MIS.cpp
// Drew Caltagirone
// Anthony Awaida
// Roberto Chavez
// CMPS 109

#include "MIS.h"


// Constructor
MISMembers::MISMembers(vector<string>& input) {
   using namespace std;
   for(int i = 0; i < input.size(); i++) {
       lines.push_back(input[i]);
   }
   for(int k = 0; k < 13; k++) {
      para.push_back("");
   }
   pcount = 0;
   temp = 0;
   check = 0;
   digitCheck = 0;
   NorR = 0;
   j = 0;
   NUMERIC = 0;
   REAL = 0; 
   STRING = "";
   CHAR = '\0';
   MultNUMERIC = 1;
   MultREAL = 1;   
   quoteCheck = false;
}
// resets all fields for next line use
void MISMembers::reset() {
   using namespace std;
   for(int i = 0; i < 13; i++) {
      para[i] = "";
   }
   pcount = 0;
   temp = 0;
   check = 0;
   digitCheck = 0;
   NorR = 0;
   j = 0;
   NUMERIC = 0;
   REAL = 0; 
   STRING = "";
   CHAR = '\0';
   MultNUMERIC = 1;
   MultREAL = 1; 
   quoteCheck = false;
}
// adds a label to the label map
void MISMembers::addLabel(int i, int j) {
   using namespace std;
   reset();
   // checks for any preceding whitespace/ indentation
   while(true) {
      if(lines[i][j] == ' ' || lines[i][j] == '\t') {
         j++;
      }
      else {
         break; // if something other than the instruction and whitespae is found   
      }
   }
   while (lines[i][j] != '\0') { 
      if(pcount == 0) {
         para[0] += lines[i][j];
      }
      j++;   
   }
   labelVar[para[0]] = i;
   reset();
}
// adds a var to the var map
void MISMembers::VAR(int i) {
   using namespace std;
   reset();
   //cout << "made it here" << endl;
   // checks for any preceding whitespace/ indentation
   j = 0;
   while(true) {
      if(lines[i][j] == ' ' || lines[i][j] == '\t' || lines[i][j] == 'V' || lines[i][j] == 'A' || lines[i][j] == 'R') {
         j++;
      }
      else {
         break;   
      }
   }
   if(lines[i][j] != '$') {
      errVec.push_back("Every VAR must start with '$'.");
      //error << "Every VAR must start with '$'." << endl;
      reset();
      return;
   }
   // string parsing to get all variables and numeric values
   while (lines[i][j] != '\0') {
      if (lines[i][j] == ',') {
         pcount++;
         j++;
      }
      if(lines[i][j] == '\"') {
         quoteCheck = !quoteCheck;
      }
      if(lines[i][j] == ' ' && quoteCheck == false) {
         j++; // Don't include spaces, unless they are part of a String 
      } 
      else { // else there are no spaces
         if(pcount == 0) {
            para[0] += lines[i][j];
         }
         if(pcount == 1) {
            para[1] += lines[i][j];
         }
         if(pcount == 2) {
            para[2] += lines[i][j];
         }
         if(pcount == 3) {
            para[3] += lines[i][j];
         }
         j++;  
      } 
   }
   if(pcount != 3 && pcount != 2) {
      errVec.push_back("Incorrect number of parameters for VAR.");
      //error << "Incorrect number of parameters for VAR." << endl;
      reset();
      return;   
   }
   if(para[1] == "NUMERIC") {
      for(int tempN = 0; tempN < para[2].length(); tempN++) {
         if(isdigit(para[2][tempN]) != true && para[2][tempN] != '.' && para[2][tempN] != '-') {
            errVec.push_back("Must initialize constant numeric value to NUMERIC.");
            //error << "Must initialize constant numeric value to NUMERIC." << endl;
            reset();
            return; 
         }
      }
      NUMERIC = atoi(para[2].c_str());
      intVar[para[0]] = NUMERIC;   
   }
   else if(para[1] == "REAL") {
      for(int tempR = 0; tempR < para[2].length(); tempR++) {
         if(isdigit(para[2][tempR]) != true && para[2][tempR] != '.' && para[2][tempR] != '-') {
            errVec.push_back("Must initialize constant numeric value to REAL.");
            //error << "Must initialize constant numeric value to REAL." << endl;
            reset();
            return; 
         }
      }
      REAL = atof(para[2].c_str());
      doubleVar[para[0]] = REAL;
   }
   else if(para[1] == "CHAR") {
      char nl = '\\';
      if(para[2][0] != '\'' && para[2][2] != '\'' ) {
         //error << "Incorrect Char syntax." << endl;
         errVec.push_back("Incorrect Char syntax.");
         reset();
         return;
      }
      if(para[2].length() != 3 && para[2].length() != 4) {
         errVec.push_back("Incorrect Char syntax");
         //error << "Incorrect Char syntax." << endl;
         reset();
         return;              
      }
      // check all the C++ Character Literals
      if(para[2].length() == 4) {
         if(para[2][1] == nl && para[2][2] == 'n') {
            CHAR = '\n';
            charVar[para[0]] = CHAR;
            reset();
            return;
            }
         else if(para[2][1] == nl && para[2][2] == 't') {
            CHAR = '\t';
            charVar[para[0]] = CHAR;
            reset();
            return;
         }
         else if(para[2][1] == nl && para[2][2] == 'v') {
            CHAR = '\v';
            charVar[para[0]] = CHAR;
            reset();
            return;
         }
         else if(para[2][1] == nl && para[2][2] == 'b') {
            CHAR = '\b';
            charVar[para[0]] = CHAR;
            reset();
            return;
         }
         else if(para[2][1] == nl && para[2][2] == 'r') {
            CHAR = '\r';
            charVar[para[0]] = CHAR;
            reset();
            return;
         }
         else if(para[2][1] == nl && para[2][2] == 'f') {
            CHAR = '\f';
            charVar[para[0]] = CHAR;
            reset();
            return;
         }
         else if(para[2][1] == nl && para[2][2] == 'a') {
            CHAR = '\a';
            charVar[para[0]] = CHAR;
            reset();
            return;
         }
         else if(para[2][1] == nl && para[2][2] == nl) {
            CHAR = '\\';
            charVar[para[0]] = CHAR;
            reset();
            return;
         }
         else if(para[2][1] == nl && para[2][2] == '?') {
            CHAR = '\?';
            charVar[para[0]] = CHAR;
            reset();
            return;
         }
         else if(para[2][1] == nl && para[2][2] == '\'') {
            CHAR = '\'';
            charVar[para[0]] = CHAR;
            reset();
            return;
         }
         else if(para[2][1] == nl && para[2][2] == '\"') {
            CHAR = '\"';
            charVar[para[0]] = CHAR;
            reset();
            return;
         }
         else if(para[2][1] == nl && para[2][2] == '0') {
            CHAR = '\0';
            charVar[para[0]] = CHAR;
            reset();
            return;
         }
         else {
            //error << "Incorrect Char syntax." << endl;
            errVec.push_back("Incorrect Char syntax.");
            reset();
            return;                  
         }
      }
      CHAR = para[2][1];
      charVar[para[0]] = CHAR;
   }
   else if(para[1] == "STRING") {
      for(int tempS = 0; tempS < para[2].length(); tempS++) {
         if(isdigit(para[2][tempS]) != true) {
            errVec.push_back("Must have string size of a positive integer value.");
            //error << "Must have string size of a positive integer value." << endl;
            reset();
            return; 
         }
      }
      if(para[3][0] != '\"' || para[3][para[3].length()-1] != '\"') {
         errVec.push_back("Incorrect String syntax.");
         //error << "Incorrect String syntax." << endl;  
         reset();
         return; 
      }
      for(int tempSS = 1; tempSS < para[3].length()-1; tempSS++) {
         STRING += para[3][tempSS];
      }
      stringVar[para[0]] = STRING;
   } 
   else {
      //error << "Data type not valid." << endl;
      errVec.push_back("Data type not valid.");
      reset();
      return;
   }
   reset(); // after all of calculations, reset all helper fields
}
// prints out instruction errors from main
void MISMembers::errors() {
   using namespace std;
   //error << "Instruction not valid." << endl;
   errVec.push_back("Instruction not valid.");
}
// Destructor
MISMembers::~MISMembers() {
   using namespace std;
   reset();
   doubleVar.clear();
   intVar.clear();
   stringVar.clear();
   charVar.clear();
   lines.clear();
   para.clear();
}


ADD::ADD() {
   // Constructor
}
// Performs ADD instruction
void ADD::DoTask(MISMembers* Instance, int i) {
   using namespace std;
   Instance->reset();
   Instance->j = 0;
   int j = Instance->j;
   // checks for any preceding whitespace/ indentation
   while(true) {
      if(Instance->lines[i][j] == ' ' || Instance->lines[i][j] == '\t' || Instance->lines[i][j] == 'A' || Instance->lines[i][j] == 'D' || Instance->lines[i][j] == 'D') {
         j++;
      }
      else {
         break;   
      }
   }
   // string parsing to get all variables and numeric values
   while (Instance->lines[i][j] != '\0') {
      if (Instance->lines[i][j] == ',') {
         Instance->pcount++;
         j++;
      }
      if(Instance->lines[i][j] == '\"') {
         Instance->quoteCheck = !Instance->quoteCheck;
      }
      if(Instance->lines[i][j] == ' ' && Instance->quoteCheck == false) {
         j++; // Don't include spaces, unless they are part of a String 
      } 
      else {
         if(Instance->pcount == 0) {
            Instance->para[0] += Instance->lines[i][j];
         }
         if(Instance->pcount == 1) {
            Instance->para[1] += Instance->lines[i][j];
         }
         if(Instance->pcount == 2) {
            Instance->para[2] += Instance->lines[i][j];
         }
         if(Instance->pcount == 3) {
            Instance->para[3] += Instance->lines[i][j];
         }
         if(Instance->pcount == 4) {
            Instance->para[4] += Instance->lines[i][j];
         }
         if(Instance->pcount == 5) {
            Instance->para[5] += Instance->lines[i][j];
         }
         if(Instance->pcount == 6) {
            Instance->para[6] += Instance->lines[i][j];
         }
         if(Instance->pcount == 7) {
            Instance->para[7] += Instance->lines[i][j];
         }
         if(Instance->pcount == 8){
            Instance->para[8] += Instance->lines[i][j];
         }
         if(Instance->pcount == 9) {
            Instance->para[9] += Instance->lines[i][j];
         }
         if(Instance->pcount == 10) {
            Instance->para[10] += Instance->lines[i][j];
         }
         if(Instance->pcount == 11) {
            Instance->para[11] += Instance->lines[i][j];
         }
         if(Instance->pcount == 12) {
            Instance->para[12] += Instance->lines[i][j];
         }
         j++;   
      }
   }
   if(Instance->pcount > 12 || Instance->pcount < 2) {
      Instance->errVec.push_back("Incorrect number of parameters for ADD.");
      //error << "Incorrect number of parameters for ADD." << endl;
      Instance->reset();
      return;   
   }
   // calculations
   Instance->check = 0; // use to check if output is NUMERIC or REAL
   // Checking para[0] which is the destination variable
   if(Instance->intVar.count(Instance->para[0]) > 0) {
      Instance->check = 0; // NUMERIC
   } 
   else if(Instance->doubleVar.count(Instance->para[0]) > 0) {
      Instance->check = 1; // REAL
   }
   else {
      Instance->errVec.push_back("Variable has not been declared.");
      //error << "Variable has not been declared." << endl; // print this to the error file 
      Instance->reset();
      return;
   }
   // if the destination is NUMERIC
   if(Instance->check == 0) {
      for(Instance->temp = 1; Instance->temp <= Instance->pcount; Instance->temp++) {
         for(int temp1 = 0; temp1 < Instance->para[Instance->temp].length(); temp1++) {
            if(isdigit(Instance->para[Instance->temp][temp1]) != true && Instance->para[Instance->temp][temp1] != '.' && Instance->para[Instance->temp][temp1] != '-') {
               Instance->digitCheck = 1; 
               break;
            }
            Instance->digitCheck = 0; 
         }
         if(Instance->digitCheck == 0) {
            Instance->NUMERIC += atoi(Instance->para[Instance->temp].c_str()); // converts from string to int
         }
         if(Instance->digitCheck == 1) {
            if(Instance->intVar.count(Instance->para[Instance->temp]) > 0) { 
               Instance->NorR = 0;
            } 
            else if(Instance->doubleVar.count(Instance->para[Instance->temp]) > 0) {
               Instance->NorR = 1;
            }
            else {
               Instance->errVec.push_back("Variable has not been declared.");
               //error << "Variable has not been declared." << endl; // print this to the error file 
               Instance->reset();
               return;
            }                  
            if(Instance->NorR == 0) {
               Instance->NUMERIC += Instance->intVar[Instance->para[Instance->temp]];
            }
            if(Instance->NorR == 1) {
               Instance->NUMERIC += Instance->doubleVar[Instance->para[Instance->temp]];
            }
         }
      }
   }  
   // if the Destination is REAL
   if(Instance->check == 1) {
      for(Instance->temp = 1; Instance->temp <= Instance->pcount; Instance->temp++) {
         for(int temp2 = 0; temp2 < Instance->para[Instance->temp].length(); temp2++) {
            if(isdigit(Instance->para[Instance->temp][temp2]) != true && Instance->para[Instance->temp][temp2] != '.' && Instance->para[Instance->temp][temp2] != '-') {
               Instance->digitCheck = 1; 
               break;
            }
            Instance->digitCheck = 0; 
         }
         if(Instance->digitCheck == 0) {
            Instance->REAL += atof(Instance->para[Instance->temp].c_str()); // converts from string to floating number
         }
         if(Instance->digitCheck == 1) {
            if(Instance->intVar.count(Instance->para[Instance->temp]) > 0) {
               Instance->NorR = 0;
            } 
            else if(Instance->doubleVar.count(Instance->para[Instance->temp]) > 0) {
               Instance->NorR = 1;
            }
            else {
               Instance->errVec.push_back("Variable has not been declared.");
               //error << "Variable has not been declared." << endl; // print this to the error file 
               Instance->reset();
               return; 
            }
            if(Instance->NorR == 0) {
               Instance->REAL += Instance->intVar[Instance->para[Instance->temp]];
            }
            if(Instance->NorR == 1) {
               Instance->REAL += Instance->doubleVar[Instance->para[Instance->temp]];
            }
         }
      }
   }
   if(Instance->check == 0) {
      Instance->intVar.erase(Instance->para[0]);
      Instance->intVar[Instance->para[0]] = Instance->NUMERIC;
   }
   if(Instance->check == 1) {
      Instance->doubleVar.erase(Instance->para[0]);
      Instance->doubleVar[Instance->para[0]] = Instance->REAL;
   }
   Instance->reset(); // reset all fields after calculations 
}

ADD::~ADD() {
   // Destructor
}


SUB::SUB() {
   // Constructor
}
// Performs SUB instruction
void SUB::DoTask(MISMembers* Instance, int i) {
   using namespace std;
   Instance->reset();
   Instance->j = 0;
   int j = Instance->j;
   // checks for any preceding whitespace/ indentation
   while(true) {
      if(Instance->lines[i][j] == ' ' || Instance->lines[i][j] == '\t' || Instance->lines[i][j] == 'S' || Instance->lines[i][j] == 'U' || Instance->lines[i][j] == 'B') {
         j++;
      }
      else {
         break;   
      }
   }
   // string parsing to get all variables and numeric values
   while (Instance->lines[i][j] != '\0') {
      if (Instance->lines[i][j] == ',') {
         Instance->pcount++;
         j++;
      }
      if(Instance->lines[i][j] == '\"') {
         Instance->quoteCheck = !Instance->quoteCheck;
      }
      if(Instance->lines[i][j] == ' ' && Instance->quoteCheck == false) {
         j++; // Don't include spaces, unless they are part of a String 
      } 
      else {
         if(Instance->pcount == 0) {
            Instance->para[0] += Instance->lines[i][j];
         }
         if(Instance->pcount == 1) {
           Instance->para[1] += Instance->lines[i][j];
         }
         if(Instance->pcount == 2) {
            Instance->para[2] += Instance->lines[i][j];
         }
         j++;
      }
   }
   if(Instance->pcount != 2) {
      Instance->errVec.push_back("Incorrect number of parameters for SUB.");
      //error << "Incorrect number of parameters for SUB." << endl;
      Instance->reset();
      return;        
   }
   // calculations
   Instance->check = 0; // use to check if output is NUMERIC or REAL
   // Checking para[0] which is the destination variable
   if(Instance->intVar.count(Instance->para[0]) > 0) {
      Instance->check = 0; // NUMERIC
   } 
   else if(Instance->doubleVar.count(Instance->para[0]) > 0) {
      Instance->check = 1; // REAL
   }
   else {
      Instance->errVec.push_back("Variable has not been declared.");
      //error << "Variable has not been declared." << endl; // print this to the error file 
      Instance->reset();
      return;
   }
   if(Instance->check == 0) {
      for(int temp3 = 0; temp3 < Instance->para[1].length(); temp3++) {
         if(isdigit(Instance->para[1][temp3]) != true && Instance->para[1][temp3] != '.' && Instance->para[1][temp3] != '-') {
            Instance->digitCheck = 1; 
            break;
         }
         Instance->digitCheck = 0; 
      }
      if(Instance->digitCheck == 0) {
         Instance->NUMERIC += atoi(Instance->para[1].c_str()); // converts from string to int
      }
      if(Instance->digitCheck == 1) {
         if(Instance->intVar.count(Instance->para[1]) > 0) { 
            Instance->NorR = 0;
         } 
         else if(Instance->doubleVar.count(Instance->para[1]) > 0) {
            Instance->NorR = 1;
         }
         else {
            Instance->errVec.push_back("Variable has not been declared.");
            //error << "Variable has not been declared." << endl; // print this to the error file 
            Instance->reset();
            return;
         }      
         if(Instance->NorR == 0) {
            Instance->NUMERIC += Instance->intVar[Instance->para[1]];
         }
         if(Instance->NorR == 1) {
            Instance->NUMERIC += Instance->doubleVar[Instance->para[1]];
         }
      }
      for(int temp4 = 0; temp4 < Instance->para[2].length(); temp4++) {
         if(isdigit(Instance->para[2][temp4]) != true && Instance->para[2][temp4] != '.' && Instance->para[2][temp4] != '-') {
            Instance->digitCheck = 1; 
            break;
         }
         Instance->digitCheck = 0; 
      }
      if(Instance->digitCheck == 0) {
         Instance->NUMERIC -= atoi(Instance->para[2].c_str()); // converts from string to int
      }
      if(Instance->digitCheck == 1) {
         if(Instance->intVar.count(Instance->para[2]) > 0) { 
            Instance->NorR = 0;
         } 
         else if(Instance->doubleVar.count(Instance->para[2]) > 0) {
            Instance->NorR = 1;
         }
         else {
            Instance->errVec.push_back("Variable has not been been declared.");
            //error << "Variable has not been declared." << endl;; // print this to the error file 
            Instance->reset();
            return;
         }         
         if(Instance->NorR == 0) {
            Instance->NUMERIC -= Instance->intVar[Instance->para[2]];
         }
         if(Instance->NorR == 1) {                 
            Instance->NUMERIC -= Instance->doubleVar[Instance->para[2]];
         }
      }
   }
   if(Instance->check == 1) {
      for(int temp5 = 0; temp5 < Instance->para[1].length(); temp5++) {
         if(isdigit(Instance->para[1][temp5]) != true && Instance->para[1][temp5] != '.' && Instance->para[1][temp5] != '-') {
            Instance->digitCheck = 1; 
            break;
         }
         Instance->digitCheck = 0; 
      }
      if(Instance->digitCheck == 0) {
         Instance->REAL += atof(Instance->para[1].c_str()); // converts from string to floating number
      }
      if(Instance->digitCheck == 1) {
         if(Instance->intVar.count(Instance->para[1]) > 0) {
            Instance->NorR = 0;
         } 
         else if(Instance->doubleVar.count(Instance->para[1]) > 0) {
            Instance->NorR = 1;
         }
         else {
            Instance->errVec.push_back("Variable has not been declared.");
            //error << "Variable has not been declared." << endl; // print this to the error file 
            Instance->reset();
            return;
         }  
         if(Instance->NorR == 0) {
            Instance->REAL += Instance->intVar[Instance->para[1]];
         }
         if(Instance->NorR == 1) {
            Instance->REAL += Instance->doubleVar[Instance->para[1]];
         }
      } 
      for(int temp6 = 0; temp6 < Instance->para[2].length(); temp6++) {
         if(isdigit(Instance->para[2][temp6]) != true && Instance->para[2][temp6] != '.' && Instance->para[2][temp6] != '-' ) {
            Instance->digitCheck = 1; 
            break;
         }
         Instance->digitCheck = 0; 
      }
      if(Instance->digitCheck == 0) {
         Instance->REAL -= atof(Instance->para[2].c_str()); // converts from string to floating number
      }
      if(Instance->digitCheck == 1) {
         if(Instance->intVar.count(Instance->para[2]) > 0) {
            Instance->NorR = 0;
         } 
         else if(Instance->doubleVar.count(Instance->para[2]) > 0) {
            Instance->NorR = 1;
         }
         else {
            Instance->errVec.push_back("Variable has not been declared.");
            //error << "Variable has not been declared." << endl; // print this to the error file 
            Instance->reset();
            return;
         }     
         if(Instance->NorR == 0) { 
            Instance->REAL -= Instance->intVar[Instance->para[2]];
         }
         if(Instance->NorR == 1) {
            Instance->REAL -= Instance->doubleVar[Instance->para[2]];
         }
      }
   }
   if(Instance->check == 0) {
      Instance->intVar.erase(Instance->para[0]);
      Instance->intVar[Instance->para[0]] = Instance->NUMERIC;
   }
   if(Instance->check == 1) {
      Instance->doubleVar.erase(Instance->para[0]);
      Instance->doubleVar[Instance->para[0]] = Instance->REAL;
   }
   Instance->reset(); 
}

SUB::~SUB() {
   // Destructor
}


MULT::MULT() {
   // Constructor
}
// Performs MULT instruction
void MULT::DoTask(MISMembers* Instance, int i) {
   using namespace std;
   Instance->reset();
   Instance->j = 0;
   int j = Instance->j;
   // checks for any preceding whitespace/ indentation
   while(true) {
      if(Instance->lines[i][j] == ' ' || Instance->lines[i][j] == '\t' || Instance->lines[i][j] == 'M' || Instance->lines[i][j] == 'U' || Instance->lines[i][j] == 'L' || Instance->lines[i][j] == 'T') {
         j++;
      }
      else {
         break;   
      }
   }
   // string parsing to get all variables and numeric values
   while (Instance->lines[i][j] != '\0') {
      if (Instance->lines[i][j] == ',') {
         Instance->pcount++;
         j++;
      }
      if(Instance->lines[i][j] == '\"') {
         Instance->quoteCheck = !Instance->quoteCheck;
      }
      if(Instance->lines[i][j] == ' ' && Instance->quoteCheck == false) {
         j++; // Don't include spaces, unless they are part of a String 
      } 
      else {
         if(Instance->pcount == 0) {
            Instance->para[0] += Instance->lines[i][j];
         }
         if(Instance->pcount == 1) {
            Instance->para[1] += Instance->lines[i][j];
         }
         if(Instance->pcount == 2) {
            Instance->para[2] += Instance->lines[i][j];
         }
         if(Instance->pcount == 3) {
            Instance->para[3] += Instance->lines[i][j];
         }
         if(Instance->pcount == 4) {
            Instance->para[4] += Instance->lines[i][j];
         }
         if(Instance->pcount == 5) {
            Instance->para[5] += Instance->lines[i][j];
         }
         if(Instance->pcount == 6) {
            Instance->para[6] += Instance->lines[i][j];
         }
         if(Instance->pcount == 7) {
            Instance->para[7] += Instance->lines[i][j];
         }
         if(Instance->pcount == 8){
            Instance->para[8] += Instance->lines[i][j];
         }
         if(Instance->pcount == 9) {
            Instance->para[9] += Instance->lines[i][j];
         }
         if(Instance->pcount == 10) {
            Instance->para[10] += Instance->lines[i][j];
         }
         if(Instance->pcount == 11) {
            Instance->para[11] += Instance->lines[i][j];
         }
         if(Instance->pcount == 12) {
            Instance->para[12] += Instance->lines[i][j];
         }
         j++;  
      } 
   }
   if(Instance->pcount > 12 || Instance->pcount < 2) {
      Instance->errVec.push_back("Incorrect number of parameters for MULT");
      //error << "Incorrect number of parameters for MULT." << endl;
      Instance->reset();
      return;   
   }
   // calculations
   Instance->check = 0; // use to check if output is NUMERIC or REAL
   // Checking para[0] which is the destination variable
   if(Instance->intVar.count(Instance->para[0]) > 0) {
      Instance->check = 0; // NUMERIC
   } 
   else if(Instance->doubleVar.count(Instance->para[0]) > 0) {
      Instance->check = 1; // REAL
   }
   else {
      Instance->errVec.push_back("Variable has not been declared.");
      //error << "Variable has not been declared." << endl; // print this to the error file 
      Instance->reset();
      return;
   }
   // if the destination is NUMERIC
   if(Instance->check == 0) {
      for(Instance->temp = 1; Instance->temp <= Instance->pcount; Instance->temp++) {
         for(int temp7 = 0; temp7 < Instance->para[Instance->temp].length(); temp7++) {
            if(isdigit(Instance->para[Instance->temp][temp7]) != true && Instance->para[Instance->temp][temp7] != '.' && Instance->para[Instance->temp][temp7] != '-') {
               Instance->digitCheck = 1; 
               break;
            }
            Instance->digitCheck = 0; 
         }
         if(Instance->digitCheck == 0) {
            Instance->MultNUMERIC *= atoi(Instance->para[Instance->temp].c_str()); // converts from string to int
         }
         if(Instance->digitCheck == 1) {
            if(Instance->intVar.count(Instance->para[Instance->temp]) > 0) { 
               Instance->NorR = 0;
            } 
            else if(Instance->doubleVar.count(Instance->para[Instance->temp]) > 0) {
               Instance->NorR = 1;
            }
            else {
               Instance->errVec.push_back("Variable has not been declared.");
               //error << "Variable has not been declared." << endl; // print this to the error file 
               Instance->reset();
               return;
            }                 
            if(Instance->NorR == 0) {
               Instance->MultNUMERIC *= Instance->intVar[Instance->para[Instance->temp]];
            }
            if(Instance->NorR == 1) {
               Instance->MultNUMERIC *= Instance->doubleVar[Instance->para[Instance->temp]];
            }
         }
      }
   }      
   // if the Destination is REAL
   if(Instance->check == 1) {
      for(Instance->temp = 1; Instance->temp <= Instance->pcount; Instance->temp++) {
         for(int temp8 = 0; temp8 < Instance->para[Instance->temp].length(); temp8++) {
            if(isdigit(Instance->para[Instance->temp][temp8]) != true && Instance->para[Instance->temp][temp8] != '.' && Instance->para[Instance->temp][temp8] != '-') {
               Instance->digitCheck = 1; 
               break;
            }
            Instance->digitCheck = 0; 
         }
         if(Instance->digitCheck == 0) {
            Instance->MultREAL *= atof(Instance->para[Instance->temp].c_str()); // converts from string to floating number
         }
         if(Instance->digitCheck == 1) {
            if(Instance->intVar.count(Instance->para[Instance->temp]) > 0) {
               Instance->NorR = 0;
            } 
            else if(Instance->doubleVar.count(Instance->para[Instance->temp]) > 0) {
               Instance->NorR = 1;
            }
            else {
               Instance->errVec.push_back("Variable has not been declared.");
               //error << "Variable has not been declared." << endl; // print this to the error file 
               Instance->reset();
               return;
            }      
            if(Instance->NorR == 0) {
               Instance->MultREAL *= Instance->intVar[Instance->para[Instance->temp]];
            }
            if(Instance->NorR == 1) {
               Instance->MultREAL *= Instance->doubleVar[Instance->para[Instance->temp]];
            }
         }
      }
   }
   if(Instance->check == 0) {
      Instance->intVar.erase(Instance->para[0]);
      Instance->intVar[Instance->para[0]] = Instance->MultNUMERIC;
   }
   if(Instance->check == 1) {
      Instance->doubleVar.erase(Instance->para[0]);
      Instance->doubleVar[Instance->para[0]] = Instance->MultREAL;
   }
   Instance->reset();
}

MULT::~MULT(){
   // Destructor
}


DIV::DIV() {
   // Constructor
}
// Performs DIV instruction
void DIV::DoTask(MISMembers* Instance, int i) {
   using namespace std;
   Instance->reset();
   Instance->j = 0;
   int j = Instance->j;
   // checks for any preceding whitespace/ indentation
   while(true) {
      if(Instance->lines[i][j] == ' ' || Instance->lines[i][j] == '\t' || Instance->lines[i][j] == 'D' || Instance->lines[i][j] == 'I' || Instance->lines[i][j] == 'V') {
         j++;
      }
      else {
         break;   
      }
   }
   // string parsing to get all variables and numeric values
   while (Instance->lines[i][j] != '\0') {
      if (Instance->lines[i][j] == ',') {
         Instance->pcount++;
         j++;
      }
      if(Instance->lines[i][j] == '\"') {
         Instance->quoteCheck = !Instance->quoteCheck;
      }
      if(Instance->lines[i][j] == ' ' && Instance->quoteCheck == false) {
         j++; // Don't include spaces, unless they are part of a String 
      } 
      else {
         if(Instance->pcount == 0) {
            Instance->para[0] += Instance->lines[i][j];
         }
         if(Instance->pcount == 1) {
            Instance->para[1] += Instance->lines[i][j];
         }
         if(Instance->pcount == 2) {
            Instance->para[2] += Instance->lines[i][j];
         }
         j++;
      }
   }
   if(Instance->pcount != 2) {
      Instance->errVec.push_back("Incorrect number of parameters for DIV.");
      //error << "Incorrect number of parameters for DIV." << endl;
      Instance->reset();
      return;   
   }
   // calculations
   Instance->check = 0; // use to check if output is NUMERIC or REAL
   // Checking para[0] which is the destination variable
   if(Instance->intVar.count(Instance->para[0]) > 0) {
      Instance->check = 0; // NUMERIC
   } 
   else if(Instance->doubleVar.count(Instance->para[0]) > 0) {
      Instance->check = 1; // REAL
   }
   else {
      Instance->errVec.push_back("Variable has not been declared.");
      //error << "Variable has not been declared." << endl; // print this to the error file 
      Instance->reset();
      return;
   }
   // if the destination is NUMERIC
   if(Instance->check == 0) {
      for(int temp9 = 0; temp9 < Instance->para[1].length(); temp9++) {
         if(isdigit(Instance->para[1][temp9]) != true && Instance->para[1][temp9] != '.' && Instance->para[1][temp9] != '-') {
            Instance->digitCheck = 1; 
            break;
         }
         Instance->digitCheck = 0; 
      }
      if(Instance->digitCheck == 0) {
         Instance->NUMERIC += atoi(Instance->para[1].c_str()); // converts from string to int
      }
      if(Instance->digitCheck == 1) {
         if(Instance->intVar.count(Instance->para[1]) > 0) { 
            Instance->NorR = 0;
         } 
         else if(Instance->doubleVar.count(Instance->para[1]) > 0) {
            Instance->NorR = 1;
         }
         else {
            Instance->errVec.push_back("Variable has not been declared.");
            //error << "Variable has not been declared." << endl; // print this to the error file 
            Instance->reset();
            return;
         }         
          if(Instance->NorR == 0) {
            Instance->NUMERIC += Instance->intVar[Instance->para[1]];
         }
         if(Instance->NorR == 1) {
            Instance->NUMERIC += Instance->doubleVar[Instance->para[1]];
         }
      }
      for(int temp10 = 0; temp10 < Instance->para[2].length(); temp10++) {
         if(isdigit(Instance->para[2][temp10]) != true && Instance->para[2][temp10] != '.' && Instance->para[2][temp10] != '-') {
            Instance->digitCheck = 1; 
            break;
         }
         Instance->digitCheck = 0; 
      }
      if(Instance->digitCheck == 0) {
         if(atoi(Instance->para[2].c_str()) == 0) {
            Instance->errVec.push_back("Cannot divide by zero.");
            //error << "Cannot divide by zero." << endl;   
            Instance->reset();
            return;
         }
         Instance->NUMERIC /= atoi(Instance->para[2].c_str()); // converts from string to int
      }
      if(Instance->digitCheck == 1) {
         if(Instance->intVar.count(Instance->para[2]) > 0) { 
            Instance->NorR = 0;
         } 
         else if(Instance->doubleVar.count(Instance->para[2]) > 0) {
            Instance->NorR = 1;
         }
         else {
            Instance->errVec.push_back("Variable has not been declared.");
            //error << "Variable has not been declared." << endl; // print this to the error file 
            Instance->reset();
            return;
         }         
         if(Instance->NorR == 0) {
            if(Instance->intVar[Instance->para[2]] == 0) {
               Instance->errVec.push_back("Cannot divide by zero.");
               //error << "Cannot divide by zero." << endl;
               Instance->reset();
               return;
            }
            Instance->NUMERIC /= Instance->intVar[Instance->para[2]];
         }
         if(Instance->NorR == 1) {
            if(Instance->doubleVar[Instance->para[2]] == 0) {
               Instance->errVec.push_back("Cannot divide by zero.");
               //error << "Cannot divide by zero." << endl;;
               Instance->reset();
               return;
            }                  
            Instance->NUMERIC /= Instance->doubleVar[Instance->para[2]];
         }
      }    
   }      
   // if the Destination is REAL
   if(Instance->check == 1) {
      for(int temp11 = 0; temp11 < Instance->para[1].length(); temp11++) {
         if(isdigit(Instance->para[1][temp11]) != true && Instance->para[1][temp11] != '.' && Instance->para[1][temp11] != '-') {
            Instance->digitCheck = 1; 
            break;
         }
         Instance->digitCheck = 0; 
      }
      if(Instance->digitCheck == 0) {
         Instance->REAL += atof(Instance->para[1].c_str()); // converts from string to floating number
      }
      if(Instance->digitCheck == 1) {
         if(Instance->intVar.count(Instance->para[1]) > 0) {
            Instance->NorR = 0;
         } 
         else if(Instance->doubleVar.count(Instance->para[1]) > 0) {
            Instance->NorR = 1;
         }
         else {
            Instance->errVec.push_back("Variable has not been declared.");
            //error << "Variable has not been declared." << endl; // print this to the error file 
            Instance->reset();
            return;
         }                  
         if(Instance->NorR == 0) {
            Instance->REAL += Instance->intVar[Instance->para[1]];
         }
         if(Instance->NorR == 1) {
            Instance->REAL += Instance->doubleVar[Instance->para[1]];
         }
      } 
      for(int temp12 = 0; temp12 < Instance->para[2].length(); temp12++) {
         if(isdigit(Instance->para[2][temp12]) != true && Instance->para[2][temp12] != '.' && Instance->para[2][temp12] != '-') {
            Instance->digitCheck = 1; 
            break;
         }
         Instance->digitCheck = 0; 
      }
      if(Instance->digitCheck == 0) {
         if(atof(Instance->para[2].c_str()) == 0) {
            Instance->errVec.push_back("Cannot divide by zero.");
            //error << "Cannot divide by zero." << endl;   
            Instance->reset();
            return;
         }
         Instance->REAL /= atof(Instance->para[2].c_str()); // converts from string to floating number
      }
      if(Instance->digitCheck == 1) {
         if(Instance->intVar.count(Instance->para[2]) > 0) {
            Instance->NorR = 0;
         } 
         else if(Instance->doubleVar.count(Instance->para[2]) > 0) {
            Instance->NorR = 1;
         }
         else {
            Instance->errVec.push_back("Variable has not been declared.");
            //error << "Variable has not been declared." << endl; // print this to the error file 
            Instance->reset();
            return;
         }                  
         if(Instance->NorR == 0) {
            if(Instance->intVar[Instance->para[2]] == 0) {
               Instance->errVec.push_back("Cannot divide by zero.");
               //error << "Cannot divide by zero." << endl;
               Instance->reset();
               return;
            }  
            Instance->REAL /= Instance->intVar[Instance->para[2]];
         }
         if(Instance->NorR == 1) {
            if(Instance->doubleVar[Instance->para[2]] == 0) {
               Instance->errVec.push_back("Cannot divide by zero.");
               //error << "Cannot divide by zero." << endl;
               Instance->reset();
               return;
            }  
            Instance->REAL /= Instance->doubleVar[Instance->para[2]];
         }
      } 
   }
   if(Instance->check == 0) {
      Instance->intVar.erase(Instance->para[0]);
      Instance->intVar[Instance->para[0]] = Instance->NUMERIC;
   }
   if(Instance->check == 1) {
      Instance->doubleVar.erase(Instance->para[0]);
      Instance->doubleVar[Instance->para[0]] = Instance->REAL;
   }
}

DIV::~DIV() {
   // Destructor
}


JMP::JMP(){
   //Constructor
}
// Performs JMP instruction
int JMP::DoTask(MISMembers* Instance, int i, int j) {
   using namespace std;
   Instance->reset();
   // checks for any preceding whitespace/ indentation
   while(true) {
      if(Instance->lines[i][j] == ' ' || Instance->lines[i][j] == '\t') {
         j++;
      }
      else {
         break;   
      }
   }
   // string parsing to get all variables and numeric values
   while (Instance->lines[i][j] != '\0') {
      if (Instance->lines[i][j] == ',') { // parses paramater at , 
         Instance->pcount++;
         j++;
      }
      if(Instance->lines[i][j] == '\"') {
         Instance->quoteCheck = !Instance->quoteCheck;
      }
      if(Instance->lines[i][j] == ' ' && Instance->quoteCheck == false) {
         j++; // Don't include spaces, unless they are part of a String 
      } 
      else {
         if(Instance->pcount == 0) {
            Instance->para[0] += Instance->lines[i][j]; //adds each parameter to para vector
         }
         j++;
      }
   }
   if(Instance->pcount != 0 && Instance->para[0] == "") {
      Instance->errVec.push_back("Incorrect number of parameters for JMP.");
      //error << "Incorrect number of parameters for JMP." << endl;
      Instance->reset();
      return -1;        
   }
   int x = -1;
   if(Instance->labelVar.count(Instance->para[0]) > 0) {
      x = Instance->labelVar[Instance->para[0]];
   }
   Instance->reset();
   return x;
}

JMP::~JMP(){
   //Destructor
}


JMPZ::JMPZ(){
   //Constructor
}
// Performs JMPZ instruction
int JMPZ::DoTask(MISMembers* Instance, int i, int j) {
   using namespace std;
   Instance->reset();
   // checks for any preceding whitespace/ indentation
   while(true) {
      if(Instance->lines[i][j] == ' ' || Instance->lines[i][j] == '\t') {
         j++;
      }
      else {
         break;   
      }
   }
   // string parsing to get all variables and numeric values
   while (Instance->lines[i][j] != '\0') {
      if (Instance->lines[i][j] == ',') { // parses paramater at , 
         Instance->pcount++;
         j++;
      }
      if(Instance->lines[i][j] == '\"') {
         Instance->quoteCheck = !Instance->quoteCheck;
      }
      if(Instance->lines[i][j] == ' ' && Instance->quoteCheck == false) {
         j++; // Don't include spaces, unless they are part of a String 
      } 
      else {
         if(Instance->pcount == 0) {
            Instance->para[0] += Instance->lines[i][j]; //adds each parameter to para vector
         }
         if(Instance->pcount == 1) {
           Instance->para[1] += Instance->lines[i][j];
         }
         j++;
      }
   }
   if(Instance->pcount != 1) {
      Instance->errVec.push_back("Incorrect number of parameters for JMP.");
      //error << "Incorrect number of parameters for JMP." << endl;
      Instance->reset();
      return -1;        
   }
   int x = -1;
   for(int k = 0; k < Instance->para[1].length(); k++) {
      if(isdigit(Instance->para[1][k]) != true && Instance->para[1][k] != '.' && Instance->para[1][k] != '-') {
         Instance->digitCheck = 1; 
            break;
         }
         Instance->digitCheck = 0; 
      }
   if(Instance->labelVar.count(Instance->para[0]) > 0) {
      if(Instance->digitCheck == 0) {
         if(atoi(Instance->para[1].c_str()) == 0) {
            x = Instance->labelVar[Instance->para[0]];
         }
      }
      if(Instance->digitCheck == 1) {
         if(Instance->intVar.count(Instance->para[1]) > 0) {
            if(Instance->intVar[Instance->para[1]] == 0) {
               x = Instance->labelVar[Instance->para[0]];
            }
         }
         else if(Instance->doubleVar.count(Instance->para[1]) > 0) {
            if(Instance->doubleVar[Instance->para[1]] == 0) {
               x = Instance->labelVar[Instance->para[0]];
            }
         }
         else {
            Instance->errVec.push_back("Label does not exist.");
            //error << "Label does not exist." << endl;
            Instance->reset();
            return -1; 
         }
      }
   }
   else {
      Instance->errVec.push_back("Label does not exist.");
      //error << "Label does not exist." << endl;
      Instance->reset();
      return -1;
   }
   Instance->reset();
   return x;
}

JMPZ::~JMPZ(){
   //Destructor
}

 
JMPNZ::JMPNZ(){
   //Constructor
}
// Performs JMPNZ instruction
int JMPNZ::DoTask(MISMembers* Instance, int i, int j) {
   using namespace std;
   Instance->reset();
   // checks for any preceding whitespace/ indentation
   while(true) {
      if(Instance->lines[i][j] == ' ' || Instance->lines[i][j] == '\t') {
         j++;
      }
      else {
         break;   
      }
   }
   // string parsing to get all variables and numeric values
   while (Instance->lines[i][j] != '\0') {
      if (Instance->lines[i][j] == ',') { // parses paramater at , 
         Instance->pcount++;
         j++;
      }
      if(Instance->lines[i][j] == '\"') {
         Instance->quoteCheck = !Instance->quoteCheck;
      }
      if(Instance->lines[i][j] == ' ' && Instance->quoteCheck == false) {
         j++; // Don't include spaces, unless they are part of a String 
      } 
      else {
         if(Instance->pcount == 0) {
            Instance->para[0] += Instance->lines[i][j]; //adds each parameter to para vector
         }
         if(Instance->pcount == 1) {
           Instance->para[1] += Instance->lines[i][j];
         }
         j++;
      }
   }
   if(Instance->pcount != 1) {
      Instance->errVec.push_back("Incorrect number of parameters for JMP.");
      //error << "Incorrect number of parameters for JMP." << endl;
      Instance->reset();
      return -1;        
   }
   int x = -1;
   for(int k = 0; k < Instance->para[1].length(); k++) {
      if(isdigit(Instance->para[1][k]) != true && Instance->para[1][k] != '.' && Instance->para[1][k] != '-') {
         Instance->digitCheck = 1; 
            break;
         }
         Instance->digitCheck = 0; 
      }
   if(Instance->labelVar.count(Instance->para[0]) > 0) {
      if(Instance->digitCheck == 0) {
         if(atoi(Instance->para[1].c_str()) != 0) {
            x = Instance->labelVar[Instance->para[0]];
         }
      }
      if(Instance->digitCheck == 1) {
         if(Instance->intVar.count(Instance->para[1]) > 0) {
            if(Instance->intVar[Instance->para[1]] != 0) {
               x = Instance->labelVar[Instance->para[0]];
            }
         }
         else if(Instance->doubleVar.count(Instance->para[1]) > 0) {
            if(Instance->doubleVar[Instance->para[1]] != 0) {
               x = Instance->labelVar[Instance->para[0]];
            }
         }
         else {
            Instance->errVec.push_back("Variable does not exist.");
            //error << "Variable does not exist." << endl;
            Instance->reset();
            return -1; 
         }
      }
   }
   else {
      Instance->errVec.push_back("Label does not exist.");
      //error << "Label does not exist." << endl;
      Instance->reset();
      return -1;
   }
   Instance->reset();
   return x;
}

JMPNZ::~JMPNZ(){
   //Destructor
}


JMPGT::JMPGT(){
   //Constructor
}
// Performs JMPGT instruction
int JMPGT::DoTask(MISMembers* Instance, int i, int j) {
   using namespace std;
   Instance->reset();
   // checks for any preceding whitespace/ indentation
   while(true) {
      if(Instance->lines[i][j] == ' ' || Instance->lines[i][j] == '\t') {
         j++;
      }
      else {
         break;   
      }
   }
   // string parsing to get all variables and numeric values
   while (Instance->lines[i][j] != '\0') {
      if (Instance->lines[i][j] == ',') { // parses paramater at , 
         Instance->pcount++;
         j++;
      }
      if(Instance->lines[i][j] == '\"') {
         Instance->quoteCheck = !Instance->quoteCheck;
      }
      if(Instance->lines[i][j] == ' ' && Instance->quoteCheck == false) {
         j++; // Don't include spaces, unless they are part of a String 
      } 
      else {
         if(Instance->pcount == 0) {
            Instance->para[0] += Instance->lines[i][j]; //adds each parameter to para vector
         }
         if(Instance->pcount == 1) {
           Instance->para[1] += Instance->lines[i][j];
         }
         if(Instance->pcount == 2) {
            Instance->para[2] += Instance->lines[i][j];
         }
         j++;
      }
   }
   if(Instance->pcount != 2) {
      Instance->errVec.push_back("Incorrect number of parameters for JMPGT.");
      //error << "Incorrect number of parameters for JMP." << endl;
      Instance->reset();
      return -1;        
   }
   int x = -1;
   double p1, p2;
   for(int k = 0; k < Instance->para[1].length(); k++) {
      if(isdigit(Instance->para[1][k]) != true && Instance->para[1][k] != '.' && Instance->para[1][k] != '-') {
         Instance->digitCheck = 1; 
            break;
         }
      Instance->digitCheck = 0; 
   }
   for(int l = 0; l < Instance->para[2].length(); l++) {
      if(isdigit(Instance->para[2][l]) != true && Instance->para[2][l] != '.' && Instance->para[2][l] != '-') {
         Instance->check = 1; 
            break;
         }
      Instance->check = 0; 
   }
   if(Instance->labelVar.count(Instance->para[0]) > 0) {
      if(Instance->digitCheck == 0) {
         p1 = atof(Instance->para[1].c_str());
      }
      if(Instance->digitCheck == 1) {
         if(Instance->intVar.count(Instance->para[1]) > 0) {
            p1 = Instance->intVar[Instance->para[1]];
         }
         else if(Instance->doubleVar.count(Instance->para[1]) > 0) {
            p1 = Instance->doubleVar[Instance->para[1]];
         }
         else {
            Instance->errVec.push_back("Variable does not exist.");
            //error << "Variable does not exist." << endl;
            Instance->reset();
            return -1; 
         }      
      }
      if(Instance->check == 0) {
         p2 = atof(Instance->para[2].c_str());
      }
      if(Instance->check == 1) {
         if(Instance->intVar.count(Instance->para[2]) > 0) {
            p2 = Instance->intVar[Instance->para[2]];
         }
         else if(Instance->doubleVar.count(Instance->para[2]) > 0) {
            p2 = Instance->doubleVar[Instance->para[2]];
         }
         else {
            Instance->errVec.push_back("Variable does not exist.");
            //error << "Variable does not exist." << endl;
            Instance->reset();
            return -1; 
         }      
      }
   }
   else {
      Instance->errVec.push_back("Variable does not exist.");
      //error << "Label does not exist." << endl;
      Instance->reset();
      return -1;
   }
   if(p1 > p2) {
      x = Instance->labelVar[Instance->para[0]];
   }
   Instance->reset();
   return x; 
}

JMPGT::~JMPGT(){
   //Destructor
}


JMPLT::JMPLT(){
   //Constructor
}
// Performs JMPLT instruction
int JMPLT::DoTask(MISMembers* Instance, int i, int j) {
   using namespace std;
   Instance->reset();
   // checks for any preceding whitespace/ indentation
   while(true) {
      if(Instance->lines[i][j] == ' ' || Instance->lines[i][j] == '\t') {
         j++;
      }
      else {
         break;   
      }
   }
   // string parsing to get all variables and numeric values
   while (Instance->lines[i][j] != '\0') {
      if (Instance->lines[i][j] == ',') { // parses paramater at , 
         Instance->pcount++;
         j++;
      }
      if(Instance->lines[i][j] == '\"') {
         Instance->quoteCheck = !Instance->quoteCheck;
      }
      if(Instance->lines[i][j] == ' ' && Instance->quoteCheck == false) {
         j++; // Don't include spaces, unless they are part of a String 
      } 
      else {
         if(Instance->pcount == 0) {
            Instance->para[0] += Instance->lines[i][j]; //adds each parameter to para vector
         }
         if(Instance->pcount == 1) {
           Instance->para[1] += Instance->lines[i][j];
         }
         if(Instance->pcount == 2) {
            Instance->para[2] += Instance->lines[i][j];
         }
         j++;
      }
   }
   if(Instance->pcount != 2) {
      Instance->errVec.push_back("Incorrect number of parameters for JMP.");
      //error << "Incorrect number of parameters for JMP." << endl;
      Instance->reset();
      return -1;        
   }
   int x = -1;
   double p1, p2;
   for(int k = 0; k < Instance->para[1].length(); k++) {
      if(isdigit(Instance->para[1][k]) != true && Instance->para[1][k] != '.' && Instance->para[1][k] != '-') {
         Instance->digitCheck = 1; 
            break;
         }
      Instance->digitCheck = 0; 
   }
   for(int l = 0; l < Instance->para[2].length(); l++) {
      if(isdigit(Instance->para[2][l]) != true && Instance->para[2][l] != '.' && Instance->para[2][l] != '-') {
         Instance->check = 1; 
            break;
         }
      Instance->check = 0; 
   }
   if(Instance->labelVar.count(Instance->para[0]) > 0) {
      if(Instance->digitCheck == 0) {
         p1 = atof(Instance->para[1].c_str());
      }
      if(Instance->digitCheck == 1) {
         if(Instance->intVar.count(Instance->para[1]) > 0) {
            p1 = Instance->intVar[Instance->para[1]];
         }
         else if(Instance->doubleVar.count(Instance->para[1]) > 0) {
            p1 = Instance->doubleVar[Instance->para[1]];
         }
         else {
            Instance->errVec.push_back("Variable does not exist.");
            //error << "Variable does not exist." << endl;
            Instance->reset();
            return -1; 
         }      
      }
      if(Instance->check == 0) {
         p2 = atof(Instance->para[2].c_str());
      }
      if(Instance->check == 1) {
         if(Instance->intVar.count(Instance->para[2]) > 0) {
            p2 = Instance->intVar[Instance->para[2]];
         }
         else if(Instance->doubleVar.count(Instance->para[2]) > 0) {
            p2 = Instance->doubleVar[Instance->para[2]];
         }
         else {
            Instance->errVec.push_back("Variable does not exist.");
            //error << "Variable does not exist." << endl;
            Instance->reset();
            return -1; 
         }      
      }
   }
   else {
      Instance->errVec.push_back("Variable does not exist.");
      //error << "Label does not exist." << endl;
      Instance->reset();
      return -1;
   }
   if(p1 < p2) {
      x = Instance->labelVar[Instance->para[0]];
   }
   Instance->reset();
   return x;
}

JMPLT::~JMPLT(){
   //Destructor
}


JMPGTE::JMPGTE(){
   //Constructor
}
// Performs JMPGTE instruction
int JMPGTE::DoTask(MISMembers* Instance, int i, int j) {
   using namespace std;
   Instance->reset();
   // checks for any preceding whitespace/ indentation
   while(true) {
      if(Instance->lines[i][j] == ' ' || Instance->lines[i][j] == '\t') {
         j++;
      }
      else {
         break;   
      }
   }
   // string parsing to get all variables and numeric values
   while (Instance->lines[i][j] != '\0') {
      if (Instance->lines[i][j] == ',') { // parses paramater at , 
         Instance->pcount++;
         j++;
      }
      if(Instance->lines[i][j] == '\"') {
         Instance->quoteCheck = !Instance->quoteCheck;
      }
      if(Instance->lines[i][j] == ' ' && Instance->quoteCheck == false) {
         j++; // Don't include spaces, unless they are part of a String 
      } 
      else {
         if(Instance->pcount == 0) {
            Instance->para[0] += Instance->lines[i][j]; //adds each parameter to para vector
         }
         if(Instance->pcount == 1) {
           Instance->para[1] += Instance->lines[i][j];
         }
         if(Instance->pcount == 2) {
            Instance->para[2] += Instance->lines[i][j];
         }
         j++;
      }
   }
   if(Instance->pcount != 2) {
      Instance->errVec.push_back("Incorrect number of parameters for JMP.");
      //error << "Incorrect number of parameters for JMP." << endl;
      Instance->reset();
      return -1;        
   }
   int x = -1;
   double p1, p2;
   for(int k = 0; k < Instance->para[1].length(); k++) {
      if(isdigit(Instance->para[1][k]) != true && Instance->para[1][k] != '.' && Instance->para[1][k] != '-') {
         Instance->digitCheck = 1; 
            break;
         }
      Instance->digitCheck = 0; 
   }
   for(int l = 0; l < Instance->para[2].length(); l++) {
      if(isdigit(Instance->para[2][l]) != true && Instance->para[2][l] != '.' && Instance->para[2][l] != '-') {
         Instance->check = 1; 
            break;
         }
      Instance->check = 0; 
   }
   if(Instance->labelVar.count(Instance->para[0]) > 0) {
      if(Instance->digitCheck == 0) {
         p1 = atof(Instance->para[1].c_str());
      }
      if(Instance->digitCheck == 1) {
         if(Instance->intVar.count(Instance->para[1]) > 0) {
            p1 = Instance->intVar[Instance->para[1]];
         }
         else if(Instance->doubleVar.count(Instance->para[1]) > 0) {
            p1 = Instance->doubleVar[Instance->para[1]];
         }
         else {
            Instance->errVec.push_back("Variable does not exist.");
            //error << "Variable does not exist." << endl;
            Instance->reset();
            return -1; 
         }      
      }
      if(Instance->check == 0) {
         p2 = atof(Instance->para[2].c_str());
      }
      if(Instance->check == 1) {
         if(Instance->intVar.count(Instance->para[2]) > 0) {
            p2 = Instance->intVar[Instance->para[2]];
         }
         else if(Instance->doubleVar.count(Instance->para[2]) > 0) {
            p2 = Instance->doubleVar[Instance->para[2]];
         }
         else {
            Instance->errVec.push_back("Variable does not exist.");
            //error << "Variable does not exist." << endl;
            Instance->reset();
            return -1; 
         }      
      }
   }
   else {
      Instance->errVec.push_back("Label does not exist.");
      //error << "Label does not exist." << endl;
      Instance->reset();
      return -1;
   }
   if(p1 > p2 || p1 == p2) {
      x = Instance->labelVar[Instance->para[0]];
   }
   Instance->reset();
   return x;
}

JMPGTE::~JMPGTE(){
   //Destructor
}


JMPLTE::JMPLTE(){
   //Constructor
}
// Performs JMPLTE instruction
int JMPLTE::DoTask(MISMembers* Instance, int i, int j) {
   using namespace std;
   Instance->reset();
   // checks for any preceding whitespace/ indentation
   while(true) {
      if(Instance->lines[i][j] == ' ' || Instance->lines[i][j] == '\t') {
         j++;
      }
      else {
         break;   
      }
   }
   // string parsing to get all variables and numeric values
   while (Instance->lines[i][j] != '\0') {
      if (Instance->lines[i][j] == ',') { // parses paramater at , 
         Instance->pcount++;
         j++;
      }
      if(Instance->lines[i][j] == '\"') {
         Instance->quoteCheck = !Instance->quoteCheck;
      }
      if(Instance->lines[i][j] == ' ' && Instance->quoteCheck == false) {
         j++; // Don't include spaces, unless they are part of a String 
      } 
      else {
         if(Instance->pcount == 0) {
            Instance->para[0] += Instance->lines[i][j]; //adds each parameter to para vector
         }
         if(Instance->pcount == 1) {
           Instance->para[1] += Instance->lines[i][j];
         }
         if(Instance->pcount == 2) {
            Instance->para[2] += Instance->lines[i][j];
         }
         j++;
      }
   }
   if(Instance->pcount != 2) {
      Instance->errVec.push_back("Incorrect number of parameters for JMP.");
      //error << "Incorrect number of parameters for JMP." << endl;
      Instance->reset();
      return -1;        
   }
   int x = -1;
   double p1, p2;
   for(int k = 0; k < Instance->para[1].length(); k++) {
      if(isdigit(Instance->para[1][k]) != true && Instance->para[1][k] != '.' && Instance->para[1][k] != '-') {
         Instance->digitCheck = 1; 
            break;
         }
      Instance->digitCheck = 0; 
   }
   for(int l = 0; l < Instance->para[2].length(); l++) {
      if(isdigit(Instance->para[2][l]) != true && Instance->para[2][l] != '.' && Instance->para[2][l] != '-') {
         Instance->check = 1; 
            break;
         }
      Instance->check = 0; 
   }
   if(Instance->labelVar.count(Instance->para[0]) > 0) {
      if(Instance->digitCheck == 0) {
         p1 = atof(Instance->para[1].c_str());
      }
      if(Instance->digitCheck == 1) {
         if(Instance->intVar.count(Instance->para[1]) > 0) {
            p1 = Instance->intVar[Instance->para[1]];
         }
         else if(Instance->doubleVar.count(Instance->para[1]) > 0) {
            p1 = Instance->doubleVar[Instance->para[1]];
         }
         else {
            Instance->errVec.push_back("Variable does not exist.");
            //error << "Variable does not exist." << endl;
            Instance->reset();
            return -1; 
         }      
      }
      if(Instance->check == 0) {
         p2 = atof(Instance->para[2].c_str());
      }
      if(Instance->check == 1) {
         if(Instance->intVar.count(Instance->para[2]) > 0) {
            p2 = Instance->intVar[Instance->para[2]];
         }
         else if(Instance->doubleVar.count(Instance->para[2]) > 0) {
            p2 = Instance->doubleVar[Instance->para[2]];
         }
         else {
            Instance->errVec.push_back("Variable does not exist.");
            //error << "Variable does not exist." << endl;
            Instance->reset();
            return -1; 
         }      
      }
   }
   else {
      Instance->errVec.push_back("Label does not exist.");
      //error << "Label does not exist." << endl;
      Instance->reset();
      return -1;
   }
   if(p1 < p2 || p1 == p2) {
      x = Instance->labelVar[Instance->para[0]];
   }
   Instance->reset();
   return x;
}

JMPLTE::~JMPLTE(){
   //Destructor
}


ASSIGN::ASSIGN() {
   //Constructor
}
// Performs ASSIGN instruction
void ASSIGN::DoTask(MISMembers* Instance, int i) {
   using namespace std;
   Instance->reset();
   Instance->j = 0;
   int j = Instance->j;
   // checks for any preceding whitespace/ indentation
   while(true) {
      if(Instance->lines[i][j] == ' ' || Instance->lines[i][j] == '\t' || Instance->lines[i][j] == 'A' || Instance->lines[i][j] == 'S' || Instance->lines[i][j] == 'S' || Instance->lines[i][j] == 'I' || Instance->lines[i][j] == 'G' || Instance->lines[i][j] == 'N') {
         j++;
      }
      else {
         break;   
      }
   }
   // string parsing to get all variables and numeric values
   while (Instance->lines[i][j] != '\0') {
      if (Instance->lines[i][j] == ',') { // parses paramater at , 
         Instance->pcount++;
         j++;
      }
      if(Instance->lines[i][j] == '\"') {
         Instance->quoteCheck = !Instance->quoteCheck;
      }
      if(Instance->lines[i][j] == ' ' && Instance->quoteCheck == false) {
         j++; // Don't include spaces, unless they are part of a String 
      } 
      else {
         if(Instance->pcount == 0) {
            Instance->para[0] += Instance->lines[i][j]; //adds each parameter to para vector
         }
         if(Instance->pcount == 1) {
           Instance->para[1] += Instance->lines[i][j];
         }
         j++;
      }
   }
   if(Instance->pcount != 1) {
      Instance->errVec.push_back("Incorrect number of parameters for ASSIGN.");
      //error << "Incorrect number of parameters for ASSIGN." << endl;
      Instance->reset();
      return;        
   }
   if(Instance->intVar.count(Instance->para[0]) > 0) {
      for(int tempIA = 0; tempIA < Instance->para[1].length(); tempIA++) {
         if(isdigit(Instance->para[1][tempIA]) != true && Instance->para[1][tempIA] != '-') {
            Instance->digitCheck = 1;
            break; 
         }
         Instance->digitCheck = 0;      
      }
      if(Instance->digitCheck == 0) {
         Instance->NUMERIC += atoi(Instance->para[1].c_str()); // converts from string to int
      }
      else if(Instance->digitCheck == 1 && (Instance->intVar.count(Instance->para[1]) > 0)) {
         Instance->NUMERIC += Instance->intVar[Instance->para[1]];
      }
      else {
         Instance->errVec.push_back("Must ASSIGN NUMERIC VAR to NUMERIC VAR.");
         //error << "Must ASSIGN NUMERIC VAR to NUMERIC VAR" << endl; // print this to the error file 
         Instance->reset();
         return;
      }                  
      Instance->intVar.erase(Instance->para[0]);
      Instance->intVar[Instance->para[0]] = Instance->NUMERIC;
   } 
   else if(Instance->doubleVar.count(Instance->para[0]) > 0) {
      for(int tempFA = 0; tempFA < Instance->para[1].length(); tempFA++) {
         if(isdigit(Instance->para[1][tempFA]) != true && Instance->para[1][tempFA] != '.' && Instance->para[1][tempFA] != '-') {
            Instance->digitCheck = 1;
            break; 
         }
         Instance->digitCheck = 0;      
      }
      if(Instance->digitCheck == 0) {
         Instance->REAL += atof(Instance->para[1].c_str()); // converts from string to int
      }
      else if(Instance->digitCheck == 1 && (Instance->doubleVar.count(Instance->para[1]) > 0)) {
         Instance->REAL += Instance->intVar[Instance->para[1]];
      }      
      else {
         Instance->errVec.push_back("Must ASSIGN REAL VAR to REAL VAR.");
         //error << "Must ASSIGN REAL VAR to REAL VAR." << endl; // print this to the error file 
         Instance->reset();
         return;
      }                  
      Instance->doubleVar.erase(Instance->para[0]);
      Instance->doubleVar[Instance->para[0]] = Instance->REAL;
   }
   else if(Instance->charVar.count(Instance->para[0]) > 0) {
      if(Instance->charVar.count(Instance->para[1]) > 0) {
         Instance->charVar[Instance->para[0]] = Instance->charVar[Instance->para[1]];         
      }
      else {
         char nl = '\\';
         if(Instance->para[2][0] != '\'' && Instance->para[2][2] != '\'' ) {
            Instance->errVec.push_back("Incorrect Char syntax.");
            //error << "Incorrect Char syntax." << endl;
            Instance->reset();
            return;
         }
         if(Instance->para[1].length() != 3 && Instance->para[1].length() != 4) {
            Instance->errVec.push_back("Incorrect Char syntax.");
            //error << "Incorrect Char syntax." << endl;
            Instance->reset();
            return;              
         }
         // check all the C++ Character Literals
         if(Instance->para[1].length() == 4) {
            if(Instance->para[1][1] == nl && Instance->para[1][2] == 'n') {
               Instance->CHAR = '\n';
               Instance->charVar[Instance->para[0]] = Instance->CHAR;
               Instance->reset();
               return;
            }
            else if(Instance->para[1][1] == nl && Instance->para[1][2] == 't') {
               Instance->CHAR = '\t';
               Instance->charVar[Instance->para[0]] = Instance->CHAR;
               Instance->reset();
               return;
            }
            else if(Instance->para[1][1] == nl && Instance->para[1][2] == 'v') {
               Instance->CHAR = '\v';
               Instance->charVar[Instance->para[0]] = Instance->CHAR;
               Instance->reset();
               return;
            }
            else if(Instance->para[1][1] == nl && Instance->para[1][2] == 'b') {
               Instance->CHAR = '\b';
               Instance->charVar[Instance->para[0]] = Instance->CHAR;
               Instance->reset();
               return;
            }
            else if(Instance->para[1][1] == nl && Instance->para[1][2] == 'r') {
               Instance->CHAR = '\r';
               Instance->charVar[Instance->para[0]] = Instance->CHAR;
               Instance->reset();
               return;
            }
            else if(Instance->para[1][1] == nl && Instance->para[1][2] == 'f') {
               Instance->CHAR = '\f';
               Instance->charVar[Instance->para[0]] = Instance->CHAR;
               Instance->reset();
               return;
            }
            else if(Instance->para[1][1] == nl && Instance->para[1][2] == 'a') {
               Instance->CHAR = '\a';
               Instance->charVar[Instance->para[0]] = Instance->CHAR;
               Instance->reset();
               return;
            }
            else if(Instance->para[1][1] == nl && Instance->para[1][2] == nl) {
               Instance->CHAR = '\\';
               Instance->charVar[Instance->para[0]] = Instance->CHAR;
               Instance->reset();
               return;
            }
            else if(Instance->para[1][1] == nl && Instance->para[1][2] == '?') {
               Instance->CHAR = '\?';
               Instance->charVar[Instance->para[0]] = Instance->CHAR;
               Instance->reset();
               return;
            }
            else if(Instance->para[1][1] == nl && Instance->para[1][2] == '\'') {
               Instance->CHAR = '\'';
               Instance->charVar[Instance->para[0]] = Instance->CHAR;
               Instance->reset();
               return;
            }
            else if(Instance->para[1][1] == nl && Instance->para[1][2] == '\"') {
               Instance->CHAR = '\"';
               Instance->charVar[Instance->para[0]] = Instance->CHAR;
               Instance->reset();
               return;
            }
            else if(Instance->para[1][1] == nl && Instance->para[1][2] == '0') {
               Instance->CHAR = '\0';
               Instance->charVar[Instance->para[0]] = Instance->CHAR;
               Instance->reset();
               return;
            }
            else {
               Instance->errVec.push_back("Incorrect Char syntax.");
               //error << "Incorrect Char syntax." << endl;;
               Instance->reset();
               return;                  
            }
         }
         Instance->CHAR = Instance->para[1][1];
         Instance->charVar[Instance->para[0]] = Instance->CHAR;
      }   
   }
   else if(Instance->stringVar.count(Instance->para[0]) > 0) {
      if(Instance->stringVar.count(Instance->para[1]) > 0) {
         Instance->stringVar[Instance->para[0]] = Instance->para[1];
      }
      else if(Instance->para[1][0] == '\"' && Instance->para[1][Instance->para[1].length()-1] == '\"') {
         for(int tempSA = 1; tempSA < Instance->para[3].length()-1; tempSA++) {
            Instance->STRING += Instance->para[1][tempSA];
         }
      Instance->stringVar[Instance->para[0]] = Instance->STRING;
      } 
      else {
         Instance->errVec.push_back("Variable has not been declared..");
         //error << "Variable has not been declared." << endl; // print this to the error file 
         Instance->reset();
         return;
      }
   }
   Instance->reset();
}

ASSIGN::~ASSIGN() {
   // Destructor
}


OUT::OUT() {
   // Constructor
}
// Performs OUT instruction
void OUT::DoTask(MISMembers* Instance, int i) {
   using namespace std;
   Instance->reset();
   Instance->j = 0;
   string temporary;
   int j = Instance->j;
   //cout << "made it here";
   // checks for any preceding whitespace/ indentation
   while(true) {
      if(Instance->lines[i][j] == ' ' || Instance->lines[i][j] == '\t' || Instance->lines[i][j] == 'O' || Instance->lines[i][j] == 'U' || Instance->lines[i][j] == 'T') {
         j++;
      }
      else {
         break;   
      }
   }
   // string parsing to get all variables and numeric values
   while (Instance->lines[i][j] != '\0') {
      if (Instance->lines[i][j] == ',') {
         Instance->pcount++;
         j++;
      }
      if(Instance->lines[i][j] == '\"') {
         Instance->quoteCheck = !Instance->quoteCheck;
      }
      if(Instance->lines[i][j] == ' ' && Instance->quoteCheck == false) {
         j++; // Don't include spaces, unless they are part of a String 
      } 
      else {
         if(Instance->pcount == 0) {
            Instance->para[0] += Instance->lines[i][j];
         }
         if(Instance->pcount == 1) {
            Instance->para[1] += Instance->lines[i][j];
         }
         if(Instance->pcount == 2) {
            Instance->para[2] += Instance->lines[i][j];
         }
         if(Instance->pcount == 3) {
            Instance->para[3] += Instance->lines[i][j];
         }
         if(Instance->pcount == 4) {
            Instance->para[4] += Instance->lines[i][j];
         }
         if(Instance->pcount == 5) {
            Instance->para[5] += Instance->lines[i][j];
         }
         if(Instance->pcount == 6) {
            Instance->para[6] += Instance->lines[i][j];
         }
         if(Instance->pcount == 7) {
            Instance->para[7] += Instance->lines[i][j];
         }
         if(Instance->pcount == 8){
            Instance->para[8] += Instance->lines[i][j];
         }
         if(Instance->pcount == 9) {
            Instance->para[9] += Instance->lines[i][j];
         }
         if(Instance->pcount == 10) {
            Instance->para[10] += Instance->lines[i][j];
         }
         if(Instance->pcount == 11) {
            Instance->para[11] += Instance->lines[i][j];
         }
         j++;   
      }
   }
   if(Instance->pcount > 11 || Instance->para[0] == "") {
      Instance->errVec.push_back("Incorrect number of parameters for OUT.");
      //error << "Incorrect number of parameters for OUT." << endl;
      Instance->reset();
      return;   
   }
   Instance->check = 0;
   for(int tempO = 0; tempO <= Instance->pcount; tempO++) {
      for(int tempP = 0; tempP < Instance->para[tempO].length(); tempP++) {
         if(isdigit(Instance->para[tempO][tempP]) != true && Instance->para[tempO][tempP] != '.' && Instance->para[tempO][tempP] != '-') {
            Instance->check = 1;
            break;
         }
         Instance->check = 0;
      }
      if(Instance->check == 0) {
         for(int tempD = 0; tempD < Instance->para[tempO].length(); tempD++) {
            if(isdigit(Instance->para[tempO][tempD]) != true && Instance->para[tempO][tempD] != '-') { // check if its floating point or integer
               Instance->digitCheck = 1;
               break;
            }
            Instance->digitCheck = 0;
         }
         if(Instance->digitCheck == 0) {
            temporary = Instance->para[tempO].c_str();
            Instance->outVec.push_back(temporary);
            //Instance->outVec.push_back(atoi(Instance->para[tempO].c_str()));
            //out << atoi(Instance->para[tempO].c_str()) << endl;
         }
         if(Instance->digitCheck == 1) {
            Instance->outVec.push_back(Instance->para[tempO].c_str());
            //out << atof(Instance->para[tempO].c_str()) << endl;
         }
      } 
      if(Instance->check == 1) {
         if(Instance->intVar.count(Instance->para[tempO]) > 0) {
            temporary = to_string(Instance->intVar[Instance->para[tempO]]);
            Instance->outVec.push_back(temporary);
            //out << Instance->intVar[Instance->para[tempO]] << endl;
         }
         else if(Instance->doubleVar.count(Instance->para[tempO]) > 0) {
            Instance->outVec.push_back(to_string(Instance->doubleVar[Instance->para[tempO]]));
            //out << Instance->doubleVar[Instance->para[tempO]] << endl;
         }      
         else if(Instance->charVar.count(Instance->para[tempO]) > 0) {
            Instance->outVec.push_back(to_string(Instance->charVar[Instance->para[tempO]]));
            //out << Instance->charVar[Instance->para[tempO]] << endl;
         }
         else if(Instance->stringVar.count(Instance->para[tempO]) > 0) {
            Instance->outVec.push_back(Instance->stringVar[Instance->para[tempO]]);
            //out << Instance->stringVar[Instance->para[tempO]] << endl;
         }      
         else if(Instance->para[tempO][0] == '\'' && Instance->para[tempO][Instance->para[tempO].length()-1] == '\'') {
            char nl = '\\';
            if(Instance->para[tempO][0] != '\'' && Instance->para[tempO][2] != '\'' ) {
               Instance->errVec.push_back("Incorrect Char syntax.");
               //error << "Incorrect Char syntax." << endl;
               continue;
            }
            if(Instance->para[tempO].length() != 3 && Instance->para[tempO].length() != 4) {
               Instance->errVec.push_back("Incorrect Char syntax.");
               //error << "Incorrect Char syntax." << endl; 
               continue;             
            }
            // check all the C++ Character Literals
            if(Instance->para[tempO].length() == 4) {
               if(Instance->para[tempO][1] == nl && Instance->para[tempO][2] == 'n') {
                  Instance->CHAR = '\n';
                  Instance->outVec.push_back(to_string(Instance->CHAR));
                  //out << Instance->CHAR << endl;
               }
               else if(Instance->para[tempO][1] == nl && Instance->para[tempO][2] == 't') {
                  Instance->CHAR = '\t';
                  Instance->outVec.push_back(to_string(Instance->CHAR));
                  //out << Instance->CHAR << endl;
               }
               else if(Instance->para[tempO][1] == nl && Instance->para[tempO][2] == 'v') {
                  Instance->CHAR = '\v';
                  Instance->outVec.push_back(to_string(Instance->CHAR));
                  //out << Instance->CHAR << endl;
               }
               else if(Instance->para[tempO][1] == nl && Instance->para[tempO][2] == 'b') {
                  Instance->CHAR = '\b';
                  Instance->outVec.push_back(to_string(Instance->CHAR));
                  //out << Instance->CHAR << endl;   
               }
               else if(Instance->para[tempO][1] == nl && Instance->para[tempO][2] == 'r') {
                  Instance->CHAR = '\r';
                  Instance->outVec.push_back(to_string(Instance->CHAR));
                  //out << Instance->CHAR << endl;   
               }
               else if(Instance->para[tempO][1] == nl && Instance->para[tempO][2] == 'f') {
                  Instance->CHAR = '\f';
                  Instance->outVec.push_back(to_string(Instance->CHAR));
                  //out << Instance->CHAR << endl;   
               }
               else if(Instance->para[tempO][1] == nl && Instance->para[tempO][2] == 'a') {
                  Instance->CHAR = '\a';
                  Instance->outVec.push_back(to_string(Instance->CHAR));
                  //out << Instance->CHAR << endl;   
               }
               else if(Instance->para[tempO][1] == nl && Instance->para[tempO][2] == nl) {
                  Instance->CHAR = '\\';
                  Instance->outVec.push_back(to_string(Instance->CHAR));
                  //out << Instance->CHAR << endl;   
               }
               else if(Instance->para[2][1] == nl && Instance->para[tempO][2] == '?') {
                  Instance->CHAR = '\?';
                  Instance->outVec.push_back(to_string(Instance->CHAR));
                  //out << Instance->CHAR << endl;   
               }
               else if(Instance->para[tempO][1] == nl && Instance->para[tempO][2] == '\'') {
                  Instance->CHAR = '\'';
                  Instance->outVec.push_back(to_string(Instance->CHAR));
                  //out << Instance->CHAR << endl;   
               }
               else if(Instance->para[tempO][1] == nl && Instance->para[tempO][2] == '\"') {
                  Instance->CHAR = '\"';
                  Instance->outVec.push_back(to_string(Instance->CHAR));
                  //out << Instance->CHAR << endl;   
               }
               else if(Instance->para[tempO][1] == nl && Instance->para[tempO][2] == '0') {
                  Instance->CHAR = '\0';
                  Instance->outVec.push_back(to_string(Instance->CHAR));
                  //out << Instance->CHAR << endl;   
               }
               else {
                  Instance->errVec.push_back("Incorrect Char syntax.");
                  //error << "Incorrect Char syntax." << endl;;                
               }
            }
            if(Instance->para[tempO].length() == 3) {
               Instance->CHAR = Instance->para[tempO][1];
               Instance->outVec.push_back(to_string(Instance->CHAR));
               //out << Instance->CHAR << endl;   
            }
         }
         else if(Instance->para[tempO][0] == '\"' && Instance->para[tempO][Instance->para[tempO].length()-1] == '\"') {
            Instance->STRING = "";
            for(int x = 1; x < Instance->para[tempO].length()-1; x++) {
               Instance->STRING += Instance->para[tempO][x];
            }
            Instance->outVec.push_back(Instance->STRING);
            //out << Instance->STRING << endl;
         }
         else {
            Instance->errVec.push_back("Incorrect OUT parameter.");
            //error << "Invalid OUT parameter." << endl;
         }
      } // check == 1;
   } // for loop
   Instance->reset(); 
}

OUT::~OUT() {
   // Destructor
}


SLEEP::SLEEP() {
   // Constructor
}
// Performs SLEEP instruction
void SLEEP::DoTask(MISMembers* Instance, int i) {
   using namespace std;
   Instance->j = 6;
   double temp_num = 0;
   while (Instance->lines[i][Instance->j] != '\0') {
      if (Instance->lines[i][Instance->j] == ',') {
         Instance->pcount++;
         Instance->j++;
      }
      if(Instance->pcount == 0) {
         Instance->para[0] += Instance->lines[i][Instance->j];
      }
      Instance->j++;
            //if(pcount == 1) {
               //para[1] += lines[i][j];
            //}
         //}
   }
      if (isdigit(Instance->para[0][0]) == false){
          //cout << " why is it here?" << endl;
         if(Instance->intVar.count(Instance->para[0]) > 0) {
            temp_num = Instance->intVar[Instance->para[0]];
            Instance->check = 0; // NUMERIC
         } 
         else if(Instance->doubleVar.count(Instance->para[0]) > 0) {
            temp_num = Instance->doubleVar[Instance->para[0]];
            Instance->check = 1; // REAL
         }
         else {
            Instance->errVec.push_back("Variable has not been declared.");
            //printf("Variable has not been declared.\n"); // print this to the error file 
            Instance->reset();
            return; // go to main for loop
         }
            //temp_num = intVar[para[1]];
      }
      else{
          //cout << "here?" << endl;
         temp_num = atof(Instance->para[0].c_str());
      }
         //para[0] = lines[i][7];
         //temp_num = atoi(para[0].c_str());
      //cout << "temp_num " << temp_num << endl;
         //if (lines[i][6] == '$'){  // its a variable
      double million = 1000000;
      int total = temp_num*million;
      usleep(total);
}

SLEEP::~SLEEP() {
   // Destructor
}

GET_STR_CHAR::GET_STR_CHAR(){
   // Constructor
}
// Performs GET_STR_CHAR instruction
void GET_STR_CHAR::DoTask(MISMembers* Instance, int i){
   using namespace std;
   Instance->j = 13;
   Instance->pcount = 0;

   while (Instance->lines[i][Instance->j] != '\0') {
      if (Instance->lines[i][Instance->j] == ',') {
         Instance->pcount++;
         Instance->j++;
      }
      if(Instance->pcount == 0) {
         Instance->para[0] += Instance->lines[i][Instance->j];
      }
      if(Instance->pcount == 1) {
         Instance->para[1] += Instance->lines[i][Instance->j];
      }
      if(Instance->pcount == 2) {
         Instance->para[2] += Instance->lines[i][Instance->j];
      }
      Instance->j++;

   }
   int temp_num = 0;
   if (isdigit(Instance->para[1][0]) == 0){
      temp_num = Instance->intVar[Instance->para[1]];
   }
   else{
      temp_num = atoi(Instance->para[1].c_str());
   }
        
   string parse = Instance->stringVar[Instance->para[0]];
   string para2;
   for (int x = 0; i < Instance->para[2].length(); ++x){
      para2 += Instance->para[2][x];
   }
   Instance->charVar[para2] = parse[temp_num];
}

GET_STR_CHAR::~GET_STR_CHAR(){
   // Destructor
}


SET_STR_CHAR::SET_STR_CHAR(){
   // Constructor
}
// Performs SET_STR_CHAR instruction
void SET_STR_CHAR::DoTask(MISMembers* Instance, int i){
   using namespace std;
   Instance->pcount = 0;
   Instance->j = 13;
        //cout << "made it here" << endl;
   while (Instance->lines[i][Instance->j] != '\0') {
          if (Instance->lines[i][Instance->j] == ',') {
            Instance->pcount++;
            Instance->j++;
          }
          if(Instance->pcount == 0) {
            Instance->para[0] += Instance->lines[i][Instance->j];
          }
          if(Instance->pcount == 1) {
            Instance->para[1] += Instance->lines[i][Instance->j];
          }
          if(Instance->pcount == 2) {
            Instance->para[2] += Instance->lines[i][Instance->j];
          }
          Instance->j++;

        }
        int temp_num = 0;
        char temp = ' ';
        string address;
        
        if (isdigit(Instance->para[1][0]) == false){
          temp_num = Instance->intVar[Instance->para[1]];
        }
        else{

          temp_num = atoi(Instance->para[1].c_str());
        }
        if (Instance->para[2][0] == '$'){

          int a = Instance->para[2].length();
          for (int x = 0; x < a; ++x){
             address += Instance->para[2][x];
          }

          temp = Instance->charVar[address];


        }
        else{

          temp = Instance->para[2][1];
        }
        int a = Instance->para[2].length();

        string parse = Instance->stringVar[Instance->para[0]];

        parse[temp_num] = temp;

        Instance->stringVar[Instance->para[0]] = parse;
}

SET_STR_CHAR::~SET_STR_CHAR(){
   // Destructor
}
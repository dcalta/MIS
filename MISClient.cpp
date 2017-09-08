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

int main(int argc, char *argv[]) {
   // Create a socket
   // AF_INET is family of address, so basically 127.0.0.1
   int socket1 = socket(AF_INET, SOCK_STREAM, 0);

   // Fill in the address of server
   struct sockaddr_in peeraddr; // struct that handles internet address in C
   int peeraddr_len;
   memset(&peeraddr, 0, sizeof(peeraddr)); // must memset or else error
   char* peerHost = "127.0.0.1"; // Local IP address

   // convert to IP
   struct hostent *host = gethostbyname(peerHost); 
    
   peeraddr.sin_family = AF_INET; // peer address must match
   short peerPort = 9999; // Must be 9999 or higher

   peeraddr.sin_port = htons(peerPort); // network host to short

   // Write resolved IP address of a server to the address structure
   memmove(&(peeraddr.sin_addr.s_addr), host->h_addr_list[0], 4);

   // Connect to a server
   connect(socket1, (struct sockaddr*) &peeraddr, sizeof(peeraddr));

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////* End of Socket Set up*///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   // input file
   std::ifstream myfile(argv[1]);
   std::string tempFile = argv[1];
   std::string inFile = ""; // input file name
   std::string errFile = ""; // error file name
   std::string outFile = ""; // out file name

   for(int z = 0; z < tempFile.length() - 4; z++) { // change the name of inFile, -4 because .mis
      inFile+= tempFile[z];
   }

   errFile = inFile + ".err";
   outFile = inFile + ".out";
   remove(errFile.c_str()); // removes the .err if it exist for new writing
   remove(outFile.c_str()); // removes the .out if it exist for new writing
   std::ofstream out(outFile.c_str());  // writes to output file
   std::ofstream error(errFile.c_str());
 
   // stores the lines from input
   std::vector<std::string> lines;
   std::string cur;
   std::string tempString = "";
   // adds to input
   while (getline(myfile, cur)) {
      lines.push_back(cur);
   }

   for(int i = 0; i < lines.size(); i++) {
      tempString += lines[i];
      if(i != lines.size()-1) {
         tempString += '^'; // character that repreents a new string a vector
      } 
      else {
         tempString += '`'; // character that represents the end of a vector
      }  
   }

   char sendToServer[1024]; 
   char bufferCheck[1024]; // helps fix random characters in buffer
   int endCheck = 0;
   // Converts from std::string to char[]
   strncpy(sendToServer, tempString.c_str(), sizeof(sendToServer));
   sendToServer[sizeof(sendToServer) - 1] = 0;


   //char sendToServer[] = "qwerty";
   write(socket1, sendToServer, strlen(sendToServer)); // Sends to server

   char buffer[1024]; // Recieve from server
   read(socket1, buffer, 1024);

   char buffer1[1024]; // for some weird reason this fixed the buffer characters
   for(int y = 0; y < strlen(buffer) - 1; y++ ) {
     buffer1[y] = buffer[y];
   }
   while(buffer[endCheck] != '`') {
      endCheck++;   
   }
   strncpy(bufferCheck, buffer, endCheck+1); // fixes more random buffer characters
   
   std::vector<std::string> outV; // put into vector for .out
   std::vector<std::string> errV; // put into a vector for .err
   std::string intoVector1 = "";
   std::string intoVector2 = "";
   int placeHolder = 0;
   for(int a = 0; a < strlen(buffer); a++) {
      if(buffer[a] == '^') {
         outV.push_back(intoVector1);
         intoVector1 = "";
         a++;
      }
      if(buffer[a] == '`') {
         outV.push_back(intoVector1);
         intoVector1 = "";
         a++;
         placeHolder = a;
         break; // leave this as the outV is done
      }
      intoVector1 += buffer[a];  
   }
   for(int b = placeHolder; b < strlen(buffer); b++) {
      if(buffer[b] == '^') {
         errV.push_back(intoVector2);
         intoVector2 = "";
         b++;
      }
      if(buffer[b] == '@') {
         errV.push_back(intoVector2);
         intoVector2 = "";
         b++;
         placeHolder = b;
         break; // leave this as the errV is done
      }
      intoVector2 += buffer[b];  
   }
   int errOutCheck = 0;
   // For loop that fixes error of Errors being printed out to Out file
   for (int checkSymbol = 0; checkSymbol < strlen(buffer); checkSymbol++) {
      if(buffer[checkSymbol] == '`') {
         errOutCheck = 1;
         break;
      }
   }
   // if there is something in the outfile
   if(errOutCheck == 1) {
      for(int ii = 0; ii < outV.size(); ii++) {
         out << outV[ii] << std::endl;
      }
      for(int ee = 0; ee < errV.size(); ee++) {
         error << errV[ee] << std::endl;
      }
   }
   // if there is nothing in the outfile
   else {
      for(int ee = 0; ee < errV.size(); ee++) {
         error << errV[ee] << std::endl;
      }      
   }
   
   close(socket1); // Close the socket 
   
   myfile.close();
   out.close();
   error.close();
   return 0;
}
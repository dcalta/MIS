#include "MIS.h"
int main(int argc, char *argv[]) {
    int listenPort = 9999; // Must be 9999 or higher
    // AF_INET is family of address, so basically 127.0.0.1
    
    // Create a socket
    int socket1 = socket(AF_INET, SOCK_STREAM, 0);
    if (socket1 < 0) {
       exit(0);
    }
    //address of socket created in a C struct
    struct sockaddr_in myaddr;  // C style sockets and structs were easier to use for us
    // need to memset or we get errors
    memset(&myaddr, 0, sizeof(struct sockaddr_in));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(listenPort);  
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind socket
    bind(socket1, (struct sockaddr*) &myaddr, sizeof(myaddr)); // dont use namespace std because std::bind is a thing

    struct linger linger_opt = { 1, 0 };
    setsockopt(socket1, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));

    // listen for a connection
    listen(socket1, 1); 

    struct sockaddr_in peeraddr;
    socklen_t peeraddr_len;
    int socket2 = accept(socket1, (struct sockaddr*) &peeraddr, &peeraddr_len);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////* End of Socket Set up*//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   // ^ = new line for vector
   // ` = end of out vector
   // @ = end of err vector

   // ` = end of vector from the client
    
   close(socket1); //close socket
   std::vector<std::string> lines; // Vector that will act as input file
   char buffer[1024];
   char bufferCheck[1024]; // helps fix random characters in buffer
   int endCheck = 0;
   read(socket2, buffer, 1024); // Read from Client, store in buffer


   char buffer1[1024]; // for some weird reason this fixed the buffer characters
   for(int y = 0; y < strlen(buffer) - 1; y++ ) {
      buffer1[y] = buffer[y];
   }
   while(buffer[endCheck] != '`') {
      endCheck++;   
   }
   strncpy(bufferCheck, buffer, endCheck+1); // fixes more random buffer characters
   std::string intoVector = "";
   for(int a = 0; a < strlen(buffer); a++) {
      if(buffer[a] == '^') {
         lines.push_back(intoVector);
         intoVector = "";
         a++;
      }
      if(buffer[a] == '`') {
         lines.push_back(intoVector);
         intoVector = "";
         a++;
      }
      intoVector += buffer[a];  
   }
   MISMembers* MIS = new MISMembers(lines);

   int j, y, r;
   for(int z = 0; z < lines.size(); z++) { // Scan for labels
      y = 0;
      while(true) {
         if(lines[z][y] == ' ' || lines[z][y] == '\t' || lines[z][y] == '\n') {
            j++;
         }
         else {
            break;   
         }
      }
      if(lines[z][y] == 'L' && lines[z][y+1] == 'A' && lines[z][y+2] == 'B' && lines[z][y+3] == 'E' && lines[z][y+4] == 'L' && lines[z][y+5] == ' ') {
         y = y+5;
         MIS->addLabel(z, y);
      }      
   }
   // Does the MIS instructions
   for(int i = 0; i < lines.size(); i++) {
      j = 0;
      while(true) {
         if(lines[i][j] == ' ' || lines[i][j] == '\t') {
            j++;
         }
         else {
            break;   
         }
      }
      if (lines[i][j] == 'V' && lines[i][j+1] == 'A' && lines[i][j+2] == 'R' && lines[i][j+3] == ' ') {
         MIS->VAR(i);
      } 
      else if(lines[i][j] == 'A' && lines[i][j+1] == 'D' && lines[i][j+2] == 'D' && lines[i][j+3] == ' ') {
         ADD* a = new ADD();         
         a->DoTask(MIS, i);  
         delete(a);
      }
      else if(lines[i][j] == 'S' && lines[i][j+1] == 'U' && lines[i][j+2] == 'B' && lines[i][j+3] == ' ') {
         SUB* s = new SUB();
         s->DoTask(MIS, i);
         delete(s);
      }
      else if(lines[i][j] == 'M' && lines[i][j+1] == 'U' && lines[i][j+2] == 'L' && lines[i][j+3] == 'T' && lines[i][j+4] == ' ') {
         MULT* m = new MULT();
         m->DoTask(MIS, i);
         delete(m);
      }
      else if(lines[i][j] == 'D' && lines[i][j+1] == 'I' && lines[i][j+2] == 'V' && lines[i][j+3] == ' ') {
         DIV* d = new DIV();
         d->DoTask(MIS, i);
         delete(d);
      }
      else if(lines[i][j] == 'A' && lines[i][j+1] == 'S' && lines[i][j+2] == 'S' && lines[i][j+3] == 'I' && lines[i][j+4] == 'G' && lines[i][j+5] == 'N' && lines[i][j+6] == ' ') {
         ASSIGN* as = new ASSIGN();
         as->DoTask(MIS, i);
         delete(as);
      }
      else if(lines[i][j] == 'O' && lines[i][j+1] == 'U' && lines[i][j+2] == 'T' && lines[i][j+3] == ' ') {
         OUT* o = new OUT();
         o->DoTask(MIS, i);
         delete(o);
      }else if (lines[i][j] == 'L' && lines[i][j+1] == 'A' && lines[i][j+2] == 'B' && lines[i][j+3] == 'E' && lines[i][j+4] == 'L' && lines[i][j+5] == ' ') {
         // LABEL is a valid syntax
      }
      else if(lines[i][j] == 'J' && lines[i][j+1] == 'M' && lines[i][j+2] == 'P' && lines[i][j+3] == ' ') {
         j = j+3;
         JMP* jm = new JMP();
         r = jm->DoTask(MIS, i, j);
         if(r == -1) {
            MIS->errors();
         } else {
            i=r-1;
         }
         delete(jm);
      }
      else if (lines[i][j] == 'J' && lines[i][j+1] == 'M' && lines[i][j+2] == 'P' && lines[i][j+3] == 'Z' && lines[i][j+4] == ' '){
         j = j+4;
         JMPZ* jmz = new JMPZ();
         r = jmz->DoTask(MIS, i, j);
         if(r == -1) {
            // Do nothing
         } else {
            i=r-1;
         }
         delete(jmz);
      }
      else if (lines[i][j] == 'J' && lines[i][j+1] == 'M' && lines[i][j+2] == 'P' && lines[i][j+3] == 'N' && lines[i][j+4] == 'Z' && lines[i][j+5] == ' '){
         j = j+5;
         JMPNZ* jmnz = new JMPNZ();
         r = jmnz->DoTask(MIS, i, j);
         if(r == -1) {
            //Do nothing
         } else {
            i=r-1;
         }
         delete(jmnz);
      }
      else if (lines[i][j] == 'J' && lines[i][j+1] == 'M' && lines[i][j+2] == 'P' && lines[i][j+3] == 'G' && lines[i][j+4] == 'T' && lines[i][j+5] == ' '){
         j = j+5;
         JMPGT* jmgt = new JMPGT();
         r = jmgt->DoTask(MIS, i, j);
         if(r == -1) {
            //Do nothing
         } else {
            i=r-1;
         }
         delete(jmgt);
      }
      else if (lines[i][j] == 'J' && lines[i][j+1] == 'M' && lines[i][j+2] == 'P' && lines[i][j+3] == 'L' && lines[i][j+4] == 'T' && lines[i][j+5] == ' '){
         j = j+5;
         JMPLT* jmlt = new JMPLT();
         r = jmlt->DoTask(MIS, i, j);
         if(r == -1) {
            //Do nothing
         } else {
            i=r-1;
         }
         delete(jmlt);
      }
      else if (lines[i][j] == 'J' && lines[i][j+1] == 'M' && lines[i][j+2] == 'P' && lines[i][j+3] == 'G' && lines[i][j+4] == 'T' && lines[i][j+5] == 'E' && lines[i][j+6] == ' '){
         j = j+6;
         JMPGTE* jmgte = new JMPGTE();
         r = jmgte->DoTask(MIS, i, j);
         if(r == -1) {
            //Do nothing
         } else {
            i=r-1;
         }
         delete(jmgte);
      }
      else if (lines[i][j] == 'J' && lines[i][j+1] == 'M' && lines[i][j+2] == 'P' && lines[i][j+3] == 'L' && lines[i][j+4] == 'T' && lines[i][j+5] == 'E' && lines[i][j+6] == ' '){
         j = j+6;
         JMPLTE* jmlte = new JMPLTE();
         r = jmlte->DoTask(MIS, i, j);
         if(r == -1) {
            //Do nothing
         } else {
            i=r-1;
         }
         delete(jmlte);
      }
      else if(lines[i][j] == 'T' && lines[i][j+1] == 'H' && lines[i][j+2] == 'R' && lines[i][j+3] == 'E' && lines[i][j+4] == 'A' && lines[i][j+5] == 'D' && lines[i][j+6] == '_' && lines[i][j+7] == 'B' && lines[i][j+8] == 'E' && lines[i][j+9] == 'G' && lines[i][j+10] == 'I' && lines[i][j+11] == 'N' && lines[i][j+12] == ' ') {

      }
      else if(lines[i][j] == 'T' && lines[i][j+1] == 'H' && lines[i][j+2] == 'R' && lines[i][j+3] == 'E' && lines[i][j+4] == 'A' && lines[i][j+5] == 'D' && lines[i][j+6] == '_' && lines[i][j+7] == 'E' && lines[i][j+8] == 'N' && lines[i][j+9] == 'D' && lines[i][j+10] == ' ' ) {

      }
      else if(lines[i][j] == 'L' && lines[i][j+1] == 'O' && lines[i][j+2] == 'C' && lines[i][j+3] == 'K' && lines[i][j+4] == ' ') {

      } 
      else if(lines[i][j] == 'U' && lines[i][j+1] == 'N' && lines[i][j+2] == 'L' && lines[i][j+3] == 'O' && lines[i][j+4] == 'C' && lines[i][j+5] == 'K' && lines[i][j+6] == ' ') {

      }
      else if(lines[i][j] == 'B' && lines[i][j+1] == 'A' && lines[i][j+2] == 'R' && lines[i][j+3] == 'R' && lines[i][j+4] == 'I' && lines[i][j+5] == 'E' && lines[i][j+6] == 'R' && lines[i][j+7] == ' ') {
        
      } 
      else {
         MIS->errors();
      }
   }

   std::string tempString1 = "";
   std::string tempString2 = "";
   // convert outVec to a string for sending
   for(int k = 0; k < MIS->outVec.size(); k++) {
      tempString1 += MIS->outVec[k];
      if(k != MIS->outVec.size()-1) {
         tempString1 += '^'; // character that repreents a new string a vector
      } 
      else {
         tempString1 += '`'; // character that represents the end of a vector
      }  
   }
   // convert the errVec to a string for sending
   for(int l = 0; l < MIS->errVec.size(); l++) {
      tempString2 += MIS->errVec[l];
      if(l != MIS->errVec.size()-1) {
         tempString2 += '^'; // character that repreents a new string a vector
      } 
      else {
         tempString2 += '@'; // character that represents the end of a err vector
      }  
   }
   tempString1+=tempString2; // add both to string for concat sending
   char sendToClient[1024];
   strncpy(sendToClient, tempString1.c_str(), sizeof(sendToClient));
   sendToClient[sizeof(sendToClient) - 1] = 0;

    write(socket2, sendToClient, strlen(sendToClient));

    close(socket2); // Close the data socket
    delete(MIS);
    return 0;
}
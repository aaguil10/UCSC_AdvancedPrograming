#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

#include "hexAI.h"

int main (){
  std::cout << "running!....\n";
  try{
    // Create the socket
    ServerSocket server(30000);
    Board B(11);
    hexAI jim(B);
    string move;
    while ( true ){
      ServerSocket new_sock;
      server.accept (new_sock);
      try{
        while ( true ){
          //get move from client
          std::string data;
          new_sock >> data;
          std::cout << "Data Recieved: " << data << std::endl;
          if(data == "q" || data == "Done"){
            exit(0);
          }
          //update board
          B.stringMove(P1,data);
          cout << B << endl;
          //compute and send move to client
          move = jim.play(B);
          B.stringMove(P2, move);
          new_sock << move;
        }
      } catch ( SocketException& ) {} //Catch if connection breaks
    }
  } catch ( SocketException& e ) {  //Catch if we can't connect to client
    std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
  }
  return 0;
}

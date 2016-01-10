#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main ( int argc, int argv[] ){
  std::cout << "running....\n";
  vector<string> rply;
  rply.push_back("Unfortunately, I can't help you with this question. Can you rephrase your question? ");
  rply.push_back("love and intention will bring the desired result");
  rply.push_back("explore the law of dharma ");
  rply.push_back("Listen to your heart ");
  rply.push_back("The universe knows the answer, so do you");
  try{
    // Create the socket
    ServerSocket server ( 30002 );
    int i = 0;
    while ( true ){

      ServerSocket new_sock;
      server.accept ( new_sock );

      try{
        while ( true ){
          std::string data;
          new_sock >> data;
          std::cout << "Data Receved: " << data << std::endl;
          new_sock << rply[i++%5];
	}
      } catch ( SocketException& ) {}
    }
  } catch ( SocketException& e ) {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
  }

  return 0;
}

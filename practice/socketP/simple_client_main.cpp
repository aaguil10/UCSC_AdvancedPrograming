#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
//#include <stdlib.h> 
//#include <crandom>

int main ( int argc, int argv[] ){
  std::cout << "Hello, I'm the almighty server prophet!"
            << " Type in any question about the future."
            << std::endl;
  int i = 0;
  while(i++ < 3){
    try{

      ClientSocket client_socket ( "localhost", 30001 );

      std::string reply;
      std::string msg;
      try{
           
        //std::cin >> msg;
        std::getline(std::cin, msg);
        client_socket << msg;  //sends message
	client_socket >> reply; //puts responce in "reply"
          
      } catch ( SocketException& ) {}

      std::cout << "We received this response from the server:\n\"" 
                 << reply << "\"\n" << std::endl;
      if(i < 3){ std::cout << "Ask another question." << std::endl; }

    } catch ( SocketException& e ){
      std::cout << "Exception was caught:" << e.description() << "\n";
    }
  }
  return 0;
}

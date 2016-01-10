#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <vector>
#include <random>

#include <stdio.h>      
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>

using namespace std;

#include "hexAI.h"


char* getIP(){
  struct ifaddrs * ifAddrStruct=NULL;
  struct ifaddrs * ifa=NULL;
  void * tmpAddrPtr=NULL;
  char *meip;
  getifaddrs(&ifAddrStruct);
  int i = 0;
  for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
    if (ifa ->ifa_addr->sa_family==AF_INET) { // check it is IP4
      // is a valid IP4 Address
      tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
      char addressBuffer[INET_ADDRSTRLEN];
      inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
      printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
      if(i++ == 1){
        meip = addressBuffer;
        return meip;
      }
    } else if (ifa->ifa_addr->sa_family==AF_INET6) { // check it is IP6
      // is a valid IP6 Address
      tmpAddrPtr=&((struct sockaddr_in6 *)ifa->ifa_addr)->sin6_addr;
      char addressBuffer[INET6_ADDRSTRLEN];
      inet_ntop(AF_INET6, tmpAddrPtr, addressBuffer, INET6_ADDRSTRLEN);
      printf("%s IP Address %s\n", ifa->ifa_name, addressBuffer); 
      if(i++ == 1){
        meip = addressBuffer;
        return meip;
      }
    } 
  }
  if (ifAddrStruct!=NULL) freeifaddrs(ifAddrStruct);
  return meip;
}

int main (){
  std::cout << "running!....\n";
  try{
    // Create the socket
    int port;
    cout << "Enter a port number around 30001(If program crashes use diffrent port)" << endl;
    cin >> port;
    ServerSocket server(port);
    cout << "Thanks!" << endl;
    printf("Enter this address on ./simple_client: %s\n", getIP());
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

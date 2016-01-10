#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <sys/time.h>
#include <random>
#include <algorithm>
#include <vector>

using namespace std;
#include "Board.h"

//fills up matrix with random moves
bool finish(Board &G, EDGECOLOR color,vector<EDGECOLOR> &color_tag){
  srand(unsigned(time(NULL)));
  vector< vector<edge> > M = G.get_matrix();
  random_shuffle(color_tag.begin(), color_tag.end());
  int i = 0; 
  for(int x = 0; x < G.GetSize(); ++x){
    for(int y = 0; y < G.GetSize(); ++y){
      if((M[x][y].get_node() == 3000) 
             && (i < G.GetSize() * G.GetSize())) {
        G.setColor(x,y,color_tag[i]);
        G.setNode(x,y);
        i++;
      }
    }
  }
  return G.FindWinner(color);
}

//fills up board 100 times and if it wins 100 time return true
bool did_we_win(Board &G, EDGECOLOR color){
  Board A = G;
  int wins_P1 = 0;
  const int trials = 100;
  //creates verctor full of colors that will be shuffel later
  vector<EDGECOLOR> color_tag;
  for (int i = 0; i < (G.GetSize()*G.GetSize()); i++) {
    if (i < ((G.GetSize()*G.GetSize())/ 2)){
      color_tag.push_back(P1);
    } else {
      color_tag.push_back(P2);
    }
  }
  //Go through the board
  for(int x = 0; x < trials; x++){
    A = G;
    // Checks if P1 wins, keeps track of how often
    if(finish(A, color, color_tag) == true){
      wins_P1++;  // keeps track of P1 wins, increments
    }
  }
  if(wins_P1 == trials){
    return true;
  }
  return false;
}

//Cointiualty asks you for coordinates until you enter vaild ones
char enter_input(Board &B, string &human_string){
  cin >> human_string;
  if (human_string == "q") return 'q';  //'q' means player want to quit
  try{
    B.stringMove(P1, human_string);
  } catch (int e) {
    switch (e) {
      case 1:
        cout << "Bad Coordinates! Please try again." << endl;
        return enter_input(B, human_string);
      case 2:
        cout << "Used coordinates. Please try again." << endl;
        return enter_input(B, human_string);
    }
  }
  return 'g';  //'g' means valid input
}

//returns true if player won or lost
bool print_results(Board &B){
  if(did_we_win(B,P1)){
    cout << B;
    cout << "******************************************" << endl;
    cout << "                You Won!" << endl;
    cout << "******************************************" << endl;
    return true;
  }
  if(did_we_win(B,P2)){
    cout << B;
    cout << "------------------------------------------" << endl;
    cout << "                You Lost!" << endl;
    cout << "------------------------------------------" << endl;
    return true;
  }
  return false;
}

int main (){
  int port;
  string IP;
  cout << "Enter the same Port # that you used for server" << endl;
  cin >> port;
  cout << "Enter IP address of server" << endl;
  cin >> IP;
  cout << "Hello, Welcome to the game of Hex!" << endl;
  cout << "Top corner: (0,0) and Bottom Right Corner (10,10)" << endl;
  string human_string;
  Board B(11);
  cout << B << endl;
  //main while loop for game
  while(true){
    cout << "\nEnter your next move x,y (or type q to quit): ";
    //sets up connection to server
    try{
      ClientSocket client_socket (IP, port);
      string reply;
      //if human quits this will let the server know 
      if (enter_input(B, human_string) == 'q'){
        reply = 'q';
        client_socket << reply;
        break;
      }
      //checks for winner or loser
      if(print_results(B)){
        client_socket << "Done";
        break;
      }
      client_socket << human_string;   // sends the human's move to the server
      cout << "Waiting for AI to return move..." << endl;
      client_socket >> reply; // receive response from server
      B.stringMove(P2, reply);
      cout << "We received this move from the server:\n\"";
      cout << reply << "\"\n" << std::endl;
      cout << B << endl;
      //checks for winner or loser
      if(print_results(B)){
        client_socket << "Done";
        break;
      }
      } catch ( SocketException& e ){  //if you can't connect to server
        cout << "Exception was caught:" << e.description() << "\n";
     }
  }
  return 0;
}

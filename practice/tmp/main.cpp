#include <iostream>
#include <random>
using namespace std;

#include "Graph.h"
#include "Board.h"

int main(){
   srand(time(0));
   //Graph G(10,0.5);
   Board B(6);
   cout << B << endl; 
   B.random_player();
   cout << B << endl;

   if(FindWinner(B,P1)){
     cout << "Player 1 wins!" << endl;
   } else {
     cout << "Player 2 wins!" << endl;
   }
   return 0;
}

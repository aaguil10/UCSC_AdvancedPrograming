//Assignment 4 - Game of Hex
//Jake VanAdrighem ID: 1387294
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "graph.h"
#include "hex.h"

using namespace std;

int main()
{
  int gameSize = 11;
  HexGame game(gameSize);
  int randPlayer = 0;
  for(int count = 0; count < (gameSize * gameSize); count++){
    randPlayer = rand() % 2;
    randPlayer += 1;
    game.makeMove(count,randPlayer);
  }
  cout << "XX is Player 1 Positions. OO belong to Player 2." << endl << endl;
  cout << game;
  int winner = game.determineWinner();
  cout << endl << "PLAYER " << winner << " WINS" << endl;
  return 0;
}

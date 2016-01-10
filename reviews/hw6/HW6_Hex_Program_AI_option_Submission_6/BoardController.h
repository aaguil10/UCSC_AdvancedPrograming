#ifndef _BOARD_CONTROLLER_H
#define _BOARD_CONTROLLER_H

#include <iostream>
#include <stdio.h>
#include <random>
#include <stdlib.h>
#include <string>
#include <vector>
#include "Board.h"
#include "Edge.h"

using namespace std;

class BoardController{
 public:
  friend std::ostream &operator<<(std::ostream &out, Board &b);
  BoardController(int sizeInput);
  bool CapturePoint(int x, int y, int player);
  int simulate();
 private:
  //  int multiThreader(vector<Edge*> takenEdgesInput, Board *b);
  void mainGame();
  Board *gameBoard;
  int size, turn, winner;
  vector<Edge*> takenEdges;

};

#endif

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <stdio.h>
#include <random>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include "Edge.h"

using namespace std;

class Board{
  friend class BoardController;
 public:
  Board(); //Default constructor sets size to 11.
  Board(int input);
  int printB(Board *input);
  void printNode(int x, int y);
  int getSize(){return size;}
  Edge* getNode(int x, int y){return quickBoard[x][y];}
  int getWinner();
  int getWinner(Edge* input);
  void MontiCarlo(uniform_real_distribution<> dis1, mt19937 gen);
  void MontiCarloLooper();

 private:
  //These are used by the winner-finding algorithm
  Edge* searchSpecificNodeOne(Edge* input);
  Edge* searchSpecificNodeTwo(Edge* input);
  bool side1, side2;
  volatile int total;
  ////

  vector<Edge*> board; //this is the main board.
  vector< vector<Edge*> > quickBoard;// This board is used for accessing nodes directly.
  void initBoard();
  void initStartingBoard();
  int multiThreader(vector<Edge*> takenEdgesInput, Board *b);
  int size, turns;
  int winner;
  mutex mtx;
  vector< vector<int> > visited;
  vector<Edge*> takenEdges;
  Edge* searchOne(Edge* input);
};

#endif

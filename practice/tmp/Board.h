/*Board.h this file defines the board class which is responsible for keeping track of the state of the game aa well as printing and finding the winner of the game.  */

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>    
#include <list>
#include <random>
using namespace std;

#include "edge.h"


class Board{
 public:
  Board(int board_s);
  friend ostream& operator<<(ostream&, Board&);
  friend void edge::build_adj(int, int, Board&); 
  friend bool FindWinner(Board&,EDGECOLOR);
  friend bool look_for_path(Board&,EDGECOLOR,edge&,int,int);

  inline int GetSize(){ return board_size; }
  void random_player();

 private:
  
  int board_size;
  vector< vector<edge> > matrix;
};
 
#endif

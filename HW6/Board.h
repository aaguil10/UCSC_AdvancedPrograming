/*Board.h this file defines the board class which is responsible for keeping track of the state of the game aa well as printing and finding the winner of the game.  */

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>    
#include <list>
#include <random>
using namespace std;

#include "edge.h"
#include "hexAI.h"

class Board{
 public:
  Board(int board_s);
  Board(Board&);
  friend class edge;
  friend class hexAI;
  friend ostream& operator<<(ostream&, Board&);
  friend void edge::build_adj(int, int, Board&);

  inline int getNode(int x, int y){return ((board_size * (x)) + y);}
  inline void setNode(int x, int y){ 
    matrix[x][y].node = ((board_size * (x)) + y);
  }
  inline void setColor(int x, int y,EDGECOLOR color){ 
    matrix[x][y].set_color(color); 
  }
  void makeMove(EDGECOLOR,int, int);
  void stringMove(EDGECOLOR,string coor);
  void playAI ();
  void reset();

  bool FindWinner(EDGECOLOR);
  inline int GetSize(){ return board_size; }

  friend bool finish_game(Board&, EDGECOLOR);
  friend int monte_carlo(Board &, EDGECOLOR);

  vector< vector<edge> > get_matrix(){ 
    return matrix;
  }

 private:
  bool look_for_path(EDGECOLOR,edge&,int,int);

  int highestProb[3];
  int board_size;
  vector< vector<edge> > t_matrix;
  vector< vector<edge> > matrix;
 
};
 
#endif

#ifndef HEXAI_H
#define HEXAI_H

#include <iostream>
#include <vector>    
#include <list>
#include <random>
using namespace std;

#include "edge.h"
#include "Board.h"

class hexAI{
 public:

  hexAI(Board&);
  bool finish_game(Board&, EDGECOLOR,vector<EDGECOLOR>&);
  double monte_carlo(Board &, EDGECOLOR);

  inline void set_highestProb(double x, double y, double z){
    highestProb[0] = x;
    highestProb[1] = y;
    highestProb[2] = z;
  }
  inline double get_highestProb(){ return highestProb[0]; }
  inline int get_num_plays(){ return num_of_P2; }
  string play(Board&);
  
 
 private:
  inline int plays_left(int num, int board_size){ 
    return (board_size*board_size)-((num * 2)+1); 
  }

  double highestProb[3];
  int num_of_P2;
};
 
#endif

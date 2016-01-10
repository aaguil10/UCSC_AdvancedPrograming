#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

class Edge{
  friend class Board;
  friend class BoardController;
 public:
  Edge(Edge* prevInput, Edge* nextInput){
    neighbors[0] = nextInput;
    neighbors[1] = prevInput;
    value = 0;
  }
  
  Edge(int input){value = input;}
  Edge(){value = 0;}
  ~Edge(){}
  int value; //0 - untaken, 1 or 2 are players.
  int x, y;
 private:
/*
neighbors[6] represents the list of nodes connected to any one particular node.
[0] = east node
[1] = west node
[2] = north east node
[3] = north west node
[4] = south east node
[5] = south west node

A visual representation would look like this:
     
     3 /\ 2
      /  \
     /    \
  1 |      | 0
    |      |
     \    /
    5 \  / 4
       \/ 
*/

  Edge *neighbors[6];

};

#endif

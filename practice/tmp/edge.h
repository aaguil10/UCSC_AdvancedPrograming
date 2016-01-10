/*edge.h edge is what is stores in the matix and keeps track of the other nodes it's connected to */

#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <list>
using namespace std;

class Board;

const int NOTREACHED = 3000;
enum EDGECOLOR{P1,P2,NOCOLOR};

struct edge_ref{
 int x;
 int y;
};

class edge{
 public:
  edge(){
    color = NOCOLOR;
    node = NOTREACHED;
  }

  friend ostream& operator<<(ostream&, edge&);
  friend bool look_for_path(Board&,EDGECOLOR,edge&,int,int);
  void build_adj(int, int, Board&);


  inline int set_node(int nodeX){ node = nodeX; }
  inline void set_coor(int x, int y){ node_x = x; node_y = y; }
  inline int get_node(){ return node; }
  inline void set_color(int node_color){ color = node_color; }
  inline int get_color(){ return color; }
  inline int get_adj_list(){ return adj_list.size(); }

  int visited = false;
 private:
  int color;
  int node;
  list<edge_ref> adj_list;
  int node_x;
  int node_y;
};


#endif

/*edge.cpp  */

#include <iostream>
#include "edge.h"
#include "Board.h"
using namespace std;

//prints color of edge
ostream& operator<<(ostream& out, edge &E){
  if(E.color == P1){
    out << '@';
  } else if(E.color == P2) {
    out << '!';
  } else {
    out << '*';
  }
}

//creates a list of edges that egde[i][j] is connected to.
void edge::build_adj(int x, int y, Board &G){
  for(int j = -1; j <= 1; j++){
    for(int i = -1; i <= 1; i++){
      if(x+i < 0 || x+i >= G.GetSize()){
        continue;
      }
      if(y+j < 0 || y+j >= G.GetSize()){
        continue;
      }
      if(i == 0 && j == 0){
        continue;
      }
      if(i == -1 && j == -1){
        continue;
      }
      if(i == 1 && j== 1){
        continue;
      }
      edge_ref tmp;
      tmp.x = x+i;
      tmp.y = y+j;
      adj_list.push_back(tmp);
    }
  }
}

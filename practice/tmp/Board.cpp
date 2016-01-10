/*Board.cpp */
#include <vector>
#include <random>
using namespace std;
#include "Board.h"
#include "edge.h"

//construtor for board
Board::Board(int board_s = 11){
  board_size = board_s;
  for(int i = 0; i < board_size; ++i){            
    vector<edge> row;
    matrix.push_back(row);         
  }                   
  //insert empty edge to matrix                     
  for(int i = 0; i < board_size; ++i){
    for(int j = 0; j< board_size; ++j){
      edge tmp;
      tmp.set_coor(i,j);
      matrix[j].push_back(tmp);
    }
  }
}

//Generates random games
void Board::random_player(){
  for(int x = 0; x < board_size; ++x){
    for(int y = 0; y < board_size; ++y){
      while(matrix[x][y].get_node() == 3000){
        int column = (rand()%2);
        matrix[x][y].set_color(column);
        int node_number = y + (x*board_size);
        matrix[x][y].set_node(node_number);
      }
    }
  }
}

//recursive function that searches for a path across the board
bool look_for_path(Board &G,EDGECOLOR color,edge &E, int size, int i){
  E.visited = true;
  if(color != E.get_color()){
    return false;      
  }
    
  int y = E.node_y;
  int x = E.node_x;    
    
  if(color == P1){
    if(y == size-1){
       return true;
    } else {
      for(auto p = E.adj_list.begin(); p != E.adj_list.end(); p++){
        if(G.matrix[(*p).x][(*p).y].visited == true){
          continue;
        }
        bool iftrue = look_for_path(G,color,G.matrix[(*p).x][(*p).y],size,y);
        if(iftrue == true){
          return true;
        }
      }
    }
  }
  if(color == P2){
    if(x == size){
      return true;
    } else {
      for(auto p = E.adj_list.begin(); p != E.adj_list.end(); p++){
        if(G.matrix[(*p).x][(*p).y].visited == true){
          continue;
        }
        bool iftrue = look_for_path(G,color,G.matrix[(*p).x][(*p).y],size,x);
        if(iftrue == true){
          return true;
        }
      }
    }
  }
  return false;
}




bool FindWinner(Board &G, EDGECOLOR color){
  for (int i = 0; i < G.GetSize(); i++) {
    for (int j = 0; j < G.GetSize(); j++) {
      G.matrix[i][j].build_adj(i,j,G);
    }
  }
  for (int j = 0; j < G.GetSize(); j++) {
    if(color == P1){
      bool iftrue = look_for_path(G,color,G.matrix[0][j],G.GetSize(),j);
      if(iftrue == true){
        return true;
      }
    }
    if(color == P2){
      bool iftrue = look_for_path(G,color,G.matrix[j][0],G.GetSize(),j);
      if(iftrue == true){
        return true;
      }
    }
  }
  return false;
}

//Prints board
ostream& operator<<(ostream& out, Board &B){
  for(int i = 0; i < B.board_size ; i++){
    if(i > 0){
      out << "\n";
      for(int x = 0; x < i; x++){
        out << " ";
      }
    }
    for(int x = 0; x < B.board_size ; x++){
      out << " " << B.matrix[i][x] << " ";
    }
  }
  out << endl;
}

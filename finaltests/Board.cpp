/*Board.cpp */
#include <vector>
#include <random>
#include <algorithm>
#include <sstream>
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
  //Creates adjacency list for every single node in the graph.
  for (int i = 0; i < GetSize(); i++) {
    for (int j = 0; j < GetSize(); j++) {
      matrix[i][j].build_adj(i,j,*this);
    }
  }
}

//copy construtor
Board::Board(Board &B){
  //Builds empty matrix
  board_size = B.GetSize();
  for(int i = 0; i < board_size; ++i){
    vector<edge> row;
    matrix.push_back(row);
  }
  for(int i = 0; i < board_size; ++i){
    for(int j = 0; j< board_size; ++j){
      edge tmp;
      tmp.set_coor(i,j);
      matrix[j].push_back(tmp);
    }
  }
  //Creates lisr of edges that this edge is connected to
  for (int i = 0; i < GetSize(); i++) {
    for (int j = 0; j < GetSize(); j++) {
      matrix[i][j].build_adj(i,j,*this);
    }
  }
  //copyies values from B 
  for(int i = 0; i < B.GetSize(); ++i){
    for(int j = 0; j < B.GetSize(); ++j){
      matrix[i][j].set_color(B.matrix[i][j].get_color());
      matrix[i][j].set_node(B.matrix[i][j].get_node());
    }
  }
}

//recursive function that searches for a path across the board
bool Board::look_for_path(EDGECOLOR color,edge &E, int size, int i){
  E.visited = true;
  if(color != E.get_color()){
    return false;      
  }
  int y = E.node_y;
  int x = E.node_x;    
  //call this function on all P1 nodes connected to this one
  if(color == P1){
    if(y == size-1){
       return true;
    } else {
      for(auto p = E.adj_list.begin(); p != E.adj_list.end(); p++){
        if(matrix[(*p).x][(*p).y].visited == true){
          continue;
        }
        bool iftrue = look_for_path(color,matrix[(*p).x][(*p).y],size,y);
        if(iftrue == true){
          return true;
        }
      }
    }
  }
  //call this function on all P2 nodes connected to this one
  if(color == P2){
    if(x == size-1){
      return true;
    } else {
      for(auto p = E.adj_list.begin(); p != E.adj_list.end(); p++){
        if(matrix[(*p).x][(*p).y].visited == true){
          continue;
        }
        bool iftrue = look_for_path(color,matrix[(*p).x][(*p).y],size,x);
        if(iftrue == true){
          return true;
        }
      }
    }
  }
  return false;
}



bool Board::FindWinner(EDGECOLOR color){
  //Creates adjacency list for every single node in the graph.
  for (int j = 0; j < GetSize(); j++) {
    //See if a vertical path of P1 nodes exist
    if(color == P1){
      bool iftrue = look_for_path(color,matrix[0][j],GetSize(),j);
      if(iftrue == true){
        return true;
      }
    }
    //check if a horizontal path of P2 nodes exist
    if(color == P2){
      bool iftrue = look_for_path(color,matrix[j][0],GetSize(),j);
      if(iftrue == true){
        return true;
      }
    }
  }
  return false;
}


void Board::makeMove(EDGECOLOR color,int x, int y) {
    int node = getNode(x, y);
    // Make sure the position is okay
  if (node > (board_size * board_size) || node < -1) {
    throw 1;
  }
  if (matrix[x][y].get_color() != NOCOLOR) {
    throw 2;
  }
  matrix[x][y].set_color(color);
  matrix[x][y].set_node(node);
}

void Board::stringMove(EDGECOLOR color, string coor){
  //parse string from "x,y" to "x" and "y"
  std::string delimiter = ",";
  string sx,sy;
  size_t pos = 0;
  std::string token;
  while ((pos = coor.find(delimiter)) != std::string::npos) {
    token = coor.substr(0, pos);
    sx = token;
    coor.erase(0, pos + delimiter.length());
  }
  sy = coor;
  //convert strings into ints
  int x,y;
  std::istringstream ss(sx);
  ss >> x;
  std::istringstream si(sy);
  si >> y;
  //cout << "x: " << x << " y: " << y << endl;
  makeMove(color, x, y);
}

void Board::reset(){
  for(int i = 0; i < board_size; ++i){
    for(int j = 0; j < board_size; ++j){
      matrix[i][j].set_color(NOCOLOR);
      matrix[i][j].set_node(3000);
      matrix[i][j].visited == false;
    }
  }
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

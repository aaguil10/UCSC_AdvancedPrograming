// HW4 Implement a HEX board.

// Objective : Display a legal Hex Position on an 11x11 board

// To play Hex you want to display a hex board and its position. Write code that can use ordinary ASCII characters to display the board. (This board can be found at the wikipedia article on HEX).

// This board should be represented as a graph. Each node of the graph is a hex square and the edges are the hex neighbor squares that can be used in a path. The hex graph should be written as a C++ class.

// You are to write a program that generates hex moves on this board at random. When the board is full, you will print it to the screen. The print hex board should be the overloaded operator << used for output.

// Grading standards will be based on documentation, good style, correctness, and elegance.

#include <cstdlib>      
#include <iostream>     
#include <cmath>        
#include <ctime>
#include <iomanip>
#include <vector>    
#include <list>  
using namespace std;
   

const int NOTREACHED = 3000;
enum EDGECOLOR{P1,P2,NOCOLOR};
class Graph;

// edge_ref is an object use to store coordinates of the edges surrounding 
// the current node
struct edge_ref{
 int x;
 int y;
};

// each node stores a number that can be decoded to location of edge
// edges store the the info need for each node in the graph
class edge{
 public:
  edge(){
    color = NOCOLOR;
    node = NOTREACHED;
  }

  friend ostream& operator<<(ostream&, edge);
  friend bool look_for_path(Graph&,EDGECOLOR,edge&,int,int);
  void build_adj(int, int, Graph&);

  int set_node(int nodeX){           // Has the node number. 
    node = nodeX;
  }

  void set_coor(int x, int y){
    node_x = x;
    node_y = y;
  }

  int get_node(){
    return node;
  }

  void set_color(int node_color){  // P1 has 0 
    color = node_color;           // P2 has 1 
  }

  int get_color(){
    return color;
  }

  //returns size of adjacency list
  int get_adj_list(){
    return adj_list.size();
  }

  int visited = false;
 private:
  int color;
  int node;
  list<edge_ref> adj_list;
  int node_x;
  int node_y;
};

//int edge::edge_count = 0;

//Prints Color of edge
ostream& operator<<(ostream& out, edge E){
  if(E.color == P1){
    out << '@';
  } else if(E.color == P2) {
    out << '!';
  } else {
    out << '*';
  }
}


class Graph{                               
 public:
  friend bool look_for_path(Graph&,EDGECOLOR,edge&,int,int);

 // Initialze the matrix with default 11x11 board
  Graph(int board_s = 11){
    board_size = board_s;
    for(int i = 0; i < board_size; ++i){            
      vector<edge> row;
      matrix.push_back(row);         
    }                                        
    for(int i = 0; i < board_size; ++i){
      for(int j = 0; j< board_size; ++j){
        edge tmp;
        //stores what postion node is at
        tmp.set_coor(i,j);
        matrix[j].push_back(tmp);
      }
    }
  }

  //Fills Graph with Random Plays
  void random_player(){
    //for each player
    for(int x = 0; x < board_size; ++x){
      for(int y = 0; y<board_size; ++y){
        //For each empty position
        while(matrix[x][y].get_node() == 3000){
          int column = (rand()%2);
          matrix[x][y].set_color(column);
          int node_number = y + (x*board_size);
          matrix[x][y].set_node(node_number);
        }
      }
    }
  }
  
  int GetSize(){
    return board_size;
  }

  friend ostream& operator<<(ostream&, Graph);  
  friend void edge::build_adj(int, int, Graph&); 
  friend bool FindWinner(Graph&,EDGECOLOR);

 private:
  vector< vector<edge> > matrix;
  int board_size;   
};

//Prints out Hex Board
ostream& operator<<(ostream& out, Graph G){
  out << endl;
  for(int i = 0; i < G.board_size ; i++){
    if(i > 0){
      out << "\n";
      for(int x = 0; x < i; x++){
        out << " ";
      }
    }
    for(int x = 0; x < G.board_size ; x++){
      out << " " << G.matrix[i][x] << " ";
    }
  }
  out << endl;
}

  //Finds every edge that the current edge is connected to.
  void edge::build_adj(int x, int y, Graph &G){
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

  //Depending on color it finds whether there exist a path across the board
  //this is called recursively 
  bool look_for_path(Graph &G,EDGECOLOR color,edge &E, int size, int i){
    E.visited = true;
    //if edge is not what we are looking for
    if(color != E.get_color()){
      return false;      
    }
    
    int y = E.node_y;
    int x = E.node_x;    
    
    if(color == P1){
      if(y == size-1){
         return true;
      } else {
        //iterate through edges connected to curent one
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
        //iterate through edges connected to curent one
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


   bool FindWinner(Graph &G, EDGECOLOR color){
     //adds nodes to adj_list of every edge in graph
     for (int i = 0; i < G.GetSize(); i++) {
       for (int j = 0; j < G.GetSize(); j++) {
         G.matrix[i][j].build_adj(i,j,G);
       }
     }

     //start looking for path
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


  
int main(){
   srand(time(0));
   cout << "Welcome to the game of Hex!" << "\n" << endl;
   cout << "Player 1: " << " @ " << " and goes vertically" << endl;
   cout << "Player 2: " << " ! " << " and goes horizontally" << endl;
   cout << "Open Squares: " << " * " << endl;
   cout << "\n";

   Graph G;
   G.random_player();
   cout << G;

   if(FindWinner(G,P1)){
     cout << "Player 1 wins!" << endl;
   } else {
     cout << "Player 2 wins!" << endl;
   }

   return 0;
}



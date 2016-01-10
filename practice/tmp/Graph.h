/*This program creates a matrix representation of a graph. The first argument sets the number of nodes. the second argument creates the density of the graph.*/


#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>

using namespace std; 


class Graph{
 private:
  int vector_must_have;
  int at_least_3_other;
  //ints in ordr to prevent a double free corupption
  int size;
  vector<vector<int>> matrix;
 
public:
  Graph(int s, double d);
  friend ostream& operator<<(ostream &out, Graph &g); 

  inline int GetElement(int r, int c){ return (this->matrix)[r][c]; }
  inline int GetSize(){ return size; }
  inline void EditElement(int r, int c, int v){
    (this->matrix)[r][c] = v;
    (this->matrix)[c][r] = v;
  }

};
 
#endif

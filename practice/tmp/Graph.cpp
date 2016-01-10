/*This program has the functions to intilize graph and print it out */

#include "Graph.h"
using namespace std;

inline double Probability() {
  return 1.0*rand()/RAND_MAX;
}


Graph::Graph(int s = 0,double d = 0.0){
    this->size = s;
    //creates matrix
    for (int i = 0; i < s; i++) {
      vector<int> row;
      (this->matrix).push_back(row);
    }
    //adds elements to first half of graph
    for (int i = 0; i < s; i++) {
      for (int j = 0; j < s; j++) {
        if (Probability() < d/2) {
          (this->matrix)[j].push_back(1 + (rand()%200));
        } else {
          (this->matrix)[j].push_back(0);
        }
      }
    }
    //adds to other side
    for (int i = 0; i < s; i++) {
      for (int j = 0; j < s; j++) {
        if (GetElement(i,j) != 0){
          (this->matrix)[j][i] = GetElement(i,j);
        }
      }
    }
  }

//Prints out graph
ostream& operator<<(ostream &out, Graph &g){
  out << "Graph Size: " <<g.GetSize() << endl;
  for (int i = 0; i < g.GetSize(); i++) {
    out << "\n";
    for (int j = 0; j < g.GetSize(); j++) {
      out <<  " " << g.GetElement(i,j) << " ";
    }
  }
  out << "\n" << "End of Graph\n" << endl;
}

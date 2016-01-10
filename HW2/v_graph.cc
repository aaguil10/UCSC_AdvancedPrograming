//This program should generate two graphs
#include<vector>
#include<string>
#include<iostream>
#include<random>
using namespace std;

//returns random number
double Probability() {
  return 1.0*rand()/RAND_MAX;
}

//Graph object that holds bool values
class Graph {
 public:
  Graph(int,double);
  int GetSize(){
    return size;
  }
  bool GetElement(int r, int c){
    return (this->matrix)[r][c];
  } 
 private:
  vector<vector<bool>> matrix;
  int size;
};

//Constructor creates a 2-dimensional vector of size s.
//vector represents a graph matrix which has a desity of d.
Graph::Graph(int s = 0,double d = 0.0){
  this->size = s;
  //creates matrix
  for (int i = 0; i < s; i++) {
    vector<bool> row;
    (this->matrix).push_back(row);
  }
  //initializes matrix
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      if (Probability() < d) {
        (this->matrix)[i][j] = true;
      }
    }
  }
}

//Over loads <<  operator to print graph.
ostream& operator<<(ostream& out, Graph& g){
  out << "Graph Size: " <<g.GetSize() << endl;
  for (int i = 0; i < g.GetSize(); i++) {
    out << "\n";
    for (int j = 0; j < g.GetSize(); j++) {
      out << " " << g.GetElement(i,j) << " ";
    }
  }
  out << "\n" << "End of Graph\n" << endl;
}


int main(){
  srand(time(0));
  cout << "Test simple graph generation\n";
  Graph myGraph(10,0.7);
  cout << myGraph;
  Graph elGrapho(8,0.5);
  cout << elGrapho;

}


#include<iostream>
#include<string>
#include<random>
using namespace std;

typedef bool *ptr_bool;
typedef ptr_bool *bool_matrix;

void p(string x) {
  cerr << "LOG: " << x << endl;
}

double Probability() {
  return 1.0*rand()/RAND_MAX;
}

class Graph {
 public:
  Graph(int,double);
  bool_matrix g1;
  int GetSize() {
    return size;
  }
 private:
  int size;
  //bool_matrix g1; 


};

Graph::Graph(int s, double density){
  p("In Cons");
  this->size = s;
  this->g1 = static_cast<bool_matrix>(calloc(s,sizeof(bool*)));
  //this->g1 = new bool_matrix[s]();
  for (int i = 0; i < s; i++) {
    this->g1[i] = static_cast<ptr_bool>(calloc(s,sizeof(bool)));
    //this->g1[i] = new ptr_bool;
  }
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      if (Probability() < density) {
        this->g1[i][j] = true;
      }
    }
  } 

}

ostream& operator<<(ostream& out, Graph& g){
  p("in stream");
  out << "Graph Size: " << g.GetSize() << "\n";
  for (int i = 0; i < g.GetSize(); i++) {
    out << "\n";
    for (int j = 0; j < g.GetSize(); j++) {
      out << " " << g.g1[i][j] << " ";
    }
  }
  p("End stream");

}

int main() {
  srand(time(0));
  cout << "Testing graph generation\n";

  Graph *me = new Graph(8,0.9)

  Graph myGraph(8,0.7);
  cout << myGraph << "LALALA\n";
  p("Done 1"); 
  Graph elGrapho(8,0.5);
  cout << elGrapho << "\n";
  


}

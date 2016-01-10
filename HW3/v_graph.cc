//This program should generate two graphs
#include<vector>
#include<string>
#include<iostream>
#include<random>
#include <queue>
#include<tuple>
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

  int GetElement(int r, int c){ //gets cost of edge
    return (this->matrix)[r][c];
  }

  void EditElement(int r, int c, int v){
    (this->matrix)[r][c] = v;
  }
  void PrintShortPath(int start, int end){
    Dijkstra(start);
    cout << "Shortest Path: " << start << "->";
    for (int i = 0; i < size; i++){ 
      if ( S[i] == end) {
        cout << S[i];
        break;
      }
      cout << S[i] << "->";
    }
    cout << "\n" << endl;
  }
  
  void Dijkstra(int source){
    int u = 0;
    int traverse = 0;
    S.push_back(source); //starts search with source
    ISS(source);
    for (int i = 0; i < size; i++){ //adds vertexes to the queue
      Q.push_back(i);
    }
    //Q.erase(Q.begin() + (source-1));
    while(!Q.empty()){
      u = ExtractMin(Q,size, S[traverse]); 
      S[traverse++] = u;
      for (int i = 0; i < size; i++) {//traverse adjacentcy vector
        if (GetElement(u,i) != 0) {
          Relax(u,i);
        }
      }     
    }
    cout << "Finshed Dijksta's!" << endl;    
  }

    void bidirectional(int source){
    }
 
 private:
  vector<vector<int>> matrix;
  int size;

  //variables for dijkstra's
  vector<int> d; //distance from source
  vector<int> pie;  //pie[v] parent of vector
  vector<int> Q;  //Todo: find a way to organize by cost of edge
  vector<int> S;  //stores the final short path
  const int INF = -2; //infinity
  const int NIL = -1; 

  //Initalize Single Source
  void ISS(int s){
    for (int i = 0; i < size; i++) {
       d.push_back(INF);
       pie.push_back(NIL); 
    }
    d[s] = 0;
  }

  //updates shortest path
  void Relax(int u, int v){
    if (d[v] > d[u] + GetElement(u,v)) {
      d[v] = d[u] + GetElement(u,v);
      pie[v] = u;
    }
  }
  //s stores size, ref stores the vertax we are currently looking at
  int ExtractMin(vector<int> &Q, int s,int ref){
    int smallest = 200;
    int refS = 200;
    for (int i = 0; i < Q.size(); i++) {  //Looks throught nodes next to vertex
      if((this->matrix)[ref][Q[i]] != 0  
        && (this->matrix)[ref][Q[i]] < smallest){
        smallest = (this->matrix)[ref][Q[i]]; // smallest = to cost
        refS = i;  //i = the node with smallest cost
      }
    }
    Q.erase(Q.begin() + (refS-1));
    return refS;  //returns the item with the smallest cost
  }

  //Not using may come in handy later
  int SumQ(vector<int> Q,int s){
    int sum = 0;
    for (int i = 0; i < s; i++) {
      sum = sum + Q[i];
    }
  }

};

//Constructor creates a 2-dimensional vector of size s.
//vector represents a graph matrix which has a desity of d.
Graph::Graph(int s = 0,double d = 0.0){
  this->size = s;
  //creates matrix
  for (int i = 0; i < s; i++) {
    vector<int> row;
    (this->matrix).push_back(row);
  }
  //initializes matrix
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      if (Probability() < d) {
        (this->matrix)[j].push_back(1 + (rand()%100));
      } else {
        (this->matrix)[j].push_back(0);
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
      out <<  " " << g.GetElement(i,j) << " ";

    }
  }
  out << "\n" << "End of Graph\n" << endl;
}

// Create simulation in seperate class
class Simulation {
 public:

 private:

};

int main(){
  srand(time(0));
  cout << "Test simple graph generation\n";
  Graph myGraph(10,0.7);
  myGraph.EditElement(1,1,1000);
  cout << myGraph;
  Graph elGrapho(8,0.5);
  cout << elGrapho;
  cout << "*************************************\n";
  Graph g(5,0.0);
  Graph g1(4, 0.0);
  cout << g;
  g.EditElement(0,1,8);
  g.EditElement(0,0,3);
  g.EditElement(0,4,4);
  g.EditElement(1,0,8);
  g.EditElement(1,2,6);
  g.EditElement(2,0,1);
  g.EditElement(2,1,6);
  g.EditElement(2,3,7);
  g.EditElement(3,2,7);
  g.EditElement(3,4,3);
  g.EditElement(4,0,4);
  g.EditElement(4,3,3);


  g1.EditElement(0,2,1);
  g1.EditElement(0,3,5);
  g1.EditElement(1,3,2);
  g1.EditElement(2,0,1);
  g1.EditElement(2,3,4);
  g1.EditElement(3,0,5);
  g1.EditElement(3,1,2);
  g1.EditElement(3,2,4);

  cout << g;
  //g.Dijkstra(3);
  g.PrintShortPath(3,0);

  cout << g1;
  //g.Dijkstra(3);
  g1.PrintShortPath(1,2);

}






//This program should generate two graphs
#include<vector>
#include<string>
#include<iostream>
#include<random>
#include <queue>
#include<tuple>
#include<list>
using namespace std;

void printVector(vector<int> v, string s){
    cout << s;
    for (int i = 0; i < v.size(); i++) {
      cout << " " << v[i] << " ";
    }
    cout << endl;
}

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
    (this->matrix)[c][r] = v;
  }

    void bidirectional(int source){
    }
 
 private:
  vector<vector<int>> matrix;
  int size;

 

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
      if (Probability() < d/2) {
        (this->matrix)[j].push_back(1 + (rand()%200));
      } else {
        (this->matrix)[j].push_back(0);
      }
    }
  }
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      if (GetElement(i,j) != 0){
        //EditElement(j,i,GetElement(i,j));
        (this->matrix)[j][i] = GetElement(i,j);
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

class ShortestPath{
public:   
    ShortestPath(Graph g, int source, int dest):
        g(g),
        source(source), dest(dest) {
        Dijkstra();  
    }

  void Dijkstra(){
    int u = 0;
    int traverse = 0;
    S.push_back(source); //starts search with source
    printVector(S,"*S: ");
    ISS(source);
    Q = vector<int> {};
    for (int i = 0; i < g.GetSize(); i++){ //adds vertexes to the queue
      if(i == source){
        continue;
      }
      Q.push_back(i);
      //q.push_front(i);
    }
    while(!Q.empty()){
      cout << endl;
      u = ExtractMin(Q, g.GetSize() , S[traverse++]); 
      //S[traverse++] = u;  
      S.push_back(u);
      if(u == dest){
        break;
      }
      cout << "U: " << u << endl;
      printVector(S, "S: ");
      for (int i = 0; i < g.GetSize(); i++) {//traverse adjacentcy vector
        if (g.GetElement(u,i) != 0) {
          Relax(u,i);
        }
      }     
    }
    cout << "Finshed Dijksta's!" << endl;    
  }

private:
    Graph g;
    int source;
    int dest;
    using nodeDist = tuple<int, int, int>;
    priority_queue<nodeDist, vector<nodeDist>, greater<nodeDist>> nodes;
    list<int> q;

 //variables for dijkstra's
  vector<int> d; //distance from source
  vector<int> pie;  //pie[v] parent of vector
  vector<int> Q;  //Todo: find a way to organize by cost of edge
  vector<int> S;  //stores the final short path
  const int INF = -2; //infinity
  const int NIL = -1; 

 //Initalize Single Source
  void ISS(int s){
    for (int i = 0; i < g.GetSize(); i++) {
       d.push_back(INF);
       pie.push_back(NIL); 
    }
    d[s] = 0;
  }

  //updates shortest path
  void Relax(int u, int v){
    if (d[v] > d[u] + g.GetElement(u,v)) {
      d[v] = d[u] + g.GetElement(u,v);
      pie[v] = u;
    }
  }
  //s stores size, ref stores the vertax we are currently looking at
  int ExtractMin(vector<int> &Q, int s,int ref){
    nodes = priority_queue<nodeDist, vector<nodeDist>, greater<nodeDist>>();
    for (int i = 0; i < Q.size(); i++) {
      if(g.GetElement(ref,Q[i]) != 0) { 
        nodes.push(make_tuple(g.GetElement(ref,Q[i]), Q[i],i ));
        cout << " >Cost: " << g.GetElement(ref,Q[i]) << " value: " << Q[i] << " slot: " << i << endl;
      }
    }
    int cost;
    int vector;
    int adjVector;
    tie(cost, vector, adjVector) = nodes.top();
    nodes.pop();
    cout << " Cost: " << cost << " value: " << vector << " slot: " << adjVector << endl;
    Q.erase(Q.begin() + (vector-1));
    return vector;  //returns the item with the smallest cost
  }

};


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
  cout << g1;

  Graph tree(3,0.0);
  tree.EditElement(0,1,8);
  tree.EditElement(0,2,5);
  tree.EditElement(2,1,7);
  cout << tree;
  ShortestPath(tree, 2, 1); 

}






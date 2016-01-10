//This program should generate two graphs that compares a unidirectional search with a bidirectional seach
//for the shortest path 
#include<vector>
#include<string>
#include<iostream>
#include<random>
#include <queue>
using namespace std;

//General Helper Function
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
  Graph(int s = 0,double d = 0.0){
    this->size = s;
    //creates matrix
    for (int i = 0; i < s; i++) {
      vector<int> row;
      (this->matrix).push_back(row);
    }
    //initializes upper part of matrix
    for (int i = 0; i < s; i++) {
      for (int j = 0; j < s; j++) {
        if (Probability() < d/2) {
          (this->matrix)[j].push_back(1 + (rand()%200));
        } else {
          (this->matrix)[j].push_back(0);
        }
      }
    }
    //Copies to the bottom part
    for (int i = 0; i < s; i++) {
      for (int j = 0; j < s; j++) {
        if (GetElement(i,j) != 0){
          (this->matrix)[j][i] = GetElement(i,j);
        }
      }
    }
  }

  int GetSize(){
    return size;
  }

  //gets cost of edge
  int GetElement(int r, int c){
    return (this->matrix)[r][c];
  }

  //adds edeg with cost
  void EditElement(int r, int c, int v){
    (this->matrix)[r][c] = v;
    (this->matrix)[c][r] = v;
  }

 private:
  vector<vector<int>> matrix;
  int size;

};

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


struct distNode{
  int node;
  int distance;
};

//compares two distNode objects
class distCompare{
 public:
  bool operator()(distNode& node1, distNode& node2){
    if (node1.distance  > node2.distance) { 
      return true;
    } else {
      return false;
    }
  }
};

class Dijk{
 public:   
   Dijk(Graph g, int source, int dest):
     g(g),
     source(source), dest(dest) {
       Dijkstra();
     }
  
    void Dijkstra(){
      for (int i = 0; i < g.GetSize(); i++) { 
        d.push_back(INF);
        visited.push_back(false);
      }
      // distance of source is 0
      d[source] = 0;
      // initialize priority queue and use compare method
      priority_queue< distNode, vector< distNode >, distCompare> pq;
      // put souce node into queue
      distNode first = {source,0};
      pq.push(first);
      // While queue is not empty, pick the topmost node
      // using it's neighbors update the distance of each n
      // ode that can be reached
      // and insert that node in the priority queue
      while(!pq.empty()){
        distNode temp = pq.top();
        pq.pop();
        int node = temp.node;
        if (temp.node != source){
          S.push_back(temp.node);
        }
        if(temp.node == dest){
          break;
        }
        for (int i = 0;i < g.GetSize();i++  ) {
          if (g.GetElement(node,i) != 0) {
            // Update the distance if it is smaller than the current distance
            if(d[i] > (d[node] + g.GetElement(node,i))) {             
              d[i] = d[node] + g.GetElement(node,i); 
            }
            // If not visited put it into the queue
            if (!visited[i]) {
              distNode nodeNew;                   
              nodeNew.node = i;
              nodeNew.distance = d[i];
              pq.push(nodeNew);
              visited[i] = true;
            }
          }
        }
      }  
    }

    int ClosedSetSize(){
      return S.size(); 
    }
    
private:
    Graph g;
    int source;
    int dest;

 //variables for dijkstra's
  vector<bool> visited; 
  vector<int> d; //distance from source
  vector<int> S; //Closed set from source
  const int INF = 123123223; //infinity 

};


class BiPath{
 public:   
   BiPath(Graph g, int source, int dest):
     g(g),
     source(source), dest(dest) {
       Bidirectional();
     }
  
    // ADD STUFF HERE! 
    void Bidirectional(){
      //ISS innitalizes d, vistited, pg fot the side of the source
      //An innitalizes b, vis, gp fot the side of destination
      for (int i = 0; i < g.GetSize(); i++) {
        d.push_back(INF);
        visited.push_back(false);
        b.push_back(INF);
        vis.push_back(false);
      }
      d[source] = 0;
      b[dest] = 0;
      priority_queue< distNode, vector< distNode >, distCompare> pq;
      priority_queue< distNode, vector< distNode >, distCompare> qp;
      distNode first = {source,0};
      distNode second = {dest,0};
      pq.push(first);
      qp.push(second);
      while(!pq.empty()){
        //dijksta form source
        distNode temp = pq.top();
        pq.pop();
        int node = temp.node;
        if (temp.node != source){
          S.push_back(temp.node);
        }
        //check whether we find match in closed sets
        if(compClose(S,D)){
          break;
        }
        for (int i=0;i < g.GetSize();i++  ) {
          if (g.GetElement(node,i) != 0) {
            if(d[i] > (d[node] + g.GetElement(node,i))) {
              d[i] = d[node] + g.GetElement(node,i);
            }
            if (!visited[i]) {
              distNode nodeNew;
              nodeNew.node = i;
              nodeNew.distance = d[i];
              pq.push(nodeNew);
              visited[i]=true;
            }
          }
        }
        //dijksta from destination
        temp = qp.top();
        qp.pop();
        node = temp.node;
        if (temp.node != dest){
          D.push_back(temp.node);
        }
        if(compClose(S,D)){
          break;
        }
        for (int i=0;i < g.GetSize();i++  ) {
          if (g.GetElement(node,i) != 0) {
            if(b[i] > (b[node] + g.GetElement(node,i))) {
              b[i] = b[node] + g.GetElement(node,i);
            }
            if (!vis[i]) {
              distNode nodeNew;
              nodeNew.node = i;
              nodeNew.distance = b[i];
              qp.push(nodeNew);
              vis[i]=true;
            }
          }
        }
      }
    }
    
    int ClosedSetSize(){
      if(S.size() >= D.size()){
        return S.size(); 
      } else {
        return D.size();
      }
    }

private:
    Graph g;
    int source;
    int dest;

 //variables for iterating from source
  vector<bool> visited; 
  vector<int> d; //distance from source
  vector<int> S; //Closed set from source
  const int INF = 123123223; //infinity 

  //variables for iterating from destination
  vector<bool> vis; 
  vector<int> b; //distance from destination
  vector<int> D; //Closed set from destination  

  //Compares Two Closed sets if they have one elment in common it returns
  //true else false
  bool compClose(vector<int> a, vector<int> b){
    if(a.size() == 0 || b.size() == 0){
      return false;
    }
    bool match = false;
    for (int i =0; i < a.size();i++) {
      if (a[i] == (b.back())){
        match = true;
      }
    }
    return match;
  }

};

int main(){
  srand(time(0));
 
  //Prints the avrage amount of iterations it took to find shortest path
  //for Dijkstra's and Bidirections
  cout << " Density: 0.1, Node Size 1000" << endl;
  double avgD = 0;
  double avgB = 0;
  for (int i = 0; i < 100; ++i) {
    Graph g3(1000,0.1);
    Dijk d(g3, 3, 1);
    BiPath b(g3, 3, 1);
    avgD += d.ClosedSetSize();
    avgB += b.ClosedSetSize();
  }
  avgD = avgD/100;
  avgB = avgB/100;
  cout << "Average Closed Set Nodes for Dijkstra: " << avgD <<endl;
  cout << "Average Closed Set Nodes for Bidirectional: " << avgB <<endl;

  cout << endl;

  //Round Two...
  cout << " Density: 0.01, Node Size 1000" << endl;
  avgD = 0;
  avgB = 0;
  for (int i = 0; i < 100; ++i) {
    Graph g3(1000,0.01);
    Dijk d(g3, 3, 1);
    BiPath b(g3, 3, 1);
    avgD += d.ClosedSetSize();
    avgB += b.ClosedSetSize();
  }
  avgD = avgD/100;
  avgB = avgB/100;
  cout << "Average Closed Set Nodes for Dijkstra: " << avgD <<endl;
  cout << "Average Closed Set Nodes for Bidirectional: " << avgB <<endl;
  
}



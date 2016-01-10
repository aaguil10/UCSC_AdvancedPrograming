//CUSTOM GRAPH CLASS -- Jake VanAdrighem
//ID: 1387294
#ifndef GRAPH_CLASS
#define GRAPH_CLASS

#include <functional>
#include <list>
#include <set>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::list;
using std::pair;
using std::make_pair;
using std::vector;
using std::set;


class graph {
 public:
  graph(int sizeIn, int maxWeight);
  graph(int sizeIn, int weight, vector< vector<int> > graphIn);
  graph(int sizeIn, double density, int maxWeight);
  vector<vector<int> >& getGraph(){ return graphData; };
  int getWeight(){ return MAXWEIGHT; };
  int getSize(){ return graphSize; };
  bool setEdge(int src, int dest, int weight);
  void printStructure();
  
 private:
  int MAXWEIGHT;//Added to eliminate magic numbers. Max weight of vertex is always set during construction.
  int graphSize;
  vector< vector<int> > graphData;
};

//Create an edgeless graph
graph::graph(int sizeIn, int maxWeight){
  MAXWEIGHT = maxWeight;
  graphSize = sizeIn;
  graphData.resize(graphSize);
  for(int rowCount = 0; rowCount < graphSize; rowCount++) graphData[rowCount].resize(graphSize);
}

//Use a premade 2D edge array as a graph
graph::graph(int sizeIn, int weight, vector< vector<int> > graphIn){
  graphSize = sizeIn;
  graphData = graphIn;
  MAXWEIGHT = weight;
}

//Generate a graph with weights below MAXWEIGHT at a given density
graph::graph(int sizeIn, double density, int maxWeight)
{
  MAXWEIGHT = maxWeight;//Set the max weight of an edge
  srand(time(0));
  graphData.resize(sizeIn);
  graphSize = sizeIn;
  for(int rowCount = 0; rowCount < graphSize; rowCount++) graphData[rowCount].resize(graphSize);
  //Populate the graph. Vector defaults data members to 0 which means we only need to apply our true locations
  for(int row = 0; row < graphSize; row++)
  {
    for(int vert = 0; vert < graphSize; vert++)
    {
      if(graphData[row][vert] > 0) break;//If a weight already exists for this node, then we ignore it and continue.
      if(row == vert) continue;//The weight of a node to itself should only be 0
      if((1.0 * rand() / RAND_MAX ) < density)
      {	
        graphData[row][vert] =  rand() % (MAXWEIGHT + 1);//Bound the weight of a node by 200 via (modulus 201)
	       graphData[vert][row] = graphData[row][vert];//Graph is undirected so we reciprocate connections both ways
      }
    }
  }
}


bool graph::setEdge(int src, int dest, int weight){
  if( weight <= MAXWEIGHT){
    graphData[src][dest] = weight;
    return true;
  }
  else return false;
}

//Print the adjecency matrix
void graph::printStructure()
{
  for(int row = 0; row < graphSize; row++)
  {
    for(int elem = 0; elem < graphSize; elem++)
    {
      if( row == elem ) continue;
      cout << graphData[row][elem] << "  ";
    }
    cout << endl;
  }
}


#endif

//DIJKSTRA ALGORITH USES CUSTOM GRAPH CLASS -- Jake VanAdrighem
//ID: 1387294
#ifndef DIJKSTRA_CLASS
#define DIJKSTRA_CLASS

#include <list>
#include <pair>
#include <set>
#include <utility>
#include <vector>

#include "graph.h"

using std::list;
using std::make_pair;
using std::pair;
using std::set;
using std::vector;

list<pair<int,int> > Dijkstra(graph graphData, int weight, int size, int src, int dest){
  //Temporary storage used in the algorithm.
  int currentNode;
  int currentNodeDist = 0;
  int neighborDistance = 0;
  int newPathDist = 0;
  // CONTAINERS
  vector<int> dist(graphSize, (weight + 1));//Total path distance for each node. Start weight above max.
  vector<int> previous(graphSize, -1);//Node prior to indexedNode in the path from src.
  vector<bool> visited(graphSize, false);//Determines whether node was visisted
  set<pair<int,int> > Q;//set structure used as minimum priority queue, <weight, ID> auto sorted based on strict weak ordering.
  //TRAVERSAL PREP
  dist[src] = 0;//distance from src -> itself is 0
  previous[src] = src;//Going backwards from src on the path loops to itself
  Q.insert(make_pair(dist[src],src));//src is the first node we visit. <0,src>
  //ALGORITHM
  while(!Q.empty()){
    if(visited[dest]) break;//Stop working if we've visited the destination and looked at its neighbors
    currentNode = Q.begin()->second;
    currentNodeDist = Q.begin()->first;
    Q.erase(Q.begin()); //Remove the new currentNode from the "queue"
    visited[currentNode] = true;
    //Update all neighbors
    for( int currentNeighbor = 0; currentNeighbor < graphSize; currentNeighbor++ ){
      //Get the distance from currentNode to the potential neighbor we're visiting
      neighborDistance = graphData[currentNode][currentNeighbor];
      //We should ignore edgeless connections and nodes we've already looked at
      if(neighborDistance == 0 || visited[currentNeighbor]) continue;
      //Calculate the distance from current node to src + distance from current node to neighbor
      newPathDist = currentNodeDist + neighborDistance;
      //if distance from current to src + neighbor edge is the new lowest path distance then we update our nodes information
      if(newPathDist < dist[currentNeighbor]){
	//Erase will do nothing if the vertex doesn't exist in the set. This allows us to "add" to the "queue" if the node wasn't previously in it.
	Q.erase(make_pair(dist[currentNeighbor], currentNeighbor));
	dist[currentNeighbor] = newPathDist;
	previous[currentNeighbor] = currentNode;
	//Re-inserting the vertex is a forced re-order.
	Q.insert(make_pair(dist[currentNeighbor], currentNeighbor));
      }
    }
  }
  list< pair<int,int> > path;//list<(weight, id)>
  //If the destination was unreachable then we return a list with 1 node containing <-1,-1>
  if(previous[dest] == -1){
    path.push_front(make_pair(-1,-1));
    return path;
  }
  //Put the path and weights into a list backwards from dest to src and return it.
  path.push_front(make_pair(dist[dest],dest));
  while(path.front().second != src){
    path.push_front( make_pair(dist[previous[path.front().second]], previous[path.front().second]) );
  }
  return path;
}

#endif

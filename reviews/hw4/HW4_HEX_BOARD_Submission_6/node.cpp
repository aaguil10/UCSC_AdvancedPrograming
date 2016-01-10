#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>
#include "node.h"

using namespace std;
//function to push all of a node's neighbours onto its list (of neighbours).
void node::addConnections(int i, int j, int size) {
  if (i != (size-1)) {
    neighborColumns.push_back(i+1); //push right neighbour
    neighborRows.push_back(j); 
  }
  if (j != (size-1)) {             //push bottom neighbour
    neighborColumns.push_back(i);  
    neighborRows.push_back(j+1);
  }
  if (i != 0) {                    //push left neighbour
    neighborColumns.push_back(i-1); 
    neighborRows.push_back(j); 
  }
  if (j != 0) {                    //push top neighbour
    neighborColumns.push_back(i); 
    neighborRows.push_back(j-1); 
  }
  if (i != (size-1) && j != 0) {   //push top right neighbour
    neighborColumns.push_back(i+1); 
    neighborRows.push_back(j-1); 
  }
  if (i != 0 && j != (size-1)) {   //push bottom left neighbour
    neighborColumns.push_back(i-1); 
    neighborRows.push_back(j+1); 
  }
}

//node constructor. constructs a single node. 
node::node(int a, int b) {
  x = a;
  y = b;
  xParent = -1;
  yParent = -1;
  status = 0;
  totalCost = 0;
  
  setColor(0);
}


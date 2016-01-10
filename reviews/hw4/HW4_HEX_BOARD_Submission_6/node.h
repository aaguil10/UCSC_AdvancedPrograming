using namespace std;

class node {
  int x;
  int y;
  int xParent;
  int yParent;
  int status; //keeps track of node status
              // 0 = undiscovered
              // 1 = on the open list
              // 2 = on the closed list
  int totalCost;
  int color; //keeps track of which player has the node;
             // 0 = empty
             // 1 = player 1
             // 2 = player 2
  vector<int> neighborColumns; //keeps tracks of x-coordinate of node connections
  vector<int> neighborRows;//keeps tracks of y-coordinate of node connections
  
public:
  //node constructors
  node(int a, int b); // node constructor
  
  //node accessors
  int getRow(int index) { return neighborRows.at(index); }
  int getColumn(int index) { return neighborColumns.at(index); }
  int getXParent(void) { return xParent; }
  int getYParent(void) { return yParent; }
  int getStatus(void) { return status; }
  int getTotalCost(void) { return totalCost; }
  int getColor(void) { return color; }
  int getNeighborCount(void) { return neighborRows.size(); }
  
  //node mutators
  void setXParent(int xPar) { xParent = xPar; }
  void setYParent(int yPar) { yParent = yPar;}
  void setStatus(int stat) { status = stat;}
  void setTotalCost(int tCost) { totalCost = tCost; }
  void setColor(int num) { color = num; }
  void addConnections(int i, int j, int size); //build connections of a single node.
  void resetNodes(void);
};

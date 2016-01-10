//Kevin Yeap
//1270597
//kyeap@ucsc.edu
//cpms109 f14

#include <iostream>
#include <ctime>
#include <vector>
#include <iomanip>
#include "node.h"

using namespace std;

inline int getRandNum(int matrixSize) {
  return static_cast<int>(rand()%matrixSize);
}

//hexBoard class. contains size and hexMatrix
class hexBoard {
  int size; //size of hexBoard passed in when a hexBoard object is declared
  vector<vector<node>> hexMatrix; // my data structure that contains my nodes

public:
  //hexBoard constructors
  hexBoard(int hexBoard); //hexBoard constructor
  
  //hexBoard accessors
  int getSize(void){ return size; }
  vector<vector<node>> getGrid(void){ return hexMatrix; }
  
  //hexBoard mutators
  void randomizedEndGame(void); //randomly generates an endgame scenario
  void buildConnections(void); //connects all the nodes
  int determineWinnerUpDown(int xx, int yy); //determines if Player 2 wins or not.
  void printWinner(void); //performs Path finding and prints out a winner
};

  
//hexBoard constructor. Used to declare hexBoard object in the main function.
hexBoard::hexBoard(int hexSize){
  size = hexSize;
  hexMatrix.resize(size); //resizes the vector that contains the x-coordinate vectors.
  
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      node newNode(i, j); //declare a new node
      hexMatrix.at(i).push_back(newNode); //push a new node to vector
    }
  }
  buildConnections();
}


//connects every single node to its neighbors
void hexBoard::buildConnections(void) { 
  for(int i = 0; i < size; i++) { //traverse all nodes
    for(int j = 0; j < size; j++) { 
      hexMatrix.at(i).at(j).addConnections(i, j, size); //add its neighbour to the nodes list of neighbours
    }
  }
}


//generates a randomized endGame scenario
void hexBoard::randomizedEndGame(void) {
  int x = getRandNum(size);
  int y = getRandNum(size);
  int numOfNodes = getSize()*getSize();
  
  for (int i = 0; i < numOfNodes; i++) {
    while (getGrid().at(x).at(y).getColor() != 0) { //randomly assign positions until an empty position is found
      x = getRandNum(size); //assign random x position
      y = getRandNum(size); //assign random y position
    }
    hexMatrix.at(x).at(y).setColor((i%2)+1); //alternately assign player 1 or 2 to the random position found
  } 
}


//determine if Player two has won
int hexBoard::determineWinnerUpDown(int xx, int yy) {
  vector<vector<node>> hexMatrixCopy = getGrid();
  int xStart = xx; //start node coordinates
  int yStart = yy;
  int x = xStart; //neighbour node coordinates
  int y = yStart;
  int xCurrent = xStart; //current node coordinate
  int yCurrent = yStart;
  int currentNodeTotal = 0; //total cost to get to the node from start
  int newNodeCost = 1; //cost to get to next node will always be 1
  int player = hexMatrixCopy.at(xStart).at(yStart).getColor(); //the player (1 or 2) that owns the start position of path finder is stored in here
  vector<int> openXList;
  vector<int> openYList;
  
  if (player == 2) { // if the node colour at matrix[x, 0] is not player 2, don't bother checking it for a path
    openXList.push_back(xStart); //push it onto openList.
    openYList.push_back(yStart); 
  }
  
  //determine if there is winner left to right
  while (openXList.size() > 0) { //while there are nodes on the opens list....
    for (int i = 0; i < hexMatrixCopy.at(xCurrent).at(yCurrent).getNeighborCount(); i++) {
      x = hexMatrixCopy.at(xCurrent).at(yCurrent).getColumn(i); // grabbing neighbour coordinates
      y = hexMatrixCopy.at(xCurrent).at(yCurrent).getRow(i);
      
      currentNodeTotal = hexMatrixCopy.at(xCurrent).at(yCurrent).getTotalCost();
      
      //if the neighbour node colour is (same player) && (unvisited)...
      if (hexMatrixCopy.at(x).at(y).getColor() == player && hexMatrixCopy.at(x).at(y).getStatus() == 0) { 
        openXList.push_back(x); //push it onto openList.
        openYList.push_back(y); 
        //update foundNode data
        hexMatrixCopy.at(x).at(y).setXParent(xCurrent); //update parent
        hexMatrixCopy.at(x).at(y).setYParent(yCurrent);
        hexMatrixCopy.at(x).at(y).setTotalCost(currentNodeTotal + newNodeCost); //update total cost
        hexMatrixCopy.at(x).at(y).setStatus(1); //update node status
        //check if player2 won
        if (x == (getSize()-1)) { 
          return 2; 
        }
      }
      //if the neighbour node is (same player) && (visited)...
      else if (hexMatrixCopy.at(x).at(y).getColor() == player && hexMatrixCopy.at(x).at(y).getStatus() == 1 ) {
        int newPathCost = currentNodeTotal + newNodeCost;
        int oldPathCost = hexMatrixCopy.at(x).at(y).getTotalCost();
        if ( newPathCost < oldPathCost) { //if new path is lest cost than old path, update the node.
          hexMatrixCopy.at(x).at(y).setXParent(xCurrent); //update parent
          hexMatrixCopy.at(x).at(y).setYParent(yCurrent);
          hexMatrixCopy.at(x).at(y).setTotalCost(newPathCost); //update total cost
        }
      }
      //go here if neighbour node is (!= colour) || (popped)...
      else { 
        //Do nothing
      }
    }
    
    //When the code reaches here it should be done pushing all currentNode's neighbours
    hexMatrixCopy.at(xCurrent).at(yCurrent).setStatus(2); //set node status to popped
    openXList.erase(openXList.begin()); //pop current node from open list
    openYList.erase(openYList.begin());
  
    //if there are nodes left in the open list assign current node to next node
    if (openXList.size() > 0) { 
      xCurrent = openXList.at(0); //assigning current node to the next node.
      yCurrent = openYList.at(0);
    }
  }
  return 0;
}


//perform path finding and print the winner of the Game
void hexBoard::printWinner(void) {
  int winPlayer2;

  for (int i = 0; i < getSize(); i++) {
    winPlayer2 = determineWinnerUpDown(0, i);
    if (winPlayer2 == 2) { break; } //if a winning path is found. stop checking.
  }
  
  //if player 2 did not win then player 1 wins
  if (winPlayer2 == 2) {
    cout << "\tPlayer 2 wins" << endl << endl;
  } else {
    cout << "\tPlayer 1 wins" << endl << endl;
  }
}


//define overloaded << operator used for printing out the hexBoard
ostream& operator<<(ostream& out, hexBoard& hexBoard) {
  int border = 30;
  char label = 'a';
  
  out << endl << setw(4*border/5) << " hexBoard size " << hexBoard.getSize() << endl << endl << "     ";
  
  //ALL THE LETTERS asdlfkjahsdflahhasjk
  for(int i = 0; i < (hexBoard.getSize()); i++) {
    out << static_cast<char>(label + i) << " ";
  }
  //--------------------------------------
  out << endl << setw(3);
  for(int i = 0; i < (hexBoard.getSize()*2+3); i++) {
    out <<  "-";
  }
  for(int i = 0; i < (hexBoard.getSize()); i++) {
    out << endl << setw(i+border-28) << (i+1) << " \\ ";
    for(int j = 0; j < (hexBoard.getSize()); j++) {
      out << hexBoard.getGrid().at(i).at(j).getColor() << " ";
    }
    out << "\\ ";
  }
  out << endl << setw(15);
  //-----------------------------------------
  for(int i = 0; i < (hexBoard.getSize()*2+3); i++) {
    out << "-";
  }
  return out;
}


//runs the program.
int main() {
  srand(time(0)); //seed the random number generate based on time.
  int hexSize = 11; //controls how big the board is. currently specified to an 11x11 board
  
  hexBoard test1(hexSize); 
  test1.randomizedEndGame();
  cout << test1 << endl << endl;
  test1.printWinner();
  
  return 0; //EXIT SUCCESSFUL.
}

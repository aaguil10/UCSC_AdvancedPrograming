#include "Board.h"
#include <pthread.h>
#include <thread>
#include <time.h>

using namespace std;
using namespace chrono;

Board::Board(){
  winner = 0;
  initStartingBoard();
  visited.resize(size);
  for (int i = 0; i<size; i++){
    visited[i].resize(size);
  }
}

Board::Board(int input){
  size = input;
  initStartingBoard();
  winner = 0;
  visited.resize(size);
  for (int i = 0; i<size; i++){
    visited[i].resize(size);
  }
}

void Board::initStartingBoard(){

  board.resize(size);
  quickBoard.resize(size);

  for(int i = 0; i < size; i++){
    quickBoard[i].resize(size);
  }

  Edge* temp;
  Edge* tempPrev;
  Edge* tempFwd;

  //This part creates the nodes, and connects them much like an adjacency list.
  for (int i = 0; i < size; i++){
    board[i] = new Edge(0);
    temp = board[i];

    for(int j = 0; j < size; j++){
      quickBoard[i][j] = temp;
      temp->neighbors[0] = new Edge(0);
      temp->x = i; temp->y = j;
      tempPrev = temp;
      temp = temp->neighbors[0];
      temp->neighbors[1] = tempPrev;
    }
    quickBoard[0][i]->neighbors[1] = NULL;
  }
  quickBoard[0][0]->neighbors[5] = NULL;
  quickBoard[0][0]->neighbors[2] = NULL;
  quickBoard[0][0]->neighbors[3] = NULL;

  quickBoard[size-1][0]->neighbors[5] = NULL;
  quickBoard[size-1][size-1]->neighbors[4] = NULL;
  quickBoard[size-1][size-1]->neighbors[2] = NULL;
  quickBoard[0][size-1]->neighbors[2] = NULL;


  //Once they're all connected there, I take care of special cases.

  //This loop connects all the top nodes to the ones below them.
  board[0]->neighbors[4] = board[1];
  temp = board[0]->neighbors[0];
  tempPrev = board[1];

  while(temp != NULL){
    temp->neighbors[3] = NULL;
    temp->neighbors[2] = NULL;
    temp->neighbors[5] = tempPrev;
 
    if (tempPrev->neighbors[0])
      temp->neighbors[4] = tempPrev->neighbors[0];
    temp = temp->neighbors[0];
    tempPrev = tempPrev->neighbors[0];
  }

  //This loop connects all the bottom nodes to the ones above them.
  temp = board[size-1];
  tempPrev = board[size-2];

  while(temp->neighbors[0] != NULL){
    temp->neighbors[3] = tempPrev;
    temp->neighbors[4] = tempPrev->neighbors[0];
    temp = temp->neighbors[0];
    tempPrev = tempPrev->neighbors[0];
  }

  temp->neighbors[3] = tempPrev;
  
  //This loop connects the rest of the nodes in the middle.
  for (int i = 1; i < size-1; i++){
    temp = board[i];
    tempPrev = board[i-1];
    tempFwd = board[i+1];

    temp->neighbors[4] = tempFwd;
    temp->neighbors[3] = tempPrev;
    temp->neighbors[2] = tempPrev->neighbors[0];

    temp = temp->neighbors[0];
    tempPrev = tempPrev->neighbors[0];

    while(temp->neighbors[0] != NULL){
      temp->neighbors[3] = tempPrev;
      temp->neighbors[2] = tempPrev->neighbors[0];
      temp->neighbors[5] = tempFwd;
      temp->neighbors[4] = tempFwd->neighbors[0];

      temp = temp->neighbors[0];
      tempPrev = tempPrev->neighbors[0];
      tempFwd = tempFwd->neighbors[0];
    }

    temp->neighbors[3] = tempPrev;
    temp->neighbors[5] = tempFwd;
    temp->neighbors[4] = tempFwd->neighbors[0];
  }
}

int Board::printB(Board *b){
  /*
   1   2   3   4   5   6   7...
   __  __  __  __  __  __  __
  /  \/  \/  \/  \/  \/  \/  \
1 |  ||  ||  ||  ||  ||  ||  |_
   \/  \/  \/  \/  \/  \/  \/  \
2   |  ||  ||  ||  ||  ||  ||  |_
     \/  \/  \/  \/  \/  \/  \/  \
3     |  ||  ||  ||  ||  ||  ||  |_
       \/  \/  \/  \/  \/  \/  \/  \
4       |  ||  ||  ||  ||  ||  ||  |
.       \__/\__/\__/\__/\__/\__/\__/
.
  */

  string gap = " ";
  string extraGap = " ";
  int counter = 10;
  
  //This part prints the first row in the board.
  cout << "   ";
  for (int i = 1; i<=b->getSize(); i++){
    if (i < 10){
      cout << i << "   ";
    } else {
      cout << i << "  ";
    }
  }

  cout << "\n";
  cout << "   ";
  for (int i = 0; i<b->getSize(); i++){
    cout << "__  ";
  }

  cout << "\n  ";
  for (int i = 0; i<b->getSize(); i++){
    cout << "/  \\";
  }

  cout << "\n";
  //This prints the center
  for (int i = 0; i<b->getSize(); i++){
    if (i == counter-1){
      gap.resize(gap.size()-1);
      extraGap.append(" ");
      counter = counter*10;
    }
    cout << i+1 << gap;

    for (int j = 0; j<b->getSize(); j++){
      if (b->getNode(i, j)->value != 0){
	cout << "|" << b->getNode(i, j)->value << " |";
      } else {
	cout << "|  |"; 
      }
    }
    
    cout << "_" << endl;
    gap.append(" ");
    cout << gap << extraGap;
    
    for (int j = 0; j<b->getSize(); j++){
      cout << "\\/  ";
    }
    cout << '\\' << endl;
    gap.append(" ");
  }
 
  return 0;
}

int Board::getWinner(){ //This is the main call to the function which calculatesthe winner.

   for (int i = 0; i < size; i++){
     if (visited[i][0] == 0 && quickBoard[i][0]->value == 1)
       searchOne(quickBoard[i][0]);
     if (winner == 1){return 1;}
   }
   return 2;
}

int Board::getWinner(Edge* input){
  side1 = false;
  side2 = false;
  winner = 0;
  visited.clear();
  visited.resize(size);
  for (int i = 0; i<size; i++){
    visited[i].resize(size);
  }
  if (input->value == 1)
    searchSpecificNodeOne(input);
  else if (input->value == 2)
    searchSpecificNodeTwo(input);

  return winner;
}

//player 2 wants to connect from top to bottom
Edge* Board::searchSpecificNodeTwo(Edge* input){
  if (winner == 2)
    return NULL;

  Edge* temp = input;
  visited[input->x][input->y] = 1;

  if (temp == quickBoard[0][temp->y])
    side2 = true;

  if (temp == quickBoard[size-1][temp->y])
    side1 = true;

  if (side1 && side2){
    winner = 2;
    return NULL;
  }

  for (int i = 0; i < 6; ++i){
    if (temp->neighbors[i]){
      if (temp->neighbors[i]->value == 2 && visited[temp->neighbors[i]->x][temp->neighbors[i]->y] == 0){
        searchSpecificNodeTwo(temp->neighbors[i]);
      }
    }

    if (winner == 2){
      return NULL;
    }
  }

  return NULL;
}

//player 1 wants to connect from left to right
Edge* Board::searchSpecificNodeOne(Edge* input){
  if (winner == 1)
    return NULL;

  Edge* temp = input;
  visited[input->x][input->y] = 1;

  if (temp == quickBoard[temp->x][0])
    side2 = true;

  if (temp == quickBoard[temp->x][size-1])
    side1 = true;

  if (side1 && side2){
    winner = 1;
    return NULL;
  }

  for (int i = 0; i < 6; ++i){
    if (temp->neighbors[i]){
      if (temp->neighbors[i]->value == 1 && visited[temp->neighbors[i]->x][temp->neighbors[i]->y] == 0){
	searchSpecificNodeOne(temp->neighbors[i]);
      }
    }

    if (winner == 1){
      return NULL;
    }
  }

  return NULL;
}

//player 1 wants to connect from left to right
Edge* Board::searchOne(Edge* input){//This is a recursive function that works like DFS.
  if (winner == 1)
    return NULL;

  Edge* temp = input;
  visited[input->x][input->y] = 1;

  if (temp == quickBoard[temp->x][size-1]){
    winner = 1;
    return NULL;
  }
  
  for (int i = 0; i < 6; ++i){
    if (temp->neighbors[i]){
	if (temp->neighbors[i]->value == 1 && visited[temp->neighbors[i]->x][temp->neighbors[i]->y] == 0){
	  searchOne(temp->neighbors[i]);
	}
    }
    
    if (winner == 1){
      return NULL;
    }
  }

  return NULL;
}


void Board::printNode(int x, int y){
  cout << "printing node " << x << ", " << y << ": ";
  cout << quickBoard[y-1][x-1]->value << endl;
}



int Board::multiThreader(vector<Edge*> takenEdgesInput, Board *b){
  b->total = 0;
  b->takenEdges = takenEdgesInput;
 
  thread first (&Board::MontiCarloLooper, this);
  thread second (&Board::MontiCarloLooper, this);
 
  first.join();
  second.join();
 
  return total;
}


void Board::MontiCarloLooper(){
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis1(0, ((size*size)-turns));
  for (int i = 0; i < 1000; i++)
    MontiCarlo(dis1, gen);

}

void Board::MontiCarlo(uniform_real_distribution<> dis2, mt19937 gen1){
 random_device rd;
  mt19937 gen(rd());

  Board *finalBoard = new Board(size);
  Board *boardOfNotTaken = new Board(size);
  vector <Edge*> listToRandomize;

  for (int i = 0; i < takenEdges.size(); i++){
    //The final board must have the pieces we've started with.
    finalBoard->quickBoard[takenEdges[i]->x][takenEdges[i]->y]->value = takenEdges[i]->value;

    //Delete nodes which have a pre-existing value.
    boardOfNotTaken->quickBoard[takenEdges[i]->x][takenEdges[i]->y]->value = -1;
  }

  //We start with player one because it must currently be the player's turn. 
  int playerTurn = 1;

  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      
      if (boardOfNotTaken->quickBoard[i][j]-> value != -1){

	//All the nodes which do not have a value are to be pushed into a one dimensional list for randomizing.
	listToRandomize.push_back(boardOfNotTaken->quickBoard[i][j]);

	//They are also given an alternating value, depending on whose turn it is.
	if (playerTurn == 1){
	  boardOfNotTaken->quickBoard[i][j]->value = 1;
	  playerTurn = 2;
	} else {
	  boardOfNotTaken->quickBoard[i][j]->value = 2;
	  playerTurn = 1;
	}

      }
    }  
  }
  
  uniform_real_distribution<> dis1(0, listToRandomize.size()-1);
  int holder, randomNum;
  //cout << "second one: " << listToRandomize.size()-1 << endl;

  //swaps values for the list of nodes we've determined to be untouched.
  for (int i = 0; i <listToRandomize.size(); i++){
    randomNum = dis1(gen);
    holder = listToRandomize[i]->value;
    listToRandomize[i]->value = listToRandomize[randomNum]->value;
    listToRandomize[randomNum]->value = holder;
  }

  for (int i = 0; i < listToRandomize.size(); i++){
    finalBoard->quickBoard[listToRandomize[i]->x][listToRandomize[i]->y]->value = listToRandomize[i]->value;  
  }
  if (finalBoard->getWinner() == 1){
    mtx.lock();
    total++;
    mtx.unlock();
  }
}

void Board::initBoard(){
  board.resize(size);
  quickBoard.resize(size);
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(1, 3);

  for(int i = 0; i < size; i++){
    quickBoard[i].resize(size);
  }

  Edge* temp;
  Edge* tempPrev;
  Edge* tempFwd;
  //This part creates the nodes, and connects them much like an adjacency list.
  for (int i = 0; i < size; i++){
    board[i] = new Edge((int) dis(gen));
    temp = board[i];
    
    for(int j = 0; j < size; j++){
      quickBoard[i][j] = temp;
      temp->neighbors[0] = new Edge((int) dis(gen));
      temp->x = i; temp->y = j;
      tempPrev = temp;
      temp = temp->neighbors[0];
      temp->neighbors[1] = tempPrev;
    }
  }

  //Once they're all connected there, I take care of special cases.

  //This loop connects all the top nodes to the ones below them.
  board[0]->neighbors[4] = board[1];
  temp = board[0]->neighbors[0];
  tempPrev = board[1];

  while(temp != NULL){
    temp->neighbors[5] = tempPrev;
    temp->neighbors[4] = tempPrev->neighbors[0];
    temp = temp->neighbors[0];
    tempPrev = tempPrev->neighbors[0];
  }

  //This loop connects all the bottom nodes to the ones above them.
  temp = board[size-1];
  tempPrev = board[size-2];

  while(temp->neighbors[0] != NULL){
    temp->neighbors[3] = tempPrev;
    temp->neighbors[4] = tempPrev->neighbors[0];
    temp = temp->neighbors[0];
    tempPrev = tempPrev->neighbors[0];
  }
  temp->neighbors[3] = tempPrev;

  //This loop connects the rest of the nodes in the middle.
  for (int i = 1; i < size-1; i++){
    temp = board[i];
    tempPrev = board[i-1];
    tempFwd = board[i+1];

    temp->neighbors[4] = tempFwd;
    temp->neighbors[3] = tempPrev;
    temp->neighbors[2] = tempPrev->neighbors[0];

    temp = temp->neighbors[0];
    tempPrev = tempPrev->neighbors[0];

    while(temp->neighbors[0] != NULL){
      temp->neighbors[3] = tempPrev;
      temp->neighbors[2] = tempPrev->neighbors[0];
      temp->neighbors[5] = tempFwd;
      temp->neighbors[4] = tempFwd->neighbors[0];
      temp = temp->neighbors[0];
      tempPrev = tempPrev->neighbors[0];
      tempFwd = tempFwd->neighbors[0];
    }

    temp->neighbors[3] = tempPrev;
    temp->neighbors[5] = tempFwd;
    temp->neighbors[4] = tempFwd->neighbors[0];
  }
}

#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <thread> 
#include <pthread.h>
#include <chrono> 
#include "BoardController.h"
#include "Board.h"

using namespace std;

BoardController::BoardController(int sizeInput){
  gameBoard = new Board(sizeInput);
  size = sizeInput;
  gameBoard->printB(gameBoard);
  turn = 0;
  winner = 0;
  mainGame();
}

void BoardController::mainGame(){
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(1, 3);
  int currentTurn;
  int x, y;

  cout << "Welcome to Hex! Where my AI is made up and the simulations don't matter." << endl;
  cout << "User wants to go from top to bottom and PC wants to go from left to right." << endl;
  cout << "Flipping coin to see who goes first... " << endl;
    std::this_thread::sleep_for (std::chrono::seconds(2));

  currentTurn = (int) dis(gen);
  cout << currentTurn << endl;

  while(winner == 0){
    if (currentTurn == 1){
      turn++;
      gameBoard->turns = turn;
      currentTurn = 2;
      cout << "PC's turn!" << endl;
      simulate(); 
      
    } else {
      currentTurn = 1;
      cout << "User's turn! (enter input in this format: x, y)" << endl;
      cin >> x;
      cin >> y;
      if (!CapturePoint(x, y, 2)){
	currentTurn = 2;
      } else {
	winner = gameBoard->getWinner(gameBoard->quickBoard[x-1][y-1]);
	turn++;
      }
    }
  }

  cout << winner << " wins this round!" << endl;
}


//Changes the value of a specified node to player
bool BoardController::CapturePoint(int x, int y, int player){
  if  (gameBoard->quickBoard[x-1][y-1]->value != 0){
    cout << "This position is already taken. Try again!" << endl;
    return false;
  } else {
    //add node to list of preset nodes
    takenEdges.push_back(gameBoard->quickBoard[x-1][y-1]);
    
    //set node input to player number and print
    gameBoard->quickBoard[x-1][y-1]->value = player;
    gameBoard->printB(gameBoard);
    return true;
  }
}

//PC player is #1.
int BoardController::simulate(){
  
  if (turn == 1){
    CapturePoint(6, 6, 1);
    return 1;
  } else if (turn == 2){
    if (gameBoard->quickBoard[6][6]->value != 0){
      CapturePoint(5, 6, 1);
      return 1;
    } else {
      CapturePoint(size/2, size/2, 1);
      return 1;
    }
  }
  
  int numOfSimulations = 1000;
  double winRate;
  Board * tempBoard = new Board(size);
  int wins = 0;

  //NODE SELECTION LOGIC
  //Step one: collect all nodes which belong to PC.
  vector<Edge*> PCEdges;
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      if (gameBoard->quickBoard[i][j]->value == 1){
	PCEdges.push_back(gameBoard->quickBoard[i][j]);
      }
    }
  }

  //Step two: Collect all nodes which are either connected to PC
  //          or are at most 1 jump away.
  
  vector<Edge*> viableEdges;
  bool isTaken[size][size];

  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      isTaken[i][j] = false;
    }  
  }

  
  for (int i = 0; i < PCEdges.size(); i++){
    for (int j = 0; j < 6; j++){
      //If the neighbor is empty...
      if (PCEdges[i]->neighbors[j])
	if (PCEdges[i]->neighbors[j]->value == 0 && 
	    isTaken[PCEdges[i]->neighbors[j]->x][PCEdges[i]->neighbors[j]->y] == false){

	  //add it to the stack.
	  viableEdges.push_back(PCEdges[i]->neighbors[j]);
	  isTaken[PCEdges[i]->neighbors[j]->x][PCEdges[i]->neighbors[j]->y] = true;
	}
    }
  }
  
  //Step three: add to the stacks the edges connected to our current viableEdges list.
  //           (We want to search for nodes that are 1 jump away from our current nodes.)
  int currentSize = viableEdges.size();
  for (int i = 0; i < currentSize; i++){
    for (int j = 0; j < 6; j++){
      if (viableEdges[i]->neighbors[j]){
	if (viableEdges[i]->neighbors[j]->value == 0 &&
	    isTaken[viableEdges[i]->neighbors[j]->x][viableEdges[i]->neighbors[j]->y] == false){

	  viableEdges.push_back(viableEdges[i]->neighbors[j]);
	  isTaken[viableEdges[i]->neighbors[j]->x][viableEdges[i]->neighbors[j]->y] = true;
	}
      }
    }
  }

  //Iterate through all possible entries and select the best one
  Edge* bestEdge;// = viableEdges[0];
  int bestWinRate = 0;
  tempBoard->turns = turn;
  for (int i = 0; i < viableEdges.size(); i++){
    takenEdges.push_back(viableEdges[i]);
    
    wins = tempBoard->multiThreader(takenEdges, tempBoard);
    cout << wins << endl;

    if (bestWinRate < wins){
      bestEdge = viableEdges[i];
      bestWinRate = wins;
    }

    wins = 0;
    takenEdges.pop_back();
  }
  
  winRate = (double) bestWinRate/((double) 4000);
  cout << "simulation win rate: " << winRate << endl;
  cout << "winning node: " << bestEdge->x+1 << " " << bestEdge->y+1 << endl;
  CapturePoint(bestEdge->x+1, bestEdge->y+1, 1);
  winner = gameBoard->getWinner(gameBoard->quickBoard[bestEdge->x][bestEdge->y]);

  return 0;
}

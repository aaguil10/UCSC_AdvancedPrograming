//threadedHex.cpp - Implements threadedHex.h
//Author: Matt Caruano
//Date: 3/12/2014

#include <iostream>
#include <random>  //For a better random number generator
#include <thread>  //For threadedAIMove
#include <cstdlib>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <utility> //For pair
#include <ctime>
#include "threadedHex.h"

using namespace std;



//************************************Constructor************************************
Hex::Hex(int s)  //Test with and without (int s)
{
	size = s;        
	adjList.resize(size*size);		//Declare the size of the adjacency list so it can be addressed in [i] format

	//Initialize playerMoves and probability vectors
	for (int i = 0; i < (size*size); i++)
	{
		playerMoves.push_back(3);
		unThreadedProbability.push_back(0);
	}
}

//************************************Helper Functions************************************
void clearQueue(queue<int> &q)
//Effectively clears a queue. Code directly copied from 
//that posted by David Rodriguez on Stackoverflow.com.
{
	queue<int> empty;
	swap(q, empty);
}
//************************************************************
int myRandom(int i)
//Used for random shuffles based on a seed. Code verbatum from cplusplus.com
{
	return rand() % i;
}

//************************************Manipulation Functions************************************
bool Hex::makeMove(int horizontal, int vertical)
//Makes a move where the player designates. The player is ALWAYS player 1 (White)
//The first number is the X direction, the second is the Y direction
{
	bool isTop, isLeft, isRight, isBottom;
	int mappedNode = vertical * 11 + horizontal;

	//Make sure the move is legal
	if(!(mappedNode < size*size) || horizontal < 0 || vertical < 0 || playerMoves[mappedNode] != 3)
	{
		return false;
	}

	//Register the move
	playerMoves[mappedNode] = 1;
	//Update neighbors properly
	isTop = isLeft = isRight = isBottom = false;

	if (mappedNode < size)
		isTop = true;  //Don't add it as a neighbor to mappedNode-10, mappedNode-11
	if ((mappedNode % size) == 0)
		isLeft = true; //Don't add it as a neighbor to mappedNode-1, mappedNode+10
	if ((mappedNode + 1) % size == 0)
		isRight = true; //Don't add it as a neighbor to mappedNode+1, mappedNode-10
	if (mappedNode >= ((size*size) - size))
		isBottom = true; //Don't add it as a neighbor to mappedNode+10, mappedNode+11

	if (mappedNode == 0)  //This is the top-left corner
	{
		//Add mappedNode to mappedNode+1 and mappedNode+11's adjacency lists only
		adjList[mappedNode + 1].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode + 11].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		return true;
	}

	if (mappedNode == (size - 1))  //This is the top-right corner
	{
		//Add mappedNode to mappedNode-1, mappedNode+10, and mappedNode+11's adjacency lists only
		adjList[mappedNode - 1].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode + 10].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode + 11].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		return true;
	}

	if (mappedNode == ((size*size) - size))  //This is the bottom-left corner
	{
		//Add mappedNode to mappedNode+1, mappedNode-10, and mappedNode-11's adjacency lists only
		adjList[mappedNode + 1].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode - 10].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode - 11].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		return true;
	}

	if (mappedNode == ((size*size) - 1))  //This is the bottom-right corner
	{
		//Add mappedNode to mappedNode-1 and mappedNode-11's adjacency lists only
		adjList[mappedNode - 1].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode - 11].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		return true;
	}

	if (isTop)
	{
		//Add mappedNode to mappedNode-1, mappedNode+1, mappedNode+10 and mappedNode+11's adjacency lists only
		adjList[mappedNode - 1].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode + 1].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode + 10].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode + 11].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		return true;
	}

	if (isLeft)
	{
		//Add mappedNode to mappedNode+1, mappedNode-10, mappedNode-11 and mappedNode+11's adjacency lists only
		adjList[mappedNode + 1].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode - 10].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode - 11].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode + 11].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		return true;
	}

	if (isRight)
	{
		//Add mappedNode to mappedNode-1, mappedNode-11, mappedNode+10, and mappedNode+11's adjacency lists only
		adjList[mappedNode - 1].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode - 11].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode + 10].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode + 11].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		return true;
	}

	if (isBottom)
	{
		//Add mappedNode to mappedNode-1, mappedNode+1, mappedNode-10, and mappedNode-11's adjacency lists only
		adjList[mappedNode - 1].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode + 1].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode - 10].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		adjList[mappedNode - 11].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
		return true;
	}

	//Otherwise, mappedNode has 6 neighbors, and needs to be added to each of their adjacency lists
	adjList[mappedNode - 1].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
	adjList[mappedNode + 1].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
	adjList[mappedNode - 10].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
	adjList[mappedNode - 11].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
	adjList[mappedNode + 10].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
	adjList[mappedNode + 11].push_back(make_pair(mappedNode, playerMoves[mappedNode]));
	return true;
}
//************************************************************
void Hex::unThreadedAIMove(int simulations)
{
	srand(static_cast<unsigned>(time(0)));

	bool isTop, isLeft, isRight, isBottom;
	int currentEvalMove = -1;
	int whiteMovesMade = 0;
	int blackMovesMade = 0;
	int whiteMovesRemaining = 0;
	int blackMovesRemaining = 0;
	int totalMovesRemaining = 0;
	int blackMovesRemainingCopy = 0;
	int whiteMovesRemainingCopy = 0;
	double blackWinCount = 0;
	bool whiteNeighbor = false;
	vector<bool> alreadyTested (size*size, false);        //contains the nodes that have already been tested
	vector< vector< pair<int, int> > > adjListCopy;		  //Used to preserve originals and try a specific move
	vector<int> playerMovesCopy;						  //Used to preserve originals and try a specific move
	vector< vector< pair<int, int> > > simulationAdjList; //Used in individual simulations on a given move
	vector<int> simulationPlayerMoves;					  //Used in individual simulations on a given move
	vector<int> randomMoves;

	//Clear the probability vector
	for (int i = 0; i < (size*size); i++)
	{
		unThreadedProbability[i] = 0;
	}

	//Determine how many moves each player has made so far, so we can
	//determine how many moves each player has left
	for (int i = 0; i < (size*size); i++)
	{
		if (playerMoves[i] == 1)
		{
			whiteMovesMade++;
		}
	}
	blackMovesMade = whiteMovesMade - 1;
	totalMovesRemaining = size*size - (blackMovesMade + whiteMovesMade);
	whiteMovesRemaining = blackMovesRemaining = totalMovesRemaining / 2;

	//Main simulation loop for evaluation of all available moves
	for (int i = 0; i < totalMovesRemaining; i++)
	{
		//Copy the adjList and playerMoves data structures
		adjListCopy = adjList;
		playerMovesCopy = playerMoves;

		//Pick the first available board spot
		for (int i = 0; i < (size*size); i++)
		{
			if (playerMoves[i] != 3 || alreadyTested[i] == true)
				continue;
			else
			{
				currentEvalMove = i;
				alreadyTested[currentEvalMove] = true;
				playerMovesCopy[currentEvalMove] = 2;

				//*************************************************************************************************
				//Add currentEvalMove to the adjListCopy adjacency list
				isTop = isLeft = isRight = isBottom = false;	
				if (i < size)
					isTop = true;  //Don't add it as a neighbor to i-10, i-11
				if ((i % size) == 0)
					isLeft = true; //Don't add it as a neighbor to i-1, i+10
				if ((i + 1) % size == 0)
					isRight = true; //Don't add it as a neighbor to i+1, i-10
				if (i >= ((size*size) - size))
					isBottom = true; //Don't add it as a neighbor to i+10, i+11

				if (i == 0)  //This is the top-left corner
				{
					//Add i to i+1 and i+11's adjacency lists only
					adjListCopy[i + 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				if (i == (size - 1))  //This is the top-right corner
				{
					//Add i to i-1, i+10, and i+11's adjacency lists only
					adjListCopy[i - 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 10].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				if (i == ((size*size) - size))  //This is the bottom-left corner
				{
					//Add i to i+1, i-10, and i-11's adjacency lists only
					adjListCopy[i + 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 10].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				if (i == ((size*size) - 1))  //This is the bottom-right corner
				{
					//Add i to i-1 and i-11's adjacency lists only
					adjListCopy[i - 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				if (isTop)
				{
					//Add i to i-1, i+1, i+10 and i+11's adjacency lists only
					adjListCopy[i - 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 10].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				if (isLeft)
				{
					//Add i to i+1, i-10, i-11 and i+11's adjacency lists only
					adjListCopy[i + 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 10].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 11].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				if (isRight)
				{
					//Add i to i-1, i-11, i+10, and i+11's adjacency lists only
					adjListCopy[i - 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 11].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 10].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				if (isBottom)
				{
					//Add i to i-1, i+1, i-10, and i-11's adjacency lists only
					adjListCopy[i - 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 10].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				//Otherwise, i has 6 neighbors, and needs to be added to each of their adjacency lists
				adjListCopy[i - 1].push_back(make_pair(i, playerMovesCopy[i]));
				adjListCopy[i + 1].push_back(make_pair(i, playerMovesCopy[i]));
				adjListCopy[i - 10].push_back(make_pair(i, playerMovesCopy[i]));
				adjListCopy[i - 11].push_back(make_pair(i, playerMovesCopy[i]));
				adjListCopy[i + 10].push_back(make_pair(i, playerMovesCopy[i]));
				adjListCopy[i + 11].push_back(make_pair(i, playerMovesCopy[i]));
			    //*************************************************************************************************

				break;
			}
		}

		//Recopy the data structures for use in individual simulations
		simulationAdjList = adjListCopy;
		simulationPlayerMoves = playerMovesCopy;
		blackMovesRemainingCopy = blackMovesRemaining - 1; //We just made a move
		whiteMovesRemainingCopy = whiteMovesRemaining;
		blackWinCount = 0;

		//Run as many simulations on that move as desired
		for (int j = 0; j < simulations; j++)
		{
			//Fill up the moves vector so it can be shuffled
			for (int i = 0; i < blackMovesRemainingCopy; i++)
			{
				randomMoves.push_back(2);
			}
			for (int i = 0; i < whiteMovesRemainingCopy; i++)
			{
				randomMoves.push_back(1);
			}

			//Shuffle the vector, thus generating random moves for each player
			random_shuffle(randomMoves.begin(), randomMoves.end(), myRandom);

			//Enter the moves
			for (int i = 0; i < (size*size); i++)
			{
				if (simulationPlayerMoves[i] != 3)
					continue;
				else
				{
					simulationPlayerMoves[i] = randomMoves.back();
					randomMoves.pop_back();
				}							
			}

			//*************************************************************************************************
			//Actually make each of the randomly generated moves by updating the necessary adjacency lists 
			for (int i = 0; i < (size*size); i++)
			{
				isTop = isLeft = isRight = isBottom = false;

				//If this move was not a simulated move, continue
				if (playerMoves[i] != 3)
					continue;

				//Otherwise, insert it
				if (i < size)
					isTop = true;  //Don't add it as a neighbor to i-10, i-11
				if ((i % size) == 0)
					isLeft = true; //Don't add it as a neighbor to i-1, i+10
				if ((i + 1) % size == 0)
					isRight = true; //Don't add it as a neighbor to i+1, i-10
				if (i >= ((size*size) - size))
					isBottom = true; //Don't add it as a neighbor to i+10, i+11

				if (i == 0)  //This is the top-left corner
				{
					//Add i to i+1 and i+11's adjacency lists only
					simulationAdjList[i + 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				if (i == (size - 1))  //This is the top-right corner
				{
					//Add i to i-1, i+10, and i+11's adjacency lists only
					simulationAdjList[i - 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 10].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				if (i == ((size*size) - size))  //This is the bottom-left corner
				{
					//Add i to i+1, i-10, and i-11's adjacency lists only
					simulationAdjList[i + 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 10].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				if (i == ((size*size) - 1))  //This is the bottom-right corner
				{
					//Add i to i-1 and i-11's adjacency lists only
					simulationAdjList[i - 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				if (isTop)
				{
					//Add i to i-1, i+1, i+10 and i+11's adjacency lists only
					simulationAdjList[i - 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 10].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				if (isLeft)
				{
					//Add i to i+1, i-10, i-11 and i+11's adjacency lists only
					simulationAdjList[i + 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 10].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				if (isRight)
				{
					//Add i to i-1, i-11, i+10, and i+11's adjacency lists only
					simulationAdjList[i - 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 10].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				if (isBottom)
				{
					//Add i to i-1, i+1, i-10, and i-11's adjacency lists only
					simulationAdjList[i - 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 10].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				//Otherwise, i has 6 neighbors, and needs to be added to each of their adjacency lists
				simulationAdjList[i - 1].push_back(make_pair(i, simulationPlayerMoves[i]));
				simulationAdjList[i + 1].push_back(make_pair(i, simulationPlayerMoves[i]));
				simulationAdjList[i - 10].push_back(make_pair(i, simulationPlayerMoves[i]));
				simulationAdjList[i - 11].push_back(make_pair(i, simulationPlayerMoves[i]));
				simulationAdjList[i + 10].push_back(make_pair(i, simulationPlayerMoves[i]));
				simulationAdjList[i + 11].push_back(make_pair(i, simulationPlayerMoves[i]));
			}//*************************************************************************************************

			//Determine the winner ******************************
			vector<int> wColor(size*size, 0);
			queue<int> wQueue;
			string winner = "Black";

			//Run BFS from nodes 0, size, (2* size), ... up until (size-1)*size
			//(This is specifically checking if White is the winner)
			for (int i = 0; i < size; i++)
			{
				//BFS from node [i*size]
				//If player 1 didn't play that node, or the node is colored, continue
				if (simulationPlayerMoves[i*size] != 1 || wColor[i*size] == 2)
					continue;

				clearQueue(wQueue);
				wColor[i*size] = 1;
				wQueue.push(i*size);
				while (!wQueue.empty())
				{
					int u = wQueue.front();
					int v;
					for (int i = 0; i < simulationAdjList[u].size(); i++)
					{
						//Only process White neighbors
						if ((simulationAdjList[u][i]).second != 1)
							continue;

						//If the neighbor is a winning neighbor, breakout of for loop
						for (int j = 1; j <= size; j++)
						{
							if ((simulationAdjList[u][i]).first == j*size - 1)
							{
								winner = "White";
								break;
							}
						}

						//If the winner was found, break out of for loop
						if (winner == "White")
							break;

						//Push the neighbor onto the stack
						v = (simulationAdjList[u][i]).first;
						if (wColor[v] == 0)
						{
							wQueue.push(v);
							wColor[v] = 1;
						}
					}

					//If the winner was found, break out of the while loop
					if (winner == "White")
						break;

					wQueue.pop();
					wColor[u] = 2;
				}

				//If the winner was found, break out of the for loop
				if (winner == "White")
					break;
			}
			//***************************************************

			if (winner == "Black")
				blackWinCount++;

			//Reset the simulation-specific data structures
			simulationAdjList = adjListCopy;
			simulationPlayerMoves = playerMovesCopy;
		}

		//Update the probability
		unThreadedProbability[currentEvalMove] = blackWinCount / static_cast<double>(simulations); 
	}

	//Select the move with the highest probability of winning
	int bestMove = 0;
	for (int i = 0; i < (size*size); i++)
	{
		if (unThreadedProbability[i] >= unThreadedProbability[bestMove])
		{
			bestMove = i;
		}
	}
	playerMoves[bestMove] = 2;

	//*************************************************************************************************
	//Make that move
	isTop = isLeft = isRight = isBottom = false;
	if (bestMove < size)
		isTop = true;  //Don't add it as a neighbor to bestMove-10, bestMove-11
	if ((bestMove % size) == 0)
		isLeft = true; //Don't add it as a neighbor to bestMove-1, bestMove+10
	if ((bestMove + 1) % size == 0)
		isRight = true; //Don't add it as a neighbor to bestMove+1, bestMove-10
	if (bestMove >= ((size*size) - size))
		isBottom = true; //Don't add it as a neighbor to bestMove+10, bestMove+11

	if (bestMove == 0)  //This is the top-left corner
	{
		//Add bestMove to bestMove+1 and bestMove+11's adjacency lists only
		adjList[bestMove + 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	if (bestMove == (size - 1))  //This is the top-right corner
	{
		//Add bestMove to bestMove-1, bestMove+10, and bestMove+11's adjacency lists only
		adjList[bestMove - 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	if (bestMove == ((size*size) - size))  //This is the bottom-left corner
	{
		//Add bestMove to bestMove+1, bestMove-10, and bestMove-11's adjacency lists only
		adjList[bestMove + 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	if (bestMove == ((size*size) - 1))  //This is the bottom-right corner
	{
		//Add bestMove to bestMove-1 and bestMove-11's adjacency lists only
		adjList[bestMove - 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	if (isTop)
	{
		//Add bestMove to bestMove-1, bestMove+1, bestMove+10 and bestMove+11's adjacency lists only
		adjList[bestMove - 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	if (isLeft)
	{
		//Add bestMove to bestMove+1, bestMove-10, bestMove-11 and bestMove+11's adjacency lists only
		adjList[bestMove + 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	if (isRight)
	{
		//Add bestMove to bestMove-1, bestMove-11, bestMove+10, and bestMove+11's adjacency lists only
		adjList[bestMove - 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	if (isBottom)
	{
		//Add bestMove to bestMove-1, bestMove+1, bestMove-10, and bestMove-11's adjacency lists only
		adjList[bestMove - 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	//Otherwise, bestMove has 6 neighbors, and needs to be added to each of their adjacency lists
	adjList[bestMove - 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
	adjList[bestMove + 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
	adjList[bestMove - 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
	adjList[bestMove - 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
	adjList[bestMove + 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
	adjList[bestMove + 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
	//*************************************************************************************************

	return;  //The best move has now officially been made

}
//************************************************************
void fractionalAIMove(vector<double>& probability, int n, Hex& h)
{
	srand(static_cast<unsigned>(time(0)));

	bool isTop, isLeft, isRight, isBottom;
	int currentEvalMove = -1;
	int whiteMovesMade = 0;
	int blackMovesMade = 0;
	int whiteMovesRemaining = 0;
	int blackMovesRemaining = 0;
	int totalMovesRemaining = 0;
	int blackMovesRemainingCopy = 0;
	int whiteMovesRemainingCopy = 0;
	double blackWinCount = 0;
	bool whiteNeighbor = false;
	vector<bool> alreadyTested(h.size*h.size, false);        //contains the nodes that have already been tested
	vector< vector< pair<int, int> > > adjListCopy;		  //Used to preserve originals and try a specific move
	vector<int> playerMovesCopy;						  //Used to preserve originals and try a specific move
	vector< vector< pair<int, int> > > simulationAdjList; //Used in individual simulations on a given move
	vector<int> simulationPlayerMoves;					  //Used in individual simulations on a given move
	vector<int> randomMoves;

	//Clear the probability vector
	for (int i = 0; i < (h.size*h.size); i++)
	{
		probability[i] = 0;
	}

	//Determine how many moves each player has made so far, so we can
	//determine how many moves each player has left
	for (int i = 0; i < (h.size*h.size); i++)
	{
		if (h.playerMoves[i] == 1)
		{
			whiteMovesMade++;
		}
	}
	blackMovesMade = whiteMovesMade - 1;
	totalMovesRemaining = h.size*h.size - (blackMovesMade + whiteMovesMade);
	whiteMovesRemaining = blackMovesRemaining = totalMovesRemaining / 2;

	//Main simulation loop for evaluation of all available moves
	for (int i = 0; i < totalMovesRemaining; i++)
	{
		//Copy the adjList and playerMoves data structures
		adjListCopy = h.adjList;
		playerMovesCopy = h.playerMoves;

		//Pick the first available board spot
		for (int i = 0; i < (h.size*h.size); i++)
		{
			if (h.playerMoves[i] != 3 || alreadyTested[i] == true)
				continue;
			else
			{
				currentEvalMove = i;
				alreadyTested[currentEvalMove] = true;
				playerMovesCopy[currentEvalMove] = 2;

				//*************************************************************************************************
				//Add currentEvalMove to the adjListCopy adjacency list
				isTop = isLeft = isRight = isBottom = false;
				if (i < h.size)
					isTop = true;  //Don't add it as a neighbor to i-10, i-11
				if ((i % h.size) == 0)
					isLeft = true; //Don't add it as a neighbor to i-1, i+10
				if ((i + 1) % h.size == 0)
					isRight = true; //Don't add it as a neighbor to i+1, i-10
				if (i >= ((h.size*h.size) - h.size))
					isBottom = true; //Don't add it as a neighbor to i+10, i+11

				if (i == 0)  //This is the top-left corner
				{
					//Add i to i+1 and i+11's adjacency lists only
					adjListCopy[i + 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				if (i == (h.size - 1))  //This is the top-right corner
				{
					//Add i to i-1, i+10, and i+11's adjacency lists only
					adjListCopy[i - 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 10].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				if (i == ((h.size*h.size) - h.size))  //This is the bottom-left corner
				{
					//Add i to i+1, i-10, and i-11's adjacency lists only
					adjListCopy[i + 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 10].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				if (i == ((h.size*h.size) - 1))  //This is the bottom-right corner
				{
					//Add i to i-1 and i-11's adjacency lists only
					adjListCopy[i - 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				if (isTop)
				{
					//Add i to i-1, i+1, i+10 and i+11's adjacency lists only
					adjListCopy[i - 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 10].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				if (isLeft)
				{
					//Add i to i+1, i-10, i-11 and i+11's adjacency lists only
					adjListCopy[i + 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 10].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 11].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				if (isRight)
				{
					//Add i to i-1, i-11, i+10, and i+11's adjacency lists only
					adjListCopy[i - 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 11].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 10].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				if (isBottom)
				{
					//Add i to i-1, i+1, i-10, and i-11's adjacency lists only
					adjListCopy[i - 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i + 1].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 10].push_back(make_pair(i, playerMovesCopy[i]));
					adjListCopy[i - 11].push_back(make_pair(i, playerMovesCopy[i]));
					break;
				}

				//Otherwise, i has 6 neighbors, and needs to be added to each of their adjacency lists
				adjListCopy[i - 1].push_back(make_pair(i, playerMovesCopy[i]));
				adjListCopy[i + 1].push_back(make_pair(i, playerMovesCopy[i]));
				adjListCopy[i - 10].push_back(make_pair(i, playerMovesCopy[i]));
				adjListCopy[i - 11].push_back(make_pair(i, playerMovesCopy[i]));
				adjListCopy[i + 10].push_back(make_pair(i, playerMovesCopy[i]));
				adjListCopy[i + 11].push_back(make_pair(i, playerMovesCopy[i]));
				//*************************************************************************************************

				break;
			}
		}

		//Recopy the data structures for use in individual simulations
		simulationAdjList = adjListCopy;
		simulationPlayerMoves = playerMovesCopy;
		blackMovesRemainingCopy = blackMovesRemaining - 1; //We just made a move
		whiteMovesRemainingCopy = whiteMovesRemaining;
		blackWinCount = 0;

		//Run as many simulations on that move as desired
		for (int j = 0; j < n; j++)
		{
			//Fill up the moves vector so it can be shuffled
			for (int i = 0; i < blackMovesRemainingCopy; i++)
			{
				randomMoves.push_back(2);
			}
			for (int i = 0; i < whiteMovesRemainingCopy; i++)
			{
				randomMoves.push_back(1);
			}

			//Shuffle the vector, thus generating random moves for each player
			random_shuffle(randomMoves.begin(), randomMoves.end(), myRandom);

			//Enter the moves
			for (int i = 0; i < (h.size*h.size); i++)
			{
				if (simulationPlayerMoves[i] != 3)
					continue;
				else
				{
					simulationPlayerMoves[i] = randomMoves.back();
					randomMoves.pop_back();
				}
			}

			//*************************************************************************************************
			//Actually make each of the randomly generated moves by updating the necessary adjacency lists 
			for (int i = 0; i < (h.size*h.size); i++)
			{
				isTop = isLeft = isRight = isBottom = false;

				//If this move was not a simulated move, continue
				if (h.playerMoves[i] != 3)
					continue;

				//Otherwise, insert it
				if (i < h.size)
					isTop = true;  //Don't add it as a neighbor to i-10, i-11
				if ((i % h.size) == 0)
					isLeft = true; //Don't add it as a neighbor to i-1, i+10
				if ((i + 1) % h.size == 0)
					isRight = true; //Don't add it as a neighbor to i+1, i-10
				if (i >= ((h.size*h.size) - h.size))
					isBottom = true; //Don't add it as a neighbor to i+10, i+11

				if (i == 0)  //This is the top-left corner
				{
					//Add i to i+1 and i+11's adjacency lists only
					simulationAdjList[i + 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				if (i == (h.size - 1))  //This is the top-right corner
				{
					//Add i to i-1, i+10, and i+11's adjacency lists only
					simulationAdjList[i - 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 10].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				if (i == ((h.size*h.size) - h.size))  //This is the bottom-left corner
				{
					//Add i to i+1, i-10, and i-11's adjacency lists only
					simulationAdjList[i + 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 10].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				if (i == ((h.size*h.size) - 1))  //This is the bottom-right corner
				{
					//Add i to i-1 and i-11's adjacency lists only
					simulationAdjList[i - 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				if (isTop)
				{
					//Add i to i-1, i+1, i+10 and i+11's adjacency lists only
					simulationAdjList[i - 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 10].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				if (isLeft)
				{
					//Add i to i+1, i-10, i-11 and i+11's adjacency lists only
					simulationAdjList[i + 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 10].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				if (isRight)
				{
					//Add i to i-1, i-11, i+10, and i+11's adjacency lists only
					simulationAdjList[i - 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 10].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				if (isBottom)
				{
					//Add i to i-1, i+1, i-10, and i-11's adjacency lists only
					simulationAdjList[i - 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i + 1].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 10].push_back(make_pair(i, simulationPlayerMoves[i]));
					simulationAdjList[i - 11].push_back(make_pair(i, simulationPlayerMoves[i]));
					continue;
				}

				//Otherwise, i has 6 neighbors, and needs to be added to each of their adjacency lists
				simulationAdjList[i - 1].push_back(make_pair(i, simulationPlayerMoves[i]));
				simulationAdjList[i + 1].push_back(make_pair(i, simulationPlayerMoves[i]));
				simulationAdjList[i - 10].push_back(make_pair(i, simulationPlayerMoves[i]));
				simulationAdjList[i - 11].push_back(make_pair(i, simulationPlayerMoves[i]));
				simulationAdjList[i + 10].push_back(make_pair(i, simulationPlayerMoves[i]));
				simulationAdjList[i + 11].push_back(make_pair(i, simulationPlayerMoves[i]));
			}//*************************************************************************************************

			//Determine the winner ******************************
			vector<int> wColor(h.size*h.size, 0);
			queue<int> wQueue;
			string winner = "Black";

			//Run BFS from nodes 0, size, (2* size), ... up until (size-1)*size
			//(This is specifically checking if White is the winner)
			for (int k = 0; k < h.size; k++)
			{
				//BFS from node [i*size]
				//If player 1 didn't play that node, or the node is colored, continue
				if (simulationPlayerMoves[k*h.size] != 1 || wColor[k*h.size] == 2)
					continue;

				clearQueue(wQueue);
				wColor[k*h.size] = 1;
				wQueue.push(k*h.size);
				while (!wQueue.empty())
				{
					int u = wQueue.front();
					int v;
					for (int m = 0; m < simulationAdjList[u].size(); m++)
					{
						//Only process White neighbors
						if ((simulationAdjList[u][m]).second != 1)
							continue;

						//If the neighbor is a winning neighbor, breakout of for loop
						for (int j = 1; j <= h.size; j++)
						{
							if ((simulationAdjList[u][m]).first == j*h.size - 1)
							{
								winner = "White";
								break;
							}
						}

						//If the winner was found, break out of for loop
						if (winner == "White")
							break;

						v = (simulationAdjList[u][m]).first;
						if (wColor[v] == 0)
						{
							wQueue.push(v);
							wColor[v] = 1;
						}
					}

					//If the winner was found, break out of the while loop
					if (winner == "White")
						break;

					wQueue.pop();
					wColor[u] = 2;
				}

				//If the winner was found, break out of the for loop
				if (winner == "White")
					break;
			}
			//***************************************************

			if (winner == "Black")
				blackWinCount++;

			//Reset the simulation-specific data structures
			simulationAdjList = adjListCopy;
			simulationPlayerMoves = playerMovesCopy;
		}

		//Update the probability
		probability[currentEvalMove] = blackWinCount / static_cast<double>(n);
	}

	return;
}
//************************************************************
void Hex::threadedAIMove(int simulations)
{
	//10 Separate probability vectors, will be summed after the simulations
	vector<double> prob1, prob2, prob3, prob4, prob5, prob6, prob7, prob8, prob9, prob10, sumProbs;
	bool isTop, isLeft, isRight, isBottom;
	int numSimulations = simulations / 10;

	//Initialize probability vectors
	for (int i = 0; i < (size*size); i++)
	{
		prob1.push_back(0);
		prob2.push_back(0);
		prob3.push_back(0);
		prob4.push_back(0);
		prob5.push_back(0);
		prob6.push_back(0);
		prob7.push_back(0);
		prob8.push_back(0);
		prob9.push_back(0);
		prob10.push_back(0);
		sumProbs.push_back(0);
	}

	//Create the threads
	thread first(fractionalAIMove, ref(prob1), numSimulations, *this);
	thread second(fractionalAIMove, ref(prob2), numSimulations, *this);
	thread third(fractionalAIMove, ref(prob3), numSimulations, *this);
	thread fourth(fractionalAIMove, ref(prob4), numSimulations, *this);
	thread fifth(fractionalAIMove, ref(prob5), numSimulations, *this);
	thread sixth(fractionalAIMove, ref(prob6), numSimulations, *this);
	thread seventh(fractionalAIMove, ref(prob7), numSimulations, *this);
	thread eighth(fractionalAIMove, ref(prob8), numSimulations, *this);
	thread ninth(fractionalAIMove, ref(prob9), numSimulations, *this);
	thread tenth(fractionalAIMove, ref(prob10), numSimulations, *this);
	first.join();
	second.join();
	third.join();
	fourth.join();
	fifth.join();
	sixth.join();
	seventh.join();
	eighth.join();
	ninth.join();
	tenth.join();

	//Sum all of the probability vectors up
	for (int i = 0; i < (size*size); i++)
	{
		sumProbs[i] = (prob1[i] + prob2[i] + prob3[i] + prob4[i] + prob5[i] + prob6[i] + prob7[i] + prob8[i] + prob9[i] + prob10[i]) / static_cast<double>(10);
	}


	//Select the move with the highest probability of winning
	int bestMove = 0;
	for (int i = 0; i < (size*size); i++)
	{
		if (sumProbs[i] >= sumProbs[bestMove])
		{
			bestMove = i;
		}
	}
	playerMoves[bestMove] = 2;

	//*************************************************************************************************
	//Make that move
	isTop = isLeft = isRight = isBottom = false;
	if (bestMove < size)
		isTop = true;  //Don't add it as a neighbor to bestMove-10, bestMove-11
	if ((bestMove % size) == 0)
		isLeft = true; //Don't add it as a neighbor to bestMove-1, bestMove+10
	if ((bestMove + 1) % size == 0)
		isRight = true; //Don't add it as a neighbor to bestMove+1, bestMove-10
	if (bestMove >= ((size*size) - size))
		isBottom = true; //Don't add it as a neighbor to bestMove+10, bestMove+11

	if (bestMove == 0)  //This is the top-left corner
	{
		//Add bestMove to bestMove+1 and bestMove+11's adjacency lists only
		adjList[bestMove + 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	if (bestMove == (size - 1))  //This is the top-right corner
	{
		//Add bestMove to bestMove-1, bestMove+10, and bestMove+11's adjacency lists only
		adjList[bestMove - 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	if (bestMove == ((size*size) - size))  //This is the bottom-left corner
	{
		//Add bestMove to bestMove+1, bestMove-10, and bestMove-11's adjacency lists only
		adjList[bestMove + 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	if (bestMove == ((size*size) - 1))  //This is the bottom-right corner
	{
		//Add bestMove to bestMove-1 and bestMove-11's adjacency lists only
		adjList[bestMove - 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	if (isTop)
	{
		//Add bestMove to bestMove-1, bestMove+1, bestMove+10 and bestMove+11's adjacency lists only
		adjList[bestMove - 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	if (isLeft)
	{
		//Add bestMove to bestMove+1, bestMove-10, bestMove-11 and bestMove+11's adjacency lists only
		adjList[bestMove + 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	if (isRight)
	{
		//Add bestMove to bestMove-1, bestMove-11, bestMove+10, and bestMove+11's adjacency lists only
		adjList[bestMove - 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	if (isBottom)
	{
		//Add bestMove to bestMove-1, bestMove+1, bestMove-10, and bestMove-11's adjacency lists only
		adjList[bestMove - 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove + 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
		adjList[bestMove - 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
		return;
	}

	//Otherwise, bestMove has 6 neighbors, and needs to be added to each of their adjacency lists
	adjList[bestMove - 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
	adjList[bestMove + 1].push_back(make_pair(bestMove, playerMoves[bestMove]));
	adjList[bestMove - 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
	adjList[bestMove - 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
	adjList[bestMove + 10].push_back(make_pair(bestMove, playerMoves[bestMove]));
	adjList[bestMove + 11].push_back(make_pair(bestMove, playerMoves[bestMove]));
	//*************************************************************************************************

	return;  //The best move has now officially been made
}
//************************************************************
void Hex::randomPlay()
//Fill the board with entirely random moves
{
	srand(static_cast<unsigned>(time(0)));

	int playerWithExtraMove;
	random_device rd;
	bool isTop, isLeft, isRight, isBottom;
	playerMoves.clear();

	//Randomly decide which player gets the extra move, either player 1 or player 2
	playerWithExtraMove = static_cast<int>(rd() % 2) + 1;
	playerMoves.push_back(playerWithExtraMove);

	//Of the remaining moves, give each player an equal amount
	for (int i = 0; i < ((size*size)/2); i++)
	{
		playerMoves.push_back(1);
		playerMoves.push_back(2);
	}

	//Shuffle the vector, thus generating random moves for each player
	random_shuffle(playerMoves.begin(), playerMoves.end(), myRandom);

	//Actually make the moves and update the graph
	for (int i = 0; i < (size*size); i++)
	{
		isTop = isLeft = isRight = isBottom = false;

		if (i < size)
			isTop = true;  //Don't add it as a neighbor to i-10, i-11
		if ((i % size) == 0)
			isLeft = true; //Don't add it as a neighbor to i-1, i+10
		if ((i + 1) % size == 0)
			isRight = true; //Don't add it as a neighbor to i+1, i-10
		if (i >= ((size*size) - size))
			isBottom = true; //Don't add it as a neighbor to i+10, i+11

		if (i == 0)  //This is the top-left corner
		{
			//Add i to i+1 and i+11's adjacency lists only
			adjList[i + 1].push_back(make_pair(i, playerMoves[i]));
			adjList[i + 11].push_back(make_pair(i, playerMoves[i]));
			continue;
		}

		if (i == (size-1))  //This is the top-right corner
		{
			//Add i to i-1, i+10, and i+11's adjacency lists only
			adjList[i - 1].push_back(make_pair(i, playerMoves[i]));
			adjList[i + 10].push_back(make_pair(i, playerMoves[i]));
			adjList[i + 11].push_back(make_pair(i, playerMoves[i]));
			continue;
		}

		if (i == ((size*size) - size))  //This is the bottom-left corner
		{
			//Add i to i+1, i-10, and i-11's adjacency lists only
			adjList[i + 1].push_back(make_pair(i, playerMoves[i]));
			adjList[i - 10].push_back(make_pair(i, playerMoves[i]));
			adjList[i - 11].push_back(make_pair(i, playerMoves[i]));
			continue;
		}

		if (i == ((size*size) - 1))  //This is the bottom-right corner
		{
			//Add i to i-1 and i-11's adjacency lists only
			adjList[i - 1].push_back(make_pair(i, playerMoves[i]));
			adjList[i - 11].push_back(make_pair(i, playerMoves[i]));
			continue;
		}

		if (isTop)
		{
			//Add i to i-1, i+1, i+10 and i+11's adjacency lists only
			adjList[i - 1].push_back(make_pair(i, playerMoves[i]));
			adjList[i + 1].push_back(make_pair(i, playerMoves[i]));
			adjList[i + 10].push_back(make_pair(i, playerMoves[i]));
			adjList[i + 11].push_back(make_pair(i, playerMoves[i]));
			continue;
		}

		if (isLeft)
		{
			//Add i to i+1, i-10, i-11 and i+11's adjacency lists only
			adjList[i + 1].push_back(make_pair(i, playerMoves[i]));
			adjList[i - 10].push_back(make_pair(i, playerMoves[i]));
			adjList[i - 11].push_back(make_pair(i, playerMoves[i]));
			adjList[i + 11].push_back(make_pair(i, playerMoves[i]));
			continue;
		}

		if (isRight)
		{
			//Add i to i-1, i-11, i+10, and i+11's adjacency lists only
			adjList[i - 1].push_back(make_pair(i, playerMoves[i]));
			adjList[i - 11].push_back(make_pair(i, playerMoves[i]));
			adjList[i + 10].push_back(make_pair(i, playerMoves[i]));
			adjList[i + 11].push_back(make_pair(i, playerMoves[i]));
			continue;
		}

		if (isBottom)
		{
			//Add i to i-1, i+1, i-10, and i-11's adjacency lists only
			adjList[i - 1].push_back(make_pair(i, playerMoves[i]));
			adjList[i + 1].push_back(make_pair(i, playerMoves[i]));
			adjList[i - 10].push_back(make_pair(i, playerMoves[i]));
			adjList[i - 11].push_back(make_pair(i, playerMoves[i]));
			continue;
		}

		//Otherwise, i has 6 neighbors, and needs to be added to each of their adjacency lists
		adjList[i - 1].push_back(make_pair(i, playerMoves[i]));
		adjList[i + 1].push_back(make_pair(i, playerMoves[i]));
		adjList[i - 10].push_back(make_pair(i, playerMoves[i]));
		adjList[i - 11].push_back(make_pair(i, playerMoves[i]));
		adjList[i + 10].push_back(make_pair(i, playerMoves[i]));
		adjList[i + 11].push_back(make_pair(i, playerMoves[i]));
	}
}

//************************************Access Functions************************************
char Hex::translatePlayer(int pointOnBoard)
{
	if (playerMoves[pointOnBoard] == 1)
		return 'O';
	else if (playerMoves[pointOnBoard] == 2)
		return 'X';
	else
		return '-';
}
//************************************************************
string Hex::determineWinner()
{
	//Check if White is the winner ******************************
	vector<int> wColor(size*size, 0);
	queue<int> wQueue;

	//Run BFS from nodes 0, size, (2* size), ... up until (size-1)*size
	//(This is specifically checking if White is the winner)
	for (int i = 0; i < size; i++)
	{
		//BFS from node [i*size]
		//If player 1 didn't play that node, or the node is colored, continue
		if (playerMoves[i*size] != 1 || wColor[i*size] == 2)
			continue;

		clearQueue(wQueue);
		wColor[i*size] = 1;
		wQueue.push(i*size);
		while (!wQueue.empty())
		{
			int u = wQueue.front();
			int v;
			//Evaluate all of u's neighbors
			for (int i = 0; i < adjList[u].size(); i++)
			{
				//Only process White neighbors
				if ((adjList[u][i]).second != 1) 
					continue;

				//If the neighbor is a winning neighbor, return
				for (int j = 1; j <= size; j++)
				{
					if ((adjList[u][i]).first == j*size - 1)
						return "White";
				}

				v = (adjList[u][i]).first;
				if (wColor[v] == 0)
				{
					wQueue.push(v);
					wColor[v] = 1;
				}
			}

			wQueue.pop();
			wColor[u] = 2;
		}
	}

	//Check if Black is the winner ******************************
	vector<int> bColor(size*size, 0);
	queue<int> bQueue;

	//Run BFS from nodes 0, 1, 2, ... , size-1
	//(This is specifically checking if Black is the winner)
	for (int i = 0; i < size; i++)
	{
		//BFS from node [i]
		//If player 2 didn't play that node, or the node is colored, continue
		if (playerMoves[i] != 2 || bColor[i] == 2)
			continue;

		clearQueue(bQueue);
		bColor[i] = 1;
		bQueue.push(i);
		while (!bQueue.empty())
		{
			int u = bQueue.front();
			int v;
			for (int i = 0; i < adjList[u].size(); i++)
			{
				//Only process Black neighbors
				if ((adjList[u][i]).second != 2)
					continue;

				//If the neighbor is a winning neighbor, return
				for (int j = ((size*size)-size); j <= (size*size); j++)
				{
					if ((adjList[u][i]).first == j)
						return "Black";
				}

				v = (adjList[u][i]).first;
				if (bColor[v] == 0)
				{
					bQueue.push(v);
					bColor[v] = 1;
				}
			}

			bQueue.pop();
			bColor[u] = 2;
		}
	}

	return "No one";  //No one has won yet
}

//************************************Friend Functions************************************
ostream& operator<<(ostream& out, Hex& h)
{
	int nodeNum = 0;

	//Print top board label
	out << "     ";
	for (int i = 0; i < h.getSize() / 2; i++)
	{
		out << " ";
	}
	out << "Black (X)\n";

	//Print top number labels
	out << "  ";
	for (int i = 0; i < h.getSize(); i++)
	{
		out << setw(2) << i;
	}


	//Print top border
	out << "\n  ";
	for (int i = 0; i < h.getSize() - 3; i++)
	{
		out << "___";
	}

	for (int i = 0; i < h.getSize(); i++)
	{
		out << "\n";

		//Add the slant to the board
		for (int k = 0; k < i; k++)
		{
			if (i == 6)
			{
				out << "White ";
				break;
			}

			if (i == 7)
			{
				out << " (O)   ";
				break;
			}

			if (i == 9)
			{
				out << "         ";
				break;
			}

			if (i == 10)
			{
				out << "         ";
				break;
			}

			out << " ";
		}

		out << i << " \\";

		//Output the row
		for (int j = 0; j < h.getSize(); j++)
		{
			out << setw(2) << h.translatePlayer(nodeNum);
			nodeNum++;
		}

		out << " \\";

		if (i == 6)
		{
			out << " White";
		}
	}

	//Print bottom border
	out << "\n";

	for (int i = 0; i < h.getSize() + 2; i++)
	{
		out << " ";
	}

	for (int i = 0; i < h.getSize() - 3; i++)
	{
		out << "---";
	}

	//Print bottom board label
	out << "\n";
	for (int i = 0; i < h.getSize() + 6; i++)
	{
		out << " ";
	}

	out << setw((2 * h.getSize()) / 2) << "Black\n";

	return out;
}
//************************************Helper Functions************************************
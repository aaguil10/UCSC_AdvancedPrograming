//threadedHexGame.cpp
//Author: Matt Caruano
//Date: 3/12/2014
//Generates an 11x11 hex board, accepts input from the user in the form of X Y pairs, and generates a move
//using AI implemented in threadedHex.h. It prints out the board state after every move, and stops
//when a winner has been determined, and announces which player has won.

#include <iostream>
#include <string>
#include <ctime> //For time analysis
#include "threadedHex.h"

using namespace std;

int main()
{
	int horizontal, vertical;
	bool validMove = false;
	string winner = "No one";
	Hex* game = new Hex();

	/*
	//Time analysis
	Hex* testGame1 = new Hex();
	Hex* testGame2 = new Hex();
	float unThreadedRT, threadedRT;
	(*testGame1).makeMove(5, 5);
	(*testGame2).makeMove(5, 5);

	//Testing move with no threading
	clock_t timeStamp = clock();
	cout << "Calculating unthreaded move..." << endl;
	(*testGame1).unThreadedAIMove(1000);
	timeStamp = clock() - timeStamp;
	unThreadedRT = (static_cast<float>(timeStamp) / CLOCKS_PER_SEC);

	//Testing move with ten threads
	timeStamp = clock();
	cout << "Calculating threaded move..." << endl;
	(*testGame2).threadedAIMove(1000);
	timeStamp = clock() - timeStamp;
	threadedRT = (static_cast<float>(timeStamp) / CLOCKS_PER_SEC);

	cout << "********** Unthreaded Game **********" << endl;
	cout << *testGame1 << endl;
	cout << "Move was made in " << unThreadedRT << " seconds." << endl << endl;
	cout << "*********** Threaded Game ***********" << endl;
	cout << *testGame2 << endl;
	cout << "Move was made in " << threadedRT << " seconds." << endl;
	*/
	
	

	cout << *game << endl;
	cout << "Specify your move in by entering the coordinates separated by a space." << endl;
	cout << "The first coordinate is the X coordinate." << endl;
	cin >> horizontal >> vertical;
	validMove = (*game).makeMove(horizontal, vertical);
	while (!validMove)
	{
		cout << "Invalid move, please re-enter. Valid moves are in the range 0-10 0-10." << endl;
		cin >> horizontal >> vertical;
		validMove = (*game).makeMove(horizontal, vertical);
	}
	cout << *game << endl;

	while (winner == "No one")
	{
		//Run AI move
		cout << "Black is thinking..." << endl;
		(*game).threadedAIMove(1000);
		cout << *game << endl; // Show the move the AI just made
		winner = (*game).determineWinner();
		if (winner == "Black") //The AI just won.
		{
			cout << *game << endl;
			break;
		}

		cout << "Enter your next move: ";
		cin >> horizontal >> vertical;
		validMove = (*game).makeMove(horizontal, vertical);
		while (!validMove)
		{
			cout << "Invalid move, please re-enter. Valid moves are in the range 0-10 0-10." << endl;
			cin >> horizontal >> vertical;
			validMove = (*game).makeMove(horizontal, vertical);
		}
		cout << *game << endl; //Show the move the player just made
		winner = (*game).determineWinner();
	}

	cout << winner << " wins!" << endl;

	//system("PAUSE");  //Enable to prevent the output window from closing after the winner has been determined
	return 0;
}
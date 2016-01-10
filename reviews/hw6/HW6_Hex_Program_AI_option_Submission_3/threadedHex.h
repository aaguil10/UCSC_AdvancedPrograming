//threadedHex.h
//Author: Matt Caruano
//Date: 3/12/2014
//Provides tools for generating an 11x11 hex gameboard and either randomly populating it
//or taking input from a user and making the move and generating individual random moves
//in response. The program assumes the client is the first player.

#pragma once
#include <vector>
#include <iomanip>
using namespace std;

class Hex{

public:
	friend ostream& operator<<(ostream& out, Hex& h);	

	Hex(int s = 11);
	void randomPlay();
	inline int getSize(){ return size; };
	char translatePlayer(int pointOnBoard);
	bool makeMove(int horizontal, int vertical);  //Bool to determine if the move was legal or not
	void unThreadedAIMove(int simulations); 
	void threadedAIMove(int simulations);
	string determineWinner();
	~Hex(){};	

private:
	int size;
	vector< vector< pair<int, int> > > adjList;   //An adjacency list of (node, player) pairs
	vector<int> playerMoves; //Contains either a 1, 2, or 3 indicating which player occupies that position, 3 being empty
	vector<double> unThreadedProbability; //Store the calculated probability of winning for each move
	friend void fractionalAIMove(vector<double>& probability, int n, Hex& h);
};
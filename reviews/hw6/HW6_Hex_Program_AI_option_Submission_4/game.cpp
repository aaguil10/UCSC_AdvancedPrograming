//Alexander Sadeghi, Delan Diaz

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "game.h"
#include "hexGraph.h"
#include "hexBoard.h"
using namespace std;

ostream& operator<<(ostream &out, Space sp) {
	if(sp == EMPTY)
		out << "-";
	else if(sp == BLACK)
		out << "B";
	else
		out<< "R";
	return out;
}

//This function gets the coordinates for the spot on the graph
//the player would like to make his next move on
pair<int, int> Game::getPlayerMove() {
        int coord = 0;
        int x;
        int y;
        cout << "Player is RED" << endl;
        cout << "CPU is BLACK" << endl;
        while(true) {
            if (coord == 0) {
                cout << "Enter move coordinate X: ";
                cin >> x;
            } else if (coord == 1) {
                cout << "Enter move coordinate Y: ";
                cin >> y;
            } else break;
	    coord++;
        }
        return pair<int, int>(x, y);
}
    
//main loop of the game
void Game::play() {
	Space winner;
    	bool playerWentFirst = true;
    	hexGraph gameGraph(board);
    	int AIMoveIndex = -1;
    	while(true) {
        	turn++;
        	drawBoard();
        	if (AIMoveIndex != -1) { // Remind the player of where the CPU went
        	    	pair<int, int> comMove = board->getCoords(AIMoveIndex);
            		cout << "Black just moved (" << comMove.first << ", " << comMove.second << ")." << endl;
        	}
		movePlayer(turn == 1 && !playerWentFirst); // Pass whether the pi rule is in effect
        	drawBoard();
		if ((winner = gameGraph.checkWinner(board))) break;
        	cout << "Calculating CPU move" << endl;
        	AIMoveIndex = gameGraph.getAIMove(*board, ai_monte_carlo_iterations, ai_plies, 
BLACK);//calcultae AI move
        	board->setSpace(AIMoveIndex, BLACK);
		if ((winner = gameGraph.checkWinner(board))) break;
    	}
    	drawBoard();
    	if (winner == RED){
		cout << "Player Wins!" << endl;
		win = 0;
	}
    	if (winner == BLACK){ 
		cout << "CPU Player Wins!" << endl;
		win = 1;
	}
}

void Game::movePlayer(bool isTurn){
	pair<int, int> move;
	if (isTurn) cout << "(To use the pie rule, move where the CPU player just did.)" << endl;
    	int badmove = false;
    	do {
        	if (badmove) {
            		drawBoard();
            		cout << "Invalid Move." << endl;
        	}
        	move = getPlayerMove();
        	badmove = true;
    	} while (!board->isValidMove(move.first, move.second, isTurn));
        // Record move in game board
    	board->setSpace(move.first, move.second, RED);
}

void Game::drawBoard() {  
	int height, width;
	height = width = 11;    	
	string vt = "";
    	cout << "\n MOVE #" << turn << " ";   
    	cout << endl << vt << endl;
	const int totalpadding = log10(11);
    	// Print first row of column numbers 
    	cout << vt;
    	for (int i = 0; i < totalpadding + 2; i++) {
        	cout << " ";
    	}

    	for (int j = 0; j < width; j++) {
        	if (j < 10) {
            		cout << "  ";
		}
		else {
	    	cout << j/10 << " ";
		}
    	}
    	cout << endl;
    
    	// Print second row of column numbers
    	cout << vt;
    	for (int i = 0; i < totalpadding + 3; i++) {
        	cout << " ";
    	}

    	for (int j = 0; j < width; j++) {
        	cout << j%10 << " ";
    	}
    	cout << endl;

    	// Print the rows, one by one
    	int intlength;
    	for (int i = height - 1; i >= 0; i--) {
		cout << vt;
        	// Pad the board on the left to make it a parallelogram
	    	for (int j = 0; j < height - i - 1; j++) {
            		cout << " ";
	    	}
        	// Pad the number on the left, so that the board doesn't shift around.
	    	intlength = (i == 0) ? 0 : log10(i);
	    	for (int j = 0; j < totalpadding - intlength; j++) {
            		cout << " ";
	    	}
        	// Print the row nunber
	    	cout << " " << i << "  "; 
        	// Print all of the spaces in the row
	    	for(int j = 0; j < width; j++) {
            		cout << board->getSpace(j, i) << " ";
        	}
        	// Print the row number one more time on the right
	    	cout << " " << i << endl;
    	}
    	// Print first row of column numbers
    	cout << vt;
    	for (int i = 0; i < width + totalpadding + 4; i++) {
        	cout << " ";
    	}
    	for (int j = 0; j < width; j++) {
      		if (j >= 10) cout << j/10 << " ";
	    	else cout << j << " ";
    	}
    	cout << endl;

    	// Print second row of column numbers 
    	cout << vt;
    	for (int i = 0; i < width + totalpadding + 5; i++) {
        	cout << " ";
    	}
    	for (int j = 0; j < width; j++) {
        	if (j < 10) {
            		cout << "  ";
		}
		else {
	    		cout << j%10 << " ";
		}
    	}
    	cout << endl << endl;
}

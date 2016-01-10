#include <iostream>
#include <cstring>
#include <ctime>
#include <vector>
#include "HexBoard.h"
using namespace std;

class HexGame {		// Manages the game
private:
	HexBoard board;
	int turn;			// 1 = P1 -1 = P2
	bool AI;			// true = yes, false = no
public:
	HexGame();			//initialized the game
	bool isNum(string s);	//validation
	void play();			//gameplay
	void promptMove(int &x, int &y, int turn);	//prompt user for coordinates
	void easyBotMove(int &x, int &y);		//simple AI
};

HexGame::HexGame() {
	int size;
	string input;
	char answer;

	while (cout << "Please enter size of board: ", getline(cin, input), !isNum(input));			//validation
	size = atoi(input.c_str());			//set the size of the board

	while (cout << "Play against AI? (y/n): ", getline(cin, input), answer = toupper(input[0]), answer != 'Y' && answer != 'N');	//multiplayer or AI
	if (answer == 'Y') {
		AI = true;
		srand(time(NULL));
	}
	else
		AI = false;

	board = HexBoard(size);		//create board
	turn = 1;
}

void HexGame::easyBotMove(int &x, int &y) {		//Random AI
	int limit = board.getSize();
	x = rand() % limit;
	y = rand() % limit;
}

void HexGame::play() {
	int x, y;
	bool error = false;
	
	while(!board.isFinished(-1*turn)) {		//check for winner
		if (!error) {
			cout << board;
			cout << (turn > 0 ? "Player 1" : "Player 2") << "'s turn:\n";
		}

		(AI && turn < 0) ? easyBotMove(x, y) : promptMove(x, y, turn);		//deciding to use AI or let the 2nd player move

		if (board.set(x, y, turn)) {		//return true if the move is valid
			cout << endl << (turn > 0 ? "Player 1" : "Player 2") << " moved [" << x << ", " << y << "]\n";
			error = false;
			turn = -1 * turn;		//changing the player/turn
		}
		else {
			cout << "Error: Invalid coordinates. ";
			error = true;
		}
	}

	cout << board;
	cout << (-1*turn > 0 ? "Player 1" : "Player 2") << " wins!\n";
}

void HexGame::promptMove(int &x, int &y, int turn) {		//prompting the player 
	string input;

	while (cout << "Please enter x-coordinate: ", getline(cin, input), !isNum(input));
	x = atoi(input.c_str());
	while (cout << "Please enter y-coordinate: ", getline(cin, input), !isNum(input));
	y = atoi(input.c_str());
}

bool HexGame::isNum(string s) {			//validating
	for (int i = 0; i < strlen(s.c_str()); i++)
		if (!isdigit(s[i]))
			return false;
	return true;
}

int main() {
	HexGame hex;
	hex.play();

	return 0;
}

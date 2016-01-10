//Builds a hex board out of the element "hexTile"
//Allows you to play a game against an AI opponent
//Uses Monte Carlo method to determine best possible move
//Prints filled board using overloaded << operator

#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <random>
#include <cassert>
#include <thread>

using namespace std;

class hexTile{

public:
	//Coordinates and associated team number for each tile
	int x = 0;
	int y = 0;
	int team = 0;

	//Constructors
	hexTile(int inX, int inY){
		x = inX;
		y = inY;
	}

	hexTile(){

	}

	//Friend function for overloading << operator
	friend ostream& operator<< (ostream &output, vector<vector<hexTile> > &board);
};

//Overloads << stream operator with the function for printing the board nicely with labels
ostream& operator<< (ostream &output, vector<vector<hexTile> > &board)
{
	for (int i = 0; i <= 10; ++i){
		if (i > 1){
			cout << "Y";
		}
		cout << (11 - i) << "  ";
		for (int j = 0; j <= 10; ++j){
			output << board[i][j].team << " ";
		}
		output << endl;
		for (int k = 0; k <= i; ++k){
			output << " ";
		}
	}
	cout << endl;
	for (int l = 0; l <= 13; ++l){
		output << " ";
	}
	for (int l = 0; l < 11; ++l){
		if (l < 9){
			output << "X ";
		}
		else{
			output << "1 ";
		}
	}
	cout << endl;
	for (int l = 0; l <= 13; ++l){
		output << " ";
	}
	for (int l = 0; l < 11; ++l){
		output << ((l + 1) % 10) << " ";
	}
	cout << endl;
	return output;
}

//Randomly returns an int 0-10
inline int randVal(int maxNum){
	int val;
	val = maxNum * rand() / RAND_MAX;
	return val;
}

//Initializes the 11 by 11 board and sets all of the tiles' x's and y's to the proper value
vector<vector<hexTile> > initializeBoard(){
	vector<vector<hexTile> > board(11, vector<hexTile>(11));
	for (int i = 0; i <= 10; ++i){
		for (int j = 0; j <= 10; ++j){
			board[i][j].y = i;
			board[i][j].x = j;
		}
	}
	return board;
}

//Recursively runs across tile streaks to check for a win
void checkWin(int i, int j, vector<vector<hexTile> > &board, vector<bool> &visited, bool flat, int &winner){
	int currNode = ((11 * i) + j);
	if ((visited[currNode] == true) || (winner != 0)){
		return;
	}

	//cout << "Checking i = " << i << " j = " << j << " TEAM = " << board[i][j].team << endl;
	visited[currNode] = true;


	int currTeam = board[i][j].team;

	//The proper win check
	if (flat && (j == 10)){
		winner = currTeam;
		//cout << winner << " IS THE WINNER" << endl;
	}

	if (!flat && (i == 10)){
		winner = currTeam;
		//cout << winner << " IS THE WINNER" << endl;
	}

	//Neighbor recursion
	//LEFT
	if (j > 0){
		if (board[i][j - 1].team == currTeam){
			checkWin(i, (j - 1), board, visited, flat, winner);
		}
	}

	//TOP
	if (i > 0){
		if (board[i - 1][j].team == currTeam){
			checkWin((i - 1), j, board, visited, flat, winner);
		}
	}

	//TOP RIGHT
	if ((i > 0) && (j > 10)){
		if (board[i - 1][j + 1].team == currTeam){
			checkWin((i - 1), (j + 1), board, visited, flat, winner);
		}
	}

	//RIGHT
	if (j < 10){
		if (board[i][j + 1].team == currTeam){
			checkWin(i, (j + 1), board, visited, flat, winner);
		}
	}

	//BOTTOM
	if (i < 10){
		if (board[i + 1][j].team == currTeam){
			checkWin((i + 1), j, board, visited, flat, winner);
		}
	}

	//BOTTOM LEFT
	if ((i < 10) && (j < 0)){
		if (board[i + 1][j - 1].team == currTeam){
			checkWin((i + 1), (j - 1), board, visited, flat, winner);
		}
	}

}

//This function that fills a board by choosing a random tile on the board, and if it's open, taking that tile.
int playRandom(vector<vector<hexTile> > &board, vector<int> optionsBase){
	//srand(time(0));
	vector<int> options(121);
	vector<bool> visited(121);
	options = optionsBase;
	int turnNum = 0;
	int currTeam = 1;
	int currIndex = 0;
	int currMove = 0;
	int winner = 0;
	bool flat = true;
	//Board Fill
	do{
		if (currTeam > 2){
			currTeam = 1;
		}
		currIndex = randVal(121 - turnNum);
		assert(currIndex < 121 && currIndex >= 0);
		currMove = options[currIndex];
		int i = currMove / 11;
		int j = currMove % 11;
		if (board[i][j].team == 0){
			board[i][j].team = currTeam;
		}
		int temp = options[(120 - turnNum)];
		options[(120 - turnNum)] = currMove;
		options[currIndex] = temp;
		++turnNum;
		++currTeam;
	} while (turnNum < 121);

	//Initialize visited
	for (int v = 0; v < 121; ++v){
		visited[v] = false;
	}

	//Run through left side
	for (int iVal = 0; iVal <= 10; ++iVal){
		checkWin(iVal, 0, board, visited, true, winner);
	}

	//Reinitialize visited
	for (int v = 0; v < 121; ++v){
		visited[v] = false;
	}

	//Run through top
	for (int jVal = 0; jVal <= 10; ++jVal){
		checkWin(0, jVal, board, visited, false, winner);
	}

	if (winner == 0){
		//cout << "NO WINNER" << endl;
	}

	return winner;
}

//Checks how good a move is using a large number of random boards
double checkMove(int y, int x, vector<vector<hexTile> > board, vector<int> optionsBase){

	vector<vector<hexTile> > baseTestBoard = board;
	double winCount = 0;
	double loseCount = 0;
	double numTests = 100;
	int result = 0;
	if (baseTestBoard[y][x].team == 0){
		baseTestBoard[y][x].team = 2;
	}
	else{
		return 0;
	}

	vector<vector<hexTile> > testBoard = baseTestBoard;

	//Runs through games in which you move places, and seeing if you win
	for (int i = 0; i < numTests; i++){
		result = playRandom(testBoard, optionsBase);
		if (result == 2){
			++winCount;
		}
		testBoard = baseTestBoard;
		result = 0;
	}

	//Runs through games where they move places, and seeing when you lose.
	baseTestBoard[x][y].team = 1;

	for (int i = 0; i < numTests; i++){
		testBoard = baseTestBoard;
		result = 0;
		result = playRandom(testBoard, optionsBase);
		if (result == 1){
			++loseCount;
			//cout << "LOSECOUNT IS: " <<loseCount;
		}
		if (result == 0){
			//cout << "ERROR: CHECK DID NOT SET WINNER";
		}
	}

	//Checking if your opponent is one tile from winning
	if (loseCount == numTests){
		return(numTests * 5);
	}

	//Return a general value that says how "good" the move would be afterwards
	return ((2*winCount) + loseCount);

}

//The four checker functions handled by each of the four threads, all writing to the same vector.
//These run through and systematically check how good every move on the board is.
vector<vector<double> > wins(11, vector<double>(11));

void checkJA(vector<vector<hexTile> > *board, vector<int> *optionsBase){
	
	for (int i = 0; i < 11; ++i){
		for (int j = 0; j < 3; ++j){
			wins[i][j] = checkMove(i, j, *board, *optionsBase);
		}
	}

};

void checkJB(vector<vector<hexTile> > *board, vector<int> *optionsBase){

	for (int i = 0; i < 11; ++i){
		for (int j = 3; j < 6; ++j){
			wins[i][j] = checkMove(i, j, *board, *optionsBase);
		}
	}

};

void checkJC(vector<vector<hexTile> > *board, vector<int> *optionsBase){

	for (int i = 0; i < 11; ++i){
		for (int j = 6; j < 9; ++j){
			wins[i][j] = checkMove(i, j, *board, *optionsBase);
		}
	}

};

void checkJD(vector<vector<hexTile> > *board, vector<int> *optionsBase){

	for (int i = 0; i < 11; ++i){
		for (int j = 9; j < 11; ++j){
			wins[i][j] = checkMove(i, j, *board, *optionsBase);
		}
	}

};

//Calls the system which checks the viability of each seperate 
int checkBoard(vector<vector<hexTile> > board, vector<int> optionsBase){

	for (int i = 0; i < 11; ++i){
		for (int j = 0; j < 11; ++j){
			wins[i][j] = 0;
		}
	}

	int highest = 0;

	//*****
	//SET SEQUENTIAL EQUAL TO TRUE TO CHECK SEQUENTIAL INSTEAD OF MULTITHREADED PROCESSING
	//*****
	bool sequential = false;

	//Sequentially goes through every move when 
	if (sequential){
		for (int i = 0; i < 11; ++i){
			for (int j = 0; j < 11; ++j){
				wins[i][j] = checkMove(i, j, board, optionsBase);
				if (wins[i][j] >= highest){
					highest = ((11 * i) + j);
				}
				//cout << i << " ," << j <<": " << wins[i][j] << endl;
			}
		}
	}

	//Multithreaded function call
	if (!sequential){

		//Start every thread and pass it the required vectors
		//***THIS IS THE PART THAT G++ CAN'T COMPILE
		thread A(checkJA, &board, &optionsBase);
		thread B(checkJB, &board, &optionsBase);
		thread C(checkJC, &board, &optionsBase);
		thread D(checkJD, &board, &optionsBase);

		//Rejoin all the threads
		A.join();
		B.join();
		C.join();
		D.join();

		//Check which was the best move of all the moves on the entire board.
		cout << endl << endl;
		for (int i = 0; i < 11; ++i){
			for (int j = 0; j < 11; ++j){
				//cout << "i: " << i << " j: " << j << " value: " << wins[i][j] << endl;
				if (wins[i][j] >= highest){
					highest = ((11 * i) + j);
				}
			}
		}
		cout << endl << endl;

	}

	//Return the best available move
	cout << "AI MOVES TO X: " << ((highest%11) + 1) << " Y: " << (11-(highest/11)) << endl;
	return highest;

}

int gameWinCheck(vector<vector<hexTile> > board){

	vector<bool> visited(121);
	int winner = 0;

	//Initialize visited
	for (int v = 0; v < 121; ++v){
		visited[v] = false;
	}

	//Run through left side
	for (int iVal = 0; iVal <= 10; ++iVal){
		checkWin(iVal, 0, board, visited, true, winner);
	}

	//Reinitialize visited
	for (int v = 0; v < 121; ++v){
		visited[v] = false;
	}

	//Run through top
	for (int jVal = 0; jVal <= 10; ++jVal){
		checkWin(0, jVal, board, visited, false, winner);
	}

	return winner;

}

//Turns the single returned number into an actual move and makes it
void aiMakeMove(vector<vector<hexTile> > &board, int bestMove){
	int i = bestMove / 11;
	int j = bestMove % 11;
	board[i][j].team = 2;
}

int main(){
	int x;
	int y;
	int winningTeam = 0;
	bool gameOver = false;
	bool inputInvalid = false;
	srand(time(0));

	//Declares board
	vector<vector<hexTile> > board(11, vector<hexTile>(11));

	//Declares options array
	vector<int> optionsBase(121);

	for (int i = 0; i < 121; ++i){
		optionsBase[i] = i;
	}

	//Initializes the board
	board = initializeBoard();

	//GAME LOOP
	do{
		cout << board << endl;
		//Check for winners
		if (gameWinCheck(board) == 2){
			gameOver = true;
			cout << endl << "PLAYER 2 IS THE WINNER!";
			break;
		}
		//Player 1 input move
		do{
			inputInvalid = false;
			cout << "SELECT A TILE." << endl << "X VALUE (1-11): ";
			cin >> x;
			cout << "Y VALUE (1-11): ";
			cin >> y;
			cout << endl;

			if (y < 1 || y > 11 || x < 1 || x > 11){
				inputInvalid = true;
				cout << endl << endl << "THIS MOVE IS INVALID. PLEASE SELECT ANOTHER." << endl << endl;
			}
			else{
				if (board[11 - y][x - 1].team != 0){
					inputInvalid = true;
					cout << endl << "THIS MOVE IS INVALID. PLEASE SELECT ANOTHER." << endl << endl;
				}
			}
		} while (inputInvalid);

		//Make Player 1 move
		board[11 - y][x - 1].team = 1;

		cout << board << endl;

		//Check for a win
		if (gameWinCheck(board) == 1){
			gameOver = true;
			cout << endl << "PLAYER 1 IS THE WINNER!";
			break;
		}

		cout << endl << "AI IS THINKING..." << endl << endl;

		int a = time(0);

		//Calls the entire AI system
		aiMakeMove(board, checkBoard(board, optionsBase));
		
		int b = time(0);

		//Says how long it took
		cout << "DONE IN " << (b - a) << " SECONDS" << endl << endl;
	} while (!gameOver);


	checkBoard(board, optionsBase);

	//Prints the board using overloaded << operator
	//cout << board;
	cin.ignore();
	return 0;
}

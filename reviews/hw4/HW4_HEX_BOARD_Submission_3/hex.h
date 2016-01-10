//CUSTOM HEXGAME CLASS -- Jake VanAdrighem
//ID: 1387294

#include <iostream>
#include <iomanip>

#include "graph.h"

using std::cout;
using std::vector;
using std::endl;
using std::ostream;
using std::setw;

class HexGame{
public:
	HexGame(int inputBoardSize);
	bool verifyMove(int position);
	void makeMove(int position, int player);
	int PlayGame();
	int determineWinner();
	void printPlayer1(){ player1Board->printStructure(); };
	void printPlayer2(){ player2Board->printStructure(); };
	//Overloaded output stream operator
	friend ostream& operator<<(ostream &out, HexGame &inputGame);
private:
	vector<vector<int> > positionAvailable;
	graph* player1Board;
	graph* player2Board;
	int boardSize;
};


HexGame::HexGame(int inputBoardSize){
	boardSize = inputBoardSize;
	positionAvailable.resize(boardSize);
	for(int rowCount = 0; rowCount < boardSize; rowCount++){
		positionAvailable[rowCount].resize(boardSize);
	}
	player1Board = new graph((inputBoardSize * inputBoardSize), 0);
	player2Board = new graph((inputBoardSize * inputBoardSize), 0);
}

bool HexGame::verifyMove(int position){
	if(position > (boardSize * boardSize)) return false;
	int row = position / boardSize;
	int column = position % boardSize;
	if((row > boardSize) || (column > boardSize)) return false;
	if((positionAvailable[row][column] == 1) || (positionAvailable[row][column] == 2)) return false;
	return true;
}

void HexGame::makeMove(int position, int player){
	if((player > 2) || (player < 1)) return;
	int row = position / boardSize;
	int column = position % boardSize;
	positionAvailable[row][column] = player;//Make the position on the board as taken
	vector<vector<int> > tempBoard;
	if(player == 1) tempBoard = player1Board->getGraph();
	if(player == 2) tempBoard = player2Board->getGraph();
	//Allowed moves depend on the position of the node.
	//3 Types of Nodes: Corner, Edge and Inner
	if(position == 0){//Top Left Corner
		if(positionAvailable[row][column + 1] == player){
			tempBoard[position][position + 1] = 1;
		}
		if(positionAvailable[row + 1][column] == player){
			tempBoard[position][position + boardSize] = 1;
			tempBoard[position + boardSize][position] = 1;
		}
		return;
	}
	if(position == boardSize - 1){//Top right corner
		if(positionAvailable[row][column - 1] == player){
			tempBoard[position][position - 1] = 1;
			tempBoard[position - 1][position] = 1;
		}
		if(positionAvailable[row + 1][column] == player){
			tempBoard[position][position + boardSize] = 1;
			tempBoard[position + boardSize][position] = 1;
		}
		return;
	}
	if(position == (((boardSize * boardSize) - 1) - (boardSize - 1))){//Bottom Left Corner
		if(positionAvailable[row][column + 1] == player){
			tempBoard[position][position + 1] = 1;
			tempBoard[position + 1][position] = 1;
		}
		if(positionAvailable[row - 1][column] == player){
			tempBoard[position][position - boardSize] = 1;
			tempBoard[position - boardSize][position] = 1;
		}
		return;
	}
	if(position == (boardSize * boardSize) - 1){//Bottom Right Corner
		if(positionAvailable[row][column - 1] == player){
			tempBoard[position][position - 1] = 1;
			tempBoard[position - 1][position] = 1;
		}
		if(positionAvailable[row - 1][column] == player){
			tempBoard[position][position - boardSize] = 1;
			tempBoard[position - boardSize][position] = 1;
		}
		return;
	}
	if(row == 0){//Top Edge
		if(positionAvailable[row][column - 1] == player){
			tempBoard[position][position - 1] = 1;
			tempBoard[position - 1][position] = 1;
		}
		if(positionAvailable[row][column + 1] == player){
			tempBoard[position][position + 1] = 1;
			tempBoard[position + 1][position] = 1;
		}
		if(positionAvailable[row + 1][column] == player){
			tempBoard[position][position + boardSize] = 1;
			tempBoard[position + boardSize][position] = 1;
		}
		if(positionAvailable[row + 1][column - 1] == player){
			tempBoard[position][position + boardSize - 1] = 1;
			tempBoard[position + boardSize - 1][position] = 1;
		}
		return;
	}
	if(row == boardSize - 1){//Bottom Edge
		if(positionAvailable[row][column - 1] == player){
			tempBoard[position][position - 1] = 1;
			tempBoard[position - 1][position] = 1;
		}
		if(positionAvailable[row][column + 1] == player){
			tempBoard[position][position + 1] = 1;
			tempBoard[position + 1][position] = 1;
		}
		if(positionAvailable[row - 1][column] == player){
			tempBoard[position][position - boardSize] = 1;
			tempBoard[position - boardSize][position] = 1;
		}
		if(positionAvailable[row - 1][column + 1] == player){
			tempBoard[position][position - boardSize + 1] = 1;
			tempBoard[position - boardSize + 1][position] = 1;
		}
		return;
	}
	if(column == 0){//Left Edge
		if(positionAvailable[row - 1][column] == player){
			tempBoard[position][position - boardSize] = 1;
			tempBoard[position - boardSize][position] = 1;
		}
		if(positionAvailable[row + 1][column] == player){
			tempBoard[position][position + boardSize] = 1;
			tempBoard[position + boardSize][position] = 1;
		}
		if(positionAvailable[row - 1][column + 1] == player){
			tempBoard[position][position - boardSize + 1] = 1;
			tempBoard[position - boardSize + 1][position] = 1;
		}
		if(positionAvailable[row][column + 1] == player){
			tempBoard[position][position + 1] = 1;
			tempBoard[position + 1][position] = 1;
		}
		return;
	}
	if(column == boardSize){//Right Edge
		if(positionAvailable[row - 1][column] == player){
			tempBoard[position][position - boardSize] = 1;
			tempBoard[position - boardSize][position] = 1;
		}
		if(positionAvailable[row + 1][column] == player){
			tempBoard[position][position + boardSize] = 1;
			tempBoard[position + boardSize][position] = 1;
		}
		if(positionAvailable[row - 1][column - 1] == player){
			tempBoard[position][position - boardSize - 1] = 1;
			tempBoard[position - boardSize - 1][position] = 1;
		}
		if(positionAvailable[row][column - 1] == player){
			tempBoard[position][position - 1] = 1;
			tempBoard[position - 1][position] = 1;
		}
		return;
	}
	else{//Inner Node
		if(positionAvailable[row][column - 1] == player){
			tempBoard[position][position - 1] = 1;
			tempBoard[position - 1][position] = 1;
		}
		if(positionAvailable[row][column + 1] == player){
			tempBoard[position][position + 1] = 1;
			tempBoard[position + 1][position] = 1;
		}
		if(positionAvailable[row - 1][column + 1] == player){
			tempBoard[position][position - boardSize + 1] = 1;
			tempBoard[position - boardSize + 1][position] = 1;
		}
		if(positionAvailable[row - 1][column] == player){
			tempBoard[position][position - boardSize] = 1;
			tempBoard[position - boardSize][position] = 1;
		}
		if(positionAvailable[row + 1][column] == player){
			tempBoard[position][position + boardSize] = 1;
			tempBoard[position + boardSize][position] = 1;
		}
		if(positionAvailable[row + 1][column - 1] == player){
			tempBoard[position][position + boardSize - 1] = 1;
			tempBoard[(position + boardSize - 1)][position] = 1;
		}
		return;
	}
}

int HexGame::PlayGame(){
	bool gameover = false;
	while(!gameover){
		//Player1Turn
		//Check for winner
		//Player2Turn
		//Check for winner
	}
	return 0;
}

ostream& operator<<(ostream &out, HexGame &inputGame){
  out << endl;
  for( int rowCount = 0; rowCount < inputGame.boardSize; rowCount++ ){
    for( int colCount = 0; colCount < inputGame.boardSize; colCount++ ){
      if( inputGame.positionAvailable[rowCount][colCount] == 1){
	out << "XX" << setw(5);
	continue;
      }
      if( inputGame.positionAvailable[rowCount][colCount] == 2){
	out << "OO" << setw(5);
	continue;
      }
      else out << (rowCount * inputGame.boardSize) + colCount << setw(5);
    }
    out << endl;
    for( int spacePrint = 0; spacePrint <= rowCount; spacePrint++ ) out << setw(spacePrint + 3);
  }
  return out;
}

int HexGame::determineWinner(){
  if(player1Board){
    return 1;
  }
  else if(player2Board){
    return 2;
  }
  return 0;
}

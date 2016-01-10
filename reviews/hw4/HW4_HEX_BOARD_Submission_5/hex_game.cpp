//CMPS109 HW4: Implementation of Hex Game Board
//Copyright Jingya Liu, Di Ni

#include<iostream>
#include<ctime>
#include<stack>
#include"hex_game.h"

using namespace std;

//overload operator << to output hex board
//number in the heart of each hexagon is the player num who occupied it
ostream& operator<< (ostream &out, hex_board& board){
	//print out hexagons row by row
	for (int row = 0; row < STD_SIZE; ++row){
		if (row != 0)
			out << " \\";
		//print out "/ \"
		for (int col = 0; col < STD_SIZE; ++col)
			out << " / \\";
		out << endl;

		//spacing before "| x |" starts from the second row
		for (int col = 0; col < row; ++col)
			out << "  ";

		//print out "| x |" where x is the player number who occupied this hexagon
		for (int col = 0; col < STD_SIZE; ++col)
		if (col == 0)
			out << "| " << board.grids[row][col].getPlayer() << " |";
		else
			out << " " << board.grids[row][col].getPlayer() << " |";
		out << endl;

		//spacing before "\ /" starts from the second row
		for (int col = 0; col < row; ++col)
			out << "  ";

		//finish printing
		if (row == STD_SIZE - 1){
			for (int col = 0; col < STD_SIZE; ++col)
				out << " \\ /";
			out << endl;
		}
	}
	return out;
}

//set up hexagon nodes ids and their neighbours ids
void hex_board::initialize(){
	for (int row = 0; row < STD_SIZE; ++row){
		for (int col = 0; col <STD_SIZE; ++col){
			grids[row][col].setID(row, col);

			if (col == 0 && row == 0){
				//if it's the upper left corner hexagon
				grids[row][col].addNeighbors(row, col + 1);
				grids[row][col].addNeighbors(row + 1, col);
			}
			else if (col == STD_SIZE - 1 && row == STD_SIZE - 1){
				//if it's the bottom right corner hexagon
				grids[row][col].addNeighbors(row, col - 1);
				grids[row][col].addNeighbors(row - 1, col);
			}
			else if (col == STD_SIZE - 1 && row == 0){
				//if it's the upper right corner hexagon
				grids[row][col].addNeighbors(row, col - 1);
				grids[row][col].addNeighbors(row + 1, col);
				grids[row][col].addNeighbors(row + 1, col - 1);
			}
			else if (col == 0 && row == STD_SIZE - 1){
				//if it's the bottom left corner hexagon
				grids[row][col].addNeighbors(row, col + 1);
				grids[row][col].addNeighbors(row - 1, col + 1);
				grids[row][col].addNeighbors(row - 1, col);
			}
			else if (col == 0){
				//if it's a left side edge hexagon
				grids[row][col].addNeighbors(row, col + 1);
				grids[row][col].addNeighbors(row + 1, col);
				grids[row][col].addNeighbors(row - 1, col);
				grids[row][col].addNeighbors(row - 1, col + 1);
			}
			else if (col == STD_SIZE - 1){
				//if it's a right side edge hexagon
				grids[row][col].addNeighbors(row, col - 1);
				grids[row][col].addNeighbors(row + 1, col);
				grids[row][col].addNeighbors(row - 1, col);
				grids[row][col].addNeighbors(row + 1, col - 1);
			}
			else if (row == 0){
				//if it's upper side edge hexagon
				grids[row][col].addNeighbors(row, col - 1);
				grids[row][col].addNeighbors(row, col + 1);
				grids[row][col].addNeighbors(row + 1, col - 1);
				grids[row][col].addNeighbors(row + 1, col);
			}
			else if (row == STD_SIZE - 1){
				//if it's bottom side edge hexagon
				grids[row][col].addNeighbors(row, col - 1);
				grids[row][col].addNeighbors(row, col + 1);
				grids[row][col].addNeighbors(row - 1, col);
				grids[row][col].addNeighbors(row - 1, col + 1);
			}
			else{
				//if it's an interior hexagon
				grids[row][col].addNeighbors(row, col - 1);
				grids[row][col].addNeighbors(row, col + 1);
				grids[row][col].addNeighbors(row - 1, col);
				grids[row][col].addNeighbors(row - 1, col + 1);
				grids[row][col].addNeighbors(row + 1, col - 1);
				grids[row][col].addNeighbors(row + 1, col);
			}
		}
	}
}

//take a move at random position on hex board
void hex_board::randomStep(mt19937 generator, uniform_int_distribution<int> dis, int player_turn){
	bool isMarked = false;
	do{
		int row = dis(generator);
		int col = dis(generator);
		//if this hexagon has not been occupied, take it! otherwise choose another random position
		if (grids[row][col].getPlayer() == 0){
			grids[row][col].setPlayer(player_turn);
			isMarked = true;
		}
	} while (!isMarked);
}

//two players take turns to play random moves until the board is full
void hex_board::randomPlay(){
	mt19937 generator(static_cast<unsigned>(time(nullptr)));
	uniform_int_distribution<int> distribution(0, STD_SIZE - 1);

	//take turns between player 1 and 2
	for (int i = 0; i < STD_SIZE*STD_SIZE; ++i)
		randomStep(generator, distribution, i % 2 + 1);
}

//output the path from hexagon node "start" to "end"
void hex_board::printPath(int start, int end, vector<int>& previous)
{
	//hexagon node output format: (row_num, col_cum) 
   //where row, col both start from 0 to STD_SIZE - 1
	for (int next = end; next != start; next = previous[next])
		cout << "(" << deTransRow(next) << ", " << deTransCol(next) << ") <- ";
	cout << "(" << deTransRow(start) << ", " << deTransCol(start) << ")" << endl;
}

//perform depth first search from node "start" until the opposite side is reached
int hex_board::DFS(int start){
	vector<bool> visited(STD_SIZE * STD_SIZE, false);
	stack<int> s;
	vector<int> previous(STD_SIZE * STD_SIZE, -1);
	int winner = 0;
	int candidate = grids[deTransRow(start)][deTransCol(start)].getPlayer();
	int currnode;

	s.push(start);
	while (!s.empty()){
		currnode = s.top();
		s.pop();                             // Pop the top node off the stack
		visited[currnode] = true;            // Set current node as visited

		//if starting from the left edge, we need to reach the right edge to win
		if (deTransCol(start) == 0){
			if (deTransCol(currnode) == STD_SIZE - 1){
				winner = candidate;
				cout << "Winner connects left side with right side of the board!" << endl;
            cout << "Path starts from (" << deTransRow(start) << ", " << deTransCol(start) << ") "
               << " ends at node (" << deTransRow(currnode) << ", " << deTransCol(currnode) << ")" << endl;
            //if you want to see the actual connecting path uncomment the following line
				//printPath(start, currnode, previous);
				break;
			}
		}
		//if starting from the top row, we need to reach the bottom row to win
		else{
			if (deTransRow(currnode) == STD_SIZE - 1){
				winner = candidate;
				cout << "Winner connects upper side with bottom side of the board!" << endl;
            cout << "Path starts from (" << deTransRow(start) << ", " << deTransCol(start) << ") "
               << " ends at node (" << deTransRow(currnode) << ", " << deTransCol(currnode) << ")" << endl;
            //if you want to see the actual connecting path uncomment the following line
				//printPath(start, currnode, previous);
				break;
			}
		}

		vector<int> neighborList = grids[deTransRow(currnode)][deTransCol(currnode)].getNeighbors();

		//push neighbour nodes into stack if neighbour is occupied by the same player as start node
		for (int neighborID : neighborList){
			if (grids[deTransRow(neighborID)][deTransCol(neighborID)].getPlayer() == candidate
				&& !visited[neighborID]){
				s.push(neighborID);
				visited[neighborID] = true;
				previous[neighborID] = currnode;
			}
		}
	}

	return winner;
}

void hex_board::findWinner(){
	int i = 0;
	int candidate_win_col = 0;
	int candidate_win_row = 0;
	while (i++ < STD_SIZE){
		candidate_win_col = DFS(transform(i - 1, 0));

		if (candidate_win_col != 0){
			cout << "The winner is Player " << candidate_win_col << '\n' << endl;
			//we would like to find the winner as soon as possible.
         //But in this random play version, there might be more than one path
         //connecting two opposite sides of hex board and sometimes both players win.
			//If you want to explore all possible connecting paths and all possible winners
         //just comment out the following line
			break;
		}
		candidate_win_row = DFS(transform(0, i - 1)); 
		if (candidate_win_row != 0){
			cout << "The winner is Player " << candidate_win_row << '\n' << endl;
			//comment out the following line to explore all possible connecting paths and winners
			break;
		}
	}
}

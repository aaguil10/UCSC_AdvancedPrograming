#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#define P1 'R'		//red
#define P2 'B'		//blue
#define EMPTY '-'	//empty

class HexBoard {
private:
	vector<vector<int> > board;	//board
	int size;
public:
	HexBoard() { HexBoard(5); }		//default board of size 5
	HexBoard(int s);				//board of size s
	int inline getSize() { return size; }	//getter
	bool inline isEmpty(int x, int y) { return board[y][x] ? false : true; }	//check to see if the loacation on board is empty
	bool set(int x, int y, int color);		//set the color if valid
	bool isFinished(int color);				//checks for winner
	bool check(int x, int y, int color, vector<vector<bool> > visited, bool root);		//check algorithm
	friend ostream& operator<<(ostream &cout, HexBoard board);	//overloaded <<
};

HexBoard::HexBoard(int s) {				//board of size s
	size = s;
	board = vector<vector<int> >(s, vector<int>(s, 0));
}

ostream& operator<<(ostream &cout, HexBoard hb) {			//overloading operator
	int space;

	cout << endl<< "   ";
	for (int i = 0; i < hb.size; i++)
		cout << setw(2) << left << i;		//formatting
	cout << endl;

	for (int y = 0; y < hb.size; y++) {
		cout << setw(2) << right << y;
		for (int x = 0; x < hb.size; x++) {
			space = hb.board[y][x];
			cout << " ";
			if (space == 0)
				cout << EMPTY;
			else if (space > 0)
				cout << P1;
			else
				cout << P2;
		}
		cout << " " << setw(2) << left << y << endl;
	}

	cout << "   ";
	for (int i = 0; i < hb.size; i++)
		cout << setw(2) << left << i;
	cout << endl << endl;
	return cout;
}

bool HexBoard::check(int x, int y, int color, vector<vector<bool> > visited, bool root) {		//checking algorithm
	if (0 <= x && x < size && 0 <= y && y < size && !visited[y][x]) {
		visited[y][x] = true;

		if (board[y][x] == color) {			//Red shoulg go from left to right, Blue should go from top to bottom
			if ((color > 0 && x == size-1) || (color < 0 && y == size-1))
				return true;
			if (color > 0) {		//for red
				if (check(x+1, y, color, visited, false) ||	// right
					check(x, y-1, color, visited, false) ||	// up
					check(x, y+1, color, visited, false) ||	// down
					check(x+1, y-1, color, visited, false) ||	// top right
					check(x+1, y+1, color, visited, false))	// bot right
					return true;
			}
			else if (color < 0) {	//for blue
				if (check(x, y+1, color, visited, false) ||	// down
					check(x-1, y, color, visited, false) ||	// left
					check(x+1, y, color, visited, false) ||	// right
					check(x-1, y+1, color, visited, false) ||	// bot left
					check(x+1, y+1, color, visited, false))	// bot right
					return true;
			}
		}
		else if (color > 0 && x == 0) {		//beginning col
			if (check(x, y+1, color, visited, false))	// down
				return true;	
		}
		else if (color < 0 && y == 0) {		//beginning row
			if (check(x+1, y, color, visited, false))	// right
				return true;
		}
	}
	
	return false;
}

bool HexBoard::isFinished(int color) {		//check for the winner
	vector<vector<bool> > visited = vector<vector<bool> >(size, vector<bool>(size, false));		//creates the visited list
	return check(0, 0, color, visited, true);
	
}

bool HexBoard::set(int x, int y, int color) {		//set the point if valid
	if (x >= size || y >= size)
		return false;
	if (isEmpty(x, y))
		board[y][x] = color;
	else
		return false;
	return true;
}

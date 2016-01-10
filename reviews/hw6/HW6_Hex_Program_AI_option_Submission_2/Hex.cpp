//Gary Lee
//gflee@ucsc.edu
//CMPS 109
//hw6
//
//Hex.cpp

#include <iostream> // cout
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <pthread.h>

using namespace std;

double probability(){ return 1.0*rand()/RAND_MAX;}
typedef int* int_ptr;
typedef int_ptr* int_matrix;
typedef char* char_ptr;
typedef char_ptr* char_matrix;

// Threads can't accept more than one argument, so structs are necessary for passing multiple arguments
struct arg_struct{
	int i;
	int j;
	int_matrix disc;
	int_matrix matrix;
};

class Board{
	int size;
	int finished;
	char_matrix hex_board;
	// Two-dimensional array that holds info on whether space is occupied
	// 0 = unoccupied, 1 = occupied
	int_matrix occupied;
	int_matrix temp;
	int_matrix wins;
	int_matrix discovered;
	int count;
public:
	Board(){
		size = 0;
	}//constructor
	int winner;
	void play_game(int s);
	void find_winner(int_matrix disc, int_matrix matrix);
	int dfs_search1(int i, int j, int_matrix disc, int_matrix matrix);
	int dfs_search2(int i, int j, int_matrix disc, int_matrix matrix);
	void print_board();
}; //class

void Board::play_game(int s){
	winner = 0;
	size = s;
	hex_board = new char_ptr[s]; //creates new array of size "s"
	occupied = new int_ptr[s];
	temp = new int_ptr[s];
	wins = new int_ptr[s];
	discovered = new int_ptr[s];
	for(int i = 0; i < s; ++i){
		hex_board[i] = new char[s]; //creates new char array of size "s" and places it in indicated slot of "hex_board"
		occupied[i] = new int[s];
		temp[i] = new int[s];
		wins[i] = new int[s];
		discovered[i] = new int[s];
	}
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			hex_board[i][j] = '-';
			occupied[i][j] = 0;
			temp[i][j] = 0;
			wins[i][j] = 0;
			discovered[i][j] = 0;
		}
	}
	int a = 0;
	int b = 0;
	int c = 0;
	int x = 0;
	int y = 0;
	count = 0;
	winner = 1;
	while(count < 121){
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				wins[i][j] = 0;
			}
		}
		// Player moves
		cout << "Enter in the row you want to play on:" << endl;
		cin >> a;
		cout << "Enter in the column you want to play on:" << endl;
		cin >> b;
		cout << "Player move:" << endl;
		cout << "row = " << a << endl;
		cout << "column = " << b << endl;
		if(occupied[a-1][b-1] != 0 || a > size || b > size){
			cout << "Invalid move. Try again."<< endl;
			continue;
		}
		hex_board[a-1][b-1] = 'A';
		occupied[a-1][b-1] = 1;
		// AI moves
		// The program scans each slot of the 2d array to see if it is occupied
		// If the slot is unoccupied, a temporary 2d array is created
		// The playing board is copied to the temporary array
		// The program simulates a move by the AI
		// After a move has been simulated, 1000 separate games are run
		// The program does this for every available slot of the playing board
		// After each slot has had a simulation run on it, the slot with the highest amount of wins is chosen by the AI
		// scope 1 start
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				if(occupied[i][j] == 0){
					// The playing board is copied to the temporary board
					// scope 2 start
					for(int i2 = 0; i2 < size; i2++){
						for(int j2 = 0; j2 < size; j2++){
							temp[i2][j2] = occupied [i2][j2];
						}
					}
					// scope 2 end
					temp[i][j] = 2;
					int z = 0;
					int w = 0;
					// The program runs a simulation of 1000 games with the potential move placed on the temporary board
					while(z < 1000){
						// scope 3 start
						for(int g = 0; g < size; g++){
							for(int h = 0; h < size; h++){
								discovered[g][h] = 0;
							}
						}
						for(int i3 = 0; i3 < s; ++i3){
							for(int j3 = 0; j3 < s; ++j3){
								if(temp[i3][j3] == 0){
									if(probability() > 0.5){
										temp[i3][j3] = 1;
									}else{
										temp[i3][j3] = 2;
									}
								}
							}
						}
						// A winner is chosen for each of the 1000 games and is recorded
						// scope 3 end
						find_winner(discovered, temp);
						if(winner == 2){
							w++;
						}
						wins[i][j] = w;
						winner = 0;
						z++;
					}
				}
			}
		}
		// The program traverse the winning data and selects the slot with the highest amount of wins to play
		// scope 1 end
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				if(wins[x][y] < wins[i][j]){
					x = i;
					y = j;
				}
			}
		}
		// The AI makes its move
		cout << "AI move:" << endl;
		cout << "row = " << x+1 << endl;
		cout << "column = " << y+1 << endl;
		hex_board[x][y] = 'B';
		occupied[x][y] = 2;
		print_board();
		count+=2;
		cout << "Moves left: " << 121 - count << endl;
		for(int g = 0; g < size; g++){
			for(int h = 0; h < size; h++){
				discovered[g][h] = 0;
			}
		}
		// The program scans for a winner after every move by the player and the AI
		// Depth-first-search is used to traverse the playing board
		find_winner(discovered, occupied);
		if(winner == 1){
			cout << "You are the winner!" << endl;
			cout << "Game Over" << endl;
			return;
		}
		if(winner == 2){
			cout << "You are the loser!" << endl;
			cout << "Game Over" << endl;
			return;
		}
	}
}

// This function executes the depth-first-search functions to find a winner
void Board::find_winner(int_matrix disc, int_matrix matrix){
	int a = 0;
	int b = 0;
	for(int i = 0; i < size; ++i){
		for(int g = 0; g < size; g++){
			for(int h = 0; h < size; h++){
				discovered[g][h] = 0;
			}
		}
		struct arg_struct args1;
		args1.i = i;
		args1.j = 0;
		args1.disc = disc;
		args1.matrix = matrix;
		a = dfs_search1(i, 0, disc, matrix);
		struct arg_struct args2;
		args2.i = 0;
		args2.j = i;
		args2.disc = disc;
		args2.matrix = matrix;
		b = dfs_search2(0, i, discovered, matrix);
		if(a != 0){
			winner = 2;
			break;
		}
		if(b != 0){
			winner = 1;
			break;
		}
	}
}

// Implementation of depth first search for AI
// This function searches for a path from the left side of the board to the right side of the board containing only moves made by the AI
int Board::dfs_search1(int i, int j, int_matrix disc, int_matrix matrix){
	//i = row, j = column
	//0 = true, 1 = false
	int a = 0;
	int b = 0;
	int c = 0;
	if(i >= size || j >= size){
		return 0;
	}
	if(disc[i][j] == 1 || matrix[i][j] != 2){
		return 0;
	}
	disc[i][j] = 1;
	if(j == (size-1)){
		return 1;
	}
	// Recursion
	if(i == 0){
		a = dfs_search1(i, (j+1), disc, matrix);
		b = dfs_search1((i+1), j, disc, matrix);
	}else if( i == (size-1)){
		a = dfs_search1((i-1), (j+1), disc, matrix);
		b = dfs_search1(i, (j+1), disc, matrix);
	}else{
		a = dfs_search1((i-1), (j+1), disc, matrix);
		b = dfs_search1(i, (j+1), disc, matrix);
		c = dfs_search1((i+1), j, disc, matrix);
	}
	if(a != 0){
		return a;
	}else if(b != 0){
		return b;
	}else if(c != 0){
		return c;
	}else{
		return 0;
	}
}

// Implementation of depth first search for the player
// This function searches for a path that goes from the top of the board to the bottom of the board containing only moves made by the player
int Board::dfs_search2(int i, int j, int_matrix disc, int_matrix matrix){
	//i = row, j = column
	//0 = true, 1 = false
	int a = 0;
	int b = 0;
	int c = 0;
	if(i >= size || j >= size){
		return 0;
	}
	if(disc[i][j] == 1 || matrix[i][j] != 1){
		return 0;
	}
	disc[i][j] = 1;
	if(i == (size-1)){
		return 1;
	}
	// Recursion
	if(j == 0){
		a = dfs_search2(i+1, j, disc, matrix);
		b = dfs_search2(i, j+1, disc, matrix);
	}else if( j == (size-1)){
		a = dfs_search2((i+1), (j-1), disc, matrix);
		b = dfs_search2(i+1, j, disc, matrix);
	}else{
		a = dfs_search2((i+1), (j-1), disc, matrix);
		b = dfs_search2(i+1, j, disc, matrix);
		c = dfs_search2(i, j+1, disc, matrix);
	}
	if(a != 0){
		return a;
	}else if(b != 0){
		return b;
	}else if(c != 0){
		return c;
	}else{
		return 0;
	}
}

//Prints game board
void Board::print_board(){
	cout << "Board Size: " << size << endl;
	cout << "  ";
	for(int i = 0; i < size; ++i){
		cout << "[" << i+1 << "]";
	}
	cout << endl;
	int spaces = 0;
	int x = 0;
	for(int i = 0; i < size; ++i){
		x = spaces;
		while(x > 0){	//spaces hex board out
			cout << " ";
			x--;
		}
		cout << "[" << i+1 << "] ";
		for (int j = 0; j < size; ++j){
			cout << " " << hex_board[i][j] << " ";
		}
		cout << "[" << i+1 <<"]" << endl;
		spaces++;
	}
	for(int j = size; j > 1; j--){
		cout << " ";
	}
	cout << "     ";
	for(int i = 0; i < size; ++i){
		cout << "[" << i+1 << "]";
	}
	cout << endl;
}

void *pmf(void *ptr){
	int a = 0;
	int b = 0;
	int size = 11;
	int_matrix d = new int_ptr[size];
	int_matrix m = new int_ptr[size];
	for(int i = 0; i < size; ++i){
		d[i] = new int[size];
		m[i] = new int[size];
	}
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			d[i][j] = 0;
			m[i][j] = 0;
		}
	}
	for(int i = 0; i < size; ++i){
		for(int g = 0; g < size; g++){
			for(int h = 0; h < size; h++){
				d[g][h] = 0;
			}
		}
		struct arg_struct args1;
		args1.i = i;
		args1.j = 0;
		args1.disc = d;
		args1.matrix = m;
		struct arg_struct args2;
		args2.i = 0;
		args2.j = i;
		args2.disc = d;
		args2.matrix = m;
	}
}

int main(){
	cout << "Player 1 (you) is represented as 'A' and goes top to bottom." << endl;
	cout << "Player 2 (AI) is represented by 'B' and goes left to right." << endl;
	Board board;
	// Two threads are created
	pthread_t thread1, thread2;
	int rt1, rt2;
	const char *x = "i";
	const char *y = "j";
	// The two threads are executed at the same time
	rt1 = pthread_create( &thread1, NULL, pmf, (void*) x);
	rt2 = pthread_create( &thread2, NULL, pmf, (void*) y);
	// This is to make sure that one thread does not finish and exit the program before the other is also finished
	pthread_join( thread1, NULL);
	pthread_join( thread2, NULL);
	srand(time(0));
	board.play_game(11);
	return 0;
}

//CMPS109 HW4: Implementation of Hex Game Board
//Copyright Jingya Liu, Di Ni

#ifndef HEX_GAME_H
#define HEX_GAME_H

#include<array>
#include<random>
#include<vector>

const int STD_SIZE = 11;                                              //standard hex game board size
inline int transform(int row, int col){ return row * STD_SIZE + col; }//convert row, col into id num
inline int deTransRow(int id){ return id / STD_SIZE; }                //convert id num into row num
inline int deTransCol(int id){ return id % STD_SIZE; }                //convert id num into col num
using namespace std;

//hexagon class definition
class hexagon
{
public:
   //default constructor
	hexagon() :id(0){}                          
	void setID(int row, int col){ id = transform(row, col); }
	int getID() const { return id; }
	void addNeighbors(int row, int col){ neighbors.push_back(transform(row, col)); }
	vector<int>& getNeighbors(){ return neighbors; }
	void setPlayer(int p){ player = p; }
	int getPlayer() const { return player; }
private:
   //array of hexagon node ids to which this hexagon could connect
	vector<int> neighbors;
   //player num who occupied this hexagon;default to be 0, not occupied
	int player = 0;                                                  
	int id;
};

//hex board class definition
class hex_board
{
public:
   //overload operator << to output hex board
   friend ostream& operator<<(ostream &out, hex_board& board);
   //default constructor
	hex_board(){ initialize(); }
   //two players take turns to play random moves until the board is full
	void randomPlay();
	void findWinner();
	array <array<hexagon, STD_SIZE>, STD_SIZE>& getGrids(){ return grids; }

private:
	array <array<hexagon, STD_SIZE>, STD_SIZE> grids;
   //set up hexagon nodes ids and their neighbours
	void initialize();
   //take a move at random position on hex board
	void randomStep(mt19937 generator, uniform_int_distribution<int> dis, int player_turn);
   //perform depth first search from node "start" until the opposite side is reached
	int DFS(int start);
   //output the path from hexagon node "start" to "end"
	void printPath(int start, int end, vector<int>& previous);
};

#endif

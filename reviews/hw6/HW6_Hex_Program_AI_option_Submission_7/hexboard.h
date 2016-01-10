#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <chrono> 
#include <algorithm>
#include <set>
#include <utility>

using namespace std;

typedef int vertex_n;


//the 2 colors used for the game 
enum colors_t {black, white, empty};

//the struct for each of the hex squares
struct node 
{
   vertex_n x;
   vertex_n y;
   colors_t color = empty;
   //pointers to the neighbor hexs
   vector<node*> surroundNode;
   bool visited = false;
};

class graph
{
public:
	graph(int s);
	void neighborNodes (node *temp, int i, int j);
	int playAIgame(colors_t AIcolor, int xCoor, int yCoor);
	pair<int, int> newMovement(colors_t AIcolor, bool swapOK);
	colors_t searchForWinner(bool AI);
	bool playerMovement(colors_t Pcolor, int x, int y, bool swapOK);
	void clearG1();

private:
   int size;
   //the hex board
   vector<vector<node>> g1;
   vector<vector<node>> g1copy;
   vector<colors_t> boardColor;
   vector<pair<int,int>> position;
};

#endif
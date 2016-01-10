#pragma once

#include <iostream>
#include <cstdint>
#include <ctime>
#include <climits>
#include <cmath>
#include <vector>

using namespace std;


inline double probability()
{
	return 1.0*rand() / RAND_MAX;
}

class Graph
{

private:
	int _size;
	int** _g1;
	const int MAX = INT_MAX;

	vector<int> closed1, // nodes explored
		open1, // verts needed to explore
		dist1, // distance from source to index
		parent1; // closest node from index

	vector<int> closed2, // nodes explored
		open2, // verts needed to explore
		dist2, // distance from source to index
		parent2; // closest node from index

	int dijkstraStep(vector<int>*, vector<int>*, vector<int>*, vector<int>*);
	int getLowestCostIndex(vector<int>*, vector<int>*, vector<int>*);
	bool visited(int, vector<int>&);

public:
	Graph(int size = 1, double density = 0.5, bool debug = false);
	Graph(const Graph&);
	~Graph();

	friend ostream& operator<<(ostream&, const Graph&);

	// returns the shortest path as a stack
	vector<int> dijkstra(int source, int target);
	vector<int> biDirectionalSearch(int source, int target);
	void print();
};


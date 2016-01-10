#pragma once

#include <iostream>
#include <ctime>

using namespace std;

class Graph
{

private:
	int _size;
	bool** _g1;

	inline double probability();

public:
	Graph(int size = 1, double density = 0.5);
	Graph(const Graph&);
	~Graph();

	friend ostream& operator<<(ostream&, const Graph&);

	void print();
};


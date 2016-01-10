//============================================================================
// Name        : asg2.cpp
// Copyright   : Nguyen Do
// Description : C++ version of graph generation
// Converted from C includes:
// matrix representation
// calloc replace by vector and resize
// printf goes to use of "<<"
// struct becomes class
// advanced make_  becomes a constructor
// use <random> instead of rand() and srand()
//============================================================================

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iomanip> //to format width for cout
#include <random>  //to generate random
using namespace std;

//Mersenne Twister 19937 generator, run once
static mt19937 rng;

//inline probability function
inline double probability(){ return 1.0*rng()/RAND_MAX;}

class Graph{
private:
	vector< vector<bool> > bool_matrix;
	int size;
public:
	//constructor, to replace make_graph
	Graph (int s, double density){
		this->size =s;
		//initialize columns
		this->bool_matrix.resize(this->size);
		//initialize rows
		for (int i = 0; i < this->size; i++)
			bool_matrix[i].resize(this->size);
		//add true values to graph
		for(int i=0; i<this->size; ++i)
			for(int j=0; j<this->size; ++j)
			{
				if(probability()< density)
					this->bool_matrix[i][j] = true;
			}
	}

	//overload operator<< instead of print_graph() method
	friend ostream& operator<<(ostream& os, const Graph& g)
	{
		os << "graph size "<< g.size << "\n";
		for(int i = 0; i < g.size; ++i)
		{
			os <<"\n";
			for (int j = 0; j < g.size; ++j)
				os << setw(5) << g.bool_matrix[i][j];
		}
		return os;
	}
};

int main()
{
	Graph test1(10,0.7), test2(8,0.5);
	cout<< "Test simple graph generation\n";
	cout<<test1;
	cout<<"\nEND of TEST 1\n\n";
	cout<<test2;
	cout<<"\nEND of TEST 2\n\n";
	return 0;
}

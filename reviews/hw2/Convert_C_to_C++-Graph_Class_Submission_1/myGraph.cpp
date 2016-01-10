//
// Logan McGhee - LMcGhee@ucsc.edu
// CS 109 @ UCSC, Winter 2014
// Graph generation using rand and variables and things.
//

#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;	// I am using namespace std for this program, as stated here.

inline double probability(){ return 1.0*rand() / RAND_MAX; }	//returns a value

class graph{	//replaces the C typedef, yay classes!
public:
	graph(int s, double density){	//Start constructor
		this->size = s;		//assignments from parameters
		vector<bool> newVec(size,0);	//creates an empty vector of size 'size' with all values 0
		for (int i = 0; i < s; i++){
            this->g1.push_back(newVec);	//pushes a row of empty vectors into the matrix g1 for s 
		}
		for (auto& element:this->g1)
            for(auto element2: element)
                if(probability()<density) element2 = true; //calls probability and assigns values to the matrix accordingly
	};	 //end constructor
	void print_graph();		//publicly accessible print function
private:
	int size;
	vector<vector<bool>> g1;	//our matrix for the graph generation
};

void graph::print_graph(){	//Prints the matrix/graph
	cout << "Graph size = " << size << endl;
	for (auto& elem : g1){	//For each element in the matrix, we print out the corresponding 
		cout << endl;
		for (auto elem2: elem){
			cout << elem2 <<"\t";  
		}
	}
}

int main(){
	srand(time(0));		//set random using time variable
	cout << "Test simple graph generation" << endl;
	graph test1(10, 0.7);	//initialize the first test graph
	test1.print_graph();	//print the first test graph
	cout << endl << "END of TEST 1" << endl << endl;
	graph test2(8, 0.5);	//initialize the second test graph
	test2.print_graph();	//print the second test graph
	cout << endl << "END of TEST 2" << endl << endl;


	return 0;
}

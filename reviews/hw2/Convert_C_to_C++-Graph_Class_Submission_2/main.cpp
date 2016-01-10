// Author: Leif Myer
// Last Editted: 1.14.14
// HW2 - Convert a C Graph

#include <iostream>
#include <ctime>

#include "Graph.h"

using namespace std;


int main()
{
	Graph* graph1;
	srand(time(NULL));
	cout << "Test simple graph generation" << endl;
	graph1 = new Graph(10, 0.7);
	graph1->print();
	cout << endl << "END of TEST 1" << endl << endl;
	Graph* graph2 = new Graph(8, 0.5);
	cout << *graph2;
	cout << endl << "END of TEST 2" << endl << endl;
	//system("pause");
	return 0;
}
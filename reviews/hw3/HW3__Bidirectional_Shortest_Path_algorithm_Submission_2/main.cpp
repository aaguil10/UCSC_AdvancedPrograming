// Author: Leif Myer
// Last Editted: 2.5.14
// HW3 - Dijkstra Implementation

#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>

#include "Graph.h"

using namespace std;


int main()
{
	Graph g1(1000, 0.1);

	int source;
	int target;

	clock_t startTime;
	clock_t endTime;

	srand(time(NULL));

	for (int i = 0; i < 500; i++)
	{
		source = round(probability() * 999);
		target = round(probability() * 999);
		
		// dijkstra
		startTime = clock(); // begin timer
		vector<int> dpath = g1.dijkstra(source, target);
		endTime = clock() - startTime; // end timer
		double diff = endTime % CLOCKS_PER_SEC;
		cout << "Dijkstra time: " << fixed << setprecision(0) << diff << "ms -- ";

		// biDirectional
		startTime = clock(); // begin timer
		vector<int> bpath = g1.biDirectionalSearch(source, target);
		endTime = clock() - startTime; // end timer
		diff = endTime % CLOCKS_PER_SEC;
		cout << "Bi-Directional time: " << fixed << setprecision(3.0) << diff << "ms" << endl;
		cout << "-------------------" << endl;
	}

	return 0;
}
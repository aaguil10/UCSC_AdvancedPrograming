//Kevin Neal
//2/6/2014
//Homework 3

//Pohl  Implement Dijkstra's and Bidirectional search

//matrix representation
//calloc goes to new or use vector
//printf goes to use of "<<"
//struct becomes class
//advanced make_  becomes a constructor

#include <cstdlib>
#include <random>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

using namespace std;

double probability(){ return 1.0*rand() / RAND_MAX; }

//Edge class
/*class edge{

public:
	double weight;
	int to;
	int from;
	edge(int v1, int v2, int w);
};*/

//Instead of struct, changed graph to a class
class graph{
	
public:
	graph(int s, double density);
	void print_graph();
	void printWeight();
	bool is_connected();
	void dijkstras();

private:
	int size;
	double dens;
	vector<vector<bool> > g1;
	vector<int>weightArray;
};

//Constructor for Edges
/*edge::edge(int v1, int v2, int w){
	to = v1;
	from = v2;
	weight = w;
}*/

//Constructor for Graph
graph::graph(int s, double density){
	int range = 200 - 1 + 1;
	int num;

	size = s;
	dens = density;

	vector<vector<bool> > graph_bool(s, vector<bool>(s));
	g1 = graph_bool;

	vector<int>tempArr(s);
	weightArray = tempArr;

	for (int i = 0; i < s; ++i){
		for (int j = 0; j < s; ++j){
			if (probability() < density){
				g1[i][j] = true;
				num = rand() % range + 1;
				weightArray[i] = num;
			}
		}
	}
}

//Dijkstra's Search Algorithm
void graph::dijkstras(){
	int curr, min = 0;
	vector<int>visited(size);
	vector<int>shortest_path(size);
	vector<int>nodeWeight(size);

	int infin = -1;
	int VISITED = 1;
	int UNVISITED = 2;

	//randomly generates start and end vertices
	int startVert = rand() % size;
	int endVert = rand() % size;

	while (startVert == endVert || (startVert || endVert == 0)){
		startVert = rand() % size;
		endVert = rand() % size;
	}

	//initializes distances to infinity and sets all nodes to unvisited
		for (int i = 0; i < size; i++){
			shortest_path[i] = infin;
			visited[i] = UNVISITED;
		}

		//set Current to start Vertex and set weight of Current to 0
		curr = startVert;
		shortest_path[curr] = 0;		

		/*for (int i = 0; i < size; i++){
			min = -1;

			for (int j = 0; j < size; j++){

				if (visited[j] == UNVISITED && ((min == -1) || (shortest_path[i] < visited[min]))){
					min = i;
				}

				visited[min] = VISITED;

				for (int i = 0; i < size; i++){
					if (g1[min][i]){
						if (shortest_path[min] + g1[min][i] < shortest_path[min]){
							shortest_path[i] = shortest_path[min] + g1[min][i];
						}
					}
				}
			}
			
		}*/
}


//Prints out the graph
void graph::print_graph(){
	cout << "Graph size: " << size << endl;

	for (int i = 0; i < size; ++i){
			cout << endl;
		for (int j = 0; j < size; ++j)
			cout << g1[i][j] << "\t";
	}
	cout << endl;
}

//Print for Edges
void graph::printWeight(){

	for (int i = 0; i < weightArray.size(); i++){
		cout << "Vertex : " << i << " Weight : " << weightArray[i] << endl;
	}
	/*for (int i = 0; i < edgeArray.size(); i++){
		cout << "Vertex: " << i << ", to: " << edgeArray[i].to << 
			" , from: " << edgeArray[i].from << ", weight: " << edgeArray[i].weight << endl;
	}*/
}

//Creates test graphs and prints them
int main(){
	srand(time(0));
	graph test1(30, 0.1);
	graph test2(8, 0.5);

	cout << "Test simple graph generation" << endl;
	
	test1.print_graph();
	test1.printWeight();
	test1.dijkstras();
	cout << endl << "End of TEST 1" << endl << endl;
	
	test2.print_graph();
	test2.printWeight();
	test2.dijkstras();
	cout << endl << "End of TEST 2" << endl << endl;
	return 0;
}

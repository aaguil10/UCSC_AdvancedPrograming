/* 
 * File:   Dijkstra.cpp
 * Author: Jacky Chiu jchiu6@ucsc.edu
 *
 * Created on Febuary 1, 2014, 8:20 PM
 */


 
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
 
inline double probability(){ return 1.0*rand()/RAND_MAX;}

class graph{
    
    class edge {
    public:
        int weight;
    };

private:
    vector < vector <bool> > bool_matrix; //create a vector bool_matrix
    vector < vector <edge> > edgeL;
    int size; //graph size

public: 
    graph(int s, double density) : size(s) {
        bool_matrix.resize(s,vector<bool>(s,false)); //initialize bool_matrix
        for(int i = 0; i < s; ++i) //iterate through 2D vector
                for(int j = 0; j < s; ++j)
                    if(probability()< density) bool_matrix[i][j] = true;
                int x = 0;
                int y = 0;
                edgeL.resize (s + 1);
                for (x = 0; x < s; x++) {
                    edgeL[x].resize(s + 1);
                    for (y = 0; y < s; y++) {
                        edgeL[x][y].weight = 0;
                    }
                }
            
//initialize weight edge
                for (x = 0; x < s; x++) {
                    for (y = 0; y < s; y++) {
                        if ((probability() * 100) < density) {
                            edgeL[x][y].weight = probability() * 99;
                            edgeL[x][y].weight = edgeL[x][y].weight;
                        }
                        else {
                            edgeL[x][y].weight = -1;
                            edgeL[x][y].weight = -1;
                        }
                    }
                }
   //nodes without any representation
   for (int i=0; i<s; i++) edgeL[i][i].weight = 0;   
}
    
    void print_graph() const {
        cout << "graph size " << size << endl; //print graph size
        for(int i = 0; i < size; ++i) //printing the graph objects
        {
            cout << endl;
            for (int j = 0; j < size; ++j)
                cout << " \t " << bool_matrix[i][j];
        }
    }
    
    void print_graph2() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << setw(4) << edgeL[i][j].weight << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
};
 
 
int main()
{
    srand(time(NULL)); //generate random numbers
    //graph test1(10, 0.7), test2(8, 0.5); 
   //cout << "Test simple graph generation\n" << endl;
   //test1.print_graph(); //print out test1
   //cout << "\nEND of TEST 1\n\n" << endl;
   //test2.print_graph(); //print out test2
   //cout << "\nEND of TEST 2\n\n" << endl
    print_graph2();
   return 0;
}

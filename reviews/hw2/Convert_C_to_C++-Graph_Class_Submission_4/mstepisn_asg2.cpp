// Martina Stepisnik
// 27 January 2014
// Assignment 2


// Convert C program for
// generating matrix representation of a graph
// into C++ language


#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <vector>

using namespace std;
inline double probability(){return 1.0*rand()/RAND_MAX;} // used for setting T/F 

class Graph{

public: // can be accessed outside of the class
    
    Graph(int sz, double density){ // constructor takes in a size and density variable
        size = sz; // set the size of the graph to what was passed in
        
        bool_matrix.resize(size); // create space for rows
        for (int cols = 0; cols < size; cols++){
            bool_matrix[cols].resize(size); // create space for columns
        }
        
        // fill in the matrix
        for(int row = 0; row < size; row++){
            for(int col = 0; col < size; col++){
                if(probability() < density){
                    bool_matrix[row][col] = true;
                }
            }
        }
    }
    
    void printGraph(){
        cout << "Graph Size = " << size << endl; // print size of graph
        for(int row = 0; row < size; row++){
            cout << endl; // new line at end of each row
            for(int col = 0; col < size; col++){
                cout << bool_matrix[row][col]  << "\t" ; // print out each value and seperate with a tab
            }
        }
        cout << endl;
    }
    
    // access size of graph outside the class
    // used for debugging
    int getSize(){ 
        return size;
    }
    
private:
    
    int size; // size of graph
    vector<vector<bool>> bool_matrix; // 2D array of booleans 
    
};

int main(){
    srand(time(0)); // make rand() "more random" 
    
    cout << "Test Simple Graph Generation" << endl;
    cout << endl;
    Graph test1(10,0.7); // size = 10, density = .7
    test1.printGraph();
    cout << "END OF TEST ONE" << endl;
    cout << endl;
    Graph test2(8, 0.5); // size = 8, density = .5
    test2.printGraph();
    cout << "End OF TEST TWO" << endl;
    
    return 0; // end 
}


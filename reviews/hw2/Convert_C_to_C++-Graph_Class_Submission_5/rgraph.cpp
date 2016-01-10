// Kevin Doyle (kdoyle)
// January 27th, 2014
// CMPS 109A
// Assignment 2
// Converting a C graph generator
// into a C++ graph generator

// This program prints out two pseudo-randomly
// generated matrices of ones and zeros.

#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <new>

using namespace std;
inline double probability(){ return 1.0*rand()/RAND_MAX;}

class graph{
   private:
      int size;
      int** matrix;
   
   public:
      void makeGraph(int s, double density);
      void printGraph(void);
   
};

// Allocates and assembles a new graph
void graph::makeGraph(int s, double density){
   int i, j;
   this->size = s;
   
   // Allocation
   this->matrix = new int*[s];
   for(i = 0; i < s; ++i){
      this->matrix[i] = new int[s];
   }
      
   // Assignment
   for(i = 0; i < s; ++i){
      for(j = 0; j < s; ++j){
         if(probability() < density){
            this->matrix[i][j] = true;
         }
      }
   }
}
   
// Prints out a graph
void graph::printGraph(void){
   int i, j;
   cout << "graph size " << this->size << "\n";
   for(i = 0; i < this->size; ++i){
      cout << "\n";
      for(j = 0; j < this->size; ++j){
         cout << " " << this->matrix[i][j] << "\t";
      }
   }
}
    
int main(void){
   graph test1, test2;
   srand(time(0));
   cout << "Test simple graph generation\n";
   test1.makeGraph(10, 0.7);
   test1.printGraph();
   cout << "\nEND of TEST 1\n\n";
   test2.makeGraph(8, 0.5);
   test2.printGraph();
   cout << "\nEND of TEST 2\n" << endl;
   return 0;
}
   
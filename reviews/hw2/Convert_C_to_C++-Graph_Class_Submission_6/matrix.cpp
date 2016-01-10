//Aiden Hoopes, ahoopes, hw2, CMPS109
#include <iostream>
#include <ctime>
#include <vector>//Using fancy, modern vectors
using namespace std;
 
inline double probability(){ return (double)rand()/RAND_MAX;}//INLINE = FAST

class graph{//Classes in C++ instead of structs
   public:// Everything is public for ease of access
      int size;
      double density;
      vector<vector<bool>> g1;//2D vector array which holds the values
      graph( int a, double b );// This is the constructor
};

graph::graph( int a, double b ){//Constructor function sets size and density
   size = a;
   density = b;
   g1.resize(size);//This sets the size of the vector rows
   for(int i = 0; i < size; ++i){//This loop resizes vector columns properly
      g1[i].resize(size);
   }
   for(int i = 0; i < size; ++i){//This loop sets all the values
      for(int j = 0; j < size; ++j){
         if( probability() < density) g1[i][j] = true;
      }
   }
} 
 
void print_graph( graph* g){//Prints out entire 2D array with tabs inbetween
   cout << "graph size " << g->size << endl;
   for(int i = 0; i < g->g1.size(); ++i){
      cout << endl;
      for(int j = 0; j < g->g1[i].size(); ++j){
         cout << " " << g->g1[i][j] << "\t ";
      }
   }
}
 
int main(){
   srand(time(0));//Seed the random number generator
   //Matrices in the graph are made when graph is initialized 
   graph test1(10, 0.7);//Initializes with size and density 
   graph test2(8, 0.5);//Size and density are now fields of class graph
   //All that's left to do is to print them out!
   cout << "Test simple graph generation" << endl;
   print_graph(&test1);
   cout << endl << "END of TEST 1" << endl << endl;
   print_graph(&test2);
   cout << endl << "END of TEST 2" << endl << endl;
   return 0;
}

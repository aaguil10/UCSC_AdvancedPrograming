//Jacky Wong
//ID: 1281439
//
//matrix representation
//calloc goes to new or use vector
//printf goes to use of "<<"
//struct becomes class
//advanced make_ becomes a constructor
//
//This program prints out matrices of booleans representing a graph

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

inline double probability(){ return 1.0*rand()/RAND_MAX;}
inline int rand_dist(){ return rand() % 200 + 1;}          //returns a random int from 1-200
inline int rand_vert(){ return rand() % 1000;}             //returns a random int from 0-999

//declaration of graph class
//contains size and a 2D bool vector representing a matrix
//contains vectors representing graph data
class graph{
private:
   int size;
   int start, end;
   float uni_time, bi_time;
   vector< vector <bool> > matrix;           //vectors for unidirectional search
   vector< vector <int> > dist;
   vector <int> tentdist;
   vector <int> color;
   vector <int> parent;
   vector <int> tentparent;

   vector < vector <bool> > trans_matrix;    //vectors for bidirectional search
   vector < vector <int> > trans_dist;
   vector <int> tentdist1;
   vector <int> tentdist2;
   vector <int> color1;
   vector <int> color2;
   vector <int> parent1;
   vector <int> parent2;
   vector <int> tentparent1;
   vector <int> tentparent2;

public:
   graph(int s, double density);
   void print_graph();
   bool is_connected();
   void find_path();
   void print_path();
   void bi_find_path();
   void change_start_end();
   void print_time();
   void reset_vectors();
};

//changed make_graph to a constructor and returns a pointer to the graph created
//takes in size and density as arguments
graph::graph(int s, double density){
   size = s;
   uni_time = 0;
   bi_time = 0;
   matrix.resize(size);                //resize the vector of vectors to s
   dist.resize(size);                  //resize the vector of int vectors for distance
   color.resize(size,0);               //resize the int vector representing colors
   tentdist.resize(size,-1);           //resize the tentative distance vectors and initialize it to -1, representing infinity
   parent.resize(size,-1);             //resize the parent vector and initialize it to -1, representing no parent
   tentparent.resize(size,-1);         //resize the tentative parent vector and initialize it to -1, representing no parent

   trans_matrix.resize(size);          //resize vectors for bidirectional search
   trans_dist.resize(size);
   color1.resize(size,0);
   color2.resize(size,0);
   tentdist1.resize(size,-1);
   tentdist2.resize(size,-1);
   parent1.resize(size,-1);
   parent2.resize(size,-1);
   tentparent1.resize(size,-1);
   tentparent2.resize(size,-1);

   for(int i = 0; i < size; ++i){   
      matrix[i].resize(size);          //resize the inner vectors
      dist[i].resize(size);            //resize the distance vector
      trans_matrix[i].resize(size);    //resize the inner vectors
      trans_dist[i].resize(size);      //resize the distance vector
   }

   for(int i = 0; i < size; ++i){
      for(int j = 0; j < size; ++j){
         if(probability() < density){   //fill in the vector matrix with random connections based on probability
            matrix[i][j] = true;
            trans_matrix[j][i] = true;
         }
         dist[i][j] = rand_dist();     //randomize all distances to an int from 1-200
         trans_dist[j][i] = dist[i][j];
      }
   }
}

//changes the start and end nodes
void graph::change_start_end(){
   start = rand_vert();
   end = rand_vert();
   if(start == end){
      while(start == end)
         end = rand_vert();
   }

}

//print the graph by iterating through each vector
void graph::print_graph(){
   cout << "graph size " << size << endl;
   for(int i = 0; i < size; ++i){
      cout << endl;
      for(int j = 0; j < size; ++j){
         cout << " " << matrix[i][j] << "\t";
      }
   }
   for(int i = 0; i < size; ++i){
      cout << endl;
      for(int j = 0; j < size; ++j){
         cout << " " << dist[i][j] << "\t";
      }
   }
}

//breadth first search to check if the graph is connected
bool graph::is_connected(){
   int old_size = 0, c_size = 0;
   vector <bool> close(size);
   vector <bool> open(size);

   for(int i = 0; i < size; ++i){
      open[i] = close[i] = false;
   }
   open[0] = true;

   while(c_size < size){
      for(int i = 0; i < size; ++i){
         old_size = c_size;
         if(open[i] && (close[i] == false)){
            close[i] = true;
            c_size++;
            for(int j = 0; j < size; ++j)
               open[j] = open[j] || matrix[i][j];
         }
      }
   if(c_size == size) return true;
   if(old_size == c_size) return false;
   }
}

//unidirectional graph search using Dijkstra's algorithm
void graph::find_path(){
   clock_t t = clock();

   int current;
   int smallest;

   smallest = start;         //initialize smallest and current to start
   current = start;
   tentdist[current] = 0;    //initialize tentative distance of start to 0;


   //Begin Dijkstra's algorithm to find the path
   while(true){   
      current = smallest;                                                    //set current node to smallest
      for(int i = 0; i < size; ++i){
         if(matrix[current][i] == 1 && color[i] == 0 && i != current){       //loop through all unvisited nodes that current can connect to
            if(tentdist[i] == -1){                                           //if the tentative distance is infinity, set it
                tentdist[i] = tentdist[current] + dist[current][i];          //calculate their tentative distances
                tentparent[i] = current;                                     //set tentative parent of destination node to current
            }
            else if(tentdist[i] >= tentdist[current] + dist[current][i]){   //if the current tentative distance of a neighbor is larger than what it will be
               tentdist[i] = tentdist[current] + dist[current][i];           //replace it with the new tentative distance
               tentparent[i] = current;
            }
         }
      }   

      color[current] = 1;                             //set the current node to visited
      if(current != start)                            //set parent of node
         parent[current] = tentparent[current];

      if(color[end] == 1){                            //if the destination node is visited, then we want to end
         break;
      }

      smallest = -1;                                //initialize smallest as -1
      int i;
      for(i = 0; i < color.size(); ++i){            //find the first noninfinity tentative distance
         if(tentdist[i] > -1 && color[i] == 0){
            smallest = i;
            break;
         }
      }
      for(; i < color.size(); ++i){                 //find the smallest tentative distance
         if(tentdist[i] > -1 && tentdist[i] <= tentdist[smallest] && color[i] == 0){
            smallest = i;
         }
      }
      if(smallest == -1){                           //if it didn't find any non-infinity tentative distance, then the graph is disconnected
         cout << " DISCONNECTED!!! " << endl;
         break;
      }
   }

   t = clock() - t;
   uni_time = uni_time + ((float)t)/CLOCKS_PER_SEC;
}


//bidirectional graph search using Dijkstra's algorithm
void graph::bi_find_path(){
   clock_t t = clock();

   int current1, current2;
   int smallest1, smallest2;
   vector <int> visited1;
   vector <int> visited2;
   bool found = false;
   smallest1 = start;          //initialize smallest and current variables to their respective beginnings
   smallest2 = end;
   current1 = start;           
   current2 = end;
   tentdist1[current1] = 0;    //intialize start tentative distances to 0
   tentdist2[current2] = 0;


   while(true){
      current1 = smallest1;      //set current to smallest for each search
      current2 = smallest2;

     //start searching from start node
      for(int i = 0; i < size; ++i){                                              //set tentative distances of the neighbor nodes
         if(matrix[current1][i] == 1 && color1[i] == 0 && i != current1){
            if(tentdist1[i] == -1){
                tentdist1[i] = tentdist1[current1] + dist[current1][i];
                tentparent1[i] = current1;
            }
            else if(tentdist1[i] >= (tentdist1[current1] + dist[current1][i])){
               tentdist1[i] = tentdist1[current1] + dist[current1][i];
               tentparent1[i] = current1;
            }
         }
      }
      color1[current1] = 1;                              //set current node to visited
      if(current1 != start) parent1[current1] = tentparent1[current1];

      visited1.push_back(current1);                      //add the node to the visited list for this search

      if(color1[end] == 1){                              //if end is colored in this search, then a path was found
         break;
      }

      for(int i = 0; i < visited2.size(); ++i){          //if the node added to visited exists in the other search's visited, then there is a connection
         if(current1 == visited2[i]){
            found = true;
            break;
         }
      }
      if(found) break;                                 //if a link is found, then break out of the algorithm

      smallest1 = -1;                                  //find the smallest tentative distance
      int i;
      for(i = 0; i < color1.size(); ++i){
         if(tentdist1[i] > -1 && color1[i] == 0){
            smallest1 = i;
            break;
         }
      }
      for(; i < color1.size(); ++i){
         if(tentdist1[i] > -1 && tentdist1[i] <= tentdist1[smallest1] && color1[i] == 0){
            smallest1 = i;
         }
      }
      if(smallest1 == -1){                             //if the only tentative distances are infinity, then the graph is disconnected
         cout << " DISCONNECTED!!! " << endl;
         break;
      }

      //start search from end node 
      for(int i = 0; i < size; ++i){                   //set parent of smallest node
         if(trans_matrix[current2][i] == 1 && color2[i] == 0 && i != current2){
            if(tentdist2[i] == -1){
                tentdist2[i] = tentdist2[current2] + trans_dist[current2][i];
                tentparent2[i] = current2;
            }
            else if(tentdist2[i] >= (tentdist2[current2] + trans_dist[current2][i])){
               tentdist2[i] = tentdist2[current2] + trans_dist[current2][i];
               tentparent2[i] = current2;

            }
         }
      }
      color2[current2] = 1;                //set current node to visited
      visited2.push_back(current2);        //add current node to visited list for this search

      if(current2 != end) parent2[current2] = tentparent2[current2];/////////////////////////////////////////////


      if(color2[start] == 1){              //if the start node was visited in this search, then a path was found
         break;
      }

      for(int i = 0; i < visited1.size(); ++i){            //if the current node exists in the visited list of the other search, then a link has been found
         if(current2 == visited1[i]){
            found = true;
            break;
         }
      }  
      if(found) break;         //if a link is found, break out of the algorithm

      smallest2 = -1;          //find the smallest tentative distance
      for(i = 0; i < color2.size(); ++i){
         if(tentdist2[i] > -1 && color2[i] == 0){
            smallest2 = i;
            break;
         }
      }
      for(; i < color2.size(); ++i){
         if(tentdist2[i] > -1 && tentdist2[i] <= tentdist2[smallest2] && color2[i] == 0){
            smallest2 = i;
         }
      }
      if(smallest2 == -1){     //if the only tentative distances is infinity, then the graph is disconnected
         cout << " DISCONNECTED!!! " << endl;
         break;
      }
   }
   t = clock() - t;
   bi_time = bi_time + ((float)t)/CLOCKS_PER_SEC;
}

//print path of graph
void graph::print_path(){
   int current;
   current = end;
   cout << end;
   while(current != start){
      cout << "<-" <<  parent[current];
      current = parent[current];
   }
   cout << endl;
}

//print the time taken for each searches
void graph::print_time(){
   cout << "Time for unidirectional: " << uni_time << " seconds " << endl;
   cout << "Time for bidirectional: " << bi_time << " seconds " << endl;

}

//reset the vectors so a new search can be made
void graph::reset_vectors(){
   color.clear();
   tentdist.clear();
   parent.clear();
   tentparent.clear();
   color1.clear();
   color2.clear();
   tentdist1.clear();
   tentdist2.clear();
   parent1.clear();
   parent2.clear();
   tentparent1.clear();
   tentparent2.clear();

   color.resize(size,0);               
   tentdist.resize(size,-1);           
   parent.resize(size,-1);             
   tentparent.resize(size,-1);         
   color1.resize(size,0);
   color2.resize(size,0);
   tentdist1.resize(size,-1);
   tentdist2.resize(size,-1);
   parent1.resize(size,-1);
   parent2.resize(size,-1);
   tentparent1.resize(size,-1);
   tentparent2.resize(size,-1);

}

//perform tests
int main(){
   srand(time(0));
   cout << "Test pathfinding with 1000 nodes and 0.1 density 100 times" << endl;
   graph test1 = graph(1000, 0.1);
   while(!test1.is_connected()){
      test1 = graph(1000, 0.1);
   }
   for(int i = 0; i < 100 ; ++i){
      test1.change_start_end();
      test1.find_path();
      test1.bi_find_path();
      test1.reset_vectors();
   }
   test1.print_time();
   cout << endl << "END of TEST 1" << endl << endl;

   cout << "Test path finding with 1000 nodes and 0.01 density 100 times" << endl;
   graph test2 = graph(1000, 0.01);
   while(!test2.is_connected()){
      test2 = graph(1000,0.01);
   }
   for(int i = 0; i < 100; ++i){
      test2.change_start_end();
      test2.find_path();
      test2.bi_find_path();
      test2.reset_vectors();
   }
   test2.print_time();
   cout << endl << "END of TEST 2" << endl << endl;

   return 0;
}












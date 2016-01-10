//matrix representation
//calloc goes to new or use vector
//printf goes to use of "<<"
//struct becomes class
//advanced make_  becomes a constructor

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
 
double probability() {
  return 1.0*rand()/RAND_MAX;
}

typedef enum bool{false, true} bool; //unneeded in C++
typedef bool* ptr_bool;
typedef ptr_bool* bool_matrix;
 
typedef struct graph{
 
  int size;
  bool_matrix g1;
 
} graph;
 
void make_graph(int s, double density, graph* g){
  int i, j;  //after C99 can be local to for
  g->size =s;
  g->g1 = (bool_matrix)(calloc(s,sizeof(bool*)));
  for(i = 0; i < s; ++i) {
    g->g1[i] = (ptr_bool)(calloc(s, sizeof(bool)));
  }
  for(i =0; i < s; ++i) {
    for(j =0; j < s; ++j) {
      if(probability()< density) {
        g->g1[i][j] = true;
      }
    }
  }
}
 
void print_graph( graph* g){
  int i,j;
  printf("graph size %d\n" , g->size );
  for(i = 0; i < g->size; ++i) {
    printf("\n");
    for (j = 0; j < g->size; ++j) {
      printf(" %d\t ", g->g1[i][j]);
    }
  }
}

int main() {
  graph test1, test2; 
  srand(time(0)); 
  printf( "Test simple graph generation\n");
  make_graph(10, 0.7, &test1);
  print_graph(&test1);
  printf("\nEND of TEST 1\n\n");
  make_graph(8, 0.5, &test2);
  print_graph(&test2);
  printf("\nEND of TEST 2\n\n");
  return 0;
}

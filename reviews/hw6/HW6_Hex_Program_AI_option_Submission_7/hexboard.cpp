//assignment 4
//displaying the hex board
//to do a node struct was created to track neighbors and 
//overloading was perform to present the board

#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <chrono> 
#include <algorithm>
#include <set>
#include <utility>
#include "hexboard.h"

using namespace std;

//make a random seed for the shuffle in the movement function

typedef int vertex_n;


//class for the hexboard  
//the constructor
   graph::graph(int s = 11){
      //set size to the s input
      size = s;
      g1.resize(size);
      position.resize(size*size);
      //cycle through the graph and initializes
      for(auto i = 0; i < size; i++)
      {
         g1[i].resize(size);
         for(auto j = 0; j < size; j++)
         {
            //sets the x and y position
            g1[i][j].x = i;
            g1[i][j].y = j;

            //also stores list of all position to use in shuffle 
            //in the movement function
            position.push_back(make_pair(i,j));
         }
      }
      //assigns the pointers to the neighboring nodes
      for(auto i = 0; i < size; i++)
      {
         for(auto j = 0; j < size; j++)
         {

            neighborNodes(&g1[i][j], 0, -1);
            neighborNodes(&g1[i][j], 1, -1);
            neighborNodes(&g1[i][j], -1, 0);
            neighborNodes(&g1[i][j], 1, 0);
            neighborNodes(&g1[i][j], -1, 1);
            neighborNodes(&g1[i][j], 0, 1);
         }
      }
   }

   //assigning the neighbors to the nodes
   void graph::neighborNodes (node *temp, int i, int j)
   {
      int tempI = temp->x + i;
      int tempJ = temp->y + j;
      if(tempI < 0 || tempI >= size || tempJ < 0 || tempJ >= size)
      {
         return;
      }
      temp->surroundNode.push_back(&g1[tempI][tempJ]);
   }


  int graph::playAIgame(colors_t AIcolor, int xCoor, int yCoor) {
    int winNum = 0;
    int count = 1;
    //play the game 1000 times
    for(int k=0; k<1000; k++) {
      shuffle(position.begin(), position.end(), default_random_engine(time(0)));
      g1[xCoor][yCoor].color = AIcolor;
      count = 1;
      if(AIcolor == white) count = 0;

      //goes through all of the position 
      //for(int m = 0; m<position.size(); m++)
      for(auto m : position)
      {
         int i = m.first;
         int j = m.second;
         //even is blacks turn and it will get a shuffle position and make it black
         if(g1[i][j].color != empty){
            continue;
         }
         if(count%2 == 0)
         {
            g1[i][j].color = black;
         }
         else
         {
            g1[i][j].color = white;
         }
         count++;
      }
      //count the number of wins the AI gets in 1000 games
      if( searchForWinner(true) == AIcolor) winNum++;
      for(int a=0; a<11; a++) {
         for(int b=0; b<11; b++) {
            g1[a][b] = g1copy[a][b];
            g1[a][b].visited = false;
         }
      }
    }
    return winNum;
  }
  //AI movement
  pair<int, int> graph::newMovement(colors_t AIcolor, bool swapOK) {
    //storing the win for each spot
    vector< vector<int> > wincount;
    //making a copy of the original board
    g1copy.resize(11);
    wincount.resize(11);
    for(int i=0; i<11; i++) {
      g1copy[i].resize(11);
      wincount[i].resize(11);
      for(int j=0; j<11; j++) {
        g1copy[i][j] = g1[i][j];
        wincount[i][j] = 0;
      }
    }

    for(int i=0; i<11; i++) {
      for(int j=0; j<11; j++) {
        if(g1[i][j].color == empty || swapOK) {
          wincount[i][j] = playAIgame(AIcolor, i, j);

          //loop returns g1 to its original boardstate
          for(int i=0; i<11; i++) {
            for(int j=0; j<11; j++) {
              g1[i][j] = g1copy[i][j];
              g1[i][j].visited = false;
            }
          }
          
        }
      }
    }
    //get the i and j location with the highest wins
    int winI = 0;
    int winJ = 0;
    for(int i=0; i<11; i++) {
      for(int j=0; j<11; j++) {
        if(wincount[i][j] > wincount[winI][winJ]) {
          winI = i;
          winJ = j;
        }
      }
    }
    g1[winI][winJ].color = AIcolor;
    pair<int, int> answer = make_pair(winI, winJ);
    return answer;
  }

   //search for a winner 
   colors_t graph::searchForWinner(bool AI)
   {
      for(int i = 0; i<size; i++)
      {
         if(g1[i][0].color == white)
         {
            //making a queue
            set<pair<vertex_n, vertex_n>> vQueue;
            vQueue.insert(make_pair(i, 0));
            //assigned the visited node to true
            g1[i][0].visited = true;
            vertex_n tempX;
            vertex_n tempY;
            while(!vQueue.empty())
            {
               tempX=vQueue.begin()->first;
               tempY=vQueue.begin()->second;
               vQueue.erase(vQueue.begin());
               //return the winner is the end is reach 
               //else the other one is the winner
               if(tempY == size-1){
                  return white;
               }
               //checks the neighbor
               for(auto i : g1[tempX][tempY].surroundNode)
               {
                  if( (!i->visited) && (i->color == white) )
                  {
                     i->visited = true;
                     vQueue.insert(make_pair(i->x, i->y));
                  }
               }
            }
         }
      }
      //resetting the visited 
      for(int i = 0; i<size; i++) {
        for(int j = 0; j<size; j++) {
          g1[i][j].visited = false;
        }
      }

      if(!AI) 
      {
        for(int i = 0; i<size; i++) {
           if(g1[0][i].color == black)
           {
              //making a queue
              set<pair<vertex_n, vertex_n>> vQueue;
              vQueue.insert(make_pair(0, i));
              //assigned the visited node to true
              g1[0][i].visited = true;
              vertex_n tempX;
              vertex_n tempY;
              while(!vQueue.empty())
              {
                 tempX=vQueue.begin()->first;
                 tempY=vQueue.begin()->second;
                 vQueue.erase(vQueue.begin());
                 //return the winner is the end is reach 
                 //else the other one is the winner
                 if(tempX == size-1){
                    return black;
                 }
                 //checks the neighbor
                 for(auto i : g1[tempX][tempY].surroundNode)
                 {
                    if(!i->visited && i->color == black)
                    {
                       i->visited = true;
                       vQueue.insert(make_pair(i->x, i->y));
                    }
                 }
              }
           }
         }
      }
 
      for(int i = 0; i<size; i++) {
        for(int j = 0; j<size; j++) {
          g1[i][j].visited = false;
        }
      }

      if(AI) return black;
      return empty;
   }
   //the player movement
   bool graph::playerMovement(colors_t Pcolor, int x, int y, bool swapOK) {
      if(g1[x][y].color == empty || swapOK) {
        g1[x][y].color = Pcolor;
      } else {
        cout << "Not an empty space. Try again." << endl;
        return false;
      }
      return true;
   }
   //clearing the board
   void graph::clearG1(){
      for(int a=0; a<11; a++) {
        for(int b=0; b<11; b++) {
          g1[a][b].color = empty;
        }
      }
   }


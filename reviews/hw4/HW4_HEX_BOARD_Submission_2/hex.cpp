// Kevin Doyle
// February 17th, 2014
// CMPS 109
// Assignment 4

// This program plays the game HEX by itself, in a dumb way. 
// It will build a blank game board, then randomly distribute 
// moves across the board until no moves remain. Then it 
// determines which player has won the game. 

// In particular, this exact file as I submit it will play and
// print four games, in the board dimensions mentioned on the
// HEX Wikipedia page. 


#include <iostream>
#include <cstdlib>
#include <random>
#include <ctime>
#include <vector>
#include <list>
#include <iterator>   

using namespace std;

// Creates random numbers
default_random_engine randoNumGen( time(0) );
// Defines a distribution
// Note, this distribution will limit the game board
// size to be smaller than 100x100
uniform_int_distribution<int> int_dist( 0 , 100 );

class node {
   public:
      // I would like these to be private, but it wasn't working.
      int i, j;

      node() : i(-1), j(-1) {}
      node( int i, int j) : i(i), j(j) {}
};

class HEX {
   private:
      // 2D vector of chars used as game board
      vector< vector< char > > board;
      
      // List of open spaces
      list< node > open;
      
      // Counts the remaining moves
      int moves = 0;
      
      // Size of one dimension of the board
      int size = 0;
   
   public:
      // Overloards the << operator when << is used with a hex object
      friend ostream& operator<< (ostream &out, const HEX &h);
      
      // Constructs a hex game board
      HEX( int size );
      
      // Plays the game
      void playGame();
      
      // Creates a list of available spaces
      void listOpen();
      
      // Randomly selects an open space
      list<node>::iterator findSpace();
      
      // Returns the winning char (X or O)
      char findWinner();

};

inline int randNum() { return int_dist(randoNumGen); }

HEX::HEX( int new_size ) {
   
   // Sets the size of the board
   size = new_size;

   // Sets the counter of remaining moves for this board
   moves = size * size;
   
   // Sets us up the board, with - in unplayed upon spaces
   board.resize( size, vector< char >( size, '-' ) );
   
   
}

// Creates list of open spaces
void HEX::listOpen() {
   int i, j;

   // Creates a list of nodes
   // Each node represents an open space on the game board
   for( i = 0; i < this->size; i++ ) {
      for( j = 0; j < this->size; j++ ) {
         this->open.push_back( node(i, j) );
      }
   }
}

// Find open spot on list
list<node>::iterator HEX::findSpace( ) {
   // Generates a random number restricted by
   // the number of available moves (the list length)
   int k = randNum() % this->moves;
   list<node>::iterator it;
   
   // Iterate down the list to the kth position
   it = this->open.begin();
   advance(it, k);

   // Returns the randomly selected position
   return it;
}

// Determines winner by breadth first search
// If one player does not win, the other does
char HEX::findWinner( ) {
   // Lets say X plays top to bottom
   // We'll see if X made a path

   // Misc useful declarations
   node temp;
   int i = 0, j;
   int k, l;
   
   // Will store our connected nodes
   list< node > Q;
   
   // Keeps track of visited nodes
   vector< vector < bool > > V;
   V.resize( this->size, vector< bool >( this->size, false ) );
   
   // Breadth first search
   for( j = 0; j < this->size; j++) {
      if( this->board[i][j] == 'X' ) {
         // Creates a root node and pushes onto queue
         node root( i, j );
         Q.push_front(root);
         V[i][j] = true;
         
         // The connected nodes will be pushed onto the queue.
         // Connected nodes are then taken off the queue, checked for 
         // unvisited connected nodes, and the cycle repeats as long as
         // new connected nodes continue to be found.
         while( !Q.empty() ) {
            temp = Q.front();
            Q.pop_front();
            
            // If a path of connected nodes leads to the other side of the board,
            // then X is the winner, and the char 'X' is returned.
            if( temp.i == this->size - 1 ) { return 'X'; }
            
            k = temp.i;
            l = temp.j;
                              
            // These are six checks for connected nodes
            if( k-1 >= 0 && this->board[k-1][l] == 'X' ) {
               if( !V[k-1][l] ) {
                  V[k-1][l] = true;
                  node connection( k-1, l );
                  Q.push_back( connection );
               }
            }
            
            if( k-1 >= 0 && l+1 < this->size 
                                 && this->board[k-1][l+1] == 'X' ) {
               if( !V[k-1][l+1] ) {
                  V[k-1][l+1] = true;
                  node connection( k-1, l+1 );
                  Q.push_back( connection );
               }
            }
            
            if( l+1 < this->size && this->board[k][l+1] == 'X' ) {
               if( !V[k][l+1] ) {
                  V[k][l+1] = true;
                  node connection( k, l+1 );
                  Q.push_back( connection );
               }
            }
            
            if( k+1 < this->size && this->board[k+1][l] == 'X' ) {
               if( !V[k+1][l] ) {
                  V[k+1][l] = true;
                  node connection( k+1, l );
                  Q.push_back( connection );
               }
            }
            
            if( k+1 < this->size && l-1 >= 0 && this->board[k+1][l-1] == 'X' ) {
               if( !V[k+1][l-1] ) {
                  V[k+1][l-1] = true;
                  node connection( k+1, l-1 );
                  Q.push_back( connection );
               }
            }
            
            if( l-1 >= 0 && this->board[k][l-1] == 'X' ) {
               if( !V[k][l-1] ) {
                  V[k][l-1] = true;
                  node connection( k, l-1 );
                  Q.push_back( connection );
               }
            } 
         }
      }
   }
   
   // No path of X nodes connected to the opposite side, 
   // so O must have made a bridge and 'blocked' the Xs. 
   // Thus, we return 'O' as the winner. 
   return 'O';
   
}

// Plays the game until no possible moves remain
void HEX::playGame() {
   int i, j;
   list<node>::iterator itX, itO;
   
   this->listOpen();
   
   // Makes random plays on the board
   while( this->moves > 0 ) {
      
      itX = this->findSpace();
      
      node spaceX = *itX;
      i = spaceX.i;
      j = spaceX.j;
      this->board[i][j] = 'X';
      this->open.erase(itX);

      this->moves--;
      if ( this->moves == 0) { break; }     
      
      itO = this->findSpace();
      
      node spaceO = *itO;
      i = spaceO.i;
      j = spaceO.j;
      this->board[i][j] = 'O';
      this->open.erase(itO);

      this->moves--;
   }
   
}

ostream& operator<< (ostream &out, const HEX &h) { 
   int i, j, k;
   for( i = 0; i < h.size; i++ ) {
      out << endl;
      k = i;
      for( j = 0; j < h.size; j++ ) {
         while( k > 0 ) {
            out << "  ";
            k--;
         }
         out << " " << h.board[i][j] << "  ";
      }
   }
   out << endl;
}


int main(void) {
   srand(time(0));

   // Creates the blank game boards
   HEX test0( 11 );
   HEX test1( 13 );
   HEX test2( 14 );
   HEX test3( 19 );
   
   // Plays on the boards
   test0.playGame();
   test1.playGame();
   test2.playGame();
   test3.playGame();
   
   // Prints the boards and announces winners
   cout << test0 << endl;
   cout << "The winner of game 1 is: " << test0.findWinner() << endl;
   
   cout << test1 << endl;
   cout << "The winner of game 2 is: " << test1.findWinner() << endl;
   
   cout << test2 << endl;
   cout << "The winner of game 3 is: " << test2.findWinner() << endl;
   
   cout << test3 << endl;
   cout << "The winner of game 4 is: " << test3.findWinner() << endl;

   
   return 0;
}

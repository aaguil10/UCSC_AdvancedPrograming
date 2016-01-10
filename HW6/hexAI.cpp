/*hexAI.cpp */
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

#include "hexAI.h"

hexAI::hexAI(Board &G){
  highestProb[0] = 0;
  highestProb[1] = 0;
  highestProb[2] = 0;
  num_of_P2 = 0;
}


// generates random game
// fills the board with colors evenly 50/50
// uses vector with size equal to # of moves in the board
// shuffles the vector & fills the board with the colors
bool hexAI::finish_game(Board &G, EDGECOLOR color,vector<EDGECOLOR> &color_tag){
  srand(unsigned(time(NULL)));
  // shuffles all the entries in the array to simulate moves
  random_shuffle(color_tag.begin(), color_tag.end());
  int i = 0; 
  for(int x = 0; x < G.GetSize(); ++x){
    for(int y = 0; y < G.GetSize(); ++y){
      if((G.matrix[x][y].get_node() == 3000) 
             && (i < G.GetSize() * G.GetSize())) {
        G.matrix[x][y].set_color(color_tag[i]);
        int node_number = y + (x * G.GetSize());
        G.matrix[x][y].set_node(node_number);
        i++;
      }
    }
  }
  return G.FindWinner(color);
}


/***************************************************************************\
Monte Carlo algorithm 
* ! ! * *      0 is the player's move, @ is the AI's move
 * * * @ *     it's the AI's move now, so the AI looks at all the empty
  * ! * * *    positions. For each empty position, the AI simulates the real
   * * @ * *   game by filling the hex board with random colors and performs
    * * * * *  the same check-win operation 1000 times. After all empty positions are tested, the AI picks the position with the highest winning rate. 
Now, the AI makes its real move with the highest winning rate.
*****************************************************************************/

double hexAI::monte_carlo(Board &G, EDGECOLOR){
  Board A = G;
  int wins_P1 = 0;
  int wins_P2 = 0;
  const int trials = 1000;

  //creates verctor full of colors that will be shuffel later
  vector<EDGECOLOR> color_tag;
  for (int i = 0; i < plays_left(num_of_P2, G.GetSize()); i++) {
    if (i < (plays_left(num_of_P2, G.GetSize())/ 2)){
      color_tag.push_back(P1);
    } else {
      color_tag.push_back(P2);
    }
  }

  set_highestProb(0, 0, 0);
  //Go through the board
  for(int i = 0; i < G.GetSize(); ++i){
    for(int j = 0; j < G.GetSize(); ++j){
      // For each empty position
      if(G.matrix[i][j].get_node()== 3000 
         || G.matrix[i][j].get_color() == NOCOLOR){
        wins_P1 = 0;
        wins_P2 = 0;
        // Simulates the win-lose operation 1000 times
        for(int x = 0; x < trials; x++){
          A = G;
          A.makeMove(P2,i,j);
          // Checks if P1 wins, keeps track of how often
          if(finish_game(A, P2, color_tag) == true){
            // Increment the probability by 1 at that position if the AI wins
	    wins_P1++;  // keeps track of P1 wins
          } else {
	    wins_P2++;  // keeps track of P2 wins
	  }
        }
        A.matrix[i][j].incr_prob(static_cast<double>(wins_P1)/trials);
        //Gets the highest probability
        if(highestProb[0] < A.matrix[i][j].get_prob()){
          //store the corresponding (x,y) coord in array.
          set_highestProb(static_cast<double>(wins_P1)/trials, i, j);
        }   
      }
    }
  }
  return highestProb[0];
}


//returns a string with the AI's move "x,y"
string hexAI::play(Board &G){
  //compute best move
  this->monte_carlo(G,P2);
  int x = highestProb[1];
  int y = highestProb[2];
  string move = to_string(x) + "," + to_string(y);
  num_of_P2++;
  return move;
}
  

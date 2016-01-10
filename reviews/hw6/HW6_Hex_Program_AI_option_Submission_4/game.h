//Alexander Sadeghi, Delan Diaz

#include <vector>
#include <cstdlib>
#include "hexBoard.h"

using namespace std;

enum Agent {NOBODY, PLAYER, COM};
	
class Game {
	public:
        	//constructor
      		Game(int iterations, int plies):turn(0), ai_monte_carlo_iterations(iterations), ai_plies(plies) {
        		board = new hexBoard(11);
      		}
      		~Game(){
        		delete board;
      		}
      		void drawBoard();
      		void play();
		pair<int, int> getPlayerMove();
		int win;
    	private:
      		void movePlayer(bool piRule = false);
      		int turn;
     		int ai_monte_carlo_iterations;
      		int ai_plies;
      		hexBoard* board;
};

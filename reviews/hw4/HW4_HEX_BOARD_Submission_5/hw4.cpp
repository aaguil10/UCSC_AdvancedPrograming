//CMPS109 HW4: Implementation of Hex Game Board
//Copyright Jingya Liu, Di Ni

#include<iostream>
#include"hex_game.h"
using namespace std;

int main()
{
   hex_board board1;
   board1.randomPlay();

   cout << board1 << endl;
   board1.findWinner();

   return 0;
}

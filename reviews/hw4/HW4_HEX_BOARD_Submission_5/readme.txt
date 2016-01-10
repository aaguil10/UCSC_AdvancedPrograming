This is a C++ version of Hex Game implementation. 
Jingya Liu Team Member: Di Ni
==============================================================
TO COMPILE:
1) Extract all files to your working directory
2) Excute 'make'

==============================================================
OPTIONS:
1) The program generate a 11 * 11 Hex game board by default.If you want to change the board size,
just modify "STD_SIZE" in hex_game.h file.

2) You can output the connecting path on hex board,just by uncommenting a few lines in hex_game.cpp.
Please follow instructions in hex_game.cpp.

3) This program let two players take turns to make random moves until hex board is full and then
determine which playter wins. By default, the program terminates once a "first" winner is found.
But in this random play version, it might be that both palyters win.In addition, there might also be mutiple
connecting paths in the board.
In hex_game.cpp file, there are options to explore all these possibilities just by comment out
several lines.Please follow instructions in hex_game.cpp.


==============================================================
In this assignment,my team member Di Ni and I discussed the class desgin and algorithm implementation together.
I coded up the classes main frames,hex board output function and transform hex board into a graph.
Di Ni coded the random play functions and find winner function.I further finalize the codes and seperate them into
header file and implementaion files.

By doing this assignment, I learned:
1)C++ implementation of depth first search
2)how to transfrom a hex game board into a graph representation
3)how to seperate a large chunk of code into header file and implementation file

Thank you for taking the time to read this and grade my program.

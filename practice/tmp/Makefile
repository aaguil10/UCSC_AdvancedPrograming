
main: Graph.o Board.o edge.o main.o
	g++ -std=c++11 -g -o main edge.o Board.o Graph.o main.o

Graph.o: Graph.cpp Graph.h
	g++ -std=c++11 -g -c Graph.cpp

main.o: main.cpp
	g++ -std=c++11 -g -c main.cpp

Board.o: Board.cpp Board.h
	g++ -std=c++11 -g -c Board.cpp

edge.o: edge.cpp edge.h
	g++ -std=c++11 -g -c edge.cpp

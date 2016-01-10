# Makefile for the socket programming example

all : simple_server simple_client

simple_server: hexAI.o edge.o Board.o ServerSocket.o Socket.o simple_server_main.o 
	g++ -std=c++11 -o simple_server Board.o edge.o hexAI.o ServerSocket.o Socket.o simple_server_main.o

simple_client: ClientSocket.o Socket.o simple_client_main.o Board.o edge.o hexAI.o
	g++ -std=c++11 -o simple_client ClientSocket.o Socket.o simple_client_main.o Board.o edge.o hexAI.o

Socket.o: Socket.cpp Socket.h 
	g++ -std=c++11 -c Socket.cpp

ServerSocket.o: ServerSocket.cpp ServerSocket.h
	g++ -std=c++11 -c ServerSocket.cpp

ClientSocket.o: ClientSocket.cpp ClientSocket.h
	g++ -std=c++11 -c ClientSocket.cpp
    
simple_server_main.o: simple_server_main.cpp 
	g++ -std=c++11 -c simple_server_main.cpp
    
simple_client_main.o: simple_client_main.cpp 
	g++ -std=c++11 -c simple_client_main.cpp    

Board.o: Board.cpp Board.h
	g++ -std=c++11 -g -c Board.cpp

edge.o: edge.cpp edge.h
	g++ -std=c++11 -g -c edge.cpp

hexAI.o: hexAI.cpp hexAI.h
	g++ -std=c++11 -g -c hexAI.cpp
    


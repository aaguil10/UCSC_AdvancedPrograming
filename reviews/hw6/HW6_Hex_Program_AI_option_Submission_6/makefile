CXXFLAGS = -g -O0 -std=c++11

#hw4: hw4.o BoardController.o Board.o 
#	g++ -o hw6 ${CXXFLAGS} hw4.o Board.o BoardController.o

hw6.o: hw4.cpp BoardController.o Board.o
	g++ -o hw6 ${CXXFLAGS} hw4.cpp BoardController.o Board.o -lpthread
Board.o: Board.cpp Board.h
	g++ -c ${CXXFLAGS} Board.cpp -lpthread
BoardController.o: BoardController.cpp BoardController.h Board.h
	g++ -c ${CXXFLAGS} BoardController.cpp -lpthread
clean:
	rm -f hw6 *.o *~
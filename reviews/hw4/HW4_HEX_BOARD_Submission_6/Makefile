#//Kevin Yeap
#//1270597
#//kyeap@ucsc.edu
#//cpms109 f14

CC     = gcc
CFLAGS = -std=c++11 -Wall -Wextra -lstdc++

hex:	hex.o node.o
	${CC} -o hex ${CFLAGS} hex.o node.o

hex.o:	hex.cpp 
	${CC} -c ${CFLAGS} hex.cpp 
  
node.o:	node.cpp node.h
	${CC} -c ${CFLAGS} node.cpp 

clean:
	rm -f hex hex.o node.o

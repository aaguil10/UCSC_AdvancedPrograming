CC	= g++
CFLAGS  = -g -Wall -O0 -std=c++11

main: main.o
	$(CC) -o main $(CFLAGS) main.o

main.o: main.cpp
	$(CC) -c $(CFLAGS) main.cpp

clean:
	rm -f main.o
	rm -f main
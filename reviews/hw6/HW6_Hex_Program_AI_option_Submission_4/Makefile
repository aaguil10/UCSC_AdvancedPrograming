TARGET= client
CC= g++
CFLAGS= -std=c++0x -O3 -Wall -Wextra
DEPS = game.h hexBoard.h hexGraph.h
OBJ = main.o hexGraph.o game.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o
	rm -f $(TARGET)

.PHONY: default all clean

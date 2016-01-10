GCC       = g++ -std=c++11

MKFILE    = Makefile
SOURCES   = pi.cc
EXECBIN   = pi
OBJECTS   = $(SOURCES:.cc=.o)

all:
		$(GCC) -o $(EXECBIN) $(SOURCES)

clean:
		- rm $(EXECBIN)

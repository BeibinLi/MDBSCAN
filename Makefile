CC = g++
CFLAGS  = -c -g -std=c++11 -pedantic -pedantic-errors -Wall -Wextra -Wconversion -Wno-unused-parameter -w

all: Point.o MDBSCAN.o main.o
	$(CC) -g Point.o MDBSCAN.o main.o -o prog

Point.o: Point.h Point.cpp
	$(CC) $(CFLAGS)  Point.cpp

MDBSCAN.o: MDBSCAN.h MDBSCAN.cpp Point.o
	$(CC) $(CFLAGS)  MDBSCAN.cpp

main.o: main.cpp Point.o MDBSCAN.o
	$(CC) $(CFLAGS)  main.cpp Point.o MDBSCAN.o

test1: all
	./prog < 1.in

test2: all
	./prog < 2.in

test3: all
	./prog < 3.in

clean:
	rm -rf *.o *.out *.exe



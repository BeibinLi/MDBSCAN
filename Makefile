CC = g++
CFLAGS  = -g -std=c++11 -pedantic -pedantic-errors -Wall -Wextra -Wconversion -Wno-unused-parameter -w

prog: main.cpp MDBSCAN.o Point.o
	$(CC) $(CFLAGS) main.cpp Point.o MDBSCAN.o -o prog

Point.o: Point.h Point.cpp
	$(CC) $(CFLAGS) -c Point.cpp

MDBSCAN.o: MDBSCAN.h MDBSCAN.cpp
	$(CC) $(CFLAGS) -c MDBSCAN.cpp


test1: prog
	./prog < 1.in

test2: prog
	./prog < 2.in

test3: prog
	./prog < 3.in

clean:
	rm -rf *.o *.out *.exe prog



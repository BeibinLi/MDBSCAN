CC = g++
CFLAGS  = -c -g -std=c++11 -pedantic -pedantic-errors -Wall -Wextra -Wconversion -Wno-unused-parameter

all: Point.o MDBSCAN.o main.o
	$(CC) -g Point.o MDBSCAN.o main.o -o a.o

Point.o: Point.h Point.cpp
	$(CC) $(CFLAGS)  Point.cpp

MDBSCAN.o: MDBSCAN.h MDBSCAN.cpp Point.o
	$(CC) $(CFLAGS)  MDBSCAN.cpp

main.o: main.cpp Point.o MDBSCAN.o
	$(CC) $(CFLAGS)  main.cpp Point.o MDBSCAN.o


clean:
	rm *.o

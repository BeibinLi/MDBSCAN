#include <iostream>
#include "math.h"

#include "Point.h"

#include "mex.h"


using namespace std;


Point::Point(){}
Point::~Point(){}

void Point::debug() {
	cout << time << " " << x << " " << y << endl;
}

double square_distance(Point a, Point b) {
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

double square_distance(Point * a, Point * b) {
	return (a->x - b->x)*(a->x - b->x) + (a->y - b->y)*(a->y - b->y);
}

double cartesian_distance(Point a, Point b) {
	return sqrt(square_distance(a, b));
}

double cartesian_distance(Point *a, Point *b) {
	return sqrt(square_distance(a, b));
}


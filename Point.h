#pragma once
#ifndef POINT_H
#define POINT_H


class Point
{
public:
	long long time;
	double x;
	double y;

	enum PType {UNKNOWN, VISITED, CLUSTERED, NOISE }; // Point type

	PType t;
	int CID; // cluster ID: = -1 for noise

	Point(long long time_, double x_, double y_) : 
		time(time_), x(x_), y(y_), t(PType::UNKNOWN), CID(-1) {}

	void debug();

	inline bool operator> (const Point& rhs) { return rhs.time < this->time; }
	inline bool operator< (const Point& rhs) { return rhs.time > this->time; }

	Point();
	~Point();
};

double square_distance(Point a, Point b);
double square_distance(Point *a, Point *b);

double cartesian_distance(Point a, Point b);
double cartesian_distance(Point *a, Point *b);

#endif

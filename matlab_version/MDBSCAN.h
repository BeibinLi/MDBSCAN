#pragma once
#ifndef MDBSCAN_H
#define MDBSCAN_H


#include <vector>
#include <deque>
#include "limits.h"

/*
	Modified DBSCAN Algorithm for Fixation Identification
*/
const long long TIME_REJECTION_GAP = LONG_MAX; 
// if two data exceed this time difference, there is a data lost in recording


// DBSCAN algorithm Main function.
// vector<long long> C contains the index [start_point, end_point]
std::vector < std::vector<long long> > mdbscan(const std::vector<Point *> & data, 
		double eps, long long minPts);

#endif

#include <algorithm>
#include <iostream>
#include <ctime>

#include "Point.h"
#include "MDBSCAN.h"

using namespace std;



void expandCluster(long long index, const std::vector<Point *> & data, 
		std::deque<long long> neighbors, std::vector<long long> & C, double eps, long long minPts);

std::deque<long long> regionQuery(long long index, const std::vector<Point*> & data, double eps);

deque<long long> regionQuery(long long index, const vector<Point*> & data, double eps) {
	deque<long long> rst;
	double square_dist = eps * eps; // we use square distance to save calculation time.

	for (size_t i = index; i < data.size(); i++) {
		if (i > 0 && abs(data[i]->time - data[i - 1]->time) > TIME_REJECTION_GAP) break; // exceed time gap, data lost
		if (square_distance(*data[i], *data[index]) <= square_dist) rst.push_back(i);
		else break;
	}

	for (long long i = index - 1; i >= 0; i--) {
		if ( abs(data[i]->time - data[i+1]->time) > TIME_REJECTION_GAP) break; // exceed time gap, data lost
		if (square_distance(*data[i], *data[index]) <= square_dist) rst.push_front( i );
		else break;
	}

	return rst;
}


void expandCluster(long long index, const vector<Point *> & data, deque<long long> neighbors, 
		vector<long long> & C, double eps, long long minPts ) {
	C.push_back( index );

	for (size_t i = 0; i < neighbors.size(); i++) {
		long long index_of_p = neighbors[i];
		Point * p = data[ index_of_p ];

		if (p->t == Point::PType::UNKNOWN ) {
			p->t = Point::PType::VISITED;
			if (p->t != Point::PType::CLUSTERED) {
				p->t = Point::PType::CLUSTERED;
				C.push_back(index_of_p);
			}

			deque<long long> neighbors_2 = regionQuery(index_of_p, data, eps);

			if (neighbors_2.size() >= minPts) 
				neighbors.insert(neighbors.end(), neighbors_2.begin(), neighbors_2.end());
		}
	}
}

vector < vector<long long>> mdbscan(const vector<Point *> & data, double eps, long long minPts) {
	vector< vector<long long>> rst;

	vector<long long> C;

	size_t n = data.size();

	for (long long i = 0; i < n; i++) {
		Point * p = data[i];
		if (p->t != Point::PType::UNKNOWN ) continue; // visited

		p->t = Point::PType::VISITED;
		deque<long long> neighbors = regionQuery(i, data, eps);

		if (neighbors.size() < minPts) p->t = Point::PType::NOISE;
		else {
			// p is not noise
			expandCluster(i, data, neighbors, C, eps, minPts);

			long long start_i = *min_element(C.begin(), C.end());
			long long end_i = *max_element(C.begin(), C.end());

			if (data[end_i]->time - data[start_i]->time >= 100) 
				// the fixation is greater than 100 ms
				rst.push_back({ *min_element(C.begin(), C.end()), *max_element(C.begin(), C.end()) });

			C.clear();
		}
	}
	return rst;
}



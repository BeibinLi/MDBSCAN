
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>
#include <assert.h>
#include <math.h>
#include <ctime>

#include "Point.h"
#include "MDBSCAN.h"

using namespace std;

void output(const vector<Point *> & data, vector < vector<long long> > clusters, string outfile) {
	cout << "There are " << clusters.size() << " fixations in the analysis" << endl;

	ofstream f;
	if (outfile.length() < 5) outfile = "out.txt";
	f.open( outfile.c_str() );

	long long prev_end = -1;
	for (size_t i = 0; i < clusters.size(); i++) {
		vector<long long> cls = clusters[i];

		assert( cls[0] < cls[1] );
		assert(cls[0] >= prev_end);
		prev_end = cls[1];

		// one cluseter is between data[cls[0]] and data[cls[1]] inclusively
		for (long long j = cls[0]; j <= cls[1]; j++)
			data[j]->CID = i + 1; // we need to + 1 because CID should be positive
	}

	for (size_t i = 0; i < data.size(); i++) {
		if (i > 0) assert(data[i]->CID == -1 || data[i]->CID >= data[i - 1]->CID);

		Point * p = data[i];
		f << p->x << " " << p->y << " " << p->time << " " << p->CID << endl;
	}

	f.close();
}


// Read gaze data from file
void read_data(string filename, vector<Point *> & data) {
	fstream f;
	f.open( filename.c_str() );

	long long time;
	double x, y;

	while (f.good()) {
		f >> x >> y >> time;
		data.push_back(new Point(time, x, y));
	}
	f.close();
}

int main(int argc, char *argv[])
{ 
	const int PIXEL_PER_DEGREE = 26.7;
	double eps = PIXEL_PER_DEGREE * 0.5; 
	int minPts = 20;
	string filename = "1.in";
	if (argc >= 2) filename = argv[1];

	vector<Point *> data;
	read_data(filename, data);
	cout << "Data Size: " << data.size() << endl;

	vector < vector<long long> > rst = dbscan(data, eps, 10);
	string output_name = filename.substr( 0, filename.find('.') );
	output(data, rst, output_name + ".out");

	for (long long i = 0; i < data.size(); i++) delete data[i];
	cout << "Finished" << endl;
	return 0;
}


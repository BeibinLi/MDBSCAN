/*
 * In Matlab call "mex dbscan_wrap.cpp",
 * Then, you can use "out = dbscan_wrap(data, eps, minPts)" in the matlab,
 * where data is a 2D array with t rows and 3 columns, the first column
 * is the x, the second column is y, and the third columns is time.
 *
 * eps and minPts are two numbers which are chosen for the DBSCAN algorithm.
 * 
 * The output of this function (cpp file) is a 2D matrix with t rows
 * and 4 columns, where the first three columns are same as the input data,
 * while the last column represent the CID (cluster ID), -1 means the point
 * is a saccade; otherwise, if CID >= 0, it's a fixation point. 
 *
 */


#include <vector>
#include <string>

#include "Point.cpp"
#include "MDBSCAN.cpp" 
// it's a terrible practice to include CPP files, 
// but this is the easiest way for Matlab


#include "mex.h"
using namespace std;




void mexFunction (int nlhs, mxArray *plhs[],
		int nrhs, const mxArray *prhs[])
{  
	if(nlhs != 1 || nrhs != 3){
		mexPrintf("I have %d inputs and %d outputs\n", nrhs, nlhs);
		mexErrMsgTxt("Need 3 input (data (n by 3 matrix: x,y,time), "
				"eps, minPts) and 1 output in the call\n");
	}


	double eps = * mxGetPr( prhs[1] );
	double minPts = * mxGetPr( prhs[2] );

	size_t m = mxGetM( prhs[0] ); // number of rows
	size_t n = mxGetN( prhs[0] ); // number of columns

	size_t rows(m), cols(n);

	if(rows < 2 || cols != 3){
		mexPrintf("Data has %d rows and %d columns\n", rows, cols);
		mexErrMsgTxt("Need n by 3 Matrix as Input!\n"
				"The first Column is time, the second columns is x, "
				"and third column is y");
	}

	mexPrintf("m=%d, n=%d\n", m, n);

	double * in = mxGetPr( prhs[0] );


	vector<Point *> data(rows);
	for(int i=0; i < rows; i++){
		//         data[i] = new Point( in[cols * i + 2], in[cols * i + 0],
		//                             in[cols * i + 1]);
		data[i] = new Point( in[2 * rows + i], in[ i],
				in[ rows + i ]);
	}


	vector < vector<long long> > clusters = mdbscan(data, eps, minPts);

	// OUTPUT  
	plhs[0]= mxCreateDoubleMatrix(rows, cols + 1, mxREAL);
	double * out = mxGetPr( plhs[0] );
	// create output memory space

	mexPrintf("There are %d fixations in the analysis\n", clusters.size());


	long long prev_end = -1;
	for (size_t i = 0; i < clusters.size(); i++) {
		vector<long long> cls = clusters[i];

		prev_end = cls[1];

		// one cluseter is between data[cls[0]] and data[cls[1]] inclusively
		for (long long j = cls[0]; j <= cls[1]; j++)
			data[j]->CID = i + 1; // we need to + 1 because CID should be positive
	}

	for (size_t i = 0; i < rows; i++) {
		Point * p = data[i];

		//         out[i*cols + 0] = p->x;
		//         out[i*cols + 1] = p->y;
		//         out[i*cols + 2] = p->time;
		//         out[i*cols + 3] = p->CID;

		out[i] = p->x;
		out[ rows + i ] = p->y;
		out[rows * 2 + i] = p->time;
		out[rows * 3 + i] = p->CID;
	}






	// clean
	for(auto i:data) delete i;
}



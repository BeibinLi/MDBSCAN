%% Author: Beibin Li    March/21/2016
%% Instruction: The first time you run the MDBSCAN program, you should use 
% the matlab command "mex mdbscan_wrap.cpp", and then you will get a mexw32
% or mexw64 file, which is used as a Matlab function.
%
% Then, you can call MDBSCAN algorithm by using the function
% mdbscan_wrap(data, eps, minPts), where the data is a n by 3 matrix (first
% column is x, and second column is y, the last column is time).
%
% The function will return an output, which is a n by 4 matrix ( the last
% column is fixation ID, -1 if it's a saccade). 
function [data_increase, time] = example( filename )

if( nargin == 0 ),
    filename = '1.in';
end

% Read data and Remove Invalid Items
data = load( filename );
data = data( find(data(:,1) > 0), : );
data = data( find(data(:,2) > 0), : );

D_THRESHOLD = 27; % 27 pixels per degree, and we use 1 degree
minTime = 100;

mdbscan_result = mdbscan_wrap(data, D_THRESHOLD/2, 20 );
dlmwrite('mdbscan.out', mdbscan_result, 'delimiter','\t');


visualize_results('mdbscan.out')





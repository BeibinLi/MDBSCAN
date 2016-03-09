# Modified DBSCAN Algorithm on Oculomotor Fixation Identification


## Author
Beibin Li

For any information, please contact:
[Beibin Li](beibin.li@yale.edu).
You can also visit [my personal website](http://beibinli.com).

Co-authors: Quan Wang, Erin Barney, Logan Hart, Carla Wall, Katarzyna Chawarska,
Irati Saez de Urabain, Timothy J. Smith, Frederick Shic  

## Copyright
This algorithm is published in [ETRA 2016](http://etra.fxpal.com/2016/) ACMSIGGRAPH.

- Permission to make digital or hard copies of part or all of this work for personal or classroom use is granted without fee provided that copies are not made or distributed for profit or commercial advantage 
and that copies bear this notice and the full citation on the first page. 
Copyrights for third party components of this work must be honored. For all other uses, contact the owner/author(s). 
- 2016 Copyright held by the owner/author(s). 
- ETRA' 16, March 14-17, 2016, Charleston, SC, USA 
- ISBN: 978-1-4503-4125-7/16/03 
- DOI: http://dx.doi.org/10.1145/2857491.2888587

## Descriptions
The modified DBSCAN (MDBSCAN) algorithm is an oculomotor fixation identification algorithm.
It combines the advantages from both dispersion-based and velocity-based algorithms.

## Abstract
This paper modifies the DBSCAN algorithm to identify fixations and saccades. 
This method combines advantages from dispersion-based algorithms, such as  resilience 
to noise and intuitive fixational structure, and  from velocity-based algorithms, 
such as the ability to deal appropriately with smooth pursuit (SP) movements. 

## Usage
1. Required tools: g++ (at least version 4.8), make. Windows users can use Visual Studio to import these C++ files.
1. Use terminal command ```make all``` to compile the C++ code
2. Use terminal command ```make test1```, ```make test2```, or `make test3`to run sample inputs.
3. Use [this m file](visualize_results.m) to visualize fixations in the dataset. 
For instance, run ```visualize_results('1.out')``` in Matlab terminal to get visualization.

## Input format
The input files should be tab/space separated files.
It should have three columns. 
The first column is the x-axis reading, and the second column is the y-axis reading. The last column is teh time.

In the sample inputs, the x and y are in pixel unit, and time is in milisecond unit.

So, we use the threshold `26.7 * 0.5` pixels (0.5 degree) and `minPts = 20` in our [main.cpp](main.cpp) file.
You can change these two values based on your need.

The [main.cpp](main.cpp) file is just a demonstration how to use MDBSCAN algorithms.



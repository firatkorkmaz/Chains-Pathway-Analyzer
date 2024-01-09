# Chains: Pathway Analyzer
A program written in C++ to open an input text file and read its data about some location point pairs and the cost values of moving between them, in order to list all the possible pathways and feature the cheapest routes between a main point pair specified in the input file, which is the pair of starting point and destination point.

## General Information
Example of an input file content:
```
1 4
1 2 2
1 3 2
1 4 6
2 1 1
2 3 3
2 4 3
3 4 5
4 1 4
4 2 2
```
Here, there are 4 given points (1, 2, 3, 4) and 6 cost values for some binary points. The first line emphasizes that the starting point will be 1 and the destination point will be 4. The rest of the lines give the cost values for specific binary points: 
```
1 2 2  -->  From 1 to 2, the cost is 2.
1 3 2  -->  From 1 to 3, the cost is 2.
1 4 6  -->  From 1 to 4, the cost is 6.
2 1 1  -->  From 2 to 1, the cost is 1.
2 3 3  -->  From 2 to 3, the cost is 3.
2 4 3  -->  From 2 to 4, the cost is 3.
3 4 5  -->  From 3 to 4, the cost is 5.
4 1 4  -->  From 4 to 1, the cost is 4.
4 2 2  -->  From 4 to 2, the cost is 2.
```
By using this data, the program finds all the possible pathways from 1 to 4 for a round trip as requested in the first line of the file, and sorts this pathway list by costs in ascending order to feature the cheapest paths for the user. All the results are written in a new text file. This input example gives that output:
```
From 1 to 4, There are 4 Pathways:

[5]: 1-2-4
[6]: 1-4
[7]: 1-3-4
[10]: 1-2-3-4

The Shortest Pathways from 1 to 4:

[5]: 1-2-4

-------------------------

From 4 to 1, There are 2 Pathways:

[3]: 4-2-1
[4]: 4-1

The Shortest Pathways from 4 to 1:

[3]: 4-2-1

=========================

The Shortest Pathways from 1 to 1 Through 4:

[8] 1-2-4-2-1

```

There are 2 program files in this project, the first file can be considered as a preparation program before the main program, and the second file is the main program.

1. **1_Add_Pairs_to_Vector_of_Vectors.cpp**: Shows adding unique Pair type of data to vector of vectors in groups.
2. **2_Chains_Pathway_Analyzer.cpp**: The main program.

Along with the given input example in **test0.txt** file, there are also 7 additional input files given in this project with **test#.txt** filenames to test the program.

## Setup & Run
Compile the files with a C++ compiler and run the executable/output files:
```
g++ filename.cpp
```

# Stoer-Wagner Algorithm
An implementation of Stoer-Wagner Algorithm using Fibonacci-heap.  
We used an open-sourced [Fibonacci-heap implementation](https://github.com/robinmessage/fibonacci/blob/master/fibonacci.hpp).

## Language
C++11

## Compile
```
g++ -o main main.cpp -std=c++11 -O2
```

## Execute
```
./main < example/ps1_in.txt
```

## Input
The first line of the input file contains two integer numbers, where n is the number of vertices and m is the number of edges.  
The following m lines describe edges of the graph by using three integers ai, bi, wi. - the vertex numbers (<b>0-based</b>) connected by the edge and the weight of the edge.  

example
![ex1](https://raw.githubusercontent.com/cseteram/ct2018f/master/project/image/ex1.png)
```
8 12
0 1 2
0 4 3
1 2 3
1 4 2
1 5 2
2 3 4
2 6 2
3 6 2
3 7 2
4 5 3
5 6 1
6 7 3
```

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
The following m lines describe edges of the graph by using three integers ai, bi, wi - the vertex numbers (0-based) connected by the edge and the weight of the edge.

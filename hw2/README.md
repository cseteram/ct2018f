# Local Environment

## OS
CentOS Linux release 7.2.1511 (Core)

## Language
C++11

## Compile
```
g++ -o encoding encoding.cpp -Wall -std=c++11 -O2
g++ -o decoding decoding.cpp -Wall -std=c++11 -O2
```

## Execute
```
./encoding sample/infile.txt encoding.txt
./decoding encoding.txt outfile.txt
diff sample/infile.txt outfile.txt
```

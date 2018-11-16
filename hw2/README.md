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
./encoding sample/ta_in.txt ta_enc.txt
./decoding ta_enc.txt ta_out.txt
diff sample/ta_in.txt ta_out.txt
```

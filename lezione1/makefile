CXX = g++ -std=c++11
OPT = -O2 -g0 -Wall

all: es1 es2 es2b

es1: es1.cpp
	$(CXX) $(OPT) es1.cpp -o es1.exe

es2: es2.cpp
	$(CXX) $(OPT) es2.cpp -o es2.exe

es2b: es2b.cpp
	$(CXX) $(OPT) es2b.cpp -o es2b.exe

clean:
	rm -f es1.exe es2.exe es2b.exe


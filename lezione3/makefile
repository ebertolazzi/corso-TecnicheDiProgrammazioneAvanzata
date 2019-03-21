LIBPATH    = ../C++course-library
COURSE_LIB = $(LIBPATH)/course_lib.cpp
CXX        = g++ -std=c++11 -I$(LIBPATH)
OPT        = -O2 -g0 -Wall

all: es8 es9 es10

es8: es8_quicksort.cpp
	$(CXX) $(OPT) es8_quicksort.cpp $(COURSE_LIB) -o es8.exe

es9: es9_mergesort.cpp
	$(CXX) $(OPT) es9_mergesort.cpp $(COURSE_LIB) -o es9.exe

es10: es10_comparison.cpp
	$(CXX) $(OPT) es10_comparison.cpp $(COURSE_LIB) -o es10.exe

clean:
	rm -f es8.exe es9.exe es10.exe


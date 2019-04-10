LIBPATH    = ../C++course-library
COURSE_LIB = $(LIBPATH)/course_lib.cpp
CXX        = g++ -std=c++11 -I$(LIBPATH)
OPT        = -O2 -g0 -Wall

all: es35 es36 es37 es38

es35: es35_STL.cpp
	$(CXX) $(OPT) es35_STL.cpp $(COURSE_LIB) -o es35.exe

es36: es36_deque.cpp
	$(CXX) $(OPT) es36_deque.cpp $(COURSE_LIB) -o es36.exe

es37: es37_set.cpp
	$(CXX) $(OPT) es37_set.cpp $(COURSE_LIB) -o es37.exe

es38: es38_map.cpp
	$(CXX) $(OPT) es38_map.cpp $(COURSE_LIB) -o es38.exe

clean:
	rm -f es??.exe

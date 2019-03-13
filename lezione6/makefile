LIBPATH    = ../C++course-library
COURSE_LIB = $(LIBPATH)/course_lib.cpp
CXX        = g++ -std=c++11 -I$(LIBPATH)
OPT        = -O2 -g0 -Wall

all: es15

es15: es15_binary_search.cpp
	$(CXX) $(OPT) es15_binary_search.cpp $(COURSE_LIB) -o es15

clean:
	rm -f es15


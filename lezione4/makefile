LIBPATH    = ../C++course-library
COURSE_LIB = $(LIBPATH)/course_lib.cpp
CXX        = g++ -std=c++11 -I$(LIBPATH)
OPT        = -O2 -g0 -Wall

all: es11

es11: es11_string_sort.cpp
	$(CXX) $(OPT) es11_string_sort.cpp $(COURSE_LIB) -o es11

clean:
	rm -f es11


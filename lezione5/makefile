LIBPATH    = ../C++course-library
COURSE_LIB = $(LIBPATH)/course_lib.cpp
CXX        = g++ -std=c++11 -I$(LIBPATH)
OPT        = -O2 -g0 -Wall

all: es12 es13 es14

es12: es12_heap_sort.cpp
	$(CXX) $(OPT) es12_heap_sort.cpp $(COURSE_LIB) -o es12

es13: es13_plot_heap.cpp
	$(CXX) $(OPT) es13_plot_heap.cpp $(COURSE_LIB) -o es13

es14: es14_struct.cpp
	$(CXX) $(OPT) es14_struct.cpp $(COURSE_LIB) -o es14

clean:
	rm -f es12 es13 es14


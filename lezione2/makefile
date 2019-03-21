LIBPATH    = ../C++course-library
COURSE_LIB = $(LIBPATH)/course_lib.cpp
CXX        = g++ -std=c++11 -I$(LIBPATH)
OPT        = -O2 -g0 -Wall

all: es1 es2 es3 es4 es5

es1: es1_bubble_sort.cpp
	$(CXX) $(OPT) es1_bubble_sort.cpp $(COURSE_LIB) -o es1.exe

es2: es2_insert_sort.cpp
	$(CXX) $(OPT) es2_insert_sort.cpp $(COURSE_LIB) -o es2.exe

es3: es3_selection_sort.cpp
	$(CXX) $(OPT) es3_selection_sort.cpp $(COURSE_LIB) -o es3.exe

es4: es4_shell_sort.cpp
	$(CXX) $(OPT) es4_shell_sort.cpp $(COURSE_LIB) -o es4.exe

es5: es5_comparison.cpp
	$(CXX) $(OPT) es5_comparison.cpp $(COURSE_LIB) -o es5.exe

clean:
	rm -f es1.exe es2.exe es3.exe es4.exe es5.exe


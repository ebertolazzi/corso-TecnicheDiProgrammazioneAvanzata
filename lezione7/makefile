LIBPATH    = ../C++course-library
COURSE_LIB = $(LIBPATH)/course_lib.cpp
CXX        = g++ -std=c++11 -I$(LIBPATH)
OPT        = -O2 -g0 -Wall

all: es16 es17 es18 es19 es20

es16: es16_dynamic_allocation_c.cpp
	$(CXX) $(OPT) es16_dynamic_allocation_c.cpp $(COURSE_LIB) -o es16.exe

es17: es17_dynamic_allocation_cpp.cpp
	$(CXX) $(OPT) es17_dynamic_allocation_cpp.cpp $(COURSE_LIB) -o es17.exe

es18: es18_memory_leak.cpp
	$(CXX) $(OPT) es18_memory_leak.cpp $(COURSE_LIB) -o es18.exe

es19: es19_mergesort_leak.cpp
	$(CXX) $(OPT) es19_mergesort_leak.cpp $(COURSE_LIB) -o es19.exe

es20: es20_mergesort_vector.cpp
	$(CXX) $(OPT) es20_mergesort_vector.cpp $(COURSE_LIB) -o es20.exe

clean:
	rm -f es16.exe es17.exe es18.exe es19.exe es20.exe


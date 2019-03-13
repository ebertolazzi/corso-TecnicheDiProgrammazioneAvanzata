LIBPATH    = ../C++course-library
COURSE_LIB = $(LIBPATH)/course_lib.cpp
CXX        = g++ -std=c++11 -I$(LIBPATH)
OPT        = -O2 -g0 -Wall

all: es21

es21: es21_eratostene.cpp
	$(CXX) $(OPT) es21_eratostene.cpp $(COURSE_LIB) -o es21

clean:
	rm -f es21


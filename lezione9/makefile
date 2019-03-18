LIBPATH    = ../C++course-library
COURSE_LIB = $(LIBPATH)/course_lib.cpp
CXX        = g++ -std=c++11 -I$(LIBPATH)
OPT        = -O2 -g0 -Wall

all: es22 es23 es24 es25

es22: es22_hanoi.cpp
	$(CXX) $(OPT) es22_hanoi.cpp $(COURSE_LIB) -o es22

es23: es23_hanoi2.cpp
	$(CXX) $(OPT) es23_hanoi2.cpp $(COURSE_LIB) -o es23

es24: es24_stringhe.cpp
	$(CXX) $(OPT) es24_stringhe.cpp $(COURSE_LIB) -o es24

es25: es25_fake_ackermann.cpp
	$(CXX) $(OPT) es25_fake_ackermann.cpp $(COURSE_LIB) -o es25

clean:
	rm -f es22 es23 es24 es25

LIBPATH    = ../C++course-library
COURSE_LIB = $(LIBPATH)/course_lib.cpp
CXX        = g++ -std=c++11 -I$(LIBPATH)
OPT        = -O2 -g0 -Wall

all: es26 es27 es28 es29 es30

es26: es26_quicksort.cpp
	$(CXX) $(OPT) es26_quicksort.cpp $(COURSE_LIB) -o es26

es27: es27_quicksort2.cpp
	$(CXX) $(OPT) es27_quicksort2.cpp $(COURSE_LIB) -o es27

es28: es28_quicksort3.cpp
	$(CXX) $(OPT) es28_quicksort3.cpp $(COURSE_LIB) -o es28

es29: es29_hanoi_move.cpp hanoi_lib.cpp hanoi_lib.h
	$(CXX) $(OPT) es29_hanoi_move.cpp hanoi_lib.cpp -o es29

es30: es30_hanoi_move2.cpp hanoi_lib2.cpp hanoi_lib2.h
	$(CXX) $(OPT) es30_hanoi_move2.cpp hanoi_lib2.cpp -o es30

es31: es31_hanoi_move3.cpp hanoi_lib3.cpp hanoi_lib3.h
	$(CXX) $(OPT) es31_hanoi_move3.cpp hanoi_lib3.cpp -o es31

es32: es32_hanoi_move4.cpp hanoi_lib4.cpp hanoi_lib4.h
	$(CXX) $(OPT) es32_hanoi_move4.cpp hanoi_lib4.cpp -o es32

es33: es33_hanoi_move5.cpp hanoi_lib5.cpp hanoi_lib5.h
	$(CXX) $(OPT) es33_hanoi_move5.cpp hanoi_lib5.cpp -o es33

clean:
	rm -f es26 es27 es28 es29 es30 es31 es32 es33

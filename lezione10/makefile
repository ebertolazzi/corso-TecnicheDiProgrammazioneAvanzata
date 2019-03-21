LIBPATH    = ../C++course-library
COURSE_LIB = $(LIBPATH)/course_lib.cpp
CXX        = g++ -std=c++11 -I$(LIBPATH)
OPT        = -O2 -g0 -Wall

all: es26 es27 es28 es29 es30

es26: es26_hanoi_move1.cpp hanoi_lib1.cpp hanoi_lib1.h
	$(CXX) $(OPT) es26_hanoi_move1.cpp hanoi_lib1.cpp -o es26.exe

es27: es27_hanoi_move2.cpp hanoi_lib2.cpp hanoi_lib2.h
	$(CXX) $(OPT) es27_hanoi_move2.cpp hanoi_lib2.cpp -o es27.exe

es28: es28_hanoi_move3.cpp hanoi_lib3.cpp hanoi_lib3.h
	$(CXX) $(OPT) es28_hanoi_move3.cpp hanoi_lib3.cpp -o es28.exe

es29: es29_hanoi_move4.cpp hanoi_lib4.cpp hanoi_lib4.h
	$(CXX) $(OPT) es29_hanoi_move4.cpp hanoi_lib4.cpp -o es29.exe

es30: es30_hanoi_move5.cpp hanoi_lib5.cpp hanoi_lib5.h
	$(CXX) $(OPT) es30_hanoi_move5.cpp hanoi_lib5.cpp -o es30.exe

clean:
	rm -f es??.exe

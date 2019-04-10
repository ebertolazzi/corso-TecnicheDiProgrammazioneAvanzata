LIBPATH    = ../C++course-library
COURSE_LIB = $(LIBPATH)/course_lib.cpp
CXX        = g++ -std=c++11 -I$(LIBPATH)
OPT        = -O2 -g0 -Wall

all: es31 es32 es33 es34

es31: es31_string1.cpp
	$(CXX) $(OPT) es31_string1.cpp $(COURSE_LIB) -o es31.exe

es32: es32_string2.cpp
	$(CXX) $(OPT) es32_string2.cpp $(COURSE_LIB) -o es32.exe

es33: es33_string3.cpp
	$(CXX) $(OPT) es33_string3.cpp $(COURSE_LIB) -o es33.exe

es34: es34_string4.cpp
	$(CXX) $(OPT) es34_string4.cpp $(COURSE_LIB) -o es34.exe

clean:
	rm -f es??.exe

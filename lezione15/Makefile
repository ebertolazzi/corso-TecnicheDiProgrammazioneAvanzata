# get the type of OS currently running
# comandi di gnumake
# lancio shell e comando uname
OS=$(shell uname -s)
PWD=$(shell pwd)

# variabili inizializzate (strighe senza " ")
# per accedere al contenuto $(NOME DELLA VARIABILE)
INC  = -I../C++course-library -I/usr/local/include/eigen3
LIBS =
DEFS =
WARN =

# default values

# check if the OS string contains 'Linux'
ifneq (,$(findstring Linux, $(OS)))
  CXX      = g++
  CC       = gcc
  CXXFLAGS = -std=c++11 $(WARN) -O3 -fPIC
endif

# check if the OS string contains 'MINGW'
ifneq (,$(findstring MINGW, $(OS)))
  CXX      = g++
  CC       = gcc
  CXXFLAGS = -std=c++11 $(WARN) -O3
endif

# check if the OS string contains 'Darwin'
ifneq (,$(findstring Darwin, $(OS)))
  WARN     = -Wall -Wno-sign-compare -Wno-global-constructors -Wno-padded -Wno-documentation-unknown-command 
  CXX      = clang++
  CC       = clang
  #CXX      = g++-8
  #CC       = gcc-8
  CXXFLAGS = $(WARN) $(INC) -O3 -fPIC
  LIBS     = -framework Accelerate
endif

SRCS  =
OBJS  = $(SRCS:.cc=.o)
DEPS  =
MKDIR = mkdir -p

#
# RULE: sintassi
#
# nome_della_regola: dipendenze
# <tab> comandi da eseguire se le dipendenze "non sono rispettate"
all: es44 es45 es46 es47

es44: es44_eigen3.o
	$(CXX) $(INC) $(CXXFLAGS) es44_eigen3.o -o es44.exe $(LIBS)

es45: es45_eigen3.o
	$(CXX) $(INC) $(CXXFLAGS) es45_eigen3.o -o es45.exe $(LIBS)

es46: es46_eigen3.o
	$(CXX) $(INC) $(CXXFLAGS) es46_eigen3.o -o es46.exe $(LIBS)

es47: es47_eigen3_strassen.o
	$(CXX) $(INC) $(CXXFLAGS) es47_eigen3_strassen.o -o es47.exe $(LIBS)

#
# REGOLA CON PATTERN
#
# %.qualcosa: %.quacosaltro DIPENDENZE
# <tab> comandi
#
# % fa "match" con file nella diretory "match".qualcosaltro
# e genera il file "match".qualcosa
# $< = espansione del "match" %.cc
# $@ = espansione del "match" %.o

%.o: %.cc $(DEPS)
	$(CXX) $(INC) $(CXXFLAGS) $(DEFS) -c $< -o $@

%.o: %.c $(DEPS)
	$(CC) $(INC) $(CFLAGS) $(DEFS) -c  $< -o $@

run:
	./es44.exe

clean:
	rm -f es??.exe *.o

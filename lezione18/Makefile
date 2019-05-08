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
all: es55 es56

es55: es55_load_dictionary.o
	$(CXX) $(INC) $(CXXFLAGS) es55_load_dictionary.o -o es55.exe $(LIBS)

es56: es56_sodoku.o
	$(CXX) $(INC) $(CXXFLAGS) es56_sodoku.o -o es56.exe $(LIBS)

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
	./es51.exe

clean:
	rm -f es??.exe *.o

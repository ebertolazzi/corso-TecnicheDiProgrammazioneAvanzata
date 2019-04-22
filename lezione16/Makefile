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
all: es48 es49 es50 es51

es48: es48_fibonacci.o
	$(CXX) $(INC) $(CXXFLAGS) es48_fibonacci.o -o es48.exe $(LIBS)

es49: es49_fibonacci2.o
	$(CXX) $(INC) $(CXXFLAGS) es49_fibonacci2.o -o es49.exe $(LIBS)

es50: es50_fibonacci3.o
	$(CXX) $(INC) $(CXXFLAGS) es50_fibonacci3.o -o es50.exe $(LIBS)

es51: es51_power.o
	$(CXX) $(INC) $(CXXFLAGS) es51_power.o -o es51.exe $(LIBS)

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

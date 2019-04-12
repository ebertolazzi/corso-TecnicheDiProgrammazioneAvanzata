# get the type of OS currently running
# comandi di gnumake
# lancio shell e comando uname
OS=$(shell uname -s)
PWD=$(shell pwd)

# variabili inizializzate (strighe senza " ")
# per accedere al contenuto $(NOME DELLA VARIABILE)
INC  = -I../C++course-library
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
  WARN     = -Wall -Weverything -Wno-sign-compare -Wno-global-constructors -Wno-padded -Wno-documentation-unknown-command 
  CXX      = clang++
  CC       = clang
  CXXFLAGS = $(WARN) $(INC) -O3 -fPIC
endif

SRCS  =
OBJS  = $(SRCS:.cc=.o)
DEPS  = src/Clothoid.hh src/CubicRootsFlocke.hh
MKDIR = mkdir -p

#
# RULE: sintassi
#
# nome_della_regola: dipendenze
# <tab> comandi da eseguire se le dipendenze "non sono rispettate"
all: es42

es42: es42_mm.o
	$(CXX) $(INC) $(CXXFLAGS) es42_mm.o -o es42.exe $(LIBS)

lib: lib/$(LIB_CLOTHOID)$(STATIC_EXT) lib/$(LIB_CLOTHOID)$(DYNAMIC_EXT)

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
	./es42.exe

clean:
	rm -f es??.exe *.o

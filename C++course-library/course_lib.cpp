/*\
:|:
:|: Questo file contiene le funzioni e i programmi
:|: di utilita' usati nel corso
:|:
:|: Tecniche di programmazione avanzata [145480]
:|: AA 2018/2019
:|:
:|: corso tenuto da
:|: prof. Enrico Bertolazzi
:|:
:|: ATTENZIONE per compilare questo file serve
:|: attivare C++11
:|:
:|: clang++ -std=c++-11 -stdlib=libc++ ....
:|: g++     -std=c++-11 -stdlib=libc++ ....
:|:
\*/

#include "course_lib.h"

#ifdef OS_WINDOWS
HANDLE TermColor::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#else
std::ostream * TermColor::pStream = &std::cout;
#endif

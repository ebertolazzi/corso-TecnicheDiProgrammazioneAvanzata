/*\
:|:
:|: Questo heder contiene le funzioni e i programmi
:|: di utilita' usati nel corso
:|:
:|: Tecniche di programmazione avanzata [145480]
:|: AA 2018/2019
:|:
:|: corso tenuto da
:|: prof. Enrico Bertolazzi
:|:
:|: ATTENZIONE per compilare questo header serve
:|: attivare C++11
:|:
:|: clang++ -std=c++-11 -stdlib=libc++ ....
:|: g++     -std=c++-11 -stdlib=libc++ ....
:|:
\*/

// queste due istruzioni del preprocessore
// servono per evitare la "doppia inclusione"
// del file e quindi possibili errori
#ifndef COURSE_LIB_HPP
#define COURSE_LIB_HPP

#ifdef __clang__
#pragma clang diagnostic ignored "-Wc++11-extensions"
#endif

// determina se sono su sistema operativo WINDOWS
#if defined(_WIN32) || defined(_WIN64) || defined(WIN32) || defined(WIN64)
  #define OS_WINDOWS
#endif

// inclusione header C++11 per l'uso della classe
// chrono usata per misuare i tempi di esecuzione

#include <iostream>
#include <iomanip>

#include <algorithm>

#include <chrono>
#include <ctime>
#include <thread> // for sleep

/*\

 Classe usata per misurare il tempo;

 TicToc tm;

 tm.tic(); // inizio a misurare il tempo


 tm.toc(); // prende misura del tempo

 cout << "Tempo trascorso in secondi = " << tm.elapsed_s() << '\n';
 cout << "Tempo trascorso in millisecondi = " << tm.elapsed_s() << '\n';

\*/

#ifdef OS_WINDOWS

/*
  La classe std::chrono::high_resolution_clock ha una bassa risoluzione
  su windows (meno di 1 millisecondo).
  Meglio usare chiamate di sistema specifiche di WINDOWS.
*/

#include <windows.h>

class TicToc {

  typedef double real_type;
  LARGE_INTEGER frequency;        // ticks per second
  LARGE_INTEGER t1, t2;           // ticks
  real_type elapsed_time;

  TicToc( TicToc const & );
  TicToc const & operator = ( TicToc const & ) const;

public:

  TicToc()
  : elapsed_time(0)
  { QueryPerformanceFrequency(&frequency); tic(); }

  ~TicToc() {}

  void
  tic()
  { QueryPerformanceCounter(&t1); }

  void
  toc() {
    QueryPerformanceCounter(&t2);
    elapsed_time = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;;
  }

  real_type
  elapsed_s() const
  { return 1e-3*elapsed_time; }

  real_type
  elapsed_ms() const
  { return elapsed_time; }
};

#else

class TicToc {

  typedef double real_type;
  //typedef std::chrono::steady_clock clock;
  typedef std::chrono::high_resolution_clock clock;
  using elapsed_resolution = std::chrono::microseconds;

  clock::time_point start_time;
  clock::time_point stop_time;

  elapsed_resolution elapsed_time;

  TicToc( TicToc const & );
  TicToc const & operator = ( TicToc const & ) const;

public:

  TicToc()
  : elapsed_time(0)
  { tic(); }

  ~TicToc() {}

  void
  tic()
  { start_time = clock::now(); }

  void
  toc() {
    stop_time    = clock::now();
    elapsed_time = std::chrono::duration_cast<elapsed_resolution>(stop_time - start_time);
  }

  real_type
  elapsed_s() const
  { return 1e-6*elapsed_time.count(); }

  real_type
  elapsed_ms() const
  { return 1e-3*elapsed_time.count(); }

  void
  sleep_for_seconds( unsigned s )
  { std::this_thread::sleep_for(std::chrono::seconds(s)); }

  void
  sleep_for_milliseconds( unsigned ms )
  { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

};
#endif

#include <random>

class Random {

  typedef double real_type;

  std::random_device rd;  // Will be used to obtain a seed for the random number engine
  std::mt19937       gen; // Standard mersenne_twister_engine seeded with rd()
public:
  Random()
  //: gen(rd())
  : gen(1)
  {}

  real_type
  dice( real_type a, real_type b ) {
    std::uniform_real_distribution<double> dis(a,b);
    return dis(gen);
  }
};

template <typename T>
class AutoAllocate {

  AutoAllocate( AutoAllocate const & );
  AutoAllocate const & operator = ( AutoAllocate const & ) const;

  T * ptr;

public:

  AutoAllocate( int size, T ** out_ptr )
  { *out_ptr = ptr = new T[size]; }

  ~AutoAllocate()
  { delete [] ptr; }

};

/*\
:|:   _____                    ____      _
:|:  |_   _|__ _ __ _ __ ___  / ___|___ | | ___  _ __
:|:    | |/ _ \ '__| '_ ` _ \| |   / _ \| |/ _ \| '__|
:|:    | |  __/ |  | | | | | | |__| (_) | | (_) | |
:|:    |_|\___|_|  |_| |_| |_|\____\___/|_|\___/|_|
\*/

/**
 * @file mycolorsdef.h
 * Header definitionens of different colors in a Terminal.
 *
 * @author A. Huber
 * Fakultät für Luft- und Raumfahrttechnik
 * Universität der Bundeswehr München
 * email: a.huber@unibw.de
 *
 * @since 07.03.2017
\*/

class TermColor {

  #ifdef OS_WINDOWS
  static HANDLE hConsole;
  #else
  static std::ostream * pStream;
  #endif

public:

  #ifdef OS_WINDOWS

  /// Default color of the Terminal.
  static
  void
  set_COLOR_DEFAULT()
  { SetConsoleTextAttribute( hConsole, WORD(15) ); }

  /// Red color in the Terminal.
  static
  void
  set_COLOR_RED()
  { SetConsoleTextAttribute( hConsole, WORD(12) ); }

  /// Green color in the Terminal.
  static
  void
  set_COLOR_GREEN()
  { SetConsoleTextAttribute( hConsole, WORD(10) ); }

  /// Yellow color in the Terminal.
  static
  void
  set_COLOR_YELLOW()
  { SetConsoleTextAttribute( hConsole, WORD(14) ); }

  /// Darkblue color in the Terminal.
  static
  void
  set_COLOR_DARK_BLUE()
  { SetConsoleTextAttribute( hConsole, WORD(9) ); }

  /// Purple color in the Terminal.
  static
  void
  set_COLOR_PURPLE()
  { SetConsoleTextAttribute(hConsole, WORD(13)); }

  /// Lightblue color in the Terminal.
  static
  void
  set_COLOR_LIGHT_BLUE()
  { SetConsoleTextAttribute(hConsole, WORD(11)); }

  #else

  /// Default color of the Terminal.
  static
  void
  set_COLOR_DEFAULT()
  { (*pStream) << "\033[0m"; }

  /// Red color in the Terminal.
  static
  void
  set_COLOR_RED()
  { (*pStream) << "\033[1;31m"; }

  /// Green color in the Terminal.
  static
  void
  set_COLOR_GREEN()
  { (*pStream) << "\033[1;32m"; }

  /// Yellow color in the Terminal.
  static
  void
  set_COLOR_YELLOW()
  { (*pStream) << "\033[1;33m"; }

  /// Darkblue color in the Terminal.
  static
  void
  set_COLOR_DARK_BLUE()
  { (*pStream) << "\033[1;34m"; }

  /// Purple color in the Terminal.
  static
  void
  set_COLOR_PURPLE()
  { (*pStream) << "\033[1;35m"; }

  /// Lightblue color in the Terminal.
  static
  void
  set_COLOR_LIGHT_BLUE()
  { (*pStream) << "\033[1;36m"; }

  #endif
};

/*\
:|:  ____             _   _
:|: / ___|  ___  _ __| |_(_)_ __   __ _
:|: \___ \ / _ \| '__| __| | '_ \ / _` |
:|:  ___) | (_) | |  | |_| | | | | (_| |
:|: |____/ \___/|_|   \__|_|_| |_|\__, |
:|:                               |___/
\*/

/*\
  funzione confronto di default.
  Puo essere cambiata specializzando il template

  template <>
  bool
  compare_gt( TIPO const & a, TIPO const & b ) {
    ...
  }

  dove TIPO è un tipo usato nella specializzazione.
  Ad esempio se TIPO è `char const *` cioè un puntatore
  a carattere (il carattere non è modificabile)
  e questo rappresenta una stringa allora per
  confrontare le stringhe si può usare:

  template <>
  bool
  compare_gt( char const * const & a, char const * const & b ) {
    return strcmp( a, b ) > 0;
  }

  il tipo `char const * const` è un puntatore costante (cioè
  non si può cambiare dove punta) a dei caratteri costanti
  (cioè non modificabuli). Questo puntatore è passato
  per riferimento (tramite &), cioè passiamo l'indirizzo
  della variabile che contiene il puntatore.
\*/
template <typename T>
bool
compare_gt( T const & a, T const & b ) {
  return a < b;
}

template <typename T>
bool
check_if_sorted( T const a[], int n ) {
  bool ok = true;
  for ( int i = 1; i < n && ok; ++i ) {
    ok = compare_gt<T>(a[i-1],a[i]);
    if ( !ok ) {
      TermColor::set_COLOR_RED();
      std::cout
        << "Fallito il confronto tra:\n"
        << "a[" << i-1 << "] = " << a[i-1] << '\n'
        << "a[" << i << "] = " << a[i] << '\n';
      TermColor::set_COLOR_DEFAULT();
    }
  }
  return ok;
}

/*
||  ___      _    _    _     ___          _
|| | _ )_  _| |__| |__| |___/ __| ___ _ _| |_
|| | _ \ || | '_ \ '_ \ / -_)__ \/ _ \ '_|  _|
|| |___/\_,_|_.__/_.__/_\___|___/\___/_|  \__|
*/

template <typename T>
void
bubble_sort( T a[], int n ) {
  for ( int i = 0; i < n-1; ++i )
    for ( int j = i+1; j < n; ++j )
      if ( !compare_gt<T>(a[i],a[j]) ) // elementi non ordinati --> scambia gli elementi
        std::swap( a[i], a[j] );
}

/*
||  ___                  _   ___          _
|| |_ _|_ _  ___ ___ _ _| |_/ __| ___ _ _| |_
||  | || ' \(_-</ -_) '_|  _\__ \/ _ \ '_|  _|
|| |___|_||_/__/\___|_|  \__|___/\___/_|  \__|
*/
/*\
:|: Ordina il vettore usanfo l'algoritmo
:|: di inserzione.
:|: costruisce i vettori si lunghezza 1,2,..,n
:|: ordinati inserendo un elemento alla volta
:|: nei vettori gia ordinati.
\*/
template <typename T>
void
insert_sort( T a[], int N ) {
  for ( int n = 1; n < N; ++n ) {
    // a[0], a[1], ..., a[n-1] sono ordinati
    // inserisce a[n] nella posizione corretta.
    int i = n;
    for ( --i; i >= 0; --i ) {
      // continua a inserire se non soddisfa l'ordinamento
      if ( compare_gt<T>(a[i],a[i+1]) ) break;
      std::swap( a[i], a[i+1] );
    }
  }
}

/*
||  ___      _        _   _          ___          _
|| / __| ___| |___ __| |_(_)___ _ _ / __| ___ _ _| |_
|| \__ \/ -_) / -_) _|  _| / _ \ ' \\__ \/ _ \ '_|  _|
|| |___/\___|_\___\__|\__|_\___/_||_|___/\___/_|  \__|
*/
/*\
:|: Ordina il vettore a di n elementi per selezione.
:|: Si cerca il massimo di un vettore di n-elementi
:|: e si mette in coda.
:|: Poi di cerca il massimo di un vettore di (n-1)-elementi
:|: e si mette in coda e cosi via fino ad arrivare
:|: ad un vettore di 2 elementi.
\*/
template <typename T>
void
selection_sort( T a[], int N ) {
  int n = N;
  while ( --n > 0 ) {
    // Cerca l'elemento massimo in un vettore di n elementi.
    int ipos = 0;
    for ( int i = 1; i <= n; ++i )
      if ( !compare_gt<T>(a[i],a[ipos]) )
        ipos = i;
    if ( ipos < n ) std::swap( a[ipos], a[n] );
  }
}

/*
||  ___ _        _ _ ___          _
|| / __| |_  ___| | / __| ___ _ _| |_
|| \__ \ ' \/ -_) | \__ \/ _ \ '_|  _|
|| |___/_||_\___|_|_|___/\___/_|  \__|
*/

template <typename T>
void
shell_insert_sort( T a[], int N, int step ) {
  for ( int n = step; n < N; n += step ) {
    // a[0], a[step], ..., a[k*step] sono ordinati
    // inserisce a[n] nella posizione corretta.
    int i = n-step;
    while ( i >= 0 ) {
      if ( !compare_gt<T>(a[i],a[i+step]) ) break;
      std::swap( a[i], a[i+step] );
      i -= step;
    }
  }
}

template <typename T>
void
shell_sort( T a[], int n ) {
  int step = n>>3;
  while ( step > 0 ) {
    for ( int k = 0; k < step; ++k )
      shell_insert_sort( a+k, n-k, step );
    step = (step>>2)-1;
  }
  insert_sort( a, n );
}

/*
||   ___       _    _    ___          _
||  / _ \ _  _(_)__| |__/ __| ___ _ _| |_
|| | (_) | || | / _| / /\__ \/ _ \ '_|  _|
||  \__\_\\_,_|_\__|_\_\|___/\___/_|  \__|
*/

template <typename T>
int
partition( T a[], int ilow, int ihigh ) {
  int ipivot = ilow;
  T   pivot  = a[ilow]; // salva pivot in posizione ilow
  int i      = ilow;
  while ( ++i <= ihigh ) {
    if ( a[i] < pivot ) {
      // aggiunge a[i] alla lista elementi < pivot
      ++ipivot;
      std::swap( a[i], a[ipivot] );
      // gli elementi a[ilow+1..ipivot] < pivot
    }
  }
  // scambia a[ilow] <=> a[ipivot]
  // std::swap( a[ilow], a[ipivot] );
  a[ilow]   = a[ipivot];
  a[ipivot] = pivot;
  return ipivot;
}

template <typename T>
void
qsort( T a[], int ilow, int ihigh ) {
  if ( ilow < ihigh ) {
    int ipivot = partition( a, ilow, ihigh );
    qsort( a, ilow, ipivot-1 );
    qsort( a, ipivot+1, ihigh );
  }
}

/*
||  __  __                  ___          _
|| |  \/  |___ _ _ __ _ ___/ __| ___ _ _| |_
|| | |\/| / -_) '_/ _` / -_)__ \/ _ \ '_|  _|
|| |_|  |_\___|_| \__, \___|___/\___/_|  \__|
||                |___/
*/

template <typename T>
void
merge( T a1[], int n1, T a2[], int n2, T out[] ) {
  int i1 = 0;
  int i2 = 0;
  int i  = 0;
  while( i1 < n1 && i2 < n2 ) {
    if ( a1[i1] < a2[i2] ) { out[i] = a1[i1]; ++i1; }
    else                   { out[i] = a2[i2]; ++i2; }
    ++i;
  }
  while ( i1 < n1 ) out[i++] = a1[i1++];
  while ( i2 < n2 ) out[i++] = a2[i2++];
}

template <typename T>
void
mergesort( T a[], int n ) {
  /* Base case: 0- or 1-element lists are already sorted. */
  if ( n <= 1 ) return;

  /* Split v into two subvectors. */
  T *left, *right;
  int n2 = n>>1; // n/2
  AutoAllocate<T> memleft(n2, &left);
  AutoAllocate<T> memright(n - n2, &right);
  for ( int i = 0; i < n2;   ++i ) left[i]  = a[i];
  for ( int i = 0; i < n-n2; ++i ) right[i] = a[n2+i];

  /* Recursively sort these arrays. */
  mergesort( left, n2 );
  mergesort( right, n-n2 );

  /* Combine them together. */
  merge( left, n2, right, n-n2, a);
}

#endif

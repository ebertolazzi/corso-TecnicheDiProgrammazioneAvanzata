/*\
:|:
:|: Tecniche di programmazione avanzata [145480]
:|: AA 2018/2019
:|:
:|: corso tenuto da
:|: prof. Enrico Bertolazzi e prof. Andrea Del Prete
:|:
:|:
\*/

#include <string>
#include <cstdint>

using namespace std;

typedef int64_t int_type;

// the first 20 number

string num0to19[] = {
  "",
  "uno",
  "due",
  "tre",
  "quattro",
  "cinque",
  "sei",
  "sette",
  "otto",
  "nove",
  "dieci",
  "undici",
  "dodici",
  "tredici",
  "quattordici",
  "quindici",
  "sedici",
  "diciassette",
  "diciotto",
  "diciannove"
} ;

string decine[] = {
  "",
  "dieci",
  "venti",
  "trenta",
  "quaranta",
  "cinquanta",
  "sessanta",
  "settanta",
  "ottanta",
  "novanta"
} ;

// convert number from 0 to 999
string
num3digitToString( int_type num ) {
  int_type n = num % 1000;
  if ( n < 20 ) return num0to19[n];
  int_type c = n/100;
  int_type d = (n/10) % 10;
  int_type u = n % 10;
  string res = "";
  if ( c == 0 ) {
  } else if ( c == 1 ) {
    res = "cento";
  } else {
    res = num0to19[c] + "cento";
  }
  if ( d == 0 ) {
    res += num0to19[u];
  } else if ( d == 1 ) {
    res += num0to19[10+u];
  } else {
    string dec = decine[d];
    if ( u == 1 || u == 8 ) dec.pop_back();
    res += dec + num0to19[u];
  }
  return res;
}

// convert number from 0 to 999
string
num6digitToString( int_type num ) {
  int_type m = (num/1000)%1000;
  if ( m == 0 ) return num3digitToString(num);
  if ( m == 1 ) return "mille"+num3digitToString(num);
  return num3digitToString(m)+"mila"+num3digitToString(num);
}

// convert number from 0 to 999
string
num9digitToString( int_type num ) {
  int_type m = (num/1000000L)%1000;
  string num6 = num6digitToString(num);
  if ( m == 0 ) return num6;
  if ( num6.length() ) num6 = " e " + num6;
  if ( m == 1 ) return "un milione"+num6;
  return num3digitToString(m)+" milioni"+num6;
}

// convert number from 0 to 999
string
num12digitToString( int_type num ) {
  int_type m = (num/1000000000L)%1000;
  string num9 = num9digitToString(num);
  if ( m == 0 ) return num9;
  if ( num9.length() ) num9 = " e " + num9;
  if ( m == 1 ) return "un miliardo"+num9;
  return num3digitToString(m)+" miliardi"+num9;
}

// convert number from 0 to 999
string
num15digitToString( int_type num ) {
  int_type m = (num/1000000000000L)%1000;
  string num12 = num12digitToString(num);
  if ( m == 0 ) return num12;
  if ( num12.length() ) num12 = " e " + num12;
  if ( m == 1 ) return "un bilione"+num12;
  return num3digitToString(m)+" bilioni"+num12;
}


void
numeri_lettere( int64_t N, string & res ) {
  res = num15digitToString( N );
  if ( res.length() == 0 ) res = "zero";
}

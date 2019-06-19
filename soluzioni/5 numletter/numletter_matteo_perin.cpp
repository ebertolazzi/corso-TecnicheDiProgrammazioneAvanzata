#include<map>
#include <iostream>
#include<string>
#include "course_lib.h"
#include<cstdint> //libreria per il workaround c++ 11

using namespace std;


void Sub_sequenza(std::string & stringa,int64_t n){

  int r;

  map<int64_t, std::string> num;
  num[0]="zero";
  num[1]="uno";
  num[2]="due";
  num[3]="tre";
  num[4]="quattro";
  num[5]="cinque";
  num[6]="sei";
  num[7]="sette";
  num[8]="otto";
  num[9]="nove";
  num[10]="dieci";
  num[11]="undici";
  num[12]="dodici";
  num[13]="tredici";
  num[14]="quattordici";
  num[15]="quindici";
  num[16]="sedici";
  num[17]="diciassette";
  num[18]="diciotto";
  num[19]="diciannove";
  num[20]="venti";
  num[21]="ventuno";
  num[28]="ventotto";
  num[30]="trenta";
  num[31]="trentuno";
  num[38]="trentotto";
  num[40]="quaranta";
  num[41]="quarantuno";
  num[48]="quarantotto";
  num[50]="cinquanta";
  num[51]="cinquantuno";
  num[58]="cinquantotto";
  num[60]="sessanta";
  num[61]="sessantuno";
  num[68]="sessantotto";
  num[70]="settanta";
  num[71]="settantuno";
  num[78]="settantotto";
  num[80]="ottanta";
  num[81]="ottantuno";
  num[88]="ottantotto";
  num[90]="novanta";
  num[91]="novantuno";
  num[98]="novantotto";
  num[100]="cento";



//cout<<n<<"\n";
if(n/100!=0){
    if(n/100==1) {
      stringa=stringa + (num[100]);
      n=n-100;
      }
    else {
      stringa=stringa + (num[n/100]);
      stringa=stringa +(num[100]);
      cout<<stringa<<"\n";
      n=n-((n/100)*100);
      }
  }
cout<<r<<"\n";
cout<<"\n";

  if(n==0){}
  else{
   if(n<=21 || n%10==1 || n%10==8 || n%10==0) { stringa += (num[n]);}
    else {
    int j=(n/10)*10;
    int h=(n-j);
  cout<< num[6] <<"\n";
  cout<<"\n";
  cout<< num[r-j] <<"\n";
    stringa=stringa + (num[j]);
    stringa=stringa + (num[h]);

     //cout<<stringa<<"\n";
   }
  }
}

void numeri_lettere(int64_t N, string & res){

  map<int64_t,std::string> special;

  special[1000]="mille"; //caratteri che in num hanno significato particolare
  special[1000000]="un milione ";
  special[1000000000]="un miliardo ";
  special[1000000000000]="un bilione ";


  map<int64_t, std::string> num;

  num[1000]="mila";
  num[1000000]= " milioni";
  num[1000000000]= " miliardi";
  num[1000000000000]= " bilioni";
  
//cout<<n<<"\n";
 if(N/1000000000000!=0){
   int64_t  tmp=N/1000000000000;
  if(tmp==1 && N%1000000000000!=0 ) {
    res += special[1000000000000] += " e ";
    N=N-1000000000000;
  }
  else if(tmp==1 && N%1000000000000==0){
    res += special[1000000000000];
    N=N-1000000000000;
    }
  else{
      //cout<<tmp<<"\n";
     Sub_sequenza(res,tmp);
    if(N-(tmp*1000000000000)==0) res += num[1000000000000];
    else  res += num[1000000000000] += " e " ;
     N=N-(tmp*1000000000000);
  }
}

 if(N/1000000000!=0 && N!=0){
   int64_t  tmp=N/1000000000;
    //cout<<tmp*1000000000<<"\n";
  if(tmp==1 && N%1000000000!=0) {
   res += special[1000000000] += " e ";
    N=N-1000000000;
  }
  else if(tmp==1 && N%1000000000==0){
    res += special[1000000000];
    N=N-1000000000;
    }
  else{
      //cout<<tmp<<"\n";
     Sub_sequenza(res,tmp);
    if(N-(tmp*1000000000)==0) res += num[1000000000];
    else  res += num[1000000000] += " e " ;
    N-=(tmp*1000000000);
  }
}
  //cout<<n<<"\n";
if(N/1000000!=0  && N!=0){
  int64_t tmp=N/1000000;
  if(tmp==1 && N%1000000!=0) {
    res += special[1000000] += " e ";
    N=N-1000000;
  }
  else if(tmp==1 && N%1000000==0){
    res += special[1000000];
    N=N-1000000;
  }
  else{
      //cout<<tmp<<"\n";
     Sub_sequenza(res,tmp);
     if(N-(tmp*1000000)==0) {
       res += num[1000000];
      //cout<<n<<"\n";
     }
     else  res += num[1000000] += " e " ;
     N=N-(tmp*1000000);
  }
}
//cout<<n <<"\n";
if(N/1000!=0  && N!=0){
     int64_t tmp=N/1000;
     if(tmp==1){
         res += special[1000];
         N=N-1000;
     }
     else{
     Sub_sequenza(res,tmp);     
     /*if(N-(tmp*1000)==0)*/ res += num[1000];
     //else  res += num[1000] += " e " ;
     N=N-(tmp*1000);
   } 
}
//cout<<n <<"\n";
//cout<<N/1000 <<"\n";
if(N==0)  res += num[N];
else Sub_sequenza(res,N);

 cout<</*"Il tuo numero è: " <<*/res;
}
/*
int main(){
  std::string res;
 int64_t n=515129370224208;
  numeri_lettere(n,res);
}*/

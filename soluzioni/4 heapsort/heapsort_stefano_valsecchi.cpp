#include <iostream>
#include <fstream>

using namespace std;



void scambia( int & a, int & b){
	int tmp = a;
	a = b;
	b = tmp;
}


void heapify( int vet[], int padre, int n ){
	int sinistro = 2 * padre + 1;
	int destro = 2 * padre + 2;
	int maggiore = padre;
	
	if( sinistro <= n && vet[sinistro] > vet[padre] ){
		maggiore = sinistro;
	}
	
	if( destro <= n && vet[destro] > vet[maggiore] ){
		maggiore = destro;
	}
	
	if( maggiore != padre ){
		scambia( vet[maggiore], vet[padre] );
		heapify( vet, maggiore, n );
	}
}



void costruisciHeap( int vet[], int n ){
	
  for( int i = (n - 1) / 2; i >= 0; i--){
		heapify( vet, i, n );
	}
	return;
}	



int main(){
	
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	int n;
	in >> n;
	int const N = n;
	/*
	 N ed n sono variabili dello stesso valore: nel corso del programma
	 n verrà modificata, mentre N memorizza la lunghezza dell array iniziale.
	 L'uso dell'uno o dell'altra è indifferente nelle fasi iniziali.
	*/
	
	int vet[n];
	
	// inserisco in vet[] gli elementi da ordinare
	for( int i = 0; i < n; i++ ){
		in >> vet[i];
	}
	in.close();
	
	// la prima riga dell'output contiene il numero di elementi da ordinare
	out << n << endl;
	
	// costruisco heap
	costruisciHeap( vet, n - 1 );
	
	// la seconda riga dell'output contiene gli elementi parzialmente ordinati
	for(int i = 0; i < n; i++ ){
		out << vet[i] << " ";
	}
	out << endl;
	
	for( int i = n - 1; i > 0; i--){
		scambia( vet[0], vet[i] );
		n--;
		heapify( vet, 0, n - 1 );
	}
		
	// la terza riga dell'output contiene gli elementi ordinati
	for( int i = 0; i < N; i++ ){
		out << vet[i] << " ";
	}
	
	
	out.close();
	return 0;
}

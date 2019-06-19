#include <iostream>
#include <math.h>

using namespace std;


void scambia( int & a, int & b){
	int tmp = a;
	a = b;
	b = tmp;
}


void newHeapify( int vet[], int padre, int diff, int inizio ){
	int sinistro = 2 * (padre - inizio) + 1 + inizio;
	int destro = 2 * (padre- inizio) + 2 + inizio;
	int maggiore = padre;
		
	if( sinistro <= inizio + diff && vet[sinistro] > vet[padre] ){
		maggiore = sinistro;
	}
	
	if( destro <= inizio + diff && vet[destro] > vet[maggiore] ){
		maggiore = destro;
	}
	
	if( maggiore != padre ){
		scambia( vet[maggiore], vet[padre] );
		newHeapify( vet, maggiore, diff, inizio );
	}
}

void newQuick( int vet[], int inizio, int fine, int profond){
		
	
	if( inizio >= fine ){
		return;
	}
	
	if( profond <= 0 ){
		
		int diff = fine - inizio + 1;

	  for( int i = inizio + (diff - 2) / 2; i >= inizio; i--){
		  newHeapify( vet, i, diff - 1, inizio );
	  }
				
	  for( int i = inizio + diff - 1; i > inizio; i--){
		  scambia(vet[inizio], vet[i]);
		  diff--;
		  newHeapify( vet, inizio, diff - 1, inizio );
	  }

	}else{
		
		int idxpivot;	
		int n = fine - inizio;
		
		
		if( vet[inizio] <= vet[inizio + n / 2] ){
			if( vet[inizio + n / 2] <= vet[fine] ){
				idxpivot = inizio + n / 2;
			}
			else{
				if( vet[inizio] <= vet[fine] ){
					idxpivot = fine;
				}
				else{
					idxpivot = inizio;
				}
			}
		}
		else{
			if( vet[inizio] <= vet[fine] ){
				idxpivot = inizio;
			}
			else{
				if( vet[inizio + n / 2] <= vet[fine] ){
					idxpivot = fine;
				}
				else{
					idxpivot = inizio + n / 2;
				}
			}
		}
		
		
		
		if(inizio != idxpivot) scambia(vet[inizio], vet[idxpivot]);

		int i = inizio + 1, j = fine;	
		
		while( i < j ){
			while( vet[j] >= vet[inizio] && i < j ){
				j--;			
			}
			while( vet[i] <= vet[inizio] && i < j){
				i++;
			}
			scambia(vet[i], vet[j]);
		}		
		
		
		if( vet[inizio] < vet[i] ){
			idxpivot = inizio;
		}
		else{
			scambia( vet[inizio], vet[i] );
			idxpivot = i;
		}
			
				
		newQuick( vet, inizio, idxpivot - 1, profond - 1 );
		newQuick( vet, idxpivot + 1, fine, profond - 1 );
		
	}
}




void
ordina( int vet[], int n ) {		
		
	int profond = log(n);
	int inizio = 0;
	newQuick( vet, inizio, n - 1, profond );	
	
}

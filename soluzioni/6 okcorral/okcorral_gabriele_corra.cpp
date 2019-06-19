#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
#include <vector>
#include <fstream>
#include "course_lib.h"
using namespace std;

/*\
    _                           _                      _           _ ___ 
   / \   _ __ _ __ __ _ _   _  (_)___   ___  ___  _ __| |_ ___  __| |__ \
  / _ \ | '__| '__/ _` | | | | | / __| / __|/ _ \| '__| __/ _ \/ _` | / /
 / ___ \| |  | | | (_| | |_| | | \__ \ \__ \ (_) | |  | ||  __/ (_| ||_| 
/_/   \_\_|  |_|  \__,_|\__, | |_|___/ |___/\___/|_|   \__\___|\__,_|(_) 
                        |___/                                            

\*/
bool isSorted(int a[],int n) {
    int prev = a[0];
	for (int i = 1; i < n; i++) {
		if (a[i] < prev) {
			return false;
        }
		prev = a[i];
	}
    return true;
}

/*\
 ____                                   _                        ___ 
|  _ \ _____   _____ _ __ ___  ___     / \   _ __ _ __ __ _ _   |__ \
| |_) / _ \ \ / / _ \ '__/ __|/ _ \   / _ \ | '__| '__/ _` | | | |/ /
|  _ <  __/\ V /  __/ |  \__ \  __/  / ___ \| |  | | | (_| | |_| |_| 
|_| \_\___| \_/ \___|_|  |___/\___| /_/   \_\_|  |_|  \__,_|\__, (_) 
                                                            |___/    

\*/
bool inverseSorted(int a[],int n) {
    int prev = a[0];
	for (int i = 1; i < n; i++) {
		if (a[i] > prev) {
			return false;
        }
		prev = a[i];
	}
    return true;
}

void revereseArray(int a[], int start, int end) 
{ 
    while (start < end) 
    { 
        int temp = a[start];  
        a[start] = a[end]; 
        a[end] = temp; 
        start++; 
        end--; 
    }  
}

/*\
 ____                     
/ ___|_      ____ _ _ __  
\___ \ \ /\ / / _` | '_ \ 
 ___) \ V  V / (_| | |_) |
|____/ \_/\_/ \__,_| .__/ 
                   |_|    
\*/
// funzione che scambia due elementi
void swap (int &a, int &b){
    int temp = a; // variabile temporanea
    a = b;
    b = temp;
    
}

/*\
 ____  _          _ _   ____             _   
/ ___|| |__   ___| | | / ___|  ___  _ __| |_ 
\___ \| '_ \ / _ \ | | \___ \ / _ \| '__| __|
 ___) | | | |  __/ | |  ___) | (_) | |  | |_ 
|____/|_| |_|\___|_|_| |____/ \___/|_|   \__|
                                             
\*/
void my_shell_sort(int a[], int n) {
  /*\
  Lo Shell Sort è simile all'Isertion Sort, 
  invece di considerare elementi a distanza 1, 
  si considerano elementi a distanza h.
  \*/
  int h = 1;
  // Calcolo dell'h
  while (h <= n) {
    h = 3*h + 1; 
  }
  h = h/3; // h utilizzato inizialmente

  // Analizzo la sottosequenza di elementi distanziati di h
  while (h >= 1) { 
    for (int i = h; i < n; i++) {
      int temp = a[i]; // salvo l'elemento corrente in una variabile temporanea
      int j = i;
      // Confronto il suo valore con quello dell'elemento precedente (indice-h)
      while (j >= h && a[j-h] > temp) { // processo iterativo di scambio "all'indietro"
        a[j] = a[j-h];
        j = j-h;
      }
      // Sposto l'elemento considerato inizialmente nella posizione corretta
      a[j] = temp;
    }
    h = h/3; // nuovo h
  }
}

/*\
 ___                     _   _               ____             _   
|_ _|_ __  ___  ___ _ __| |_(_) ___  _ __   / ___|  ___  _ __| |_ 
 | || '_ \/ __|/ _ \ '__| __| |/ _ \| '_ \  \___ \ / _ \| '__| __|
 | || | | \__ \  __/ |  | |_| | (_) | | | |  ___) | (_) | |  | |_ 
|___|_| |_|___/\___|_|   \__|_|\___/|_| |_| |____/ \___/|_|   \__|
                                                                  
\*/
void insertion_sort(int a[], int first, int last){
    // il primo elemento "first" nel sottoarray è già ordinato
    // parto ad ordinare da "first+1"
    for(int i = first+1; i <= last; i++)
    {
// salvo il valore di a[i]
        int temp = a[i];
        int j = i;
        // confronti all'interno del sottoarray
        while(j > first && a[j-1] > temp){ 
            // si sposta a sinistra finché non trova la posizione di temp(a[i])
            a[j] = a[j-1];
            j--;
        }
        a[j] = temp; // inserisco a[i] nella posizione corretta
    }
}

/*\
 ____            _   _ _   _                     
|  _ \ __ _ _ __| |_(_) |_(_) ___  _ __          
| |_) / _` | '__| __| | __| |/ _ \| '_ \   _____ 
|  __/ (_| | |  | |_| | |_| | (_) | | | | |_____|
|_|   \__,_|_|   \__|_|\__|_|\___/|_| |_|        
                                                 
  ___        _      _     ____             _   
 / _ \ _   _(_) ___| | __/ ___|  ___  _ __| |_ 
| | | | | | | |/ __| |/ /\___ \ / _ \| '__| __|
| |_| | |_| | | (__|   <  ___) | (_) | |  | |_ 
 \__\_\\__,_|_|\___|_|\_\|____/ \___/|_|   \__|
                                               
\*/
// Funzione di Partizionamento dell'array
// restituisce la posizione finale del pivot
int partition(int a[], int first, int last){
    // Scelgo come pivot l'elemento finale del sottoarray
    int pivot = a[last];

    /*\
    Gli elementi:
        - minori del pivot vengono spostati a sinistra della sua posizione finale
        - maggiore del pivot vengono spostati a destra della sua posizione finale
    
    Tutte le volte che incontro un elemento <= al pivot:
        la pos_fin è incrementata
        l'elemento è spostato alla sinistra del pivot
    \*/
    int pos_fin = first;
    for(int i = first; i < last; i++)
    {
        if (a[i] <= pivot) {
            swap(a[i], a[pos_fin]);
            pos_fin++;
        }
    }
    // Sposto il pivot nella posizioen corretta
    swap(a[pos_fin],a[last]); 

    return pos_fin;
}

// Ottimizzazione del Quick Sort
int random_partition(int a[], int first, int last){
    // Scelgo un indice random tra [first, last]
    int ind_pivot = rand() % (last - first + 1) + first;

    // Scambio l'elemento finale con l'elemento scelto in modo random
    swap(a[ind_pivot], a[last]);

    // Partizionamento
    return partition(a, first, last);
}

/*\
 _   _                    ____             _   
| | | | ___  __ _ _ __   / ___|  ___  _ __| |_ 
| |_| |/ _ \/ _` | '_ \  \___ \ / _ \| '__| __|
|  _  |  __/ (_| | |_) |  ___) | (_) | |  | |_ 
|_| |_|\___|\__,_| .__/  |____/ \___/|_|   \__|
                 |_|                           

\*/
// TO DO
void heap_sort(int *first, int *last){
	make_heap(first,last);
	sort_heap(first,last);
}

/*\
 ___       _            ____             _   
|_ _|_ __ | |_ _ __ ___/ ___|  ___  _ __| |_ 
 | || '_ \| __| '__/ _ \___ \ / _ \| '__| __|
 | || | | | |_| | | (_) |__) | (_) | |  | |_ 
|___|_| |_|\__|_|  \___/____/ \___/|_|   \__|
                                             
\*/
void intro_sort(int a[], int *begin, int *end, int max_depth){
    if (begin < end) {
        if ((end - begin) <= 16) { // Esegui l'Insertion Sort se il sottoarray  is < 20
            insertion_sort(a, begin - a, end - a);
        }
        else if (max_depth == 0) { // Esegui l'Heap Sort se max_depth = 0
            heap_sort(begin,end+1);
        }
        else // Esegui il Quick Sort
        {
            /*\
            Utilizzando la scelta random:
                int pos_fin = random_partition(a, begin - a, end - a);
            \*/

            // Senza
            int pos_fin = partition(a, begin - a, end - a);
            intro_sort( a , begin , a + pos_fin - 1 , max_depth - 1 );
            intro_sort( a , a + pos_fin + 1 , end , max_depth - 1 );
        }
    }
}

/*\
 __  __                       ____             _   
|  \/  | ___ _ __ __ _  ___  / ___|  ___  _ __| |_ 
| |\/| |/ _ \ '__/ _` |/ _ \ \___ \ / _ \| '__| __|
| |  | |  __/ | | (_| |  __/  ___) | (_) | |  | |_ 
|_|  |_|\___|_|  \__, |\___| |____/ \___/|_|   \__|
                 |___/                             

\*/
void merge(int a[], int first, int last, int middle,int n){
    int ind_left = first;        // scandisce a[first...middle]
    int ind_right = middle+1;    // scandisce a[middle+1...last]
    int ind_supp = first;        // indice array di support
    // Ho bisogno di un array di supporto su cui salvare temporaneamente gli elementi ordinati
    // Non conosco a priori la dimensione dell'array, quindi devo utilizzare l'allocazione dinamica della memoria
    // Creo un puntatore all'array di supporto
    int *supp;         
    // ho creato un nomeda usare per chiamare l'array, ma non ho spazio in memoria da usare per l'array               
    supp = new int[last+1]; // ha una doppia funzione     
    // 1) Richiedo un blocco di last+1 pezzi di memoria, (last -> è l'elemento variabile)
    // ognuno grande abbastanza da contenere un integer
    // 2) supp "punta" all'inizio del blocco di memoria crato

    while(ind_left <= middle && ind_right <= last){
        if (a[ind_left] <= a[ind_right]) {
            supp[ind_supp] = a[ind_left];
            ind_left++; // mi sposto nel sottoarray sinistro
        }
        else
        {
            supp[ind_supp] = a[ind_right];
            ind_right++; // mi sposto nel sottoarray destro
        }
        ind_supp++; // incremento l'indice dell'array di supporto
    }
    // 2 Casi:
    // 1) il While è interrotto da ind_left > middle
    // allora gli eventuali elementi del sottoarray destro rimanenti si trovano già nella posizione corretta 
    // NON devo salvarli nell'array di supporto
    // 2) il While è interrotto da ind_right > last
    // allora gli eventuali elementi del sottoarray sinistro devono essere spostati in fondo all'array ordinato
    ind_right = last; // senza creare nuove variabili, modifico ind_right
    
    for(int move_left_element = middle; move_left_element >= ind_left; move_left_element--)
    {
        a[ind_right] = a[move_left_element];
        ind_right--;
    }
    for(int pos = first; pos < ind_supp; pos++)
    {
        a[pos] = supp[pos];
    }
    delete[] supp; // rilascio la memoria allocata
}

void merge_sort_rec(int a[], int first, int last, int n){
    if (first < last) {
        int middle = (first + last) / 2;
        merge_sort_rec(a,first,middle,n);
        merge_sort_rec(a,middle+1,last,n);
        merge(a, first, last, middle, n);
    }
}


/*\
 ___ _                 _   _           
|_ _| |_ ___ _ __ __ _| |_(_)_   _____ 
 | || __/ _ \ '__/ _` | __| \ \ / / _ \
 | || ||  __/ | | (_| | |_| |\ V /  __/
|___|\__\___|_|  \__,_|\__|_| \_/ \___|                                       
  ___        _      _      ____             _   
 / _ \ _   _(_) ___| | __ / ___|  ___  _ __| |_ 
| | | | | | | |/ __| |/ / \___ \ / _ \| '__| __|
| |_| | |_| | | (__|   <   ___) | (_) | |  | |_ 
 \__\_\\__,_|_|\___|_|\_\ |____/ \___/|_|   \__|
                                                
\*/
// partition
int partition_for_iterative (int a[], int first, int last){
    int perno = a[last];
    int pos = first-1; 
    // Obbiettivo: trovare la posizione del perno

    for(int next = first; next <= last-1; next++)
    {
        if (a[next] <= perno) {
            // parto da "first", e non "first+1" 
            // poiché prima di fare lo swap incremento "pos"
            pos++;
            swap(a[pos],a[next]); // scambio
        }
    }
    // Sposto il perno nella posizione corretta
    swap(a[pos+1],a[last]); 

    // Ritorno la posizione del perno
    return (pos + 1);
}

// quik sort
void quick_sort_iterative (int a[], int first, int last) {
    int start_ind = 0;
    int end_ind = last;
    int top = -1;
    int *stack = new int[last+1];

    stack[++top] = start_ind;
    stack[++top] = end_ind;

    while(top>=0){
        end_ind = stack[top--];
        start_ind = stack[top--];

        int pos_fin = partition_for_iterative(a,start_ind,end_ind);

        if (pos_fin-1 > start_ind) {
            stack[++top] = start_ind;
            stack[++top] = pos_fin - 1;
        }
        
        if (pos_fin + 1 < end_ind) {
            stack[++top] = pos_fin + 1;
            stack[++top] = end_ind;
        }
        
    }
    
    delete stack;
}

/*\
  ___          _ _             
 / _ \ _ __ __| (_)_ __   __ _ 
| | | | '__/ _` | | '_ \ / _` |
| |_| | | | (_| | | | | | (_| |
 \___/|_|  \__,_|_|_| |_|\__,_|
                               
\*/
void
ordina( int vec[], int N ) {  
    /*\
    Se l'array è già ordinato
    lo restituisco.
    \*/
    if (isSorted(vec , N)) {
    
    }
    /*\
    Se l'array è ordinato ma rovesciato,
    lo rovescio.
    \*/
    else if (inverseSorted(vec,N)) {
        revereseArray(vec,0,N-1);
    }
    /*\
    Se l'array contiene un solo elemento
    lo restituisco
    \*/
    else if (N<=1) {
      
    }
    /*\
    Uso l'Insertion Sort per array di dimensioni molto piccole 1 < N <= 16.
    \*/
    else if (N>1 && N<=16) {
        insertion_sort(vec,0,N-1);
    }
    /*\
    Uso lo Shell Sort per array di dimensioni piccole 16 < N <= 100.
    \*/
    else if (N>16 && N<=100) {
        shell_sort(vec,N);
    }
    /*\
    Uso il Quick Sort iterativo per array di dimensioni 100 < N <= 10 000
    \*/
    else if (N>100 && N<=10000)
    {
        quick_sort_iterative( vec, 0,N-1 );

    }
    else if (N>10000 && N<=10000000) {
    /*\
    Uso l'IntroSort per array di dimensioni superiori 10 000 < N < 10 000 000
    Differenze dal Quick Sort Iterativo:
        - è ricorsivo
        - è ibrido:
            - Insertion Sort -> è + veloce quando il sottoarray da ordinare diventa piccolo
            - Heap Sort -> evita il caso peggiore del Quick Sort     
    \*/
        int max_depth = log(N) * 2; 
        /*\
        L'algoritmo da me utilizzando non usa la scelta random del pivot
        - può essere abilitata -
        \*/
        intro_sort(vec , vec , vec + N - 1 , max_depth);
    }
    /*\
    Per dimensioni di array molto grandi N >= 10 000 000 
    può essere + conveniente il Merge Sort dell'Intro Sort essendo + stabile
    \*/
    else
    {
        merge_sort_rec(vec,0,N-1,N);
    }
}
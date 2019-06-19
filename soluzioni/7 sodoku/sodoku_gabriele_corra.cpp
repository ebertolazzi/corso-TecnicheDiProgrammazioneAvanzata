/*\
 ____            _       _          
/ ___| _   _  __| | ___ | | ___   _ 
\___ \| | | |/ _` |/ _ \| |/ / | | |
 ___) | |_| | (_| | (_) |   <| |_| |
|____/ \__,_|\__,_|\___/|_|\_\\__,_|
                                    
~~~~~~~~~~~~MY~~~~~~~~~~~~~
~~~~~ITERATIVE METHOD:~~~~~

+-+-+-+-+-+-+-+-+ +-+-+-+-+-+
|G|a|b|r|i|e|l|e| |C|o|r|r|a|
+-+-+-+-+-+-+-+-+ +-+-+-+-+-+

Tavola del sudoku:
    - Matrice 9x9 -
   1 2 3 4 5 6 7 8 9
1 |                 |
2 |                 |
3 |                 |
4 |                 |
5 |                 |
6 |                 |
7 |                 |
8 |                 |
9 |                 |

Creo una matrice che contiene per ogni posizione le possibili soluzioni (9x9 = 81 posizioni) :
[ Calcolo le soluzioni controllando i numeri nella riga, nella colonna e nella sottotabella corrispondente ad ogni posizione ]
    - Matrice 81xN, N:numero di soluzioni per quella determinata posizione -
|   1       { sol1, sol2, sol3 }
|   2       {  }
|   3       {  }
|   ...
|
|           Se in quella determinata posizione è già presente un numero la riga è vuota
|   
V   81

Se in una posizione è possibile inserire un solo numero 
    => lo inserisco
    => aggiorno la matrice delle soluzioni

Se in una nuova posizione è possibile inserire un solo numero
    => lo inserisco
    => aggiorno la matrice delle soluzioni

Continuo finchè possibile...

La tabella è completa?
    => Sì, allora la restituisco
    => No, non ho posizioni con una sola soluzione possibile, ma più di una -> procedo per tentativi

\*/

#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

#include "course_lib.h"

using namespace std;


void print_vector ( vector<int> &v )
{
    for ( int i = 0; i < v.size(); i++ ) { cout << v[i] << " "; }
    cout << endl;
}

void print_board ( unsigned board[9][9] )
{
    for ( int i = 0; i < 9; i++ )
    {
        for ( int j = 0; j < 9; j++ ) { cout << board[i][j] << " "; }
        cout << endl;
    }
}

void print_NotSquareMatrix ( vector< vector<int> > &m )
{
    int size_row;
    for ( int i = 0; i < m.size(); i++ )
    {
        cout << i << ": ";
        size_row = m[i].size();
        if ( size_row != 0 )
        {
            for ( int j = 0; j < size_row; j++ )
            {
                cout << m[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void print_NotSquareMatrix_ParticularRow ( vector< vector<int> > &m, int &row )
{ 
    for ( int i = 0; i < m[row].size(); i++ )
    {
        cout << m[row][i] << " ";
    }
    cout << endl;
}

void initial_configuration ( unsigned board[9][9] ,
                    vector<int> &row1, vector<int> &row2, vector<int> &row3,
                    vector<int> &row4, vector<int> &row5, vector<int> &row6,
                    vector<int> &row7, vector<int> &row8, vector<int> &row9,
                    vector<int> &col1, vector<int> &col2, vector<int> &col3,
                    vector<int> &col4, vector<int> &col5, vector<int> &col6,
                    vector<int> &col7, vector<int> &col8, vector<int> &col9,
                    vector<int> &tab1, vector<int> &tab2, vector<int> &tab3,
                    vector<int> &tab4, vector<int> &tab5, vector<int> &tab6,
                    vector<int> &tab7, vector<int> &tab8, vector<int> &tab9 )
{
    for ( int row = 0; row < 9; row++ )
    {
        for ( int col = 0; col < 9; col++ )
        {
            if ( board[row][col] != 0 )
            {
                if ( row == 0 ) 
                {  
                    row1.push_back( board[row][col] );
                    if      ( col < 3 ) 
                    {  
                        if      ( col == 0 ) { col1.push_back( board[row][col] ); tab1.push_back( board[row][col] ); }
                        else if ( col == 1 ) { col2.push_back( board[row][col] ); tab1.push_back( board[row][col] ); }
                        else                 { col3.push_back( board[row][col] ); tab1.push_back( board[row][col] ); }
                    }
                    else if ( col < 6 ) 
                    {  
                        if      ( col == 3 ) { col4.push_back( board[row][col] ); tab2.push_back( board[row][col] ); }
                        else if ( col == 4 ) { col5.push_back( board[row][col] ); tab2.push_back( board[row][col] ); }
                        else                 { col6.push_back( board[row][col] ); tab2.push_back( board[row][col] ); }                    
                    }
                    else                
                    {  
                        if      ( col == 6 ) { col7.push_back( board[row][col] ); tab3.push_back( board[row][col] ); }
                        else if ( col == 7 ) { col8.push_back( board[row][col] ); tab3.push_back( board[row][col] ); }
                        else                 { col9.push_back( board[row][col] ); tab3.push_back( board[row][col] ); }   
                    }
                }
                if ( row == 1 ) 
                {  
                    row2.push_back( board[row][col] );
                    if      ( col < 3 ) 
                    {  
                        if      ( col == 0 ) { col1.push_back( board[row][col] ); tab1.push_back( board[row][col] ); }
                        else if ( col == 1 ) { col2.push_back( board[row][col] ); tab1.push_back( board[row][col] ); }
                        else                 { col3.push_back( board[row][col] ); tab1.push_back( board[row][col] ); }
                    }
                    else if ( col < 6 ) 
                    {  
                        if      ( col == 3 ) { col4.push_back( board[row][col] ); tab2.push_back( board[row][col] ); }
                        else if ( col == 4 ) { col5.push_back( board[row][col] ); tab2.push_back( board[row][col] ); }
                        else                 { col6.push_back( board[row][col] ); tab2.push_back( board[row][col] ); }                    
                    }
                    else                
                    {  
                        if      ( col == 6 ) { col7.push_back( board[row][col] ); tab3.push_back( board[row][col] ); }
                        else if ( col == 7 ) { col8.push_back( board[row][col] ); tab3.push_back( board[row][col] ); }
                        else                 { col9.push_back( board[row][col] ); tab3.push_back( board[row][col] ); }   
                    }
                }
                if ( row == 2 ) 
                {  
                    row3.push_back( board[row][col] );
                    if      ( col < 3 ) 
                    {  
                        if      ( col == 0 ) { col1.push_back( board[row][col] ); tab1.push_back( board[row][col] ); }
                        else if ( col == 1 ) { col2.push_back( board[row][col] ); tab1.push_back( board[row][col] ); }
                        else                 { col3.push_back( board[row][col] ); tab1.push_back( board[row][col] ); }
                    }
                    else if ( col < 6 ) 
                    {  
                        if      ( col == 3 ) { col4.push_back( board[row][col] ); tab2.push_back( board[row][col] ); }
                        else if ( col == 4 ) { col5.push_back( board[row][col] ); tab2.push_back( board[row][col] ); }
                        else                 { col6.push_back( board[row][col] ); tab2.push_back( board[row][col] ); }                    
                    }
                    else                
                    {  
                        if      ( col == 6 ) { col7.push_back( board[row][col] ); tab3.push_back( board[row][col] ); }
                        else if ( col == 7 ) { col8.push_back( board[row][col] ); tab3.push_back( board[row][col] ); }
                        else                 { col9.push_back( board[row][col] ); tab3.push_back( board[row][col] ); }   
                    }
                }
                if ( row == 3 ) 
                {  
                    row4.push_back( board[row][col] );
                    if      ( col < 3 ) 
                    {  
                        if      ( col == 0 ) { col1.push_back( board[row][col] ); tab4.push_back( board[row][col] ); }
                        else if ( col == 1 ) { col2.push_back( board[row][col] ); tab4.push_back( board[row][col] ); }
                        else                 { col3.push_back( board[row][col] ); tab4.push_back( board[row][col] ); }
                    }
                    else if ( col < 6 ) 
                    {  
                        if      ( col == 3 ) { col4.push_back( board[row][col] ); tab5.push_back( board[row][col] ); }
                        else if ( col == 4 ) { col5.push_back( board[row][col] ); tab5.push_back( board[row][col] ); }
                        else                 { col6.push_back( board[row][col] ); tab5.push_back( board[row][col] ); }                    
                    }
                    else                
                    {  
                        if      ( col == 6 ) { col7.push_back( board[row][col] ); tab6.push_back( board[row][col] ); }
                        else if ( col == 7 ) { col8.push_back( board[row][col] ); tab6.push_back( board[row][col] ); }
                        else                 { col9.push_back( board[row][col] ); tab6.push_back( board[row][col] ); }   
                    }
                }
                if ( row == 4 ) 
                {  
                    row5.push_back( board[row][col] );
                    if      ( col < 3 ) 
                    {  
                        if      ( col == 0 ) { col1.push_back( board[row][col] ); tab4.push_back( board[row][col] ); }
                        else if ( col == 1 ) { col2.push_back( board[row][col] ); tab4.push_back( board[row][col] ); }
                        else                 { col3.push_back( board[row][col] ); tab4.push_back( board[row][col] ); }
                    }
                    else if ( col < 6 ) 
                    {  
                        if      ( col == 3 ) { col4.push_back( board[row][col] ); tab5.push_back( board[row][col] ); }
                        else if ( col == 4 ) { col5.push_back( board[row][col] ); tab5.push_back( board[row][col] ); }
                        else                 { col6.push_back( board[row][col] ); tab5.push_back( board[row][col] ); }                    
                    }
                    else                
                    {  
                        if      ( col == 6 ) { col7.push_back( board[row][col] ); tab6.push_back( board[row][col] ); }
                        else if ( col == 7 ) { col8.push_back( board[row][col] ); tab6.push_back( board[row][col] ); }
                        else                 { col9.push_back( board[row][col] ); tab6.push_back( board[row][col] ); }   
                    }
                }
                if ( row == 5 ) 
                {  
                    row6.push_back( board[row][col] );
                    if      ( col < 3 ) 
                    {  
                        if      ( col == 0 ) { col1.push_back( board[row][col] ); tab4.push_back( board[row][col] ); }
                        else if ( col == 1 ) { col2.push_back( board[row][col] ); tab4.push_back( board[row][col] ); }
                        else                 { col3.push_back( board[row][col] ); tab4.push_back( board[row][col] ); }
                    }
                    else if ( col < 6 ) 
                    {  
                        if      ( col == 3 ) { col4.push_back( board[row][col] ); tab5.push_back( board[row][col] ); }
                        else if ( col == 4 ) { col5.push_back( board[row][col] ); tab5.push_back( board[row][col] ); }
                        else                 { col6.push_back( board[row][col] ); tab5.push_back( board[row][col] ); }                    
                    }
                    else                
                    {  
                        if      ( col == 6 ) { col7.push_back( board[row][col] ); tab6.push_back( board[row][col] ); }
                        else if ( col == 7 ) { col8.push_back( board[row][col] ); tab6.push_back( board[row][col] ); }
                        else                 { col9.push_back( board[row][col] ); tab6.push_back( board[row][col] ); }   
                    }
                }
                if ( row == 6 ) 
                {  
                    row7.push_back( board[row][col] );
                    if      ( col < 3 ) 
                    {  
                        if      ( col == 0 ) { col1.push_back( board[row][col] ); tab7.push_back( board[row][col] ); }
                        else if ( col == 1 ) { col2.push_back( board[row][col] ); tab7.push_back( board[row][col] ); }
                        else                 { col3.push_back( board[row][col] ); tab7.push_back( board[row][col] ); }
                    }
                    else if ( col < 6 ) 
                    {  
                        if      ( col == 3 ) { col4.push_back( board[row][col] ); tab8.push_back( board[row][col] ); }
                        else if ( col == 4 ) { col5.push_back( board[row][col] ); tab8.push_back( board[row][col] ); }
                        else                 { col6.push_back( board[row][col] ); tab8.push_back( board[row][col] ); }                    
                    }
                    else                
                    {  
                        if      ( col == 6 ) { col7.push_back( board[row][col] ); tab9.push_back( board[row][col] ); }
                        else if ( col == 7 ) { col8.push_back( board[row][col] ); tab9.push_back( board[row][col] ); }
                        else                 { col9.push_back( board[row][col] ); tab9.push_back( board[row][col] ); }   
                    }
                }
                if ( row == 7 ) 
                {  
                    row8.push_back( board[row][col] );
                    if      ( col < 3 ) 
                    {  
                        if      ( col == 0 ) { col1.push_back( board[row][col] ); tab7.push_back( board[row][col] ); }
                        else if ( col == 1 ) { col2.push_back( board[row][col] ); tab7.push_back( board[row][col] ); }
                        else                 { col3.push_back( board[row][col] ); tab7.push_back( board[row][col] ); }
                    }
                    else if ( col < 6 ) 
                    {  
                        if      ( col == 3 ) { col4.push_back( board[row][col] ); tab8.push_back( board[row][col] ); }
                        else if ( col == 4 ) { col5.push_back( board[row][col] ); tab8.push_back( board[row][col] ); }
                        else                 { col6.push_back( board[row][col] ); tab8.push_back( board[row][col] ); }                    
                    }
                    else                
                    {  
                        if      ( col == 6 ) { col7.push_back( board[row][col] ); tab9.push_back( board[row][col] ); }
                        else if ( col == 7 ) { col8.push_back( board[row][col] ); tab9.push_back( board[row][col] ); }
                        else                 { col9.push_back( board[row][col] ); tab9.push_back( board[row][col] ); }   
                    }
                }
                if ( row == 8 ) 
                {  
                    row9.push_back( board[row][col] );
                    if      ( col < 3 ) 
                    {  
                        if      ( col == 0 ) { col1.push_back( board[row][col] ); tab7.push_back( board[row][col] ); }
                        else if ( col == 1 ) { col2.push_back( board[row][col] ); tab7.push_back( board[row][col] ); }
                        else                 { col3.push_back( board[row][col] ); tab7.push_back( board[row][col] ); }
                    }
                    else if ( col < 6 ) 
                    {  
                        if      ( col == 3 ) { col4.push_back( board[row][col] ); tab8.push_back( board[row][col] ); }
                        else if ( col == 4 ) { col5.push_back( board[row][col] ); tab8.push_back( board[row][col] ); }
                        else                 { col6.push_back( board[row][col] ); tab8.push_back( board[row][col] ); }                    
                    }
                    else                
                    {  
                        if      ( col == 6 ) { col7.push_back( board[row][col] ); tab9.push_back( board[row][col] ); }
                        else if ( col == 7 ) { col8.push_back( board[row][col] ); tab9.push_back( board[row][col] ); }
                        else                 { col9.push_back( board[row][col] ); tab9.push_back( board[row][col] ); }   
                    }
                }
            }
        }
    }
}

void calc_poss_sol ( vector<int> &el, 
                    vector<int> &v1, vector<int> &v2, vector<int> &v3 )
{
    bool one   = false; bool two   = false; bool three = false;
    bool four  = false; bool five  = false; bool six   = false;
    bool seven = false; bool eight = false; bool nine  = false;

    for ( int i = 0; i < v1.size(); i++ )
    {
        if ( v1[i] == 1 && !one  ) one   = true;
        if ( v1[i] == 2 && !two  ) two   = true;
        if ( v1[i] == 3 && !three) three = true;
        if ( v1[i] == 4 && !four ) four  = true;
        if ( v1[i] == 5 && !five ) five  = true;
        if ( v1[i] == 6 && !six  ) six   = true;
        if ( v1[i] == 7 && !seven) seven = true;
        if ( v1[i] == 8 && !eight) eight = true;
        if ( v1[i] == 9 && !nine ) nine  = true;
    }

    for ( int j = 0; j < v2.size(); j++ )
    {
        if ( v2[j] == 1 && !one  ) one   = true;
        if ( v2[j] == 2 && !two  ) two   = true;
        if ( v2[j] == 3 && !three) three = true;
        if ( v2[j] == 4 && !four ) four  = true;
        if ( v2[j] == 5 && !five ) five  = true;
        if ( v2[j] == 6 && !six  ) six   = true;
        if ( v2[j] == 7 && !seven) seven = true;
        if ( v2[j] == 8 && !eight) eight = true;
        if ( v2[j] == 9 && !nine ) nine  = true;        
    }

    for ( int k = 0; k < v3.size(); k++ )
    {
        if ( v3[k] == 1 && !one  ) one   = true;
        if ( v3[k] == 2 && !two  ) two   = true;
        if ( v3[k] == 3 && !three) three = true;
        if ( v3[k] == 4 && !four ) four  = true;
        if ( v3[k] == 5 && !five ) five  = true;
        if ( v3[k] == 6 && !six  ) six   = true;
        if ( v3[k] == 7 && !seven) seven = true;
        if ( v3[k] == 8 && !eight) eight = true;
        if ( v3[k] == 9 && !nine ) nine  = true;             
    }

    if ( !one )   el.push_back( 1 );
    if ( !two )   el.push_back( 2 );
    if ( !three ) el.push_back( 3 );
    if ( !four )  el.push_back( 4 );
    if ( !five )  el.push_back( 5 );
    if ( !six )   el.push_back( 6 );
    if ( !seven ) el.push_back( 7 );
    if ( !eight ) el.push_back( 8 );
    if ( !nine )  el.push_back( 9 );

}

void possible_solutions ( unsigned board[9][9] ,
                    vector<int> &row1, vector<int> &row2, vector<int> &row3,
                    vector<int> &row4, vector<int> &row5, vector<int> &row6,
                    vector<int> &row7, vector<int> &row8, vector<int> &row9,
                    vector<int> &col1, vector<int> &col2, vector<int> &col3,
                    vector<int> &col4, vector<int> &col5, vector<int> &col6,
                    vector<int> &col7, vector<int> &col8, vector<int> &col9,
                    vector<int> &tab1, vector<int> &tab2, vector<int> &tab3,
                    vector<int> &tab4, vector<int> &tab5, vector<int> &tab6,
                    vector<int> &tab7, vector<int> &tab8, vector<int> &tab9,
                    vector< vector<int> > &solutions )
{
    vector<int> element_ij; 
    for ( int i = 0; i < 9; i++ )
    {
        for ( int j = 0; j < 9; j++ )
        {
            // Clear the vector of possible solutions for the particular element ij
            element_ij.clear();

            // Calculate the possible solutions for each element of the board that is = 0
            // to do that the function "calc_poss_sol" use the vector which has the elements in the starting sudoku
            if ( board[i][j] == 0 )
            {
                if ( i == 0 )
                {
                    if ( j < 3 )
                    {
                        if      ( j == 0 ) { calc_poss_sol( element_ij, row1, col1, tab1 ); }
                        else if ( j == 1 ) { calc_poss_sol( element_ij, row1, col2, tab1 ); }
                        else               { calc_poss_sol( element_ij, row1, col3, tab1 ); }
                    }
                    else if ( j < 6 )
                    {
                        if      ( j == 3 ) { calc_poss_sol( element_ij, row1, col4, tab2 ); }
                        else if ( j == 4 ) { calc_poss_sol( element_ij, row1, col5, tab2 ); }
                        else               { calc_poss_sol( element_ij, row1, col6, tab2 ); }           
                    }
                    else 
                    {
                        if      ( j == 6 ) { calc_poss_sol( element_ij, row1, col7, tab3 ); }
                        else if ( j == 7 ) { calc_poss_sol( element_ij, row1, col8, tab3 ); }
                        else               { calc_poss_sol( element_ij, row1, col9, tab3 ); }        
                    } 
                }
                if ( i == 1 )
                {
                    if ( j < 3 )
                    {
                        if      ( j == 0 ) { calc_poss_sol( element_ij, row2, col1, tab1 ); }
                        else if ( j == 1 ) { calc_poss_sol( element_ij, row2, col2, tab1 ); }
                        else               { calc_poss_sol( element_ij, row2, col3, tab1 ); }
                    }
                    else if ( j < 6 )
                    {
                        if      ( j == 3 ) { calc_poss_sol( element_ij, row2, col4, tab2 ); }
                        else if ( j == 4 ) { calc_poss_sol( element_ij, row2, col5, tab2 ); }
                        else               { calc_poss_sol( element_ij, row2, col6, tab2 ); }           
                    }
                    else 
                    {
                        if      ( j == 6 ) { calc_poss_sol( element_ij, row2, col7, tab3 ); }
                        else if ( j == 7 ) { calc_poss_sol( element_ij, row2, col8, tab3 ); }
                        else               { calc_poss_sol( element_ij, row2, col9, tab3 ); }        
                    }                 
                }
                if ( i == 2 )
                {
                    if ( j < 3 )
                    {
                        if      ( j == 0 ) { calc_poss_sol( element_ij, row3, col1, tab1 ); }
                        else if ( j == 1 ) { calc_poss_sol( element_ij, row3, col2, tab1 ); }
                        else               { calc_poss_sol( element_ij, row3, col3, tab1 ); }
                    }
                    else if ( j < 6 )
                    {
                        if      ( j == 3 ) { calc_poss_sol( element_ij, row3, col4, tab2 ); }
                        else if ( j == 4 ) { calc_poss_sol( element_ij, row3, col5, tab2 ); }
                        else               { calc_poss_sol( element_ij, row3, col6, tab2 ); }           
                    }
                    else 
                    {
                        if      ( j == 6 ) { calc_poss_sol( element_ij, row3, col7, tab3 ); }
                        else if ( j == 7 ) { calc_poss_sol( element_ij, row3, col8, tab3 ); }
                        else               { calc_poss_sol( element_ij, row3, col9, tab3 ); }        
                    }                 
                }
                if ( i == 3 )
                {
                    if ( j < 3 )
                    {
                        if      ( j == 0 ) { calc_poss_sol( element_ij, row4, col1, tab4 ); }
                        else if ( j == 1 ) { calc_poss_sol( element_ij, row4, col2, tab4 ); }
                        else               { calc_poss_sol( element_ij, row4, col3, tab4 ); }
                    }
                    else if ( j < 6 )
                    {
                        if      ( j == 3 ) { calc_poss_sol( element_ij, row4, col4, tab5 ); }
                        else if ( j == 4 ) { calc_poss_sol( element_ij, row4, col5, tab5 ); }
                        else               { calc_poss_sol( element_ij, row4, col6, tab5 ); }           
                    }
                    else 
                    {
                        if      ( j == 6 ) { calc_poss_sol( element_ij, row4, col7, tab6 ); }
                        else if ( j == 7 ) { calc_poss_sol( element_ij, row4, col8, tab6 ); }
                        else               { calc_poss_sol( element_ij, row4, col9, tab6 ); }        
                    }                 
                }
                if ( i == 4 )
                {
                    if ( j < 3 )
                    {
                        if      ( j == 0 ) { calc_poss_sol( element_ij, row5, col1, tab4 ); }
                        else if ( j == 1 ) { calc_poss_sol( element_ij, row5, col2, tab4 ); }
                        else               { calc_poss_sol( element_ij, row5, col3, tab4 ); }
                    }
                    else if ( j < 6 )
                    {
                        if      ( j == 3 ) { calc_poss_sol( element_ij, row5, col4, tab5 ); }
                        else if ( j == 4 ) { calc_poss_sol( element_ij, row5, col5, tab5 ); }
                        else               { calc_poss_sol( element_ij, row5, col6, tab5 ); }           
                    }
                    else 
                    {
                        if      ( j == 6 ) { calc_poss_sol( element_ij, row5, col7, tab6 ); }
                        else if ( j == 7 ) { calc_poss_sol( element_ij, row5, col8, tab6 ); }
                        else               { calc_poss_sol( element_ij, row5, col9, tab6 ); }        
                    }                         
                }
                if ( i == 5 )
                {
                    if ( j < 3 )
                    {
                        if      ( j == 0 ) { calc_poss_sol( element_ij, row6, col1, tab4 ); }
                        else if ( j == 1 ) { calc_poss_sol( element_ij, row6, col2, tab4 ); }
                        else               { calc_poss_sol( element_ij, row6, col3, tab4 ); }
                    }
                    else if ( j < 6 )
                    {
                        if      ( j == 3 ) { calc_poss_sol( element_ij, row6, col4, tab5 ); }
                        else if ( j == 4 ) { calc_poss_sol( element_ij, row6, col5, tab5 ); }
                        else               { calc_poss_sol( element_ij, row6, col6, tab5 ); }           
                    }
                    else 
                    {
                        if      ( j == 6 ) { calc_poss_sol( element_ij, row6, col7, tab6 ); }
                        else if ( j == 7 ) { calc_poss_sol( element_ij, row6, col8, tab6 ); }
                        else               { calc_poss_sol( element_ij, row6, col9, tab6 ); }        
                    }                         
                }
                if ( i == 6 )
                {
                    if ( j < 3 )
                    {
                        if      ( j == 0 ) { calc_poss_sol( element_ij, row7, col1, tab7 ); }
                        else if ( j == 1 ) { calc_poss_sol( element_ij, row7, col2, tab7 ); }
                        else               { calc_poss_sol( element_ij, row7, col3, tab7 ); }
                    }
                    else if ( j < 6 )
                    {
                        if      ( j == 3 ) { calc_poss_sol( element_ij, row7, col4, tab8 ); }
                        else if ( j == 4 ) { calc_poss_sol( element_ij, row7, col5, tab8 ); }
                        else               { calc_poss_sol( element_ij, row7, col6, tab8 ); }           
                    }
                    else 
                    {
                        if      ( j == 6 ) { calc_poss_sol( element_ij, row7, col7, tab9 ); }
                        else if ( j == 7 ) { calc_poss_sol( element_ij, row7, col8, tab9 ); }
                        else               { calc_poss_sol( element_ij, row7, col9, tab9 ); }        
                    }                                         
                }
                if ( i == 7 )
                {
                    if ( j < 3 )
                    {
                        if      ( j == 0 ) { calc_poss_sol( element_ij, row8, col1, tab7 ); }
                        else if ( j == 1 ) { calc_poss_sol( element_ij, row8, col2, tab7 ); }
                        else               { calc_poss_sol( element_ij, row8, col3, tab7 ); }
                    }
                    else if ( j < 6 )
                    {
                        if      ( j == 3 ) { calc_poss_sol( element_ij, row8, col4, tab8 ); }
                        else if ( j == 4 ) { calc_poss_sol( element_ij, row8, col5, tab8 ); }
                        else               { calc_poss_sol( element_ij, row8, col6, tab8 ); }           
                    }
                    else 
                    {
                        if      ( j == 6 ) { calc_poss_sol( element_ij, row8, col7, tab9 ); }
                        else if ( j == 7 ) { calc_poss_sol( element_ij, row8, col8, tab9 ); }
                        else               { calc_poss_sol( element_ij, row8, col9, tab9 ); }        
                    }                 
                }
                if ( i == 8 )
                {
                    if ( j < 3 )
                    {
                        if      ( j == 0 ) { calc_poss_sol( element_ij, row9, col1, tab7 ); }
                        else if ( j == 1 ) { calc_poss_sol( element_ij, row9, col2, tab7 ); }
                        else               { calc_poss_sol( element_ij, row9, col3, tab7 ); }
                    }
                    else if ( j < 6 )
                    {
                        if      ( j == 3 ) { calc_poss_sol( element_ij, row9, col4, tab8 ); }
                        else if ( j == 4 ) { calc_poss_sol( element_ij, row9, col5, tab8 ); }
                        else               { calc_poss_sol( element_ij, row9, col6, tab8 ); }           
                    }
                    else 
                    {
                        if      ( j == 6 ) { calc_poss_sol( element_ij, row9, col7, tab9 ); }
                        else if ( j == 7 ) { calc_poss_sol( element_ij, row9, col8, tab9 ); }
                        else               { calc_poss_sol( element_ij, row9, col9, tab9 ); }        
                    }                 
                }   

                solutions.push_back(element_ij);
            }
            else
            {
                element_ij = {};
                solutions.push_back( element_ij );
            }
                
        }
    }
}

void check_poss_sol ( unsigned board[9][9], 
                        vector< vector<int> > &solutions,
                        int &el_value, int &el_row, int &el_col, int &el_posInTab )
{
    for ( int element = 0; element < solutions.size(); element++ )
    {
        if ( solutions[element].size() == 1 )
        {
            el_value = solutions[element][0];
            el_posInTab = element;

            el_row = element / 9;
            if      ( element >= 72 ) { el_col = element - 72; }
            else if ( element >= 63 ) { el_col = element - 63; }
            else if ( element >= 54 ) { el_col = element - 54; }
            else if ( element >= 45 ) { el_col = element - 45; }
            else if ( element >= 36 ) { el_col = element - 36; }
            else if ( element >= 27 ) { el_col = element - 27; }
            else if ( element >= 18 ) { el_col = element - 18; }
            else if ( element >= 9 )  { el_col = element - 9;  }
            else                      { el_col = element - 0;  }

            // Insert element in the board
            board[el_row][el_col] = solutions[element][0];

            // Remove the solutions 
            solutions[element].pop_back();

            return;
        }
    }
}

void update_poss_sol ( vector< vector<int> > &solutions,
                        int &el_value, int &el_row, int &el_col, int &el_posInTab )
{
    
    // Update the elements in the rows [ VERTICALLY ]
    //int same_rowDown = el_posInTab - 9 ; int same_rowUp = el_posInTab + 9 ;
    int same_rowDown = el_posInTab; int same_rowUp = el_posInTab;
    for ( int i = 1; i <= 10; i++  )
    {
        same_rowDown = el_posInTab - 9*i;
        if ( same_rowDown < 0 ) break; 
        else
        {
            solutions[same_rowDown].erase( remove( solutions[same_rowDown].begin(), solutions[same_rowDown].end(), el_value ), solutions[same_rowDown].end() );       
        }
    }
    for ( int i = 1; i <= 10; i++ )
    {
        same_rowUp = el_posInTab + 9*i;
        if ( same_rowUp > 80 ) break;
        else
        {
            solutions[same_rowUp].erase( remove( solutions[same_rowUp].begin(), solutions[same_rowUp].end(), el_value ), solutions[same_rowUp].end() );              
        }
    }

    /*
    - Equivalent method -

    while ( same_rowDown >= 0  )
    {
        solutions[same_rowDown].erase( remove( solutions[same_rowDown].begin(), solutions[same_rowDown].end(), el_value ), solutions[same_rowDown].end() );      
        same_rowDown = same_rowDown - 9;
    }
    while ( same_rowUp <= 80 )
    {
        solutions[same_rowUp].erase( remove( solutions[same_rowUp].begin(), solutions[same_rowUp].end(), el_value ), solutions[same_rowUp].end() );      
        same_rowUp = same_rowUp + 9;        
    }
    */

    // Update the elements in the columns [ HORIZONTALLY ]
    if      ( el_posInTab >= 72 ) 
    {  
        for ( int i = 72; i <= 80; i++ )
        {
            if ( i == el_posInTab ) { }
            else
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                     
            }
        }
    }
    else if ( el_posInTab >= 63 ) 
    {  
        for ( int i = 63; i <= 71; i++ )
        {
            if ( i == el_posInTab ) { }
            else
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                   
            }
        }
    }
    else if ( el_posInTab >= 54 ) 
    {  
        for ( int i = 54; i <= 62; i++ )
        {
            if ( i == el_posInTab ) { }
            else
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                   
            }
        }
    }
    else if ( el_posInTab >= 45 ) 
    {  
        for ( int i = 45; i <= 53; i++ )
        {
            if ( i == el_posInTab ) { }
            else
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );             
            }
        }
    }
    else if ( el_posInTab >= 36 ) 
    {  
        for ( int i = 36; i <= 44; i++ )
        {
            if ( i == el_posInTab ) { }
            else
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                
            }
        }
    }
    else if ( el_posInTab >= 27 ) 
    {  
        for ( int i = 27; i <= 35; i++ )
        {
            if ( i == el_posInTab ) { }
            else
            {

                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );             
            }
        }
    }
    else if ( el_posInTab >= 18 ) 
    {  
        for ( int i = 18; i <= 26; i++ )
        {
            if ( i == el_posInTab ) { }
            else
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                   
            }
        }
    }
    else if ( el_posInTab >= 9  ) 
    {  
        for ( int i = 9; i <= 17; i++ )
        {
            if ( i == el_posInTab ) { }
            else
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                   
            }
        }
    }
    else                          
    {  
        for ( int i = 0; i <= 8; i++ )
        {
            if ( i == el_posInTab ) { }
            else
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                 
            }
        }
    }

    // Update the subtable
    if ( el_row >= 6 )
    {
        if ( el_col >= 6 ) // Sub 9
        {
            for ( int i = 60; i <= 62; i++ )
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                 
                solutions[i+9].erase( remove( solutions[i+9].begin(), solutions[i+9].end(), el_value ), solutions[i+9].end() );
                solutions[i+9+9].erase( remove( solutions[i+9+9].begin(), solutions[i+9+9].end(), el_value ), solutions[i+9+9].end() );
            }
        }
        else if ( el_col >= 3 ) // Sub 8
        {
            for ( int i = 57; i <= 59; i++ )
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                 
                solutions[i+9].erase( remove( solutions[i+9].begin(), solutions[i+9].end(), el_value ), solutions[i+9].end() );
                solutions[i+9+9].erase( remove( solutions[i+9+9].begin(), solutions[i+9+9].end(), el_value ), solutions[i+9+9].end() );
            }
        }
        else // Sub 7
        {
            for ( int i = 54; i <= 56; i++ )
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                 
                solutions[i+9].erase( remove( solutions[i+9].begin(), solutions[i+9].end(), el_value ), solutions[i+9].end() );
                solutions[i+9+9].erase( remove( solutions[i+9+9].begin(), solutions[i+9+9].end(), el_value ), solutions[i+9+9].end() );
            }
        }
    }
    else if ( el_row >= 3 )
    {
        if ( el_col >= 6 ) // Sub 6
        {
            for ( int i = 33; i <= 35; i++ )
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                 
                solutions[i+9].erase( remove( solutions[i+9].begin(), solutions[i+9].end(), el_value ), solutions[i+9].end() );
                solutions[i+9+9].erase( remove( solutions[i+9+9].begin(), solutions[i+9+9].end(), el_value ), solutions[i+9+9].end() );
            }
        }
        else if ( el_col >= 3 ) // Sub 5
        {
            for ( int i = 30; i <= 32; i++ )
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                 
                solutions[i+9].erase( remove( solutions[i+9].begin(), solutions[i+9].end(), el_value ), solutions[i+9].end() );
                solutions[i+9+9].erase( remove( solutions[i+9+9].begin(), solutions[i+9+9].end(), el_value ), solutions[i+9+9].end() );
            }
        }
        else // Sub 4
        {
            for ( int i = 27; i <= 29; i++ )
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                 
                solutions[i+9].erase( remove( solutions[i+9].begin(), solutions[i+9].end(), el_value ), solutions[i+9].end() );
                solutions[i+9+9].erase( remove( solutions[i+9+9].begin(), solutions[i+9+9].end(), el_value ), solutions[i+9+9].end() );
            }            
        }
    }
    else
    {
        if ( el_col >= 6 ) // Sub 3
        {
            for ( int i = 6; i <= 8; i++ )
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                 
                solutions[i+9].erase( remove( solutions[i+9].begin(), solutions[i+9].end(), el_value ), solutions[i+9].end() );
                solutions[i+9+9].erase( remove( solutions[i+9+9].begin(), solutions[i+9+9].end(), el_value ), solutions[i+9+9].end() );
            }
        }
        else if ( el_col >= 3 ) // Sub 2
        {
            for ( int i = 3; i <= 5; i++ )
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                 
                solutions[i+9].erase( remove( solutions[i+9].begin(), solutions[i+9].end(), el_value ), solutions[i+9].end() );
                solutions[i+9+9].erase( remove( solutions[i+9+9].begin(), solutions[i+9+9].end(), el_value ), solutions[i+9+9].end() );
            }
        }
        else // Sub 1
        {
            for ( int i = 0; i <= 2; i++ )
            {
                solutions[i].erase( remove( solutions[i].begin(), solutions[i].end(), el_value ), solutions[i].end() );                 
                solutions[i+9].erase( remove( solutions[i+9].begin(), solutions[i+9].end(), el_value ), solutions[i+9].end() );
                solutions[i+9+9].erase( remove( solutions[i+9+9].begin(), solutions[i+9+9].end(), el_value ), solutions[i+9+9].end() );
            }            
        }        
    }
}

void check_complete ( unsigned board[9][9], bool &complete )
{
    for ( int i = 0; i < 9; i++ )
    {
        for ( int j = 0; j < 9; j++ )
        {
            if ( board[i][j] == 0 )
            {
                return;
            }
        }
    }
    complete = true;
}


void try_firstValue_Series ( unsigned board[9][9], 
                        vector< vector<int> > &solutions,
                        int &el_value, int &el_row, int &el_col, int &el_posInTab )
{
    for ( int element = 0; element < solutions.size(); element++ )
    {
        if ( solutions[element].size() == 2 )
        {
            el_value = solutions[element][0];
            el_posInTab = element;

            el_row = element / 9;
            if      ( element >= 72 ) { el_col = element - 72; }
            else if ( element >= 63 ) { el_col = element - 63; }
            else if ( element >= 54 ) { el_col = element - 54; }
            else if ( element >= 45 ) { el_col = element - 45; }
            else if ( element >= 36 ) { el_col = element - 36; }
            else if ( element >= 27 ) { el_col = element - 27; }
            else if ( element >= 18 ) { el_col = element - 18; }
            else if ( element >= 9 )  { el_col = element - 9;  }
            else                      { el_col = element - 0;  }

            // Insert element in the board
            board[el_row][el_col] = solutions[element][0];

            // Remove the solutions 
            solutions[element].pop_back();

            return;
        }
    }
}

void try_secondValue_Series ( unsigned board[9][9], 
                        vector< vector<int> > &solutions,
                        int &el_value, int &el_row, int &el_col, int &el_posInTab )
{
    int counter = 0;

    for ( int element = 0; element < solutions.size(); element++ )
    {
        if ( solutions[element].size() == 2 )
        {
            counter++;
            if ( counter == 2 )
            {
                el_value = solutions[element][0];
                el_posInTab = element;

                el_row = element / 9;
                if      ( element >= 72 ) { el_col = element - 72; }
                else if ( element >= 63 ) { el_col = element - 63; }
                else if ( element >= 54 ) { el_col = element - 54; }
                else if ( element >= 45 ) { el_col = element - 45; }
                else if ( element >= 36 ) { el_col = element - 36; }
                else if ( element >= 27 ) { el_col = element - 27; }
                else if ( element >= 18 ) { el_col = element - 18; }
                else if ( element >= 9 )  { el_col = element - 9;  }
                else                      { el_col = element - 0;  }

                // Insert element in the board
                board[el_row][el_col] = solutions[element][0];

                // Remove the solutions 
                solutions[element].pop_back();

                return;
            }
        }
    }
}

void try_firstValue ( unsigned board[9][9], 
                        vector< vector<int> > &solutions,
                        int &el_value, int &el_row, int &el_col, int &el_posInTab, int try_numberPossSol )
{
    for ( int element = 0; element < solutions.size(); element++ )
    {
        if ( solutions[element].size() == 2 )
        {
            el_value = solutions[element][try_numberPossSol];
            el_posInTab = element;

            el_row = element / 9;
            if      ( element >= 72 ) { el_col = element - 72; }
            else if ( element >= 63 ) { el_col = element - 63; }
            else if ( element >= 54 ) { el_col = element - 54; }
            else if ( element >= 45 ) { el_col = element - 45; }
            else if ( element >= 36 ) { el_col = element - 36; }
            else if ( element >= 27 ) { el_col = element - 27; }
            else if ( element >= 18 ) { el_col = element - 18; }
            else if ( element >= 9 )  { el_col = element - 9;  }
            else                      { el_col = element - 0;  }

            // Insert element in the board
            board[el_row][el_col] = solutions[element][0];

            // Remove the solutions 
            solutions[element].pop_back();

            return;
        }
    }
}

void try_secondValue ( unsigned board[9][9], 
                        vector< vector<int> > &solutions,
                        int &el_value, int &el_row, int &el_col, int &el_posInTab,
                        int temp )
{
    int counter = 0;

    for ( int element = 0; element < solutions.size(); element++ )
    {
        if ( solutions[element].size() == 2 )
        {
            counter++;
            if ( counter == 2 )
            {
                if ( solutions[element][0] != temp ) el_value = solutions[element][0];
                else el_value = solutions[element][1];
                
                
                el_posInTab = element;

                el_row = element / 9;
                if      ( element >= 72 ) { el_col = element - 72; }
                else if ( element >= 63 ) { el_col = element - 63; }
                else if ( element >= 54 ) { el_col = element - 54; }
                else if ( element >= 45 ) { el_col = element - 45; }
                else if ( element >= 36 ) { el_col = element - 36; }
                else if ( element >= 27 ) { el_col = element - 27; }
                else if ( element >= 18 ) { el_col = element - 18; }
                else if ( element >= 9 )  { el_col = element - 9;  }
                else                      { el_col = element - 0;  }

                // Insert element in the board
                board[el_row][el_col] = solutions[element][0];

                // Remove the solutions 
                solutions[element].pop_back();

                return;
            }
        }
    }
}

void
sodoku( unsigned board[9][9] ) {

    //cout << "Starting board: " << endl;
    //print_board( board ); cout << endl;
    // Create a vector which contains numbers already inserted
    // Rows
    vector<int> row1; vector<int> row2; vector<int> row3;
    vector<int> row4; vector<int> row5; vector<int> row6;
    vector<int> row7; vector<int> row8; vector<int> row9;
    // Cols
    vector<int> col1; vector<int> col2; vector<int> col3;
    vector<int> col4; vector<int> col5; vector<int> col6;
    vector<int> col7; vector<int> col8; vector<int> col9;
    // Subtables
    vector<int> tab1; vector<int> tab2; vector<int> tab3;
    vector<int> tab4; vector<int> tab5; vector<int> tab6;
    vector<int> tab7; vector<int> tab8; vector<int> tab9;    
    initial_configuration( board , 
                    row1, row2, row3, row4, row5, row6, row7, row8, row9,
                    col1, col2, col3, col4, col5, col6, col7, col8, col9,
                    tab1, tab2, tab3, tab4, tab5, tab6, tab7, tab8, tab9 );
    
    // Calculate all the possible solutions (numbers) that can stay in every free place
    vector< vector<int> > solutions;
    possible_solutions( board , 
                    row1, row2, row3, row4, row5, row6, row7, row8, row9,
                    col1, col2, col3, col4, col5, col6, col7, col8, col9,
                    tab1, tab2, tab3, tab4, tab5, tab6, tab7, tab8, tab9,
                    solutions );

    return;

    //cout << "size: " << solutions.size() << endl;

    //cout << "1) Possibili soluzioni: " << endl;
    //print_NotSquareMatrix( solutions ); cout << endl;

    // If the possible solutions for a place is one -> place the number
    int el_value; int el_row; int el_col; int el_posInTab; // Position of the element with only one possible solution
    check_poss_sol( board, solutions, el_value, el_row, el_col, el_posInTab );
    if ( el_value != 0 ) 
    {
        update_poss_sol( solutions, el_value, el_row, el_col, el_posInTab );
        //cout << "Sol aggiornate: " << endl;
        //print_NotSquareMatrix( solutions );
        //cout << "Board aggiornata: " << endl;
        //print_board( board );
        //cout << "È stato inserito il valore: " << el_value << " in posizione (" << el_row << ", " << el_col << ")" << " -> " << el_posInTab << endl; 
    }
    else { cout << "Check failed!" << endl; } cout << endl;

    // AGAIN
    el_value = 0; el_row = 0; el_col = 0; el_posInTab = 0;
    check_poss_sol( board, solutions, el_value, el_row, el_col, el_posInTab );
    if ( el_value != 0 ) 
    {
        update_poss_sol( solutions, el_value, el_row, el_col, el_posInTab );
        //cout << "Sol aggiornate: " << endl;
        //print_NotSquareMatrix( solutions );
        //cout << "Board aggiornata: " << endl;
        //print_board( board );
        //cout << "È stato inserito il valore: " << el_value << " in posizione (" << el_row << ", " << el_col << ")" << " -> " << el_posInTab << endl; 
    }
    else 
    { //cout << "Check failed!" << endl; 
    } //cout << endl;

    // AGAIN
    bool stop = false;
    while ( !stop )
    {
        el_value = 0; el_row = 0; el_col = 0; el_posInTab = 0;
        check_poss_sol( board, solutions, el_value, el_row, el_col, el_posInTab );
        //cout << "Valore trovato: " << el_value << endl;
        //cout << "size: " << solutions.size() << endl;
        if ( el_value != 0 ) 
        {
            update_poss_sol( solutions, el_value, el_row, el_col, el_posInTab );
            //cout << "Sol aggiornate: " << endl;
            //print_NotSquareMatrix( solutions );
            //cout << "Board aggiornata: " << endl;
            //print_board( board );
            //cout << "È stato inserito il valore: " << el_value << " in posizione (" << el_row << ", " << el_col << ")" << " -> " << el_posInTab << endl; 
        }
        else 
        { //cout << "Check failed!" << endl; 
        stop = true; 
        } // cout << endl;
    }

    // Complete?
    bool complete = false;
    check_complete( board, complete );
    if ( complete ) return;


    // VVVVVVVVV TO DO VVVVVVVVV

    // If it is not complete
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //  CONTINUE SEARCHING BY TRIAL AND ERROR
    //  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    for ( int try_method = 1; try_method <= 2; try_method++ )
    {
        if ( try_method == 1 )
        {
            //
            //  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<1>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
            //  - Try a new element whenever the program fails -
            //
            el_value = 0; el_row = 0; el_col = 0; el_posInTab = 0;
            try_firstValue_Series( board, solutions, el_value, el_row, el_col, el_posInTab );
            if ( el_value != 0 ) 
            {
                update_poss_sol( solutions, el_value, el_row, el_col, el_posInTab );
            }

            // AGAIN
            stop = false;
            while ( !stop )
            {
                el_value = 0; el_row = 0; el_col = 0; el_posInTab = 0;
                check_poss_sol( board, solutions, el_value, el_row, el_col, el_posInTab );
                if ( el_value != 0 ) 
                {
                    update_poss_sol( solutions, el_value, el_row, el_col, el_posInTab );
                }
                else {}
            }

            // Complete?
            check_complete( board, complete );
            if ( complete ) return;

            // If not
            el_value = 0; el_row = 0; el_col = 0; el_posInTab = 0;
            try_secondValue_Series( board, solutions, el_value, el_row, el_col, el_posInTab );
            if ( el_value != 0 ) 
            {
                update_poss_sol( solutions, el_value, el_row, el_col, el_posInTab );
            }    

            // AGAIN
            stop = false;
            while ( !stop )
            {
                el_value = 0; el_row = 0; el_col = 0; el_posInTab = 0;
                check_poss_sol( board, solutions, el_value, el_row, el_col, el_posInTab );
                if ( el_value != 0 ) 
                {
                    update_poss_sol( solutions, el_value, el_row, el_col, el_posInTab );
                }
                else {}
            }

            // Complete?
            check_complete( board, complete );
            if ( complete ) return;
        }

        if ( try_method == 2 )
        {
            //
            //  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<2>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
            //  - Try assigning two numbers at the same time -
            //
            for ( int attempt = 1; attempt <= 2; attempt++ )
            {
                el_value = 0; el_row = 0; el_col = 0; el_posInTab = 0;
                try_firstValue( board, solutions, el_value, el_row, el_col, el_posInTab, attempt );
                //cout << "Valore scelto: " << el_value << endl;
                update_poss_sol( solutions, el_value, el_row, el_col, el_posInTab );
                int temp = el_value;
                el_value = 0; el_row = 0; el_col = 0; el_posInTab = 0;
                try_secondValue( board, solutions, el_value, el_row, el_col, el_posInTab, temp );
                //cout << "Valore scelto: " << el_value << endl;
                //cout << "size: " << solutions.size() << endl;
                if ( el_value != 0 ) 
                {
                    update_poss_sol( solutions, el_value, el_row, el_col, el_posInTab );
                    //cout << "Sol aggiornate: " << endl;
                    //print_NotSquareMatrix( solutions );
                    //cout << "Board aggiornata: " << endl;
                    print_board( board );
                    //cout << "È stato inserito il valore: " << el_value << " in posizione (" << el_row << ", " << el_col << ")" << " -> " << el_posInTab << endl; 
                }

                // AGAIN
                stop = false;
                while ( !stop )
                {
                    el_value = 0; el_row = 0; el_col = 0; el_posInTab = 0;
                    check_poss_sol( board, solutions, el_value, el_row, el_col, el_posInTab );
                    //cout << "Valore trovato: " << el_value << endl;
                    //cout << "size: " << solutions.size() << endl;
                    if ( el_value != 0 ) 
                    {
                        update_poss_sol( solutions, el_value, el_row, el_col, el_posInTab );
                        //cout << "Sol aggiornate: " << endl;
                        //print_NotSquareMatrix( solutions );
                        //cout << "Board aggiornata: " << endl;
                        //print_board( board );
                        //cout << "È stato inserito il valore: " << el_value << " in posizione (" << el_row << ", " << el_col << ")" << " -> " << el_posInTab << endl; 
                    }
                    else 
                    { //cout << "Check failed!" << endl; 
                    stop = true; 
                    } //cout << endl;
                }

                // Complete?
                check_complete( board, complete );
                if ( complete ) return;
            }
        }
    }

        //
        //  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<3>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
        //  - TO DO -
        //


}

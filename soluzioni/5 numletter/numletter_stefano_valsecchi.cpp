#include <string>
#include <iostream>

using namespace std;




void primi20( string numero, string & risultato, int shift ){
	
	int const dim = numero.size();
	
	if( numero[ dim - 2 - 3 * shift ] != '1' ){
				
		switch( numero[dim - 1 - 3 * shift] ){

		case '0': 
			if( dim == 1 )
				risultato += "zero";
		  break;
		case '1':
			if( shift >= 2 &&  (( numero[ dim - 3 * shift - 2 ] == '0' && numero[ dim - 3 * shift - 3 ] == '0') || dim == 3 * shift + 1 ) )
				risultato += "un";
			else if( (dim == 4 || (dim > 6 && numero[dim - 5] == '0' && numero[ dim - 6 ] == '0') ) && shift == 1 )
				risultato += "";
			else
				risultato += "uno";
		  break;
		case '2': risultato += "due";
		  break;
		case '3': risultato += "tre";
		  break;
		case '4': risultato += "quattro";
		  break;
		case '5': risultato += "cinque";
		  break;
		case '6': risultato += "sei";
		  break;
		case '7': risultato += "sette";
		  break;
		case '8': risultato += "otto";
		  break;
		case '9': risultato += "nove";
		  break;
		default:
			cout << "ERRORE 10" << endl;
			return;
		
	  }
	}else{
		switch( numero[dim - 1 - 3 * shift] ){

		case '0': risultato += "dieci";
		  break;
		case '1': risultato += "undici";
		  break;
		case '2': risultato += "dodici";
		  break;
		case '3': risultato += "tredici";
		  break;
		case '4': risultato += "quattordici";
		  break;
		case '5': risultato += "quindici";
		  break;
		case '6': risultato += "sedici";
		  break;
		case '7': risultato += "diciassette";
		  break;
		case '8': risultato += "diciotto";
		  break;
		case '9': risultato += "diciannove";
		  break;
		default:
			cout << "ERRORE 20" << endl;
			return;
		
	  }
	}
	
}

void primi100( string numero, string & risultato, int shift ){
	int const dim = numero.size();
	
	if( numero[dim - 2 - 3 * shift] == '0' || dim < 2 + 3 * shift){
		primi20(numero, risultato, shift);
	}else{	
		switch( numero[dim - 2 - 3 * shift] ){
			case '0':
				break;
			case '1':
				break;
			case '2': 
				if( numero[dim - 1 - 3 * shift] != '1' && numero[dim - 1 - 3 * shift] != '8' )
					risultato += "venti";
				else
					risultato += "vent";
				break;
			case '3':
				if( numero[dim - 1 - 3 * shift] != '1' && numero[dim - 1 - 3 * shift] != '8' )
					risultato += "trenta";
				else
					risultato += "trent";
				break;
			case '4':
				if( numero[dim - 1 - 3 * shift] != '1' && numero[dim - 1 - 3 * shift] != '8' )
					risultato += "quaranta";
				else
					risultato += "quarant";
				break;
			case '5':
				if( numero[dim - 1 - 3 * shift] != '1' && numero[dim - 1 - 3 * shift] != '8' )
					risultato += "cinquanta";
				else
					risultato += "cinquant";
				break;
			case '6':
				if( numero[dim - 1 - 3 * shift] != '1' && numero[dim - 1 - 3 * shift] != '8' )
					risultato += "sessanta";
				else
					risultato += "sessant";
				break;
			case '7':
				if( numero[dim - 1 - 3 * shift] != '1' && numero[dim - 1 - 3 * shift] != '8' )
					risultato += "settanta";
				else
					risultato += "settant";
				break;
			case '8':
				if( numero[dim - 1 - 3 * shift] != '1' && numero[dim - 1 - 3 * shift] != '8' )
					risultato += "ottanta";
				else
					risultato += "ottant";
				break;
			case '9':
				if( numero[dim - 1 - 3 * shift] != '1' && numero[dim - 1 - 3 * shift] != '8' )
					risultato += "novanta";
				else
					risultato += "novant";
				break;
			default:
				cout << "ERRORE 100" << endl;
				return;
		}
		primi20( numero, risultato, shift );
	
	}
}

void primi1000( string numero, string & risultato, int shift ){
	int const dim = numero.size();
	if( numero[dim - 3 - 3 * shift] == '0' || dim < 3 + 3 * shift){
		primi100( numero, risultato, shift );
	}else{
		switch( numero[dim - 3 - 3 * shift] ){
		case '0':
		  break;
		case '1': risultato += "cento";
		  break;
		case '2': risultato += "duecento";
		  break;
		case '3': risultato += "trecento";
		  break;
		case '4': risultato += "quattrocento";
		  break;
		case '5': risultato += "cinquecento";
		  break;
		case '6': risultato += "seicento";
		  break;
		case '7': risultato += "settecento";
		  break;
		case '8': risultato += "ottocento";
		  break;
		case '9': risultato += "novecento";
		  break;
		default:
			cout << "ERRORE 1000" << endl;
			return;
		
	  }
	  primi100( numero, risultato, shift );
	}
}

void stampa( string numero, string & risultato ){
	
	
	int const dim = numero.size();
	int shift = (dim - 1) / 3;
	
	
	if( shift == 4 ){
		
		primi1000( numero, risultato, shift );
				
		if( numero[dim - 1 - 3 * shift] == '1' && dim == 13 ){
			risultato += " bilione";
		  if( numero[dim - 12] != '0' || numero[dim - 11] != '0' || numero[dim - 10] != '0' || numero[dim - 9] != '0' || numero[dim - 8] != '0' || numero[dim - 7] != '0' || numero[dim - 6] != '0' || numero[dim - 5] != '0' || numero[dim - 4] != '0' || numero[dim - 3] != '0' || numero[dim - 2] != '0' || numero[dim - 1] != '0' )
				risultato += " e ";
		}
		else if( (numero[dim - 1 - 3 * shift] != '0' || numero[dim - 2 - 3 * shift] != '0' || numero[dim - 3 - 3 * shift] != '0') ){
			risultato += " bilioni";
			if( numero[dim - 12] != '0' || numero[dim - 11] != '0' || numero[dim - 10] != '0' || numero[dim - 9] != '0' || numero[dim - 8] != '0' || numero[dim - 7] != '0' || numero[dim - 6] != '0' || numero[dim - 5] != '0' || numero[dim - 4] != '0' || numero[dim - 3] != '0' || numero[dim - 2] != '0' || numero[dim - 1] != '0' )
				risultato += " e ";
		}
		
		shift--;		
		
	}
	
	if( shift == 3 ){
		
		primi1000( numero, risultato, shift );
				
		if( numero[dim - 1 - 3 * shift] == '1' && (dim == 10 || ( dim >= 13 && numero[dim - 11] == '0' && numero[dim - 12] == '0' ) ) ){
			
			risultato += " miliardo";
			if( numero[dim - 9] != '0' || numero[dim - 8] != '0' || numero[dim - 7] != '0' || numero[dim - 6] != '0' || numero[dim - 5] != '0' || numero[dim - 4] != '0' || numero[dim - 3] != '0' || numero[dim - 2] != '0' || numero[dim - 1] != '0' )
				risultato += " e ";
		}
		else if( (numero[dim - 1 - 3 * shift] != '0' || numero[dim - 2 - 3 * shift] != '0' || numero[dim - 3 - 3 * shift] != '0') ){
			risultato += " miliardi";
			if( numero[dim - 9] != '0' || numero[dim - 8] != '0' || numero[dim - 7] != '0' || numero[dim - 6] != '0' || numero[dim - 5] != '0' || numero[dim - 4] != '0' || numero[dim - 3] != '0' || numero[dim - 2] != '0' || numero[dim - 1] != '0' )
				risultato += " e ";
		}
		
		shift--;
		
	}
	
	if( shift == 2 ){
		
		primi1000( numero, risultato, shift );
		
		if( numero[dim - 1 - 3 * shift] == '1' && (dim == 7 || ( dim >= 10 && numero[dim - 8] == '0' && numero[dim - 9] == '0' ) ) ){
			risultato += " milione";
			if( numero[dim - 6] != '0' || numero[dim - 5] != '0' || numero[dim - 4] != '0' || numero[dim - 3] != '0' || numero[dim - 2] != '0' || numero[dim - 1] != '0' )
				risultato += " e ";
		}
		else if( (numero[dim - 1 - 3 * shift] != '0' || numero[dim - 2 - 3 * shift] != '0' || numero[dim - 3 - 3 * shift] != '0') ){
			risultato += " milioni";
			if( numero[dim - 6] != '0' || numero[dim - 5] != '0' || numero[dim - 4] != '0' || numero[dim - 3] != '0' || numero[dim - 2] != '0' || numero[dim - 1] != '0' )
				risultato += " e ";
		}
		
		shift--;
		
	}
	
	if( shift == 1 ){
		
		
		primi1000( numero, risultato, shift );
		if( numero[dim - 1 - 3 * shift] == '1' && (dim == 4 || (dim > 6 && ( numero[dim - 2 - 3 * shift] == '0' && numero[dim - 3 - 3 * shift] == '0' ) ) ) ) risultato += "mille";
		else if( (numero[dim - 1 - 3 * shift] != '0' || numero[dim - 2 - 3 * shift] != '0' || numero[dim - 3 - 3 * shift] != '0') && dim >= 4 ) risultato += "mila";
		shift--;
		
	}
	primi1000( numero, risultato, shift );

}



void numeri_lettere( long num, string & risultato){
		
	int resto;
	string numero = "";
	
	if(num > 0){
		while( num > 0 ){
			resto = num % 10;
			
			switch(resto){
				case 0: numero = '0' + numero;
				  break;
				case 1: numero = '1' + numero;
				  break;
				case 2: numero = '2' + numero;
				  break;
				case 3: numero = '3' + numero;
				  break;
				case 4: numero = '4' + numero;
				  break;
				case 5: numero = '5' + numero;
				  break;
				case 6: numero = '6' + numero;
				  break;
				case 7: numero = '7' + numero;
				  break;
				case 8: numero = '8' + numero;
				  break;
				case 9: numero = '9' + numero;
				  break;
				default: cout << "ERRORE" << endl;
				  break;
			}
			
			num = ( num - resto ) / 10;
		}
	}
	else numero = "0";
	
	risultato = "";
	
	stampa( numero, risultato );

}

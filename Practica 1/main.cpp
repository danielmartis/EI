#include "tokenizador.h"
#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
	Tokenizador tk(",.·# ",false,false);
	string NombreArchivo = "prueba";
	string cad = "hola adios , , . #  prueba";
	list<string> ls;
	string anyadir;
	tk.Tokenizar(NombreArchivo);
	tk.Tokenizar(cad,ls);
	cout<<ls.size();
	list<string>::iterator itS;
	for(itS = ls.begin(); itS!=ls.end(); itS++){
	  cout<<(*itS)<<endl;
	}
	cout<<tk;
	
	return 0;
}

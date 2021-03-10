#include "tokenizador.h"
#include <iostream>
#include <list>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
	Tokenizador tk("@.-_ ",true,false);
	string NombreArchivo = "prueba";
	string cad = argv[1];
	//string mayac = "áéíóúàèìòùÁÉÍÓÚÀÈÌÒÙAEIOUÑ";
	list<string> ls;
	string anyadir;
	//tk.Tokenizar(NombreArchivo);
	tk.Tokenizar(cad,ls);
	//tk.Tokenizar(mayac,ls);
	//cout<<ls.size();
	list<string>::iterator itS;
	for(itS = ls.begin(); itS!=ls.end(); itS++){
	  cout<<(*itS)<<endl;
	}
	cout<<tk<<endl;
	
	return 0;
}

#include "tokenizador.h"
#include <iostream>
#include <list>
#include <string>
using namespace std;

int main() {
	Tokenizador tk;
	list<string> ls;
	string anyadir;
	tk.Tokenizar("hola,adios,p p1,dios,ula",ls);

	list<string>::iterator itS;
	for(itS = ls.begin(); itS!=ls.end(); itS++){
	  cout<<(*itS)<<endl;
	}
	cout<<tk;
	
	return 0;
}

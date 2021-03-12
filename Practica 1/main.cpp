#include "tokenizador.h"
#include <iostream>
#include <list>
#include <string>
#include <sys/resource.h>
using namespace std;



void numeros1(){
	string cad = "pal1 10.000,34 10,000.34 10.000.123.456.789.009,34 10,000,123,456,789,009.34 20.03 40,03 2005 10. 20, 10.0 20,0 La 20,12.456,7.8.9,";
}

void numeros2(){
	string cad = ".34 .56";
}

void numeros3(){
	string cad = "Pal1 10.35% 10,35% 23.000,3% 23,5$ 23.05$ 23,05$ 11.1$ 11.05$ 3.4% 4,3%";
}

void numeros4(){
	string cad = "pal1 10.00a 10.000.a.000 10/12/85 1 23E+10";
}

void numeros5(){
	string cad = ".34@@&,56";
}

void numG1(){
	numeros1();
	numeros2();
	numeros3();
	numeros4();
	numeros5();
}

double getcputime(void){
	struct timeval tim;
	struct rusage ru;
	getrusage(RUSAGE_SELF, &ru);
	tim = ru.ru_utime;
	double t =(double)tim.tv_sec + (double)tim.tv_usec / 1000000.0;
	tim = ru.ru_stime;
	t+=(double)tim.tv_sec + (double)tim.tv_usec/ 1000000.0;
	return t;
}
int main(int argc, char* argv[]) {
	Tokenizador tk("@.,&",true,false);
	string NombreArchivo = "prueba";
	string cad = "pal1&10.00@10.000&abc@10/12/85";
	long double aa = getcputime();
	//string mayac = "????????????????????AEIOU?";
	list<string> ls;
	string anyadir;
	//tk.Tokenizar(NombreArchivo);
	//tk.TokenizarListaFicheros("listaFicheros.txt");
	tk.Tokenizar(cad,ls);
	//cout<<ls.size();
	list<string>::iterator itS;
	for(itS = ls.begin(); itS!=ls.end(); itS++){
	  cout<<(*itS)<<endl;
	}
	cout<<tk<<endl;
	cout<< "Ha tardado "<<getcputime() - aa << " segundos"<<endl;
	return 0;
}

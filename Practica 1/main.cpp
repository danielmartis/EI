#include "tokenizador.h"
#include <iostream>
#include <list>
#include <string>
#include <sys/resource.h>
using namespace std;

void comprobar(list<string> obtenido, list<string> esperado, string caso){
	cout<<caso<<" ";
	if(obtenido == esperado){
		cout<<"correcto ";
	}
	else{
		cout<<"error ";
		list<string>::iterator itO,itC;
		cout<<"Obtenido: ";
		for(itO = obtenido.begin(); itO!= obtenido.end();itO++){
			cout<<*itO<<", ";
		}
		cout<<"\nEsperdo: ";
		for(itC = esperado.begin(); itC!=esperado.end();itC++){
			cout<<*itC<<", ";
		}
	}
	cout<<endl;
}


void numeros1(Tokenizador tk){
	string cad = "pal1 10.000,34 10,000.34 10.000.123.456.789.009,34 10,000,123,456,789,009.34 20.03 40,03 2005 10. 20, 10.0 20,0 La 20,12.456,7.8.9,";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,	{"pal1","10.000,34", "10,000.34","10.000.123.456.789.009,34","10,000,123,456,789,009.34","20.03","40,03","2005","10","20","10.0","20,0","La","20,12.456,7.8.9"},"numeros1");
}

void numeros2(Tokenizador tk){
	string cad = ".34 ,56";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"0.34","0,56"},"numeros2");
}

void numeros3(Tokenizador tk){
	string cad = "Pal1 10.35% 10,35$ 23.000,3% 23,5$ 23.05$ 23,05$ 11.1$ 11.05$ 3.4% 4,3%";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"Pal1","10.35","%","10,35","$","23.000,3","%","23,5","$","23.05","$","23,05","$","11.1","$","11.05","$", "3.4","%","4,3","%"},"numeros3");
}

void numeros4(Tokenizador tk){
	string cad = "pal1 10.00a 10.000.a.000 10/12/85 1,23E+10";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","10.00a","10.000.a.000","10/12/85", "1","23E+10"},"numeros4");
}

void numeros5(Tokenizador tk){
	string cad = "pal1&10.00@10.000&abc@10/12/85";
	list<string> obt, esp;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","10.00","10.000","abc@10/12/85"},"numeros5");
}

void numeros6(Tokenizador tk){
	string cad = ".34@@&,56";
	list<string> obt, esp;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"0.34","0,56"},"numeros6");

}

void numeros7(Tokenizador tk){
	string cad = "...10.000.a.000 ,,23.05 10/12/85 1,23E+10";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"0.10.000.a.000","0,23.05","10/12/85","1","23E+10"},"numeros7");
}

void numeros8(Tokenizador tk){
	string cad = "...10.000.000 ,,23.05 10/12/85 1,23E+10";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"0.10.000.000","0,23.05","10/12/85","1","23E+10"},"numeros8");
}


void numeros9(Tokenizador tk){
	string cad = ".3..2 4,,,,5 ..35";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"0.3","0.2","4","0,5","0.35"},"numeros9");
}

void num1(Tokenizador tk){
	numeros1(tk);
	numeros2(tk);
	numeros3(tk);
	numeros4(tk);
	numeros5(tk);
	numeros6(tk);
	numeros7(tk);
	numeros8(tk);
	numeros9(tk);
}

void guion1(Tokenizador tk){
	string cad = "MS-DOS p1 p2 UN-DOS-TRES";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"MS-DOS","p1","p2","UN-DOS-TRES"},"Guion1");
}

void guion2(Tokenizador tk){
	string cad = "pal1 -MS-DOS- p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","MS-DOS","p1","p2"},"Guion2");
}

void guion3(Tokenizador tk){
	string cad = "pal1 -MS-DOS- p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","MS-DOS","p1","p2"},"Guion3");
}

void guion4(Tokenizador tk){
	string cad = "pal1 MS-DOS--TRES p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","MS-DOS","TRES","p1","p2"},"Guion4");
}

void guion5(Tokenizador tk){
	string cad = "pal1 MS-DOS-TRES--- p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","MS-DOS-TRES","p1","p2"},"Guion5");
}
void guion6(Tokenizador tk){
	string cad = "pal1 MS-DOS#p3 p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","MS-DOS","p3","p1","p2"},"Guion6");
}
void guion7(Tokenizador tk){
	string cad = "pal1#MS-DOS#p3 p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","MS-DOS","p3","p1","p2"},"Guion7");;
}
void guion8(Tokenizador tk){
	string cad = "pal1#MS- DOS#p3 p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","MS","DOS","p3","p1","p2"},"Guion8");
}
void guion9(Tokenizador tk){
	string cad = "pal1#MS -DOS#p3 p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","MS","DOS","p3","p1","p2"},"Guion9");
}
void guion10(Tokenizador tk){
	string cad = "MS-DOS p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"MS-DOS","p1","p2"},"Guion10");
}

void guion11(Tokenizador tk){
	string cad = "pal1 -MS-DOS p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","-MS-DOS","p1","p2"},"Guion11");
}

void guion12(Tokenizador tk){
	string cad = "pal1 MS-DOS#p3 p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","MS-DOS#p3","p1","p2"},"Guion12");
}

void guion13(Tokenizador tk){
	string cad = "pal1#MS-DOS#p3 p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1#MS-DOS#p3","p1","p2"},"Guion13");
	
}

void guion14(Tokenizador tk){
	string cad = "pal1 -MS-DOS- p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","-MS-DOS-","p1","p2"},"Guion14");
	
}

void guion15(Tokenizador tk){
	string cad = "pal1 MS-DOS--TRES p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","MS-DOS--TRES","p1","p2"},"Guion15");
}

void guion16(Tokenizador tk){
	string cad = "pal1 MS-DOS-TRES--- p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","MS-DOS-TRES---","p1","p2"},"Guion16");
}


void gui1(Tokenizador tk){
	guion1(tk);
	guion2(tk);
	guion3(tk);
	guion4(tk);
	guion5(tk);
	guion6(tk);
	guion7(tk);
	guion8(tk);
	guion9(tk);
}

void gui2(Tokenizador tk){
	guion10(tk);
	guion11(tk);
	guion12(tk);
	guion13(tk);
	guion14(tk);
	guion15(tk);
	guion16(tk);
}
void url1(Tokenizador tk){
	string cad = "p0 http://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013&newspaper=catedraTelefonicaUA@iuii.ua.es p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"p0", "http://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013&newspaper=catedraTelefonicaUA@iuii.ua.es", "p1", "p2"},"Url1");
}
void url2(Tokenizador tk){
	string cad = "p0 http://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013&newspaper=catedraTelefonicaUA@iuii.ua.es p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"p0", "http://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013&newspaper=catedraTelefonicaUA@iuii.ua.es", "p1", "p2"},"Url2");
}
void url3(Tokenizador tk){
	string cad = "p0 http://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013&newspaper=catedraTelefonicaUA@iuii.ua.es p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"p0", "http://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013&newspaper=catedraTelefonicaUA@iuii.ua.es", "p1", "p2"},"Url3");
}

void url4(Tokenizador tk){
	string cad = "p0 http://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013&newspaper=catedraTelefonicaUA@iuii.ua.es p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"p0", "http://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013&newspaper=catedraTelefonicaUA@iuii.ua.es", "p1", "p2"},"Url4");
}

void url5(Tokenizador tk){
	string cad = "p0 hhttp://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013 p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"p0", "hhttp:", "intime.dlsi.ua.es:8080","dossierct","index.jsp?lang=es","status=probable","date=22-01-2013", "p1", "p2"},"Url5");
}

void url6(Tokenizador tk){
	string cad = "p0 Http://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013 p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"p0", "Http:", "intime.dlsi.ua.es:8080","dossierct","index.jsp?lang=es","status=probable","date=22-01-2013", "p1", "p2"},"Url7");
}
void url7(Tokenizador tk){
	string cad = "http:////ab.";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"http:////ab."},"Url6");
}

void url8(Tokenizador tk){
	string cad = "p0 Http://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013 p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"p0", "http://intime.dlsi.ua.es:8080/dossierct/index.jsp?lang=es&status=probable&date=22-01-2013", "p1", "p2"},"Url8");
}
void urls1(Tokenizador tk){
	url1(tk);
}
void urls2(Tokenizador tk){
	url2(tk);
}

void urls3(Tokenizador tk){
	url3(tk);
}
void urls4(Tokenizador tk){
	url4(tk);
}
void urls5(Tokenizador tk){
	url5(tk);
	url6(tk);
	url7(tk);
}
void urls6(Tokenizador tk){
	url8(tk);
}


void em1(Tokenizador tk){
	string cad = "catedraTelefonicaUA@iuii.ua.es p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"catedraTelefonicaUA@iuii.ua.es", "p1", "p2"},"E-mail1");
}

void em2(Tokenizador tk){
	string cad = "catedraTelefonicaUA@@iuii.ua.es p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"catedraTelefonicaUA","iuii.ua.es", "p1", "p2"},"E-mail2");
}

void em3(Tokenizador tk){
	string cad = "pal1 @iuii.ua.es p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","iuii.ua.es", "p1", "p2"},"E-mail3");
}

void em4(Tokenizador tk){
	string cad = "pal1 cat@iuii.ua.es@cd p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","cat","iuii.ua.es","cd", "p1", "p2"},"E-mail4");
}

void em5(Tokenizador tk){
	string cad = "pal1 cat@iuii@cd.ua.es p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","cat","iuii@cd.ua.es", "p1", "p2"},"E-mail5");
}


void ems1(Tokenizador tk){
	em1(tk);
	em2(tk);
	em3(tk);
	em4(tk);
	em5(tk);
}

void em6(Tokenizador tk){
	string cad = "catedraTelefonicaUA@iuii.ua.es p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"catedraTelefonicaUA@iuii.ua.es", "p1", "p2"},"E-mail6");
}
void em7(Tokenizador tk){
	string cad = "pal1 @iuii.ua.es p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","@iuii.ua.es", "p1", "p2"},"E-mail7");
}
void em8(Tokenizador tk){
	string cad = "pal1&@iuii.ua.es p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","@iuii.ua.es", "p1", "p2"},"E-mail8");
}
void em9(Tokenizador tk){
	string cad = "pal1&catedra@iuii.ua.es p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","catedra@iuii.ua.es", "p1", "p2"},"E-mail9");
}
void em10(Tokenizador tk){
	string cad = "pal1 cat@iuii.ua.es@cd p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"pal1","cat@iuii.ua.es@cd", "p1", "p2"},"E-mail10");
}

void ems2(Tokenizador tk){
	em6(tk);
	em7(tk);
	em8(tk);
	em9(tk);
	em10(tk);
}

void em11(Tokenizador tk){
	string cad = "-catedraTelefonicaUA@iuii.ua.es @p1 p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"catedraTelefonicaUA@iuii.ua.es","p1","p2"},"E-mail11");
}

void em12(Tokenizador tk){
	string cad = "@p2@@dot.com@p1-p2";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"p2","dot.com", "p1-p2"},"E-mail12");
}

void em13(Tokenizador tk){
	string cad = "a@a- b@- c@c--c d@d e@-e f@--";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"a@a","b","c@c","c","d@d","e","e","f"},"E-mail13");
}

void ems3(Tokenizador tk){
	em11(tk);
	em12(tk);
	em13(tk);
}

void acro1(Tokenizador tk){
	string cad = "U.S.A p1 e.g. p2. La";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"U.S.A","p1", "e.g","p2","La"},"Acro1");
}

void acro2(Tokenizador tk){
	string cad = "U..S.A p1 e..g. p2. La";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"U","S.A","p1", "e","g","p2","La"},"Acro2");
}

void acro3(Tokenizador tk){
	string cad = "U.S....A.BC.D";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"U.S","A.BC.D"},"Acro3");
}

void acro4(Tokenizador tk){
	string cad = "...U.S.A p1 e..g. p2. La";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"U.S.A","p1", "e","g","p2","La"},"Acro4");
}

void acro5(Tokenizador tk){
	string cad = "...U.S.A... p1 e..g. p2. La";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"U.S.A","p1", "e","g","p2","La"},"Acro5");
}

void acro6(Tokenizador tk){
	string cad = "...U.S.A@p1 e..g-p2. La";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"U.S.A","p1", "e","g-p2","La"},"Acro6");
}

void acro7(Tokenizador tk){
	string cad = "Hack.4.Good p1";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"Hack.4.Good","p1"},"Acro7");
}

void acro8(Tokenizador tk){
	string cad = "...U.S.A... p1 e..g. p2. La";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"U.S.A","p1", "e","g","p2","La"},"Acro8");
}

void acros1(Tokenizador tk){
	acro1(tk);
	acro2(tk);
	acro3(tk);
	acro4(tk);
	acro5(tk);
	acro6(tk);
	acro7(tk);
	acro8(tk);
}

void acro9(Tokenizador tk){
	string cad = "U.S.A .U.S.A .p1 p1 e.g. p2. La";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"U.S.A",".U.S.A", ".p1","p1","e.g.","p2.","La"},"Acro9");
}

void acro10(Tokenizador tk){
	string cad = "U..S.A p1 e..g. p2. La";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"U..S.A","p1", "e..g.","p2.","La"},"Acro10");
}

void acro11(Tokenizador tk){
	string cad = "...U.S.A p1 e..g. p2. La";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"...U.S.A","p1", "e..g.","p2.","La"},"Acro11");
}

void acro12(Tokenizador tk){
	string cad = "a&U.S.A p1 e.g. p2. La";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"a&U.S.A","p1", "e.g.","p2.","La"},"Acro12");
}

void acros2(Tokenizador tk){
	acro9(tk);
	acro10(tk);
	acro11(tk);
	acro12(tk);
}

void acro13(Tokenizador tk){
	string cad = "a&U.S.A p1 e.g. p2. La";
	list<string> obt;
	tk.Tokenizar(cad,obt);
	comprobar(obt,{"a","U.S.A","p1", "e.g.","p2.","La"},"Acro13");
}

void acros3(Tokenizador tk){
	acro13(tk);
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
	Tokenizador tk("-#",true,false);
	string NombreArchivo = "prueba";
	long double aa = getcputime();
	
	//GUIONES
	/*gui1(tk);
	tk.DelimitadoresPalabra("/ ");
	gui2(tk);*/

	//URLS
	/*tk.DelimitadoresPalabra(",");
	urls1(tk);
	tk.DelimitadoresPalabra("@");
	urls2(tk);
	tk.DelimitadoresPalabra("/ ");
	urls3(tk);
	tk.DelimitadoresPalabra("_:/.?&-=#@");
	urls4(tk);
	tk.DelimitadoresPalabra("/&");
	urls5(tk);
	tk.PasarAminuscSinAcentos(true);
	urls6(tk);
	tk.PasarAminuscSinAcentos(false);*/

	//E-MAILS.
	/*tk.DelimitadoresPalabra("@.&");
	ems1(tk);
	tk.DelimitadoresPalabra("&.");
	ems2(tk);
	tk.DelimitadoresPalabra("@.-_");
	ems3(tk);*/

	//ACRONIMOS
	tk.DelimitadoresPalabra("@.&");
	acros1(tk);
	tk.DelimitadoresPalabra("");
	acros2(tk);
	tk.DelimitadoresPalabra("&");
	acros3(tk);
	//NUMEROS
	//num1(tk);
	

	cout<<tk<<endl;
	cout<< "Ha tardado "<<getcputime() - aa << " segundos"<<endl;
	return 0;
}

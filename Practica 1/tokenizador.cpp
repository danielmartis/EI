#include "tokenizador.h"
#include <fstream>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#include <regex>
using namespace std;
// Falta detectar si hay delimitadores repetidos.
Tokenizador::Tokenizador (const string& delimitadoresPalabra, const bool& kcasosEspeciales, const bool& minuscSinAcentos){
    casosEspeciales = kcasosEspeciales;
    //delimiters.reserve(delimitadoresPalabra.size());
    AnyadirDelimitadoresPalabra(delimitadoresPalabra);
    pasarAminuscSinAcentos = minuscSinAcentos;
}

Tokenizador::Tokenizador (const Tokenizador& tk){
    this->casosEspeciales = tk.casosEspeciales;
    this->delimiters = tk.delimiters;
    this->pasarAminuscSinAcentos = tk.pasarAminuscSinAcentos;
}

Tokenizador::Tokenizador (){
    casosEspeciales = true;
    delimiters = ",;:.-/+*\\ '\"{}[]()<>?!??&#=\t\n\r@";
    pasarAminuscSinAcentos = false;
}

Tokenizador::~Tokenizador () {
    delimiters = "";
}

Tokenizador& Tokenizador::operator= (const Tokenizador& tk) {
    this->casosEspeciales = tk.casosEspeciales;
    this->delimiters = tk.delimiters;
    this->pasarAminuscSinAcentos = tk.pasarAminuscSinAcentos;
    return *this;
}

// Falta detectar si hay casos especiales activados y actuar en consecuencia � �
void Tokenizador::Tokenizar (string& str, list<string>& tokens) const{
    string::size_type lastPos;
    string::size_type pos;
    string delimitersEspeciales = delimiters;
    string prueba;
    if(pasarAminuscSinAcentos){
        QuitarAcentosMayus(str);
    }
    //delimitersEspeciales.resize(delimitersEspeciales.size()+1, ' ');
    if(!casosEspeciales){
        lastPos = str.find_first_not_of(delimiters,0);
        pos = str.find_first_of(delimiters,lastPos);
    }
    else{
        lastPos = str.find_first_not_of(delimiters,0);
        pos = str.find_first_of(delimitersEspeciales,lastPos);
    }
    //cout<<"Pos: "<<pos<<"LastPos: "<<lastPos;
    while(string::npos != pos || string::npos != lastPos){
        if(casosEspeciales){
            //cout<<"Pos: " <<pos;
            DetectarCasosEspeciales(str,pos, lastPos, delimitersEspeciales);
            //cout<<"Pos: " << pos;
        }
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        if(!casosEspeciales){
            lastPos = str.find_first_not_of(delimiters,pos);
            pos = str.find_first_of(delimiters,lastPos);
        }
        else{
            lastPos = str.find_first_not_of(delimiters,pos);
            pos = str.find_first_of(delimitersEspeciales ,lastPos);
        }

    }
}
// Llama a Tokenizar, por lo que no hace falta detectar casos especiales.
bool Tokenizador::Tokenizar(const string& NomFichEntr, const string& NomFichSal) const{
    ifstream i;
    ofstream f;
    string cadena;
    list<string> tokens;
    i.open(NomFichEntr.c_str());
    if(!i){
        cerr << "ERROR: No existe el fichero: " << NomFichEntr << endl;
        return false;
    }
    else {
        while(!i.eof()){
            cadena="";
            getline(i,cadena);
            if(cadena.length()!= 0){
                Tokenizar(cadena,tokens);
            }
        }
    }
    i.close();

    f.open(NomFichSal.c_str());
    list<string>::iterator itS;
    for(itS= tokens.begin(); itS!=tokens.end(); itS++){
        f<< (*itS) << endl;
    }
    f.close();
    return true;
}
// LLama a Tokenizar, por lo que no hace falta detectar casos especiales.
bool Tokenizador::Tokenizar(const string& NomFichEntrada) const{
    string NomFichSalida;
    NomFichSalida = NomFichEntrada + ".tk";
    return Tokenizar(NomFichEntrada, NomFichSalida);
}

// LLama a tokenizar, por lo que no hace falta detectar casos especiales
bool Tokenizador::TokenizarListaFicheros(const string& NomFichEntrada) const{
    string NomFichSalida;
    ifstream i;
    string cadena;
    bool devolver = true;
    i.open(NomFichEntrada.c_str());
    if(!i){
        cerr<<"EROR: no se ha podido abrir el archivo";
        return false;
    }
    else {
        while(!i.eof()){
            cadena="";
            getline(i,cadena);
            if(cadena.length()!=0){
                if(!Tokenizar(cadena)){
                    devolver = false;
                }
            }
        }
    }
    return devolver;
}


// Comprobar una vez implementado TokenizarListaFicheros.
bool Tokenizador::TokenizarDirectorio(const string& dirAIndexar) const {
    struct stat dir;
    int err=stat(dirAIndexar.c_str(), &dir);
    if(err==-1 || !S_ISDIR(dir.st_mode))
        return false;
    else {
        string cmd ="find "+dirAIndexar+" -follow |sort > .list_fich";
        system(cmd.c_str());
        return TokenizarListaFicheros(".lista_fich");
    }
}
// Comprobar si nuevoDelimiters contiene delimitadores repetidos �.
void Tokenizador::DelimitadoresPalabra (const string& nuevoDelimiters) {
    delimiters = "";
    AnyadirDelimitadoresPalabra(nuevoDelimiters);
}
// Habr? que comprobar si hay delimitadores repetidos.
void Tokenizador::AnyadirDelimitadoresPalabra (const string& nuevoDelimiters){
    for(int i = 0; i<nuevoDelimiters.length();i++){
        if(delimiters.find_first_of(nuevoDelimiters[i]) != string::npos){
        }
        else{
            delimiters.resize(delimiters.size()+1,nuevoDelimiters[i]);
        }
    }
}

string Tokenizador::DelimitadoresPalabra() const {
    return delimiters;
}

void Tokenizador::CasosEspeciales(const bool& nuevosCasosEspeciales){
    casosEspeciales = nuevosCasosEspeciales;
}

bool Tokenizador::CasosEspeciales () {
    return casosEspeciales;
}

void Tokenizador::PasarAminuscSinAcentos (const bool& nuevoPasarAminuscSinAcentos){
    pasarAminuscSinAcentos = nuevoPasarAminuscSinAcentos;
}

bool Tokenizador::PasarAminuscSinAcentos (){
    return pasarAminuscSinAcentos;
}

void Tokenizador::DetectarCasosEspeciales(const string& t,string::size_type& p, string::size_type& pi, string& de) const {
    string::size_type nuevaPos = p;
    int estado = 0;
    string::size_type a,b;
    bool detener = false;
    int arroba = 0;
    bool coma = false;
    if(t.substr(pi,4).compare("ftp:") == 0|| t.substr(pi,5).compare("http:") == 0|| t.substr(pi,6).compare("https:") == 0){
        if(t[p] == '_' || t[p] == ':' || t[p] == '/' || t[p] == '.' || t[p] == '?' || t[p] == '&' || t[p] == '-' || t[p] == '=' || t[p] == '#' || t[p] == '@'){ 
            estado = 1;
        }
    }
    else if(t[p] == '.' || t[p] == ','){
        estado = 2;
    }
    else if(t[p] == '@'){
        estado = 3;
        arroba = 1;
    }
    else if(t[p] == '-'){
        estado = 4;
    }
    else if(t[p] == '@'){
        estado = 5;
    }
    switch(estado){
        case 1:
            //cout<<"Hola";
            do{
                p = t.find_first_of(de,p+1);
            }while((t[p] == '_' || t[p] == ':' || t[p] == '/' || t[p] == '.' || t[p] == '?' || t[p] == '&' || t[p] == '-' || t[p] == '=' || t[p] == '#' || t[p] == '@') && p != string::npos); 
            //cout<<p<<" ";
            if(p != string::npos){
                if(t.substr(pi,p-pi).compare("ftp:") == 0|| t.substr(pi,p-pi).compare("http:") == 0|| t.substr(pi,p-pi).compare("https:") == 0){
                    p = p-1;;
                }
            }
            else{
                //cout<<p<<" ";
                //cout<<t.size()-pi;
                //cout<<t.substr(t.size()-pi)<<" ";
                if(t.size()-pi == 4 && t.substr(pi,4).compare("ftp:") == 0){
                    p =pi+3;
                }
                if(t.size() - pi == 5 && t.substr(pi,5).compare("http:") == 0){
                    p =pi+4;
                }
                if(t.size()-pi == 6 && t.substr(pi,6).compare("https:") == 0){
                    p = pi+5;
                }
            }
            break;

        case 2:
            break;

        case 3:
            b = a = p;
            do{
                a = t.find_first_of(de,a+1);
                if(t[a] == '@'){
                    arroba++;
                }
                if(arroba == 2){
                    break;
                }
                if(a - b == 1){
                    p = b;
                    detener = true;
                }
                else if(t[a] != '.' && t[a] != '-' && t[a] != '_' && t[a] != '@'){
                    p = a;
                    detener = true;
                }
                b = a;

            }while(a != string::npos && arroba<2 && !detener && (t[a] == '.' || t[a] == '-' || t[a] == '_' || t[a] =='@'));
            
            break;

        case  4:
            //cout<<"Hola";
            //p = t.find_first_of(delimiters + " ", pi);
            //cout<<"Valor actual: " << p << "Caracter: " << t[p];
            do{
                //string::size_type a;
                //cout<<p;
                a = t.find_first_of(de,p+1);
                //cout<<"p: " <<p;
                //cout<<"Nuevo valor: " << a<<endl;
                if(a-p == 1 || t[a] != '-'){
                    detener = true;
                    if(t[a] == '-'){
                        p = a-1;
                    }
                    else{
                        p = a;
                    }
                }
                else{
                    a = p = t.find_first_of(de,a);
                }
            }while(!detener);
            if(p == string::npos){
                if(t[t.size()-1] == '-'){
                    p = t.size()-1;
                }
            }
            //p = nuevaPos;
            break;

        case 5:
            break;
    }
}
//�
void Tokenizador::QuitarAcentosMayus(string& c) const{
    //cout<<(int) 'o';
    for(int i = 0; i<c.size(); i++){
        if(c[i] == '�' || c[i] == '�' || c[i] == '�' || c[i] == '�'){
            c.replace(i,1,"o");
        }
        else if(c[i] == '�' || c[i] == '�' || c[i] == '�' || c[i] == '�'){
            c.replace(i,1,"e");
        }
        else if(c[i] == '�' || c[i] == '�' || c[i] == '�' || c[i] == '�'){
            c.replace(i,1,"a");
        }
        else if(c[i] == '�' || c[i] == '�' || c[i] == '�' || c[i] == '�'){
            c.replace(i,1,"i");
        }
        else if(c[i] == '�' || c[i] == '�' || c[i] == '�' || c[i] == '�'){
            c.replace(i,1,"u");
        }
        if((c[i]>='A' && c[i] <= 'Z') || c[i] == '�'){
            c[i] += 32;
        }
    }
}

void Tokenizador::Minusculas(string& t) const{
    for(int i = 0; i<t.size(); i++){

    }
}
ostream& operator<<(ostream& os, const Tokenizador& tk){
    os<<"Delimiters: "<<tk.delimiters << " TRATA CASOS ESPECIALES: " << tk.casosEspeciales << " PASAR A MINUSCULAS Y SIN ACENTOS: " << tk.pasarAminuscSinAcentos;
    return os;
}
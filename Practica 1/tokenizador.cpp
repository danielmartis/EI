#include "tokenizador.h"
#include <fstream>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
using namespace std;
// Falta detectar si hay delimitadores repetidos.
Tokenizador::Tokenizador (const string& delimitadoresPalabra, const bool& kcasosEspeciales, const bool& minuscSinAcentos){
    casosEspeciales = kcasosEspeciales;
    delimiters = delimitadoresPalabra;
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

// Falta detectar si hay casos especiales activados y actuar en consecuencia ï¿½ ï¿½
void Tokenizador::Tokenizar (const string& str, list<string>& tokens) const{
    string::size_type lastPos = str.find_first_not_of(delimiters,0);
    string::size_type pos = str.find_first_of(delimiters,lastPos);
    int nuevaPos; 
    /*if(casosEspeciales){
        nuevaPos = DetectarCasosEspeciales(str,lastPos,pos);
        if(nuevaPos != -1) {
            pos = nuevaPos;
        }
    }
    */
    while(string::npos != pos || string::npos != lastPos){
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters,pos);
        pos = str.find_first_of(delimiters,lastPos);
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
// Comprobar si nuevoDelimiters contiene delimitadores repetidos ñ.
void Tokenizador::DelimitadoresPalabra (const string& nuevoDelimiters) {
    delimiters = nuevoDelimiters;
}
// Habr? que comprobar si hay delimitadores repetidos.
void Tokenizador::AnyadirDelimitadoresPalabra (const string& nuevoDelimiters){
    for(int i = 0; i<nuevoDelimiters.length();i++){
        if(delimiters.find_first_of(nuevoDelimiters[i]) != string::npos){
            break;
        }
        else{
            delimiters += nuevoDelimiters[i];
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

string::size_type Tokenizador::DetectarCasosEspeciales(const string& t,string::size_type& p, string::size_type& pi) const {
    /*int nuevaPos = -1;
    switch(t){
        case ":":
            if(strcmp(t.substr(pi,4), "ftp:") == 0 || strcmp(t.substr(pi,5),"http:") || strcmp(t.substr(pi,6),"https:")) {
                do {
                   nuevaPos = find_first_of(delimiters + " ", 0);
                }while(t[nuevaPos] != "_" && t[nuevaPos] != ":" && t[nuevaPos] != "/" && t[nuevaPos] != "." && t[nuevaPos] != "?" && t[nuevaPos] != "&" && t[nuevaPos] != "-" && t[nuevaPos] != "=" && t[nuevaPos] != "#" && t[nuevaPos] != "@" );

            }
            break;

        case ".":
            break;

        case ",":
            break;

        case  "-":
            if(t.find_first_of(delimiters + " ",pi-1) >= pi && t.find_first_of(delimiters + " ",pi+1) >= pi+1)){
                nuevaPos = find_first_of(delimiters, pi+1);
            }
            break;

        case "@":
            break;
    }
    return nuevaPos;
    */
}

ostream& operator<<(ostream& os, const Tokenizador& tk){
    os<<"Delimiters: "<<tk.delimiters << " TRATA CASOS ESPECIALES: " << tk.casosEspeciales << " PASAR A MINUSCULAS Y SIN ACENTOS: " << tk.pasarAminuscSinAcentos;
    return os;
}
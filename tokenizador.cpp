#include "tokenizador.h"
#include <iostream>
using namespace std;

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
    delimiters = ",;:.-/+*\\ '\"{}[]()<>¡!¿?&#=\t\n\r@";
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


void Tokenizador::Tokenizar (const string& str, list<string>& tokens) const{
    string::size_type lastPos = str.find_first_not_of(delimiters,0);
    string::size_type pos = str.find_first_of(delimiters,lastPos);

    while(string::npos != pos || string::npos != lastPos){
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters,pos);
        pos = str.find_first_of(delimiters,lastPos);
    }
}

bool Tokenizador::Tokenizar(const string& i, const string& f) const{

}

bool Tokenizador::Tokenizar(const string& i) const{

}

bool Tokenizador::TokenizarListaFicheros(const string& i) const{

}

bool Tokenizador::TokenizarDirectorio(const string& i) const {

}

void Tokenizador::DelimitadoresPalabra (const string& nuevoDelimiters) {
    delimiters = nuevoDelimiters;
}

void Tokenizador::AnyadirDelimitadoresPalabra (const string& nuevoDelimiters){

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

ostream& operator<<(ostream& os, const Tokenizador& tk){
    os<<"Delimiters: "<<tk.delimiters;
    return os;
}
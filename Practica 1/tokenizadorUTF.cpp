#include "tokenizador.h"
#include <iostream>
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

// Falta detectar si hay casos especiales activados y actuar en consecuencia ñ á
void Tokenizador::Tokenizar (const string& str, list<string>& tokens) const{
    string::size_type lastPos = str.find_first_not_of(delimiters,0);
    string::size_type pos = str.find_first_of(delimiters,lastPos);

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
    for(itS= tokens.begn(); itS!=tokens.end(); itS++){
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

bool Tokenizador::TokenizarListaFicheros(const string& i) const{

}
// Comprobar una vez implementado TokenizarListaFicheros.
bool Tokenizador::TokenizarDirectorio(const string& dirAIndexar) const {
    struct stat dir;
    int err=stat(dirAIndexar.c_str(), &dir);
    if(err==-1 || !S_ISDIR(dir.st_mode))
        return false;
    else {
        string cmd ="find "+dirAindexar+" -follow |sort > .list_fich";
        system(cmd.c_str());
        return TokenizarListaFicheros(".lista_fich");
    }
}
// Comprobar si nuevoDelimiters contiene delimitadores repetidos.
void Tokenizador::DelimitadoresPalabra (const string& nuevoDelimiters) {
    delimiters = nuevoDelimiters;
}
// Habr? que comprobar si hay delimitadores repetidos.
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
    os<<"Delimiters: "<<tk.delimiters << " TRATA CASOS ESPECIALES: " << casosEspeciales << " PASAR A MINUSCULAS Y SIN ACENTOS: " << pasarAminuscSinAcentos;
    return os;
}
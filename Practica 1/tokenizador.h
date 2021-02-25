#include <string>
#include <list>

using namespace std;
class Tokenizador {
        friend ostream& operator<<(ostream&, const Tokenizador&);
        // cout << "DELIMITADORES: " <<delimiters << " TRATA CASOS ESPECIALES: " << casosEspeciales << " PASAR A MINUSCULAS Y SIN ACENTOS: " << pasarAminuscSinAcentos;

    public:
        Tokenizador (const string& delimitadoresPalabra, const bool& kcasosEspeciales, const bool& minuscSinacentos);
        // Inicializa delimiters a delimitadoresPalabra filtrando que no se introduzcan delimitadores repetidos (de izquierda a derecha); casosEspeciales a kcasosEspeciales; pasarAminuscSinAcentos a minuscSinacentos

        Tokenizador (const Tokenizador&);

        Tokenizador ();
        // Delimiters =",;:.-/+*\\ '\"{}[]()<>�!�?#=\t\n\r@"; casosEspeciales a true; pasarAminuscSinAcentos a false

        ~Tokenizador (); //Pone delimiters=""

        Tokenizador& operator= (const Tokenizador&);

        void Tokenizar (const string& str, list<string>& tokens) const;
        // Tokeniza str devolviendo el resultado en tokens. La lista tokens se vaciar� antes de almacenar el resultado de la tokenizaci�n.

        bool Tokenizar (const string& i, const string& f) const;
        // Tokeniza el fichero i guardando la salida en el fichero f (una palabra por linea). Devuelve true si se realiza la tokenizaci�n; false en caso contrario enviando a cerr el mensaje correspondiete (ej. no existe el fichero i)

        bool Tokenizar (const string& i) const;
        // Tokeniza el fichero i guardando la slaida en un fichero de nombre i a�adiendole la extensi�n .tk (sin eliminar previamente la extensi�n de i, por ejemplo, del archivo pp.txt se generari�a el resultado en pp.txt.tk)

        bool TokenizarListaFicheros (const string& i) const;
        // Tokeniza el fichero i que contiene un nombre de fichero por linea guardando la salida en ficheros (uno por cada linea de i) cuyo nombre sera el leido en i a�adiendole extensi�n .tk, y que contendr� una palabra en cada l�nea del fichero leido en i. Devolvera true si se realiza la tokenizaci�n de forma correcta de todos los archivos que contiene i; devolver� false en caso contrario enviando a cerr el mensaje correspondiente (ej. que no existe el archivo i, que sea un directerio; no se interrumpe la ejecuci�n si hay alg�n achivo en i que no exista)

        bool TokenizarDirectorio (const string& i) const;
        // Tokeniza todos los archivos que contenga i, incluyendo los subdirectorios, guardando la salida en ficheros cuyo nombre ser� el de entrada a�adi�ndole extensi�n .tk, y que contendr� una palabra en cada linea del fichero. Devolver� true si se eraliza la tokenizaci�n de forma correcta de todos los archivos; devolver� false en caso contrario enviando a cerr el mensaje correspondiente (p.ej que no exista el directorio i, o los ficheros que no se hayan podido tokenizar)

        void DelimitadoresPalabra (const string& nuevoDelimiters);
        // Cambia "delimiters" por "nuevoDelimiters" comprobando que no hayan delimitadores repetidos (de izquierda a derecha), en cuyo caso se eliminar�an los que hayan sido repetidos.

        void AnyadirDelimitadoresPalabra (const string& nuevoDelimiters);
        // A�ade al final de "delimiters" los nuevos delimitadores que aparezcanen "nuevoDelimiters" (no repetidos)

        string DelimitadoresPalabra() const;
        // Devuelve delimiters
        void CasosEspeciales (const bool& nuevosCasosEspeciales);
        // Cambia la variable privada "casosEspeciales"

        bool CasosEspeciales ();
        // Devuelve el contenido de la variable privada "casosEspeciales"

        void PasarAminuscSinAcentos (const bool& nuevoPasarAminuscSinAcentos);
        // Cambia la variable privada "pasarAminuscSinAcentos". Atenci�n al formato de codificaci�n del corpus. Se utilizar� el formato actual ISO-8859.

        bool PasarAminuscSinAcentos ();
        // Devuelve el contenido de la variable privada "pasarAmniuscSinAcentos"

        string::size_type DetectarCasosEspeciales(const string& t, string::size_type& p, string::size_type& pi) const;

    private:
        string delimiters;
        // Delimitadores de t�rminos. Aunque se modifique la forma de almacenamiento itnerna para mejorar la eficiencia, este campo debe peranecer para indicar el orden en que se introdujeron los delimitadores.

        bool casosEspeciales;
        // Si true detctar� palabras compuestas y casos especiales. Sino, trabajar� al igual que el algoritmo prupuesto en la secci�n "Versi� ndel tokenizador vista en clase"

        bool pasarAminuscSinAcentos;
        // Si true pasar� el token a min�sculas y quitar� acentos, antes de realizar la tokenizac�n.
};
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
        // Delimiters =",;:.-/+*\\ '\"{}[]()<>¡!¿?#=\t\n\r@"; casosEspeciales a true; pasarAminuscSinAcentos a false

        ~Tokenizador (); //Pone delimiters=""

        Tokenizador& operator= (const Tokenizador&);

        void Tokenizar (const string& str, list<string>& tokens) const;
        // Tokeniza str devolviendo el resultado en tokens. La lista tokens se vaciará antes de almacenar el resultado de la tokenización.

        bool Tokenizar (const string& i, const string& f) const;
        // Tokeniza el fichero i guardando la salida en el fichero f (una palabra por linea). Devuelve true si se realiza la tokenización; false en caso contrario enviando a cerr el mensaje correspondiete (ej. no existe el fichero i)

        bool Tokenizar (const string& i) const;
        // Tokeniza el fichero i guardando la slaida en un fichero de nombre i añadiendole la extensión .tk (sin eliminar previamente la extensión de i, por ejemplo, del archivo pp.txt se generariía el resultado en pp.txt.tk)

        bool TokenizarListaFicheros (const string& i) const;
        // Tokeniza el fichero i que contiene un nombre de fichero por linea guardando la salida en ficheros (uno por cada linea de i) cuyo nombre sera el leido en i añadiendole extensión .tk, y que contendrá una palabra en cada línea del fichero leido en i. Devolvera true si se realiza la tokenización de forma correcta de todos los archivos que contiene i; devolverá false en caso contrario enviando a cerr el mensaje correspondiente (ej. que no existe el archivo i, que sea un directerio; no se interrumpe la ejecución si hay algún achivo en i que no exista)

        bool TokenizarDirectorio (const string& i) const;
        // Tokeniza todos los archivos que contenga i, incluyendo los subdirectorios, guardando la salida en ficheros cuyo nombre será el de entrada añadiéndole extensión .tk, y que contendrá una palabra en cada linea del fichero. Devolverá true si se eraliza la tokenización de forma correcta de todos los archivos; devolverá false en caso contrario enviando a cerr el mensaje correspondiente (p.ej que no exista el directorio i, o los ficheros que no se hayan podido tokenizar)

        void DelimitadoresPalabra (const string& nuevoDelimiters);
        // Cambia "delimiters" por "nuevoDelimiters" comprobando que no hayan delimitadores repetidos (de izquierda a derecha), en cuyo caso se eliminarían los que hayan sido repetidos.

        void AnyadirDelimitadoresPalabra (const string& nuevoDelimiters);
        // Añade al final de "delimiters" los nuevos delimitadores que aparezcanen "nuevoDelimiters" (no repetidos)

        string DelimitadoresPalabra() const;
        // Devuelve delimiters
        void CasosEspeciales (const bool& nuevosCasosEspeciales);
        // Cambia la variable privada "casosEspeciales"

        bool CasosEspeciales ();
        // Devuelve el contenido de la variable privada "casosEspeciales"

        void PasarAminuscSinAcentos (const bool& nuevoPasarAminuscSinAcentos);
        // Cambia la variable privada "pasarAminuscSinAcentos". Atención al formato de codificación del corpus. Se utilizará el formato actual ISO-8859.

        bool PasarAminuscSinAcentos ();
        // Devuelve el contenido de la variable privada "pasarAmniuscSinAcentos"

    private:
        string delimiters;
        // Delimitadores de términos. Aunque se modifique la forma de almacenamiento itnerna para mejorar la eficiencia, este campo debe peranecer para indicar el orden en que se introdujeron los delimitadores.

        bool casosEspeciales;
        // Si true detctará palabras compuestas y casos especiales. Sino, trabajará al igual que el algoritmo prupuesto en la sección "Versió ndel tokenizador vista en clase"

        bool pasarAminuscSinAcentos;
        // Si true pasará el token a minúsculas y quitará acentos, antes de realizar la tokenizacón.
};
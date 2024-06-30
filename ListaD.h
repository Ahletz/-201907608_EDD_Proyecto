#ifndef LISTA_D
#define LISTA_D

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Estructura para almacenar la información de una ruta
struct Ruta {
    string origen;
    string destino;
    int distancia;

    Ruta(string o, string d, int dist) : origen(o), destino(d), distancia(dist) {}
};

// Nodo de la lista enlazada
struct NodoD {
    Ruta ruta;
    NodoD* siguiente;

    NodoD(Ruta r) : ruta(r), siguiente(nullptr) {}
};

// Clase para la lista enlazada
class ListaEnlazadaD {
private:
    NodoD* cabeza;

public:
    ListaEnlazadaD() : cabeza(nullptr) {}

    // Método para agregar una ruta a la lista
    void agregarRuta(Ruta ruta) {
        NodoD* nuevoNodo = new NodoD(ruta);
        nuevoNodo->siguiente = cabeza;
        cabeza = nuevoNodo;
    }

    // Método para mostrar la lista de rutas
    void mostrarRutas() {
        NodoD* actual = cabeza;
        while (actual != nullptr) {
            cout << "Origen: " << actual->ruta.origen << ", Destino: " << actual->ruta.destino
                 << ", Distancia: " << actual->ruta.distancia << endl;
            actual = actual->siguiente;
        }
    }

    // Método para graficar el grafo en formato DOT
    void graficarGrafo(const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo para escribir el grafo." << endl;
            return;
        }

        archivo << "digraph G {" << endl;
        archivo << "    node [shape=circle];" << endl;

        NodoD* actual = cabeza;
        while (actual != nullptr) {
            archivo << "    \"" << actual->ruta.origen << "\" -> \"" << actual->ruta.destino << "\" [label=\"" << actual->ruta.distancia << "\"];" << endl;
            actual = actual->siguiente;
        }

        archivo << "}" << endl;
        archivo.close();
        cout << "Archivo DOT generado: " << nombreArchivo << endl;

        system("dot -Tpng grafo.dot -o grafo.png");
        system("start grafo.png");
    }
};

#endif
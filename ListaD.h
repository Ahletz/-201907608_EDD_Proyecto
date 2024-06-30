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

    // Método para encontrar la ruta más corta
    void encontrarRutaMasCorta(const string& origen, const string& destino) {
        NodoD* actual = cabeza;
        vector<NodoD*> nodos;

        // Almacenar todos los nodos en un vector
        while (actual != nullptr) {
            nodos.push_back(actual);
            actual = actual->siguiente;
        }

        int numNodos = nodos.size();
        vector<int> distancias(numNodos, INT_MAX);
        vector<bool> visitados(numNodos, false);
        vector<int> previos(numNodos, -1);
        int inicio = -1, fin = -1;

        // Encontrar el índice del nodo de origen
        for (int i = 0; i < numNodos; ++i) {
            if (nodos[i]->ruta.origen == origen) {
                distancias[i] = 0;
                inicio = i;
            }
            if (nodos[i]->ruta.destino == destino) {
                fin = i;
            }
        }

        if (inicio == -1 || fin == -1) {
            cout << "Origen o destino no encontrado." << endl;
            return;
        }

        // Implementación del algoritmo de Dijkstra
        for (int i = 0; i < numNodos; ++i) {
            int u = -1;
            for (int j = 0; j < numNodos; ++j) {
                if (!visitados[j] && (u == -1 || distancias[j] < distancias[u])) {
                    u = j;
                }
            }

            if (distancias[u] == INT_MAX) break;

            visitados[u] = true;

            for (int j = 0; j < numNodos; ++j) {
                if (!visitados[j] && nodos[j]->ruta.origen == nodos[u]->ruta.destino) {
                    int alt = distancias[u] + nodos[j]->ruta.distancia;
                    if (alt < distancias[j]) {
                        distancias[j] = alt;
                        previos[j] = u;
                    }
                }
            }
        }

        // Reconstrucción del camino más corto
        vector<int> camino;
        for (int u = fin; u != -1; u = previos[u]) {
            camino.insert(camino.begin(), u);
        }

        if (distancias[fin] == INT_MAX) {
            cout << "No hay ruta posible." << endl;
        } else {
            cout << "Ruta más corta: ";
            for (size_t i = 0; i < camino.size(); ++i) {
                if (i > 0) cout << " -> ";
                cout << nodos[camino[i]]->ruta.origen << " a " << nodos[camino[i]]->ruta.destino;
            }
            cout << endl;
            cout << "Distancia total: " << distancias[fin] << endl;
        }
    }
};

#endif
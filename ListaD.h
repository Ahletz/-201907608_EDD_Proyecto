#ifndef LISTA_D
#define LISTA_D

#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <unordered_map>
#include <set>
#include <fstream>
#include <algorithm>

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

    // Método para encontrar la ruta óptima
    pair<vector<string>, int> rutaOptima(string inicio, string fin) {
        // Construir el grafo
        unordered_map<string, vector<pair<string, int>>> grafo;
        NodoD* actual = cabeza;
        while (actual != nullptr) {
            grafo[actual->ruta.origen].push_back({actual->ruta.destino, actual->ruta.distancia});
            grafo[actual->ruta.destino].push_back({actual->ruta.origen, actual->ruta.distancia}); // Si es bidireccional
            actual = actual->siguiente;
        }

        // Algoritmo de Dijkstra
        unordered_map<string, int> distancias;
        unordered_map<string, string> predecesores;
        set<pair<int, string>> cola;

        for (const auto& par : grafo) {
            distancias[par.first] = INT_MAX;
        }

        distancias[inicio] = 0;
        cola.insert({0, inicio});

        while (!cola.empty()) {
            auto [dist, nodo] = *cola.begin();
            cola.erase(cola.begin());

            for (const auto& vecino : grafo[nodo]) {
                auto [vecinoNodo, peso] = vecino;
                if (dist + peso < distancias[vecinoNodo]) {
                    cola.erase({distancias[vecinoNodo], vecinoNodo});
                    distancias[vecinoNodo] = dist + peso;
                    predecesores[vecinoNodo] = nodo;
                    cola.insert({distancias[vecinoNodo], vecinoNodo});
                }
            }
        }

        // Reconstruir el camino
        vector<string> camino;
        string actualNodo = fin;
        while (actualNodo != inicio) {
            camino.push_back(actualNodo);
            actualNodo = predecesores[actualNodo];
            if (actualNodo == "") {
                return {{}, -1}; // No se encontró camino
            }
        }
        camino.push_back(inicio);
        reverse(camino.begin(), camino.end());

        return {camino, distancias[fin]};
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
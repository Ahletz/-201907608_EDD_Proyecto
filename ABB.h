#ifndef ARBOL_BB
#define ARBOL_BB

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Piloto {
    string nombre;
    string nacionalidad;
    string numero_de_id;
    string vuelo;
    string tipo_de_licencia;
    int horas_de_vuelo;
};

// Nodo para el árbol binario de búsqueda
struct Nodo {
    Piloto piloto; // Estructura del árbol
    Nodo* izquierda; // Apuntador izquierda
    Nodo* derecha; // Apuntador derecha

    Nodo(Piloto p) : piloto(p), izquierda(nullptr), derecha(nullptr) {} // Constructor del nodo
};

// Clase árbol de búsqueda binaria
class ArbolDeBusquedaBinaria {
private:
    Nodo* raiz; // Raíz del nodo

    // Agregar nuevo nodo al árbol
    void agregar(Nodo*& nodo, Piloto p) {
        if (nodo == nullptr) {
            nodo = new Nodo(p);
        } else if (p.horas_de_vuelo < nodo->piloto.horas_de_vuelo) {
            agregar(nodo->izquierda, p);
        } else {
            agregar(nodo->derecha, p);
        }
    }

    // Eliminar nodo del árbol
    Nodo* eliminar(Nodo* nodo, int horas_de_vuelo) {
        if (nodo == nullptr) return nodo;

        if (horas_de_vuelo < nodo->piloto.horas_de_vuelo) {
            nodo->izquierda = eliminar(nodo->izquierda, horas_de_vuelo);
        } else if (horas_de_vuelo > nodo->piloto.horas_de_vuelo) {
            nodo->derecha = eliminar(nodo->derecha, horas_de_vuelo);
        } else {
            if (nodo->izquierda == nullptr) {
                Nodo* temp = nodo->derecha;
                delete nodo;
                return temp;
            } else if (nodo->derecha == nullptr) {
                Nodo* temp = nodo->izquierda;
                delete nodo;
                return temp;
            }
            Nodo* temp = minValorNodo(nodo->derecha);
            nodo->piloto = temp->piloto;
            nodo->derecha = eliminar(nodo->derecha, temp->piloto.horas_de_vuelo);
        }
        return nodo;
    }

    Nodo* minValorNodo(Nodo* nodo) {
        Nodo* actual = nodo;
        while (actual && actual->izquierda != nullptr)
            actual = actual->izquierda;
        return actual;
    }

    void mostrarPreorden(Nodo* nodo) {
        if (nodo == nullptr) return;
        mostrarPiloto(nodo->piloto);
        mostrarPreorden(nodo->izquierda);
        mostrarPreorden(nodo->derecha);
    }

    void mostrarInorden(Nodo* nodo) {
        if (nodo == nullptr) return;
        mostrarInorden(nodo->izquierda);
        mostrarPiloto(nodo->piloto);
        mostrarInorden(nodo->derecha);
    }

    void mostrarPostorden(Nodo* nodo) {
        if (nodo == nullptr) return;
        mostrarPostorden(nodo->izquierda);
        mostrarPostorden(nodo->derecha);
        mostrarPiloto(nodo->piloto);
    }

    void mostrarPiloto(Piloto p) {
        cout << "Nombre: " << p.nombre << ", Nacionalidad: " << p.nacionalidad
             << ", Numero de ID: " << p.numero_de_id << ", Vuelo: " << p.vuelo
             << ", Tipo de Licencia: " << p.tipo_de_licencia << ", Horas de Vuelo: " << p.horas_de_vuelo << endl;
    }

    // Función recursiva para generar código Graphviz
    void graficarNodo(ofstream& archivo, Nodo* nodo) {
        if (nodo == nullptr) return;

        // Graficar el nodo actual
        archivo << "    \"" << nodo->piloto.numero_de_id << "\" [label=\""
                << nodo->piloto.nombre << "\\n" << nodo->piloto.horas_de_vuelo << "\"];" << endl;

        // Graficar la conexión con el hijo izquierdo
        if (nodo->izquierda != nullptr) {
            archivo << "    \"" << nodo->piloto.numero_de_id << "\" -> \""
                    << nodo->izquierda->piloto.numero_de_id << "\" [label=\"izquierda\"];" << endl;
            graficarNodo(archivo, nodo->izquierda);
        }

        // Graficar la conexión con el hijo derecho
        if (nodo->derecha != nullptr) {
            archivo << "    \"" << nodo->piloto.numero_de_id << "\" -> \""
                    << nodo->derecha->piloto.numero_de_id << "\" [label=\"derecha\"];" << endl;
            graficarNodo(archivo, nodo->derecha);
        }
    }

public:
    ArbolDeBusquedaBinaria() : raiz(nullptr) {}

    void agregar(Piloto p) {
        agregar(raiz, p);
    }

    void eliminar(int horas_de_vuelo) {
        raiz = eliminar(raiz, horas_de_vuelo);
    }

    void mostrarPreorden() {
        mostrarPreorden(raiz);
    }

    void mostrarInorden() {
        mostrarInorden(raiz);
    }

    void mostrarPostorden() {
        mostrarPostorden(raiz);
    }

    // Método para graficar el árbol en Graphviz
    void graficarArbol(const string& nombreArchivo) {
        ofstream archivo(nombreArchivo);
        archivo << "digraph G {" << endl;
        archivo << "    node [shape=record];" << endl;

        if (raiz != nullptr) {
            graficarNodo(archivo, raiz);
        }

        archivo << "}" << endl;
        archivo.close();
    }
};

#endif

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
struct Nodo_Arbol {
    Piloto piloto; // Estructura del árbol
    Nodo_Arbol* izquierda; // Apuntador izquierda
    Nodo_Arbol* derecha; // Apuntador derecha

    Nodo_Arbol(Piloto p) : piloto(p), izquierda(nullptr), derecha(nullptr) {} // Constructor del nodo
};

// Clase árbol de búsqueda binaria
class ArbolDeBusquedaBinaria {
private:
    Nodo_Arbol* raiz; // Raíz del nodo

    // Agregar nuevo nodo al árbol
    void agregar(Nodo_Arbol*& nodo, Piloto p) {
        if (nodo == nullptr) {
            nodo = new Nodo_Arbol(p);
        } else if (p.horas_de_vuelo < nodo->piloto.horas_de_vuelo) {
            agregar(nodo->izquierda, p);
        } else {
            agregar(nodo->derecha, p);
        }
    }

    // Eliminar nodo del árbol
    Nodo_Arbol* eliminar(Nodo_Arbol* nodo, int horas_de_vuelo) {
        if (nodo == nullptr) return nodo;

        if (horas_de_vuelo < nodo->piloto.horas_de_vuelo) {
            nodo->izquierda = eliminar(nodo->izquierda, horas_de_vuelo);
        } else if (horas_de_vuelo > nodo->piloto.horas_de_vuelo) {
            nodo->derecha = eliminar(nodo->derecha, horas_de_vuelo);
        } else {
            if (nodo->izquierda == nullptr) {
                Nodo_Arbol* temp = nodo->derecha;
                delete nodo;
                return temp;
            } else if (nodo->derecha == nullptr) {
                Nodo_Arbol* temp = nodo->izquierda;
                delete nodo;
                return temp;
            }
            Nodo_Arbol* temp = minValorNodo(nodo->derecha);
            nodo->piloto = temp->piloto;
            nodo->derecha = eliminar(nodo->derecha, temp->piloto.horas_de_vuelo);
        }
        return nodo;
    }

    Nodo_Arbol* minValorNodo(Nodo_Arbol* nodo) {
        Nodo_Arbol* actual = nodo;
        while (actual && actual->izquierda != nullptr)
            actual = actual->izquierda;
        return actual;
    }

    void mostrarPreorden(Nodo_Arbol* nodo) {
        if (nodo == nullptr) return;
        mostrarPiloto(nodo->piloto);
        mostrarPreorden(nodo->izquierda);
        mostrarPreorden(nodo->derecha);
    }

    void mostrarInorden(Nodo_Arbol* nodo) {
        if (nodo == nullptr) return;
        mostrarInorden(nodo->izquierda);
        mostrarPiloto(nodo->piloto);
        mostrarInorden(nodo->derecha);
    }

    void mostrarPostorden(Nodo_Arbol* nodo) {
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
    void graficarNodo(ofstream& archivo, Nodo_Arbol* nodo) {
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


    // Función recursiva para buscar por ID
    Piloto buscarPorId(Nodo_Arbol* nodo, const string& numero_de_id) {
        if (nodo == nullptr) {
            Piloto pilotoVacio; // Retornar un piloto vacío si no se encuentra
            return pilotoVacio;
        }

        if (numero_de_id == nodo->piloto.numero_de_id) {
            return nodo->piloto;
        } else if (numero_de_id < nodo->piloto.numero_de_id) {
            return buscarPorId(nodo->izquierda, numero_de_id);
        } else {
            return buscarPorId(nodo->derecha, numero_de_id);
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

    // Buscar piloto por ID
    Piloto buscarPorId(const string& numero_de_id) {
        return buscarPorId(raiz, numero_de_id);
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

        system("dot -Tpng Arbolbb.dot -o Arbolbb.png");
        system("start Arbolbb.png");
    }
};

#endif

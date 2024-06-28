#ifndef HASH
#define HASH

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Piloto {
    string nombre;
    string nacionalidad;
    string numero_de_id;
    string vuelo;
    string tipo_de_licencia;
    int horas_de_vuelo;
};

struct Nodo {
    Piloto piloto;
    Nodo* siguiente;
};

class ListaEnlazada {
private:
    Nodo* cabeza;
public:
    ListaEnlazada() : cabeza(nullptr) {}

    ~ListaEnlazada() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    void agregar(Piloto piloto) {
        Nodo* nuevo = new Nodo{piloto, cabeza};
        cabeza = nuevo;
    }

    Piloto* buscar(const string& numero_de_id) {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->piloto.numero_de_id == numero_de_id) {
                return &actual->piloto;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }

    void eliminar(const string& numero_de_id) {
        Nodo* actual = cabeza;
        Nodo* anterior = nullptr;

        while (actual != nullptr && actual->piloto.numero_de_id != numero_de_id) {
            anterior = actual;
            actual = actual->siguiente;
        }

        if (actual == nullptr) return; // No se encontró el piloto

        if (anterior == nullptr) { // Eliminar cabeza
            cabeza = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }

        delete actual;
    }

    void mostrar() const {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            cout << actual->piloto.numero_de_id << " ";
            actual = actual->siguiente;
        }
        cout << endl;
    }

    void graficar(ofstream& archivo, int indice) const {
        Nodo* actual = cabeza;
        archivo << "node" << indice << " [label=\"{Índice " << indice << "|";
        while (actual != nullptr) {
            archivo << actual->piloto.numero_de_id << "\\n";
            actual = actual->siguiente;
        }
        archivo << "}\"];\n";
    }
};

class TablaHash {
private:
    ListaEnlazada tabla[18];
    int tamanio;

    int funcionDispersión(const string& llave) {
        int suma = 0;
        for (char c : llave) {
            suma += c;
        }
        return suma % tamanio;
    }

public:
    TablaHash() : tamanio(18) {}

    void agregar(Piloto piloto) {
        int indice = funcionDispersión(piloto.numero_de_id);
        tabla[indice].agregar(piloto);
    }

    void mostrar() {
        for (int i = 0; i < tamanio; ++i) {
            cout << "Índice " << i << ": ";
            tabla[i].mostrar();
        }
    }

    Piloto* buscar(const string& numero_de_id) {
        int indice = funcionDispersión(numero_de_id);
        return tabla[indice].buscar(numero_de_id);
    }

    void eliminar(const string& numero_de_id) {
        int indice = funcionDispersión(numero_de_id);
        tabla[indice].eliminar(numero_de_id);
    }

    void graficar(const string& filename) {
        ofstream archivo(filename);
        archivo << "digraph G {\n";
        archivo << "node [shape=record];\n";
        for (int i = 0; i < tamanio; ++i) {
            tabla[i].graficar(archivo, i);
        }
        archivo << "}\n";
        archivo.close();
    }
};


#endif
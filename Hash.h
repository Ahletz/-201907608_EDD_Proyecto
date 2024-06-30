#ifndef HASH
#define HASH

#include <iostream>
#include <string>
#include <fstream>

using namespace std;



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
        string nodoCabecera = "index" + to_string(indice);
        archivo << nodoCabecera << " [label=\"Índice " << indice << "\"];\n";
        
        if (actual != nullptr) {
            string nodoAnterior = nodoCabecera;
            while (actual != nullptr) {
                string nodoActual = "node" + to_string(indice) + "_" + actual->piloto.numero_de_id;
                archivo << nodoActual << " [label=\"" << actual->piloto.numero_de_id << "\"];\n";
                archivo << nodoAnterior << " -> " << nodoActual << ";\n";
                nodoAnterior = nodoActual;
                actual = actual->siguiente;
            }
        }
    }
};

class TablaHash {
private:
    ListaEnlazada tabla[18];
    int tamanio;

    int funcionDispercion(const std::string& llave) {
    if (llave.empty()) return 0;

    int suma = static_cast<int>(llave[0]); // Valor ASCII del primer carácter
    for (size_t i = 1; i < llave.size(); ++i) {
        if (isdigit(llave[i])) {
            suma += llave[i] - '0'; // Convertir el carácter a su valor decimal
        }
    }
    return suma % tamanio;
}

public:
    TablaHash() : tamanio(18) {}

    void agregar(Piloto piloto) {
        int indice = funcionDispercion(piloto.numero_de_id);
        tabla[indice].agregar(piloto);
    }

    void mostrar() {
        for (int i = 0; i < tamanio; ++i) {
            cout << "Índice " << i << ": ";
            tabla[i].mostrar();
        }
    }

    Piloto* buscar(const string& numero_de_id) {
        int indice = funcionDispercion(numero_de_id);
        return tabla[indice].buscar(numero_de_id);
    }

    void eliminar(const string& numero_de_id) {
        int indice = funcionDispercion(numero_de_id);
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

        system("dot -Tpng Hash.dot -o Hash.png");
        system("start Hash.png");
    }
};


#endif
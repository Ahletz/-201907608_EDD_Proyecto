#ifndef ARBOL_BB
#define ARBOL_BB

#include <iostream>
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

//nodo para esl arbol bb
struct Nodo {

    Piloto piloto; //estructura del arbol
    Nodo* izquierda; // apuntador izquierda
    Nodo* derecha; //apuntador derecha

    Nodo(Piloto p) : piloto(p), izquierda(nullptr), derecha(nullptr) {} //contructor del nodo
};

//clase arbol de busqueda binaria
class ArbolDeBusquedaBinaria {

private:
    Nodo* raiz; //raiz del nodo

    //agregar nuevo nodo al arbol
    void agregar(Nodo*& nodo, Piloto p) {
        if (nodo == nullptr) {
            nodo = new Nodo(p);
        } else if (p.horas_de_vuelo < nodo->piloto.horas_de_vuelo) {
            agregar(nodo->izquierda, p);
        } else {
            agregar(nodo->derecha, p);
        }
    }

    //eliminar nodo del arbol
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
};


#endif
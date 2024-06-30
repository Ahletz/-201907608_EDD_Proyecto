#ifndef LISTA_CIRCULAR
#define LISTA_CIRCULAR
#include <fstream> //para la creación del archivo reporte
#include <cstdlib>  // Para system()
#include <iostream>
#include <string> // Para std::string

// LISTA CIRCULAR DOBLEMENTE ENLAZADA
struct NodoCircularD {
    // VARIABLES DEL NODO 
    std::string vuelo;
    std::string numero_Registro;
    std::string modelo;
    int capacidad;
    std::string aerolinea;
    std::string estado;
    std::string destino;

    // siguiente y anterior de la lista
    NodoCircularD* next;
    NodoCircularD* prev;

    // constructor del nodo
    NodoCircularD(std::string vuelo, std::string numero_Registro, std::string modelo, int capacidad, std::string aerolinea, std::string estado, std::string destino) {
        this->vuelo = vuelo;
        this->numero_Registro = numero_Registro;
        this->modelo = modelo;
        this->capacidad = capacidad;
        this->aerolinea = aerolinea;
        this->estado = estado;
        this->destino = destino;

        this->next = nullptr;
        this->prev = nullptr;
    }
};

class CircularDoble {
    // creación de la cabeza de la lista en clase privada
private:
    NodoCircularD* head;

    // métodos públicos de la clase para manipulación
public:
    CircularDoble() { // constructor para head -> nullo (vacío)
        head = nullptr;
    }

    // método para mostrar contenido de la lista
    void Mostrar() {
        if (head == nullptr) {
            std::cout << "LISTA VACÍA, NO SE ENCUENTRA NINGÚN ELEMENTO DENTRO!" << std::endl;
            return;
        }
        NodoCircularD* current = head; // variable current apuntador de la cabeza de la lista

        // ciclo que recorre la lista
        do {
            std::cout << "-------------------------------------------------------------" << std::endl;
            std::cout << "-------------------------------------------------------------" << std::endl;
            std::cout << "|| NÚMERO DE VUELO: " << current->vuelo << std::endl;
            std::cout << "|| REGISTRO: " << current->numero_Registro << std::endl;
            std::cout << "|| AEROLÍNEA: " << current->aerolinea << std::endl;
            std::cout << "|| ESTADO: " << current->estado << std::endl;
            std::cout << "-------------------------------------------------------------" << std::endl;
            std::cout << "-------------------------------------------------------------" << std::endl;
            current = current->next; // cambiamos al siguiente nodo que esté apuntando

        } while (current != head); // si la variable ya no apunta a la cabeza y apunta a nulo termina ciclo
        std::cout << std::endl; // salto de línea
    }

    // método para agregar un nodo a la lista
    void agregar(std::string vuelo, std::string numero_Registro, std::string modelo, int capacidad, std::string aerolinea, std::string estado, std::string destino) {
        // instanciando el nuevo nodo
        NodoCircularD* newNodo = new NodoCircularD(vuelo, numero_Registro, modelo, capacidad, aerolinea, estado, destino);

        if (head == nullptr) { // si no hay nodos dentro de la lista
            head = newNodo; // nuevo nodo se vuelve cabeza
            newNodo->next = head; // siguiente que es sí mismo
            newNodo->prev = head; // previo que es sí mismo
        }
        else { // si existe nodo en la lista
            NodoCircularD* tail = head->prev; // cola será el anterior de la cabeza existente
            tail->next = newNodo; // el siguiente de la cola existente será el nuevo nodo
            newNodo->prev = tail; // el previo del nuevo nodo es la cola
            newNodo->next = head; // siguiente del nuevo nodo será la cabeza
            head->prev = newNodo; // el previo de la cabeza será el nuevo nodo
        }
    }

    // método para eliminar un nodo en la lista circular 
    void eliminar(const std::string& numero_registro) {
        if (head == nullptr) { // si no hay nodos en la lista
            std::cout << "NO HAY ELEMENTOS PARA ELIMINAR" << std::endl;
            return;
        }

        NodoCircularD* current = head; // current contiene la cabeza de la lista circular
        do {
            if (current->numero_Registro == numero_registro) { // si encuentra el número de registro
                if (current->next == current) { // si solo hay un nodo en la lista
                    delete current; // eliminar de la memoria el nodo
                    head = nullptr; // cabeza apunta a nulo
                    return;
                }

                current->prev->next = current->next; // siguiente del anterior ahora será siguiente
                current->next->prev = current->prev; // anterior del siguiente ahora apunta al previo

                if (current == head) {
                    head = current->next;
                }

                delete current; // Eliminar el nodo
                return;
            }
            current = current->next; // avanzar en la lista
        } while (current != head);
        std::cout << "AVIÓN CON REGISTRO " << numero_registro << " NO ENCONTRADO" << std::endl;
    }

    // Método para generar el archivo .dot para Graphviz
    void graficarLista() {
        std::ofstream archivo("listaCircularDoble.dot");
        archivo << "digraph G {\n";
        archivo << "node [shape=record];\n";
        archivo << "rankdir=LR;\n";

        NodoCircularD* current = head;
        if (current != nullptr) {
            NodoCircularD* first = current;
            // Escribir los nodos individuales de la lista
            do {
                archivo << "\"" << current->numero_Registro << "\" [label=\"{" << current->numero_Registro << "}\"];\n";
                archivo << "\"" << current->numero_Registro << "\" -> \"" << current->next->numero_Registro << "\" [dir=both];\n";
                archivo << "\"" << current->numero_Registro << "\" -> \"" << current->prev->numero_Registro << "\" [dir=both];\n";
                current = current->next;
            } while (current != first);

            // Conectar el último nodo con el primero para formar la lista circular
            archivo << "\"" << current->prev->numero_Registro << "\" -> \"" << head->numero_Registro << "\" [dir=both];\n";
        }

        archivo << "}\n";
        archivo.close();

        system("dot -Tpng listaCircularDoble.dot -o listaCircularDoble.png");
        system("start listaCircularDoble.png");
    }

    // función para recuperar datos
    std::string ObtenerString(const std::string& numero_registro, const std::string& dato) {
        if (head == nullptr) {
            std::string mensaje = "LISTA VACÍA, NO SE ENCUENTRA NINGÚN ELEMENTO DENTRO!";
            return mensaje;
        }
        NodoCircularD* current = head; // variable current apuntador de la cabeza de la lista

        // ciclo que recorre la lista
        do {
            if (numero_registro == current->numero_Registro) {
                if (dato == "vuelo") {
                    return current->vuelo;
                }
                else if (dato == "modelo") {
                    return current->modelo;
                }
                else if (dato == "aerolinea") {
                    return current->aerolinea;
                }
                else if (dato == "destino") {
                    return current->destino;
                }
            }

            current = current->next; // cambiamos al siguiente nodo que esté apuntando

        } while (current != head); // si la variable ya no apunta a la cabeza y apunta a nulo termina ciclo

        return ""; // Si no se encuentra, se retorna una cadena vacía
    }

    // función para obtener capacidad
    int Obtenerint(const std::string& numero_registro) {
        if (head == nullptr) {
            std::cout << "LISTA VACÍA, NO SE ENCUENTRA NINGÚN ELEMENTO DENTRO!" << std::endl;
            return -1;
        }
        NodoCircularD* current = head; // variable current apuntador de la cabeza de la lista

        // ciclo que recorre la lista
        do {
            if (numero_registro == current->numero_Registro) {
                return current->capacidad;
            }

            current = current->next; // cambiamos al siguiente nodo que esté apuntando

        } while (current != head); // si la variable ya no apunta a la cabeza y apunta a nulo termina ciclo

        return -1; // Si no se encuentra, se retorna -1
    }
};
#endif
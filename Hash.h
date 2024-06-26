#ifndef HASH
#define HASH

#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

// Estructura para almacenar los datos del piloto
struct Piloto {
    string nombre;
    string nacionalidad;
    string numero_de_id;
    string vuelo;
    string tipo_de_licencia;
    int horas_de_vuelo;
    Piloto* next; // Puntero al siguiente piloto en caso de colisión
};

// Nodo para la lista de llaves
struct KeyNode {
    string numero_de_id;
    KeyNode* next; // Puntero al siguiente nodo
};

// Clase para la tabla hash
class HashTable {
private:
    int size;
    Piloto** table;
    KeyNode* keysHead;

    int hashFunction(const string& key) {
        int numericKey = stoi(key); // Convertir la llave a un número entero
        return numericKey % size;
    }

public:
    HashTable(int size) {
        this->size = size;
        table = new Piloto*[size];
        for (int i = 0; i < size; i++) {
            table[i] = nullptr;
        }
        keysHead = nullptr;
    }

    ~HashTable() {
        for (int i = 0; i < size; i++) {
            Piloto* entry = table[i];
            while (entry != nullptr) {
                Piloto* prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
        delete[] table;

        KeyNode* current = keysHead;
        while (current != nullptr) {
            KeyNode* prev = current;
            current = current->next;
            delete prev;
        }
    }

    void insert(const Piloto& piloto) {
        int hashValue = hashFunction(piloto.numero_de_id);
        Piloto* newEntry = new Piloto(piloto);
        newEntry->next = table[hashValue];
        table[hashValue] = newEntry;

        KeyNode* newKeyNode = new KeyNode{ piloto.numero_de_id, keysHead };
        keysHead = newKeyNode;
    }

    Piloto* search(const string& numero_de_id) {
        int hashValue = hashFunction(numero_de_id);
        Piloto* entry = table[hashValue];

        while (entry != nullptr) {
            if (entry->numero_de_id == numero_de_id) {
                return entry;
            }
            entry = entry->next;
        }

        return nullptr;
    }

    Piloto remove(const string& numero_de_id) {
        int hashValue = hashFunction(numero_de_id);
        Piloto* entry = table[hashValue];
        Piloto* prev = nullptr;

        while (entry != nullptr && entry->numero_de_id != numero_de_id) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr) {
            throw runtime_error("ID no encontrado en la tabla hash.");
        } else {
            if (prev == nullptr) {
                table[hashValue] = entry->next;
            } else {
                prev->next = entry->next;
            }

            Piloto removed = *entry;
            delete entry;

            KeyNode* current = keysHead;
            KeyNode* prevKey = nullptr;
            while (current != nullptr && current->numero_de_id != numero_de_id) {
                prevKey = current;
                current = current->next;
            }

            if (current != nullptr) {
                if (prevKey == nullptr) {
                    keysHead = current->next;
                } else {
                    prevKey->next = current->next;
                }
                delete current;
            }

            return removed;
        }
    }

    void display() {
        for (int i = 0; i < size; i++) {
            Piloto* entry = table[i];
            if (entry != nullptr) {
                cout << "[" << i << "]";
                while (entry != nullptr) {
                    cout << " -> " << entry->numero_de_id << " (" << entry->nombre << ")";
                    entry = entry->next;
                }
                cout << endl;
            }
        }
    }

    void graphviz() {
        cout << "digraph HashTable {\n";
        cout << "    node [shape=record];\n";

        for (int i = 0; i < size; i++) {
            Piloto* entry = table[i];
            if (entry != nullptr) {
                cout << "    node" << i << " [label=\"";
                Piloto* current = entry;
                while (current != nullptr) {
                    cout << "{<f" << current << "> " << current->numero_de_id << " | " << current->nombre << "}";
                    if (current->next != nullptr) cout << " | ";
                    current = current->next;
                }
                cout << "\"];\n";

                current = entry;
                while (current != nullptr) {
                    if (current->next != nullptr) {
                        cout << "    \"node" << i << "\":f" << current << " -> \"node" << i << "\":f" << current->next << ";\n";
                    }
                    current = current->next;
                }
            }
        }

        cout << "}\n";
    }
};



#endif
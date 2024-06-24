#ifndef HASH
#define HASH

#include <iostream>
#include <list>
#include <vector>
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

class HashTable {
private:
    vector<list<Piloto>> table;
    int size;

    int hashFunction(const string& key) {
        int numeric_key = stoi(key);
        return numeric_key % size;
    }

public:
    HashTable(int size) : size(size) {
        table.resize(size);
    }

    void insert(Piloto p) {
        int index = hashFunction(p.numero_de_id);
        table[index].push_back(p);
    }

    Piloto* search(const string& key) {
        int index = hashFunction(key);
        for (auto& piloto : table[index]) {
            if (piloto.numero_de_id == key) {
                return &piloto;
            }
        }
        return nullptr; // Indica que no se encontró
    }

    void remove(const string& key) {
        int index = hashFunction(key);
        table[index].remove_if([&key](const Piloto& p) { return p.numero_de_id == key; });
    }

    void display() {
        for (int i = 0; i < size; ++i) {
            cout << "Index " << i << ": ";
            for (const auto& piloto : table[i]) {
                cout << piloto.nombre << " (" << piloto.numero_de_id << "), ";
            }
            cout << endl;
        }
    }
};





#endif
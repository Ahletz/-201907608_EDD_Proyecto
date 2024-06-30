#ifndef MATRIX
#define MATRIX

#include <iostream>
#include <string>
#include <fstream>
#include <set>

// Nodo para la lista de pilotos
struct PilotoID {
    std::string id;
    std::string vuelo;
    PilotoID* siguiente;
    
    PilotoID(const std::string& id, const std::string& vuelo)
        : id(id), vuelo(vuelo), siguiente(nullptr) {}
};

// Nodo para la lista de destinos
struct Destino {
    std::string nombre;
    Destino* siguiente;
    PilotoID* pilotos;
    
    Destino(const std::string& nombre)
        : nombre(nombre), siguiente(nullptr), pilotos(nullptr) {}
};

// Nodo para la lista de vuelos
struct VueloX {
    std::string codigo;
    VueloX* siguiente;
    Destino* destinos;
    
    VueloX(const std::string& codigo)
        : codigo(codigo), siguiente(nullptr), destinos(nullptr) {}
};

class MatrizDispersa {
private:
    VueloX* vuelos;

public:
    MatrizDispersa() : vuelos(nullptr) {}

    // Método para agregar un vuelo y un destino
    void agregarVueloDestino(const std::string& vuelo, const std::string& destino) {
        if (!existeVuelo(vuelo)) {
            VueloX* nuevoVuelo = new VueloX(vuelo);
            nuevoVuelo->siguiente = vuelos;
            vuelos = nuevoVuelo;
        }

        VueloX* vueloPtr = obtenerVuelo(vuelo);
        if (vueloPtr && !existeDestino(vueloPtr, destino)) {
            Destino* nuevoDestino = new Destino(destino);
            nuevoDestino->siguiente = vueloPtr->destinos;
            vueloPtr->destinos = nuevoDestino;
        }
    }

    // Método para agregar un piloto
    void agregarPiloto(const std::string& piloto_id, const std::string& vuelo) {
        VueloX* vueloPtr = obtenerVuelo(vuelo);
        if (vueloPtr) {
            Destino* destinoPtr = vueloPtr->destinos;
            while (destinoPtr) {
                PilotoID* nuevoPiloto = new PilotoID(piloto_id, vuelo);
                nuevoPiloto->siguiente = destinoPtr->pilotos;
                destinoPtr->pilotos = nuevoPiloto;
                destinoPtr = destinoPtr->siguiente;
            }
        }
    }

    // Método para eliminar un piloto
    void eliminarPiloto(const std::string& piloto_id) {
        VueloX* vueloPtr = vuelos;
        while (vueloPtr) {
            Destino* destinoPtr = vueloPtr->destinos;
            while (destinoPtr) {
                PilotoID* prevPiloto = nullptr;
                PilotoID* pilotoPtr = destinoPtr->pilotos;
                while (pilotoPtr) {
                    if (pilotoPtr->id == piloto_id) {
                        if (prevPiloto) {
                            prevPiloto->siguiente = pilotoPtr->siguiente;
                        } else {
                            destinoPtr->pilotos = pilotoPtr->siguiente;
                        }
                        delete pilotoPtr;
                        break;
                    }
                    prevPiloto = pilotoPtr;
                    pilotoPtr = pilotoPtr->siguiente;
                }
                destinoPtr = destinoPtr->siguiente;
            }
            vueloPtr = vueloPtr->siguiente;
        }
    }

    // Método para eliminar un vuelo y su destino asociado
    void eliminarVueloDestino(const std::string& vuelo, const std::string& destino) {
        VueloX* prevVuelo = nullptr;
        VueloX* vueloPtr = vuelos;

        while (vueloPtr) {
            if (vueloPtr->codigo == vuelo) {
                if (prevVuelo) {
                    prevVuelo->siguiente = vueloPtr->siguiente;
                } else {
                    vuelos = vueloPtr->siguiente;
                }

                Destino* prevDestino = nullptr;
                Destino* destinoPtr = vueloPtr->destinos;

                while (destinoPtr) {
                    if (destinoPtr->nombre == destino) {
                        if (prevDestino) {
                            prevDestino->siguiente = destinoPtr->siguiente;
                        } else {
                            vueloPtr->destinos = destinoPtr->siguiente;
                        }
                        delete destinoPtr;
                        break;
                    }
                    prevDestino = destinoPtr;
                    destinoPtr = destinoPtr->siguiente;
                }
                delete vueloPtr;
                break;
            }
            prevVuelo = vueloPtr;
            vueloPtr = vueloPtr->siguiente;
        }
    }

    
    // Método para graficar la matriz usando Graphviz en formato de matriz
    // Método para graficar la matriz usando Graphviz en formato de matriz
    void graficarMatriz() {
        std::ofstream archivo("matriz.dot");
        archivo << "digraph G {\n";
        archivo << "node [shape=plaintext];\n";
        archivo << "tabla [label=<\n";
        archivo << "<table border='1' cellborder='1' cellspacing='0'>\n";

        // Recopilar todos los destinos únicos
        std::set<std::string> destinosUnicos;
        VueloX* vueloPtr = vuelos;
        while (vueloPtr) {
            Destino* destinoPtr = vueloPtr->destinos;
            while (destinoPtr) {
                destinosUnicos.insert(destinoPtr->nombre);
                destinoPtr = destinoPtr->siguiente;
            }
            vueloPtr = vueloPtr->siguiente;
        }

        // Escribir las cabeceras de las columnas
        archivo << "<tr><td></td>";
        for (const auto& destino : destinosUnicos) {
            archivo << "<td>" << destino << "</td>";
        }
        archivo << "</tr>\n";
        
        // Escribir las filas con los vuelos y los IDs de los pilotos
        vueloPtr = vuelos;
        while (vueloPtr) {
            archivo << "<tr><td>" << vueloPtr->codigo << "</td>";
            for (const auto& destino : destinosUnicos) {
                archivo << "<td>";
                Destino* destinoPtr = vueloPtr->destinos;
                while (destinoPtr) {
                    if (destinoPtr->nombre == destino) {
                        PilotoID* pilotoPtr = destinoPtr->pilotos;
                        while (pilotoPtr) {
                            archivo << pilotoPtr->id << "<br/>";
                            pilotoPtr = pilotoPtr->siguiente;
                        }
                    }
                    destinoPtr = destinoPtr->siguiente;
                }
                archivo << "</td>";
            }
            archivo << "</tr>\n";
            vueloPtr = vueloPtr->siguiente;
        }

        archivo << "</table>>];\n";
        archivo << "}\n";
        archivo.close();

        system("dot -Tpng matriz.dot -o matriz.png");
        system("start matriz.png");
    }

       // system("dot -Tpng matriz.dot -o matriz.png");
        //system("start matriz.png");
    

    // Método para mostrar la matriz en consola
    void mostrarMatriz() {
        VueloX* vueloPtr = vuelos;
        while (vueloPtr) {
            Destino* destinoPtr = vueloPtr->destinos;
            while (destinoPtr) {
                PilotoID* pilotoPtr = destinoPtr->pilotos;
                while (pilotoPtr) {
                    std::cout << "Vuelo: " << vueloPtr->codigo << ", Destino: " << destinoPtr->nombre << ", Piloto ID: " << pilotoPtr->id << "\n";
                    pilotoPtr = pilotoPtr->siguiente;
                }
                destinoPtr = destinoPtr->siguiente;
            }
            vueloPtr = vueloPtr->siguiente;
        }
    }

private:
    // Método para comprobar si un vuelo existe
    bool existeVuelo(const std::string& vuelo) {
        VueloX* vueloPtr = vuelos;
        while (vueloPtr) {
            if (vueloPtr->codigo == vuelo) {
                return true;
            }
            vueloPtr = vueloPtr->siguiente;
        }
        return false;
    }

    // Método para obtener un vuelo
    VueloX* obtenerVuelo(const std::string& vuelo) {
        VueloX* vueloPtr = vuelos;
        while (vueloPtr) {
            if (vueloPtr->codigo == vuelo) {
                return vueloPtr;
            }
            vueloPtr = vueloPtr->siguiente;
        }
        return nullptr;
    }

    // Método para comprobar si un destino existe en un vuelo
    bool existeDestino(VueloX* vueloPtr, const std::string& destino) {
        Destino* destinoPtr = vueloPtr->destinos;
        while (destinoPtr) {
            if (destinoPtr->nombre == destino) {
                return true;
            }
            destinoPtr = destinoPtr->siguiente;
        }
        return false;
    }
};

#endif
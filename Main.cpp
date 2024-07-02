#include <iostream>
#include "json.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

#include "CircularDoble.h" //incluir clase lista circular doble
#include "ArbolB.h" //incluimos el arbol B
#include "ABB.h" //arbol binario de busqueda
#include "Hash.h" //tabla hash
#include "ListaD.h" //Lista de adyascencia
#include "Matriz.h" //matriz dispersa 

using json = nlohmann::json;


//estructuras
CircularDoble Circular;
BTree ArbolB (3);
ArbolDeBusquedaBinaria Bb;
TablaHash tabla;
ListaEnlazadaD adyascencia; 
MatrizDispersa matrix;

//lectura archivos json aviones
json leerJSON_Aviones() {
    
    std::string documento; //variable con nombre del documento
    std::string ruta = "C:/Users/ludwi/OneDrive/Escritorio/-201907608_EDD_Proyecto/"; //ruta de archivo predefinido

    std::cout << "INGRESE LA RUTA DEL ARCHIVO: " << std::endl; //ruta: C:/Users/ludwi/OneDrive/Escritorio/-201907608_EDD_Proyecto/aviones.json
    std::cin >> documento; //INGRESAR EL NUMERO SELECCIONADO DE LA OPCION

    ruta = ruta +documento; //agregar el nombre del archivo a la ruta

    std::cout << "ruta: " <<ruta<< std::endl; //imprimir ruta del archivo

    std::ifstream inputFile(ruta);
    json jsonData;

    if (inputFile.is_open()) {
        inputFile >> jsonData;
        inputFile.close();
    } else {
        std::cerr << "No se pudo abrir el archivo: " << std::endl;
        throw std::runtime_error("Archivo no encontrado");
    }

     // Mostrar el contenido del JSON
    //std::cout << jsonData.dump(4) << std::endl;
    std::cout<< "DATOS QUE SER CARGARON: "<< std::endl;
    std::cout<< "-------------------------------------------------------------"<< std::endl;

    // Acceder a los elementos del JSON
    for (const auto& aviones : jsonData) {

        //OBTENER LOS ELEMENTOS DEL JSON AVIONES
        std::string vuelo = aviones["vuelo"];
        std::string numero_Registro = aviones["numero_de_registro"];
        std::string modelo = aviones["modelo"];
        int capacidad = aviones["capacidad"];
        std::string aerolinea = aviones["aerolinea"];
        std::string estado = aviones["estado"];
        std::string destino = aviones["ciudad_destino"];


        matrix.agregarVueloDestino(vuelo, destino); //crear vuelos y destinos (filas y columnas) en la matriz dispersa
        

        if (estado == "Disponible")
        {
            Avion avion = {vuelo, numero_Registro, modelo, capacidad, aerolinea, estado, destino};
            ArbolB.insert(avion);
        }else
        {
            //agregar a la lista circular doble
            Circular.agregar(vuelo,numero_Registro,modelo,capacidad,aerolinea,estado,destino);
        }
        

    //MOSTRAR LOS DATOS DEL JSCON CARGADOS
        std::cout<< vuelo<< std::endl;
        std::cout<< numero_Registro<< std::endl;
        std::cout<< modelo<< std::endl;
        std::cout<< capacidad<< std::endl;
        std::cout<< aerolinea<< std::endl;
        std::cout<< destino<< std::endl;
        std::cout<< estado<< std::endl;
        std::cout<< "-------------------------------------------------------------"<< std::endl;

        
    }

     return jsonData; // Retornar los datos JSON leídos

}

//carga de json con pilotos y su informacion
json leerJSON_Pilotos() {
    
    std::string documento; //variable con nombre del documento
    std::string ruta = "C:/Users/ludwi/OneDrive/Escritorio/-201907608_EDD_Proyecto/"; //ruta de archivo predefinido

    std::cout << "INGRESE LA RUTA DEL ARCHIVO: " << std::endl; //ruta: C:/Users/ludwi/OneDrive/Escritorio/-201907608_EDD_Proyecto/aviones.json
    std::cin >> documento; //INGRESAR EL NUMERO SELECCIONADO DE LA OPCION

    ruta = ruta +documento; //agregar el nombre del archivo a la ruta

    std::cout << "ruta: " <<ruta<< std::endl; //imprimir ruta del archivo

    std::ifstream inputFile(ruta);
    json jsonData;

    if (inputFile.is_open()) {
        inputFile >> jsonData;
        inputFile.close();
    } else {
        std::cerr << "No se pudo abrir el archivo: " << std::endl;
        throw std::runtime_error("Archivo no encontrado");
    }

     // Mostrar el contenido del JSON
    //std::cout << jsonData.dump(4) << std::endl;
    std::cout<< "DATOS QUE SER CARGARON: "<< std::endl;
    std::cout<< "-------------------------------------------------------------"<< std::endl;

    // Acceder a los elementos del JSON
    for (const auto& piloto : jsonData) {

        //OBTENER LOS ELEMENTOS DEL JSON AVIONES
        std::string nombre = piloto["nombre"];
        std::string nacionalidad = piloto["nacionalidad"];
        std::string id = piloto["numero_de_id"];
        int horas = piloto["horas_de_vuelo"];
        std::string vuelo = piloto["vuelo"];
        std::string licencia = piloto["tipo_de_licencia"];

        //AGREGAR LOS ID DE LOS PILOTOS A LA MATRIZ DISPERSA
        matrix.agregarPiloto(id,vuelo);

        //AGREGAR A ESTRUCTURAS
        Piloto datos ={nombre, nacionalidad,id,vuelo,licencia,horas};

        Bb.agregar(datos);
        tabla.agregar(datos);

      
    //MOSTRAR LOS DATOS DEL JSCON CARGADOS
        std::cout<< nombre<< std::endl;
        std::cout<< nacionalidad<< std::endl;
        std::cout<< id<< std::endl;
        std::cout<< vuelo<< std::endl;
        std::cout<< horas<< std::endl;
        std::cout<< licencia<< std::endl;
        std::cout<< "-------------------------------------------------------------"<< std::endl;

        
    }

     return jsonData; // Retornar los datos JSON leídos

}

void leerArchivo() {

    std::string documento; //variable con nombre del documento
    std::string ruta = "C:/Users/ludwi/OneDrive/Escritorio/-201907608_EDD_Proyecto/"; //ruta de archivo predefinido

    std::cout << "INGRESE LA RUTA DEL ARCHIVO: " << std::endl; //ruta: C:/Users/ludwi/OneDrive/Escritorio/-201907608_EDD_Proyecto/aviones.json
    std::cin >> documento; //INGRESAR EL NUMERO SELECCIONADO DE LA OPCION

    ruta = ruta +documento; //agregar el nombre del archivo a la ruta

    std::cout << "ruta: " <<ruta<< std::endl; //imprimir ruta del archivo

    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << documento << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.back() == ';') {
            linea.pop_back();  // Elimina el último carácter ';'
        }
        
        std::istringstream stream(linea);
        std::string origen, destino;
        int distancia;
        if (std::getline(stream, origen, '/') && std::getline(stream, destino, '/') && (stream >> distancia)) {

            Ruta r = {origen, destino, distancia}; //se crea el objeto de estructura ruta 
            
            adyascencia.agregarRuta(r); //se agrega a la lista de adyascencia

        } else {
            std::cerr << "Formato incorrecto en la línea: " << linea << std::endl;
        }
    }

    archivo.close();
}

void leerMovimientos() {

    std::string documento; //variable con nombre del documento
    std::string ruta = "C:/Users/ludwi/OneDrive/Escritorio/-201907608_EDD_Proyecto/"; //ruta de archivo predefinido

    std::cout << "INGRESE LA RUTA DEL ARCHIVO: " << std::endl; //ruta: C:/Users/ludwi/OneDrive/Escritorio/-201907608_EDD_Proyecto/aviones.json
    std::cin >> documento; //INGRESAR EL NUMERO SELECCIONADO DE LA OPCION

    ruta = ruta +documento; //agregar el nombre del archivo a la ruta

    std::cout << "ruta: " <<ruta<< std::endl; //imprimir ruta del archivo

    std::ifstream archivo(ruta);

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << documento << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.back() == ';') {
            linea.pop_back();  // Elimina el último carácter ';'
        }

        if (linea.find("MantenimientoAviones") != std::string::npos) {
            std::istringstream stream(linea);
            std::string primer, segundo, tercero;
            std::getline(stream, primer, ',');
            std::getline(stream, segundo, ',');
            std::getline(stream, tercero, ',');

            std::cout << "Mantenimiento: " << segundo << ", ID: " << tercero << std::endl;

            if (segundo == "Salida") //cambio de circular doble a albol b
            {
                std::cout << "INGRESO: " << segundo << ", ID: " << tercero << std::endl;

                //se capturan los datos de la lista circular
                std::string vuelo = Circular.ObtenerString(tercero,"vuelo");
                std::string modelo = Circular.ObtenerString(tercero,"modelo");
                std::string aerolinea = Circular.ObtenerString(tercero,"aerolinea");
                std::string destino = Circular.ObtenerString(tercero,"destino");
                int capacidad = Circular.Obtenerint(tercero);

                Avion dato = {vuelo, tercero, modelo, capacidad, aerolinea, destino, "Disponible"}; //se crea una estructura avion

                ArbolB.insert(dato); //se agrega al arbol b

                Circular.eliminar(tercero); //se elimina de la lista circular doble
            }else if (segundo == "Ingreso")
            {
                Avion dato = ArbolB.remove(tercero); //eliminamos y capturamos los datos del arbol b

                std::string estado = "Mantenimiento";

                Circular.agregar(dato.vuelo,tercero,dato.modelo,dato.capacidad,dato.aerolinea, estado, dato.ciudad_destino); //se agrega a la lista doble circular
            }
            
            

        } else if (linea.find("DarDeBaja") != std::string::npos) {
            std::regex regex("\\(([^)]+)\\)");
            std::smatch match;
            if (std::regex_search(linea, match, regex)) {

                std::cout << "ID para Dar de Baja: " << match[1] << std::endl;

                std::string id = match[1];

                //dar de baja al piloto en las estructuras
                Piloto p = Bb.buscarPorId(id); //se busca las horas de vuelo de un piloto
                Bb.eliminar(p.horas_de_vuelo); //se elimina el nodo por medio de las horas de vuelo
                tabla.eliminar(id); //se elimina de la tabla hash
                matrix.eliminarPiloto(id); //se elimina de la matriz de adyascencia

            } else {
                std::cerr << "Formato incorrecto en la línea: " << linea << std::endl;
            }
        } else {
            std::cerr << "Formato desconocido en la línea: " << linea << std::endl;
        }
    }

    archivo.close();
}

void Mensaje()
{
    std::cout << "||------------- Menu -------------||" << std::endl;
    std::cout << "|| 1. CARGAR AVIONES.             ||" << std::endl; //carga de archivo, falta implementacion de estructuras (arbol b y lista cricular)
    std::cout << "|| 2. CARGAR PILOTOS.             ||" << std::endl; //implementacion de tabla hash y arbol bb 
    std::cout << "|| 3. CARGA RUTAS.                ||" << std::endl; //se agrego una lista de adyascencia 
    std::cout << "|| 4. CARGAR MOVIMIENTOS.         ||" << std::endl; //falta (ya lo tengo, solo falta agregarlo)
    std::cout << "|| 5. CONSULTA HORAS DE VUELO.    ||" << std::endl; //agregar ordenes para mostrar datos en arbol bb
    std::cout << "|| 6. RECOMENDAR RUTA             ||" << std::endl; //falta
    std::cout << "|| 7. VISUALIZAR REPORTES.        ||" << std::endl; //reporte arbol b, lista circular, tabla hash, grafo ruta y matriz
    std::cout << "|| 8. SALIR.                      ||" << std::endl; //salida exitosa

}

void Consulta_horas()
{
    bool salida = true; //variable para entrar y salir del ciclo del menu de ordenes
    while (salida) //ciclo para mostrar los ordenes 
    {
        std::cout << "|| SELECCIONES UN ORDEN: -------------||" << std::endl;
        std::cout << "|| 1. PREORDEN.                       ||" << std::endl; 
        std::cout << "|| 2. INORDEN.                        ||" << std::endl; 
        std::cout << "|| 3. POSTORDEN.                      ||" << std::endl;
        std::cout << "|| 4. REGRESAR.                       ||" << std::endl;

        int seleccion; //variable seleccion de menu     
        std::cin >> seleccion; //INGRESAR EL NUMERO SELECCIONADO DE LA OPCION

        switch (seleccion)
        {
        case 1:
            Bb.mostrarPreorden();
            break;
        case 2:
            Bb.mostrarInorden();
            break;
        case 3:
            Bb.mostrarPostorden();
            break;
        case 4:
            salida = false; //salir del sistema y volver al menu principal
            break;
        
        default:

             std::cout << "|| NO INGRESO UNA OPCION VALIDA, VUELVA A INGRESAR UNA OPCION QUE SI SEA VALIDA PORFAVOR.||" << std::endl;
            break;
        }

    }
    
     
}

void RutaMasCorta(){

    //variables para pedir ruta
    std::string origen;
    std::string destino;

    std::cout << "|| INGRESE UN ORIGEN: ";
    std::cin >> origen;
    std::cout << std:: endl; //salto de linea

    std::cout << "|| INGRESE UN DESTINO: ";
    std::cin >> destino;

    adyascencia.encontrarRutaMasCorta(origen, destino); //se llama a la funcion destino para realizar la ruta


}





int main(int argc, char const *argv[])
{   

    bool exit = true; // VARIABLE DE SALIDA DEL CICLO
 
    while (exit)
    {
        int seleccion; //variable seleccion de menu     

        Mensaje(); //llamamos la presentacion del mensaje

        std::cin >> seleccion; //INGRESAR EL NUMERO SELECCIONADO DE LA OPCION

        switch (seleccion)
        {
        case 1:
            std::cout << "|| OPCION 1 CARGA DE AVIONES. ||" << std::endl; 
           
             try {
                    json pasajerosData = leerJSON_Aviones();
            } catch (const std::runtime_error& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                
            }
            
            break;
        case 2:
            std::cout << "|| OPCION 2. CARGA DE PILOTOS. ||" << std::endl;

            try {
                    json pasajerosData = leerJSON_Pilotos();
            } catch (const std::runtime_error& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                
            }
            break;
        case 3:
            std::cout << "|| OPCION 3. CARGA DE RUTAS. ||" << std::endl;
            leerArchivo(); //se lee el archivo de rutas 
            break;
        case 4:
            std::cout << "|| OPCION 4. CARGA DE MOVIMIENTOS. ||" << std::endl; 
            leerMovimientos();
            break;
        case 5:
            std::cout << "|| OPCION 5. CONSULTA DE HORA DE VUELO. ||" << std::endl;
            Consulta_horas(); //funcion para llamar consulta de ordenes de horas 
            break;
        
        case 6:
            std::cout << "|| OPCION 6. RECOMENDAR RUTA. ||" << std::endl; 
            RutaMasCorta(); //funcion para llamar la ruta
            break;
        
        case 7:

            std::cout << "|| OPCION 7. VISUALIZAR REPORTES. ||" << std::endl; 
            matrix.mostrarMatriz();
            Circular.graficarLista();
            ArbolB.graphviz("ArbolB.dot");
            tabla.graficar("Hash.dot");
            adyascencia.graficarGrafo("grafo.dot");
            matrix.graficarMatriz();
            matrix.graficarMatriz2();
            Bb.graficarArbol("Arbolbb.dot");
            
            
            return 0;
            break;
        
        case 8:

            exit = false; //salida del ciclo en caso de cerrar programa

            break;
        
        default:

            std::cout << " NO INGRESO UNA OPCION VALIDA! " << std::endl;

            break;
        }
    }
    
    
    
    return 0;
}



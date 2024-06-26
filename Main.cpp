#include <iostream>
#include "json.hpp"

#include "CircularDoble.h" //incluir clase lista circular doble
#include "ArbolB.h" //incluimos el arbol B

using json = nlohmann::json;


//estructuras
CircularDoble Circular;

//lectura archivos json aviones
json leerJSON_Aviones() {
    
    std::string documento; //variable con nombre del documento

    std::cout << "INGRESE LA RUTA DEL ARCHIVO: " << std::endl; //ruta: C:/Users/ludwi/OneDrive/Escritorio/-201907608_EDD_Proyecto/aviones.json
    std::cin >> documento; //INGRESAR EL NUMERO SELECCIONADO DE LA OPCION

    std::cout << "ruta: " <<documento<< std::endl;

    std::ifstream inputFile(documento);
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

        //agregar a la lista circular doble
        Circular.agragar(vuelo,numero_Registro,modelo,capacidad,aerolinea,estado,destino);

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

    std::cout << "INGRESE LA RUTA DEL ARCHIVO: " << std::endl; //ruta: C:/Users/ludwi/OneDrive/Escritorio/-201907608_EDD_Proyecto/aviones.json
    std::cin >> documento; //INGRESAR EL NUMERO SELECCIONADO DE LA OPCION

    std::cout << "ruta: " <<documento<< std::endl;

    std::ifstream inputFile(documento);
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

void Mensaje()
{
    std::cout << "||------------- Menu -------------||" << std::endl;
    std::cout << "|| 1. CARGAR AVIONES.             ||" << std::endl; //carga de archivo, falta implementacion de estructuras (arbol b y lista cricular)
    std::cout << "|| 2. CARGAR PILOTOS.             ||" << std::endl; 
    std::cout << "|| 3. CARGA RUTAS.                ||" << std::endl; 
    std::cout << "|| 4. CARGAR MOVIMIENTOS.         ||" << std::endl; 
    std::cout << "|| 5. CONSULTA HORAS DE VUELO.    ||" << std::endl;
    std::cout << "|| 6. RECOMENDAR RUTA             ||" << std::endl; 
    std::cout << "|| 7. VISUALIZAR REPORTES.        ||" << std::endl; 
    std::cout << "|| 8. SALIR.                      ||" << std::endl; 

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
            break;
        case 4:
            std::cout << "|| OPCION 4. CARGA DE MOVIMIENTOS. ||" << std::endl; 
            break;
        case 5:
            std::cout << "|| OPCION 5. CONSULTA DE HORA DE VUELO. ||" << std::endl; 
            break;
        
        case 6:
            std::cout << "|| OPCION 6. RECOMENDAR RUTA. ||" << std::endl; 
            break;
        
        case 7:

            std::cout << "|| OPCION 7. VISUALIZAR REPORTES. ||" << std::endl; 
            Circular.Reporte();
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



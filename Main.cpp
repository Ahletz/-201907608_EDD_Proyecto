#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

json leerJSON_Aviones() {
    
    std::string documento; //variable con nombre del documento

    std::cout << "INGRESE LA RUTA DEL ARCHIVO: " << std::endl;
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
        std::string fabricante = aviones["fabricante"];
        int ano_fabricacion = aviones["ano_fabricacion"];
        int capacidad = aviones["capacidad"];
        int peso_maximo = aviones["peso_max_despegue"];
        std::string aerolinea = aviones["aerolinea"];
        std::string estado = aviones["estado"];

    //MOSTRAR LOS DATOS DEL JSCON CARGADOS
        std::cout<< vuelo<< std::endl;
        std::cout<< numero_Registro<< std::endl;
        std::cout<< modelo<< std::endl;
        std::cout<< fabricante<< std::endl;
        std::cout<< ano_fabricacion<< std::endl;
        std::cout<< capacidad<< std::endl;
        std::cout<< peso_maximo<< std::endl;
        std::cout<< aerolinea<< std::endl;
        std::cout<< estado<< std::endl;
        std::cout<< "-------------------------------------------------------------"<< std::endl;

        
    }

     return jsonData; // Retornar los datos JSON leídos

}




int main(int argc, char const *argv[])
{   

    bool exit = true; // VARIABLE DE SALIDA DEL CICLO
    int seleccion; //variable seleccion de menu
    
   

    while (exit)
    {
        std::cout << "||------------- Menu -------------||" << std::endl;
        std::cout << "|| 1. CARGAR AVIONES.             ||" << std::endl; 
        std::cout << "|| 2. CARGAR PILOTOS.             ||" << std::endl; 
        std::cout << "|| 3. CARGA RUTAS.                ||" << std::endl; 
        std::cout << "|| 4. CARGAR MOVIMIENTOS.         ||" << std::endl; 
        std::cout << "|| 5. CONSULTA HORAS DE VUELO.    ||" << std::endl;
        std::cout << "|| 6. RECOMENDAR RUTA             ||" << std::endl; 
        std::cout << "|| 7. VISUALIZAR REPORTES.        ||" << std::endl; 
        std::cout << "|| 8. SALIR.                      ||" << std::endl; 

        std::cin >> seleccion; //INGRESAR EL NUMERO SELECCIONADO DE LA OPCION

        if (seleccion == 8)
        {
            
        }

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



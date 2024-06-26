#ifndef LISTA_CIRCULAR
#define LISTA_CIRCULAR
#include <fstream> //para la creacion del archivo reporte
#include <cstdlib>  // Para system()
#include <iostream>

//LISTA CIRCULAR DOBLEMENTE ENLAZADA
struct NodoCircularD
{
    //VARIABLES DEL NODO 
    std::string vuelo;
    std::string numero_Registro;
    std::string modelo;
    int capacidad;
    std::string aerolinea;
    std::string estado;
    std::string destino;

    //siguiente y anterior de la lista
    NodoCircularD* next;
    NodoCircularD* prev;

    //constructor del nodo
    NodoCircularD(std::string& vuelo,std::string& numero_Registro, std::string& modelo,  int capacidad,  std::string& aerolinea, std::string& estado,std::string& destino)
    {
        this-> vuelo = vuelo;
        this-> numero_Registro = numero_Registro;
        this-> modelo = modelo;
        this-> capacidad = capacidad;
        this-> aerolinea = aerolinea;
        this-> estado = estado;
        this-> destino = destino;

        this->next = nullptr;
        this->prev = nullptr;
    }

};

class CircularDoble
{
    //creacion de la cabeza de la lista en clase privada
    private: 
    NodoCircularD* head;

    //metodos publicos de la clase para manipulacion
    public: 

    CircularDoble() //constructor para head -> nullo (vacio)
    {
        head = nullptr;

    }

    //metodo para mostrar contenido de la lista
    void Mostrar() 
    {
        if (head == nullptr)
        {
            std::cout<< "LISTA VACIA, NO SE ENCUENTRA NINGUN ELEMENTO DENTRO!"<< std::endl;
            return;
        }
        NodoCircularD* current = head; //variuable currrent apuntador de la cabeza de la lista

        //ciclo que recorre la lista
        do
        {   
            std::cout<< "-------------------------------------------------------------"<< std::endl;
            std::cout<< "-------------------------------------------------------------"<< std::endl;
            std::cout<<"|| NUMERO DE VUELO: "<<current->vuelo <<std::endl;
            std::cout<<"|| REGISTRO: "<<current->numero_Registro <<std::endl;
            std::cout<<"|| AEROLINEA: "<<current->aerolinea <<std::endl;
            std::cout<<"|| ESTADO: "<<current->estado <<std::endl;
            std::cout<< "-------------------------------------------------------------"<< std::endl;
            std::cout<< "-------------------------------------------------------------"<< std::endl;
            current = current -> next; //cambiamos al siguiente nodo que este apuntando

        } while (current != head); // si la variable ya no apunta a la cabeza y apunta a nulo termina ciclo
        std::cout<< std::endl; //salto de linea  
        
    }

    //metodo para mostrar contenido de la lista
    void agragar(std::string& vuelo,std::string& numero_Registro, std::string& modelo, int capacidad, std::string& aerolinea, std::string& estado, std::string& destino)
    {
        //instanciando el nuevo nodo
        NodoCircularD* newNodo = new NodoCircularD(vuelo, numero_Registro, modelo, capacidad, aerolinea, estado, destino);
        
        if (head == nullptr) //si no hay nodos dentro de la lista
        {
            head = newNodo; //nuevo nodo se vuelve cabeza
            newNodo->next = head; //siguiente que es si mismo
            newNodo->prev = head; //previo que es si mismo

        }else //si existe nodo en la lista 
        {
            NodoCircularD* tail = head->prev; // cola sera el anterior de la cabeza existente
            tail->next = newNodo; // el siguiente de la cola existente sera el nuevo nodo
            newNodo-> prev = tail; // el previo del nuevo nodo es la cola
            newNodo->next = head; //siguiente del nuevo nodo sera la cabeza (null)
            head->prev = newNodo; // el previo de la cabeza sera el nuevo nodo 
        }    

    }

    //metodo para eliminar un nodo en la lista circular 
    void eliminar(const std::string& numero_registro)
    {
        if (head == nullptr) //si no hay nodos en la cola 
        {
            std::cout<<"NO HAY ELEMENTOS PARA ELIMINAR" << std::endl;
            return;
        }

        NodoCircularD* current = head; //current contiene la cabeza de la lista circular
        do
        {
            if (current->numero_Registro == numero_registro) // si encuentra el numero de registro 
            {
                if (current->next == current) //si solo hay un nodo en la lista
                {
                    delete current; //eliminar de la memoria el nodo
                    head = nullptr; //cabeza apunta a nulo
                    return;
                }

                current->prev->next = current->next; //siguiente del anterior ahora sera siguiente
                current->next->prev = current->prev; //anterior del siguiente a hora apunta al previo 
                
                if (current == head)
                {
                    head = current->next;
                    return;
                }
                   
            }
            current = current->next; //avanzar en la lista
        } while (current != head);
        std::cout<< " AVION CON REGISTRO "<< numero_registro <<" NO ENCONTRADO"<<std::endl;    
        
    }




     void Reporte() {
        
    // Crear un objeto de salida de archivo
    std::ofstream archivo("listaCircularDoble.dot");

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo para escribir." << std::endl;
        return;
    }

    int contador = 0;

    // Crear una variable string vacía
    std::string contenido;

    contenido += "digraph G {\n"
                        "    rankdir=LR;\n"
                        "    node [shape=record];\n";


     if (head == nullptr)
        {
            std::cout<< "LISTA CIRCULAR VACIA, NO SE ENCUENTRA NINGUN ELEMENTO DENTRO!"<< std::endl;    
            return;
        }

         NodoCircularD* current = head; //variuable currrent apuntador de la cabeza de la lista

        //ciclo que recorre la lista
        do
        {   
            //std::cout<< ""<< std::endl;

            //llenar contenido
            std::string nodo = std::to_string(contador); //numero del nodo

           contenido += "nodo" + nodo + "[label=\""+current->numero_Registro+" \"];"; //contenido del nodo y creacion de los nodos

            contador ++; //aumento del contador
            current = current -> next; //cambiamos al siguiente nodo que este apuntando

        } while (current != head); // si la variable ya no apunta a la cabeza y apunta a nulo termina ciclo

        //llenando apuntadores
        for ( int i = 0; i <= contador; i++)
        {
            contenido +="nodo"+std::to_string(i) +"->"+"nodo"+std::to_string(i+1)+";"; //apuntar al siguiente
            
        }

        //llenado apuntadores regreso
        for ( int i = contador; i >= 0; i--)
        {
            contenido +="nodo"+std::to_string(i) +"->"+"nodo"+std::to_string(i-1)+";"; //apuntar al anterior
            
        }

        //ultimo apuntador inicio a final
        
        contenido +="nodo0 -> nodo"+std::to_string(contador-1)+";"; //apunta primero al ultimo

        contenido +="nodo"+std::to_string(contador) +"->"+"nodo 0;"; //apunta ultimo al primero



        contenido += "}" ;

    // Escribir el contenido en el archivo
    archivo << contenido;

    // Cerrar el archivo
    archivo.close();

   system("dot -Tpng listaCircularDoble.dot -o listaCircularDoble.png");
   system("start listaCircularDoble.png");

}

//funcion recuperar datos 
std::string ObtenerString(const std::string& numero_registro,const std::string& dato)
{
    if (head == nullptr)
        {
            std::string mensaje = "LISTA VACIA, NO SE ENCUENTRA NINGUN ELEMENTO DENTRO!";

             return mensaje;
        }
        NodoCircularD* current = head; //variuable currrent apuntador de la cabeza de la lista

        //ciclo que recorre la lista
        do
        {   
           
           if (numero_registro == current->numero_Registro)
           {

            if (dato == "vuelo")
            {
                return current->vuelo;

            }else if (dato == "modelo")
            {
                return current->modelo;

            }else if (dato == "aerolinea")
            {
               return current->aerolinea;

            }
            else if (dato == "destino")
            {
                return current->destino;

            }    
            
           }

            current = current -> next; //cambiamos al siguiente nodo que este apuntando

        } while (current != head); // si la variable ya no apunta a la cabeza y apunta a nulo termina ciclo   

        return "";   

}

//obtener int
int Obtenerint(const std::string& numero_registro,const std::string& dato)
{
    if (head == nullptr)
        {
            std::cout<< "LISTA VACIA, NO SE ENCUENTRA NINGUN ELEMENTO DENTRO!"<< std::endl;
            return -1;
        }
        NodoCircularD* current = head; //variuable currrent apuntador de la cabeza de la lista

        //ciclo que recorre la lista
        do
        {   
           
           if (numero_registro == current->numero_Registro)
           {

            if (dato == "capacidad")
            {
                return current->capacidad;

            }  
            
           }

            current = current -> next; //cambiamos al siguiente nodo que este apuntando

        } while (current != head); // si la variable ya no apunta a la cabeza y apunta a nulo termina ciclo      

}

};


#endif
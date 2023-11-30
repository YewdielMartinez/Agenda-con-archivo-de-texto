#ifndef AGREGAREVENTO_H
#define AGREGAREVENTO_H

#include <iostream>
#include <conio.h>//Libreria con funciones de control de entrada y salida
#include <string.h> // Libreria para hacer todas mayusculas
#include <ctime>//Libreria para el tiempo
#include <vector>//Libreria para los vectores
#include <chrono>//Libreria que sirve para el tiempo
#include <thread> //Libreria para los hilos
#include <iomanip>//Esta Libreria es para el get time
#include <string>
#include <sstream>
#include <algorithm> 
#include <fstream>
#include "Validaciones.h"
#include "Declaraciones.h"
#include "Funcionesarchivo.h"
#include "MenuPrincipal.h"

void Agregarevento() //Funcion agregar evento
{   
    //Declaracion de variables constantes etc....
    Evento eventof;
    const char* format = "%d/%m/%Y %H:%M";//Declaracion del formato para la fecha
    
    
    std::string HoraF_TiempoStr;//Declarar como string para leer la hora
    //Aqui empieza la funcion
        std::cout<<"----- Bienvenido al menu de agregar un evento -----"<<std::endl;

        do {
            std::cout << "Escribe el nombre del evento: " << std::endl;
            eventof.Nombre_Evento = ValidarPalabraConEspacios("Por favor ingrese un nombre para el evento");

            if (eventof.Nombre_Evento.empty()) {
            std::cout << "El nombre del evento no puede estar vacío. Intente de nuevo." << std::endl;
            continue;
        }

            break;

        } while (true);
    // Validar la descripción del evento
        do {
            std::cout << "Escribe la descripción del evento: " << std::endl;
            eventof.Descripcion_Evento = ValidarTextoConEspacios("Por favor ingrese una descripción para el evento");

            if (eventof.Descripcion_Evento.empty()) {
                std::cout << "La descripción del evento no puede estar vacía. Intente de nuevo." << std::endl;
                continue;
            }

            break;

        } while (true);
        //Aqui agregamos la fecha del evento y la hora 
        do 
        {
            std::cout << "Escribe la Fecha y hora del evento del evento en este formato (Dia/Mes/Año Hora:Minutos): ";
            std::string HoraF_TiempoStr;
            std::getline(std::cin, HoraF_TiempoStr);
                

            try {
                std::tm tm = {};
                std::istringstream timestream(HoraF_TiempoStr);
                timestream >> std::get_time(&tm, format);//Aqui valida que el tiempo que ya esta convertido a tiempo este en el formato correcto 
                if (timestream.fail()) 
                {
                throw std::runtime_error("Formato de fecha y hora  incorrecto(Dia/Mes/Año Hora:Minutos)");
                }
                // Validación para febrero en años bisiestos y no bisiestos
                int year = tm.tm_year + 1900; // tm.tm_year devuelve años desde 1900
                int month = tm.tm_mon + 1; // tm.tm_mon devuelve meses desde 0 (enero)
                int day = tm.tm_mday;

                bool esBisiesto = (year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0));

                if ((month == 2 && (esBisiesto && day > 29 || !esBisiesto && day > 28)) ||
                (month < 1 || month > 12 || day < 1 || day > 31)) {
                throw std::runtime_error("Fecha inválida para febrero.");
                }
                 // Validar que la fecha es posterior a la actual
                std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                if (std::mktime(&tm) <= currentTime) {
                throw std::runtime_error("La fecha y hora del evento deben ser posteriores a la actual");
                }
                
                eventof.FechaHora_Tiempo = std::chrono::system_clock::from_time_t(std::mktime(&tm));
                // Si llegamos aquí, la hora es válida
                break;
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        

        }while(true);

        agenda.push_back(eventof);
        GuardarEnArchivo();
        std::cout << "Evento agregado correctamente." << std::endl;
        if (validarRespuesta()){
        MenuPrincipal();
        
        }else{
        Agregarevento();
        }


}
void Modificarevento() {
    CargarDesdeArchivo();
        int indice {0};

        std::cout << "Lista de eventos en tu agenda:" << std::endl;
        for (size_t i = 0; i < agenda.size(); ++i) {
            std::cout << i + 1 << ". " << agenda[i].Nombre_Evento << std::endl;
        }

        while (true) {
            std::cout << "Ingrese el índice del evento que desea modificar (0 para cancelar): ";
            indice = pedirNumero();

            if (indice == 0) {
                // El usuario eligió cancelar
                MenuPrincipal();
                return;
            }

            if (indice >= 1 && static_cast<size_t>(indice) <= agenda.size()) {
                break; // Índice válido, salir del bucle
            } else {
                std::cout << "Índice de evento no válido. Intente de nuevo." << std::endl;
            }
        }

        Evento& eventof = agenda[indice - 1];
            do {
                std::cout << "Escribe el nuevo nombre del evento: " << std::endl;
                eventof.Nombre_Evento = ValidarPalabraConEspacios("Por favor ingrese un nombre para el evento");

                if (eventof.Nombre_Evento.empty()) {
                    std::cout << "El nombre del evento no puede estar vacío. Intente de nuevo." << std::endl;
                    continue;
                }

                break;

            } while (true);

                //Aqui agregamos la descripcion de el evento
            do {
                std::cout << "Escribe la nueva descripción del evento: " << std::endl;
                eventof.Descripcion_Evento = ValidarTextoConEspacios("Por favor ingrese una descripción para el evento");

                if (eventof.Descripcion_Evento.empty()) {
                    std::cout << "La descripción del evento no puede estar vacía. Intente de nuevo." << std::endl;
                    continue;
                }

                break;

            } while (true);

        const char* format = "%d/%m/%Y %H:%M";
        do {
            std::cout << "Ingrese la nueva fecha y hora (Dia/Mes/Año Hora/Minutos): ";
            std::string HoraF_TiempoStr;
            std::getline(std::cin, HoraF_TiempoStr);

            try {
                std::tm tm = {};
                std::istringstream timestream(HoraF_TiempoStr);
                timestream >> std::get_time(&tm, format);

                if (timestream.fail()) {
                    throw std::runtime_error("Formato de hora incorrecto. (Dia/Mes/Año Hora:Minutos)");
                }

                int year = tm.tm_year + 1900;
                int month = tm.tm_mon + 1;
                int day = tm.tm_mday;
                bool esBisiesto = (year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0));

                if ((month == 2 && (esBisiesto && day > 29 || !esBisiesto && day > 28)) ||
                    (month < 1 || month > 12 || day < 1 || day > 31)) {
                    throw std::runtime_error("Fecha inválida para febrero.");
                }
                 // Validar que la fecha es posterior a la actual
                std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                if (std::mktime(&tm) <= currentTime) {
                throw std::runtime_error("La fecha y hora del evento deben ser posteriores a la actual");
                }
                eventof.FechaHora_Tiempo = std::chrono::system_clock::from_time_t(std::mktime(&tm));
                break;
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        } while (true);

        std::cout << "Evento modificado correctamente." << std::endl;
        GuardarEnArchivo(); // Guardar los cambios en el archivo


    if (validarRespuesta()) {
        MenuPrincipal();
    } else {
        Modificarevento();
    }
}





#endif

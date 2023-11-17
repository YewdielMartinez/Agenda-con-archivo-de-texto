#ifndef TIEMPORESTANTE_H
#define TIEMPORESTANTE_H
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
#include "Funcionesarchivo.h"
#include "Declaraciones.h"
#include "MenuPrincipal.h"

void TiempoRestante() {//Funcion para calcular el tiempo restante para el evento
    Evento eventof;
    auto ahora = std::chrono::system_clock::now();
 
    for(const Evento& eventof : agenda){
       // Considerando el primer evento en la agenda
        auto tiempo_evento = eventof.FechaHora_Tiempo;//Aqui esta el tiempo del evento
        std::chrono::duration<double> tiempo_restante = std::chrono::duration_cast<std::chrono::seconds>(tiempo_evento - ahora);//Aqui se declara el tiempo restante restando el tiempo del evento con el actual
       
             //Aqui hace los calculos para convertir el tiempo de segundos a dias,horas,minutos y segundos
            int dias = std::chrono::duration_cast<std::chrono::hours>(tiempo_restante).count() / 24;
            int horas = std::chrono::duration_cast<std::chrono::hours>(tiempo_restante).count() % 24;
            int minutos = std::chrono::duration_cast<std::chrono::minutes>(tiempo_restante).count() % 60;
            int segundos = std::chrono::duration_cast<std::chrono::seconds>(tiempo_restante).count() % 60;

            std::cout << "Tiempo restante hasta el evento '" << eventof.Nombre_Evento << "': ";//aqui muestra el nombre del evento
                if (dias > 0) {//aqui si los dias son mayores que 0 va a mostrar los dias
                std::cout << dias << " días, ";
                }
                std::cout << horas << " horas, " << minutos << " minutos y " << segundos << " segundos." << std::endl;//Sino va a mostrar horas minutos y segundos
        if(agenda.empty()) {
        std::cout << "No hay eventos en la agenda." << std::endl;
        }
    } 
   

}
void MostrarEventosCercanos() {
    CargarDesdeArchivo(); // Cargar datos desde el archivo antes de mostrar eventos cercanos
    auto ahora = std::chrono::system_clock::now();
    auto dosSemanas = ahora + std::chrono::hours(24 * 14); // Dos semanas desde ahora

    bool hayEventosCercanos = false;

    for (const Evento& eventof : agenda) {
        auto tiempo_evento = eventof.FechaHora_Tiempo;

        if (tiempo_evento >= ahora && tiempo_evento <= dosSemanas) {
            auto tiempo_restante = std::chrono::duration_cast<std::chrono::seconds>(tiempo_evento - ahora);

            int dias = std::chrono::duration_cast<std::chrono::hours>(tiempo_restante).count() / 24;
            int horas = std::chrono::duration_cast<std::chrono::hours>(tiempo_restante).count() % 24;
            int minutos = std::chrono::duration_cast<std::chrono::minutes>(tiempo_restante).count() % 60;
            int segundos = std::chrono::duration_cast<std::chrono::seconds>(tiempo_restante).count() % 60;

            std::cout << "Evento próximo en la agenda: '" << eventof.Nombre_Evento << "' - ";
            if (dias > 0) {
                std::cout << dias << " días, ";
            }
            std::cout << horas << " horas, " << minutos << " minutos y " << segundos << " segundos." << std::endl;
            hayEventosCercanos = true;
        }
    }

    if (!hayEventosCercanos) {
        std::cout << "No hay eventos próximos en las próximas dos semanas." << std::endl;
    }

    GuardarEnArchivo(); // Guardar los cambios en el archivo después de mostrar los eventos cercanos

    if (validarRespuesta()) {
        MenuPrincipal();
    } else {
        MostrarEventosCercanos();
    }
}

#endif
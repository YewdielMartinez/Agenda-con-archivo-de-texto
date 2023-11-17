#ifndef VERAGENDA_H
#define VERAGENDA_H
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
#include "Declaraciones.h"
#include "Validaciones.h"
#include "MenuPrincipal.h"
#include "Funcionesarchivo.h"
void Veragenda() {
    CargarDesdeArchivo(); // Cargar datos desde el archivo antes de mostrar la agenda
    std::cout << "Agenda de Eventos:" << std::endl;

    for (size_t i = 0; i < agenda.size(); ++i) {
        const Evento& eventof = agenda[i];
        std::time_t tiempoEvento = std::chrono::system_clock::to_time_t(eventof.FechaHora_Tiempo);
        std::cout << "Índice: " << i + 1 << std::endl;
        std::cout << "Nombre: " << eventof.Nombre_Evento << std::endl;
        std::cout << "Descripción: " << eventof.Descripcion_Evento << std::endl;
        std::cout << "Fecha y hora: " << std::put_time(std::localtime(&tiempoEvento), format) << std::endl;
        std::cout << std::endl;
        
    }
    TiempoRestante();
    MenuPrincipal();
}
#endif
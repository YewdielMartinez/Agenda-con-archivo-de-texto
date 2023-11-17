#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <iostream>
#include <ctime>//Libreria para el tiempo
#include <vector>//Libreria para los vectores
#include <chrono>//Libreria que sirve para el tiempo
#include <thread> //Libreria para los hilos
#include <iomanip>//Esta Libreria es para el get time
#include <string>
#include <sstream>
#include <algorithm> 
#include <fstream>
#include <limits>
#include "Funcionesarchivo.h"
#include "Declaraciones.h"

double pedirNumeroM() {
    double numero{ 0 };
    bool inputCorrecto = false;

    do {
        std::cin >> numero;
        if (std::cin.fail() || numero < 1 || numero > 6) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Por favor, ingrese un número válido del 1 al 6: ";
        } else {
            inputCorrecto = true;
        }
    } while (!inputCorrecto);

    return numero;
}

double pedirNumero()
{

  double numero{ 0 };
  // Valida que sea un numero, diferente a cero y no contenga nada despues
  do
  {
    if (std::cin >> numero && std::cin.peek() == '\n')
    {
      std::cin.ignore(); // Limpiar el buffer despues de obtener el numero
      return numero;
    }
    else
    {
      // Limpia el cin y sus errores para pedir otra vez el numero
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Ingresa solamente un numero valido por favor." << std::endl;
    }
  } while (true);

}
bool validarRespuesta() {
    std::string respuesta;
    std::cout << "Quiere regresar al Menu Principal (SI/NO): ";
    std::cin >> respuesta;

    // Convertir la respuesta a mayúsculas usando std::transform
    std::transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::toupper);

    while (true) {
        if (respuesta == "SI") {
            return true;
        } else if (respuesta == "NO") {
            return false;
        } else {
            std::cout << "Respuesta inválida. Por favor, ingrese 'SI' o 'NO'." << std::endl;
            std::cout << "Quiere regresar al Menu Principal (SI/NO): ";
            std::cin >> respuesta;
            std::transform(respuesta.begin(), respuesta.end(), respuesta.begin(), ::toupper);
        }
    }
}
#endif
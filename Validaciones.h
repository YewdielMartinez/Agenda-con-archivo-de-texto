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
#include <regex>
#include <cctype>
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
bool tieneEspaciosVacios(const std::string& str) {
    return std::all_of(str.begin(), str.end(), isspace);
}
void cerrarPrograma() {
    std::cout << "Cerrando el programa. Adiós.\n";
    exit(0); // Puedes usar otro valor si prefieres un código de salida diferente
}
bool ValidarCaracter(const std::string& dato_ingresado) { 
    for (char es_palabra : dato_ingresado) { //Se crea una variable tipo char 'es_palabra' que recorre la cadena dato_ingresado caracter por caracter.
        if (!std::isalpha(es_palabra) && !std::isspace(es_palabra)) { //isalpha verifica caracter por caracter si es una palabra
            return false; //Si encontramos un caracter que NO es un caracter se retorna false
        }
    }
    return true; //Si llegamos hasta aqui se retorna true y la caden es una palabra valida 
}
std::string ValidarPalabra(std::string mensaje) {
    std::string palabra_ingresada; //Se crea una variable string llamada "palabra_ingresada"
    while (true) {
        std::getline(std::cin, palabra_ingresada); //La entrada del ususario se guarda en la variable palabra_ingresada
        if (ValidarCaracter(palabra_ingresada)){ //Se llama a la funcion val_caracter y se le manda el dato ingresado por el usuario
            return palabra_ingresada;//Si es una palabra se regresa la palabra ingresada por el usuario
        } else { //Si no se cumple se muesta este mensaje al usuario hasta que ingrese el dato correcto
            std::cout<<mensaje<<std::endl;
        }
    }
}
// Función para validar que la palabra no contenga caracteres especiales
bool ValidarPalabraC(const std::string &palabra, const std::string &mensaje) {
    std::regex regexPatron("^[a-zA-Z0-9 ]+$");  // Patrón que permite letras, números y espacios
    if (!std::regex_match(palabra, regexPatron)) {
        std::cout << mensaje << std::endl;
        return false;
    }
    return true;
}
bool tieneCaracteresEspeciales(const std::string& str) {
    return !std::all_of(str.begin(), str.end(), [](unsigned char c) {
        return std::isalnum(c);
    });
}

// Función para validar si una cadena tiene espacios en blanco al comienzo o al final
bool tieneEspaciosEnBlanco(const std::string& str) {
    return !str.empty() && (std::isspace(str.front()) || std::isspace(str.back()));
}

// Función para validar si una cadena contiene solo letras y espacios
bool contieneSoloLetrasYEspacios(const std::string& str) {
    for (char c : str) {
        if (!std::isalpha(c) && !std::isspace(c)) {
            return false;
        }
    }
    return true;
}

// Función para ingresar y validar una palabra con espacios
std::string ValidarPalabraConEspacios(const std::string& mensaje) {
    std::string input;
    do {
        std::cout << mensaje << std::endl;
        std::getline(std::cin, input);

        if (tieneEspaciosEnBlanco(input)) {
            std::cout << "No se permiten espacios en blanco al comienzo o al final. Intente de nuevo." << std::endl;
            continue;
        }

        size_t lastPos = input.find_last_of(" ");
        if (lastPos != std::string::npos && !std::isalpha(input[lastPos + 1])) {
            std::cout << "No se permiten caracteres especiales después de las palabras. Intente de nuevo." << std::endl;
            continue;
        }

        if (!contieneSoloLetrasYEspacios(input)) {
            std::cout << "La cadena solo puede contener letras y espacios. Intente de nuevo." << std::endl;
            continue;
        }

        break;

    } while (true);

    return input;
}
std::string ValidarTextoConEspacios(const std::string& mensaje) {
    std::string input;
    do {
        std::cout << mensaje << std::endl;
        std::getline(std::cin, input);

        if (tieneEspaciosEnBlanco(input)) {
            std::cout << "No se permiten espacios en blanco al comienzo o al final. Intente de nuevo." << std::endl;
            continue;
        }

        size_t lastPos = input.find_last_of(" ");
        if (lastPos != std::string::npos && !std::isalpha(input[lastPos + 1])) {
            std::cout << "No se permiten caracteres especiales después de las palabras. Intente de nuevo." << std::endl;
            continue;
        }

        if (!contieneSoloLetrasYEspacios(input)) {
            std::cout << "El texto solo puede contener letras y espacios. Intente de nuevo." << std::endl;
            continue;
        }

        break;

    } while (true);

    return input;
}
#endif
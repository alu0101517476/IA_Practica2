#include <fstream>
#include <iostream>
#include <vector>

#include "herramientas.h"
#include "laberinto.h"
#include "nodo.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Error, introduzca el nombre del fichero" << std::endl;
    exit(1);
  }
  std::string nombre_fichero(argv[1]), nombre_instancia;
  // Obtenemos el nombre de la instancia del laberinto
  size_t posicion_punto{nombre_fichero.find('.')};
  if (posicion_punto != std::string::npos) {
    nombre_instancia = nombre_fichero.substr(0, posicion_punto);
  } else {
    nombre_instancia = nombre_fichero;
  }
  Laberinto laberinto{nombre_fichero};
  std::cout << "¿Cómo desea ejecutar el programa?\n1) Cambiar casilla inicial "
               "y final\n2) Laberinto por defecto"
            << std::endl;
  int opcion;
  std::cin >> opcion;
  switch (opcion) {
    case 1: // Cambiar casilla inicial y final
      laberinto.CambiarCasillas();
      std::cout << laberinto << std::endl;
      break;
    case 2: // Laberinto por defecto
      std::cout << laberinto << std::endl;
      break;
    default:
      std::cout << "Error, Opción no válida";
      exit(1);
  } 
  std::cout << "Desea aplicar el algoritmo A* con la heurística de la distancia Manhattan o la Euclídea?\n1) Manhattan\n2) Euclídea" << std::endl;
  std::cin >> opcion;
  switch (opcion) {
    case 1: // Algoritmo A* con heurística Manhattan
      if (laberinto.AlgoritmoAEstrellaManhattan().empty()) {
        std::cout << "No se ha encontrado solución para el algoritmo A* con la heurística Manhattan" << std::endl;
        exit(1);
      } else {
        std::cout << "El camino es el siguiente: " << std::endl;
        laberinto.MostrarCamino();
        laberinto.MostrarEstadisticas(nombre_instancia);
        std::cout << std::endl;
      }
      break;
    case 2: // Algoritmo A* con heurística Euclídea
      if (laberinto.AlgoritmoAEstrellaEuclidea().empty()) {
        std::cout << "No se ha encontrado solución para el algoritmo A* con la heurística Euclídea" << std::endl;
        exit(1);
      } else {
        std::cout << "El camino es el siguiente: " << std::endl;
        laberinto.MostrarCamino();
        laberinto.MostrarEstadisticas(nombre_instancia);
        std::cout << std::endl;
      }
      break;
    default:
      std::cout << "Error, Opción no válida";
      exit(1);
  }
  return 0;
}
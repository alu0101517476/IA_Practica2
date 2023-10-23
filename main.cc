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
  std::string nombre_fichero(argv[1]);
  Laberinto laberinto{nombre_fichero};
  std::cout << "¿Cómo desea ejecutar el programa?\n1) Cambiar casilla inicial "
               "y final\n2) Laberinto por defecto"
            << std::endl;
  int opcion;
  std::cin >> opcion;
  switch (opcion) {
    case 1:
      laberinto.CambiarCasillas();
      std::cout << laberinto << std::endl;
      break;
    case 2:
      std::cout << laberinto << std::endl;
      break;
    default:
      std::cout << "Opción no válida";
      exit(1);
  } 
  if (laberinto.AlgoritmoAEstrella().empty()) {
    std::cout << "No se ha encontrado solución para el algoritmo A*" << std::endl;
    exit(1);
  }
  std::cout << "El camino es el siguiente: " << std::endl;
  laberinto.MostrarCamino();
  std::cout << std::endl;
  return 0;
}
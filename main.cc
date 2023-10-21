#include <iostream>
#include <fstream>
#include <vector>

#include "laberinto.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Error, introduzca el nombre del fichero" << std::endl;
    exit(1);
  } 
  std::string nombre_fichero(argv[1]);
  Laberinto laberinto{nombre_fichero};
  std::cout << laberinto << std::endl;
  return 0;  
}
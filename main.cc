#include <iostream>
#include <fstream>
#include <vector>

#include "laberinto.h"

int main(int argc, char* argv[]) {
  std::string nombre_fichero(argv[1]);
  Laberinto laberinto{nombre_fichero};
  std::cout << laberinto << std::endl;
  return 0;  
}
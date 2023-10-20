#include "laberinto.h"

// Constructor por defecto
Laberinto::Laberinto(std::string& nombre_fichero) {
  std::ifstream fichero_laberinto;
  fichero_laberinto.open(nombre_fichero.c_str(), std::ios::in);
  LeerFichero(fichero_laberinto);
  fichero_laberinto.close();
}

Laberinto::~Laberinto() {
  for (int i{0}; i < laberinto_.size(); ++i) {
    laberinto_[i].clear();
  }
}

// Método que se encarga de leer el fichero y guardar la información para construir el laberinto
void Laberinto::LeerFichero(std::ifstream& fichero_laberinto) {
  fichero_laberinto >> numero_columnas_ >> numero_filas_;
  laberinto_ = std::vector<std::vector<unsigned>>{
      numero_columnas_, std::vector<unsigned>(numero_filas_)};
  for (int i{0}; i < numero_columnas_; ++i) {
    for (int j{0}; j < numero_filas_; ++j) {
      unsigned identificacion;
      fichero_laberinto >> identificacion;
      // std::cout << identificacion << " ";
      //  Guardamos la entrada en caso de que se cumpla la condición
      if (identificacion == INICIO) {
        x_inicio_ = i;
        y_inicio_ = j;
      } else if (identificacion == FINAL) {
        x_final_ = i;
        y_final_ = j;
      }
      laberinto_[i][j] = identificacion;
    }
  }
}

// Método que comprueba si el movimiento que se va a realizar es válido
bool Laberinto::EsValido(const unsigned fila, const unsigned columna) const {
  return (fila <= numero_filas_ && fila >= 0 && columna <= numero_columnas_ &&
          columna >= 0 && laberinto_[columna][fila] != PARED);
}

// Método que resuelve el laberinto mediante el algoritmo A*
void Laberinto::AlgoritmoAEstrella() {
  // Guía hecha por chatgpt -> no comprueba si el movimiento es válido
}

// Sobrecarga de operador << para mostrar el laberinto por pantalla
std::ostream& operator<<(std::ostream& os, const Laberinto& laberinto) {
  for (int i{0}; i < laberinto.laberinto_.size(); ++i) {
    for (int j{0}; j < laberinto.laberinto_[i].size(); ++j) {
      switch (laberinto.laberinto_[i][j]) {
        case INICIO:
          os << CARACTER_ENTRADA;
          break;
        case FINAL:
          os << CARACTER_SALIDA;
          break;

        case PASADIZO:
          os << CARACTER_PASADIZO;
          break;
        case PARED:
          os << CARACTER_PARED;
          break;

        default:
          break;
      }
    }
    os << std::endl;
  }
  return os;
}
#ifndef LABERINTO_H
#define LABERINTO_H

#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <vector>

#include "herramientas.h"
#include "nodo.h"

// Definimos algunas declarativas correspondientes con el fichero que hacen que
// sea más claro de visualizar el código
#define PARED 1
#define PASADIZO 0
#define INICIO 3
#define FINAL 4

// Definimos char para mostrar por pantalla el laberinto
#define CARACTER_PARED "█"
#define CARACTER_PASADIZO ' '
#define CARACTER_ENTRADA 'S'
#define CARACTER_SALIDA 'E'

class Nodo;

// definimos el enum de movimientos:
enum direction_t { N, E, S, W, NW, NE, SW, SE };

// define array de desplazamiento en las 8 direcciones:
//                  N  E  S  W  NW  NE  SW  SE
const short y[] = {-1, 0, 1, 0, -1, -1, 1, 1};
const short x[] = {0, 1, 0, -1, -1, 1, -1, 1};

class Laberinto {
 public:
  // Constructor que inicializa el laberinto a partir de el nombre del fichero
  Laberinto(std::string& nombre_fichero);
  // Destructor
  ~Laberinto();
  // Método que se encarga de leer el fichero y guardar la información
  void LeerFichero(std::ifstream& fichero_laberinto);
  // Método que comprueba si un movimiento es válido
  bool EsMovimientoValido(const unsigned x, const unsigned y) const;
  bool EsCoordenadaValida(const unsigned x, const unsigned y) const;
  // Método que resuelve el laberinto mediante el algoritmo A*
  void AlgoritmoAEstrella();
  // Método que muestra la solución
  void MostrarCamino();
  // Setter
  void SetCasillaInicial(const unsigned x_inicial, const unsigned y_inicio);
  void SetCasillaFinal(const unsigned x_final, const unsigned y_final);
  // Sobrecarga de operador << para mostrar el laberinto
  friend std::ostream& operator<<(std::ostream& os, const Laberinto& laberinto);

 private:
  // Coordenadas iniciales
  unsigned x_inicio_, y_inicio_;
  // Coordenadas finales
  unsigned x_final_, y_final_;
  // Número de filas y columnas
  unsigned numero_filas_, numero_columnas_;
  // Vector de vectores que guarda todo el laberinto
  std::vector<std::vector<unsigned>> laberinto_;
  // Set de nodos que guarda la solución dada por el algoritmo A*
  std::set<Nodo*> solucion_;
};

std::ostream& operator<<(std::ostream& os, const Laberinto& laberinto);

#endif
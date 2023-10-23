#pragma once

#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <vector>
#include <iomanip>

#include "herramientas.h"
#include "nodo.h"

// Definimos algunas declarativas correspondientes con el fichero que hacen que
// sea más claro de visualizar el código
#define PARED 1
#define PASADIZO 0
#define INICIO 3
#define FINAL 4
#define CAMINO 5

// Definimos char para mostrar por pantalla el laberinto
#define CARACTER_PARED "█"
#define CARACTER_PASADIZO ' '
#define CARACTER_ENTRADA 'S'
#define CARACTER_SALIDA 'E'
#define CARACTER_CAMINO 'X'

// definimos el enum de movimientos:
enum coordenadas { N, E, S, W, NW, NE, SW, SE };

// define array de desplazamiento en las 8 direcciones:
//                  N  E  S  W  NW  NE  SW  SE
const short y[] = {-1, 0, 1, 0, -1, -1, 1, 1};  // Coordenadas columnas
const short x[] = {0, 1, 0, -1, -1, 1, -1, 1};  // Coordenadas filas

class Laberinto {
 public:
  // Constructor que inicializa el laberinto a partir de el nombre del fichero
  Laberinto(std::string& nombre_fichero);
  // Destructor
  ~Laberinto();
  // Método que se encarga de leer el fichero y guardar la información
  void LeerFichero(std::ifstream& fichero_laberinto);
  // Método que comprueba si un movimiento es válido
  bool EsMovimientoValido(const int x, const int y) const;
  bool EsCoordenadaValida(const unsigned x, const unsigned y) const;
  // Método que resuelve el laberinto mediante el algoritmo A* con heurística Manhattan
  std::set<Nodo> AlgoritmoAEstrellaManhattan();
  // Método que resuelve el laberinto mediante el algoritmo A* con heurística Euclídea
  std::set<Nodo> AlgoritmoAEstrellaEuclidea();
  // Método que muestra la solución por pantalla de manera gráfica
  void MostrarCamino();
  // Getters
  std::set<Nodo> GetCamino() const { return camino_; }
  // Método que muestra estadísticas del laberinto en un fichero de salida
  void MostrarEstadisticas(const std::string& nombre_instancia);
  // Método que muestra estadísticas del laberinto en un fichero de salida cuando no ha habido camino solución
  void MostrarEstadisticasSinCamino(const std::string& nombre_instancia);
  // Setters
  void SetCasillaInicial(const unsigned x_inicial, const unsigned y_inicio);
  void SetCasillaFinal(const unsigned x_final, const unsigned y_final);
  void SetCamino(const std::set<Nodo>& camino) { camino_ = camino; }
  // Método para cambiar la casilla inicial y final a elección del usuario
  void CambiarCasillas();
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
  // Multiset de nodos que guarda los nodos generados
  std::multiset<Nodo> nodos_generados_;
  // Multiset de nodos que guarda los nodos inspeccionados
  std::multiset<Nodo> nodos_inspeccionados_;
  // Set de nodos que guarda el camino hallado con el algoritmo A*
  std::set<Nodo> camino_;
  // Coste final del camino
  unsigned coste_final_camino_;
};

std::ostream& operator<<(std::ostream& os, const Laberinto& laberinto);

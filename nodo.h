#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <cmath>

class Laberinto;

// Clase Nodo que representa a cada casilla del laberinto
class Nodo {
 public:
  // Constructor por defecto
  Nodo();
  // Constructor que inicializa todos los valores de el nodo
  Nodo(Nodo* padre, unsigned coordenada_fila, unsigned coordenada_columna,
       unsigned coste_acumulado, unsigned funcion_heuristica,
       unsigned funcion_evaluacion);
  // Getters
  Nodo* GetPadre() { return padre_; }
  unsigned GetCoordenadaFila() { return coordenada_fila_; }
  unsigned GetCoordenadaColumna() { return coordenada_columna_; }
  unsigned GetCosteAcumulado() { return coste_acumulado_; }
  unsigned GetFuncionHeuristica() { return funcion_heuristica_; }
  unsigned GetFuncionEvaluacion() { return funcion_evaluacion_; }
  // Setters
  void SetPadre(Nodo* padre) { padre_ = padre; }
  void SetCosteAcumulado(const unsigned coste_acumulado) { coste_acumulado_ = coste_acumulado; }
  void SetFuncionEvaluacion(const unsigned funcion_evalacion) { funcion_evaluacion_ = funcion_evalacion; }
  // Método para calcular la función heurística
  unsigned CalcularFuncionHeuristica(const unsigned coordenada_fila_final, const unsigned coordenada_columna_final);
  unsigned CalcularCosteAcumulado(const unsigned movimiento_nuevo);
  unsigned CalcularFuncionEvaluacion(const unsigned coste_acumulado, const unsigned funcion_heuristica);

  // Sobrecarga de operadores
  bool operator<(Nodo* nodo2);
  bool operator<(Nodo nodo2);
  bool operator==(Nodo* nodo2);
  bool operator==(Nodo nodo2);
  bool operator()(Nodo* nodo1 ,Nodo* nodo2);
 private:
  Nodo* padre_;
  // La coordenada de la fila dónde está la celda
  unsigned coordenada_fila_;
  // La coordenada de la columna dónde está la celda
  unsigned coordenada_columna_;
  // Este atributo representa la g(n) de la celda
  unsigned coste_acumulado_;
  // Este atributo representa la h(n) de la celda
  unsigned funcion_heuristica_;
  // Este atributo representa f(n) = g(n) + h(n) de la celda
  unsigned funcion_evaluacion_;
};

// struct hecho para poder comparar 2 nodo* y que se puedan almacenar en un set
struct ComparativaNodos {
  bool operator()(Nodo* nodo1 ,Nodo* nodo2) {
    return nodo1 < nodo2;
  }
};

#endif
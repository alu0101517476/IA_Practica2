#pragma once

#include <cmath>
#include <iostream>
#include <set>

// Clase Nodo que representa a cada casilla del laberinto
class Nodo {
 public:
  // Constructor por defecto
  Nodo();
  // Constructor que inicializa todos los valores de el nodo
  Nodo(Nodo* padre, unsigned coordenada_fila, unsigned coordenada_columna,
       unsigned coste_acumulado, unsigned funcion_heuristica,
       unsigned funcion_evaluacion);
  // Constructor de copia
  Nodo(const Nodo& nodo2);
  // Constructor de copia para convertir un Nodo* a un Nodo
  Nodo(const Nodo* nodo2);
  // Getters
  Nodo* GetPadre() { return padre_; }
  unsigned GetCoordenadaFila() const { return coordenada_fila_; }
  unsigned GetCoordenadaColumna() const { return coordenada_columna_; }
  unsigned GetCosteAcumulado() const { return coste_acumulado_; }
  unsigned GetFuncionHeuristica() const { return funcion_heuristica_; }
  unsigned GetFuncionEvaluacion() const { return funcion_evaluacion_; }
  // Setters
  void SetPadre(Nodo* padre) { padre_ = padre; }
  void SetCosteAcumulado(const unsigned coste_acumulado) {
    coste_acumulado_ = coste_acumulado;
  }
  void SetFuncionEvaluacion(const unsigned funcion_evalacion) {
    funcion_evaluacion_ = funcion_evalacion;
  }
  // Método para calcular la función heurística
  unsigned CalcularHeuristicaNodo(const unsigned coordenada_fila_final,
                                  const unsigned coordenada_columna_final);
  unsigned CalcularCosteAcumulado(const unsigned movimiento_nuevo);
  unsigned CalcularFE(const unsigned coste_acumulado,
                      const unsigned funcion_heuristica);

  // Sobrecarga de operadores
  bool operator<(Nodo* nodo2) const;
  bool operator<(const Nodo& nodo2) const;
  bool operator==(Nodo* nodo2) const;
  bool operator==(const Nodo& nodo2) const;
  friend std::ostream& operator<<(std::ostream& os, Nodo nodo);
  // bool operator()(Nodo* nodo1 ,Nodo* nodo2) const;
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

std::ostream& operator<<(std::ostream& os, Nodo nodo);

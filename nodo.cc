#include "nodo.h"

// Constructor por defecto
Nodo::Nodo() {
  padre_ = NULL;
  coordenada_fila_ = 0;
  coordenada_columna_ = 0;
  coste_acumulado_ = 0;
  funcion_heuristica_ = 0;
  funcion_evaluacion_ = 0;
}

// Constructor por parámetros
Nodo::Nodo(Nodo* padre, unsigned coordenada_fila, unsigned coordenada_columna,
           unsigned coste_acumulado, unsigned funcion_heuristica,
           unsigned funcion_evaluacion) {
  padre_ = NULL;
  coordenada_fila_ = coordenada_fila;
  coordenada_columna_ = coordenada_columna;
  coste_acumulado_ = coste_acumulado;
  funcion_heuristica_ = funcion_heuristica;
  funcion_evaluacion_ = funcion_evaluacion;
}

unsigned Nodo::CalcularFuncionHeuristica(const unsigned coordenada_fila_final, const unsigned coordenada_columna_final) {
  return static_cast<unsigned>((abs(coordenada_fila_final - coordenada_fila_) + abs(coordenada_columna_final - coordenada_columna_)) * 3);
}

bool Nodo::operator<(Nodo* nodo2) { 
  return funcion_evaluacion_ < nodo2->funcion_evaluacion_; 
}

bool Nodo::operator==(Nodo* nodo2) { 
  return funcion_evaluacion_ == nodo2->funcion_evaluacion_;
}
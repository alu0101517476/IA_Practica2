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
  padre_ = padre;
  coordenada_fila_ = coordenada_fila;
  coordenada_columna_ = coordenada_columna;
  coste_acumulado_ = coste_acumulado;
  funcion_heuristica_ = funcion_heuristica;
  funcion_evaluacion_ = funcion_evaluacion;
}

// Constructor de copia
Nodo::Nodo(const Nodo& nodo2) {
  padre_ = nodo2.padre_;
  coordenada_fila_ = nodo2.coordenada_fila_;
  coordenada_columna_ = nodo2.coordenada_columna_;
  coste_acumulado_ = nodo2.coste_acumulado_;
  funcion_heuristica_ = nodo2.funcion_heuristica_;
  funcion_evaluacion_ = nodo2.funcion_evaluacion_;
}

// Constructor de copia Nodo*
Nodo::Nodo(const Nodo* nodo2) {
  padre_ = nodo2->padre_;
  coordenada_fila_ = nodo2->coordenada_fila_;
  coordenada_columna_ = nodo2->coordenada_columna_;
  coste_acumulado_ = nodo2->coste_acumulado_;
  funcion_heuristica_ = nodo2->funcion_heuristica_;
  funcion_evaluacion_ = nodo2->funcion_evaluacion_;
}

// Método que permite calcular la h(n) de un nodo
unsigned Nodo::CalcularHeuristicaNodo(const unsigned coordenada_fila_final, const unsigned coordenada_columna_final) {
  return ((abs(coordenada_fila_final - coordenada_fila_) + abs(coordenada_columna_final - coordenada_columna_)) * 3);
}

// Método que permite calcular el coste acumulado de un nodo después de hacer un movimiento
unsigned Nodo::CalcularCosteAcumulado(const unsigned nuevo_movimiento) {
  return coste_acumulado_ + nuevo_movimiento;
}

// Método que permite calcular la función de evaluación de un nodo


// Sobrecarga de operador < para comparar 2 nodo*
bool Nodo::operator<(Nodo* nodo2) const { 
  return funcion_evaluacion_ < nodo2->funcion_evaluacion_; 
}

// Sobrecarga de operador < para comparar 2 nodos
bool Nodo::operator<(const Nodo& nodo2) const {
  return (funcion_evaluacion_ < nodo2.funcion_evaluacion_);
}

// Sobrecarga de operador == para comparar 2 nodos
bool Nodo::operator==(const Nodo& nodo2) const {
  return funcion_evaluacion_ == nodo2.funcion_evaluacion_;
}

// Sobrecarga de operador == para comparar 2 nodo*
bool Nodo::operator==(Nodo* nodo2) const { 
  return funcion_evaluacion_ == nodo2->funcion_evaluacion_;
}

std::ostream& operator<<(std::ostream& os, Nodo nodo) {
  os << "(" << (nodo.coordenada_fila_ + 1) << "," << (nodo.coordenada_columna_ + 1) << ")";
  return os;
}

Nodo& Nodo::operator=(const Nodo& nodo2) {
  padre_ = nodo2.padre_;
  coordenada_fila_ = nodo2.coordenada_fila_;
  coordenada_columna_ = nodo2.coordenada_columna_;
  coste_acumulado_ = nodo2.coste_acumulado_;
  funcion_heuristica_ = nodo2.funcion_heuristica_;
  funcion_evaluacion_ = nodo2.funcion_evaluacion_;
  return *this;
}
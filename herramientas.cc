#include "herramientas.h"

unsigned CalcularFuncionHeuristica(const unsigned coordenada_fila_actual,
                                   const unsigned coordenada_columna_actual,
                                   const unsigned coordenada_fila_final,
                                   const unsigned coordenada_columna_final) {
  return ((abs(coordenada_fila_final - coordenada_fila_actual) +
           abs(coordenada_columna_final - coordenada_columna_actual)) *
          3);
}

unsigned CalcularFuncionEvaluacion(const unsigned coste_acumulado,
                                   const unsigned funcion_heuristica) {
  // f(n) = g(n) + h(n)
  return coste_acumulado + funcion_heuristica;
}
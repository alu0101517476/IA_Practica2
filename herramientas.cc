#include "herramientas.h"

// Función que devuelve el iterador del set multiset<Nodo*, ComparativaNodo>::iterador. El objetivo de esta función es encontrar el nodo por su coordenada (x,y) en el set
std::multiset<Nodo*, ComparativaNodos>::iterator EncontrarElemento(const std::multiset<Nodo*, ComparativaNodos>& lista_nodos, unsigned coordenada_fila, unsigned coordenada_columna) {
  for (auto it = lista_nodos.begin(); it != lista_nodos.end(); ++it) {
    if ((*it)->GetCoordenadaFila() == coordenada_fila && (*it)->GetCoordenadaColumna() == coordenada_columna) {
      return it;
    }
  }
  // Llegados a este punto, podemos decir que el nodo no está en el set y devolvemos el iterador del final del set
  return lista_nodos.end();
}

unsigned CalcularHeuristica(const unsigned coordenada_fila_actual,
                                   const unsigned coordenada_columna_actual,
                                   const unsigned coordenada_fila_final,
                                   const unsigned coordenada_columna_final) {
  return (static_cast<unsigned>(abs(coordenada_fila_final - coordenada_fila_actual) +
           abs(coordenada_columna_final - coordenada_columna_actual)) *
          3);
}

unsigned CalcularFuncionEvaluacion(const unsigned coste_acumulado,
                                   const unsigned funcion_heuristica) {
  // f(n) = g(n) + h(n)
  return coste_acumulado + funcion_heuristica;
}
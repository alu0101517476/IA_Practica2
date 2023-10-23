#pragma once

#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <string>
#include <vector>

class Nodo;

#include "laberinto.h"
#include "nodo.h"

struct ComparativaNodos {
  bool operator()(Nodo* nodo1, Nodo* nodo2) const {
    return (nodo1->GetFuncionEvaluacion() < nodo2->GetFuncionEvaluacion());
  }
};

// Función que devuelve el iterador del set multiset<Nodo*,
// ComparativaNodo>::iterador. El objetivo de esta función es encontrar el nodo
// por su coordenada (x,y) en el set
std::multiset<Nodo*, ComparativaNodos>::iterator EncontrarElemento(
    const std::multiset<Nodo*, ComparativaNodos>& nodos_abiertos,
    unsigned coordenada_fila, unsigned coordenada_columna);

// Función que calcula la heurística de un nodo
unsigned CalcularHeuristica(const unsigned coordenada_fila_actual,
                            const unsigned coordenada_columna_actual,
                            const unsigned coordenada_fila_final,
                            const unsigned coordenada_columna_final);

// Función que calcula la función de evaluación de un nodo
unsigned CalcularFuncionEvaluacion(const unsigned coste_acumulado,
                                   const unsigned funcion_heuristica);
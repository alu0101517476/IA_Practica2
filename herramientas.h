#include <cmath>
#include <iostream>

unsigned CalcularFuncionHeuristica(const unsigned coordenada_fila_actual,
                                   const unsigned coordenada_columna_actual,
                                   const unsigned coordenada_fila_final,
                                   const unsigned coordenada_columna_final);

unsigned CalcularFuncionEvaluacion(const unsigned coste_acumulado, const unsigned funcion_heuristica);

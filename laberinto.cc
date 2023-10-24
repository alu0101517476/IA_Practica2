#include "laberinto.h"

// Constructor por defecto
Laberinto::Laberinto(std::string& nombre_fichero) {
  std::ifstream fichero_laberinto;
  fichero_laberinto.open(nombre_fichero.c_str(), std::ios::in);
  LeerFichero(fichero_laberinto);
  fichero_laberinto.close();
}

Laberinto::~Laberinto() {
  for (size_t i{0}; i < laberinto_.size(); ++i) {
    laberinto_[i].clear();
  }
}

// Setter
void Laberinto::SetCasillaInicial(const unsigned x_inicial,
                                  const unsigned y_inicio) {
  x_inicio_ = x_inicial;
  y_inicio_ = y_inicio;
}

void Laberinto::SetCasillaFinal(const unsigned x_final,
                                const unsigned y_final) {
  x_final_ = x_final;
  y_final_ = y_final;
}

// Método que se encarga de leer el fichero y guardar la información para
// construir el laberinto
void Laberinto::LeerFichero(std::ifstream& fichero_laberinto) {
  fichero_laberinto >> numero_filas_ >> numero_columnas_;
  laberinto_ = std::vector<std::vector<unsigned>>{
      numero_filas_, std::vector<unsigned>(numero_columnas_)};
  for (size_t x{0}; x < numero_filas_; ++x) {
    for (size_t y{0}; y < numero_columnas_; ++y) {
      unsigned identificacion;
      fichero_laberinto >> identificacion;
      //  Guardamos la entrada en caso de que se cumpla la condición
      if (identificacion == INICIO) {
        x_inicio_ = x;
        y_inicio_ = y;
      } else if (identificacion == FINAL) {
        x_final_ = x;
        y_final_ = y;
      }
      laberinto_[x][y] = identificacion;
    }
  }
}

void Laberinto::CambiarCasillas() {
  // Cambiar casilla inicial y casilla final si el usuario lo desea
  char confirmacion_inicio, confirmacion_final;
  std::cout
      << "La casilla de inicio actual está en las coordenadas:\n("
      << x_inicio_ << "," << y_inicio_ << ")"
      << "\n¿Desea cambiar las coordenadas de la casilla inicial? (S/N): ";
  std::cin >> confirmacion_inicio;
  if (confirmacion_inicio == 's' || confirmacion_inicio == 'S') {
    unsigned x_aux, y_aux;
    std::cout << "Introduzca la nueva coordenada x de la casilla inicial: ";
    std::cin >> x_aux;
    std::cout << "Introduzca la nueva coordenada y de la casilla inicial: ";
    std::cin >> y_aux;
    //if (EsCoordenadaValida(x_aux, y_aux)) {
      laberinto_[x_inicio_][y_inicio_] = PARED;
      x_inicio_ = x_aux;
      y_inicio_ = y_aux;
      laberinto_[x_inicio_][y_inicio_] = INICIO;
      /*
    } else {
      std::cout << "\nError, coordenadas las coordenadas introducidas son "
                   "incorrectas\nLas coordenadas serán las originales"
                << std::endl;
    }
    */
  }
  // Posibilidad de cambiar casilla final
  std::cout << "\nLa casilla final actual está en las coordenadas:\n("
            << x_final_ << "," << y_final_ << ")"
            << "\n¿Desea cambiar las coordenadas de la casilla final? (S/N): ";
  std::cin >> confirmacion_final;
  if (confirmacion_final == 's' || confirmacion_final == 'S') {
    unsigned x_aux, y_aux;
    std::cout << "Introduzca la nueva coordenada x de la casilla final: ";
    std::cin >> x_aux;
    std::cout << "Introduzca la nueva coordenada y de la casilla final: ";
    std::cin >> y_aux;
    if (EsCoordenadaValida(x_aux, y_aux)) {
      laberinto_[x_final_][y_final_] = PARED;
      x_final_ = x_aux;
      y_final_ = y_aux;
      laberinto_[x_final_][y_final_] = FINAL;
    } else {
      std::cout << "\nError, coordenadas las coordenadas introducidas son "
                   "incorrectas\nLas coordenadas serán las originales"
                << std::endl;
    }
  }
}

// Método que comprueba si el movimiento que se va a realizar es válido
bool Laberinto::EsMovimientoValido(const int fila,
                                   const int columna) const {
  return (fila < static_cast<int>(numero_filas_) && columna < static_cast<int>(numero_columnas_) && fila >= 0 && columna >= 0
          && laberinto_[fila][columna] != PARED);
}

// Método que comprueba si una coordenada introducida es válida
bool Laberinto::EsCoordenadaValida(const int fila,
                                   const int columna) const {
  return fila < int(numero_filas_) && columna < int(numero_columnas_);
}

// Método que resuelve el laberinto mediante el algoritmo A*
std::set<Nodo> Laberinto::AlgoritmoAEstrellaManhattan() {
  // Multiset que representa la lista de nodos abiertos
  std::multiset<Nodo*, ComparativaNodos> nodos_abiertos, nodos_cerrados;
  // Insertar el nodo inicial en la lista de nodos abiertos
  unsigned heuristica_inicial{ CalcularHeuristicaManhattan(x_inicio_, y_inicio_, x_final_, y_final_) };
  nodos_abiertos.insert(new Nodo(NULL, x_inicio_, y_inicio_,
                                 0, heuristica_inicial, heuristica_inicial));
  // Métemos como nodo generado el nodo inicial
  while (!nodos_abiertos.empty()) {
    // Seleccionar el nodo de menor coste f(n), e insertarlo en la lista de
    // nodos cerrados C.
    Nodo* nodo_menor_coste{*nodos_abiertos.begin()};
    nodos_abiertos.erase(nodos_abiertos.begin());
    // Lo insertamos en la lista de nodos cerrados
    nodos_cerrados.insert(nodo_menor_coste);
    // Lo insertamos en la lista de nodos generados
    nodos_generados_.insert(*nodo_menor_coste);
    // Lo insertamos en la lista de nodos inspeccionados
    nodos_inspeccionados_.insert(*nodo_menor_coste);
    // Comprobamos si las coordenadas del nodo con menor coste son las coordenadas finales
    if (nodo_menor_coste->GetCoordenadaFila() == x_final_ && nodo_menor_coste->GetCoordenadaColumna() == y_final_) {
      // Guardamos el coste final del camino
      coste_final_camino_ = nodo_menor_coste->GetCosteAcumulado();
      Nodo* nodo_camino{nodo_menor_coste};
      std::set<Nodo> camino_solucion;
      while (nodo_camino != NULL) {
        camino_solucion.insert(*nodo_camino);
        nodo_camino = nodo_camino->GetPadre();
      }
      delete nodo_camino;
      // Devolvemos el camino
      return camino_solucion;
    }
    // inspeccionamos nodos vecinos
    for (int i{0}; i < 8; ++i) {
      // Comprobamos todos los nodos posibles vecinos
      if (EsMovimientoValido(
              nodo_menor_coste->GetCoordenadaFila() + x[i],
              nodo_menor_coste->GetCoordenadaColumna() + y[i])) {
        unsigned coste_acumulado{nodo_menor_coste->GetCosteAcumulado()};
        // Comprobamos que movimiento es para sumarle el coste
        coste_acumulado += (i <= W) ? 5 : 7;
        unsigned coordenada_fila_actual{nodo_menor_coste->GetCoordenadaFila() + x[i]};
        unsigned coordenada_columna_actual{nodo_menor_coste->GetCoordenadaColumna() + y[i]};
        unsigned heuristica_actual{CalcularHeuristicaManhattan(coordenada_fila_actual, coordenada_columna_actual, x_final_, y_final_)};
        unsigned funcion_evaluacion_actual{coste_acumulado + heuristica_actual};
        Nodo* nodo_vecino = new Nodo(nodo_menor_coste, coordenada_fila_actual, coordenada_columna_actual, coste_acumulado, heuristica_actual, funcion_evaluacion_actual);
        // Comprobamos si el nodo vecino no está ni en A ni en C
        auto iterador_nodos_abiertos{EncontrarElemento(nodos_abiertos, nodo_vecino->GetCoordenadaFila(), nodo_vecino->GetCoordenadaColumna())};
        auto iterador_nodos_cerrados{EncontrarElemento(nodos_cerrados, nodo_vecino->GetCoordenadaFila(), nodo_vecino->GetCoordenadaColumna())};
        if (iterador_nodos_abiertos == nodos_abiertos.end() && iterador_nodos_cerrados == nodos_cerrados.end()) {
          // Si el nodo vecino no está en A ni en C, su nodo padre será el nodo analizado y será insertado en A.
          nodos_abiertos.insert(new Nodo(nodo_vecino));
          // Insertamos en la lista de nodos generados el nodo vecino
          nodos_generados_.insert(nodo_vecino);
        } else if (iterador_nodos_abiertos != nodos_abiertos.end()) { // Comprobamos que el nodo vecino está en A
          if (nodo_vecino->GetCosteAcumulado() < (*iterador_nodos_abiertos)->GetCosteAcumulado()) {
            // Si el nodo vecino tiene un coste menor al nodo que ya está en el set
            // borramos el nodo e insertamos el nuevo con un valor menor
            nodos_abiertos.erase(iterador_nodos_abiertos);
            nodos_abiertos.insert(new Nodo(nodo_vecino));
            // Insertamos en la lista de nodos generados el nodo vecino
            nodos_generados_.insert(nodo_vecino);
          }
        }
      }
    }
  }
  // Si salimos del while es que no hemos encontrado un camino por lo que retornamos un set de nodos vacio
  return std::set<Nodo>{};
}

// Método que resuelve el laberinto mediante el algoritmo A* con heurística Euclídea
std::set<Nodo> Laberinto::AlgoritmoAEstrellaEuclidea() {
  // Multiset que representa la lista de nodos abiertos
  std::multiset<Nodo*, ComparativaNodos> nodos_abiertos, nodos_cerrados;
  // Insertar el nodo inicial en la lista de nodos abiertos
  unsigned heuristica_inicial{ CalcularHeuristicaEuclideana(x_inicio_, y_inicio_, x_final_, y_final_) };
  nodos_abiertos.insert(new Nodo(NULL, x_inicio_, y_inicio_,
                                 0, heuristica_inicial, heuristica_inicial));
  // Métemos como nodo generado el nodo inicial
  while (!nodos_abiertos.empty()) {
    // Seleccionar el nodo de menor coste f(n), e insertarlo en la lista de
    // nodos cerrados C.
    Nodo* nodo_menor_coste{*nodos_abiertos.begin()};
    nodos_abiertos.erase(nodos_abiertos.begin());
    // Lo insertamos en la lista de nodos cerrados
    nodos_cerrados.insert(nodo_menor_coste);
    // Lo insertamos en la lista de nodos generados
    nodos_generados_.insert(*nodo_menor_coste);
    // Lo insertamos en la lista de nodos inspeccionados
    nodos_inspeccionados_.insert(*nodo_menor_coste);
    // Comprobamos si las coordenadas del nodo con menor coste son las coordenadas finales
    if (nodo_menor_coste->GetCoordenadaFila() == x_final_ && nodo_menor_coste->GetCoordenadaColumna() == y_final_) {
      // Guardamos el coste final del camino
      coste_final_camino_ = nodo_menor_coste->GetCosteAcumulado();
      Nodo* nodo_camino{nodo_menor_coste};
      std::set<Nodo> camino_solucion;
      while (nodo_camino != NULL) {
        camino_solucion.insert(*nodo_camino);
        nodo_camino = nodo_camino->GetPadre();
      }
      delete nodo_camino;
      // Devolvemos el camino
      return camino_solucion;
    }
    // inspeccionamos nodos vecinos
    for (int i{0}; i < 8; ++i) {
      // Comprobamos todos los nodos posibles vecinos
      if (EsMovimientoValido(
              nodo_menor_coste->GetCoordenadaFila() + x[i],
              nodo_menor_coste->GetCoordenadaColumna() + y[i])) {
        unsigned coste_acumulado{nodo_menor_coste->GetCosteAcumulado()};
        // Comprobamos que movimiento es para sumarle el coste
        coste_acumulado += (i <= W) ? 5 : 7;
        unsigned coordenada_fila_actual{nodo_menor_coste->GetCoordenadaFila() + x[i]};
        unsigned coordenada_columna_actual{nodo_menor_coste->GetCoordenadaColumna() + y[i]};
        unsigned heuristica_actual{CalcularHeuristicaEuclideana(coordenada_fila_actual, coordenada_columna_actual, x_final_, y_final_)};
        unsigned funcion_evaluacion_actual{coste_acumulado + heuristica_actual};
        Nodo* nodo_vecino = new Nodo(nodo_menor_coste, coordenada_fila_actual, coordenada_columna_actual, coste_acumulado, heuristica_actual, funcion_evaluacion_actual);
        // Comprobamos si el nodo vecino no está ni en A ni en C
        auto iterador_nodos_abiertos{EncontrarElemento(nodos_abiertos, nodo_vecino->GetCoordenadaFila(), nodo_vecino->GetCoordenadaColumna())};
        auto iterador_nodos_cerrados{EncontrarElemento(nodos_cerrados, nodo_vecino->GetCoordenadaFila(), nodo_vecino->GetCoordenadaColumna())};
        if (iterador_nodos_abiertos == nodos_abiertos.end() && iterador_nodos_cerrados == nodos_cerrados.end()) {
          // Si el nodo vecino no está en A ni en C, su nodo padre será el nodo analizado y será insertado en A.
          nodos_abiertos.insert(new Nodo(nodo_vecino));
          // Insertamos en la lista de nodos generados el nodo vecino
          nodos_generados_.insert(nodo_vecino);
        } else if (iterador_nodos_abiertos != nodos_abiertos.end()) { // Comprobamos que el nodo vecino está en A
          if (nodo_vecino->GetCosteAcumulado() < (*iterador_nodos_abiertos)->GetCosteAcumulado()) {
            // Si el nodo vecino tiene un coste menor al nodo que ya está en el set
            // borramos el nodo e insertamos el nuevo con un valor menor
            nodos_abiertos.erase(iterador_nodos_abiertos);
            nodos_abiertos.insert(new Nodo(nodo_vecino));
            // Insertamos en la lista de nodos generados el nodo vecino
            nodos_generados_.insert(nodo_vecino);
          }
        }
      }
    }
  }
  // Si salimos del while es que no hemos encontrado un camino por lo que retornamos un set de nodos vacio
  return std::set<Nodo>{};
}

// Hazme un método que muestre el camino resuelto por el método Laberinto::AlgoritmoAEstrella() marcando el camino con X
void Laberinto::MostrarCamino() {
  for (const auto& nodo : AlgoritmoAEstrellaManhattan()) {
    camino_.insert(nodo);
    laberinto_[nodo.GetCoordenadaFila()][nodo.GetCoordenadaColumna()] = CAMINO;
  }
  std::cout << *this;
}

// Método que muestra estadísticas del laberinto en un fichero de salida
void Laberinto::MostrarEstadisticas(const std::string& nombre_instancia) {
  std::ofstream fichero_estadisticas;
  fichero_estadisticas.open("estadisticas.txt", std::ios::out);
  fichero_estadisticas << "Instancia: " << nombre_instancia << std::endl;
  fichero_estadisticas << "Número de filas(n): " << numero_filas_ << std::endl;
  fichero_estadisticas << "Número de columnas(m): " << numero_columnas_ << std::endl; 
  fichero_estadisticas << "Casilla inicial(S): (" << (x_inicio_)<< "," << (y_inicio_ ) << ")" << std::endl;
  fichero_estadisticas << "Casilla final(E): (" << (x_final_ ) << "," << (y_final_ ) << ")" << std::endl;
  fichero_estadisticas << "--------------------------------------------------" << std::endl;
  fichero_estadisticas << "Camino Final: " << std::endl;
  MostrarCaminoFichero(camino_, fichero_estadisticas);
  fichero_estadisticas << "--------------------------------------------------" << std::endl;
  fichero_estadisticas << "Coste: " << coste_final_camino_ << std::endl;
  fichero_estadisticas << "--------------------------------------------------" << std::endl;
  fichero_estadisticas << "Lista de Nodos generados: " << std::endl;
  MostrarMultisetNodosFichero(nodos_generados_, fichero_estadisticas);
  fichero_estadisticas << "Número de nodos generados: " << nodos_generados_.size() << std::endl;
  fichero_estadisticas << "--------------------------------------------------" << std::endl;
  fichero_estadisticas << "Nodos inspeccionados: " << std::endl;
  MostrarMultisetNodosFichero(nodos_inspeccionados_, fichero_estadisticas);
  fichero_estadisticas << "Número de nodos inspeccionados: " << nodos_inspeccionados_.size() << std::endl;
  fichero_estadisticas << "--------------------------------------------------" << std::endl;
}

// Método que muestra estadísticas del laberinto en un fichero de salida cuando no ha habido camino solución
void Laberinto::MostrarEstadisticasSinCamino(const std::string& nombre_instancia) {
  std::ofstream fichero_estadisticas;
  fichero_estadisticas.open("estadisticas.txt", std::ios::out);
  fichero_estadisticas << "NO SE HA ENCONTRADO SOLUCIÓN" << std::endl;
  fichero_estadisticas << "Instancia: " << nombre_instancia << std::endl;
  fichero_estadisticas << "Número de filas(n): " << numero_filas_ << std::endl;
  fichero_estadisticas << "Número de columnas(m): " << numero_columnas_ << std::endl; 
  fichero_estadisticas << "Casilla inicial(S): (" << (x_inicio_)<< "," << (y_inicio_) << ")" << std::endl;
  fichero_estadisticas << "Casilla final(E): (" << (x_final_) << "," << (y_final_) << ")" << std::endl;
  fichero_estadisticas << "--------------------------------------------------" << std::endl;
  fichero_estadisticas << "Lista de Nodos generados: " << std::endl;
  MostrarMultisetNodosFichero(nodos_generados_, fichero_estadisticas);
  fichero_estadisticas << "Número de nodos generados: " << nodos_generados_.size() << std::endl;
  fichero_estadisticas << "--------------------------------------------------" << std::endl;
  fichero_estadisticas << "Nodos inspeccionados: " << std::endl;
  MostrarMultisetNodosFichero(nodos_inspeccionados_, fichero_estadisticas);
  fichero_estadisticas << "Número de nodos inspeccionados: " << nodos_inspeccionados_.size() << std::endl;
  fichero_estadisticas << "--------------------------------------------------" << std::endl;
}

// Sobrecarga de operador << para mostrar el laberinto por pantalla
std::ostream& operator<<(std::ostream& os, const Laberinto& laberinto) {
  std::cout << std::endl;
  for (size_t i{0}; i < laberinto.laberinto_.size(); ++i) { // Columnas
    for (size_t j{0}; j < laberinto.laberinto_[i].size(); ++j) { // Filas
      switch (laberinto.laberinto_[i][j]) {
        case INICIO:
          os << CARACTER_ENTRADA;
          break;
        case FINAL:
          os << CARACTER_SALIDA;
          break;

        case PASADIZO:
          os << CARACTER_PASADIZO;
          break;
        case PARED:
          os << CARACTER_PARED;
          break;
        case CAMINO:
          os << CARACTER_CAMINO;
          break;

        default:
          break;
      }
    }
    os << std::endl;
  }
  return os;
}
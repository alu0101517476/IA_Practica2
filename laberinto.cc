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
void Laberinto::SetCasillaInicial(const unsigned x_inicial, const unsigned y_inicio) {
  x_inicio_ = x_inicial;
  y_inicio_ = y_inicio;
}

void Laberinto::SetCasillaFinal(const unsigned x_final, const unsigned y_final) {
  x_final_ = x_final;
  y_final_ = y_final;
}

// Método que se encarga de leer el fichero y guardar la información para
// construir el laberinto
void Laberinto::LeerFichero(std::ifstream& fichero_laberinto) {
  fichero_laberinto >> numero_columnas_ >> numero_filas_;
  laberinto_ = std::vector<std::vector<unsigned>>{
      numero_columnas_, std::vector<unsigned>(numero_filas_)};
  for (size_t i{0}; i < numero_columnas_; ++i) {
    for (size_t j{0}; j < numero_filas_; ++j) {
      unsigned identificacion;
      fichero_laberinto >> identificacion;
      //  Guardamos la entrada en caso de que se cumpla la condición
      if (identificacion == INICIO) {
        x_inicio_ = i;
        y_inicio_ = j;
      } else if (identificacion == FINAL) {
        x_final_ = i;
        y_final_ = j;
      }
      laberinto_[i][j] = identificacion;
    }
  }
  char confirmacion_inicio, confirmacion_final;
  std::cout << "La casilla de inicio actual está en las coordenadas:\nx -> "
            << x_inicio_ << " | y -> " << y_inicio_ << "\n¿Desea cambiar las coordenadas de la casilla inicial? (S/N): ";
  std::cin >> confirmacion_inicio;
  if (confirmacion_inicio == 's' || confirmacion_inicio == 'S') {
    unsigned x_aux, y_aux;
    std::cout << "Introduzca la nueva coordenada x de la casilla inicial: ";
    std::cin >> x_aux;
    std::cout << "Introduzca la nueva coordenada y de la casilla inicial: ";
    std::cin >> y_aux;
    if (EsCoordenadaValida(x_aux, y_aux)) {
      laberinto_[x_inicio_][y_inicio_] = PARED;
      x_inicio_ = x_aux;
      y_inicio_ = y_aux;
      laberinto_[x_inicio_][y_inicio_] = INICIO;
    } else {
      std::cout << "\nError, coordenadas las coordenadas introducidas son incorrectas\nLas coordenadas serán las originales" << std::endl;
    }
  }
  // Posibilidad de cambiar casilla final
  std::cout << "\nLa casilla final actual está en las coordenadas:\nx -> "
            << x_final_ << " | y -> " << y_final_ << "\n¿Desea cambiar las coordenadas de la casilla final? (S/N): ";
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
      std::cout << "\nError, coordenadas las coordenadas introducidas son incorrectas\nLas coordenadas serán las originales" << std::endl;
    }
  }
}

// Método que comprueba si el movimiento que se va a realizar es válido
bool Laberinto::EsMovimientoValido(const unsigned fila, const unsigned columna) const {
  return (fila <= numero_filas_ && columna <= numero_columnas_ &&
          laberinto_[columna][fila] != PARED);
}

// Método que comprueba si una coordenada introducida es válida
bool Laberinto::EsCoordenadaValida(const unsigned fila, const unsigned columna) const {
  return fila <= numero_filas_ && columna <= numero_columnas_;
}

// Método que resuelve el laberinto mediante el algoritmo A*
void Laberinto::AlgoritmoAEstrella() {
  // Multiset que representa la lista de nodos abiertos
  std::multiset<Nodo*, ComparativaNodos> nodos_abiertos;
  // Set que representa la lista de nodos cerrados
  std::set<Nodo> nodos_cerrados;
  // Insertar el nodo inicial en la lista de nodos abiertos
  /*
  nodos_abiertos.insert(new Nodo(
      NULL, x_inicio_, y_inicio_, 0,
      CalcularFuncionHeuristica(x_inicio_, y_inicio_, x_final_, y_final_)));
  */
  while (!nodos_abiertos.empty()) {
  }
}

// Sobrecarga de operador << para mostrar el laberinto por pantalla
std::ostream& operator<<(std::ostream& os, const Laberinto& laberinto) {
  std::cout << std::endl;
  for (size_t i{0}; i < laberinto.laberinto_.size(); ++i) {
    for (size_t j{0}; j < laberinto.laberinto_[i].size(); ++j) {
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

        default:
          break;
      }
    }
    os << std::endl;
  }
  return os;
}
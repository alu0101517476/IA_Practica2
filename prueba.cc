#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> laberinto = {
        "##########",
        "#        #",
        "#  ###   #",
        "#  #   # #",
        "#  #   # #",
        "#  ###   #",
        "#        #",
        "##########"
    };

    // Código de escape ANSI para el color de fondo negro
    std::cout << "\x1b[40m";

    for (const std::string& fila : laberinto) {
        for (char c : fila) {
            if (c == '#') {
                // Paredes negras
                std::cout << "\x1b[30m" << c;
            } else {
                // Casillas
                std::cout << "\x1b[37m" << c;
            }
        }
        std::cout << "\n";
    }

    // Restablecer los colores
    std::cout << "\x1b[0m";

    return 0;
}

#include <iostream>
#include "Juego.h"

int main() {
    std::cout << "Numero de jugadores (1-4): ";
    int n;
    std::cin >> n;
    if (n < 1) n = 1;
    if (n > 4) n = 4;

    Juego juego(n);
    juego.ejecutar();

    return 0;
}
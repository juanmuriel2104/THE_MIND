#include "Tablero.h"

void Tablero::mostrarBienvenida() {
    std::cout << "\n";
    std::cout << "          THE MIND              \n";
    std::cout << "Jueguen las cartas en orden\n";
    std::cout << "ascendente SIN comunicarse.\n";
    std::cout << "================================\n\n";
}

// Muestra nivel actual, vidas y la ultima carta jugada en la mesa
void Tablero::mostrarEstado(int nivel, int vidas, int ultimaCarta) {
    mostrarSeparador();
    std::cout << " Nivel   : " << nivel << "\n";
    std::cout << " Vidas   : ";
    for (int i = 0; i < vidas; i++) std::cout << "V";
    std::cout << "\n";
    std::cout << " En mesa : ";
    if (ultimaCarta == 0)
        std::cout << "(ninguna aun)";
    else
        std::cout << "[" << ultimaCarta << "]";
    std::cout << "\n";
    mostrarSeparador();
}

// Muestra las cartas que tiene el jugador en su mano
void Tablero::mostrarManoJugador(Jugador* j) {
    std::cout << " Tus cartas: ";
    j->mostrarMano();
}

// Muestra si la carta recién jugada es valida o no
void Tablero::mostrarCartaJugada(int numero, bool valida) {
    if (valida) {
        std::cout << " >> Carta [" << numero << "] jugada correctamente.\n";
    } else {
        std::cout << " >> CARTA [" << numero << "] FUERA DE ORDEN. Pierden una vida.\n";
    }
}

void Tablero::mostrarMensaje(const std::string& msg) {
    std::cout << "\n >> " << msg << "\n";
}

void Tablero::mostrarVictoria() {
    std::cout << "\n================================\n";
    std::cout << "     GANARON. BIEN JUGADO.      \n";
    std::cout << "================================\n";
}

void Tablero::mostrarGameOver() {
    std::cout << "\n================================\n";
    std::cout << "          GAME OVER             \n";
    std::cout << "================================\n";
}

void Tablero::mostrarSeparador() {
    std::cout << "--------------------------------\n";
}

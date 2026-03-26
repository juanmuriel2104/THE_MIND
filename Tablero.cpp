#include "Tablero.h"
#include <iostream>

Tablero::Tablero() {
    ultimaJugada = 0;   // Antes de jugar cualquier carta, la "última" es 0
}

// Una carta es válida si su número supera al último jugado
bool Tablero::esJugadaValida(int n) {
    return n > ultimaJugada;
}

// Intenta jugar la carta: si es válida la agrega a la pila y devuelve true
bool Tablero::jugar(Carta c) {
    if (!esJugadaValida(c.getNumero())) return false;
    pilaDescarte.push_back(c);
    ultimaJugada = c.getNumero();
    return true;
}

// Muestra todas las cartas que ya están en la mesa
void Tablero::mostrarPila() {
    std::cout << "Mesa: ";
    if (pilaDescarte.empty()) {
        std::cout << "(vacia)";
    } else {
        for (int i = 0; i < (int)pilaDescarte.size(); i++)
            std::cout << pilaDescarte[i].toString() << " ";
    }
    std::cout << std::endl;
}

// Reinicia la pila entre niveles
void Tablero::reiniciar() {
    pilaDescarte.clear();
    ultimaJugada = 0;
}

int Tablero::getUltima() {
    return ultimaJugada;
}
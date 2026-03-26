#pragma once
#include <vector>
#include "Carta.h"

class Tablero {
private:
    std::vector<Carta> pilaDescarte;  // Cartas ya jugadas en la mesa
    int ultimaJugada;                 // Número de la última carta jugada

public:
    Tablero();

    bool esJugadaValida(int n);       // ¿n es mayor que ultimaJugada?
    bool jugar(Carta c);              // Intenta poner la carta en la pila
    void mostrarPila();               // Imprime las cartas jugadas
    void reiniciar();                 // Limpia la pila al iniciar nivel
    int  getUltima();                 // Devuelve ultimaJugada
};
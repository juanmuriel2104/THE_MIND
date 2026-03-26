#pragma once
#include <iostream>
#include <string>
#include "Jugador.h"

class Tablero {
public:
    void mostrarBienvenida();
    void mostrarEstado(int nivel, int vidas, int ultimaCarta);
    void mostrarManoJugador(Jugador* j);
    void mostrarCartaJugada(int numero, bool valida);
    void mostrarMensaje(const std::string& msg);
    void mostrarVictoria();
    void mostrarGameOver();
    void mostrarSeparador();
};
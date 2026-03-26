#pragma once
#include <string>
#include <fstream>
#include "Carta.h"

class Jugador {
public:
    std::string nombre;
    bool activo;
    Carta** mano;
    int cantCartas;
    int capacidad;

    Jugador(std::string nombreJugador);
    ~Jugador();

    void recibirCarta(Carta* c);
    Carta* jugarMenor();
    bool tieneCarta(int n);
    int cantidadCartas() const;
    void mostrarMano() const;

    void guardar(std::ofstream& archivo) const;
    static Jugador* cargar(std::ifstream& archivo);
};
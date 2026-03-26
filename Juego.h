#pragma once
#include "Tablero.h"
#include "Jugador.h"
#include "Carta.h"

class Juego {
private:
    Jugador**  jugadores;
    int        numJugadores;
    int        nivelActual;
    int        vidas;
    int        ultimaCartaMesa;
    Tablero    tablero;

    void repartirCartas();              // Asigna cartas según el nivel
    bool validarCarta(int numero);      // Verifica si es mayor que la ultima carta
    bool todosTerminaron() const;       // Se verifica que todos tienen cero cartas
    Jugador* buscarJugadorConCarta(int numero);

public:
    Juego(int numJugadores);
    ~Juego();

    void ejecutar();
};
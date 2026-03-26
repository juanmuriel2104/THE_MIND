#pragma once
#include <vector>
#include "Jugador.h"
#include "Carta.h"
#include "Tablero.h"
#include "EstadoJuego.h"

class Juego {
private:
    int          ronda;
    int          NivelActual;
    int          Vidas;
    int          EstrellasNinja;
    int          Puntuaje;
    EstadoJuego  Estado;

    Jugador**    jugadores;
    int          numJugadores;
    Tablero      tablero;

    void repartirCartas();                      // Privado: lo llama Iniciar()
    bool todosVacios() const;                   // ¿Todos los jugadores jugaron sus cartas?
    Jugador* buscarDueno(int numero) const;     // ¿Quién tiene esa carta?
    void mostrarEstadoPantalla() const;         // Imprime nivel, vidas, mesa

public:
    Juego(int numJugadores);
    ~Juego();

    void  Iniciar();                // Inicializa o reinicia el juego
    void  RepartirCartas();         // Pública — llamada al empezar cada nivel
    bool  JugarCartas();            // Bucle de un nivel completo, devuelve true si ganaron el nivel
    bool  UsaEstrella();            // Activa estrella ninja (descarta carta menor de cada jugador)
    void  ejecutar();               // Bucle principal completo — llamado desde main
};
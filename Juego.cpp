#include "Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Constructor
Juego::Juego(int n) {
    numJugadores   = n;
    nivelActual    = 1;
    vidas          = 3;           // Empieza con 3 vidas
    ultimaCartaMesa = 0;

    jugadores = new Jugador*[numJugadores];
    for (int i = 0; i < numJugadores; i++) {
        std::string nombre = "Jugador " + std::to_string(i + 1);
        jugadores[i] = new Jugador(nombre);
    }

    srand(static_cast<unsigned int>(time(nullptr)));
}

// ── Destructor ─
Juego::~Juego() {
    for (int i = 0; i < numJugadores; i++)
        delete jugadores[i];
    delete[] jugadores;
}

// ── Repartir cartas ──
void Juego::repartirCartas() {
    // Resetear manos de todos los jugadores
    for (int i = 0; i < numJugadores; i++) {
        std::string nombre = jugadores[i]->nombre;
        delete jugadores[i];
        jugadores[i] = new Jugador(nombre);
    }

    int disponibles[100];
    for (int i = 0; i < 100; i++) disponibles[i] = i + 1;
    int restantes = 100;

    // Repartir cartas a cada jugador
    int cartasPorJugador = nivelActual;
    for (int i = 0; i < numJugadores; i++) {
        for (int c = 0; c < cartasPorJugador; c++) {
            int idx = rand() % restantes;
            int numero = disponibles[idx];

            // Mover el último disponible al lugar del elegido
            disponibles[idx] = disponibles[restantes - 1];
            restantes--;

            // Dar la carta al jugador
            jugadores[i]->recibirCarta(new Carta(numero));
        }
    }

    // Reiniciar la mesa
    ultimaCartaMesa = 0;
}

// ── Validar carta ──
bool Juego::validarCarta(int numero) {
    return numero > ultimaCartaMesa;
}

// Vericia si todos terminaron
bool Juego::todosTerminaron() const {
    for (int i = 0; i < numJugadores; i++)
        if (jugadores[i]->cantidadCartas() > 0) return false;
    return true;
}

// Buscar quien tiene una carta
Jugador* Juego::buscarJugadorConCarta(int numero) {
    for (int i = 0; i < numJugadores; i++)
        if (jugadores[i]->tieneCarta(numero)) return jugadores[i];
    return nullptr;
}

// BUCLE PRINCIPAL
void Juego::ejecutar() {
    tablero.mostrarBienvenida();

    // Bucle de niveles
    while (nivelActual <= 12 && vidas > 0) {

        tablero.mostrarMensaje("Iniciando nivel " + std::to_string(nivelActual) + "...");
        repartirCartas();

        while (!todosTerminaron() && vidas > 0) {

            tablero.mostrarEstado(nivelActual, vidas, ultimaCartaMesa);

            // Mostrar mano de cada jugador
            for (int i = 0; i < numJugadores; i++)
                tablero.mostrarManoJugador(jugadores[i]);

            // Pedir al jugador que decida con que carta va a jugar
            std::cout << "\nEscribe el numero de la carta a jugar (0 = rendirse): ";
            int eleccion;
            std::cin >> eleccion;

            if (eleccion == 0) {
                tablero.mostrarMensaje("Juego abandonado.");
                return;
            }

            // Verificar que alguien tiene la carta
            Jugador* dueno = buscarJugadorConCarta(eleccion);
            if (dueno == nullptr) {
                tablero.mostrarMensaje("Ningún jugador tiene esa carta. Intenta de nuevo.");
                continue;
            }

            // Validar orden ascendente
            bool esValida = validarCarta(eleccion);
            tablero.mostrarCartaJugada(eleccion, esValida);

            if (esValida) {
                // Jugar la carta menor del jugador dueño (saca la más baja de su mano)
                // Si el jugador tiene solo esa carta, jugarMenor() la retira correctamente
                dueno->jugarMenor();
                ultimaCartaMesa = eleccion;
            } else {
                // Carta fuera de orden, entonces se pierde una vida
                vidas--;
                dueno->jugarMenor();
                ultimaCartaMesa = eleccion;

                if (vidas <= 0) break;
            }
        }

        // Fin de nivel
        if (vidas <= 0) break;

        tablero.mostrarMensaje("¡Nivel " + std::to_string(nivelActual) + " superado!");
        nivelActual++;

        // Pausa entre niveles: el jugador teclea enter para continuar
        std::cout << "\nPresiona Enter para el siguiente nivel...";
        std::cin.ignore();
        std::cin.get();
    }

    // Resultado final
    if (vidas > 0 && nivelActual > 12)
        tablero.mostrarVictoria();
    else
        tablero.mostrarGameOver();
}
#include "Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// ── Constructor ────────────────────────────────────────────────────────────
Juego::Juego(int n) {
    numJugadores  = n;
    ronda         = 0;
    NivelActual   = 1;
    Vidas         = 3;
    EstrellasNinja = 1;
    Puntuaje      = 0;
    Estado        = ESPERANDO;

    jugadores = new Jugador*[numJugadores];
    for (int i = 0; i < numJugadores; i++) {
        std::string nombre = "Jugador " + std::to_string(i + 1);
        jugadores[i] = new Jugador(nombre);
    }

    srand(static_cast<unsigned int>(time(nullptr)));
}

// ── Destructor ─────────────────────────────────────────────────────────────
Juego::~Juego() {
    for (int i = 0; i < numJugadores; i++)
        delete jugadores[i];
    delete[] jugadores;
}

// ── Iniciar ────────────────────────────────────────────────────────────────
// Prepara el juego para empezar o reiniciar desde el nivel 1
void Juego::Iniciar() {
    NivelActual    = 1;
    Vidas          = 3;
    EstrellasNinja = 1;
    Puntuaje       = 0;
    ronda          = 0;
    Estado         = EN_JUEGO;
    tablero.reiniciar();
    RepartirCartas();
}

// ── RepartirCartas (privada) ───────────────────────────────────────────────
void Juego::repartirCartas() {
    // Resetear mano de cada jugador recreándolo
    for (int i = 0; i < numJugadores; i++) {
        std::string nombre = jugadores[i]->nombre;
        delete jugadores[i];
        jugadores[i] = new Jugador(nombre);
    }

    // Pool de 100 cartas sin repetir
    int disponibles[100];
    for (int i = 0; i < 100; i++) disponibles[i] = i + 1;
    int restantes = 100;

    // Cada jugador recibe (NivelActual) cartas
    for (int i = 0; i < numJugadores; i++) {
        for (int c = 0; c < NivelActual; c++) {
            int idx    = rand() % restantes;
            int numero = disponibles[idx];
            disponibles[idx] = disponibles[restantes - 1];
            restantes--;
            jugadores[i]->recibirCarta(new Carta(numero));
        }
    }

    tablero.reiniciar();
}

// ── RepartirCartas (pública — del UML) ────────────────────────────────────
void Juego::RepartirCartas() {
    repartirCartas();
}

// ── Helpers ────────────────────────────────────────────────────────────────
bool Juego::todosVacios() const {
    for (int i = 0; i < numJugadores; i++)
        if (jugadores[i]->cantidadCartas() > 0) return false;
    return true;
}

Jugador* Juego::buscarDueno(int numero) const {
    for (int i = 0; i < numJugadores; i++)
        if (jugadores[i]->tieneCarta(numero)) return jugadores[i];
    return nullptr;
}

void Juego::mostrarEstadoPantalla() const {
    std::cout << "\n--------------------------------\n";
    std::cout << " Nivel: " << NivelActual
              << "  |  Vidas: " << Vidas
              << "  |  Estrellas: " << EstrellasNinja
              << "  |  Puntos: " << Puntuaje << "\n";
    tablero.mostrarPila();
    std::cout << "--------------------------------\n";
    for (int i = 0; i < numJugadores; i++) {
        jugadores[i]->mostrarMano();
    }
}

// ── UsaEstrella ────────────────────────────────────────────────────────────
// Descarta la carta más baja de cada jugador cuando se usa una estrella ninja
bool Juego::UsaEstrella() {
    if (EstrellasNinja <= 0) {
        std::cout << " >> No tienes estrellas ninja disponibles.\n";
        return false;
    }
    EstrellasNinja--;
    std::cout << " >> Estrella ninja activada. Descartando carta menor de cada jugador...\n";
    for (int i = 0; i < numJugadores; i++) {
        Carta* descartada = jugadores[i]->jugarMenor();
        if (descartada != nullptr) {
            std::cout << "    " << jugadores[i]->nombre
                      << " descarta " << descartada->toString() << "\n";
            // Actualizar la mesa si la carta descartada es mayor que la última
            if (descartada->getNumero() > tablero.getUltima())
                tablero.jugar(*descartada);
            delete descartada;
        }
    }
    return true;
}

// ── JugarCartas ────────────────────────────────────────────────────────────
// Ejecuta el bucle de un nivel. Devuelve true si el nivel fue superado.
bool Juego::JugarCartas() {
    while (!todosVacios() && Vidas > 0) {
        mostrarEstadoPantalla();

        std::cout << "\nEscribe el numero de carta a jugar,\n";
        std::cout << "'e' para usar estrella ninja, o 0 para rendirse: ";

        std::string entrada;
        std::cin >> entrada;

        // Rendirse
        if (entrada == "0") {
            Estado = PERDIO;
            return false;
        }

        // Usar estrella ninja
        if (entrada == "e" || entrada == "E") {
            UsaEstrella();
            continue;
        }

        // Convertir entrada a número
        int eleccion = 0;
        bool esNumero = true;
        for (char ch : entrada) {
            if (ch < '0' || ch > '9') { esNumero = false; break; }
        }
        if (esNumero) eleccion = std::stoi(entrada);

        if (!esNumero || eleccion <= 0 || eleccion > 100) {
            std::cout << " >> Entrada inválida. Escribe un número del 1 al 100.\n";
            continue;
        }

        // Verificar que algún jugador tenga esa carta
        Jugador* dueno = buscarDueno(eleccion);
        if (dueno == nullptr) {
            std::cout << " >> Ningún jugador tiene la carta " << eleccion << ".\n";
            continue;
        }

        // Intentar jugarla en el tablero
        Carta* cartaJugada = dueno->jugarMenor();   // Saca la carta del jugador

        if (tablero.jugar(*cartaJugada)) {
            // Carta válida
            std::cout << " >> [" << eleccion << "] jugada correctamente.\n";
            Puntuaje += eleccion;   // Más puntos por cartas altas
            delete cartaJugada;
        } else {
            // Carta inválida — pierden una vida
            std::cout << " >> CARTA FUERA DE ORDEN. Pierden una vida.\n";
            Vidas--;
            // Igual se descarta para no bloquear
            tablero.jugar(*cartaJugada);
            delete cartaJugada;

            if (Vidas <= 0) {
                Estado = PERDIO;
                return false;
            }
        }
    }

    // Si llegaron aquí con vidas, superaron el nivel
    Estado = SUBIO_NIVEL;
    return true;
}

// ── ejecutar ───────────────────────────────────────────────────────────────
// Bucle completo del juego — llamado desde main()
void Juego::ejecutar() {
    std::cout << "\n================================\n";
    std::cout << "          THE MIND              \n";
    std::cout << "================================\n";
    std::cout << "Objetivo: jugar todas las cartas\n";
    std::cout << "en orden ascendente sin hablar.\n";
    std::cout << "================================\n\n";

    Iniciar();

    // Bucle de niveles (The Mind tiene 12 niveles)
    while (NivelActual <= 12 && Vidas > 0) {
        std::cout << "\n*** NIVEL " << NivelActual << " ***\n";
        std::cout << "Cada jugador recibe " << NivelActual << " carta(s).\n";
        std::cout << "Presiona Enter para continuar...";
        std::cin.ignore();
        std::cin.get();

        RepartirCartas();
        bool superado = JugarCartas();

        if (!superado) break;

        std::cout << "\n >> Nivel " << NivelActual << " superado! Puntos: " << Puntuaje << "\n";
        NivelActual++;
        ronda++;

        if (NivelActual <= 12) {
            std::cout << "Presiona Enter para el nivel " << NivelActual << "...";
            std::cin.ignore();
            std::cin.get();
        }
    }

    // Resultado final
    if (Vidas > 0 && NivelActual > 12) {
        Estado = GANO;
        std::cout << "\n================================\n";
        std::cout << "   GANARON. Puntos: " << Puntuaje << "\n";
        std::cout << "================================\n";
    } else {
        Estado = PERDIO;
        std::cout << "\n================================\n";
        std::cout << "   GAME OVER. Puntos: " << Puntuaje << "\n";
        std::cout << "================================\n";
    }
}
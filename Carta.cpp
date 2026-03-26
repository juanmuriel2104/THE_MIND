// logica detras de carta
#include "Carta.h"

Carta::Carta(int num) : numero(num), jugada(false) {}

int  Carta::getNumero() const { return numero; }
bool Carta::isJugada()  const { return jugada; }
void Carta::marcarJugada()    { jugada = true; }

bool Carta::operator<(const Carta& otra) const {
    return numero < otra.numero;
}

std::string Carta::toString() const {
    return "[" + std::to_string(numero) + "]";
}
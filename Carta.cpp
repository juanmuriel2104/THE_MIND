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
void Carta::guardar(std::ofstream& archivo) const {
    archivo.write(reinterpret_cast<const char*>(&numero), sizeof(int));
    archivo.write(reinterpret_cast<const char*>(&jugada), sizeof(bool));
}

Carta* Carta::cargar(std::ifstream& archivo) {
    int num;
    bool jug;
    archivo.read(reinterpret_cast<char*>(&num), sizeof(int));
    archivo.read(reinterpret_cast<char*>(&jug), sizeof(bool));
    Carta* c = new Carta(num);
    if (jug) c->marcarJugada();
    return c;
}

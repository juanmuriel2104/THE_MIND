#include "Jugador.h"
#include <iostream>

Jugador::Jugador(std::string nombreJugador) {
    nombre = nombreJugador;
    activo = true;
    capacidad = 10;
    cantCartas = 0;
    mano = new Carta*[capacidad];
}

Jugador::~Jugador() {
    for (int i = 0; i < cantCartas; i++)
        delete mano[i];
    delete[] mano;
}

void Jugador::recibirCarta(Carta* c) {
    mano[cantCartas] = c;
    cantCartas++;
}

Carta* Jugador::jugarMenor() {
    if (cantCartas == 0) return nullptr;
    Carta* menor = mano[0];
    for (int i = 0; i < cantCartas - 1; i++)
        mano[i] = mano[i+1];
    cantCartas--;
    return menor;
}

bool Jugador::tieneCarta(int n) {
    for (int i = 0; i < cantCartas; i++)
        if (mano[i]->getNumero() == n) return true;
    return false;
}

int Jugador::cantidadCartas() const {
    return cantCartas;
}

void Jugador::mostrarMano() const {
    std::cout << nombre << ": ";
    for (int i = 0; i < cantCartas; i++)
        std::cout << mano[i]->getNumero() << " ";
    std::cout << std::endl;
}

void Jugador::guardar(std::ofstream& archivo) const {
    int len = nombre.size();
    archivo.write(reinterpret_cast<const char*>(&len), sizeof(int));
    archivo.write(nombre.c_str(), len);
    archivo.write(reinterpret_cast<const char*>(&activo), sizeof(bool));
    archivo.write(reinterpret_cast<const char*>(&cantCartas), sizeof(int));
    for (int i = 0; i < cantCartas; i++)
        mano[i]->guardar(archivo);
}

Jugador* Jugador::cargar(std::ifstream& archivo) {
    int len;
    archivo.read(reinterpret_cast<char*>(&len), sizeof(int));
    std::string nombre(len, ' ');
    archivo.read(&nombre[0], len);
    bool activo;
    archivo.read(reinterpret_cast<char*>(&activo), sizeof(bool));
    Jugador* j = new Jugador(nombre);
    j->activo = activo;
    int cant;
    archivo.read(reinterpret_cast<char*>(&cant), sizeof(int));
    for (int i = 0; i < cant; i++)
        j->recibirCarta(Carta::cargar(archivo));
    return j;
}
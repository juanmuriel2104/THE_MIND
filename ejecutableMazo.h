// logica Mazo
#include "Mazo.h"
#include <algorithm>
#include <random>
#include <fstream>
#include <stdexcept>

Mazo::Mazo() {
    for (int i = 1; i <= 100; i++)
        cartas.emplace_back(i);
}

void Mazo::barajar() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(cartas.begin(), cartas.end(), gen);
}

Carta Mazo::sacar() {
    if (estaVacio())
        throw std::runtime_error("Mazo vacio");
    Carta c = cartas.back();
    cartas.pop_back();
    return c;
}

bool Mazo::estaVacio() const { return cartas.empty(); }
int  Mazo::cantidad()  const { return cartas.size(); }

void Mazo::guardar(const std::string& archivo) {
    std::ofstream archivo_salida(archivo);
    for (const auto& c : cartas)
        archivo_salida << c.getNumero() << "\n";
}

void Mazo::cargar(const std::string& archivo) {
    std::ifstream archivo_entrada(archivo);
    cartas.clear();
    int numero;
    while (archivo_entrada >> numero)
        cartas.emplace_back(numero);
}
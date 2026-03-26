// Mazo.h
#pragma once
#include "Carta.h"
#include <vector>
#include <string>

class Mazo {
private:
    std::vector<Carta> cartas;

public:
    Mazo();

    void  barajar();
    Carta sacar();
    bool  estaVacio() const;
    int   cantidad()  const;
    void  guardar(const std::string& archivo);
    void  cargar(const std::string& archivo);
};
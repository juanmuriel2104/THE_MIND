// Carta.h
#pragma once
#include <string>

class Carta {
private:
    int  numero;
    bool jugada;

public:
    Carta(int num);

    int         getNumero() const;
    bool        isJugada()  const;
    void        marcarJugada();
    bool        operator<(const Carta& otra) const;
    std::string toString()  const;
};

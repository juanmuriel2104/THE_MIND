// Carta.h
#pragma once
#include <string>
#include <fstream>

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
    void           guardar(std::ofstream& archivo) const;
    static Carta*  cargar(std::ifstream& archivo);
};

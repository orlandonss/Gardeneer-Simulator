#ifndef TPPOO2_MARACUJA_H
#define TPPOO2_MARACUJA_H

#include "Planta.h"
#include <string>

class Jardim;

class Maracuja : public Planta {
public:
    Maracuja(Jardim* jardim, int l, int c);

    char getTipo() const override;
    std::string getInfoPlanta() const override;
    void atualizar(Solo &solo) override;

    // Getters extra se precisares para debug
    int getIdade() const { return idade; }

private:
    Jardim* jardim;
    int linha, coluna;
    int idade;
    int instantesAguaBaixa;
    int instantesAguaAlta;
    int nutrientesAbsorvidosTotal;
};

#endif
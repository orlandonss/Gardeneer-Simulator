#ifndef TPPOO2_ERVADANINHA_H
#define TPPOO2_ERVADANINHA_H

#include "../Planta/Planta.h"
#include "../Solo/Solo.h"

class Jardim;

class ErvaDaninha : public Planta {
public:
    ErvaDaninha(Jardim* j, int l, int c);

    char getTipo() const override;
    std::string getInfoPlanta() const override;

    int getIdade() const { return idade; }
    int instantesUltMult() const { return instantesDesdeUltimaMult; }

    void atualizar(Solo &solo) override;

private:
    Jardim* jardimRef;
    int pLinha;
    int pColuna;

    int idade;
    int instantesDesdeUltimaMult;
};

#endif
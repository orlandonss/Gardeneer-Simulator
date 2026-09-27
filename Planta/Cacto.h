#ifndef TPPOO2_CACTO_H
#define TPPOO2_CACTO_H

#include "Planta.h"


class Cacto : public Planta {
public:
    Cacto();

    char getTipo() const override;
    std::string getInfoPlanta() const override;

    void atualizar(Solo &solo) override;

    int getInstantesAguaAlta() const { return instantesAguaAlta; }
    int getInstantesNutrientesBaixos() const { return instantesNutrientesBaixos; }

private:
    int instantesAguaAlta;
    int instantesNutrientesBaixos;
};

#endif
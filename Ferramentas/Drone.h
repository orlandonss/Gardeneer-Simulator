#ifndef TPPOO2_DRONE_H
#define TPPOO2_DRONE_H

#include "../Ferramentas/Ferramentas.h"

class Jardim;

class Drone : public Ferramenta {
public:
    Drone(Jardim* jardimRef);

    char get_tipo_Ferramenta() const override;
    std::string getInfoFerramenta() const override;

    bool funcionalidade_ferramenta(Solo* solo) override;

    bool jaAcabou() const override;

private:
    Jardim* jardim;
    bool usado;
};

#endif
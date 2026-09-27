#ifndef POO_TRABALHO_PLANTAR_H
#define POO_TRABALHO_PLANTAR_H

#include "../Comandos.h"

class Plantar : public Comandos {
public:
    Plantar(const std::string &frase, Simulador &simulacao);
    void executa() override;
};


#endif //POO_TRABALHO_PLANTAR_H
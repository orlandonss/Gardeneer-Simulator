#ifndef POO_TRABALHO_AVANCAR_H
#define POO_TRABALHO_AVANCAR_H
#include "../Comandos.h"

class Avanca : public Comandos {

public:
    Avanca(const std::string &frase, Simulador &simulacao);
    void executa() override;
};

#endif //POO_TRABALHO_AVANCAR_H
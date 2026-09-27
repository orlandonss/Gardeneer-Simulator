//
// Created by orlando on 10/26/25.
//

#ifndef POO_TRABALHO_DIREITA_H
#define POO_TRABALHO_DIREITA_H

#include "../Comandos.h"

class Direita : public Comandos {
public:
    Direita(const std::string &frase, Simulador &simulacao);

    void executa() override;
};

#endif //POO_TRABALHO_DIREITA_H

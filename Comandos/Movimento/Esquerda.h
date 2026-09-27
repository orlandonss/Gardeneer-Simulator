//
// Created by orlando on 10/26/25.
//

#ifndef POO_TRABALHO_ESQUERDA_H
#define POO_TRABALHO_ESQUERDA_H

#include "../Comandos.h"

class Esquerda : public Comandos {
public:
    Esquerda(const std::string &frase, Simulador &simulacao);

    void executa() override;
};

#endif //POO_TRABALHO_ESQUERDA_H

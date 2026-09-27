//
// Created by orlando on 10/26/25.
//

#ifndef POO_TRABALHO_PEGAR_H
#define POO_TRABALHO_PEGAR_H

#include "../Comandos.h"

class Pega : public Comandos {
public:
    Pega(const std::string &frase, Simulador &simulacao);

    void executa() override;
};


#endif //POO_TRABALHO_PEGAR_H

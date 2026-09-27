//
// Created by orlando on 10/26/25.
//


#ifndef POO_TRABALHO_AJUDA_H
#define POO_TRABALHO_AJUDA_H

#include "../Comandos.h"

class Ajuda : public Comandos {
public:
    Ajuda(const std::string &frase, Simulador &simulacao);

    void executa() override;
};

#endif //POO_TRABALHO_AJUDA_H

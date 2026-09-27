//
// Created by orlando on 11/1/25.
//

#ifndef TPPOO2_SAIR_H
#define TPPOO2_SAIR_H
#include "../Comandos.h"

class Sair:public Comandos{
public:
    Sair(const std::string &frase, Simulador &simulacao);
    void executa() override;
};

#endif //TPPOO2_SAIR_H
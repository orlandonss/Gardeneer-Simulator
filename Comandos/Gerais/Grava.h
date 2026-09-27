//
// Created by Samuel Olavo on 01/11/2025.
//

#ifndef TPPOO2_GRAVA_H
#define TPPOO2_GRAVA_H
#include "../Comandos.h"

class Grava:public Comandos{
public:
    Grava(const std::string &frase, Simulador &simulacao);
    void executa() override;
};


#endif //TPPOO2_GRAVA_H
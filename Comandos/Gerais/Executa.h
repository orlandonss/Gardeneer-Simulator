//
// Created by Samuel Olavo on 01/11/2025.
//

#ifndef TPPOO2_EXECUTA_H
#define TPPOO2_EXECUTA_H
#include "../Comandos.h"

class Executa : public Comandos {
public:
    Executa(const std::string &frase, Simulador &simulacao);

    void executa() override;
};

#endif //TPPOO2_EXECUTA_H
//
// Created by Samuel Olavo on 01/11/2025.
//

#ifndef TPPOO2_RECUPERA_H
#define TPPOO2_RECUPERA_H

#include "../Comandos.h"

class Recupera : public Comandos {
public:
    Recupera(const std::string &frase, Simulador &simulacao);

    void executa() override;
};


#endif //TPPOO2_RECUPERA_H

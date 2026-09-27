//
// Created by Samuel Olavo on 01/11/2025.
//

#ifndef TPPOO2_APAGA_H
#define TPPOO2_APAGA_H
#include "../Comandos.h"

class Apaga : public Comandos {
public:
    Apaga(const std::string &frase, Simulador &simulacao);

    void executa() override;
};


#endif //TPPOO2_APAGA_H

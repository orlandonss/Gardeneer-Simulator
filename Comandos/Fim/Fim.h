//
// Created by orlando on 11/1/25.
//



#ifndef TPPOO2_FIM_H
#define TPPOO2_FIM_H

#include "../Comandos.h"

class Fim : public Comandos {
public:
    Fim(const std::string &frase, Simulador &simulacao);
    void executa() override;

};

#endif // TPPOO2_FIM_H



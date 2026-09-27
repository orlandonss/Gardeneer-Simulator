//
// Created by orlando on 10/31/25.
//

#ifndef TPPOO2_CRIARMAPA_H
#define TPPOO2_CRIARMAPA_H

#include "../Comandos.h"

class CriarMapa:public Comandos{
public:
    CriarMapa(const std::string &frase, Simulador &simulacao);
    void executa() override;
};

#endif //TPPOO2_CRIARMAPA_H
//
// Created by orlando on 10/26/25.
//

#ifndef POO_TRABALHO_CIMA_H
#define POO_TRABALHO_CIMA_H

#include "../Comandos.h"

class Cima : public Comandos {
public:
    Cima(const std::string &frase, Simulador &simulacao);
    void executa() override;
};


#endif //POO_TRABALHO_CIMA_H

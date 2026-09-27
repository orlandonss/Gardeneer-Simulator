//
// Created by orlando on 10/26/25.
//

#ifndef POO_TRABALHO_BAIXO_H
#define POO_TRABALHO_BAIXO_H

#include "../Comandos.h"

class Baixo : public Comandos {
public:
    Baixo(const std::string &frase, Simulador &simulacao);
    void executa() override;
};


#endif //POO_TRABALHO_BAIXO_H
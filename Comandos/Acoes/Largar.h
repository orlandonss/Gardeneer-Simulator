//
// Created by orlando on 10/26/25.
//

#ifndef POO_TRABALHO_LARGAR_H
#define POO_TRABALHO_LARGAR_H

#include "../Comandos.h"

class Largar : public Comandos {
public:
    Largar(const std::string &frase, Simulador &simulacao);

    void executa() override;
};

#endif //POO_TRABALHO_LARGAR_H

//
// Created by orlando on 10/26/25.
//

#ifndef POO_TRABALHO_LSOLO_H
#define POO_TRABALHO_LSOLO_H

#include "../Comandos.h"

class Listar_SOLO : public Comandos {
public:
    Listar_SOLO(const std::string &frase, Simulador &simulacao);

    void executa() override;
};

#endif //POO_TRABALHO_LSOLO_H

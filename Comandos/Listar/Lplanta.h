//
// Created by orlando on 10/26/25.
//

#ifndef POO_TRABALHO_LPLANTA_H
#define POO_TRABALHO_LPLANTA_H

#include "../Comandos.h"


class Listar_planta : public Comandos {
public:
    Listar_planta(const std::string &frase, Simulador &simulacao);

    void executa() override;
};


#endif //POO_TRABALHO_LPLANTA_H

//
// Created by orlando on 10/26/25.
//

#ifndef POO_TRABALHO_LPLANTAS_H
#define POO_TRABALHO_LPLANTAS_H

#include "../Comandos.h"

class Listar_plantas : public Comandos {

public:
    Listar_plantas(const std::string &frase, Simulador &simulacao);
    void executa() override;

};
#endif //POO_TRABALHO_LPLANTAS_H
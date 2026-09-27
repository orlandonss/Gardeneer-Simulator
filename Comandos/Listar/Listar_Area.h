//
// Created by orlando on 10/29/25.
//

#ifndef TPPOO2_LISTAR_AREA_H
#define TPPOO2_LISTAR_AREA_H


#include "../Comandos.h"
#include "../../Simulador/Simulador.h"
#include <string>

class Listar_Area : public Comandos {
public:
    Listar_Area(const std::string &frase, Simulador &simulacao);

    void executa() override;
};


#endif //TPPOO2_LISTAR_AREA_H

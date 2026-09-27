//
// Created by orlando on 10/31/25.
//

#ifndef TPPOO2_INTERFACEUTILIZADOR_H
#define TPPOO2_INTERFACEUTILIZADOR_H


#include "../Simulador/Simulador.h"

class InterfaceUtilizador {
    Simulador &simulacao;
public:
    explicit InterfaceUtilizador(Simulador &simulacao);
    void executa() const;
};
#endif //TPPOO2_INTERFACEUTILIZADOR_H
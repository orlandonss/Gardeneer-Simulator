//
// Created by orlando on 10/26/25.
//

#ifndef POO_TRABALHO_LISTA_FERRAMENTAS_H
#define POO_TRABALHO_LISTA_FERRAMENTAS_H

#include "../Comandos.h"

class Listar_ferramentas : public Comandos {

public:
        Listar_ferramentas(const std::string &frase, Simulador &simulacao);
        void executa() override;
};



#endif //POO_TRABALHO_LISTA_FERRAMENTAS_H
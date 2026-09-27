#ifndef TPPOO2_COMPRA_H
#define TPPOO2_COMPRA_H

#include "../Comandos.h"

class Compra : public Comandos {
public:
    Compra(const std::string &frase, Simulador &simulacao);
    void executa() override;
};


#endif //TPPOO2_COMPRA_H

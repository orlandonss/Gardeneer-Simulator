#ifndef POO_TRABALHO_COLHER_H
#define POO_TRABALHO_COLHER_H

#include "../Comandos.h"

class Colhe : public Comandos {
public:
    Colhe(const std::string &frase, Simulador &simulacao);

    void executa() override;
};


#endif //POO_TRABALHO_COLHER_H

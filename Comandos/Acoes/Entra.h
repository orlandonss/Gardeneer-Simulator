#ifndef TPPOO2_ENTRAR_H
#define TPPOO2_ENTRAR_H
#include "../Comandos.h"


class Entra : public Comandos {
public:
    Entra(const std::string &frase, Simulador &simulacao);

    void executa() override;
};


#endif //TPPOO2_ENTRAR_H

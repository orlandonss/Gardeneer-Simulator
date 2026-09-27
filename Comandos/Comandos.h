#ifndef TPPOO2_COMANDOS_H
#define TPPOO2_COMANDOS_H

#include <string>

#include <iostream>
#include "../Simulador/Simulador.h"

class Comandos {
public:
    Comandos(const std::string &fr, Simulador &sim);
    bool validaComando(int esperado, const std::string &uso) const;
    int contaArgumentos() const;

    bool validaComando(int minimo, int maximo, const std::string &uso) const;

    virtual ~Comandos() = default;
    virtual void executa() = 0;
    Simulador &obtemSimulacao() {return  simulacao;}
    static Comandos *criaComando(std::istream &in, Simulador &sim);
    std::string getFrase() const {return frase;}

private:
    std::string frase;
    Simulador &simulacao;

};

#endif

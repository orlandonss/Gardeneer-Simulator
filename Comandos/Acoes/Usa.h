//
// Created by Samuel Olavo on 30/12/2025.
//
#ifndef TPPOO2_USA_H
#define TPPOO2_USA_H

#include "../Comandos.h"
// Nota: Ajusta o include consoante a tua estrutura de pastas.
// Se der erro, tenta: #include "../Comandos.h"

class Usa : public Comandos {
public:
    Usa(const std::string &frase, Simulador &simulacao);
    void executa() override;
};

#endif // TPPOO2_USA_H
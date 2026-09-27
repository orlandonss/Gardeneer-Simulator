#include "Grava.h"
#include <iostream>
#include <sstream>

Grava::Grava(const std::string &frase, Simulador &simulacao)
    : Comandos(frase, simulacao) {}

void Grava::executa() {
    std::istringstream iss(getFrase());
    std::string cmd, nome;
    iss >> cmd >> nome;

    if (nome.empty()) {
        std::cout << "Erro: indica o nome (grava <nome>)\n";
        return;
    }
    try {
        obtemSimulacao().gravarEstado(nome);
    } catch (const std::exception &e) {
        std::cout << e.what();
    }
}
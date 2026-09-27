#include "Apaga.h"
#include <iostream>
#include <sstream>

Apaga::Apaga(const std::string &frase, Simulador &simulacao)
    : Comandos(frase, simulacao) {}

void Apaga::executa() {
    std::istringstream iss(getFrase());
    std::string cmd, nome;
    iss >> cmd >> nome;

    if (nome.empty()) {
        std::cout << "Erro: indica o nome (apaga <nome>)\n";
        return;
    }
    try {
        obtemSimulacao().apagarEstado(nome);
    } catch (const std::exception &e) {
        std::cout << e.what();
    }
}
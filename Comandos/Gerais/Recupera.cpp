#include "Recupera.h"
#include <iostream>
#include <sstream>

Recupera::Recupera(const std::string &frase, Simulador &simulacao)
    : Comandos(frase, simulacao) {}

void Recupera::executa() {
    std::istringstream iss(getFrase());
    std::string cmd, nome;
    iss >> cmd >> nome;

    if (nome.empty()) {
        std::cout << "Erro: indica o nome (recupera <nome>)\n";
        return;
    }
    try {
        obtemSimulacao().recuperarEstado(nome);
    } catch (const std::exception &e) {
        std::cout << e.what();
    }
}
//
// Created by Samuel Olavo on 30/12/2025.
//

#include "Usa.h"
#include <iostream>
#include <sstream>

Usa::Usa(const std::string &frase, Simulador &simulacao)
    : Comandos(frase, simulacao) {}

void Usa::executa() {
    std::istringstream iss(getFrase());
    std::string cmd;
    int id;

    iss >> cmd >> id;

    if (iss.fail()) {
        std::cout << "Sintaxe incorreta. Escreve: usa <id>\n";
        return;
    }

    try {
        obtemSimulacao().usarFerramenta(id);
    } catch (const std::exception &e) {
        std::cerr << e.what();
    }
}

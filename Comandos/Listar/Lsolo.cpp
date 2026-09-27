//
// Created by orlando on 10/26/25.
//

#include "Lsolo.h"
#include <iostream>
#include <sstream>

Listar_SOLO::Listar_SOLO(const std::string &frase, Simulador &simulacao)
    : Comandos(frase, simulacao) {
}

void Listar_SOLO::executa() {
    try {
        if (!validaComando(2, 3, "lsolo <l> <c> [raio]"))
            return;

        std::istringstream iss(getFrase());
        std::string cmd;
        char lChar, cChar;
        int raio = 0;

        iss >> cmd >> lChar >> cChar;

        if (iss >> raio) {
            if (raio < 0) {
                std::cout << "O raio nao pode ser negativo.\n";
                return;
            }
        }

        std::string extra;
        if (iss >> extra) {
            std::cout << "Sintaxe incorreta. Use: lsolo <l> <c> [raio]\n";
            return;
        }

        obtemSimulacao().listarSolo(lChar, cChar, raio);

    } catch (const std::exception &e) {
        std::cerr << "Erro ao executar lsolo: " << e.what() << '\n';
    }
}


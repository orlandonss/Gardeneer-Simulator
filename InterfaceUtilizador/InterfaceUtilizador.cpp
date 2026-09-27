//
// Created by orlando on 10/31/25.
//

#include "InterfaceUtilizador.h"
#include "../Comandos/Comandos.h"
#include <iostream>

using namespace std;

InterfaceUtilizador::InterfaceUtilizador(Simulador &simulacao)
    : simulacao(simulacao) {}

void InterfaceUtilizador::executa() const {
    cout <<"Para ajuda digite o comando: <ajuda>\n";
    while (simulacao.estaAtivo()) {
        std::cout << "> ";
        Comandos* comando = Comandos::criaComando(cin, simulacao);

        if (!comando) {
            std::cout << "Comando inválido.\n";
            continue;
        }
        comando->executa();
        delete comando;
    }
}

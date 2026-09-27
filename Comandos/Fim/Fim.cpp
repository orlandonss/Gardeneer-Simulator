//
// Created by orlando on 11/1/25.
//

#include "Fim.h"
#include <iostream>

Fim::Fim(const std::string &frase,  Simulador &simulacao)
    : Comandos(frase, simulacao) {}

void Fim::executa() {
    std::cout << "A terminar o simulador...\n";
    Simulador &sim = obtemSimulacao();
    sim.termina_jogo();
}

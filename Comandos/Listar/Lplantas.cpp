#include "Lplantas.h"

#include <iostream>
#include <sstream>

using std::cout;

Listar_plantas::Listar_plantas(const std::string &frase, Simulador &simulacao) : Comandos(frase, simulacao) {
}

void Listar_plantas::executa() {
    try {
        std::istringstream iss(getFrase());
        std::string cmd;
        std::string extra;

        iss >> cmd;
        Simulador &sim = obtemSimulacao();
        sim.listarPlantas();
    } catch (const std::exception &e) {
        std::cerr << e.what();
    }
}

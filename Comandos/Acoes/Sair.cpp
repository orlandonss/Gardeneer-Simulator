#include "Sair.h"
#include <sstream>

Sair::Sair(const std::string &frase, Simulador &simulacao)
    : Comandos(frase, simulacao) {}

void Sair::executa() {

    try {
        std::istringstream iss(getFrase());
        std::string cmd;
        iss >> cmd;

        Simulador &s = obtemSimulacao();
        s.jardineiroSai();
    }catch (const std::exception& e) {
        std::cerr << e.what();
    }
}

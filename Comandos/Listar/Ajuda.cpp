#include "Ajuda.h"
#include <iostream>
#include <sstream>

Ajuda::Ajuda(const std::string &frase, Simulador &simulacao)
    : Comandos(frase, simulacao) {
}

void Ajuda::executa() {
    try{
        std::istringstream iss(getFrase());
        char cmd;
        iss >> cmd;

        Simulador &sim =obtemSimulacao();
        sim.ajuda();
    }catch (const std::exception& e) {
        std::cerr << e.what();
    }

}

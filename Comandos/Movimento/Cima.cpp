//
// Created by orlando on 10/26/25.
//

#include "Cima.h"
#include <sstream>

Cima::Cima(const std::string &frase, Simulador &simulacao) : Comandos(frase, simulacao) {

}

void Cima::executa() {
    try{
        std::istringstream iss(getFrase());
        char cmd;
        iss >> cmd;

        Simulador &sim =obtemSimulacao();
        sim.moverJardineiro(cmd);
    }catch (const std::exception& e) {
        std::cerr << e.what();
    }
}



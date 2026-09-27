#include "Lplanta.h"
#include <sstream>
#include <iostream>

using std::cout;

Listar_planta::Listar_planta(const std::string &frase, Simulador &simulacao) : Comandos(frase, simulacao) {
}


void Listar_planta::executa() {
    try {
        if (!validaComando(2, "lplanta <l> <c>")) return;

        std::istringstream iss(getFrase());
        std::string cmd;
        char linha, coluna;

        iss >> cmd >> linha >> coluna;

        Simulador &sim = obtemSimulacao();
        sim.listarPlanta(linha, coluna);

    } catch (const std::exception &e) {
        std::cerr << e.what();
    }
}
#include "Lista_Ferramentas.h"
#include <iostream>
#include <sstream>

Listar_ferramentas::Listar_ferramentas(const std::string &frase, Simulador &simulacao) : Comandos(frase, simulacao) {
}

using std::cout;

void Listar_ferramentas::executa() {
    try {
        std::istringstream iss(getFrase());
        char cmd;
        iss >> cmd;

        Simulador &sim = obtemSimulacao();
        sim.listarFerramentas();
    } catch (const std::exception &e) {
        std::cerr << e.what();
    }
}

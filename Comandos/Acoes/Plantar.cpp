#include "Plantar.h"

Plantar::Plantar(const std::string &frase, Simulador &simulacao)
    : Comandos(frase, simulacao) {}

void Plantar::executa() {

    try {
        if (!validaComando(3,"Planta <l> <c> tipo")){return;}

        std::istringstream iss(getFrase());
        std::string cmd;
        char linhaChar, colunaChar, tipo;

        iss >> cmd >> linhaChar >> colunaChar >> tipo;

        Simulador &sim= obtemSimulacao();
        sim.plantar(linhaChar,colunaChar,tipo);

    }catch (const std::exception& e) {
        std::cerr << e.what();
    }
}

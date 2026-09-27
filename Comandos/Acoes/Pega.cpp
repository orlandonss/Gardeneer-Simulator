#include "Pega.h"

Pega::Pega(const std::string &frase, Simulador &simulacao)
    : Comandos(frase, simulacao) {
}

void Pega::executa() {
    try {
        if (!validaComando(1,"pega <id>")){return;}

        std::istringstream iss(getFrase());
        std::string cmd;
        //char id;
        int id;
        iss >> cmd >>id;

        Simulador &sim= obtemSimulacao();
        sim.pegaFerramenta(id);

    }catch (const std::exception& e) {
        std::cerr << e.what();
    }
}

#include "Colhe.h"

Colhe::Colhe(const std::string &frase, Simulador &simulacao)
    : Comandos(frase, simulacao) {
}

void Colhe::executa() {
    try {
        if (!validaComando(2, "Colhe <l> <c>")) { return; }

        std::istringstream iss(getFrase());
        std::string cmd;
        char linhaChar, colunaChar;

        iss >> cmd >> linhaChar >> colunaChar;

        Simulador &sim = obtemSimulacao();
        sim.colher(linhaChar, colunaChar);
    } catch (const std::exception &e) {
        std::cerr << e.what();
    }
}

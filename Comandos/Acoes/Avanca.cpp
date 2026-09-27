#include "Avanca.h"


Avanca::Avanca(const std::string &frase, Simulador &simulacao)
    : Comandos(frase, simulacao) {
}

void Avanca::executa() {
    try {
        if (!validaComando(0, 1, "avanca [n]"))
            return;

        std::istringstream iss(getFrase());
        std::string cmd;
        iss >> cmd;

        int n = 1;
        if (!(iss >> n)) {
            n = 1;
        }

        Simulador &sim = obtemSimulacao();
        sim.avancarTempo(n);
    } catch (const std::exception& e) {
        std::cerr << e.what();
    }
}

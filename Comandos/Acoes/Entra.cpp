#include "Entra.h"

Entra::Entra(const std::string &frase, Simulador &simulacao)
    : Comandos(frase, simulacao) {
}

void Entra::executa() {
    try {
        if (!validaComando(2, "entra <l> <c>"))return;
        std::istringstream iss(getFrase());
        std::string cmd;
        char linhaChar, colunaChar;


        iss >> cmd >> linhaChar >> colunaChar;

        Simulador &s = obtemSimulacao();
        s.jardineiroEntra(linhaChar, colunaChar);
    } catch (const std::exception &e) {
        std::cerr << e.what();
    }
}

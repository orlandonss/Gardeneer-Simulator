#include "Largar.h"

Largar::Largar(const std::string &frase, Simulador &simulacao)
    : Comandos(frase, simulacao) {
}


void Largar::executa() {
    try {
        obtemSimulacao().largaferramenta();
    } catch (const std::exception& e) {
        std::cerr << e.what();
    }
}

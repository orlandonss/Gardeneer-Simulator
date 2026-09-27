#include "Compra.h"

Compra::Compra(const std::string &frase, Simulador &simulacao)
    : Comandos(frase, simulacao) {
}

void Compra::executa() {
    try{
        if (!validaComando(1, "compra <tipo>"))return;

        std::istringstream iss(getFrase());
        std::string cmd;
        char tipo;

        iss >> cmd >> tipo;

        Simulador &sim = obtemSimulacao();
        sim.compraFerramenta(tipo);
    }
    catch (const std::exception& e) {
        std::cerr << e.what();
    }
}

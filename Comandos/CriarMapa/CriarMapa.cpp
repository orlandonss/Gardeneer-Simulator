// CriarMapa.cpp
#include "CriarMapa.h"
#include <iostream>
#include <sstream>

CriarMapa::CriarMapa(const std::string &frase, Simulador &sim)
    : Comandos(frase, sim) {
}

void CriarMapa::executa() {
    try {
        if (!validaComando(2, "jardim <linhas> <colunas>"))return;;
        std::istringstream iss(getFrase());
        std::string cmd;
        int linhas, colunas;
        iss >> cmd >> linhas >> colunas;


        Simulador &sim = obtemSimulacao();
        sim.criarJardim(linhas, colunas);
    } catch (const std::exception &e) {
        std::cerr << e.what() << "> ";
    }
}

#include "Executa.h"
#include <iostream>
#include <fstream>
#include <sstream>

Executa::Executa(const std::string &frase, Simulador &simulacao)
    : Comandos(frase, simulacao) {}

void Executa::executa() {
    std::istringstream iss(getFrase());
    std::string cmd, nomeFicheiro;

    iss >> cmd >> nomeFicheiro;

    if (nomeFicheiro.empty()) {
        std::cout << "ERRO: uso correto é executa <ficheiro>\n";
        return;
    }

    std::ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        std::cout << "ERRO: nao foi possivel abrir o ficheiro '" << nomeFicheiro << "'.\n";
        return;
    }

    std::cout << "--- A executar comandos do ficheiro: " << nomeFicheiro << " ---\n";

    std::string linhaFicheiro;

    while (std::getline(ficheiro, linhaFicheiro)) {
        if (linhaFicheiro.empty()) continue;

        std::cout << "> " << linhaFicheiro << "\n"; // Mostra o comando na consola

        std::istringstream issLinha(linhaFicheiro);

        Comandos* novoComando = Comandos::criaComando(issLinha, obtemSimulacao());

        if (novoComando != nullptr) {
            novoComando->executa();
            delete novoComando;
        } else {
            std::cout << "Comando invalido no ficheiro: " << linhaFicheiro << "\n";
        }
    }

    std::cout << "--- Fim da execucao do ficheiro ---\n";
    ficheiro.close();
}
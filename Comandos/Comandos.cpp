#include "Comandos.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Listar/Listar_Area.h"
#include "Listar/Ajuda.h"
#include "CriarMapa/CriarMapa.h"
#include "Fim/Fim.h"
#include "Listar/Lsolo.h"
#include "Listar/Lplanta.h"
#include "Listar/Lplantas.h"
#include "Listar/Lista_Ferramentas.h"
#include "Acoes/Entra.h"
#include "Acoes/Sair.h"
#include "Acoes/Usa.h"
#include "../Comandos/Acoes/Avanca.h"
#include "../Comandos/Acoes/Colhe.h"
#include "../Comandos/Acoes/Pega.h"
#include "../Comandos/Acoes/Plantar.h"
#include "../Comandos/Acoes/Largar.h"
#include "../Comandos/Acoes/Compra.h"
#include "../Comandos/Movimento/Baixo.h"
#include "../Comandos/Movimento/Cima.h"
#include "../Comandos/Movimento/Direita.h"
#include "../Comandos/Movimento/Esquerda.h"
#include "../Comandos/Gerais/Apaga.h"
#include "../Comandos/Gerais/Executa.h"
#include "../Comandos/Gerais/Grava.h"
#include "../Comandos/Gerais/Recupera.h"
using std::cout;

Comandos::Comandos(const std::string &frase,  Simulador &simulacao)
    : frase(frase), simulacao(simulacao) {
}

int Comandos::contaArgumentos() const {
    std::istringstream iss(frase);
    std::string cmd;

    if (!(iss >> cmd))
        return 0;
    int n = 0;

    std::string tmp;
    while (iss >> tmp)
        ++n;
    return n;
}

bool Comandos::validaComando(int minimo, int maximo, const std::string &uso) const {
    int n = contaArgumentos();
    if (n < minimo || n > maximo) {
        std::cerr << "Numero invalido de argumentos.\n";
        std::cerr<< "Uso: " << uso << '\n';
        std::cerr << "> ";
        return false;
    }
    return true;
}


bool Comandos::validaComando(int esperado, const std::string &uso) const {
    int n = contaArgumentos();
    if (n != esperado) {
        std::cerr << "Numero invalido de argumentos!!! \n";
        std::cerr << "Uso: " << uso << '\n';
        std::cerr << "> ";
        return false;
    }
    return true;
}

Comandos *Comandos::criaComando(std::istream &in, Simulador &sim) {
    std::string linha;
    if (!std::getline(in, linha))
        return nullptr;

    std::istringstream iss(linha);
    std::string cmd;
    iss >> cmd;

    if (cmd == "jardim") { return new CriarMapa(linha, sim); }
    if (cmd == "lsolo") { return new Listar_SOLO(linha, sim); }
    if (cmd == "lplantas") { return new Listar_plantas(linha, sim); }
    if (cmd == "lplanta") { return new Listar_planta(linha, sim); }
    if (cmd == "larea") { return new Listar_Area(linha, sim); }
    if (cmd == "lferr") { return new Listar_ferramentas(linha, sim); }
    if (cmd == "ajuda") { return new Ajuda(linha, sim); }
    if (cmd == "avanca") { return new Avanca(linha, sim); }
    if (cmd == "colhe") { return new Colhe(linha, sim); }
    if (cmd == "planta") { return new Plantar(linha, sim); }
    if (cmd == "larga") { return new Largar(linha, sim); }
    if (cmd == "pega") { return new Pega(linha, sim); }
    if (cmd == "compra") { return new Compra(linha, sim); }
    if (cmd == "entra") { return new Entra(linha, sim); }
    if (cmd == "sair") { return new Sair(linha, sim); }
    if (cmd == "grava") { return new Grava(linha, sim); }
    if (cmd == "apaga") { return new Apaga(linha, sim); }
    if (cmd == "executa") { return new Executa(linha, sim); }
    if (cmd == "usa") { return new Usa(linha, sim); }
    if (cmd == "recupera") { return new Recupera(linha, sim); }
    if (cmd == "c") { return new Cima(linha, sim); }
    if (cmd == "b") { return new Baixo(linha, sim); }
    if (cmd == "d") { return new Direita(linha, sim); }
    if (cmd == "e") { return new Esquerda(linha, sim); }
    if (cmd == "fim") { return new Fim(linha, sim); }

    return nullptr;
}

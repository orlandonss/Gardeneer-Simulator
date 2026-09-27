#include "Regador.h"
#include "../Settings/Settings.h"
#include "../Solo/Solo.h"
#include <iostream>
#include <sstream>

Regador::Regador()
    : capacidade(Settings::Regador::capacidade), // 200
      dose(Settings::Regador::dose),             // 10
      acabou(false)
{
}

char Regador::get_tipo_Ferramenta() const {
    return 'g';
}

std::string Regador::getInfoFerramenta() const {
    std::ostringstream oss;
    if (acabou) {
        return "Regador (Destruido)";
    }
    oss << "Regador (Cap: " << capacidade << ")";
    return oss.str();
}

bool Regador::funcionalidade_ferramenta(Solo* solo) {
    if (acabou) return false;
    if (solo == nullptr) return false;

    int aguaAtual = solo->getAgua_solo();
    solo->setAgua(aguaAtual + dose);

    std::cout << "--> Regaste o solo (+10 agua). Nivel de agua: "
              << solo->getAgua_solo() << ".\n";

    capacidade -= dose;

    if (capacidade <= 0) {
        capacidade = 0;
        acabou = true;

        std::cout << "O regador ficou vazio!\n";
        std::cout << "--> O jardineiro, frustrado, atira o regador para tao longe que ele saiu do simulador!\n";
    } else {
        std::cout << "Restam " << capacidade << " unidades no regador.\n";
    }

    return true;
}

bool Regador::jaAcabou() const {
    return acabou;
}

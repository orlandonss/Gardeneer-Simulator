// Drone.cpp
#include "Drone.h"
#include "../Mapa/Jardim.h"
#include "../Settings/Settings.h"
#include <iostream>

Drone::Drone(Jardim* jardimRef)
    : jardim(jardimRef), usado(false)
{
}

char Drone::get_tipo_Ferramenta() const {
    return 'z';
}

std::string Drone::getInfoFerramenta() const {
    if (usado) return "Drone (Sem Bateria)";
    return "Drone de Irrigacao (1 Uso)";
}

bool Drone::funcionalidade_ferramenta(Solo* solo) {
    // 1. Validar estado
    if (usado) {
        std::cout << "O drone nao tem bateria. Tens de comprar outro.\n";
        return false;
    }
    if (jardim == nullptr || solo == nullptr) return false;

    int l_atual = 0, c_atual = 0;
    if (!jardim->getCoordenadas(solo, l_atual, c_atual)) {
        std::cout << "Erro: O drone nao consegue localizar este solo no mapa.\n";
        return false;
    }
    char lChar = (char)('A' + l_atual);
    char cChar = (char)('A' + c_atual);

    std::cout << "--> Drone ativado nas coordenadas [" << lChar << "][" << cChar << "].\n";
    std::cout << "Desejas irrigar a (L)inha inteira ou a (C)oluna inteira? ";

    char opcao;
    std::cin >> opcao;

    int numLinhas = jardim->getLinha();
    int numColunas = jardim->getColuna();
    int count = 0;

    if (opcao == 'l' || opcao == 'L') {
        for (int j = 0; j < numColunas; ++j) {
            Solo* s = &jardim->getArea()[l_atual][j];
            s->setAgua(s->getAgua_solo() + Settings::Drone::dose);
            count++;
        }
        std::cout << "--> A Regar! Linha " << lChar << " irrigada (" << count << " posicoes).\n";
    }
    else if (opcao == 'c' || opcao == 'C') {
        for (int i = 0; i < numLinhas; ++i) {
            Solo* s = &jardim->getArea()[i][c_atual];
            s->setAgua(s->getAgua_solo() + Settings::Drone::dose);
            count++;
        }
        std::cout << "--> A Regar! Coluna " << cChar << " irrigada (" << count << " posicoes).\n";
    }
    else {
        std::cout << "Opcao invalida. O drone voltou para a base.\n";
        return false;
    }
    usado = true;
    std::cout << "--> A bateria do Drone acabou. Ele vai para a reciclagem.\n";

    return true;
}

bool Drone::jaAcabou() const {
    return usado;   // ends ONLY when usado == true
}

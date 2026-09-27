#include "TesouraDePodar.h"
#include "../Solo/Solo.h"
#include "../Planta/Planta.h"
#include <iostream>

TesouraDePodar::TesouraDePodar() {
}

char TesouraDePodar::get_tipo_Ferramenta() const {
    return 't';
}

std::string TesouraDePodar::getInfoFerramenta() const {
    return "Tesoura de Podar";
}

bool TesouraDePodar::funcionalidade_ferramenta(Solo* solo) {
    if (solo == nullptr) return false;

    Planta* p = solo->getPlanta();

    if (p == nullptr) {
        std::cout << "Nao ha nenhuma planta aqui para podar.\n";
        return false;
    }

    if (p->getBeleza() == Planta::Beleza::FEIA) {
        std::cout << "--> O jardineiro identificou uma planta feia ("
                  << p->getInfoPlanta() << ") e cortou-a!\n";

        delete p;
        solo->setPlanta(nullptr);
        return true;
    }
    std::cout << "--> O jardineiro acha a planta " << p->getInfoPlanta()
                  << " bonita (ou neutra) e guardou a tesoura.\n";
    return false;
}


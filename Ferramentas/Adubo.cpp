#include "Adubo.h"
#include "../Settings/Settings.h"
#include "../Solo/Solo.h"
#include <iostream>
#include <sstream>
Adubo::Adubo()
    : capacidade(Settings::Adubo::capacidade),
      dose(Settings::Adubo::dose),
      acabou(false)
{
}

///MÉTODOS VIRTUAIS
char Adubo::get_tipo_Ferramenta() const {
    return 'a';
}

std::string Adubo::getInfoFerramenta() const {
    std::ostringstream oss;
    if (acabou) {
        return "Adubo (Vazio)";
    }
    oss << "Adubo (Cap: " << capacidade << ")";
    return oss.str();
}
bool Adubo::funcionalidade_ferramenta(Solo* solo) {
    if (acabou) {
        std::cout << "Nao ha adubo! O pacote esta vazio e voou com o vento." << std::endl;
        return false;
    }

    if (solo == nullptr) {
        std::cout << "Erro: Nao e possivel aplicar adubo num espaço vazio." << std::endl;
        return false;
    }
    std::cout << "A aplicar adubo na planta..." << std::endl;

    int nutrientesAtuais = solo->getNutrientes_solo();
    solo->setNutrientes(nutrientesAtuais + dose);

    std::cout << "Nutrientes aumentados de " << nutrientesAtuais
              << " para " << (nutrientesAtuais + dose) << "." << std::endl;

    capacidade -= dose;

    if (capacidade <= 0) {
        capacidade = 0;
        acabou = true;

        std::cout << "O pacote de adubo acabou!" << std::endl;
        std::cout << "O pacote vazio ficou leve e o vento o levou para o quintal do vizinho." << std::endl;
    } else {
        std::cout << "Ainda restam " << capacidade << " unidades de adubo." << std::endl;
    }

    return true;
}

bool Adubo::jaAcabou() const {
    return acabou;
}


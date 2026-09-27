#include "Roseira.h"
#include "../Mapa/Jardim.h"

using namespace std;

// Construtor atualizado: guarda o jardim e a posição
Roseira::Roseira(Jardim* j, int linha, int coluna)
    : Planta(Settings::Roseira::inicial_agua,
             Settings::Roseira::inicial_nutrientes,
             Beleza::BONITA),
      jardimRef(j), pLinha(linha), pColuna(coluna)
{

}

char Roseira::getTipo() const {
    return 'r';
}

void Roseira::atualizar(Solo &solo) {
    if (!getEstado()) return;

    // Perda natural
    int aguaAtual = getAgua_planta();
    int nutAtual = getNutrientes_planta();
    setAgua(aguaAtual - Settings::Roseira::perda_agua);
    setNutrientes(nutAtual - Settings::Roseira::perda_nutrientes);

    // Absorção do Solo (Água)
    int aguaSolo = solo.getAgua_solo();
    if (aguaSolo > 0) {
        int aAbsorver = min(aguaSolo, Settings::Roseira::absorcao_agua);
        solo.setAgua(aguaSolo - aAbsorver);
        setAgua(getAgua_planta() + aAbsorver);
    }

    // Absorção do Solo (Nutrientes)
    int nutSolo = solo.getNutrientes_solo();
    if (nutSolo > 0) {
        int nAbsorver = min(nutSolo, Settings::Roseira::absorcao_nutrientes);
        solo.setNutrientes(nutSolo - nAbsorver);
        setNutrientes(getNutrientes_planta() + nAbsorver);
    }

    bool morre = false;

    if (getAgua_planta() <= Settings::Roseira::morre_agua_menor) {
        morre = true;
    }
    else if (getNutrientes_planta() <= Settings::Roseira::morre_nutrientes_menor) {
        morre = true;
    }
    else if (getNutrientes_planta() >= Settings::Roseira::morre_nutrientes_maior) {
        morre = true;
    }
    // Nova regra: Morre se estiver totalmente rodeada (8 vizinhos)
    else if (jardimRef->contaVizinhosComPlanta(pLinha, pColuna) == 8) {
        morre = true;
    }

    if (morre) {
        setEstado(false);

        // Devolve metade ao solo
        int aguaParaDevolver = max(0, getAgua_planta()) / 2;
        int nutParaDevolver = max(0, getNutrientes_planta()) / 2;

        solo.setAgua(solo.getAgua_solo() + aguaParaDevolver);
        solo.setNutrientes(solo.getNutrientes_solo() + nutParaDevolver);
        return; // Morreu, não faz reprodução
    }

    if (getNutrientes_planta() > 100) {
        int l_filho, c_filho;

        // Pede ao jardim um lugar livre à volta
        if (jardimRef->getVizinhoLivreAleatorio(pLinha, pColuna, l_filho, c_filho)) {


            Roseira* novaRosa = new Roseira(jardimRef, l_filho, c_filho);

            novaRosa->setNutrientes(25);
            novaRosa->setAgua(getAgua_planta() / 2);

            // Regras da planta mãe:
            setNutrientes(100);
            setAgua(getAgua_planta() / 2);

            jardimRef->adicionarPlanta(l_filho, c_filho, novaRosa);
            jardimRef->set_car(l_filho,c_filho,'r');
        }
    }
}

std::string Roseira::getInfoPlanta() const {
    std::ostringstream os;
    os << "Planta: Roseira\n";
    os << "> Beleza: " << belezaToString(getBeleza()) << "\n";
    os << "Agua: " << getAgua_planta() << " | Nutrientes: " << getNutrientes_planta() << "\n";
    return os.str();
}
#include "ErvaDaninha.h"
#include "../Mapa/Jardim.h"
#include "../Solo/Solo.h"

ErvaDaninha::ErvaDaninha(Jardim* j, int l, int c)
    : Planta(Settings::ErvaDaninha::inicial_agua,
             Settings::ErvaDaninha::inicial_nutrientes,
             Beleza::FEIA),
      jardimRef(j), pLinha(l), pColuna(c),
      idade(0),
      instantesDesdeUltimaMult(0) {}

char ErvaDaninha::getTipo() const {
    return 'e';
}

void ErvaDaninha::atualizar(Solo &solo) {
    if (!getEstado()) return;

    // 1. Envelhecimento
    idade++;
    instantesDesdeUltimaMult++;

    int aguaSolo = solo.getAgua_solo();
    if (aguaSolo > 0) {
        int aAbsorver = std::min(aguaSolo, Settings::ErvaDaninha::absorcao_agua);
        solo.setAgua(aguaSolo - aAbsorver);
        setAgua(getAgua_planta() + aAbsorver);
    }

    int nutSolo = solo.getNutrientes_solo();
    if (nutSolo > 0) {
        int nAbsorver = std::min(nutSolo, Settings::ErvaDaninha::absorcao_nutrientes);
        solo.setNutrientes(nutSolo - nAbsorver);
        setNutrientes(getNutrientes_planta() + nAbsorver);
    }

    if (idade >= Settings::ErvaDaninha::morre_instantes) {
        setEstado(false);
        return;
    }

    if (getNutrientes_planta() > 30 && instantesDesdeUltimaMult >= 5) {

        int lDest, cDest;

        // Pede um vizinho qualquer (ocupado ou não)
        if (jardimRef->getVizinhoAleatorio(pLinha, pColuna, lDest, cDest)) {

            ErvaDaninha* nova = new ErvaDaninha(jardimRef, lDest, cDest);

            jardimRef->substituirPlanta(lDest, cDest, nova);

            instantesDesdeUltimaMult = 0;
        }
    }
}

std::string ErvaDaninha::getInfoPlanta() const {
    std::ostringstream os;
    os << "Planta: Erva Daninha (Pos: " << pLinha << "," << pColuna << ")\n";
    os << "Beleza: " << belezaToString(getBeleza()) << "\n";
    os << "Idade: " << idade << "/" << Settings::ErvaDaninha::morre_instantes << "\n";
    os << "Timer Reprod: " << instantesDesdeUltimaMult << "\n";
    os << "Agua: " << getAgua_planta() << " | Nutrientes: " << getNutrientes_planta() << "\n";
    return os.str();
}
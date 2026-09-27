#include "Maracuja.h"
#include "../Settings/Settings.h"
#include "../Solo/Solo.h"
#include "../Mapa/Jardim.h"
#include <sstream>
#include <algorithm>

Maracuja::Maracuja(Jardim *j, int l, int c)
    : Planta(Settings::Maracuja::inicial_agua,
             Settings::Maracuja::inicial_nutrientes,
             Beleza::BONITA),
      jardim(j), linha(l), coluna(c),
      idade(0),
      instantesAguaBaixa(0),
      instantesAguaAlta(0),
      nutrientesAbsorvidosTotal(0) {
}

char Maracuja::getTipo() const {
    return 'x';
}

void Maracuja::atualizar(Solo &solo) {
    idade++;
    int aguaSolo = solo.getAgua_solo();
    int absorcaoAgua = std::min(Settings::Maracuja::absorcao_agua, aguaSolo);
    if (absorcaoAgua > 0) {
        solo.setAgua(aguaSolo - absorcaoAgua);
        setAgua(getAgua_planta() + absorcaoAgua);
    }
    int nutrSolo = solo.getNutrientes_solo();
    int absorcaoNutr = std::min(Settings::Maracuja::absorcao_nutrientes, nutrSolo);
    if (absorcaoNutr > 0) {
        solo.setNutrientes(nutrSolo - absorcaoNutr);
        setNutrientes(getNutrientes_planta() + absorcaoNutr);
        nutrientesAbsorvidosTotal += absorcaoNutr;
    }

    setAgua(getAgua_planta() - Settings::Maracuja::custo_agua_turno);
    setNutrientes(getNutrientes_planta() - Settings::Maracuja::custo_nutrientes_turno);

    bool morre = false;

    if (getNutrientes_planta() <= 0) {
        morre = true;
    }

    if (getAgua_planta() < Settings::Maracuja::morre_agua_min) {
        instantesAguaBaixa++;
    } else {
        instantesAguaBaixa = 0;
    }
    if (instantesAguaBaixa >= Settings::Maracuja::instantes_agua_min) {
        morre = true;
    }

    if (getAgua_planta() > Settings::Maracuja::morre_agua_max) {
        instantesAguaAlta++;
    } else {
        instantesAguaAlta = 0;
    }
    if (instantesAguaAlta >= Settings::Maracuja::instantes_agua_max) {
        morre = true;
    }

    if (morre) {
        setEstado(false);

        int nutrDevolver = (int) (nutrientesAbsorvidosTotal * 0.70);
        solo.setNutrientes(solo.getNutrientes_solo() + nutrDevolver);

        int aguaDevolver = (int) (getAgua_planta() * 0.30);
        solo.setAgua(solo.getAgua_solo() + aguaDevolver);

        return;
    }

    if (getNutrientes_planta() > Settings::Maracuja::mult_nutrientes_min &&
        getAgua_planta() > Settings::Maracuja::mult_agua_min) {
        if (jardim != nullptr) {
            int lDest, cDest;
            if (jardim->getVizinhoLivreAleatorio(linha, coluna, lDest, cDest)) {
                Maracuja *novaPlanta = new Maracuja(jardim, lDest, cDest);

                novaPlanta->setAgua(Settings::Maracuja::nova_planta_agua); // 20
                novaPlanta->setNutrientes(Settings::Maracuja::nova_planta_nutrientes); // 20

                if (jardim->adicionarPlanta(lDest, cDest, novaPlanta)) {
                    setAgua(getAgua_planta() - Settings::Maracuja::custo_mult_agua); // -40
                    setNutrientes(getNutrientes_planta() - Settings::Maracuja::custo_mult_nutrientes); // -40
                } else {
                    delete novaPlanta; // Se falhar adição
                }
            }
        }
    }
}

std::string Maracuja::getInfoPlanta() const {
    std::ostringstream os;
    os << "Planta: Maracuja (x)\n";
    os << "Beleza: " << belezaToString(getBeleza()) << "\n";
    os << "Idade: " << idade << "\n";
    os << "Agua: " << getAgua_planta() << " | Nutrientes: " << getNutrientes_planta() << "\n";
    os << "Status Morte: Baixa(" << instantesAguaBaixa << "/2) Alta(" << instantesAguaAlta << "/3)\n";
    return os.str();
}

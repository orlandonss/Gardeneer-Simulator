#include "Cacto.h"
#include "../Solo/Solo.h"

Cacto::Cacto()
    : Planta(0, Settings::Cacto::absorcao_nutrientes, Beleza::NEUTRA),
      instantesAguaAlta(0),
      instantesNutrientesBaixos(0) {}

char Cacto::getTipo() const {
    return 'c';
}

void Cacto::atualizar(Solo &solo) {

    int aguaSolo = solo.getAgua_solo();
    int absorvida =
        (aguaSolo * Settings::Cacto::absorcao_agua_percentagem) / 100;

    if (absorvida > 0) {
        solo.setAgua(aguaSolo - absorvida);
        setAgua(getAgua_planta() + absorvida);
    }

    int nutrientesSolo = solo.getNutrientes_solo();
    int n = std::min(Settings::Cacto::absorcao_nutrientes, nutrientesSolo);

    if (n > 0) {
        solo.setNutrientes(nutrientesSolo - n);
        setNutrientes(getNutrientes_planta() + n);
    }

    if (solo.getAgua_solo() > Settings::Cacto::morre_agua_solo_maior) {
        instantesAguaAlta++;
    } else {
        instantesAguaAlta = 0;
    }

    if (solo.getNutrientes_solo() < Settings::Cacto::morre_nutrientes_solo_menor) {
        instantesNutrientesBaixos++;
    } else {
        instantesNutrientesBaixos = 0;
    }

    if (instantesAguaAlta >= Settings::Cacto::morre_agua_solo_instantes ||
        instantesNutrientesBaixos >= Settings::Cacto::morre_nutrientes_solo_instantes) {
        setEstado(false);
        }
}

std::string Cacto::getInfoPlanta() const {
    std::ostringstream os;

    os << "Planta: Cacto\n";

    os << "Beleza: " << belezaToString(getBeleza()) << "\n";

    os << "Instantes Agua Alta: " << instantesAguaAlta << "\n";

    os << "Instantes Nutrientes Baixos: " << instantesNutrientesBaixos << "\n";

    os << "Agua: " << getAgua_planta() << " | Nutrientes: " << getNutrientes_planta() << "\n";

    return os.str();
}

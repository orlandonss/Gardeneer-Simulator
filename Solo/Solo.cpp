//
// Created by orlando on 10/29/25.
//

#include "Solo.h"
#include <random>
#include "../Random/Random.h"
using namespace std;

Solo::Solo()
    : planta(nullptr), ferramenta(nullptr), nutrientes(Random::getRandom(40, 50)), agua(Random::getRandom(80, 100)),
      estaJardineiro(false), caractere('.') {
}

///SETTERS

void Solo::setPlanta(Planta *novaPlanta) {
    this->planta = novaPlanta;
}


void Solo::setFerramenta(Ferramenta *f) {
    if (ferramenta == f)return;
    delete ferramenta;
    ferramenta = f;
}

Ferramenta* Solo::retirarFerramenta() {
    Ferramenta* temp = ferramenta;
    ferramenta = nullptr;
    return temp;
}
void Solo::setJardineiro(Jardineiro *j) {
    jardineiro = j;
}
void Solo::setAgua(int novaAgua) {
    agua = novaAgua;
}

void Solo::setNutrientes(int novoNutriente) {
    nutrientes = novoNutriente;
}

void Solo::atualiza_solo() {
    //aqui vem a logica em que nos atualizamos o solo
    // o solo vai atualizar consoante a logica das plantas
    //se planta for determindado tipo, realiza deteminada acao
}


///GETTERS

Ferramenta *Solo::verificaFerrameta(int l, int c) const {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            if (ferramenta != nullptr) {
                return ferramenta;
            }
        }
    }
    return nullptr;
}


Planta *Solo::verificaPlanta(int l, int c) const {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < c; j++) {
            if (planta != nullptr) {
                return planta;
            }
        }
    }
    return nullptr;
}


//informacao precisa para que consulte o solo

std::string Solo::getInfo() const {
    ostringstream os;
    os << "Agua : " << agua
            << " Nutrientes: " << nutrientes
            << " Planta: " << planta->getTipo()
            << "Ferramenta: " << ferramenta->get_tipo_Ferramenta()
            << (jardineiro == nullptr ? "" : " Jardineiro: sim");

    return os.str();
}


///AQUI ESTA PRESENTE O DESTRUTOR!!!
Solo::~Solo() {
    delete ferramenta;
    delete planta;
}

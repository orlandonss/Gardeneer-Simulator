#include "Planta.h"

Planta::Planta(int agua,  int nutrientes,Beleza beleza)
    : agua(agua), nutrientes(nutrientes), viva(true), beleza(beleza) {}

Planta::~Planta(){};



std::string Planta::belezaToString(Beleza b) {
    switch (b) {
        case Beleza::FEIA:   return "Feia";
        case Beleza::NEUTRA: return "Neutra";
        case Beleza::BONITA: return "Bonita";
    }
    return "";
}
void Planta::setAgua(int newAgua) {
    agua = newAgua;
}

void Planta::setNutrientes(int newNutrientes) {
    nutrientes = newNutrientes;
}

void Planta::setEstado(bool estado) {
    viva = estado;
}

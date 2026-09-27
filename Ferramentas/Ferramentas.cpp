#include "Ferramentas.h"

int Ferramenta::prox_n_serie = 1;

Ferramenta::Ferramenta()
    : n_serie(prox_n_serie++)
{
}

Ferramenta::~Ferramenta() = default;

int Ferramenta::getId() const {
    return n_serie;
}

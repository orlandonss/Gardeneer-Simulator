#include "Jardineiro.h"
#include "../Ferramentas/Regador.h"
#include "../Ferramentas/Adubo.h"
#include "../Ferramentas/TesouraDePodar.h"
#include "../Ferramentas/Drone.h"
Jardineiro::Jardineiro()
    : ferramenta_a_segurar(nullptr), c(' '), l(' '), esta_no_jardim(false)
{
}
Jardineiro::Jardineiro(const Jardineiro &origem)
    : ferramenta_a_segurar(nullptr), c(origem.c), l(origem.l), esta_no_jardim(origem.esta_no_jardim)
{
    for (Ferramenta* fOriginal : origem.ferramentas) {
        if (fOriginal == nullptr) continue;

        Ferramenta* fNova = nullptr;
        char tipo = fOriginal->get_tipo_Ferramenta();

        switch (tipo) {
            case 'g': fNova = new Regador(); break;
            case 'a': fNova = new Adubo(); break;
            case 't': fNova = new TesouraDePodar(); break;
            case 'z': fNova = new Drone(nullptr); break;
        }

        if (fNova != nullptr) {
            this->ferramentas.push_back(fNova);
            if (origem.ferramenta_a_segurar == fOriginal) {
                this->ferramenta_a_segurar = fNova;
            }
        }
    }
}
Jardineiro::~Jardineiro() {
    for (Ferramenta* f : ferramentas) {
        delete f;
    }
    ferramentas.clear();
}

bool Jardineiro::adicionarFerramenta(Ferramenta *f) {
    if (f == nullptr) return false;
    ferramentas.push_back(f);
    return true;
}

void Jardineiro::setFerramenta_naMao(Ferramenta *f) {
    ferramenta_a_segurar = f;
}

bool Jardineiro::retiraFerramenta_da_Mao() {
    if (ferramenta_a_segurar == nullptr) return false;
    ferramenta_a_segurar = nullptr;
    return true;
}

bool Jardineiro::removeFerramenta(Ferramenta *f) {
    for (auto it = ferramentas.begin(); it != ferramentas.end(); ++it) {
        if (*it == f) {
            if (ferramenta_a_segurar == f) {
                ferramenta_a_segurar = nullptr;
            }
            delete *it;
            ferramentas.erase(it);
            return true;
        }
    }
    return false;
}

bool Jardineiro::soltarFerramenta(Ferramenta *f) {
    for (auto it = ferramentas.begin(); it != ferramentas.end(); ++it) {
        if (*it == f) {
            // Se estiver na mão, tira primeiro
            if (ferramenta_a_segurar == f) {
                ferramenta_a_segurar = nullptr;
            }

            ferramentas.erase(it);
            return true;
        }
    }
    return false;
}


Ferramenta* Jardineiro::getFerramentaPorID(int id) const {
    for (Ferramenta* f : ferramentas) {
        if (f->getId() == id) {
            return f;
        }
    }
    return nullptr;
}


void Jardineiro::Sai() {
    esta_no_jardim = false;
}

bool Jardineiro::Entra(char linha, char coluna) {
    l = linha;
    c = coluna;
    esta_no_jardim = true;
    return true;
}
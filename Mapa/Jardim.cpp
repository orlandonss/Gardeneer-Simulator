// Jardim.cpp
#include "Jardim.h"
#include <iostream>
#include "../Ferramentas/Adubo.h"
#include "../Ferramentas/Drone.h"
#include "../Ferramentas/Regador.h"
#include "../Ferramentas/TesouraDePodar.h"
#include "../Random/Random.h"
#include "../Planta/Planta.h"
#include "../Planta/Cacto.h"
#include "../Planta/Roseira.h"
#include "../Planta/ErvaDaninha.h"
#include "../Planta/Maracuja.h"
using std::cout;

Jardim::Jardim(int l, int c)
    : linha(l), coluna(c), car(' '), area(nullptr) {
    area = new Solo *[linha];

    for (int i = 0; i < linha; ++i) {
        area[i] = new Solo[coluna];
    }

    int j = 0;
    while (j != 3) {
        gera_ferramenta_posicao_aleatoria();
        j++;
    }
}
Jardim::Jardim(const Jardim &origem)
    : linha(origem.linha), coluna(origem.coluna), car(origem.car), area(nullptr), ptr_jardineiro(nullptr)
{
    area = new Solo*[linha];
    for (int i = 0; i < linha; ++i) {
        area[i] = new Solo[coluna];
    }

    // Copiar conteúdo Célula a Célula
    for (int i = 0; i < linha; ++i) {
        for (int j = 0; j < coluna; ++j) {
            Solo& dest = area[i][j];
            const Solo& src = origem.area[i][j];

            dest.setAgua(src.getAgua_solo());
            dest.setNutrientes(src.getNutrientes_solo());
            dest.setCaractere(src.getCaractere_solo());

            if (src.getFerramenta() != nullptr) {
                char tipoF = src.getFerramenta()->get_tipo_Ferramenta();

                Ferramenta* novaF = criaFerramentaPorTipo(tipoF);

                dest.setFerramenta(novaF);
            }

            // C. Copiar Planta (se existir)
            if (src.getPlanta() != nullptr) {
                Planta* pOriginal = src.getPlanta();
                Planta* pNova = nullptr;
                char tipoP = pOriginal->getTipo();
                switch(tipoP) {
                    case 'c': pNova = new Cacto(); break;
                    case 'r': pNova = new Roseira(this, i, j); break;
                    case 'e': pNova = new ErvaDaninha(this, i, j); break;
                    case 'x': pNova = new Maracuja(this, i, j); break;
                }

                if (pNova != nullptr) {
                    pNova->setAgua(pOriginal->getAgua_planta());
                    pNova->setNutrientes(pOriginal->getNutrientes_planta());
                    pNova->setEstado(pOriginal->getEstado());
                    dest.setPlanta(pNova);
                }
            }
        }
    }
}

void Jardim::gerar_Grelha() const {
    if (linha <= 0 || coluna <= 0)
        return;

    cout << "   ";
    for (int c = 0; c < coluna; ++c) {
        cout << " " << char('A' + c) << " ";
    }
    cout << "\n";

    for (int r = 0; r < linha; ++r) {
        cout << " " << char('A' + r) << " ";
        for (int c = 0; c < coluna; ++c) {
            cout << " " << area[r][c].getCaractere_solo() << " ";
        }
        cout << "\n";
    }
}


void Jardim::atualizaJardim() {
    for (int l = 0; l < linha; l++) {
        for (int c = 0; c < coluna; c++) {
            Solo &solo = area[l][c];
            Planta *planta = solo.getPlanta();

            if (planta == nullptr)
                continue;

            planta->atualizar(solo);

            if (!planta->getEstado()) {
                delete planta;

                solo.setPlanta(nullptr);

                if (solo.getFerramenta() != nullptr) {
                    solo.setCaractere(solo.getFerramenta()->get_tipo_Ferramenta());
                } else {
                    solo.setCaractere('.');
                }
            }
        }
    }
}

int Jardim::contaVizinhosComPlanta(int l, int c) const {
    int contador = 0;

    for (int i = l - 1; i <= l + 1; i++) {
        for (int j = c - 1; j <= c + 1; j++) {
            if (i == l && j == c) continue;


            if (i >= 0 && i < linha && j >= 0 && j < coluna) {
                if (area[i][j].getPlanta() != nullptr) {
                    contador++;
                }
            }
        }
    }
    return contador;
}

bool Jardim::getVizinhoLivreAleatorio(int lOrigem, int cOrigem, int &lDest, int &cDest) {

    for (int k = 0; k < 10; k++) {
        int idx = Random::getRandom(0, 7);

        int tentaL = lOrigem;
        int tentaC = cOrigem;

        if (idx == 0) { tentaL--; tentaC--; }
        else if (idx == 1) { tentaL--; }
        else if (idx == 2) { tentaL--; tentaC++; }
        else if (idx == 3) { tentaC--; }
        else if (idx == 4) { tentaC++; }
        else if (idx == 5) { tentaL++; tentaC--; }
        else if (idx == 6) { tentaL++; }
        else { tentaL++; tentaC++; } // idx == 7

        if (tentaL >= 0 && tentaL < linha && tentaC >= 0 && tentaC < coluna) {
            if (area[tentaL][tentaC].getPlanta() == nullptr) {
                lDest = tentaL;
                cDest = tentaC;
                return true;
            }
        }
    }

    return false;
}

bool Jardim::adicionarPlanta(int l, int c, Planta *p) {
    if (l < 0 || l >= linha || c < 0 || c >= coluna) return false;
    if (p == nullptr) return false;

    if (area[l][c].getPlanta() != nullptr) return false;

    area[l][c].setPlanta(p);

    set_car(l, c, p->getTipo());

    return true;
}

bool Jardim::getVizinhoAleatorio(int lOrigem, int cOrigem, int &lDest, int &cDest) {

    for (int k = 0; k < 10; k++) {
        int idx = Random::getRandom(0, 7);

        int tentaL = lOrigem;
        int tentaC = cOrigem;

        if (idx == 0) { tentaL--; tentaC--; }
        else if (idx == 1) { tentaL--; }
        else if (idx == 2) { tentaL--; tentaC++; }
        else if (idx == 3) { tentaC--; }
        else if (idx == 4) { tentaC++; }
        else if (idx == 5) { tentaL++; tentaC--; }
        else if (idx == 6) { tentaL++; }
        else { tentaL++; tentaC++; } // idx == 7

        if (tentaL >= 0 && tentaL < linha && tentaC >= 0 && tentaC < coluna) {
            lDest = tentaL;
            cDest = tentaC;
            return true;
        }
    }

    return false;
}


bool Jardim::substituirPlanta(int l, int c, Planta *p) {
    if (l < 0 || l >= linha || c < 0 || c >= coluna) return false;

    Planta *plantaExistente = area[l][c].getPlanta();
    if (plantaExistente != nullptr) {
        delete plantaExistente;
        area[l][c].setPlanta(nullptr);
    }

    area[l][c].setPlanta(p);
    set_car(l, c, p->getTipo());

    return true;
}

Ferramenta *Jardim::criaFerramentaPorTipo(char tipo) {
    switch (tipo) {
        case 'g': return new Regador();
        case 'a': return new Adubo();
        case 't': return new TesouraDePodar();
        case 'z': return new Drone(this);
        default: return nullptr;
    }
}

bool Jardim::getCoordenadas(const Solo* soloAlvo, int &linha, int &coluna) const {
    if (area == nullptr) return false;
    for (int i = 0; i < this->linha; ++i) {
        for (int j = 0; j < this->coluna; ++j) {
            if (&area[i][j] == soloAlvo) {
                linha = i;
                coluna = j;
                return true;
            }
        }
    }
    return false; // Não encontrou
}
void Jardim::gera_ferramenta_posicao_aleatoria() {
    if (area == nullptr) return;
    if (linha <= 0 || coluna <= 0) return;

    int tentativas = 0;
    while (tentativas < 100) {
        int l = Random::getRandom(0, linha - 1);
        int c = Random::getRandom(0, coluna - 1);

        Solo *solo = &area[l][c];

        if (solo->getFerramenta() == nullptr) {
            char tipo = gera_feramenta_random();
            Ferramenta *f = criaFerramentaPorTipo(tipo);
            if (f != nullptr) {
                solo->setFerramenta(f);
                if (solo->getPlanta() == nullptr && solo->getJardineiro() == nullptr) {
                    set_car(l, c, tipo);
                }
                break;
            }
        }
        tentativas++;
    }
}

void Jardim::set_ptr_jardineiro(Jardineiro *j) {
  ptr_jardineiro=j;
}


char Jardim::gera_feramenta_random() const {
    const char tipos[4] = {'g', 'a', 't', 'd'};
    int idx = Random::getRandom(0, 3);
    return tipos[idx];
}

void Jardim::set_car(int l, int c, char crtr) const {
    if (l < 0 || l >= linha || c < 0 || c >= coluna)
        return;
    area[l][c].setCaractere(crtr);
}

Jardim::~Jardim() {
    if (!area) return;

    for (int i = 0; i < linha; ++i) {
        delete[] area[i];
    }
    delete[] area;
    area = nullptr;
}

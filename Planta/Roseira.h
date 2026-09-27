#ifndef TPPOO2_ROSEIRA_H
#define TPPOO2_ROSEIRA_H

#include "../Planta/Planta.h" // Verifica se o caminho está correto


class Jardim;

class Roseira : public Planta {
public:
    Roseira(Jardim* j, int linha, int coluna);

    std::string getInfoPlanta() const override;
    char getTipo() const override;

    void atualizar(Solo &solo) override;

private:
    Jardim* jardimRef;
    int pLinha;
    int pColuna;
};

#endif
#ifndef TPPOO2_REGADOR_H
#define TPPOO2_REGADOR_H

#include "Ferramentas.h"

class Regador : public Ferramenta {
public:
    /// CONSTRUTOR

    Regador();

    /// MÉTODOS VIRTUAIS
    bool funcionalidade_ferramenta(Solo* solo) override;
    char get_tipo_Ferramenta() const override;
    std::string getInfoFerramenta() const override;
    bool jaAcabou() const override;


private:
    int capacidade;
    int dose;
    bool acabou;
};

#endif

#ifndef TPPOO2_ADUBO_H
#define TPPOO2_ADUBO_H

#include "Ferramentas.h"
#include <string>

class Adubo : public Ferramenta {
public:
    /// CONSTRUTOR
    Adubo();

    /// MÉTODOS VIRTUAIS
    bool funcionalidade_ferramenta(Solo* solo) override;
    char get_tipo_Ferramenta() const override;
    std::string getInfoFerramenta() const override;

    ///GETTERS
    bool jaAcabou() const override;




private:
    int capacidade;
    int dose;
    bool acabou;
};

#endif // TPPOO2_ADUBO_H
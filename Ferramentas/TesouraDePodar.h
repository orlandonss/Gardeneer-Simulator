#ifndef TPPOO2_TESOURADEPODAR_H
#define TPPOO2_TESOURADEPODAR_H

#include "Ferramentas.h"

class TesouraDePodar : public Ferramenta {
public:
    TesouraDePodar();
    /// MÉTODOS VIRTUAIS
    bool funcionalidade_ferramenta(Solo* solo) override;
    char get_tipo_Ferramenta() const override;
    std::string getInfoFerramenta() const override;

};
#endif

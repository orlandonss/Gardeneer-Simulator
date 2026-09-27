#ifndef TPPOO2_FERRAMENTAS_H
#define TPPOO2_FERRAMENTAS_H

#include <string>
#include <sstream>
#include <iostream>

class Solo;
class Ferramenta {
public:
    // CONSTRUTOR
    Ferramenta();

    // FUNÇÔES VIRTUAIS
    virtual bool funcionalidade_ferramenta(Solo* solo) = 0;
    virtual char get_tipo_Ferramenta() const = 0;
    virtual std::string getInfoFerramenta() const = 0;
    virtual bool jaAcabou() const { return false; }

    // GETTERS
    int getId() const;

    // DESTRUTOR
    virtual ~Ferramenta();

private:
    static int prox_n_serie;
    int n_serie;
};

#endif //TPPOO2_FERRAMENTAS_H
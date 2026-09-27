#ifndef TPPOO2_JARDINEIRO_H
#define TPPOO2_JARDINEIRO_H

#include "../Ferramentas/Ferramentas.h"
#include <vector>

class Jardineiro {
public:
    Jardineiro();

    Jardineiro(const Jardineiro &origem);
    ///operaçoes
    bool adicionarFerramenta(Ferramenta *f);
    bool removeFerramenta(Ferramenta *f);
    bool retiraFerramenta_da_Mao();
    bool soltarFerramenta(Ferramenta *f);

    ///setters
    bool Entra(char linha, char coluna);
    void Sai();
    void setFerramenta_naMao(Ferramenta *f);

    ///getters
    int getNumFerramentas() const { return (int) ferramentas.size(); }
    char getLinha() const { return l; }
    char getColuna() const { return c; };
    Ferramenta *getFerramentaNaMao() const { return ferramenta_a_segurar; }
    bool getEstadoJardineiro() const { return esta_no_jardim; }
    const std::vector<Ferramenta*>& getInventario() const { return ferramentas; }
    Ferramenta* getFerramentaPorID(int id) const;

    ~Jardineiro();


private:
    std::vector<Ferramenta *> ferramentas;
    Ferramenta *ferramenta_a_segurar;
    bool esta_no_jardim;
    char l, c;
};

#endif

//
// Created by orlando on 10/29/25.
//

#ifndef TPPOO2_SOLO_H
#define TPPOO2_SOLO_H

#include "../Planta/Planta.h"
#include "../Ferramentas/Ferramentas.h"
#include "../Jardineiro/Jardineiro.h"


class Solo {
public:
    Solo();

    ///VERIFICACOES
    Planta *verificaPlanta(int l, int c) const;

    Ferramenta *verificaFerrameta(int l, int c) const;

    ///GETTERS
    std::string getInfo() const;

    int getAgua_solo() const { return agua; }
    int getNutrientes_solo() const { return nutrientes; }
    char getCaractere_solo() const noexcept { return caractere; }
    Ferramenta *getFerramenta() const { return ferramenta; }
    Ferramenta* retirarFerramenta();
    Planta *getPlanta() const { return planta; }
    Jardineiro* getJardineiro() const { return jardineiro; }


    ///SETTERS
    void setNutrientes(int novoNutriente);
    void setAgua(int novaAgua);
    void setFerramenta(Ferramenta *f);
    void setPlanta(Planta *);
    void setJardineiro(Jardineiro *j);
    void setCaractere(char Novoc) { caractere = Novoc; }
    void atualiza_solo();

    ~Solo();

private:
    int nutrientes;
    int agua;
    bool estaJardineiro;
    Jardineiro *jardineiro;
    Planta *planta;
    Ferramenta *ferramenta;
    char caractere;

};


#endif //TPPOO2_SOLO_H

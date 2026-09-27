//
// Created by orlando on 10/29/25.
//

#ifndef TPPOO2_MAPA_H
#define TPPOO2_MAPA_H

#include "../Solo/Solo.h"
#include "../Jardineiro/Jardineiro.h"
class Planta;

class Jardim {
public:

    Jardim(int l, int c);
    Jardim(const Jardim &origem);
    ///GETTERS
    int getLinha() const {return  linha;}
    int getColuna() const{return  coluna;}
    Solo **getArea() const {return  area;};
    bool getVizinhoLivreAleatorio(int lOrigem, int cOrigem, int& lDest, int& cDest);
    bool getVizinhoAleatorio(int lOrigem, int cOrigem, int& lDest, int& cDest);
    bool getCoordenadas(const Solo* soloAlvo, int &linha, int &coluna) const;
    //SETTERS
    void set_car(int l, int c, char crtr) const;
    void set_ptr_jardineiro(Jardineiro *j);
    void gerar_Grelha() const;
    void atualizaJardim();
    bool adicionarPlanta(int l, int c, Planta* p);
    bool substituirPlanta(int l, int c, Planta* p);

    //logica geral
    char gera_feramenta_random() const;
    void gera_ferramenta_posicao_aleatoria();
    Ferramenta *criaFerramentaPorTipo(char tipo);
    int contaVizinhosComPlanta(int l, int c) const;

    ~Jardim();

private:
    int linha, coluna;
    char car;
    Solo **area;
    Jardineiro *ptr_jardineiro;
};

#endif //TPPOO2_MAPA_H
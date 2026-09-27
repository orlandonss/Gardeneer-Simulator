#ifndef TPPOO2_SIMULADOR_H
#define TPPOO2_SIMULADOR_H

#include"../Mapa/Jardim.h"
#include <map>
#include <string>

///PARA COMANDOS DO JOGO
struct SaveState {
    Jardim* jardimCopia = nullptr;
    Jardineiro* jardineiroCopia = nullptr;
    int turnoCopia = 0;   // or contadorCopia
};

class Simulador {
public:
    Simulador();

    ~Simulador();

    void gerarGrelhaComTurno()const ;
    ///ACOES DE COMANDOS
    void ajuda();
    void criarJardim(const int &linhas, const int &colunas);
    void avancarTempo(int n = 1);
    void moverJardineiro(char direcao);
    void jardineiroEntra(const char &linha, const char &coluna);
    void jardineiroSai();
    void plantar(const char &linha, const char &coluna, const char &tipo);
    void colher(const char &linha, const char &coluna);
    void compraFerramenta(const char &c);
    void pegaFerramenta(int n);
    void largaferramenta();

    ///LISTAGEM DE COMANDOS
    void listarPlantas() const;
    void listarFerramentas() const;
    void listarArea() const;
    void listarSolo(char linha, char coluna, int raio = 0) const;
    void gravarEstado(const std::string &nome);
    void recuperarEstado(const std::string &nome);
    void apagarEstado(const std::string &nome);
    void listarPlanta(char linha, char coluna) const;
    void usarFerramenta(int id);

    ///AUXILIAR
    int letterToIndex(char letter, int size) const;
    char toLowerAscii(char ch) const;
    char toUpperAscii(char ch) const;
    char indexToUpper(int idx) const;
    char indexToLetter(int index) const;
    int maxInt(int a, int b) const;
    int minInt(int a, int b) const;
    void autoApanharFerramenta(Solo &solo_novo);

    ///SETTERTERS
    void resetarMovimentosTurno() { num_movimentos_restantes = 10;entradasNoTurno=0; }
    void resetaPlantacoes() { plantacoes_por_turno = 2; }
    void resetaRecolhas() { recolhas_por_turno = 5; }
    void termina() { ativo = false; }
    void reseta_controlo_Entrada_saida() {  saidasNoTurno=0; }
    void termina_jogo() { ativo = false; }


    ///GETTETS
    Jardim *getJardim() const { return jardim; }
    Jardineiro *getJardineiro() const { return jardineiro; }
    bool estaAtivo() const { return ativo; }



private:
    Jardim *jardim;
    Jardineiro *jardineiro;
    std::map<std::string, SaveState> saves;
    int turnos;
    int entradasNoTurno;
    int saidasNoTurno;
    int num_movimentos_restantes;
    int plantacoes_por_turno;
    int recolhas_por_turno;
    int acoes_plantar;
    int acoes_colher;
    bool ativo;
};

#endif //TPPOO2_SIMULADOR_H

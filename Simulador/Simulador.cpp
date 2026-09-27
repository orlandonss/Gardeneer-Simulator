#include "Simulador.h"
#include <iostream>
#include "../Planta/Cacto.h"
#include "../Planta/ErvaDaninha.h"
#include "../Planta/Maracuja.h"
#include "../Planta/Roseira.h"
#include "../Ferramentas/Drone.h"
#include "../Ferramentas/Adubo.h"
#include "../Ferramentas/Regador.h"
#include "../Ferramentas/TesouraDePodar.h"
#include "../Settings/Settings.h"
#include "../Solo/Solo.h"

///CONSTRUTOR  E DESTRUTOR
Simulador::Simulador()
    : turnos(0),
      num_movimentos_restantes(Settings::Jardineiro::max_movimentos),
      plantacoes_por_turno(Settings::Jardineiro::max_plantacoes),
      recolhas_por_turno(Settings::Jardineiro::max_colheitas),
      jardim(nullptr),
      ativo(true),
      jardineiro(nullptr),entradasNoTurno(0),saidasNoTurno(0),
      acoes_plantar(10),
      acoes_colher(5){
}

Simulador::~Simulador() {
    delete jardineiro;
    jardineiro = nullptr;
    delete jardim;
    jardim = nullptr;
};

///INICIO DA SIMULACAO E ACOES

void Simulador::criarJardim(const int &linhas, const int &colunas) {
    if (jardim) {
        throw::std::invalid_argument("Já existe um jardim criado. Não é possível criar outro.\n>");
    }

    if (linhas < 3 || colunas < 3 || linhas > 26 || colunas > 26) {
        throw::std::invalid_argument("Tamanho inválido (entre 3 e 26)\n>");
    }
    jardim = new Jardim(linhas, colunas);
    gerarGrelhaComTurno();
}

///SETTERS

void Simulador::avancarTempo(int n) {
    if (!jardim) {
        throw std::invalid_argument("O Jardim ainda não foi criado\n>");
    }
    if (n <= 0) {
        throw std::invalid_argument("Número de turnos a avançar não pode ser negativo!!\n>");
    }
    //objetivo: executar n vezes o comando atualiza
    for (int i = 0; i < n; i++) {
        turnos++;
        resetarMovimentosTurno();
        resetaPlantacoes();
        resetaRecolhas();

        if (turnos % 2 == 0) {
            reseta_controlo_Entrada_saida();
        }

        jardim->atualizaJardim();
    }
    std::cout << "Jardim atualizado\n";
    gerarGrelhaComTurno();
}

///AUXILIARES

int Simulador::letterToIndex(char letter, int size) const {
    letter = toUpperAscii(letter);
    if (letter < 'A' || letter >= ('A' + size)) return -1;
    return letter - 'A';
}

char Simulador::toLowerAscii(char ch) const {
    if (ch >= 'A' && ch <= 'Z') return ch + 32;
    return ch;
}

char Simulador::toUpperAscii(char ch) const {
    if (ch >= 'a' && ch <= 'z') return ch - 32;
    return ch;
}

char Simulador::indexToUpper(int idx) const {
    if (idx < 0 || idx > 25) return '?';
    return 'A' + idx;
}

char Simulador::indexToLetter(int index) const {
    if (index < 0 || index > 25) return '?';
    return 'A' + index;
}

int Simulador::maxInt(int a, int b) const {
    return (a > b) ? a : b;
}

int Simulador::minInt(int a, int b) const {
    return (a < b) ? a : b;
}

void Simulador::gerarGrelhaComTurno() const{
    if (!jardim) return;
    jardim->gerar_Grelha();
    std::cout << "Turno: " << turnos << "\n";
}

void Simulador::autoApanharFerramenta(Solo &solo_novo) {
    if (solo_novo.getFerramenta() != nullptr) {
        Ferramenta *ferramentaApanhada = solo_novo.retirarFerramenta();

        bool maosVazias = (jardineiro->getFerramentaNaMao() == nullptr);
        bool mochilaVazia = (jardineiro->getNumFerramentas() == 0);

        if (jardineiro->adicionarFerramenta(ferramentaApanhada)) {
            std::cout << "\nApanhaste uma ferramenta: "
                    << ferramentaApanhada->getInfoFerramenta()
                    << " (ID: " << ferramentaApanhada->getId() << ")\n";

            if (maosVazias && mochilaVazia) {
                jardineiro->setFerramenta_naMao(ferramentaApanhada);
                std::cout << "--> Ferramenta pronta a usar!\n";
            }

            std::cout << "--> Apareceu uma nova ferramenta no jardim\n";
            jardim->gera_ferramenta_posicao_aleatoria();
        } else {
            solo_novo.setFerramenta(ferramentaApanhada);
            std::cout << "--> Mochila cheia! A ferramenta ficou no chão.\n";
        }
    }
}


/// ACOES DO UTILIZADOR

void Simulador::moverJardineiro(char direcao) {
    if (!jardim) {
        throw::std::invalid_argument("O Jardim ainda não foi criado\n");
    }
    if (!jardineiro || !jardineiro->getEstadoJardineiro()) {
        throw::std::invalid_argument("O jardineiro nao se encontra no jardim!\n");
    }

    if (num_movimentos_restantes > 0) {
        int numLinhas = jardim->getLinha();
        int numColunas = jardim->getColuna();

        // posição atual (índices)
        int l_atual = letterToIndex(jardineiro->getLinha(), numLinhas);
        int c_atual = letterToIndex(jardineiro->getColuna(), numColunas);

        if (l_atual < 0 || c_atual < 0) {
            throw::std::invalid_argument("Posicao do Jardineiro inválida!!\n");
        }

        int l_novo = l_atual;
        int c_novo = c_atual;

        if (direcao == 'c') {
            l_novo = l_atual - 1;
        } else if (direcao == 'b') {
            l_novo = l_atual + 1;
        } else if (direcao == 'd') {
            c_novo = c_atual + 1;
        } else if (direcao == 'e') {
            c_novo = c_atual - 1;
        } else {
            std::cout << "Direção inválida.\n";
            return;
        }

        // verifica limites
        if (l_novo < 0 || l_novo >= numLinhas ||
            c_novo < 0 || c_novo >= numColunas) {
            throw::std::invalid_argument("Fora dos limites do jardim!!!\n");
        }


        Solo &solo_anterior = jardim->getArea()[l_atual][c_atual];
        Solo &solo_novo = jardim->getArea()[l_novo][c_novo];


        solo_anterior.setJardineiro(nullptr);

        char novocar ='.';
        if (!solo_anterior.getFerramenta() && !solo_anterior.getPlanta()) {
            jardim->set_car(l_atual, c_atual, '.');
        } else if (!solo_anterior.getFerramenta() && solo_anterior.getPlanta()) {
            novocar = solo_anterior.getPlanta()->getTipo();
            jardim->set_car(l_atual, c_atual, novocar);
        } else if (solo_anterior.getPlanta() && solo_anterior.getFerramenta()) {
            novocar = solo_anterior.getPlanta()->getTipo();
            jardim->set_car(l_atual, c_atual, novocar);
        } else if (!solo_anterior.getPlanta() && solo_anterior.getFerramenta()) {
            novocar = solo_anterior.getFerramenta()->get_tipo_Ferramenta();
            jardim->set_car(l_atual, c_atual, novocar);
        }

        char novaLinha = indexToLetter(l_novo);
        char novaColuna = indexToLetter(c_novo);
        jardineiro->Entra(novaLinha, novaColuna);

        autoApanharFerramenta(solo_novo);

        solo_novo.setJardineiro(jardineiro);

        jardim->set_car(l_novo, c_novo, '*');

        jardim->set_ptr_jardineiro(jardineiro);
        gerarGrelhaComTurno();
        num_movimentos_restantes--;
    } else {
        std::cout << "Atingiu o número máximo de movimentos, avance 1 instante!!\n";
        gerarGrelhaComTurno();
    }
}


///COMANDO AJUDA

void Simulador::ajuda() {
    std::cout << "\n------------------Lista de Comandos Disponíveis --------------\n\n";

    std::cout << "GERAIS:\n";
    std::cout << "  jardim <n> <m>         - Cria um jardim com <n> linhas e <m> colunas.\n";
    std::cout << "  avanca [n]             - Avança o tempo em n unidades (1 por defeito).\n";
    std::cout << "  fim                    - Termina o simulador.\n\n";

    std::cout << "JARDINEIRO:\n";
    std::cout << "  entra <l> <c>           - Coloca o jardineiro na posição <l><c>.\n";
    std::cout << "  sair                     - Jardineiro sai do jardim\n";
    std::cout << "  move <c|b|e|d>         - Move o jardineiro: cima, baixo, esquerda, direita.\n";
    std::cout << "  lferr                  - Lista as ferramentas que o jardineiro transporta.\n";
    std::cout << "  usa <id>               - Usa a ferramenta com o ID indicado.\n";
    std::cout << "  planta <l> <c> <tipo>   - Planta um tipo de planta na posição indicada.\n";
    std::cout << "  colhe <l> <c>           - Colhe a planta na posição indicada.\n\n";

    std::cout << "SOLO E PLANTAS:\n";
    std::cout << "  lsolo <l> <c> [n]       - Lista as propriedades do solo em <l><c> (ou num raio n).\n";
    std::cout << "  lplanta <l> <c>         - Mostra os detalhes da planta na posição indicada.\n";
    std::cout << "  lplantas               - Lista todas as plantas no jardim.\n";
    std::cout << "  larea                  - Lista todas as posições do solo que não estejam vazias.\n\n";

    std::cout << "ESTADO E GUARDAR:\n";
    std::cout << "  grava <nome>          - Guarda o estado atual da simulação.\n";
    std::cout << "  recupera <nome>       - Restaura um estado previamente guardado.\n";
    std::cout << "  apaga <nome>          - Apaga um estado guardado.\n";

    std::cout << "\n----------------------------------------------------------------------\n\n";
}

void Simulador::jardineiroEntra(const char &linha, const char &coluna) {
    if (!jardim) {
        throw std::invalid_argument("O Jardim ainda nao foi criado\n>");
    }

    if (entradasNoTurno >= num_movimentos_restantes) {
        throw std::invalid_argument("ja gastaste todos os movimentos neste turno, avanca 1!\n>");
    }

    int numLinhas  = jardim->getLinha();
    int numColunas = jardim->getColuna();

    int l = letterToIndex(linha, numLinhas);
    int c = letterToIndex(coluna, numColunas);

    if (l == -1 || c == -1) {
        throw std::invalid_argument("Posicao Invalida!!\n>");
    }


    if (!jardineiro) {
        jardineiro = new Jardineiro;

        jardineiro->Entra(linha, coluna);

        Solo &solo_novo = jardim->getArea()[l][c];
        solo_novo.setJardineiro(jardineiro);

        autoApanharFerramenta(solo_novo);

        jardim->set_car(l, c, '*');
        jardim->set_ptr_jardineiro(jardineiro);
        gerarGrelhaComTurno();

        entradasNoTurno++;
        return;
    }

    if (!jardineiro->getEstadoJardineiro()) {
        jardineiro->Entra(linha, coluna);

        Solo &solo_novo = jardim->getArea()[l][c];
        solo_novo.setJardineiro(jardineiro);

        autoApanharFerramenta(solo_novo);

        jardim->set_car(l, c, '*');
        jardim->set_ptr_jardineiro(jardineiro);
        gerarGrelhaComTurno();

        entradasNoTurno++;
        num_movimentos_restantes--;
        return;
    }

    int linha_anterior  = letterToIndex(jardineiro->getLinha(),  numLinhas);
    int coluna_anterior = letterToIndex(jardineiro->getColuna(), numColunas);

    if (linha_anterior < 0 || linha_anterior >= numLinhas ||
        coluna_anterior < 0 || coluna_anterior >= numColunas) {
        std::cout << "Estado interno invalido ao teleportar!\n>";
        return;
    }

    if (linha_anterior == l && coluna_anterior == c) {
        throw std::invalid_argument("O jardineiro ja esta nesta posicao!\n>");
    }

    Solo &solo_anterior = jardim->getArea()[linha_anterior][coluna_anterior];
    Solo &solo_novo     = jardim->getArea()[l][c];


    jardineiro->Entra(linha, coluna);

    solo_anterior.setJardineiro(nullptr);
    char novocar='.';

    if (solo_anterior.getPlanta() != nullptr) {
        novocar = solo_anterior.getPlanta()->getTipo();
    } else if (solo_anterior.getFerramenta() != nullptr) {
        novocar = solo_anterior.getFerramenta()->get_tipo_Ferramenta();
    }


    jardim->set_car(linha_anterior, coluna_anterior, novocar);

    solo_novo.setJardineiro(jardineiro);

    autoApanharFerramenta(solo_novo);

    jardim->set_car(l, c, '*');
    jardim->set_ptr_jardineiro(jardineiro);
    gerarGrelhaComTurno();

    entradasNoTurno++;
}


void Simulador::jardineiroSai() {
    if (!jardim) {
        throw std::invalid_argument("O Jardim ainda não foi criado\n>");
    }
    if (!jardineiro || !jardineiro->getEstadoJardineiro()) {
        throw std::invalid_argument("O jardineiro nao se encontra no jardim!\n>");
    }

    // max outs per turn considered 1
    if (saidasNoTurno >= Settings::Jardineiro::max_entradas_saidas ) {
        throw std::invalid_argument("So podes sair uma vez a cada 2 turnos!\n>");
    }

    int numLinhas = jardim->getLinha();
    int numColunas = jardim->getColuna();

    int linha_atual  = letterToIndex(jardineiro->getLinha(),  numLinhas);
    int coluna_atual = letterToIndex(jardineiro->getColuna(), numColunas);


    Solo &s = jardim->getArea()[linha_atual][coluna_atual];

    s.setJardineiro(nullptr);

    char novocar = '.';

    if (!s.getFerramenta() && s.getPlanta()) {
        novocar = s.getPlanta()->getTipo();
        jardim->set_car(linha_atual, coluna_atual, novocar);
    }else if (s.getPlanta() && s.getFerramenta()) {
        novocar = s.getPlanta()->getTipo();
        jardim->set_car(linha_atual, coluna_atual, novocar);
    } else if (!s.getPlanta() && s.getFerramenta()) {
        novocar = s.getFerramenta()->get_tipo_Ferramenta();
        jardim->set_car(linha_atual, coluna_atual, novocar);
    }

    jardim->set_car(linha_atual, coluna_atual, novocar);

    saidasNoTurno++;
    jardineiro->Sai();

    gerarGrelhaComTurno();
}


void Simulador::pegaFerramenta(int n) {
    if (!jardim) {
        throw std::invalid_argument("O Jardim ainda não foi criado\n");
    }
    if (!jardineiro || !jardineiro->getEstadoJardineiro()) {
        throw std::invalid_argument("O jardineiro nao se encontra no jardim!\n>");
    }
    if (jardineiro->getNumFerramentas() == 0) {
        std::cout << "A mochila esta vazia! Nao tens ferramentas para pegar.\n>";
        return;
    }

    Ferramenta *f = jardineiro->getFerramentaPorID(n);

    if (f == nullptr) {
        std::cout << "Nao tens nenhuma ferramenta com o ID " << n << " na mochila.\n";
        return;
    }
    jardineiro->setFerramenta_naMao(f);

    std::cout << "O jardineiro pegou na ferramenta: "
            << f->getInfoFerramenta() << " (ID: " << n << ")\n";

    gerarGrelhaComTurno();
}

void Simulador::largaferramenta() {
    if (!jardim) {
        throw std::invalid_argument("O Jardim ainda não foi criado\n>");
    }
    if (!jardineiro || !jardineiro->getEstadoJardineiro()) {
        throw std::invalid_argument("O jardineiro nao se encontra no jardim!\n>");
    }
    Ferramenta *f = jardineiro->getFerramentaNaMao();

    if (f == nullptr) {
        std::cout << "O jardineiro nao tem nada na mao para largar.\n>";
        return;
    }
    int numLinhas = jardim->getLinha();
    int l = letterToIndex(jardineiro->getLinha(), numLinhas);
    int c = letterToIndex(jardineiro->getColuna(), jardim->getColuna());

    Solo &soloAtual = jardim->getArea()[l][c];

    if (soloAtual.getFerramenta() != nullptr) {
        std::cout << "Este solo ja tem uma ferramenta ("
                << soloAtual.getFerramenta()->getInfoFerramenta()
                << "). Nao podes largar outra aqui.\n";
        return;
    }

    soloAtual.setFerramenta(f);
    jardineiro->soltarFerramenta(f);
    jardim->set_car(l, c, f->get_tipo_Ferramenta());
    gerarGrelhaComTurno();

    std::cout << "Largaste " << f->getInfoFerramenta() << " no chao.\n";
    gerarGrelhaComTurno();
}


void Simulador::plantar(const char &linha, const char &coluna, const char &tipo) {
    if (!jardim) throw std::invalid_argument("O Jardim ainda não foi criado\n>");

    if (!jardineiro) throw std::invalid_argument("O jardineiro não esta no jardim\n>");

    if (plantacoes_por_turno == 0) {
        throw std::invalid_argument("O Jardineiro esgotou as plantaçoes por turno\n Avance um instante..\n>");
    }
    int numLinhas = jardim->getLinha();
    int numColunas = jardim->getColuna();

    int l_alvo = letterToIndex(linha, numLinhas);
    int c_alvo = letterToIndex(coluna, numColunas);

    int l_atual = letterToIndex(jardineiro->getLinha(), numLinhas);
    int c_atual = letterToIndex(jardineiro->getColuna(), numColunas);

    if (l_alvo < 0 || l_alvo >= numLinhas || c_alvo < 0 || c_alvo >= numColunas) {
        throw std::invalid_argument("Posicao inválida para plantar!!\n>");
    }

    Solo &s = jardim->getArea()[l_alvo][c_alvo];

    if (s.getPlanta() != nullptr) {
        throw std::invalid_argument("Já existe uma planta nessa posição!\n>");
    }
    //validar se está na posição para plantar
    if (l_alvo != l_atual || c_alvo != c_atual) {
        throw std::invalid_argument("O jardineiro não se encontra nessa posição!\n>");
    }

    Planta *novaPlanta = nullptr;

    switch (tipo) {
        case 'c': novaPlanta = new Cacto();
            break;
        case 'r': novaPlanta = new Roseira(jardim, l_alvo, c_alvo);
            break;
        case 'e': novaPlanta = new ErvaDaninha(jardim, l_alvo, c_alvo);
            break;
        case 'x': novaPlanta = new Maracuja(jardim, l_alvo, c_alvo);
            break;
        default:
            throw std::invalid_argument("Tipo de planta desconhecido (use c, r, e, x).\n>");
    }

    s.setPlanta(novaPlanta);
    jardim->set_car(linha, coluna, tipo);
    plantacoes_por_turno--;
    gerarGrelhaComTurno();
}


void Simulador::colher(const char &linha, const char &coluna) {
    if (!jardim) {
        throw std::invalid_argument("O Jardim ainda não foi criado\n>");
    }

    if (recolhas_por_turno <= 0) {
        std::cout << "Ja nao podes colher mais plantas neste turno! (Max: 5)\n";
        std::cout << "Tens de avançar o tempo para recuperar energias.\n";
        return;
    }


    int numLinhas = jardim->getLinha();
    int numColunas = jardim->getColuna();

    int l = letterToIndex(linha, numLinhas);
    int c = letterToIndex(coluna, numColunas);

    if (l == -1 || c == -1) {
        throw std::invalid_argument("Posicao fora dos limites do jardim.\n>");
    }

    Solo &s = jardim->getArea()[l][c];

    // 5. Verificar se existe planta para colher
    if (s.getPlanta() == nullptr) {
        std::cout << "Nao ha nenhuma planta na posicao "
                << toUpperAscii(linha) << toUpperAscii(coluna) << " para colher.\n";
        return;
    }
    std::string nomePlanta = s.getPlanta()->getInfoPlanta();

    delete s.getPlanta();
    s.setPlanta(nullptr);

    if (s.getJardineiro() != nullptr) {
        s.setCaractere('*');
    } else if (s.getFerramenta() != nullptr) {
        s.setCaractere(s.getFerramenta()->get_tipo_Ferramenta());
    } else {
        s.setCaractere('.');
    }

    recolhas_por_turno--;

    std::cout << "Planta colhida com sucesso! (Restam " << recolhas_por_turno << " colheitas neste turno).\n";

    gerarGrelhaComTurno();
}

void Simulador::compraFerramenta(const char &c) {
    if (!jardim) {
        throw std::invalid_argument("O Jardim ainda não foi criado\n>");
    }
    if (!jardineiro) {
        throw std::invalid_argument("O jardineiro não esta no jardim\n>");
    }

    const char tipo = toLowerAscii(c);

    Ferramenta *nova = nullptr;

    switch (tipo) {
        case 'g': nova = new Regador();
            break;
        case 'a': nova = new Adubo();
            break;
        case 't': nova = new TesouraDePodar();
            break;
        case 'z': nova = new Drone(jardim);
            break;
        default:
            std::cout << "ferramenta não existe!!!\n";
            return;
    }

    bool maosVazias = (jardineiro->getFerramentaNaMao() == nullptr);
    bool mochilaVazia = (jardineiro->getNumFerramentas() == 0);

    if (jardineiro->adicionarFerramenta(nova)) {
        std::cout << "Ferramenta comprada com sucesso.\n";

        if (maosVazias && mochilaVazia) {
            jardineiro->setFerramenta_naMao(nova);
            std::cout << "--> Como a mochila estava vazia, a ferramenta ficou pronta na mao!\n";
        }
    } else {
        std::cout << "Nao foi possivel comprar: A mochila esta cheia!\n";
        delete nova;
        return;
    }

    gerarGrelhaComTurno();
}

void Simulador::usarFerramenta(int id) {
    if (!jardim) {
        throw std::invalid_argument("O Jardim ainda nao foi criado\n>");
    }
    if (!jardineiro || !jardineiro->getEstadoJardineiro()) {
        throw std::invalid_argument("O jardineiro nao se encontra no jardim!\n>");
    }

    Ferramenta *f = jardineiro->getFerramentaPorID(id);

    if (f == nullptr) {
        std::cout << "Nao tens nenhuma ferramenta com o ID " << id << ".\n";
        return;
    }

    if (f != jardineiro->getFerramentaNaMao()) {
        std::cout << "Tens de ter a ferramenta na mao para a usar! (Usa: pega " << id << ")\n";
        return;
    }

    int numLinhas = jardim->getLinha();
    int numColunas = jardim->getColuna();

    int l = letterToIndex(jardineiro->getLinha(), numLinhas);
    int c = letterToIndex(jardineiro->getColuna(), numColunas);

    Solo &soloAtual = jardim->getArea()[l][c];

    std::cout << "A usar " << f->getInfoFerramenta() << "...\n";
    bool sucesso = f->funcionalidade_ferramenta(&soloAtual);

    if (sucesso) {
        if (f->jaAcabou()) {
            if (jardineiro->getFerramentaNaMao() == f) {
                jardineiro->setFerramenta_naMao(nullptr);
            }
            jardineiro->removeFerramenta(f);
        }
    }
    gerarGrelhaComTurno();

}

///LISTAGEM COMANDOS PARA EFEITOS DE CONSULTA
void Simulador::listarPlantas() const {
    if (!jardim) {
        throw std::invalid_argument("O Jardim ainda não foi criado\n>");
    }

    int numLinhas = jardim->getLinha();
    int numColunas = jardim->getColuna();
    bool encontrouAlguma = false;

    std::cout << "\n-----------PLANTAS JARDIM-----------\n";

    for (int l = 0; l < numLinhas; ++l) {
        for (int c = 0; c < numColunas; ++c) {
            Solo &soloAtual = jardim->getArea()[l][c];
            Planta *p = soloAtual.getPlanta();

            if (p != nullptr) {
                encontrouAlguma = true;

                char coordL = indexToUpper(l);
                char coordC = indexToUpper(c);

                std::cout << "------------------------------------------\n";
                std::cout << "POSICAO: [" << coordL << coordC << "]\n";

                std::cout << p->getInfoPlanta();
                std::cout << "----------------INFO DO SOLO----------------\n";
                std::cout << "Solo: " << soloAtual.getNutrientes_solo() << " nutr. | "
                        << soloAtual.getAgua_solo() << " agua\n";
            }
        }
    }

    if (!encontrouAlguma) {
        std::cout << "O jardim não tem plantas neste momento.\n";
        std::cout << ">";
    }
    gerarGrelhaComTurno();
}

void Simulador::listarPlanta(char linha, char coluna) const {
    if (!jardim) {
        throw std::invalid_argument("O Jardim ainda nao foi criado.\n>");
    }

    int numLinhas = jardim->getLinha();
    int numColunas = jardim->getColuna();

    int l = letterToIndex(linha, numLinhas);
    int c = letterToIndex(coluna, numColunas);

    if (l == -1 || c == -1) {
        throw std::invalid_argument("Posicao fora dos limites do jardim.\n>");
    }

    Solo &soloAlvo = jardim->getArea()[l][c];
    Planta *p = soloAlvo.getPlanta();

    char L = toUpperAscii(linha);
    char C = toUpperAscii(coluna);

    if (p != nullptr) {
        std::cout << ">>> Detalhes da Planta em [" << L << C << "] <<<\n";
        std::cout << p->getInfoPlanta() << "\n";
        std::cout << "Solo: " << soloAlvo.getNutrientes_solo() << " nutr. | "
                << soloAlvo.getAgua_solo() << " agua\n";
    } else {
        std::cout << "Nao existe nenhuma planta na posicao [" << L << C << "].\n";
    }
    gerarGrelhaComTurno();
}

void Simulador::listarFerramentas() const {
    if (!jardim) {
        throw std::invalid_argument("O Jardim ainda nao foi criado\n>");
    }

    if (!jardineiro || !jardineiro->getEstadoJardineiro()) {
        throw std::invalid_argument("O jardineiro nao esta no jardim\n>");
    }
    const std::vector<Ferramenta *> &mochila = jardineiro->getInventario();

    std::cout << "\n=== MOCHILA DO JARDINEIRO ===\n";

    if (mochila.empty()) {
        std::cout << " (Vazia)\n";
    } else {
        for (const Ferramenta *f: mochila) {
            if (f != nullptr) {
                std::cout << " > ID: " << f->getId()
                        << " | " << f->getInfoFerramenta();

                if (f == jardineiro->getFerramentaNaMao()) {
                    std::cout << " [EM USO / NA MAO]";
                }
                std::cout << "\n";
            }
        }
    }
    std::cout << "=============================\n";
    gerarGrelhaComTurno();
}

void Simulador::listarArea() const {
    if (!jardim) {
        throw std::invalid_argument("O Jardim ainda não foi criado\n>");
    }

    int numLinhas = jardim->getLinha();
    int numColunas = jardim->getColuna();
    bool encontrouAlgoNoJardim = false;

    std::cout << "\n---------CONTEÚDO DA ÁREA (NÃO VAZIA)----------\n";

    for (int l = 0; l < numLinhas; ++l) {
        for (int c = 0; c < numColunas; ++c) {
            Solo &solo = jardim->getArea()[l][c];

            bool temPlanta = (solo.getPlanta() != nullptr);
            bool temFerramenta = (solo.getFerramenta() != nullptr);

            bool temJardineiro = (solo.getJardineiro() != nullptr);

            if (temPlanta || temFerramenta || temJardineiro) {
                encontrouAlgoNoJardim = true;

                char coordL = indexToLetter(l);
                char coordC = indexToLetter(c);

                std::cout << "Posição: [" << coordL << "," << coordC << "]\n";

                std::cout << "Solo: " << solo.getNutrientes_solo() << " nutr. | "
                        << solo.getAgua_solo() << " agua\n";

                std::cout << "Ocupação:\n";

                if (temJardineiro) {
                    std::cout << "O jardineiro está aqui.\n";
                }

                if (temPlanta) {
                    std::cout << "Planta:" << solo.getPlanta()->getInfoPlanta() << "\n";
                }

                if (temFerramenta) {
                    std::cout << "Ferramenta: "
                            << solo.getFerramenta()->get_tipo_Ferramenta() << "\n";
                }
            }
        }
    }

    if (!encontrouAlgoNoJardim) {
        std::cout << "O jardim está completamente vazio (apenas solo).\n";
    }
    gerarGrelhaComTurno();
}

void Simulador::listarSolo(char lChar, char cChar, int raio) const {
    if (!jardim) {
        throw std::invalid_argument("O Jardim ainda não foi criado.\n>");
    }

    if (raio < 0) {
        throw std::invalid_argument("O raio não pode ser negativo.\n>");
    }

    int numLinhas = jardim->getLinha();
    int numColunas = jardim->getColuna();

    int lCentro = -1, cCentro = -1;

    lCentro = letterToIndex(lChar, numLinhas);
    cCentro = letterToIndex(cChar, numColunas);

    char L_upper = toUpperAscii(lChar);
    char C_upper = toUpperAscii(cChar);


    if (lCentro == -1 || cCentro == -1) {
        throw std::invalid_argument("Posição central inválida ou fora do jardim.\n>");
    }

    std::cout << "\n-- DETALHES DO SOLO (Centro: " << L_upper << C_upper
            << " | Raio: " << raio << ") --\n";

    int lInicio = maxInt(0, lCentro - raio);
    int cInicio = maxInt(0, cCentro - raio);

    int lFim = minInt(numLinhas - 1, lCentro + raio);
    int cFim = minInt(numColunas - 1, cCentro + raio);


    bool encontrouAlgo = false;

    for (int i = lInicio; i <= lFim; i++) {
        for (int j = cInicio; j <= cFim; j++) {
            Solo &solo = jardim->getArea()[i][j];

            char posL = indexToLetter(i);
            char posC = indexToLetter(j);

            std::cout << "------------------------------------------\n";
            std::cout << "POSIÇÃO: [" << posL << "," << posC << "]";

            if (i == lCentro && j == cCentro) std::cout << " <--- CENTRO";
            std::cout << "\n";

            std::cout << "  > Solo: " << solo.getNutrientes_solo() << " nutrientes | "
                    << solo.getAgua_solo() << " agua\n";

            bool estaVazio = true;

            if (solo.getJardineiro() != nullptr) {
                std::cout << "  > Ocupante: JARDINEIRO (*)\n";
                estaVazio = false;
            }

            if (solo.getPlanta() != nullptr) {
                std::cout << "  > Planta: " << solo.getPlanta()->getInfoPlanta()<<"\n";
                estaVazio = false;
            }
            if (solo.getFerramenta()!= nullptr) {
                std::cout << "  > Ferramenta: " << solo.getFerramenta()->get_tipo_Ferramenta()<<"\n";
            }
            if (estaVazio) {
                std::cout << "  (Sem ocupação)\n";
            }
            encontrouAlgo = true;
        }
    }

    if (!encontrouAlgo) {
        std::cout << "  (Área fora dos limites ou vazia)\n";
    }
    std::cout << "---------------------------------------------\n";
    gerarGrelhaComTurno();
}


///COMANDOS PARA GRAVAR ESTADO DA EMULACAO
void Simulador::gravarEstado(const std::string& nome) {

    std::map<std::string, SaveState>::iterator it= saves.find(nome);
    if (it != saves.end()) {
        delete it->second.jardimCopia;
        delete it->second.jardineiroCopia;
        saves.erase(it);
    }

    SaveState st;

    st.jardineiroCopia = (jardineiro ? new Jardineiro(*jardineiro) : nullptr);
    st.jardimCopia     = (jardim ? new Jardim(*jardim) : nullptr);


    if (st.jardimCopia) {
        st.jardimCopia->set_ptr_jardineiro(st.jardineiroCopia);
    }

    st.turnoCopia = turnos;

    saves[nome] = st;

    std::cout << "Estado '" << nome << "' gravado com sucesso.\n";
    gerarGrelhaComTurno();
}

void Simulador::recuperarEstado(const std::string &nome) {
    std::map<std::string, SaveState>::iterator it = saves.find(nome);
    if (it == saves.end()) {
        throw std::invalid_argument("Save nao encontrado.\n");
    }

    delete jardim;
    delete jardineiro;

    jardim = it->second.jardimCopia;
    jardineiro = it->second.jardineiroCopia;

    turnos = it->second.turnoCopia;

    if (jardim) {
        jardim->set_ptr_jardineiro(jardineiro);
    }

    it->second.jardimCopia = nullptr;
    it->second.jardineiroCopia = nullptr;

    saves.erase(it);

    std::cout << "Estado '" << nome << "' recuperado com sucesso.\n";
    gerarGrelhaComTurno();
}

void Simulador::apagarEstado(const std::string &nome) {
    std::map<std::string, SaveState>::iterator it = saves.find(nome);
    if (it == saves.end()) {
        throw std::invalid_argument("Save nao encontrado.\n");
    }

    delete it->second.jardimCopia;
    delete it->second.jardineiroCopia;

    saves.erase(it);

    std::cout << "Save '" << nome << "' apagado da memoria.\n";
    gerarGrelhaComTurno();
}

#include "Listar_Area.h"
#include <sstream>

Listar_Area::Listar_Area(const std::string &frase, Simulador &simulacao) : Comandos(frase, simulacao) {
}

void Listar_Area::executa() {
    try{
        std::istringstream iss(getFrase());
        char cmd;
        iss >> cmd;

        Simulador &sim =obtemSimulacao();
        sim.listarArea();
    }catch (const std::exception& e) {
        std::cerr << e.what();
    }


}

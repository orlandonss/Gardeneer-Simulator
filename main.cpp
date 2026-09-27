#include <iostream>
#include <sstream>
#include "Simulador/Simulador.h"
#include  "InterfaceUtilizador/InterfaceUtilizador.h"

int main(){
    Simulador simulacao;
    InterfaceUtilizador interfaceUtilizador(simulacao);
    interfaceUtilizador.executa();
    return 0;
}

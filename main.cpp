#include <iostream>
#include <string>

#include "../cabecalhos/voo.h"
#include "../cabecalhos/astronauta.h"
#include "../cabecalhos/configuracoes.h"
#include "../cabecalhos/sistema.h"
#include "../cabecalhos/menus.h"

int main(int argc, char *argv[]) {
    int escolha1 = -1, escolha2 = -1;
    int qtdAstronautas = 0, qtdVoos = 0;

    Astronauta *listaAstronautas = new Astronauta[0];
    Voo *listaVoos = new Voo[0];

    while (escolha1 != 0) {
        escolha1 = mostrarMenu();

        switch (escolha1) {
            case 0:
                break;
            case 1:
                listaVoos = cadastrarVoo(listaVoos, &qtdVoos); 
                break;
            case 2:
                listaAstronautas = cadastrarAstronauta(listaAstronautas, &qtdAstronautas);
                break;
            case 3:
                listarVoos(listaVoos, qtdVoos);
                break;
            case 4:
                adicionarAstronautaNoVoo(listaVoos, listaAstronautas, &qtdVoos, &qtdAstronautas);
                break;
            case 5:
                removerAstronautaDoVoo(listaVoos, listaAstronautas, &qtdVoos, &qtdAstronautas);
                break;
            case 6:
                lancarVoo(listaVoos, qtdVoos, qtdAstronautas);
                break;
            case 7:
                explodirVoo(listaAstronautas, listaVoos, qtdVoos, qtdAstronautas);
                break;
            case 8:
                finalizarVoo(listaAstronautas, listaVoos, qtdVoos, qtdAstronautas);
                break;
            case 9:
                listarAstronautasMortos(listaAstronautas, qtdAstronautas);
                break;
            default:
                mostrarOpcaoInvalida();
                break;
        }

    }

    return 0;
}
#include <iostream>

#include "../cabecalhos/menus.h"
#include "../cabecalhos/sistema.h"

int mostrarMenu() {
    int opcao;
    std::string funcionalidades[10] = {
        "Encerrar programa",
        "Cadastrar um voo",
        "Cadastrar um astronauta",
        "Listar voos",
        "Adicionar Astronauta em um Voo",
        "Remover Astronauta de um Voo",
        "Lancar um Voo",
        "Explodir um Voo",
        "Finalizar um Voo",
        "Mostrar astronautas mortos",
    };

    limparTerminal();

    for (int i = 0; i < 10; i++) {
        std::cout << i << " - " << funcionalidades[i] << "\n";
    }

    std::cin >> opcao;

    return opcao;
}

void mostrarOperacaoInvalida(std::string error) {
    limparTerminal();

    std::cout << "Operacao invalida: " << error << "!\n" << std::endl;

    pausarTerminal();
}

void mostrarOpcaoInvalida() {
    limparTerminal();

    std::cout << "Opcao invalida!\n" << std::endl;

    pausarTerminal();
};
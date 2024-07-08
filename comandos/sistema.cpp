#include <stdlib.h> 

#include "../cabecalhos/sistema.h"

void limparTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausarTerminal() {
    #ifdef _WIN32
        system("pause");
    #else
        system("read -p \"Aperte ENTER para voltar ao Menu principal.\" saindo");
        limparTerminal();
    #endif
}
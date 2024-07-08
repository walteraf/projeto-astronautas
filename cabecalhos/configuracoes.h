#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "voo.h"
#include "astronauta.h"


Voo* cadastrarVoo(Voo *listaVoos, int *qtdVoos);


Astronauta* cadastrarAstronauta(Astronauta *listaAstronautas, int *qtd_astronautas);


void listarVoos(Voo *listaVoos, int qtdVoos);


void adicionarAstronautaNoVoo(Voo *listaVoos, Astronauta *listaAstronautas, int *qtdVoos, int *qtd_astronautas);


void removerAstronautaDoVoo(Voo *listaVoos, Astronauta *listaAstronautas, int *qtdVoos, int *qtd_astronautas);


void lancarVoo(Voo *listaVoos, int qtdVoos, int qtd_astronautas);


void explodirVoo(Astronauta *listaAstronautas, Voo *listaVoos, int qtdVoos, int qtd_astronautas);


void finalizarVoo(Astronauta *listaAstronautas, Voo *listaVoos, int qtdVoos, int qtd_astronautas);


void listarAstronautasMortos(Astronauta *listaAstronautas, int qtd_astronautas);


int selecionarVoo(Voo *listaVoos, int qtdVoos);
std::string selecionarAstronauta(Astronauta *listaAstronautas, int qtd_astronautas);

int findVoo(int codigo, Voo *listaVoos, int qtdVoos);
int findAstronauta(std::string cpf, Astronauta *listaAstronautas, int qtd_astronautas);
int findAstronautaNoVoo(Voo voo, std::string cpf);


#endif
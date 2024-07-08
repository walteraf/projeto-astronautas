#include <iostream>

#include "../cabecalhos/configuracoes.h"
#include "../cabecalhos/menus.h"
#include "../cabecalhos/sistema.h"

Voo *cadastrarVoo(Voo *listaVoos, int *qtdVoos) {
    int codigo;

    limparTerminal();

    std::cout << "Codigo do Voo: ";
    std::cin >> codigo;

    if (findVoo(codigo, listaVoos, *qtdVoos) != -1) {
        mostrarOperacaoInvalida("voo ja cadastrado");
        return listaVoos;
    }

    Voo *new_listaVoos = new Voo[*qtdVoos + 1];

    for (int i = 0; i < *qtdVoos; i++) {
        new_listaVoos[i] = listaVoos[i];
    }

    new_listaVoos[*qtdVoos] = Voo(codigo);

    delete[] listaVoos;

    (*qtdVoos)++;

    limparTerminal();

    std::cout << "Voo cadastrado com sucesso!" << "\n" << std::endl;

    pausarTerminal(); 

    return new_listaVoos;
}

Astronauta *cadastrarAstronauta(Astronauta *listaAstronautas, int *qtdAstronautas) {
    std::string cpf;
    std::string nome;
    int idade;
    
    limparTerminal();

    std::cout << "CPF: ";
    std::cin >> cpf;

    if (findAstronauta(cpf, listaAstronautas, *qtdAstronautas) != -1) {
        mostrarOperacaoInvalida("cpf ja cadastrado");
        return listaAstronautas;
    }

    std::cout << "Nome: ";
    std::cin >> nome;
    std::cout << "Idade: ";
    std::cin >> idade;

    Astronauta *new_listaAstronautas = new Astronauta[*qtdAstronautas + 1];

    for (int i = 0; i < *qtdAstronautas; i++) {
        new_listaAstronautas[i] = listaAstronautas[i];
    }
    
    new_listaAstronautas[*qtdAstronautas] = Astronauta(cpf, nome, idade);

    delete[] listaAstronautas;

    (*qtdAstronautas)++;

    limparTerminal();

    std::cout << "Astronauta cadastrado com sucesso!" << "\n" << std::endl;

    pausarTerminal(); 

    return new_listaAstronautas;
}

void listarVoos(Voo *listaVoos, int qtdVoos) {
    int qtd_passageiros;
    std::string status;

    limparTerminal();

    std::cout << "Lista de voos\n\n";

    for (int i = 0; i < qtdVoos; i++) {
        qtd_passageiros = listaVoos[i].getQtdPassageiros();

        switch (listaVoos[i].getStatus()) {
            case 0:
                status = "Voo em Planejamento";
                break;
            case 1:
                status = "Voo em Curso";
                break;
            case 2:
                status = "Voo Finalisado";
                break;
            case 3:
                status = "Voo Explodido";
        }
        

        std::cout << i + 1 << " - Codigo: " << listaVoos[i].getCodigo() << "; Passageiros: " << qtd_passageiros << " [" << status << "]" << "\n";
        for (int j = 0; j < qtd_passageiros; j++) {
            std::cout << "    " << "- Astronauta: " << j + 1 << ": " << listaVoos[i].getPassageiros()[j].getNome() << " CPF: " << listaVoos[i].getPassageiros()[j].getCpf() << "\n";
        }
    }

    pausarTerminal();
}

void adicionarAstronautaNoVoo(Voo *listaVoos, Astronauta *listaAstronautas, int *qtdVoos, int *qtdAstronautas) {
    int opcao_voo, index_astronauta;
    std::string cpf_astronauta;

    limparTerminal();

    if (*qtdVoos == 0 || *qtdAstronautas == 0) {
        mostrarOperacaoInvalida("Quantidade insuficiente astronautas/voos");
        return;
    }

    opcao_voo = selecionarVoo(listaVoos, *qtdVoos);
    if (opcao_voo == 0) return;
    opcao_voo--;

    if (listaVoos[opcao_voo].getStatus() != 0) {
        mostrarOperacaoInvalida("O voo não esta em planejamento");
        return;
    }

    cpf_astronauta = selecionarAstronauta(listaAstronautas, *qtdAstronautas);

    if (findAstronautaNoVoo(listaVoos[opcao_voo], cpf_astronauta) != -1) {
        mostrarOperacaoInvalida("O astronauta escolhido ja faz parte dos passageiros");
        return;
    };


    int old_qtd_passageiros = listaVoos[opcao_voo].getQtdPassageiros();
    Astronauta *new_passageiros = new Astronauta[old_qtd_passageiros + 1];

    for (int i = 0; i < old_qtd_passageiros; i++) {
        new_passageiros[i] = listaVoos[opcao_voo].passageiros[i];
    }

    
    index_astronauta = findAstronauta(cpf_astronauta, listaAstronautas, *qtdAstronautas);

    if (listaAstronautas[index_astronauta].getStatus() != 0) {
        mostrarOperacaoInvalida("O astronauta escolhido nao esta disponivel para novos voos");
        return;
    } else listaAstronautas[index_astronauta].setStatus(1);

    new_passageiros[old_qtd_passageiros] = listaAstronautas[index_astronauta];

    
    delete[] listaVoos[opcao_voo].passageiros;
    listaVoos[opcao_voo].passageiros = new_passageiros;
    listaVoos[opcao_voo].setQtdPassageiros(old_qtd_passageiros + 1);

    limparTerminal();

    std::cout << "Astronauta adicionado com sucesso!\n\n" << std::endl;
    
    pausarTerminal();
}


void removerAstronautaDoVoo(Voo *listaVoos, Astronauta *listaAstronautas, int *qtdVoos, int *qtdAstronautas) {
    int opcao_voo, index_astronauta_lista, index_astronauta_passageiros;
    std::string cpf_astronauta;

    limparTerminal();

    
    if (*qtdVoos == 0 || *qtdAstronautas == 0) {
        mostrarOperacaoInvalida("Quantidade insuficiente");
        return;
    }

    opcao_voo = selecionarVoo(listaVoos, *qtdVoos);
    if (opcao_voo == 0) return;
    opcao_voo--;

    if (listaVoos[opcao_voo].getStatus() != 0) {
        mostrarOperacaoInvalida("O voo não esta em planejamento");
        return;
    }

    if (listaVoos[opcao_voo].getQtdPassageiros() == 0) {
        mostrarOperacaoInvalida("O voo não possui astronautas");
        return;
    }

    cpf_astronauta = selecionarAstronauta(listaAstronautas, *qtdAstronautas);

    if (findAstronautaNoVoo(listaVoos[opcao_voo], cpf_astronauta) == -1) {
        mostrarOperacaoInvalida("O astronauta escolhido não faz parte dos passageiros");
        return;
    };


    index_astronauta_lista = findAstronauta(cpf_astronauta, listaAstronautas, *qtdAstronautas);
    index_astronauta_passageiros = findAstronautaNoVoo(listaVoos[opcao_voo], cpf_astronauta);

    listaAstronautas[index_astronauta_lista].setStatus(0);

    
    int old_qtd_passageiros = listaVoos[opcao_voo].getQtdPassageiros();
    Astronauta *new_passageiros = new Astronauta[old_qtd_passageiros - 1];

    for (int i = 0; i < index_astronauta_passageiros; i++) {
        new_passageiros[i] = listaVoos[opcao_voo].passageiros[i];
    }

    for (int i = index_astronauta_passageiros; i < old_qtd_passageiros - 1; i++) {
        new_passageiros[i] = listaVoos[opcao_voo].passageiros[i + 1];
    }

    delete[] listaVoos[opcao_voo].passageiros;
    listaVoos[opcao_voo].passageiros = new_passageiros;
    listaVoos[opcao_voo].setQtdPassageiros(old_qtd_passageiros - 1);

    limparTerminal();

    std::cout << "Astronauta removido com sucesso!\n\n" << std::endl;
    
    pausarTerminal();
}


void lancarVoo(Voo *listaVoos, int qtdVoos, int qtdAstronautas) {
    int opcao_voo;
    
    limparTerminal();

    
    if (qtdVoos == 0 || qtdAstronautas == 0) {
        mostrarOperacaoInvalida("Quantidade insuficiente");
        return;
    }

    opcao_voo = selecionarVoo(listaVoos, qtdVoos);
    if (opcao_voo == 0) return;
    opcao_voo--;

    if (listaVoos[opcao_voo].getStatus() != 0) {
        mostrarOperacaoInvalida("O voo não esta em planejamento");
        return;
    }

    if (listaVoos[opcao_voo].getQtdPassageiros() == 0) {
        mostrarOperacaoInvalida("O voo não possui astronautas");
        return;
    }

    listaVoos[opcao_voo].setStatus(1);

    for (int i = 0; i < listaVoos[opcao_voo].getQtdPassageiros(); i++) {
        listaVoos[opcao_voo].passageiros[i].setStatus(2);
    }

    limparTerminal();

    std::cout << "Voo lancado com sucesso!\n\n" << std::endl;
    
    pausarTerminal();

}


void explodirVoo(Astronauta *listaAstronautas, Voo *listaVoos, int qtdVoos, int qtdAstronautas) {
    int opcao_voo;
    
    limparTerminal();

    
    if (qtdVoos == 0 || qtdAstronautas == 0) {
        mostrarOperacaoInvalida("Quantidade insuficiente de astronautas/voos");
        return;
    }

    opcao_voo = selecionarVoo(listaVoos, qtdVoos);
    if (opcao_voo == 0) return;
    opcao_voo--;

    if (listaVoos[opcao_voo].getStatus() != 1) {
        mostrarOperacaoInvalida("O voo não está em andamento");
        return;
    }

    listaVoos[opcao_voo].setStatus(3);

    for (int i = 0; i < listaVoos[opcao_voo].getQtdPassageiros(); i++) {
        listaVoos[opcao_voo].passageiros[i].setStatus(3);
    }

    for (int i = 0; i < listaVoos[opcao_voo].getQtdPassageiros(); i++) {
        for (int j = 0; j < qtdAstronautas; j++) {
            if (listaAstronautas[j].getCpf() == listaVoos[opcao_voo].passageiros[i].getCpf()) {
                listaAstronautas[j].setStatus(3);
            }
        }
    }
    
    
    delete[] listaVoos[opcao_voo].passageiros;
    listaVoos[opcao_voo].passageiros = new Astronauta[0];
    listaVoos[opcao_voo].setQtdPassageiros(0);

    limparTerminal();

    std::cout << "Voo explodido com sucesso!\n\n" << std::endl;
    
    pausarTerminal();    
}


void finalizarVoo(Astronauta *listaAstronautas, Voo *listaVoos, int qtdVoos, int qtdAstronautas) {
    int opcao_voo;
    
    limparTerminal();

    
    if (qtdVoos == 0 || qtdAstronautas == 0) {
        mostrarOperacaoInvalida("Quantidade insuficiente");
        return;
    }

    opcao_voo = selecionarVoo(listaVoos, qtdVoos);
    if (opcao_voo == 0) return;
    opcao_voo--;

    if (listaVoos[opcao_voo].getStatus() != 1) {
        mostrarOperacaoInvalida("O voo não esta em andamento");
        return;
    }

    listaVoos[opcao_voo].setStatus(2);

    for (int i = 0; i < listaVoos[opcao_voo].getQtdPassageiros(); i++) {
        listaVoos[opcao_voo].passageiros[i].setStatus(0);
    }

    for (int i = 0; i < listaVoos[opcao_voo].getQtdPassageiros(); i++) {
        for (int j = 0; j < qtdAstronautas; j++) {
            if (listaAstronautas[j].getCpf() == listaVoos[opcao_voo].passageiros[i].getCpf()) {
                listaAstronautas[j].setStatus(0);
            }
        }
    }

    
    delete[] listaVoos[opcao_voo].passageiros;
    listaVoos[opcao_voo].passageiros = new Astronauta[0];
    listaVoos[opcao_voo].setQtdPassageiros(0);

    limparTerminal();

    std::cout << "Voo finalizado com sucesso!\n\n" << std::endl;
    
    pausarTerminal();    
}


void listarAstronautasMortos(Astronauta *listaAstronautas, int qtdAstronautas) {
    limparTerminal();

    std::cout << "Astronautas Mortos\n\n" << std::endl;

    for (int i = 0; i < qtdAstronautas; i++) {
        if (listaAstronautas[i].getStatus() == 3) {
            std::cout << i + 1 << " - Nome: " << listaAstronautas[i].getNome() << "; Idade: " << listaAstronautas[i].getIdade() << "; CPF: " << listaAstronautas[i].getCpf() << "\n";
        }
    }

    std::cout << "\n" << std::endl;

    pausarTerminal();
}


int selecionarVoo(Voo *listaVoos, int qtdVoos) {
    int opcao;
    bool opcao_invalida;
    std::string status;

    do {
        limparTerminal();

        std::cout << "Por favor, selecione o indice do voo.\n" << std::endl;

        for (int i = 0; i < qtdVoos; i++) {
            switch (listaVoos[i].getStatus()) {
                case 0:
                    status = "Voo em Planejamento";
                    break;
                case 1:
                    status = "Em Voo";
                    break;
                case 2:
                    status = "Voo Finalisado";
                    break;
                case 3:
                    status = "Voo Explodido";
            }       

            std::cout << i + 1 << " - Codigo: " << listaVoos[i].getCodigo() << " [" << status << "]" << "\n";
        }

        std::cin >> opcao;

        opcao_invalida = opcao <= 0 || opcao > qtdVoos;

        if (opcao_invalida) mostrarOpcaoInvalida();
    } while (opcao_invalida);

    return opcao;
}

std::string selecionarAstronauta(Astronauta *listaAstronautas, int qtdAstronautas) {
    std::string cpf;
    bool opcao_invalida = true;
    std::string status;

    do {
        limparTerminal();

        std::cout << "Por favor, insira o CPF do astronauta.\n" << std::endl;

        for (int i = 0; i < qtdAstronautas; i++) {
            switch (listaAstronautas[i].getStatus()) {
                case 0:
                    status = "Astronauta Disponível";
                    break;
                case 1:
                    status = "Astronauta Alocado";
                    break;
                case 2:
                    status = "Astronauta em Voo";
                    break;
                case 3:
                    status = "Astronauta Morto";
            }       

            std::cout << listaAstronautas[i].getCpf() << " - Nome: " << listaAstronautas[i].getNome() << " [" << status << "]" << "\n";
        }

        std::cin >> cpf;

        for (int i = 0; i < qtdAstronautas; i++) {
            if (cpf.compare(listaAstronautas[i].getCpf()) == 0) {
                opcao_invalida = false;
            }
        }

        if (opcao_invalida) mostrarOpcaoInvalida();
    } while (opcao_invalida);

    return cpf;
}

int findVoo(int codigo, Voo *listaVoos, int qtdVoos) {
    for (int i = 0; i < qtdVoos; i++) {
        if (codigo == listaVoos[i].getCodigo()) {
            return i;
        }
    }

    return -1;
}

int findAstronauta(std::string cpf, Astronauta *listaAstronautas, int qtdAstronautas) {
    for (int i = 0; i < qtdAstronautas; i++) {
        if (cpf.compare(listaAstronautas[i].getCpf()) == 0) {
            return i;
        }
    }

    return -1;
}


int findAstronautaNoVoo(Voo voo, std::string cpf) {
    for (int i = 0; i < voo.getQtdPassageiros(); i++) {
        if (cpf.compare(voo.getPassageiros()[i].getCpf()) == 0) {
            return i;
        }
    }

    return -1;  
}
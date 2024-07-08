# Projeto de Gestão de Astronautas
Este é um projeto de exemplo para gestão de astronautas e voos espaciais. Ele foi desenvolvido em C++ e possui uma estrutura modularizada para facilitar a manutenção e a extensão do código.

## Instruções para Compilação e Execução
Pré-requisitos
 - Compilador C++ (GCC, Clang, MSVC, etc.)
 - Sistema operacional compatível com o compilador escolhido

## Passos para Compilação
- Clone o repositório:
git clone https://github.com/usuario/projeto-astronautas.git
cd projeto-astronautas/astronautas

- Compile o projeto:
No terminal, execute o seguinte comando para compilar o projeto:
- No windows:
g++ -I .\cabecalhos .\comandos\configuracoes.cpp .\comandos\sistema.cpp .\comandos\menus.cpp .\src\astronauta.cpp .\src\voo.cpp .\main.cpp -o astronautas

- No Linux:
g++ -I ./cabecalhos ./comandos/configuracoes.cpp ./comandos/sistema.cpp ./comandos/menus.cpp ./src/astronauta.cpp ./src/voo.cpp ./main.cpp -o astronautas

- Após a compilação bem-sucedida, execute o programa com o seguinte comando:
./astronautas

Siga as instruções do menu para gerenciar os astronautas e voos.

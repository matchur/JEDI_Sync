# JEDI SYNC - Controle de Concorrência e Sincronização com Semáforos

<p align="center">  <img src="src/text_jedi.png" alt="Yoda OK" width=500/></p>

Este projeto foi desenvolvido como parte da disciplina de **Sistemas Operacionais** do Professor Rodrigo Campiolo, o objetivo deste é a aplicação de conceitos de concorrência e sincronização utilizando semaforos e monitores. Através de uma simulação do ambiente Jedi, o projeto gerencia a entrada, avaliação e saída de Padawans e espectadores em um salão controlado por Yoda, utilizando técnicas de sincronização para evitar impasses e inanição.

## Funcionalidades
- #### Controle de Acesso ao Salão:
  - Gerencia a entrada e saída de Padawans e espectadores, respeitando os limites de capacidade e o fluxo correto das operações.

- #### Sincronização Avançada:
  - Implementação de semáforos para garantir a coordenação das threads, evitando conflitos e garantindo consistência.

- #### Interface Dinâmica via Console:
  - Exibe em tempo real as ações de Yoda, Padawans e espectadores durante a execução da simulação.

- #### Resolução de Problemas Clássicos de Concorrência:
  - Técnicas aplicadas para evitar deadlocks e starvation em cenários altamente concorrentes.

- #### Personalização de Parâmetros:
  - Permite ao usuário personalizar o número de Padawans e espectadores de forma aleatória ou manual antes de iniciar a simulação.

<p align="center">  <img src="src/training_yoda.png" alt="Yoda OK" width=740/></p>

## Arquitetura do Projeto
O projeto está organizado em submódulos separados por funcionalidade:


*utils/* - 
Contém funções genéricas, como a inicialização de semáforos e controle de sincronização.

*padawans/* - 
Define as ações específicas dos Padawans, como entrada no salão, cumprimento e avaliação.

*spec/* - 
Gerencia as ações dos espectadores, como entrada e saída do salão, além de sua interação com os testes.

*yoda/* - 
Controla as ações do Mestre Yoda, incluindo a supervisão do salão, corte de tranca e anúncio de resultados.


## Como Executar
Clone o repositório e navegue até o diretório principal.

Compile o programa utilizando o Makefile:
``` bash
make
```
Execute o programa:
``` bash
./programa
```
Caso modifique o codigo e queira refazer os arquivos:
``` bash
make rebuild
```

<p align="center">  <img src="src/yoda_cape.png" alt="Yoda OK" width=170/></p>

## Grupo:
- Matheus Vinicius Costa
- Lucas Dos Santos Vaz

#include "ctrl_semaforo.h"
#include <stdio.h>

//Declaração de Variaveis
int tranca_salao; //Binário (1 - Aberto / 0 - Fechado)
int count_avaliacao = 0;

int count_padawans_dentro = 0; //contagem de padawans que entraram
int count_padawans_testados = 0; //contagem de padawans que terminaram a avaliação_1
int count_padawans_ajoelhado = 0; //contagem de padawans que esperam cortar a trança
int count_padawans_avaliados = 0; //contagem de padawans que já fizeram a avaliação e sairam do salao 
//Declaração dos semáforos globais
//Capacidade de cada integrante dentro do salão
sem_t capacidade_padawan; 
sem_t capacidade_espectadores; 

//Espera por avaliação
sem_t exclusao_mutua;
sem_t avaliacao_padawan; //Binário (0 - Pausado/ n - Começar a avaliação)

sem_t corte_tranca;
sem_t capacidade_testes;

//Mestres Avaliadores
sem_t cumprimentar_mestres;// Binário (Ocupado / Não Ocupado)


// Função para inicializar os semáforos com valores iniciais
void inicializa_semaforos(int max_espectadores, int max_padawans) {

    // Semáforo para controlar o acesso ao salão (Starta fechado)
    tranca_salao = 0;

    // Semáforo para controlar a capacidade máxima de padawans no salão
    if (sem_init(&capacidade_padawan, 0, max_padawans) != 0) {
        perror("Erro ao inicializar semáforo: capacidade_padawans");
    }

    // Semáforo para controlar a capacidade máxima de espectadores no salão
    if (sem_init(&capacidade_espectadores, 0, max_espectadores) != 0) {
        perror("Erro ao inicializar semáforo: capacidade_espectadores");
    }

    // Semáforo para Exclusão Mútua
    if (sem_init(&exclusao_mutua, 0, 1) != 0) {
        perror("Erro ao inicializar semáforo: exclusao_mutua");
    }

    // Semáforo para sincronizar a avaliação dos Padawans (Começa com 0 para todos os Padawans iniciarem a avaliação Juntos)
    if (sem_init(&avaliacao_padawan, 0, 0) != 0) {
        perror("Erro ao inicializar semáforo: avaliacao_padawan");
    }

    // Semáforo para sincronizar o corte da trança
    if (sem_init(&corte_tranca, 0, 0) != 0) {
        perror("Erro ao inicializar semáforo: corte_tranca");
    }

    // Semáforo para capacidade de testes
    if (sem_init(&capacidade_testes, 0, 1) != 0) {
        perror("Erro ao inicializar semáforo: capacidade_testes");
    }

    // Semáforo para capacidade de testes
    if (sem_init(&cumprimentar_mestres, 0, 1) != 0) {
        perror("Erro ao inicializar semáforos: cumprimentar_mestres");
    }

    printf("Semáforos inicializados com sucesso.\n");
}

// Função para destruir os semáforos ao final da execução
void destroi_semaforos() {
    // Destroi cada semáforo e verifica erros
    if (sem_destroy(&capacidade_padawan) != 0) {
        perror("Erro ao destruir semáforo: capacidade_padawan");
    }

    if (sem_destroy(&capacidade_espectadores) != 0) {
        perror("Erro ao destruir semáforo: capacidade_espectadores");
    }

    if (sem_destroy(&avaliacao_padawan) != 0) {
        perror("Erro ao destruir semáforo: avaliacao_padawan");
    }

    if (sem_destroy(&corte_tranca) != 0) {
        perror("Erro ao destruir semáforo: corte_tranca");
    }

    if (sem_destroy(&capacidade_testes) != 0) {
        perror("Erro ao destruir semáforo: capacidade_testes");
    }

    if (sem_destroy(&cumprimentar_mestres) != 0) 
    {
        perror("Erro ao destruir semáforos: cumprimentar_mestres");
    }

    printf("Semáforos destruídos com sucesso.\n");
}

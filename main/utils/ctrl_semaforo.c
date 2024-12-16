#include "ctrl_semaforo.h"
#include <stdio.h>

// Declaração dos semáforos globais
sem_t tranca_salao;
sem_t capacidade_espectadores;
sem_t avaliacao_padawan;
sem_t corte_tranca;
sem_t capacidade_testes;

// Função para inicializar os semáforos com valores iniciais
void inicializa_semaforos(int max_espectadores, int max_padawans) {
    //TESTAR ISSO AQUI DEPOIS.....
    (void)max_padawans;
    // Semáforo para controlar o acesso ao salão (Starta fechado)
    if (sem_init(&tranca_salao, 0, 0) != 0) {
        perror("Erro ao inicializar semáforo: tranca_salao");
    }

    // Semáforo para controlar a capacidade máxima de espectadores no salão
    if (sem_init(&capacidade_espectadores, 0, max_espectadores) != 0) {
        perror("Erro ao inicializar semáforo: capacidade_espectadores");
    }

    // Semáforo para sincronizar a avaliação dos Padawans (um por vez)
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

    printf("Semáforos inicializados com sucesso.\n");
}

// Função para destruir os semáforos ao final da execução
void destroi_semaforos() {
    // Destroi cada semáforo e verifica erros
    if (sem_destroy(&tranca_salao) != 0) {
        perror("Erro ao destruir semáforo: tranca_salao");
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

    printf("Semáforos destruídos com sucesso.\n");
}

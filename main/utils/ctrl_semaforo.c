#include "ctrl_semaforo.h"
#include <stdio.h>

// --------------------------- Declaração de Variáveis Globais ---------------------------
// Variáveis para controle do estado do salão e contadores de participantes
int tranca_salao;              // Binário (1 - Aberto / 0 - Fechado)
int count_avaliacao;           // Contagem de avaliações em andamento
int count_padawans_dentro;     // Contagem de Padawans atualmente dentro do salão
int count_padawans_testados;   // Contagem de Padawans que terminaram a avaliação inicial

int count_padawans_avaliados;  // Contagem de Padawans que concluíram o processo e saíram

int count_spec_dentro;         // Contagem de Espectadores que estão dentro do salão

// --------------------------- Declaração dos Semáforos Globais ---------------------------
// Controle de capacidade do salão
sem_t capacidade_padawan;      // Limita o número de Padawans no salão
sem_t capacidade_espectadores; // Limita o número de espectadores no salão

// Controle de acesso e sincronização
sem_t exclusao_mutua;          // Garantir acesso exclusivo a seções críticas
sem_t avaliacao_padawan;       // Sincroniza início da avaliação dos Padawans
sem_t corte_tranca;            // Sincroniza o corte da trança
sem_t capacidade_testes;       // Controla a capacidade de testes simultâneos
sem_t cumprimentar_mestres;    // Sincroniza o cumprimento dos mestres

sem_t padawan_ajoelhado;       // Sincroniza Padawans Ajoelhados
sem_t padawan_espera_avaliacao;
sem_t padawan_finalizado;

sem_t ajoelhados_sem;
sem_t padawans_levantar;
sem_t saida_padawans;


// --------------------------- Funções ---------------------------

/**
 * @brief Inicializa os semáforos utilizados no programa.
 * 
 * @param max_espectadores Capacidade máxima de espectadores no salão.
 * @param max_padawans Capacidade máxima de Padawans no salão.
 */
void inicializa_semaforos(int max_espectadores, int max_padawans) {
    // Inicialização dos estados iniciais
    tranca_salao = 0;
    count_avaliacao = 0;
    count_padawans_dentro = 0;
    count_padawans_testados = 0;
    count_padawans_avaliados = 0;
    count_spec_dentro = 0;

    // Inicialização dos semáforos com valores iniciais
    if (sem_init(&capacidade_padawan, 0, max_padawans) != 0) {
        perror("Erro ao inicializar semáforo: capacidade_padawan");
    }
    if (sem_init(&capacidade_espectadores, 0, max_espectadores) != 0) {
        perror("Erro ao inicializar semáforo: capacidade_espectadores");
    }
    if (sem_init(&exclusao_mutua, 0, 1) != 0) {
        perror("Erro ao inicializar semáforo: exclusao_mutua");
    }
    if (sem_init(&avaliacao_padawan, 0, 0) != 0) { 
        perror("Erro ao inicializar semáforo: avaliacao_padawan");
    }
    if (sem_init(&corte_tranca, 0, 0) != 0) { 
        perror("Erro ao inicializar semáforo: corte_tranca");
    }
    if (sem_init(&capacidade_testes, 0, 1) != 0) {
        perror("Erro ao inicializar semáforo: capacidade_testes");
    }
    if (sem_init(&cumprimentar_mestres, 0, 1) != 0) {
        perror("Erro ao inicializar semáforo: cumprimentar_mestres");
    }
    if (sem_init(&padawan_ajoelhado, 0, 0) != 0) {
        perror("Erro ao inicializar semáforo: padawan_ajoelhado");
    }
    if (sem_init(&padawan_espera_avaliacao, 0, 0) != 0) {
        perror("Erro ao inicializar semáforo: padawan_ajoelhado");
    }
    if (sem_init(&padawan_finalizado, 0, 0) != 0) {
        perror("Erro ao inicializar semáforo: padawan_ajoelhado");
    }
    if (sem_init(&ajoelhados_sem, 0, 0) != 0) {
        perror("Erro ao inicializar semáforo: ajoelhados_sem");
    }
    if (sem_init(&padawans_levantar, 0, 0) != 0) {
        perror("Erro ao inicializar semáforo: padawans_levantar");
    }
    if (sem_init(&saida_padawans, 0, 0) != 0) {
        perror("Erro ao inicializar semáforo: saida_padawans");
    }
    



    printf("Semáforos inicializados com sucesso.\n");
}

/**
 * @brief Destroi os semáforos após o término da execução do programa.
 */
void destroi_semaforos() {
    // Destruir cada semáforo e verificar erros
    if (sem_destroy(&capacidade_padawan) != 0) {
        perror("Erro ao destruir semáforo: capacidade_padawan");
    }
    if (sem_destroy(&capacidade_espectadores) != 0) {
        perror("Erro ao destruir semáforo: capacidade_espectadores");
    }
    if (sem_destroy(&exclusao_mutua) != 0) {
        perror("Erro ao destruir semáforo: exclusao_mutua");
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
    if (sem_destroy(&cumprimentar_mestres) != 0) {
        perror("Erro ao destruir semáforo: cumprimentar_mestres");
    }
    if (sem_destroy(&padawan_ajoelhado) != 0) {
        perror("Erro ao destruir semáforo: padawan_ajoelhado");
    }

    printf("Semáforos destruídos com sucesso.\n");
}

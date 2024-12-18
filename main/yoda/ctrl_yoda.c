#include "ctrl_yoda.h"
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>

// Variáveis e semáforos globais para controle do salão e testes
extern int tranca_salao;                // Controle de abertura/fechamento do salão
extern sem_t capacidade_testes;         // Gerencia a capacidade de testes
extern sem_t avaliacao_padawan;         // Controle de avaliação dos padawans
extern sem_t corte_tranca;              // Controle para cortar a trança

extern sem_t exclusao_mutua;            // Exclusão mútua para variáveis globais
extern int count_avaliacao;             // Contador de avaliações em andamento
extern int count_padawans_dentro;       // Contador de padawans no salão
extern int count_padawans_testados;     // Contador de padawans testados
extern int count_padawans_ajoelhado;    // Contador de padawans ajoelhados

void libera_entrada() {
    printf("Yoda liberou a entrada para o salão.\n");
    sem_wait(&exclusao_mutua);
    tranca_salao = 1; // Abre o salão
    sem_post(&exclusao_mutua);
}

void fecha_entrada() {
    printf("Yoda trancou o salão.\n");
    sem_wait(&exclusao_mutua);
    tranca_salao = 0; // Fecha o salão
    sem_post(&exclusao_mutua);
}

void inicia_testes() {
    // Aguarda que todos os padawans estejam prontos para começar
    sem_wait(&exclusao_mutua);
    while (count_avaliacao < count_padawans_dentro) {
        sem_post(&exclusao_mutua);
        usleep(100); // Evita busy waiting puro
        sem_wait(&exclusao_mutua);
    }
    sem_post(&exclusao_mutua);

    // Libera os padawans para a avaliação
    for (int i = 0; i < count_padawans_dentro; i++) {
        sem_post(&avaliacao_padawan);
    }
    printf("Yoda sinaliza que avaliações comecem.\n");
}

void finaliza_testes() {
    printf("Aguardando a conclusão de todos os testes.\n");

    // Aguarda que todos os padawans tenham sido testados
    sem_wait(&exclusao_mutua);
    while (count_padawans_testados < count_padawans_dentro) {
        sem_post(&exclusao_mutua);
        usleep(100); // Evita busy waiting puro
        sem_wait(&exclusao_mutua);
    }
    sem_post(&exclusao_mutua);

    printf("Todos os testes foram concluídos.\n");
}

void corta_tranca() {
    printf("Yoda liga seu sabre de luz e se prepara para cortar tranças.\n");

    // Aguarda que todos os padawans estejam ajoelhados
    sem_wait(&exclusao_mutua);
    while (count_padawans_ajoelhado < count_padawans_dentro) {
        sem_post(&exclusao_mutua);
        usleep(100); // Evita busy waiting puro
        sem_wait(&exclusao_mutua);
    }
    sem_post(&exclusao_mutua);

    // Libera o corte da trança
    sem_post(&corte_tranca);
}

void guarda_sabre() {
    printf("Yoda aguarda todos os padawans se levantarem antes de guardar o sabre.\n");

    // Aguarda que todos os padawans tenham se levantado
    sem_wait(&exclusao_mutua);
    while (count_padawans_ajoelhado > 0) {
        sem_post(&exclusao_mutua);
        usleep(100); // Evita busy waiting puro
        sem_wait(&exclusao_mutua);
    }
    sem_post(&exclusao_mutua);

    // Guarda o sabre de luz
    printf("Yoda desliga seu sabre de luz.\n");
    sem_wait(&corte_tranca);
}

void anuncia_resultado() {
    printf("Yoda está anunciando os resultados dos testes.\n");

    // Simula um atraso para efeito dramático
    sleep(2);
}

//Aguarda todos os padawans sairem de dentro do salão
void aguarda_saida()
{
    while(count_padawans_dentro > 0){}
}

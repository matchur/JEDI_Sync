// ctrl_spec.c

#include "ctrl_spec.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Declaração dos semáforos utilizados para sincronização
static sem_t salao_mutex;
static sem_t teste_semaforo;
static int pessoas_no_salao = 0;

// Função para inicializar os recursos
void init_spec_resources() {
    sem_init(&salao_mutex, 0, 1); // Mutex para acessar o salão
    sem_init(&teste_semaforo, 0, 0); // Controle dos testes
    pessoas_no_salao = 0;
}

// Função para destruir os recursos
void destroy_spec_resources() {
    sem_destroy(&salao_mutex);
    sem_destroy(&teste_semaforo);
}

// Função para entrar no salão
void spec_entra_salao(int id,const char *nome) {
    sem_wait(&salao_mutex);
    pessoas_no_salao++;
    printf("%s - (%d) entrou no salão. Total no salão: %d\n", nome,id, pessoas_no_salao);
    sem_post(&salao_mutex);
}

// Função para assistir os testes
void assiste_testes(int id,const char *nome) {
    printf("%s - (%d) está assistindo aos testes.\n",nome,id);
    sem_wait(&teste_semaforo);
    // Simulação de assistir os testes (pode ser um sleep ou operação específica)
}

// Função para sair do salão
void spec_sai_salao(int id,const char *nome) {
    sem_wait(&salao_mutex);
    pessoas_no_salao--;
    printf("%s - (%d) saiu do salão. Total no salão: %d\n", nome,id, pessoas_no_salao);
    if (pessoas_no_salao == 0) {
        printf("O salão está vazio.\n");
    }
    sem_post(&salao_mutex);
}

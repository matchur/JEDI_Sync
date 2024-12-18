#include "ctrl_spec.h"
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// Variáveis externas para sincronização
extern int count_spec_dentro;    // Contador de espectadores dentro do salão
extern int tranca_salao;         // Indica se o salão está trancado (0 = trancado, 1 = aberto)
extern sem_t capacidade_espectadores; // Semáforo para controlar a capacidade de espectadores no salão
extern sem_t exclusao_mutua;

// Função para entrar no salão
void spec_entra_salao(int id, const char *nome) 
{
    // Aguarda o salão estar destrancado    
    printf("Espectador %d (%s) chegou.\n", id, nome);
    while (!tranca_salao) {}
    
    // Aguarda sua vez de entrar, respeitando a capacidade máxima
    printf("Espectador %d (%s) entrou no salão e está procurando um lugar.\n", id, nome);
    sem_wait(&capacidade_espectadores);

    // Incrementa o contador de espectadores dentro do salão
    sem_wait(&exclusao_mutua);
    count_spec_dentro++;
    sem_post(&exclusao_mutua);
    // Mensagem de entrada
    printf("Espectador %d (%s) sentou.\n", id, nome);
}

// Função para assistir aos testes
void assiste_testes(int id, const char *nome) 
{   
    srand(time(NULL)); // Inicializa o gerador de números aleatórios para cada thread
    
    int is_watching = 1;
    while (is_watching) {
        sleep(6); // Espectador assiste por 6 segundos
        is_watching = rand() % 2; // Define se continua assistindo (0 = para, 1 = continua)
    }
}

// Função para sair do salão
void spec_sai_salao(int id, const char *nome) 
{
    // Decrementa o contador de espectadores dentro do salão
    sem_wait(&exclusao_mutua);
    count_spec_dentro--;
    sem_post(&exclusao_mutua);

    // Libera o semáforo, permitindo que outro espectador entre
    sem_post(&capacidade_espectadores);

    // Mensagem de saída
    printf("Espectador %d (%s) saiu do salão.\n", id, nome);
}

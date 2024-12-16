#ifndef CTRL_SEMAFORO_H
#define CTRL_SEMAFORO_H

#include <semaphore.h>
#include <pthread.h>

// Declaração dos semáforos globais usados em todo o sistema
//Declaração de Variaveis
extern int tranca_salao; 
extern int count_avaliacao;
extern sem_t capacidade_padawan; 
extern sem_t capacidade_espectadores; 
extern sem_t avaliacao_padawan; 
extern sem_t corte_tranca;
extern sem_t capacidade_testes;
extern sem_t mestre_1,mestre_2,mestre_3,mestre_4;

// Inicialização e destruição dos semáforos
void inicializa_semaforos(int max_espectadores, int max_padawans);
void destroi_semaforos();

#endif // CTRL_SEMAFORO_H

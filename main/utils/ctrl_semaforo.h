#ifndef CTRL_SEMAFORO_H
#define CTRL_SEMAFORO_H

#include <semaphore.h>
#include <pthread.h>

// Declaração dos semáforos globais usados em todo o sistema
//Declaração de Variaveis
extern int tranca_salao; 
extern int count_avaliacao;
extern int count_padawans_dentro; 
extern int count_padawans_avaliados;
extern int count_padawans_ajoelhado;
extern int count_padawans_testados;

extern sem_t capacidade_padawan; 
extern sem_t capacidade_espectadores; 
extern sem_t avaliacao_padawan; 
extern sem_t corte_tranca;
extern sem_t capacidade_testes;
extern sem_t cumprimentar_mestres;
extern sem_t exclusao_mutua;

// Inicialização e destruição dos semáforos
void inicializa_semaforos(int max_espectadores, int max_padawans);
void destroi_semaforos();

#endif // CTRL_SEMAFORO_H

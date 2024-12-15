#ifndef CTRL_SEMAFORO_H
#define CTRL_SEMAFORO_H

#include <semaphore.h>
#include <pthread.h>

// Declaração dos semáforos globais usados em todo o sistema
extern sem_t tranca_salao;               // Para bloquear ou liberar acesso ao salão
extern sem_t capacidade_espectadores;   // Controle do número de espectadores no salão
extern sem_t avaliacao_padawan;         // Controle de acesso ao Padawan na avaliação
extern sem_t corte_tranca;              // Semáforo para sincronizar o corte da trança

// Inicialização e destruição dos semáforos
void inicializa_semaforos(int max_espectadores, int max_padawans);
void destroi_semaforos();

#endif // CTRL_SEMAFORO_H

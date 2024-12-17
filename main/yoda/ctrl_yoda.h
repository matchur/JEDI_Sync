#ifndef CTRL_YODA_H
#define CTRL_YODA_H

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

// Funções relacionadas ao controle de Yoda
void inicia_testes(int max_padawans);
void libera_entrada();
void anuncia_resultado();
void corta_tranca();
void finaliza_testes();
void fecha_entrada();
void guarda_sabre()

#endif // CTRL_YODA_H

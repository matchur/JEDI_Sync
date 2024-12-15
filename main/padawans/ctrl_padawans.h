#ifndef CTRL_PADAWAN_H
#define CTRL_PADAWAN_H

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

// Funções relacionadas ao comportamento do Padawan
void entra_salao(const char* nome);
void cumprimenta_mestres_avaliadores(const char* nome);
void aguarda_avaliacao(const char* nome);
void realiza_avaliacao(const char* nome);
void aguarda_corte_tranca(const char* nome);
void cumprimenta_Yoda(const char* nome);
void sai_salao(const char* nome);

#endif // CTRL_PADAWAN_H

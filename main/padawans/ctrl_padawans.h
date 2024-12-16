#ifndef CTRL_PADAWAN_H
#define CTRL_PADAWAN_H

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

// Funções relacionadas ao comportamento do Padawan
void padawan_entra_salao(int id,const char* nome);
void cumprimenta_mestres_avaliadores(int id,const char* nome);
void aguarda_avaliacao(int id,const char* nome);
void realiza_avaliacao(int id,const char* nome);
void aguarda_corte_tranca(int id,const char* nome);
void cumprimenta_Yoda(int id,const char* nome);
void padawan_sai_salao(int id,const char* nome);

#endif // CTRL_PADAWAN_H

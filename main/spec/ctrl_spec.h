#ifndef CTRL_SPEC_H
#define CTRL_SPEC_H

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

// Funções relacionadas ao comportamento dos espectadores
void spec_entra_salao(int id,const char* nome);
void assiste_testes();
void spec_sai_salao(int id,const char* nome);

#endif // CTRL_SPEC_H

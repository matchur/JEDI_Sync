#include "ctrl_padawans.h"

// Semáforos compartilhados para controle
extern sem_t tranca_salao;
extern sem_t capacidade_testes;

void entra_salao(int id, const char* nome) {
    printf("%s - (%d) está aguardando para entrar no salão.\n",id, nome);
    sem_wait(&tranca_salao); // Aguarda que o salão seja destrancado
    printf("%s entrou no salão.\n", nome);
}

void cumprimenta_mestres_avaliadores(int id,const char* nome) {
    printf("%s - (%d) está cumprimentando os mestres avaliadores.\n",id, nome);
    // Simula o cumprimento
    sleep(1);
    printf("%s - (%d) concluiu o cumprimento aos mestres avaliadores.\n",id , nome);
}

void aguarda_avaliacao(int id,const char* nome) {
    printf("%s - (%d) está aguardando pela avaliação dos mestres.\n",id, nome);
    // Simula a espera
    sleep(2);
    printf("%s - (%d) recebeu sinal para iniciar sua avaliação.\n", id, nome);
}

void realiza_avaliacao(int id,const char* nome) {
    printf("%s - (%d) está realizando a avaliação.\n",id, nome);
    // Simula o tempo de avaliação
    sleep(2);
    printf("%s - (%d) concluiu a avaliação com sucesso.\n",id, nome);
}

void aguarda_corte_tranca(int id,const char* nome) {
    printf("%s - (%d) está aguardando que Yoda corte a tranca para sair do salão.\n",id, nome);
    sem_wait(&tranca_salao); // Aguarda que o salão seja destrancado novamente
    printf("%s - (%d) pode sair do salão.\n",  id, nome);
}

void cumprimenta_Yoda(int id,const char* nome) {
    printf("%s - (%d) está cumprimentando Yoda como sinal de respeito.\n",id, nome);
    // Simula o cumprimento
    sleep(1);
    printf("%s - (%d) concluiu o cumprimento a Yoda.\n",id, nome);
}

void sai_salao(int id,const char* nome) {
    printf("%s - (%d) está saindo do salão.\n",id, nome);
    sem_post(&tranca_salao); // Libera para o próximo Padawan entrar
    printf("%s - (%d) saiu do salão.\n",id, nome);
}

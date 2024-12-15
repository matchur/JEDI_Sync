#include "ctrl_padawan.h"

// Semáforos compartilhados para controle
extern sem_t tranca_salao;
extern sem_t capacidade_testes;

void entra_salao(int id, const char* nome) {
    printf("%s está aguardando para entrar no salão.\n", nome);
    sem_wait(&tranca_salao); // Aguarda que o salão seja destrancado
    printf("%s entrou no salão.\n", nome);
}

void cumprimenta_mestres_avaliadores(int id,const char* nome) {
    printf("%s está cumprimentando os mestres avaliadores.\n", nome);
    // Simula o cumprimento
    sleep(1);
    printf("%s concluiu o cumprimento aos mestres avaliadores.\n", nome);
}

void aguarda_avaliacao(int id,const char* nome) {
    printf("%s está aguardando pela avaliação dos mestres.\n", nome);
    // Simula a espera
    sleep(2);
    printf("%s recebeu sinal para iniciar sua avaliação.\n", nome);
}

void realiza_avaliacao(int id,const char* nome) {
    printf("%s está realizando a avaliação.\n", nome);
    // Simula o tempo de avaliação
    sleep(2);
    printf("%s concluiu a avaliação com sucesso.\n", nome);
}

void aguarda_corte_tranca(int id,const char* nome) {
    printf("%s está aguardando que Yoda corte a tranca para sair do salão.\n", nome);
    sem_wait(&tranca_salao); // Aguarda que o salão seja destrancado novamente
    printf("%s pode sair do salão.\n", nome);
}

void cumprimenta_Yoda(int id,const char* nome) {
    printf("%s está cumprimentando Yoda como sinal de respeito.\n", nome);
    // Simula o cumprimento
    sleep(1);
    printf("%s concluiu o cumprimento a Yoda.\n", nome);
}

void sai_salao(int id,const char* nome) {
    printf("%s está saindo do salão.\n", nome);
    sem_post(&tranca_salao); // Libera para o próximo Padawan entrar
    printf("%s saiu do salão.\n", nome);
}

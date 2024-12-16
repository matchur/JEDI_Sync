#include "ctrl_padawans.h"
#include <unistd.h>
// Semáforos compartilhados para controle
extern sem_t tranca_salao;
extern sem_t capacidade_testes; // <-  Talvez tirar esse extern

void padawan_entra_salao(int id, const char* nome) {
    printf("%s - (%d) está aguardando para entrar no salão.\n", nome,id);
    sem_wait(&tranca_salao); // Aguarda que o salão seja destrancado
    printf("%s - (%d) entrou no salão.\n", nome,id);
}

void cumprimenta_mestres_avaliadores(int id,const char* nome) {
    printf("%s - (%d) está cumprimentando os mestres avaliadores.\n", nome,id);
    // Simula o cumprimento - Talvez colocar mais um semaforo aqui!!!!!!!!!!!!!!!!!!!
    sleep(1);
    printf("%s - (%d) concluiu o cumprimento aos mestres avaliadores.\n" , nome,id);
}

void aguarda_avaliacao(int id,const char* nome) {
    printf("%s - (%d) está aguardando pela avaliação dos mestres.\n", nome, id);
    // Simula a espera
    sleep(2);
    printf("%s - (%d) recebeu sinal para iniciar sua avaliação.\n",nome , id);
}

void realiza_avaliacao(int id,const char* nome) {
    printf("%s - (%d) está realizando a avaliação.\n",nome, id);
    // Simula o tempo de avaliação
    sleep(2);
    printf("%s - (%d) concluiu a avaliação com sucesso.\n",nome, id);
}

void aguarda_corte_tranca(int id,const char* nome) {
    printf("%s - (%d) está aguardando que Yoda corte a tranca para sair do salão.\n", nome,id);
    sem_wait(&tranca_salao); // Aguarda que o salão seja destrancado novamente
    printf("%s - (%d) pode sair do salão.\n", nome,  id);
}

void cumprimenta_Yoda(int id,const char* nome) {
    printf("%s - (%d) está cumprimentando Yoda como sinal de respeito.\n", nome,id);
    // Simula o cumprimento
    sleep(1);
    printf("%s - (%d) concluiu o cumprimento a Yoda.\n", nome,id);
}

void padawan_sai_salao(int id,const char* nome) {
    printf("%s - (%d) está saindo do salão.\n", nome,id);
    sem_post(&tranca_salao); // Libera para o próximo Padawan entrar
    printf("%s - (%d) saiu do salão.\n", nome,id);
}

#include "ctrl_padawans.h"
#include <unistd.h>
#include <stdlib.h>  
#include <time.h>    

// Semáforos compartilhados para controle
extern int tranca_salao;
extern int count_avaliacao;
extern sem_t capacidade_padawan; 
extern sem_t avaliacao_padawan;
extern sem_t mestre_1,mestre_2,mestre_3,mestre_4;
extern sem_t corte_tranca;

void padawan_entra_salao(int id, const char* nome) {

    printf("%s - (%d) está aguardando para entrar no salão.\n", nome,id);
    while(!tranca_salao){}         //busy_wait (TALVEZ TIRAR??)
    sem_wait(&capacidade_padawan); // Aguarda que o salão tenha lugar
    printf("%s - (%d) entrou no salão.\n", nome,id);
}

void cumprimenta_mestres_avaliadores(int id,const char* nome) {
    printf("%s - (%d) está indo cumprimentar os Mestres Avaliadores.\n", nome,id);
    // Simula o cumprimento
    sleep(3);
    printf("%s - (%d) está cumprimentando o Mestre Avaliador 1.\n", nome, id);
    sem_wait(&mestre_1);
    sem_post(&mestre_1);
    printf("%s - (%d) está cumprimentando o Mestre Avaliador 2.\n", nome, id);
    sem_wait(&mestre_2);
    sem_post(&mestre_2);
    printf("%s - (%d) está cumprimentando o Mestre Avaliador 3.\n", nome, id);
    sem_wait(&mestre_3);
    sem_post(&mestre_3);
    printf("%s - (%d) está cumprimentando o Mestre Avaliador 4.\n", nome, id);
    sem_wait(&mestre_4);
    sem_post(&mestre_4);
    printf("%s - (%d) concluiu o cumprimento aos Mestres Avaliadores.\n" , nome,id);
}

void aguarda_avaliacao(int id,const char* nome) {
    printf("%s - (%d) está aguardando pela avaliação dos Mestres.\n", nome, id);
    count_avaliacao++;//TALVEZ COLOCAR UM MUTEX AQUI
    sem_wait(&avaliacao_padawan);    
    count_avaliacao--;//TALVEZ COLOCAR UM MUTEX AQUI
    sleep(2);
    printf("%s - (%d) recebeu sinal para iniciar sua avaliação.\n",nome , id);
}

void realiza_avaliacao(int id,const char* nome) {
    printf("%s - (%d) está realizando a avaliação.\n",nome, id);
    sleep(1);
    printf("ZING! Concentração máxima...\n");
    sleep(1);
    printf("SWOOSH! Movimentos impressionantes...\n");
    sleep(1);
    printf("BZZZZ! Um golpe final de tirar o fôlego!\n");
    sleep(1);
    printf("%s - (%d) concluiu a avaliação com sucesso.\n",nome, id);
}

void aguarda_corte_tranca(int id,const char* nome) {
    printf("%s - (%d) está aguardando que Yoda corte a tranca para sair do salão.\n", nome,id);

    sem_wait(&corte_tranca);  

    srand(time(NULL));
    int x = rand() % 2;
    sleep(3);
    if(x)
        printf("%s - (%d) Sua trança foi cortada. pode sair do salão.\n", nome,  id);
    else
        printf("%s - (%d) Sua trança não foi cortada. pode sair do salão.\n", nome,  id);   

    sem_post(&corte_tranca);     
}

void cumprimenta_Yoda(int id,const char* nome) {
    printf("%s - (%d) está cumprimentando Yoda como sinal de respeito.\n", nome,id);
    sleep(2);
    printf("%s - (%d) concluiu o cumprimento a Yoda.\n", nome,id);
}

void padawan_sai_salao(int id,const char* nome) {
    printf("%s - (%d) está saindo do salão.\n", nome,id);
    sem_post(&capacidade_padawan); // Libera para o próximo Padawan entrar
    printf("%s - (%d) saiu do salão.\n", nome,id);
}

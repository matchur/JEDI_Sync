#include "ctrl_padawans.h"
#include <unistd.h>
#include <stdlib.h>  
#include <time.h>    

// Semáforos compartilhados para controle
extern int tranca_salao;
extern int count_avaliacao;
extern int count_padawans_dentro; 
extern int count_padawans_testados;
extern int count_padawans_avaliados;
extern int count_padawans_ajoelhado;

extern sem_t capacidade_padawan; 
extern sem_t avaliacao_padawan;
extern sem_t cumprimentar_mestres;
extern sem_t corte_tranca;
extern sem_t exclusao_mutua;

void padawan_entra_salao(int id, const char* nome) {

    printf("%s - (%d) está aguardando para entrar no salão.\n", nome,id);
    while(!tranca_salao){}         //busy_wait (TALVEZ TIRAR??)
    sem_wait(&capacidade_padawan); // Aguarda que o salão tenha lugar

    sem_wait(&exclusao_mutua); 
    count_padawans_dentro++;
    sem_post(&exclusao_mutua); 

    printf("%s - (%d) entrou no salão.\n", nome,id);
}

void cumprimenta_mestres_avaliadores(int id,const char* nome) {
    printf("%s - (%d) está indo cumprimentar os Mestres Avaliadores.\n", nome,id);
    // Simula o cumprimento
      
    sem_wait(&cumprimentar_mestres); //Talvez mudar essa forma de cumprimento... Exclusão Mutua simulada
    printf("%s - (%d) está cumprimentando o Mestre Avaliador 1.\n", nome, id);
    sleep(1);     
    printf("%s - (%d) está cumprimentando o Mestre Avaliador 2.\n", nome, id);
    sleep(1); 
    printf("%s - (%d) está cumprimentando o Mestre Avaliador 3.\n", nome, id);
    sleep(1); 
    printf("%s - (%d) está cumprimentando o Mestre Avaliador 4.\n", nome, id);
    sleep(1); 
    sem_post(&cumprimentar_mestres);

    printf("%s - (%d) concluiu o cumprimento aos Mestres Avaliadores.\n" , nome,id);
}

void aguarda_avaliacao(int id,const char* nome) {
    printf("%s - (%d) está aguardando pela avaliação dos Mestres.\n", nome, id);

    sem_wait(&exclusao_mutua); 
    count_avaliacao++;
    sem_post(&exclusao_mutua); 

    sem_wait(&avaliacao_padawan); //Pega um dos semaforos de avaliação e começa

    sem_wait(&exclusao_mutua); 
    count_avaliacao--;
    sem_post(&exclusao_mutua); 
    sleep(2);
    printf("%s - (%d) recebeu a ordem para iniciar sua avaliação.\n",nome , id);
}

void realiza_avaliacao(int id,const char* nome) {
    printf("%s - (%d) está realizando a avaliação.\n",nome, id);
    sleep(1);
    printf("ZING!\n");
    sleep(1);
    printf("SWOOSH!\n");
    sleep(1);
    printf("BZZZZ!\n");
    sleep(1);
    sem_wait(&exclusao_mutua); 
    count_padawans_testados++;
    sem_post(&exclusao_mutua); 
    printf("%s - (%d) concluiu. Seus movimentos serão avaliados pelos Mestres.\n",nome, id);

}s

void aguarda_corte_tranca(int id,const char* nome) {
    while(count_padawans_testados < count_padawans_dentro){}
    printf("%s - (%d) Se aproxima de Yoda, ajoelha, e espera o resultado de sua avaliação.\n", nome,id);
    sem_wait(&exclusao_mutua); 
    count_padawans_ajoelhado++;
    sem_post(&exclusao_mutua); 
    

    sem_wait(&corte_tranca);  
    sleep(2)
    printf("...");
    srand(time(NULL));
    int x = rand() % 2;
    sleep(3);
    if(x)
        printf("%s - (%d) Sua trança foi cortada.\n", nome,  id);
    else
        printf("%s - (%d) Sua trança não foi cortada.\n", nome,  id);   

    sem_post(&corte_tranca); 
    printf("%s - (%d) Se levanta.\n", nome,id);
    sem_wait(&exclusao_mutua); 
        count_padawans_ajoelhado--;
    sem_post(&exclusao_mutua);     
}

void cumprimenta_Yoda(int id,const char* nome) {
    printf("%s - (%d) está cumprimentando Yoda como sinal de respeito.\n", nome,id);
    sleep(2);
    printf("%s - (%d) concluiu o cumprimento a Yoda.\n", nome,id);
}

void padawan_sai_salao(int id,const char* nome) {
    printf("%s - (%d) está saindo do salão.\n", nome,id);
    sem_post(&capacidade_padawan); // Libera o lugar

    sem_wait(&exclusao_mutua); 
        count_padawans_dentro--;
        count_padawans_avaliados++;
    sem_post(&exclusao_mutua); 

    printf("%s - (%d) saiu do salão.\n", nome,id);
}

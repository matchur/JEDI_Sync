#include "ctrl_padawans.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Declaração de variáveis globais compartilhadas
extern int tranca_salao;
extern int count_avaliacao;
extern int count_padawans_dentro;
extern int count_padawans_testados;
extern int count_padawans_avaliados;

// Declaração de semáforos globais
extern sem_t capacidade_padawan;
extern sem_t avaliacao_padawan;
extern sem_t cumprimentar_mestres;
extern sem_t corte_tranca;
extern sem_t exclusao_mutua;
extern sem_t padawan_ajoelhado;
extern sem_t padawan_espera_avaliacao;
extern sem_t padawan_finalizado;
extern sem_t padawans_prontos;
extern sem_t ajoelhados_sem;
extern sem_t padawans_levantar;
extern sem_t saida_padawans;

// Função para simular a entrada do Padawan no salão
void padawan_entra_salao(int id, const char* nome) {
    printf("%s - (%d) está aguardando para entrar no salão.\n", nome, id);

    // Espera até que o salão esteja aberto
    while (!tranca_salao) {} // Busy wait - Avaliar se necessário

    // Aguarda espaço no salão
    sem_wait(&capacidade_padawan);

    // Incrementa contador de Padawans dentro do salão com exclusão mútua
    sem_wait(&exclusao_mutua);
    count_padawans_dentro++;
    sem_post(&exclusao_mutua);

    printf("%s - (%d) entrou no salão.\n", nome, id);
}

// Função para simular o cumprimento dos Mestres Avaliadores
void cumprimenta_mestres_avaliadores(int id, const char* nome) {
    printf("%s - (%d) está indo cumprimentar os Mestres Avaliadores.\n", nome, id);

    // Exclusão mútua para simular cumprimento sequencial
    sem_wait(&cumprimentar_mestres);

    // Simula o cumprimento de cada Mestre Avaliador
    for (int i = 1; i <= 4; i++) {
        printf("%s - (%d) está cumprimentando o Mestre Avaliador %d.\n", nome, id, i);
        sleep(1);
    }

    sem_post(&cumprimentar_mestres);

    printf("%s - (%d) concluiu o cumprimento aos Mestres Avaliadores.\n", nome, id);
}

// Função para simular a espera pela avaliação
void aguarda_avaliacao(int id, const char* nome) {
    printf("%s - (%d) está aguardando pela avaliação dos Mestres.\n", nome, id);

    // Sinaliza que este Padawan está pronto para a avaliação
    sem_post(&padawan_espera_avaliacao);

    // Aguarda sinal para iniciar a avaliação
    sem_wait(&avaliacao_padawan);

    printf("%s - (%d) recebeu a ordem para iniciar sua avaliação.\n", nome, id);
}

// Função para simular a realização da avaliação
void realiza_avaliacao(int id, const char* nome) {
    printf("%s - (%d) está realizando a avaliação.\n", nome, id);

    // Simula movimentos de avaliação
    sleep(1); printf("ZING!\n");
    sleep(1); printf("SWOOSH!\n");
    sleep(1); printf("BZZZZ!\n");
    printf("%s - (%d) concluiu. Seus movimentos serão avaliados pelos Mestres.\n", nome, id);

    // Sinaliza que este Padawan concluiu a avaliação
    sem_post(&padawan_finalizado); //semaforo para yoda
    sem_post(&padawans_prontos); //semaforo para padawans
}

// Função para aguardar o corte da trança
void aguarda_corte_tranca(int id, const char* nome) {
// Aguarda até que todos os Padawans tenham concluído os testes
    for (int i = 0; i < count_padawans_dentro; i++) {
        sem_wait(&padawans_prontos); // Espera que cada Padawan conclua o teste
    }

    printf("%s - (%d) se aproxima de Yoda, ajoelha, e espera o resultado de sua avaliação.\n", nome, id);

    // Incrementa Padawans ajoelhados
    sem_post(&ajoelhados_sem); // Sinaliza que mais um Padawan está ajoelhado

    // Aguarda a liberação do semáforo para o corte da trança
    sem_wait(&corte_tranca);

    // Simula o resultado do corte da trança
    sleep(2); printf("...");
    srand(time(NULL));
    int resultado = rand() % 2; // Determina se a trança será cortada
    sleep(3);

    if (resultado)
        printf("%s - (%d) Sua trança foi cortada.\n", nome, id);
    else
        printf("%s - (%d) Sua trança não foi cortada.\n", nome, id);

    sem_post(&corte_tranca);

    printf("%s - (%d) se levanta.\n", nome, id);

    // Sinaliza que o Padawan se levantou
    sem_post(&padawans_levantar);
}

// Função para simular o cumprimento de Yoda
void cumprimenta_Yoda(int id, const char* nome) {
    printf("%s - (%d) está cumprimentando Yoda como sinal de respeito.\n", nome, id);
    sleep(2);
    printf("%s - (%d) concluiu o cumprimento a Yoda.\n", nome, id);
}

// Função para simular a saída do Padawan do salão
void padawan_sai_salao(int id, const char* nome) {
    printf("%s - (%d) está saindo do salão.\n", nome, id);

    // Libera lugar no salão
    sem_post(&capacidade_padawan);

    // Atualiza contadores de Padawans no salão e avaliados
    sem_wait(&exclusao_mutua);
    count_padawans_dentro--;
    count_padawans_avaliados++;
    sem_post(&exclusao_mutua);

    // Sinaliza que o Padawan saiu do salão
    sem_post(&saida_padawans);

    printf("%s - (%d) saiu do salão.\n", nome, id);
}
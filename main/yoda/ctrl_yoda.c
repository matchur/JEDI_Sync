/* ==========================================================================
* Descricao: Controle das ações de Yoda no gerenciamento do salão e testes
*
* Autor: Matheus Vinicius Costa e Lucas Dos Santos Vaz
* Data de criacao: 5/12/2024
* Ultima atualizacao: 19/12/2024
* ========================================================================== */
#include "ctrl_yoda.h"
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>

// --------------------------- Extern de Variáveis Globais ---------------------------
extern int tranca_salao;                // Controle de abertura/fechamento do salão
extern int count_padawans_dentro;       // Contador de padawans no salão
extern int count_padawans_ajoelhado;    // Contador de padawans ajoelhados
extern sem_t capacidade_testes;         // Gerencia a capacidade de testes, limitando o número de Padawans que podem ser avaliados simultaneamente
extern sem_t avaliacao_padawan;         // Controle de avaliação dos padawans, sincronizando o início da avaliação de cada Padawan
extern sem_t corte_tranca;              // Controle para cortar a trança, sincroniza a ação de cortar a trança durante o processo
extern sem_t padawan_ajoelhado;         // Sincroniza a ação dos Padawans que precisam ajoelhar antes de iniciar a avaliação
extern sem_t exclusao_mutua;            // Exclusão mútua para variáveis globais, garantindo acesso exclusivo a seções críticas do código
extern sem_t padawans_levantar;         // Sincroniza a ação de levantar após a avaliação, permitindo que os Padawans saiam da posição de ajoelhado
extern sem_t padawan_espera_avaliacao;  // Sincroniza a espera dos Padawans até que a avaliação esteja pronta para começar
extern sem_t padawan_finalizado;        // Sincroniza a conclusão de um Padawan após a avaliação, indicando que ele terminou e pode sair
extern sem_t saida_padawans;            // Controle da saída dos Padawans do salão após finalizarem o processo, sincronizando a liberação do espaço

// --------------------------- Funções ---------------------------

void libera_entrada() {
    printf("Yoda liberou a entrada para o salão.\n");
    sem_wait(&exclusao_mutua);
    tranca_salao = 1; // Abre o salão
    sem_post(&exclusao_mutua);
}

void fecha_entrada() {
    printf("Yoda trancou o salão.\n");
    sem_wait(&exclusao_mutua);
    tranca_salao = 0; // Fecha o salão
    sem_post(&exclusao_mutua);
}

void inicia_testes() {
    // Aguarda que todos os padawans estejam prontos para começar
   
    for (int i = 0; i < count_padawans_dentro; i++) {
        sem_wait(&padawan_espera_avaliacao);
    }   

    // Libera os padawans para a avaliação
    for (int i = 0; i < count_padawans_dentro; i++) {
        sem_post(&avaliacao_padawan);
    }
    printf("Yoda: Que comecem, avaliações!\n");
}

void finaliza_testes() {
    printf("Aguardando a conclusão de todos os testes.\n");

    // Aguarda que todos os Padawans tenham concluído seus testes
    for (int i = 0; i < count_padawans_dentro; i++) {
        sem_wait(&padawan_finalizado); // Aguarda cada Padawan sinalizar a conclusão
    }

    printf("Todos os testes foram concluídos.\n");
}

void corta_tranca() {
    printf("Yoda liga seu sabre de luz e se prepara para cortar tranças.\n");

    // Aguarda que todos os padawans estejam ajoelhados
    for (int i = 0; i < count_padawans_dentro; i++) {
        sem_wait(&padawan_ajoelhado); // Espera por cada padawan se ajoelhar
    }

    // Libera o corte da trança
    sem_post(&corte_tranca);
}

void guarda_sabre() {
    // Aguarda que todos os Padawans tenham se levantado
    for (int i = 0; i < count_padawans_dentro; i++) {
        printf("%d padawans dentro - count: %d",count_padawans_dentro,i);
        sem_wait(&padawans_levantar); // Espera cada Padawan sinalizar que se levantou
    }

    // Guarda o sabre de luz
    printf("Yoda desliga seu sabre de luz.\n");
    sem_wait(&corte_tranca); 
}

void anuncia_resultado() {
    printf("Yoda está anunciando os resultados dos testes.\n");
    //atraso para efeito dramático
    sleep(2);
}

void aguarda_saida() {
    printf("Yoda aguarda que todos os Padawans saiam do salão.\n");

    // Aguarda que todos os Padawans saiam
    for (int i = 0; i < count_padawans_dentro; i++) {
        sem_wait(&saida_padawans); // Aguarda cada Padawan sinalizar que saiu
    }

    printf("Todos os Padawans saíram do salão.\n");
}

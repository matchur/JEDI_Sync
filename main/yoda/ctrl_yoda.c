#include "ctrl_yoda.h"
#include <unistd.h>


// Semáforos para gerenciar o salão e os testes
extern int tranca_salao;  // Tranca/Destranca o salão
extern sem_t capacidade_testes; // Gerencia a capacidade de testes
extern sem_t avaliacao_padawan;
extern int count_avaliacao;

extern int count_padawans_dentro; 
extern int count_padawans_testados; 
extern int count_padawans_ajoelhado;

void libera_entrada() {
    printf("Yoda liberou a entrada para o salão.\n");
    tranca_salao = 1; // abre o salão
}
void fecha_entrada() {
    printf("Yoda Trancou o salão.\n");
    tranca_salao = 0; // fecha o salão
}

void inicia_testes(int max_padawans) {
    //Sincronização, todos os padawans esperam para iniciar a avaliação juntos e somente com o salão trancado
    while(count_avaliacao < count_padawans_dentro && !tranca_salao){} //busy waiting 
    printf("Yoda sinaliza que avaliações comecem.\n");
    for(int i=0;i<max_padawans;i++)
        sem_post(&avaliacao_padawan);
}

void finaliza_testes() {
    while(count_padawans_testados < count_padawans_dentro){} //busy waiting
    printf("Testes finalizados.\n");
}


void corta_tranca() {
    printf("Yoda liga seu sabre de luz, e espera então os avaliados.\n");
    sem_post(&corta_tranca);
}

void guarda_sabre()
{
    printf("Yoda desliga seu sabre de luz.\n");
    wait_post(&corta_tranca);
}
void anuncia_resultado() {
    printf("Yoda está anunciando os resultados dos testes.\n");
    // Talvez guardar em uma variavel quem passou e quem não passou para depois mostrar...?
    sleep(1); // Pausa para o efeito dramático
    printf("Resultados anunciados com sucesso!\n");
}

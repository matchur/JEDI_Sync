#include "ctrl_yoda.h"
#include <unistd.h>


// Semáforos para gerenciar o salão e os testes
extern int tranca_salao;  // Tranca/Destranca o salão
extern sem_t capacidade_testes; // Gerencia a capacidade de testes
extern sem_t avaliacao_padawan;

void inicia_testes(int max_padawans) {
    printf("Yoda sinaliza que avaliações comecem.\n");
    for(int i=0;i<max_padawans;i++)
        sem_post(&avaliacao_padawan);
}

void libera_entrada() {
    printf("Yoda liberou a entrada para o salão.\n");
    tranca_salao = 1; // abre o salão
}

void fecha_entrada() {
    printf("Yoda Trancou o salão.\n");
    tranca_salao = 0; // fecha o salão
}

void anuncia_resultado() {
    printf("Yoda está anunciando os resultados dos testes.\n");
    // Talvez guardar em uma variavel quem passou e quem não passou para depois mostrar...?
    sleep(1); // Pausa para o efeito dramático
    printf("Resultados anunciados com sucesso!\n");
}

void corta_tranca() {
    printf("Yoda está trancando o salão para novos testes.\n");
    //sem_wait(&tranca_salao); // Bloqueia a entrada no salão
    printf("Salão trancado.\n");
}

void finaliza_testes() {
    printf("Yoda está finalizando os testes e encerrando o salão.\n");
    sem_post(&capacidade_testes); // Libera o salão para finalizar os testes
    printf("Testes finalizados com sucesso.\n");
}

#include "ctrl_yoda.h"
#include <unistd.h>


// Semáforos para gerenciar o salão e os testes
extern sem_t tranca_salao;  // Tranca/Destranca o salão
extern sem_t capacidade_testes; // Gerencia a capacidade de testes

void inicia_testes() {
    printf("Yoda está iniciando os testes no salão.\n");
    sem_wait(&capacidade_testes); // Permite que os testes comecem
    printf("Testes iniciados com sucesso.\n");
}

void libera_entrada() {
    printf("Yoda liberou a entrada para o salão.\n");
    sem_post(&tranca_salao); // Libera a entrada no salão
}

void fecha_entrada() {
    printf("Yoda Trancou o salão.\n");
    sem_wait(&tranca_salao); // Libera a entrada no salão
}

void anuncia_resultado() {
    printf("Yoda está anunciando os resultados dos testes.\n");
    // Simula o anúncio
    sleep(1); // Pausa para o efeito dramático
    printf("Resultados anunciados com sucesso!\n");
}

void corta_tranca() {
    printf("Yoda está trancando o salão para novos testes.\n");
    sem_wait(&tranca_salao); // Bloqueia a entrada no salão
    printf("Salão trancado.\n");
}

void finaliza_testes() {
    printf("Yoda está finalizando os testes e encerrando o salão.\n");
    sem_post(&capacidade_testes); // Libera o salão para finalizar os testes
    printf("Testes finalizados com sucesso.\n");
}

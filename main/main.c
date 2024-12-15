#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "yoda/ctrl_yoda.h"
#include "padawans/ctrl_padawan.h"
#include "spec/ctrl_spec.h"
#include "utils/ctrl_semaforo.h"

// Constantes
#define MESTRES_AVALIADORES 4
#define MIN_PADAWANS 5
#define MAX_PADAWANS 10
#define MIN_ESPECTADORES 10
#define MAX_ESPECTADORES 20
#define MAX_NAME_LENGTH 50
#define MAX_DISCOURSE_LENGTH 500

// Lista dinâmica de nomes e discursos
char** name_list = NULL;
int name_count = 0;
char** speak_list = NULL;
int speak_count = 0;

// Funções para carregar arquivos
void load_names(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir name_list.txt");
        exit(EXIT_FAILURE);
    }

    char line[MAX_NAME_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove o '\n'
        name_list = realloc(name_list, sizeof(char*) * (name_count + 1));
        name_list[name_count] = strdup(line);
        name_count++;
    }
    fclose(file);
}

void load_speeches(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir speak_list.txt");
        exit(EXIT_FAILURE);
    }

    char line[MAX_DISCOURSE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove o '\n'
        speak_list = realloc(speak_list, sizeof(char*) * (speak_count + 1));
        speak_list[speak_count] = strdup(line);
        speak_count++;
    }
    fclose(file);
}

// Seletores aleatórios
const char* get_random_name() {
    return name_list[rand() % name_count];
}

const char* get_random_speech() {
    return speak_list[rand() % speak_count];
}

// Estrutura de dados para threads
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
} ThreadData;

// Funções para threads
void* thread_padawan(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    entra_salao(data->id, data->name);
    cumprimenta_mestres_avaliadores(data->id, data->name);
    aguarda_avaliacao(data->id, data->name);
    realiza_avaliacao(data->id, data->name);
    aguarda_corte_tranca(data->id, data->name);
    cumprimenta_Yoda(data->id, data->name);
    sai_salao(data->id, data->name);
    free(data); // Libera memória alocada
    return NULL;
}

void* thread_espectador(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    entra_salao(data->id, data->name);
    assiste_testes(data->id, data->name);
    sai_salao(data->id, data->name);
    free(data); // Libera memória alocada
    return NULL;
}

// Função principal
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Carregar arquivos de nomes e discursos
    load_names("utils/name_list.txt");
    load_speeches("utils/speak_list.txt");

    // Inicialização de variáveis
    int num_padawans = rand() % (MAX_PADAWANS - MIN_PADAWANS + 1) + MIN_PADAWANS;
    int num_espectadores = rand() % (MAX_ESPECTADORES - MIN_ESPECTADORES + 1) + MIN_ESPECTADORES;

    printf("Mestre Yoda inicia a avaliação Jedi!\n");
    printf("Quantidade de Padawans: %d\n", num_padawans);
    printf("Quantidade de Espectadores: %d\n", num_espectadores);

    // Inicializa semáforos com os limites definidos
    inicializa_semaforos(num_espectadores, 1); // Máximo de espectadores e acesso de um Padawan por vez

    // Inicialização de threads
    pthread_t padawan_threads[num_padawans];
    pthread_t espectador_threads[num_espectadores];

    // Yoda inicia os testes
    inicia_testes();

    // Cria threads para os Padawans
    for (int i = 0; i < num_padawans; i++) {
        ThreadData* data = malloc(sizeof(ThreadData));
        data->id = i + 1;
        strncpy(data->name, get_random_name(), MAX_NAME_LENGTH);
        pthread_create(&padawan_threads[i], NULL, thread_padawan, data);
        usleep(rand() % 500000); // Simula chegada aleatória
    }

    // Cria threads para os Espectadores
    for (int i = 0; i < num_espectadores; i++) {
        ThreadData* data = malloc(sizeof(ThreadData));
        data->id = i + 1;
        strncpy(data->name, get_random_name(), MAX_NAME_LENGTH);
        pthread_create(&espectador_threads[i], NULL, thread_espectador, data);
        usleep(rand() % 500000); // Simula chegada aleatória
    }

    // Aguarda a finalização das threads dos Padawans
    for (int i = 0; i < num_padawans; i++) {
        pthread_join(padawan_threads[i], NULL);
    }

    // Libera a entrada para espectadores saírem
    libera_entrada();
    anuncia_resultado();

    // Aguarda a finalização das threads dos Espectadores
    for (int i = 0; i < num_espectadores; i++) {
        pthread_join(espectador_threads[i], NULL);
    }

    corta_tranca(); // Yoda realiza os cortes das tranças dos aprovados

    // Yoda faz um discurso aleatório
    printf("\nYoda: %s\n\n", get_random_speech());

    finaliza_testes(); // Finaliza os testes para esta sessão

    printf("A todos os participantes, Parabéns.\n");

    // Destroi semáforos
    destroi_semaforos();

    // Libera listas carregadas
    for (int i = 0; i < name_count; i++) free(name_list[i]);
    free(name_list);
    for (int i = 0; i < speak_count; i++) free(speak_list[i]);
    free(speak_list);

    return 0;
}
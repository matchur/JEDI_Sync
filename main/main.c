#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include "yoda/ctrl_yoda.h"
#include "padawans/ctrl_padawans.h"
#include "spec/ctrl_spec.h"
#include "utils/ctrl_semaforo.h"

// Constantes
#define MESTRES_AVALIADORES 4 // Placeholder para expansão futura
#define PLACE_PADAWANS 3
#define PLACE_SPECS 8
#define MIN_PADAWANS 3
#define MAX_PADAWANS 7
#define MIN_ESPECTADORES 5
#define MAX_ESPECTADORES 10
#define MAX_NAME_LENGTH 60
#define MAX_DISCOURSE_LENGTH 700

// Variáveis externas de controle
extern int count_avaliacao;
extern int count_padawans_dentro;
extern int count_padawans_avaliados;
extern int tranca_salao;

// Listas dinâmicas de nomes e discursos
char **name_list = NULL;
int name_count = 0;
char **speak_list = NULL;
int speak_count = 0;

// Funções para carregar arquivos
void load_names(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir name_list.txt");
        exit(EXIT_FAILURE);
    }

    char line[MAX_NAME_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove o '\n'
        name_list = realloc(name_list, sizeof(char *) * (name_count + 1));
        name_list[name_count] = strdup(line);
        name_count++;
    }
    fclose(file);
}

void load_speeches(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erro ao abrir speak_list.txt");
        exit(EXIT_FAILURE);
    }

    char line[MAX_DISCOURSE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0'; // Remove o '\n'
        speak_list = realloc(speak_list, sizeof(char *) * (speak_count + 1));
        speak_list[speak_count] = strdup(line);
        speak_count++;
    }
    fclose(file);
}

// Seletores aleatórios
const char *get_random_name() {
    srand(time(NULL));
    return name_list[rand() % name_count];
}

const char *get_random_speech() {
    return speak_list[rand() % speak_count];
}

// Estruturas de dados
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
} ThreadData;

typedef struct {
    int contagem_padawan;
} YodaInfo;

// Funções para threads
void *thread_padawan(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    padawan_entra_salao(data->id, data->name);
    cumprimenta_mestres_avaliadores(data->id, data->name);
    aguarda_avaliacao(data->id, data->name);
    realiza_avaliacao(data->id, data->name);
    aguarda_corte_tranca(data->id, data->name);
    cumprimenta_Yoda(data->id, data->name);
    padawan_sai_salao(data->id, data->name);
    free(data); // Libera memória alocada
    return NULL;
}

void *thread_Yoda(void *arg) {
    YodaInfo *data = (YodaInfo *)arg;
    while (count_padawans_avaliados < data->contagem_padawan) {
        libera_entrada();
        sleep(rand() % 4 + 6); // Intervalo de 6 a 9 segundos
        fecha_entrada();
        inicia_testes();
        finaliza_testes();
        corta_tranca();
        guarda_sabre();
        aguarda_saida();
    }
    anuncia_resultado();
    printf("\nYoda: %s\n\n", get_random_speech());
    return NULL;
}

void *thread_espectador(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    spec_entra_salao(data->id, data->name);
    assiste_testes(data->id, data->name);
    spec_sai_salao(data->id, data->name);
    free(data); // Libera memória alocada
    return NULL;
}

// Função principal
int main() {
    int num_padawans, num_espectadores;
    char escolha;
    
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Carregar arquivos de nomes e discursos
    load_names("utils/name_list.txt");
    load_speeches("utils/speak_list.txt");

    num_padawans = rand() % (MAX_PADAWANS - MIN_PADAWANS + 1) + MIN_PADAWANS;
    num_espectadores = rand() % (MAX_ESPECTADORES - MIN_ESPECTADORES + 1) + MIN_ESPECTADORES;

    do {
        system("clear");
        printf("                                                                  \n");
        printf("     ██╗███████╗██████╗ ██╗    ███████╗██╗   ██╗███╗   ██╗ ██████╗\n");
        printf("     ██║██╔════╝██╔══██╗██║    ██╔════╝╚██╗ ██╔╝████╗  ██║██╔════╝\n");
        printf("     ██║█████╗  ██║  ██║██║    ███████╗ ╚████╔╝ ██╔██╗ ██║██║     \n");
        printf("██   ██║██╔══╝  ██║  ██║██║    ╚════██║  ╚██╔╝  ██║╚██╗██║██║     \n");
        printf("╚█████╔╝███████╗██████╔╝██║    ███████║   ██║   ██║ ╚████║╚██████╗\n");
        printf(" ╚════╝ ╚══════╝╚═════╝ ╚═╝    ╚══════╝   ╚═╝   ╚═╝  ╚═══╝ ╚═════╝\n");
        printf("                                                                  \n");
        printf("---- Configuração da Cerimônia ----\n");
        printf("Quantidade de Padawans: %d\n", num_padawans);
        printf("Quantidade de Espectadores: %d\n", num_espectadores);
        printf("\n---- Escolha uma opção ----\n");
        printf("[C] - Dar início à cerimônia\n");
        printf("[R] - Randomizar novamente os valores\n");
        printf("[M] - Inserir valores manualmente\n");
        printf("[X] - Sair do programa\n");
        printf("> ");
        scanf(" %c", &escolha);
        escolha = toupper(escolha);
        switch (escolha) {
            case 'R':
                num_padawans = rand() % (MAX_PADAWANS - MIN_PADAWANS + 1) + MIN_PADAWANS;
                num_espectadores = rand() % (MAX_ESPECTADORES - MIN_ESPECTADORES + 1) + MIN_ESPECTADORES;
                break;
            case 'M':
                printf("Insira a quantidade de Padawans (mínimo %d, máximo %d): ", MIN_PADAWANS, MAX_PADAWANS);
                scanf("%d", &num_padawans);
                printf("Insira a quantidade de Espectadores (mínimo %d, máximo %d): ", MIN_ESPECTADORES, MAX_ESPECTADORES);
                scanf("%d", &num_espectadores);
                break;
            case 'C':
                printf("Dando início à cerimônia...\n");
                break;
            case 'X':
                printf("Saindo do programa. Que a força esteja com você!\n");
                exit(EXIT_SUCCESS);
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (escolha != 'C');

    inicializa_semaforos(num_espectadores, num_padawans);

    pthread_t yoda_thread;
    pthread_t espectador_threads[num_espectadores];
    pthread_t padawan_threads[num_padawans];

    YodaInfo *y_dados = malloc(sizeof(YodaInfo));
    y_dados->contagem_padawan = num_padawans;
    pthread_create(&yoda_thread, NULL, thread_Yoda, y_dados);

    for (int i = 0; i < num_padawans; i++) {
        ThreadData *data = malloc(sizeof(ThreadData));
        data->id = i + 1;
        strncpy(data->name, get_random_name(), MAX_NAME_LENGTH);
        pthread_create(&padawan_threads[i], NULL, thread_padawan, data);
        usleep(rand() % 500000);
    }

    for (int i = 0; i < num_padawans; i++) {
        pthread_join(padawan_threads[i], NULL);
    }

    pthread_join(yoda_thread, NULL);

    for (int i = 0; i < num_espectadores; i++) {
        ThreadData *data = malloc(sizeof(ThreadData));
        data->id = i + 1;
        strncpy(data->name, get_random_name(), MAX_NAME_LENGTH);
        pthread_create(&espectador_threads[i], NULL, thread_espectador, data); 
        usleep(500000); // Pausa 500ms
    }

    for (int i = 0; i < num_espectadores; i++) {
        pthread_join(espectador_threads[i], NULL);
    }

    while(count_padawans_avaliados < num_padawans){}
    destroi_semaforos();

    for (int i = 0; i < name_count; i++) free(name_list[i]);
    free(name_list);
    for (int i = 0; i < speak_count; i++) free(speak_list[i]);
    free(speak_list);

    return 0;
}

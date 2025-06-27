//Tarefa 06 - Sincronização de Processos
//Descrição: Implemente a solução de lock mutex para uma aplicação qualquer.
// Inclui a biblioteca padrão de entrada e saída (printf)
#include <stdio.h>

// Inclui a biblioteca para manipulação de threads (pthread_create, pthread_join, mutex)
#include <pthread.h>

// Inclui funções do sistema Unix, como sleep (não usada diretamente aqui, mas comum em aplicações com threads)
#include <unistd.h>

// Define o número de threads e o número de incrementos por thread
#define NUM_THREADS 5
#define NUM_INCREMENTS 100000

// Variável global que será acessada pelas threads (recurso compartilhado)
int contador = 0;

// Declaração do mutex que será usado para proteger a variável compartilhada
pthread_mutex_t lock;

// Função que cada thread irá executar
void* incrementa_contador(void* arg) {
    // Cada thread irá incrementar o contador várias vezes
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        pthread_mutex_lock(&lock);    // Trava o mutex para entrar na região crítica (evita acesso simultâneo)
        contador++;                   // Região crítica: acessa/modifica a variável global
        pthread_mutex_unlock(&lock);  // Destrava o mutex ao sair da região crítica
    }

    return NULL;
}

int main() {
    // Declara um vetor de threads
    pthread_t threads[NUM_THREADS];

    // Inicializa o mutex antes do uso
    pthread_mutex_init(&lock, NULL);

    // Criação das threads
    for (int i = 0; i < NUM_THREADS; i++) {
        // Cada thread executa a função incrementa_contador
        pthread_create(&threads[i], NULL, incrementa_contador, NULL);
    }

    // Aguarda todas as threads terminarem a execução
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Exibe o valor final da variável compartilhada
    printf("Valor final do contador: %d\n", contador);

    // Destroi o mutex e libera recursos associados a ele
    pthread_mutex_destroy(&lock);

    return 0;
}
// Compilar com: gcc -o lockmutex lockmutex.c -lpthread
// Executar com: ./lockmutex


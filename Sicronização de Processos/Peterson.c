#include <stdio.h>
#include <windows.h>
#include <stdbool.h>

// Definições
#define NUM_ITERACOES 10000

// Variáveis de controle
volatile int contador = 0;
volatile bool flag[2] = { false, false };
volatile int turno = 0;

// Função para entrada na seção crítica
void entrar_secao_critica(int self) {
    int outro = 1 - self;
    flag[self] = true;
    turno = outro;
    while (flag[outro] && turno == outro) {
        // Espera ocupada
        Sleep(0); // cede o tempo de CPU
    }
}

// Função para saída da seção crítica
void sair_secao_critica(int self) {
    flag[self] = false;
}

// Função executada pelas threads
DWORD WINAPI thread_func(LPVOID param) {
    int id = *((int *)param);

    for (int i = 0; i < NUM_ITERACOES; i++) {
        entrar_secao_critica(id);

        // Seção crítica
        contador++;

        sair_secao_critica(id);
    }

    return 0;
}

int main() {
    HANDLE threads[2];
    int ids[2] = {0, 1};

    threads[0] = CreateThread(NULL, 0, thread_func, &ids[0], 0, NULL);
    threads[1] = CreateThread(NULL, 0, thread_func, &ids[1], 0, NULL);

    // Aguarda as threads terminarem
    WaitForMultipleObjects(2, threads, TRUE, INFINITE);

    // Fecha os handles
    CloseHandle(threads[0]);
    CloseHandle(threads[1]);

    printf("Valor final do contador: %d\n", contador);
    return 0;
}
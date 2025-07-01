// Como compilar: gcc Semáforos.c -o main.exe

//simulação de um produtor-consumidor com semáforos
#include <stdio.h>
#include <windows.h>

#define TAM_BUFFER 5

int buffer[TAM_BUFFER];
int pos = 0;

// Semáforos e mutex
HANDLE sem_vazio;
HANDLE sem_cheio;
HANDLE mutex;

// Funções do produtor e consumidor
DWORD WINAPI produtor(LPVOID arg) {
    for (int i = 0; i < 10; i++) {
        WaitForSingleObject(sem_vazio, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        buffer[pos++] = i;
        printf("Produtor produziu: %d\n", i);

        ReleaseMutex(mutex);
        ReleaseSemaphore(sem_cheio, 1, NULL);
        Sleep(1000);
    }
    return 0;
}

// Função do consumidor
DWORD WINAPI consumidor(LPVOID arg) {
    for (int i = 0; i < 10; i++) {
        WaitForSingleObject(sem_cheio, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        int item = buffer[--pos];
        printf("Consumidor consumiu: %d\n", item);

        ReleaseMutex(mutex);
        ReleaseSemaphore(sem_vazio, 1, NULL);
        Sleep(2000);
    }
    return 0;
}

// Função principal
int main() {
    HANDLE t_produtor, t_consumidor;

    sem_vazio = CreateSemaphore(NULL, TAM_BUFFER, TAM_BUFFER, NULL);
    sem_cheio = CreateSemaphore(NULL, 0, TAM_BUFFER, NULL);
    mutex = CreateMutex(NULL, FALSE, NULL);

    t_produtor = CreateThread(NULL, 0, produtor, NULL, 0, NULL);
    t_consumidor = CreateThread(NULL, 0, consumidor, NULL, 0, NULL);

    WaitForSingleObject(t_produtor, INFINITE);
    WaitForSingleObject(t_consumidor, INFINITE);

    CloseHandle(sem_vazio);
    CloseHandle(sem_cheio);
    CloseHandle(mutex);
    CloseHandle(t_produtor);
    CloseHandle(t_consumidor);

    return 0;
}
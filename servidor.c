#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET servidor, cliente;
    struct sockaddr_in servidor_addr, cliente_addr;
    int cliente_len = sizeof(cliente_addr);
    char buffer[1024];
    char resposta[1024];

    WSAStartup(MAKEWORD(2, 2), &wsa);

    servidor = socket(AF_INET, SOCK_STREAM, 0);

    servidor_addr.sin_family = AF_INET;
    servidor_addr.sin_addr.s_addr = INADDR_ANY;
    servidor_addr.sin_port = htons(12345);

    bind(servidor, (struct sockaddr *)&servidor_addr, sizeof(servidor_addr));
    listen(servidor, 3);

    printf("Servidor aguardando conexões...\n");

    cliente = accept(servidor, (struct sockaddr *)&cliente_addr, &cliente_len);
    printf("Cliente conectado.\n");

    // Recebe mensagem do cliente
    recv(cliente, buffer, sizeof(buffer), 0);
    printf("- cliente: %s\n", buffer);

    // Servidor digita a resposta
    printf("Digite uma resposta para o cliente: ");
    fgets(resposta, sizeof(resposta), stdin);

    // Envia resposta
    send(cliente, resposta, strlen(resposta), 0);

    closesocket(cliente);
    closesocket(servidor);
    WSACleanup();

    return 0;
}

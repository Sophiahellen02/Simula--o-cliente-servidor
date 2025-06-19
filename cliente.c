#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in servidor_addr;
    char mensagem[1024];
    char buffer[1024] = {0};

    WSAStartup(MAKEWORD(2, 2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    servidor_addr.sin_family = AF_INET;
    servidor_addr.sin_port = htons(12345);
// Usar o endereço IP local para conectar ao servidor
    servidor_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&servidor_addr, sizeof(servidor_addr));
//    printf("Conectado ao servidor.\n");
    printf("Conectado ao servidor.\n");
    printf("Digite uma mensagem para o servidor: ");
    fgets(mensagem, sizeof(mensagem), stdin);

    send(sock, mensagem, strlen(mensagem), 0);

    recv(sock, buffer, sizeof(buffer), 0);
    printf("- servidor: %s\n", buffer);

    closesocket(sock);
    WSACleanup();

    return 0;
}

//
//  Server.c
//  SocketsServer
//
//  Created by Ilya Cherkasov on 16.11.2022.
//

#include "Server.h"
#define PORT 10000
#define BUFF_SIZE 1024

void start_server(void) {
    printf("Server Run!\n");
    int sock;
    struct sockaddr_in server_addr, client_addr;
    ssize_t read_status;
    socklen_t cli_addr_len;
    char buff[BUFF_SIZE] = {0};
    char msg[] = "Server hello!!!\n";

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { //IPPROTO_UDP
        perror("socket creation error");
        exit(-1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if ((bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr))) < 0) {
        perror("binding error");
        close(sock);
        exit(-1);
    }

    cli_addr_len = sizeof(client_addr);
    read_status = recvfrom(sock, buff, BUFF_SIZE, 0, (struct sockaddr*)&client_addr, &cli_addr_len);
    printf("Client said: %s\n", buff);
    if (read_status < 0) {
        perror("reading error");
        close(sock);
        exit(-1);
    }

    if ((sendto(sock, msg, strlen(msg), 0, (struct sockaddr*)&client_addr, cli_addr_len)) < 0) {
        perror("sending error...\n");
        close(sock);
        exit(-1);
    }
    close(sock);
};

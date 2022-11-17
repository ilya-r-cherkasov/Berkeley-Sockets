//
//  Client.c
//  SocketClient
//
//  Created by Ilya Cherkasov on 16.11.2022.
//

#include "Client.h"
#define MY_PORT 8080
#define SERVER_PORT 80
#define BUFF_SIZE 1024 * 4

void make_udp_request(void) {
    printf("Try to say hello!\n");
    int sock;
    ssize_t read_status;
    char msg[] = "Hello!\n", buff[BUFF_SIZE] = {0};
    struct sockaddr_in my_addr, server_addr;
    socklen_t sa_len = sizeof(my_addr);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        perror("cannot create socket");
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MY_PORT);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sock, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1) {
        perror("cannot bind socket");
    };
    if (sendto(sock, msg, strlen(msg), 0, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("send error");
        close(sock);
        exit(-1);
    };
    read_status = recvfrom(sock, buff, BUFF_SIZE, 0, (struct sockaddr*)&my_addr, &sa_len);
    if (read_status < 0) {
        perror("reading error...\n");
        close(sock);
        exit(-1);
    }
    printf("Response: %s\n", buff);
    close(sock);
};

int socket_http_connect(char *host, in_port_t port) {
    struct hostent *hp;
    struct sockaddr_in addr;
    int on = 1, sock;

    if((hp = gethostbyname(host)) == NULL){
        herror("gethostbyname");
        exit(1);
    }
    bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&on, sizeof(int));

    if(sock == -1){
        perror("setsockopt");
        exit(1);
    }

    if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1){
        perror("connect");
        exit(1);

    }
    return sock;
}

void send_http_request(char *host, in_port_t port) {
    int fd;
    char buffer[BUFF_SIZE];
    fd = socket_http_connect(host, port);
    write(fd, "GET /\r\n", strlen("GET /\r\n")); // write(fd, char[]*, len);
    bzero(buffer, BUFF_SIZE);

    while(read(fd, buffer, BUFF_SIZE - 1) != 0){
        fprintf(stderr, "%s", buffer);
        bzero(buffer, BUFF_SIZE);
    }

    shutdown(fd, SHUT_RDWR);
    close(fd);
}

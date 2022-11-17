//
//  http.c
//  SocketClient
//
//  Created by Ilya Cherkasov on 17.11.2022.
//

#include "http.h"
#define BUFF_SIZE 1024

int socket_tcp_connect(char *host, in_port_t port) {
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

    if(connect(sock, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) == -1) {
        perror("connect");
        exit(1);

    }
    return sock;
}

void send_http_request(struct request_params params) {
    int fd; //file descriptor
    char buffer[BUFF_SIZE];
    fd = socket_tcp_connect(params.host, params.port);
    write(fd, params.method, strlen(params.method)); // write(fd, char[]*, len);
    bzero(buffer, BUFF_SIZE);

    while(read(fd, buffer, BUFF_SIZE - 1) != 0) {
        fprintf(stderr, "%s", buffer);
        bzero(buffer, BUFF_SIZE);
    }

    shutdown(fd, SHUT_RDWR);
    close(fd);
}

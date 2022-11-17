//
//  http.h
//  SocketClient
//
//  Created by Ilya Cherkasov on 17.11.2022.
//

#ifndef http_h
#define http_h

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <netinet/tcp.h>
#include <netdb.h>

struct request_params {
    char *host;
    char *method;
    char *path;
    in_port_t port;
};

#endif /* http_h */

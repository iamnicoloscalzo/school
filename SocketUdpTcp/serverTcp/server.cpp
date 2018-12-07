#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../classi/SocketTCP.hpp"
#include "../classi/Address.hpp"
#include "../lib/mylib.h"

#define IP_LOOP "127.0.0.1"
#define PORT 9999
#define BUFSIZE 4096
#define IP_DHCP "0.0.0.0"

int main(int argc, char** argv)
{

    Address mySelf(IP_DHCP, PORT);
    Address client;
    int ret;

    SocketTCP socket(mySelf);

    socket.listenServ(5);
    int client_sock = socket.acceptConnection(&client);

    char* buff = (char *) socket.riceviServer(client_sock);

    printf("From: %s\n", client.getIp());
    printf("server ha ricevuto : %s\n", buff);

    free(buff);

    return 0;
}

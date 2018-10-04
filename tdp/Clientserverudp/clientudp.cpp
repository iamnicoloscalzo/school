#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Address.hpp"
#include "mylib.h"

#define IP_LOOP "127.0.0.1" 
#define PORT 8000
#define BUFSIZE 4096


int main(int argc, char **argv[]) {
    Address server(IP_Loop,PORT);
    struct sockaddr_in addrMyself = mySelf.getSockaddr_in();
    struct sockaddr_in mitt;
    int sockid;
    int serverlen;
    char buf[BUFSIZE+1];
    int ret;

   /* 
   * socket: create
   */
  sockid = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockid < 0) 
    error("ERRORE non sono riuscito ad aprire il socket");
    


   /* Far inserire il messaggio dall'utente */
   bzero(buf, BUFSIZE);
   printf("Inserire il messaggio: ");
   fgets(buf, BUFSIZE, stdin);

   /* Invia il messaggio al server */
   serverlen = sizeof(addrMyself);
   ret = sendto(sockid, buf, strlen(buf), 0, (struct sockaddr *) &addrMyself, serverlen);
   if (ret < 0) 
      error("ERRORE in sendto");
    
   /* Stampa il messaggio ricevuto indietro dal server*/
   ret = recvfrom(sockid, buf, strlen(buf), 0,(struct sockaddr *) &addrMyself, (socklen_t *) &serverlen);
   if (ret < 0) 
     error("ERRORE in recvfrom");
   printf("Echo da server: %s", buf);
   return 0;
   close(sockid);
}

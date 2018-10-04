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

#define IP_DHCP "0.0.0.0" 
#define PORT_ZERO 0
#define BUFSIZE 4096



int main(int argc, char **argv) {
    Address mySelf(IP_DHCP,PORT_ZERO);
    struct sockaddr_in addrMyself = mySelf.getSockaddr_in();
    struct sockaddr_in mitt;
    int sockid;
    int serverlen;
    char buf[BUFSIZE+1];
    int clientlen;
    int ret;
    char *hostaddrp;
    struct hostent *hostinfo; /* struttura per avere informazioni sul client host  */

   /* 
   * socket: create
   */
  sockid = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockid < 0) 
    error("ERRORE non sono riuscito ad aprire il socket");
    
  /* 
   * bind
   */
  if (bind(sockid, (struct sockaddr *) &addrMyself, 
	   sizeof(addrMyself)) < 0) 
    error("ERRORE non sono riuscito in binding");
   


while (1) {

    /*
     * recvfrom: receive a UDP datagram from a client
     */
    bzero(buf, BUFSIZE+1);
    ret = recvfrom(sockid, buf, BUFSIZE, 0,
		 (struct sockaddr *) &mitt, (socklen_t *) &clientlen);
    if (ret < 0)
      error("ERRORE in recvfrom");

    /* 
     * gethostbyaddr: determino chi ha inviato il pacchhetto (datagramma)
     */
    hostinfo = gethostbyaddr((const char *)&mitt.sin_addr.s_addr, 
			  sizeof(mitt.sin_addr.s_addr), AF_INET);
    if (hostinfo == NULL)
      error("ERRORE in gethostbyaddr");
    hostaddrp = inet_ntoa(mitt.sin_addr);
    if (hostaddrp == NULL)
      error("ERRORE on inet_ntoa\n");
    printf("server ha ricevuto il messaggio da %s (%s)\n", 
	   hostinfo->h_name, hostaddrp);
    printf("server ha ricevuto %d/%d bytes: %s\n", strlen(buf), ret, buf);
    
    /* 
     * sendto
     */
    ret = sendto(sockid, buf, strlen(buf), 0, 
	       (struct sockaddr *) &mitt, clientlen);
    if (ret < 0) 
      error("ERROR in sendto");
  }
    close(sockid);
}

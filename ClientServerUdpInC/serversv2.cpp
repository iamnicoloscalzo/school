#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../classi/SocketUDP.hpp"
#include "../classi/Address.hpp"
#include "../lib/mylib.h"

#define IP_LOOP "127.0.0.1" 
#define PORT 9999
#define BUFSIZE 4096
#define IP_DHCP "0.0.0.0"



int main(int argc, char **argv) {

    Address mySelf(IP_DHCP,PORT);
    Address addr;




     SocketUDP socket(mySelf);
      
     char* buff= socket.ricevi(addr);
	 printf("im here : %s\n",buff);
     bool ret= socket.invia(addr,buff);
     
  
    return 0;
}

/*
 * Client.c
 *
 *  Created on: 05/03/2015
 *      Author: nikox
 */

/*
 * Cliente.c
 *
 *  Created on: 05/03/2015
 *      Author: nikox
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PuertoX 34032
#define IpX "127.0.0.1"

int open_Socket(){
	int sock;
	sock=socket(AF_INET,SOCK_STREAM,0);
	return sock;
}

void Configure_Sockaddr(unsigned short port,char* ip,struct sockaddr_in* dest_addr){
	dest_addr->sin_family=AF_INET;
	dest_addr->sin_port=htons(port);
	dest_addr->sin_addr.s_addr=inet_addr(ip);
		memset(&(dest_addr->sin_zero),'\0',8);
}


int main(void) {
	int client=open_Socket();
	struct sockaddr_in dest_addr;
	char * pregunta="Todo Bien?" ;
	char respuesta[255];

	if(client!=1)
	{
			Configure_Sockaddr(PuertoX,IpX,&dest_addr);
			connect(client,(struct sockaddr *)&dest_addr,sizeof(struct sockaddr));
			send(client,pregunta,strlen(pregunta)+1,0);
		//	recv(client,respuesta, sizeof(respuesta) ,0);
		//	printf("%s",respuesta);
			printf("Termino");
			close(client);
	}
	else
	{
		return -1;
	}

return 0;
}

/*
 * Server.c
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
		memset(dest_addr->sin_zero,'\0',8);
}


int main(void) {
	int listener=open_Socket();
	int mailman;
	socklen_t longitud_cliente;
	struct sockaddr_in server ,client;
	char buf[255];
	socklen_t lonsitud_server=sizeof(server);

	if(listener!=-1)
	{
		Configure_Sockaddr(PuertoX,IpX,&server);

			if(bind(listener,(struct sockaddr*)&server, lonsitud_server)!=-1)
			{
				if(listen(listener,5) !=-1)
				{
					printf("Esperando por el saludo....\n");
					longitud_cliente= sizeof(struct sockaddr_in);
					 mailman = accept(listener,(struct sockaddr*)&client,&longitud_cliente);

					 if (mailman !=-1)
					 {
						 while (1){

							 recv(mailman,buf,1024,0);
							 printf("%s\n",buf);
							 break;
						 }
					 }else close(mailman);
				}
			}
	}

close(listener);


return 0;
}

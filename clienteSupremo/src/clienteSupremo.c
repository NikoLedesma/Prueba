/*
 ============================================================================
 Name        : clienteSupremo.c
 Author      : Niko
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#define  _PuertoServer 34032
#define  _IpServer "127.0.0.1"



int open_Socket(){
	int sock=socket(PF_INET,SOCK_STREAM,0);
	return sock;
}

void configure_Sockaddr_In(unsigned short puerto, char* ip , struct sockaddr_in* dest_addr){
	dest_addr->sin_family=AF_INET;
	dest_addr->sin_port=htons(puerto);
	dest_addr->sin_addr.s_addr=inet_addr(ip);
	memset(dest_addr->sin_zero,'\0',8);
}

int main(void) {
	int client_sock=open_Socket();
	struct sockaddr_in dest_addr;
	char pregunta[255];

	if(client_sock==-1){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	else{
					configure_Sockaddr_In(_PuertoServer,_IpServer,&dest_addr);


					if(connect(client_sock,(struct sockaddr *)&dest_addr,sizeof(struct sockaddr))==-1)
					{
						perror("connect");
						exit( EXIT_FAILURE);
					}


					do
					{

					printf("Ingrese lo que le quiere enviar al servidor\n");
					scanf("%s",pregunta);//fgets (pregunta, 255, stdin);


					send(client_sock,pregunta,strlen(pregunta)+1,0);
				//	recv(client,respuesta, sizeof(respuesta) ,0);
				//	printf("%s",respuesta);
					printf("Ya envio el dato\n");

					}
					while(strcmp(pregunta,"cerrar server"));

					close(client_sock);
	}





	return EXIT_SUCCESS;
}

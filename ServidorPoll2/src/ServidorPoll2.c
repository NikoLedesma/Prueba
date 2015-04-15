/*
 ============================================================================
 Name        : ServidorPoll2.c
 Author      : Niko
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <poll.h>
#include <sys/poll.h>
#include <sys/time.h>

#define  _PuertoServer 34032
#define  _IpServer "127.0.0.1"

int open_socket(void){
	int sock=socket(PF_INET,SOCK_STREAM,0);
	return sock;
}

void configure_Sockaddr_In(unsigned short puerto, char* ip,struct sockaddr_in * dest_addr){
	dest_addr->sin_family=AF_INET;
	dest_addr->sin_port=htons(puerto);
	dest_addr->sin_addr.s_addr=inet_addr(ip);
	memset(dest_addr->sin_zero,'\0',8);
}

//blab
int main(void) {
	struct sockaddr_in serverADDR,clientADDR;
	int sock_server;
	struct pollfd ufds[3],master[3];///voy a estar recibiendo datos de 9 clientes (como mucho) + 1 servidor
	nfds_t nfds; //numero de files descriptors
	socklen_t longServerADDR=sizeof(serverADDR);
	socklen_t longClientADDR= sizeof(clientADDR);
	sock_server=open_socket();
	configure_Sockaddr_In(_PuertoServer,_IpServer,&serverADDR);
	if(sock_server==-1)
	{
		perror("open_socket");
		exit(EXIT_FAILURE);
	}
	if(bind(sock_server,(struct sockaddr*)&serverADDR,longServerADDR)==-1){
		perror("bind");
		exit(EXIT_FAILURE);
	}
	if(listen(sock_server,10)==-1){
		perror("listen");
		exit (EXIT_FAILURE);
	}

	/* Agregarmos el servidor al array de estructura poll*/
	nfds=0;
	master[nfds].fd=sock_server;
	master[nfds].events=POLLIN ;
	master[nfds].revents=0;
	while(1)
	{	int i,pollResault;
		memcpy(ufds, master, (nfds+1)*sizeof(struct pollfd));
		printf("esperamos por un cliente\n");
		pollResault=poll(ufds,(nfds_t) (nfds+1),-1);//me devuelve la cantidad de descriptores que tuvieron eventos

		if(pollResault==-1)///poniendo un negativo en _timeout esperamos haste que ocurra algun evento
		{
			perror("poll");
			exit(EXIT_FAILURE);
		}
		printf("Se encontraron eventos en %d descriptores\n", pollResault);
		for(i=0;i<(nfds+1);++i){
			if(ufds[i].revents & POLLIN ){
				if(i == 0){//se conecta un nuevo cliente
					int sock_talk=accept(sock_server,(struct sockaddr*)&clientADDR,&longClientADDR);
					if(sock_talk==-1){
					perror("accept");
					exit (EXIT_FAILURE);
					}
					master[++nfds].fd=sock_talk;//primero se incrementa nfds y luego se guarda el socket
					master[nfds].events=POLLIN	;
					master[nfds].revents=0;
					printf("Se conecto un nuevo cliente:%d y la cantidad es de %d\n",master[nfds].fd,(int)nfds);
					}
					else{
						char buff [200];
						if(recv(ufds[i].fd,buff,200,0)==-1)
						{
						perror("recv");
						exit(EXIT_FAILURE);
						}
						printf("Lo que se recibio fue:%s\n",buff);
					}
				}///fin del if que pregunta por cada evento
			}///fin for

	}///fin while
	return EXIT_SUCCESS;
}

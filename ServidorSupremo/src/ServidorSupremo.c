/*
 ============================================================================
 Name        : ServidorSupremo.c
 Author      : Niko
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

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
#define cantClientes 10

int mySock_Server;
int maxDescriptor;
fd_set descriptoresLectura;
int numClientes_Conectados;



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


void ordenar_MayorAMenor(int *X)
{
	int i,j,aux;
	for (i=0;i<cantClientes;++i)
	{	for(j=0;j<cantClientes-1;++j)
		{	if(X[j]<X[j+1])
			{
			aux=X[j+1];
			X[j+1]=X[j];
			X[j]=aux;
			}
		}
	}
}


int fetch_LugarParaCliente(int *clientes){
	int i;
	for(i=0;i<3;i++)
	{
		if(clientes[i]==0)
		{

		return i;}
	}
	return -1;
}

void tratar_RecepcionDeDatos(int cantRecibida,int * clientes,int index,char * buff){
	switch(cantRecibida)
						{
						case -1:
							perror("recv");
						break;
						case 0:
							/*tratar_DesconexionDeCliente(clientes,index);*/
							printf("Se desconecto el cliente\n");
								close(clientes[index]);////cerramos el socket del cliente el cual aceptamos la conexion
								clientes[index]=0;
								ordenar_MayorAMenor(clientes);///Ordenamos de mayor a menor
								if(clientes[0]>mySock_Server)   ///Comparamos para setear el maximoDescriptor
									maxDescriptor=clientes[0];	///Comparamos con el subindice Cero ya que el array se ordena
								else maxDescriptor=mySock_Server;
						numClientes_Conectados--;///decrementamos el numero de clientes
						break;
						default://En este caso se recibe perfectamente
							printf("Se recibio una cantidad de:%d\n",cantRecibida);
							printf("Los datos Recibidos son:%s\n",buff);
						}

}







/*Tener en cuenta que se inicia el array con 0
 * lo cual significa que si me indica un cero no
 * hay descriptor de cliente*/




int main(void) {
	int i;
	int sock_Clientes[3]={0,0,0};
	char buff[255]="BASURA";
	struct sockaddr_in serverADDR,clientADDR;

	mySock_Server=open_Socket();
	if(mySock_Server==-1){
		perror("socket");
		exit(EXIT_FAILURE);
	}
	configure_Sockaddr_In(_PuertoServer,_IpServer,&serverADDR);
	//struct sockaddr_in serverADDR,clientADDR;

	if(bind(mySock_Server,(struct sockaddr*)&serverADDR,sizeof(serverADDR))==-1){
				perror("bind");
				exit(EXIT_FAILURE);
	}

	if(listen(mySock_Server,5)==-1){
		perror("listen");
		exit(EXIT_FAILURE);
	}


	socklen_t longitud_cliente= sizeof(struct sockaddr_in);
	//mailman = accept(mySock_Server,(struct sockaddr*)&clientADDR,&longitud_cliente);



		numClientes_Conectados=0;


		while(1){

			//Inicializamos los *descriptores de lectura
			FD_ZERO (&descriptoresLectura);
			FD_SET (mySock_Server, &descriptoresLectura);
			for(i=0;i<numClientes_Conectados ;i++)
				FD_SET (sock_Clientes[i], &descriptoresLectura);

			//Buscamos el fichero mas grande
			maxDescriptor=mySock_Server;
			for(i=0;i<numClientes_Conectados ;i++)
			{
				if(maxDescriptor<sock_Clientes[i])
					maxDescriptor=sock_Clientes[i];
			}


		select (maxDescriptor+1, &descriptoresLectura, NULL, NULL, NULL);//al poner Null en el ultimo parametro de select//se enclava hasta que pase algo
																		 //si salio del select se produjo un evento
		////Preguntamos si sucedio algo en algun fichero de algun cliente y tratamos
		for(i=0;i<numClientes_Conectados;++i)
		{
			if(FD_ISSET(sock_Clientes[i],&descriptoresLectura))
			{
				int cantRecibida;
				cantRecibida =recv(sock_Clientes[i],buff,200,0);
				tratar_RecepcionDeDatos(cantRecibida,sock_Clientes,i,buff);
			}
		}
		/*Preguntamos si sucedio algo en el fichero del server y tratamos*/
		if(FD_ISSET(mySock_Server,&descriptoresLectura))
		{
				int index= fetch_LugarParaCliente(sock_Clientes);////devuelve el indice en el que se puede guardar
				printf("El index es %d\n",index);
				sock_Clientes[index]=accept(mySock_Server,(struct sockaddr*)&clientADDR,&longitud_cliente);
				maxDescriptor=sock_Clientes[index];
				numClientes_Conectados++;
				printf("se realizo una nueva conexión, la cantidad de clientes conectados es %d\n",numClientes_Conectados);
		}
	}
	close(mySock_Server);//Cerramos el descriptor server
	return 0;
}

/*
 ============================================================================
 Name        : ServerSupremo.c
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
#define ClientesTotales 2
#define  _PuertoServer 34032
#define  _IpServer "127.0.0.1"


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
	for (i=0;i<numClientes_Conectados;++i)
	{	for(j=0;j<numClientes_Conectados-1;++j)
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
	for(i=0;i<ClientesTotales;i++)
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
	int sock_Clientes[2]={0,0};
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


		FD_ZERO (&descriptoresLectura);
		FD_SET (mySock_Server, &descriptoresLectura);
		numClientes_Conectados=0;
		maxDescriptor=mySock_Server;
		while(strcmp(buff ,"cerrar server")){

			printf("clientes conectados %d\n",numClientes_Conectados);
		//El primer parametro lleva el (descriptor mayor) +1
		select (maxDescriptor+1, &descriptoresLectura, NULL, NULL, NULL);//al poner Null en el ultimo parametro de select
		/*iteramos todos los clientes conectados en el array				//se enclava hasta que pase algo
		 * preguntando si sucedio algo en alguno de ellos, en tal caso
		 * trataremos el descriptor*/
		//Dese cuenta que si no hay clientes no se entra en el for
		for(i=0;i<numClientes_Conectados;++i)
		{
			if(FD_ISSET(sock_Clientes[i],&descriptoresLectura))
			{
				int cantRecibida;
				cantRecibida =recv(sock_Clientes[i],buff,200,0);
				tratar_RecepcionDeDatos(cantRecibida,sock_Clientes,i,buff);
			}
		}
		printf("salio del for");

/*Preguntamos si  en mySock_server sucedio algo en tal caso me de el
 * indicio de que es una nueva conexion a aceptar*/

		if(FD_ISSET(mySock_Server,&descriptoresLectura))
		{
		printf("se quiere realizar una nueva conexion\n");

				int index= fetch_LugarParaCliente(sock_Clientes);////devuelve el indice en el que se puede guardar
				sock_Clientes[index]=accept(mySock_Server,(struct sockaddr*)&clientADDR,&longitud_cliente);
				printf("El lugar vacio es %d\n",index);
				maxDescriptor=sock_Clientes[index];
				numClientes_Conectados++;
				FD_SET (sock_Clientes[index], &descriptoresLectura);//agrego el descriptor
				printf("El numero del descriptor del cliente es %d y del servidor %d, numero de clientes conectados %d\n",sock_Clientes[index],mySock_Server,numClientes_Conectados);

		printf("se acepto la conexion\n");
		}


	} //supuestamente si es igual devuelve un cero(negativo)
	close(mySock_Server);//Cerramos el descriptor server
	return 0;
}

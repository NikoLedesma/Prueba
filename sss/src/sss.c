/*
 ============================================================================
 Name        : sss.c
 Author      : Niko
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void ordenar_MayorAMenor(int *X)
{
	int i,j,aux;
	for (i=0;i<10;++i)
	{	for(j=0;j<9;++j)
		{	if(X[j]<X[j+1])
			{
			aux=X[j+1];
			X[j+1]=X[j];
			X[j]=aux;
			}
		}
	}
}


int main(void) {

	int i;
	int X[10]={1,4,3,2,53,1,14,157,13,132};
	int clientes[2]={0,0};

	for (i=0;i<10;++i){

	printf("la iteracion es la numero:%d\n",i);
	printf("El contenido sin inicializar es %d\n", X[i]);
	}



	for(i=0;i<2;++i)
		{
				printf("Entro al for");
			if(clientes[i]==0){
				printf("el cliente es %d\n",i);

				}
			}




printf("\n\n");
ordenar_MayorAMenor(X);

for (i=0;i<10;++i){

printf("El contenido sin inicializar es %d   en pos %d\n", X[i],i);
}

char buffer[40];
char * res;
printf("Ingrese una palabra\n");
scanf("%s",buffer);
strcpy(res,buffer);
printf("Lo que escribiste fue %s y tiene %d palabras\n",res,(int)strlen(buffer));

	return EXIT_SUCCESS;
}

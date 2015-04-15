/*
 ============================================================================
 Name        : Descriptores.c
 Author      : Niko
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <poll.h>
#include <sys/poll.h>
#include <string.h>


typedef struct persona{
	char* nombre;
	char* apellido;
	int telefono;
}Persona;


typedef struct lista{
		Persona unaPersona;
		struct lista *siguiente;
}listPersonas;

void ingresoDatosXPersona(Persona* unaPersona){
char dato[20];

printf("Ingrese el nombre de la persona:\n");
scanf("%s",dato);
strcpy(unaPersona->nombre,dato);
printf("Ingrese el apellido de la persona:\n");
scanf("%s",dato);
strcpy(unaPersona->apellido,dato);
printf("Ingrese el numero de la persona:\n");
scanf("%d",&(unaPersona->telefono));


}

int main(void) {

	Persona* personaX;
	personaX= (Persona*) malloc(sizeof(Persona)*1);
	personaX->nombre =(char*) malloc(sizeof(char)*20);
	personaX->apellido =(char*) malloc(sizeof(char)*20);

	ingresoDatosXPersona( personaX);

	printf("Nombre:%s\n",personaX->nombre);
	printf("Apellido:%s\n",personaX->apellido);
	printf("Telefono:%d\n",personaX->telefono);
	free(personaX->nombre);
	free(personaX->apellido);
	free(personaX);
	return 0;
}

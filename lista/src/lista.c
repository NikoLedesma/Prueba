/*
 ============================================================================
 Name        : lista.c
 Author      : Niko
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


typedef struct _agenda{
	char nombre[20];
	char telefono[12];
	struct _agenda *siguiente;
}Agenda;

Agenda *primero,*ultimo;


void mostrar_menu(){
	printf("\n\nMenu:\n=====\n\n");
	printf("1.-Aniadir elementos\n");
	printf("2.-Borrar elementos");
	printf("3.-Mostrar lista\n");
	printf("4.-Salir\n\n");
	printf("Escoge una opcion:");
	fflush(stdout);

}



void aniadir_elemento(){
	Agenda *nuevo;
	nuevo =(Agenda *) malloc(sizeof(Agenda));
	if (nuevo==NULL)printf("No hay memoria Disponible!\n");

}








int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}

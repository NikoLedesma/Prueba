/*
 ============================================================================
 Name        : pila.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include "funPila.h"


int main(void) {

	Pila* pilaHead=(Pila*) malloc(sizeof(Pila));
	printf("Ingrese una cadena a guardar en la pila\n");
	inicializacion(pilaHead);
	apilar(pilaHead,"holasssssssssssssssssss");
	muestra(pilaHead);
	desapilar(pilaHead);
	return EXIT_SUCCESS;
}




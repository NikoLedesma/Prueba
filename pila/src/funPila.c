/*
 * funPila.c
 *
 *  Created on: 02/03/2015
 *      Author: nikox
 */

# include "funPila.h"

void inicializacion(Pila *tas){
	tas->inicio=NULL;
	tas->tamanio=0;
}



int apilar(Pila * tas,char * dato){
	Elemento *nuevo_elemento;
	if((nuevo_elemento = (Elemento *)malloc (sizeof(Elemento)))==NULL){
		return -1;
	}
	if ((nuevo_elemento->dato = (char*) malloc(50 * sizeof(char)))==NULL){
		return -1;
	}

strcpy(nuevo_elemento->dato,dato);
nuevo_elemento->sig=tas->inicio;
tas->inicio=nuevo_elemento;
tas->tamanio++;
return 0;
}


int desapilar(Pila *tas){
	Elemento *sup_elemento;
	if (tas->tamanio==0)
	{
		return -1;
	}
	sup_elemento=tas->inicio;
	tas->inicio=tas->inicio->sig;
	free(sup_elemento->dato);
	free(sup_elemento);
	tas->tamanio--;
	return 0;
}

void muestra (Pila * tas){
	Elemento *actual;
	int i;
	actual = tas->inicio;
	for(i=0;i<tas->tamanio;i++){
		printf("\t\t%s\n",actual->dato);
		actual=actual->sig;
	}
}

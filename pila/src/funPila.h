/*
 * funPila.h
 *
 *  Created on: 02/03/2015
 *      Author: nikox
 */

#ifndef FUNPILA_H_
#define FUNPILA_H_
#include <stdlib.h>

typedef struct ElementoLista{
	char *dato;
	struct ElementoLista *sig;
}Elemento;

typedef struct ListaUbicacion{

	Elemento *inicio;
	int tamanio;
} Pila;


void inicializacion(Pila*);
int apilar(Pila*,char*);
int desapilar(Pila *);
void muestra(Pila *);


#endif /* FUNPILA_H_ */

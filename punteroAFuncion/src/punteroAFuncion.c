/*
 ============================================================================
 Name        : punteroAFuncion.c
 Author      : Niko
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int sumar(int, int);

int main(void) {
	int resultado1, resultado2;
	int (*punteroAFunc)(int, int); //declaramos un puntero a funcion
	punteroAFunc = sumar; //asignamos la direccion de la funcion sumar al punteroAFunc
	/*IMPORTANTE punteroAFunc APUNTA A UNA DIRECCION*/
	resultado1 = (*punteroAFunc)(10, 20); //esta combiene mas, es mas visual
	resultado2 = (punteroAFunc)(10, 10);
	printf("El resultado1=%d y El resultado2=%d", resultado1, resultado2);
	return EXIT_SUCCESS;
}

int sumar(int a, int b) {
return a + b;
}

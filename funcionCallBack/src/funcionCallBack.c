/*
 ============================================================================
 Name        : funcionCallBack.c
 Author      : Niko
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>




typedef int(*callback)(int,int);

///estariamos recibiendo la funcion(ES DECIR SU DIRECCION---->funcionX==(* funcionX)
int registrar_Callback(int a ,int b,callback funcionCallback){
	return funcionCallback(a,b);
}


int sumar(int x , int y){
	return x+y;
}

int main(void) {
	int resultado;
	resultado=registrar_Callback(3,4,sumar);
	printf("El resultado final es : %d\n",resultado);
	return EXIT_SUCCESS;
}

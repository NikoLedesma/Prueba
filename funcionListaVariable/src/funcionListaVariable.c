/*
 ============================================================================
 Name        : funcionListaVariable.c
 Author      : Niko
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdarg.h>

typedef struct var0{
	sem_t *sem;
	int	conteo;
 }	semaforo;

////////////proteccionPot--->el modo de funcionamiento de los semaforos
 ///////////cantSemaforos--->la cantidad de semaforos que hay
 ///////////...--->la lista variable deveria ser del tipo semaforo es decir (sem_t x,int y)

void initialize_sems(int proteccionPoT,int cantSemaforos,...){
	semaforo semAux;
	va_list pa;
	va_start(pa, cantSemaforos);
	 while (cantSemaforos--) {
		 semAux=va_arg(pa, semaforo);
		 if(sem_init( semAux.sem,proteccionPoT,semAux.conteo)){
			 perror("sem_init");
			exit (EXIT_FAILURE);
		}

	 }
	va_end(pa);
}










sem_t A,B,C;

int main(void) {
	semaforo x;
	semaforo y;
	semaforo z;
	x.sem=&A;
	x.conteo=1;
	y.sem=&B;
	y.conteo=3;
	z.sem=&C;
	z.conteo=1;

	initialize_sems(0,3,x,y,z);///////////initialize_sems(0,3,(&A,1),(&B,2),(&C,3));--->no se puede :(
	int valorA,valorB,valorC;
	sem_getvalue(&A,&valorA);
	sem_getvalue(&B,&valorB);
	sem_getvalue(&C,&valorC);
	printf("El valor del semaforo A es:%d\n "
			"El valor del semaforo B es:%d\n "
			"El valor del semaforo C es:%d\n",valorA,valorB,valorC);

	sem_destroy(&A);
	sem_destroy(&B);
	sem_destroy(&C);

	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	return EXIT_SUCCESS;
}

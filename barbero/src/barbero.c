/*
 ============================================================================
 Name        : barbero.c
 Author      : Niko
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>


#define CANT_CLIENTES 3
#define T_CUST   0  //// tiempo de un cliente
#define T_CORTE  3	//// tiempo de corte que toma un barbero
#define ASIENTOS 3

void* barbero (void*);
void* cliente (void*);


sem_t mutex;
sem_t sem_cliente;
sem_t sem_barbero;
int esperando=0;



struct timespec ts;


int main(void) {
	pthread_t barb_t,cust_t[CANT_CLIENTES];
	int i;
	///////////////
	///////////////------------------>>Inicializamos los semaforos
	///////////////
	if(sem_init(&mutex,0,1)){
			perror("sem_init");
			exit (EXIT_FAILURE);
		}
	if(sem_init(&sem_cliente,0,0)){
			perror("sem_init");
			exit (EXIT_FAILURE);
		}
	if(sem_init(&sem_barbero,0,0)){
			perror("sem_init");
			exit (EXIT_FAILURE);
		}
	///////////////
	///////////////
	///////////////

	   ts.tv_nsec =0;

	pthread_create(&barb_t,NULL,barbero,NULL);
	for (i=0;i<CANT_CLIENTES;i++){
	ts.tv_sec = 0;
	nanosleep(&ts,0);/////////espera 0 segundos
	pthread_create(&cust_t[i],NULL,cliente,NULL);
	}
	pthread_join(barb_t,NULL);
	return EXIT_SUCCESS;
}

void* barbero (void*a){
	printf ("Barber:Empiezo a trabajar\n");
	while (1) {
	sem_wait(&sem_cliente);
	sem_wait(&mutex);
	esperando--;
	sem_post(&sem_barbero);
	sem_post(&mutex);
	printf ("Barber:Comienzo el corte de pelo de un cliente quedan %d esperando.\n",esperando);
	ts.tv_sec=3;
	nanosleep (&ts,0);////////tarda 3 segundos para cortar
	printf ("Barber:Termine de cortar el pelo de un cliente quedan %d esperando.\n",esperando);
	}
	return NULL;
}


void* cliente (void* b){
	printf ("Cliente:entrando hay %d esperando\n",esperando);
	sem_wait(&mutex);
	if (esperando < ASIENTOS) {
	esperando++;
	sem_post(&sem_cliente);
	sem_post(&mutex);
	sem_wait(&sem_barbero);
	printf ("Customer:Me estan cortando el pelo.\n");
	}
	else {
	sem_post(&mutex);
	printf ("Customer:Me fui no hay lugar.\n");
	}

return NULL;
}














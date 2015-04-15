/*
 ============================================================================
 Name        : threads2.c
 Author      : Niko
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

sem_t mutex;
int a=3;
int b=6;
int res=1;


void *thread_function1(void *arg) {

  res++;//----->res=2
  b=b+a;//----->b=9
  b=b+b;//----->b=18
  a=res+b;//----->a=20
  res++; //----->res=3
  res=a+b+res;//----->res=41
  res=res+res;//----->res=82
  res=res+a;//----->res=102
  res=res+b;//----->res=120
  a=b+a;//----->a=38
  res=res+a;//----->res=158
  printf("El resultado de res en el threads 1 es %d\n",res);
  sem_post(&mutex);
  return NULL;
}


void *thread_function2(void *arg) {

  res++;//----->res=159
  a=res+a;//----->a=197
  b=res+a;//----->b=356
  res=a+b;//----->res=553
  res++;//----->res=554
  res=res+a;//----->res= 751
  printf("El resultado de res en el threads 2 es %d\n",res);
  sem_post(&mutex);
  sem_post(&mutex);
  return NULL;
}

int main(void) {
	pthread_t thread1,thread2;
	if(sem_init(&mutex,0,1)){
		perror("sem_init");
		exit (EXIT_FAILURE);
	}
	int valor;
	sem_getvalue(&mutex,&valor);
	printf("el valor del semaforo es %d\n",valor);
	sem_wait(&mutex);
	if(pthread_create(&thread1,NULL,thread_function1,NULL)){
		printf("error creating thread.\n");
		abort();
	}


	 sem_wait(&mutex);

	if(pthread_create(&thread2,NULL,thread_function2,NULL)){
			printf("error creating thread.\n");
			abort();
		}
	  sem_post(&mutex);

	if(pthread_join(thread1,NULL)){			////se espera que los dos threads terminen
		printf("Error joining thread");
		abort();
	}
	if(pthread_join(thread2,NULL)){
			printf("Error joining thread");
			abort();
		}
	 printf("El resultado de res es %d\n",res);
	if(sem_destroy(&mutex)){
			perror("sem_destroy");
			exit (EXIT_FAILURE);
		}

	printf("hola gil\n");
	return EXIT_SUCCESS;
}

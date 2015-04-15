/*
 ============================================================================
 Name        : threads.c
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


void *thread_function(void *arg) {
  int i;
  for ( i=0; i<20; i++ ) {
    printf("Thread says hi!\n");
    sleep(1);
  }
  return NULL;
}


int main(void) {
	pthread_t mythread;
	if(pthread_create(&mythread,NULL,thread_function,NULL)){
		printf("error creating thread.\n");
		abort();
	}
	printf("hola gil\n");
	if(pthread_join(mythread,NULL)){
		printf("Error joining thread");
		abort();
	}
	printf("hola gil\n");
	return EXIT_SUCCESS;
}

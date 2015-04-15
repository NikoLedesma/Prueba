/*
 ============================================================================
 Name        : Hilos.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

	pthread_t thread1,thread2;

void* funcion(void* arg )
{
	printf("EL mejor\n");
	pid_t id=getpid();

printf("tid:%d,pid:%d,tid:%d\n",thread1,id,pthread_self());
	return NULL;
}


int main(void) {

	int iret1,iret2;
	iret1=pthread_create(&thread1,NULL,funcion,NULL);
	iret2=pthread_create(&thread2,NULL,funcion,NULL);
	if(iret1!=0 && iret2!=0){
		return -1;
	}

	printf("Dio %d\n",iret1);
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	return EXIT_SUCCESS;
}

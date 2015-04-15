/*
 ============================================================================
 Name        : HilosSinSemaforos.c
 Author      : Niko
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>



int a=1;
int b=6;
int c=15;
int res;
pthread_t thread1,thread2;

void * suma(void * arg){
printf("Hola\n");
printf("Hola\n");
printf("Hola\n");
a=a+1;
b=b+1;
c=a+b;
printf("Hola\n");
printf("Hola\n");
printf("Hola\n");
}

void * resta(void * arg){
printf("Hola\n");
printf("Hola\n");
printf("Hola\n");
a=a-1;
b=b-1;
c=a-b;
printf("Hola\n");
printf("Hola\n");
printf("Hola\n");
}


int main(void) {
	pthread_create(&thread1,NULL,suma,NULL);
	pthread_create(&thread2,NULL,resta,NULL);


	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	printf("a=%d,b=%d,c=%d\n",a,b,c);
	return 0;
}

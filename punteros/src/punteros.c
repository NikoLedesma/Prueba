/*
 ============================================================================
 Name        : punteros.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char *p,*x;
	int i;

		p=malloc(sizeof(char)*654645646464);
		x=p;
		printf("El tamaño de un entero es %d y de un char es %d\n",sizeof(int),sizeof(char));
		printf("El puntero apunta a %p\n",p);

		for (i=0;i<3;i++){
			if(p==NULL){ printf("La memoria no pudo reservarse\n");
								break;}
			printf("El puntero apunta a %p\n",x++);

		}



free(p);



		return EXIT_SUCCESS;
}

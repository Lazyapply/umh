#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argcv[]){
	
	int 	iam = 0, np = 1;
	int 	p = atoi(argcv[1]);

	#pragma omp parallel num_threads(p)
	{
		np 	= omp_get_num_threads();
		iam = omp_get_thread_num();

		printf("Hola mundo - Proceso: %d - de %d procesos.\n", iam, np);
	}
	printf("Adios Mundo: soy el proceso %d de %d procesos.\n", iam, np);
}


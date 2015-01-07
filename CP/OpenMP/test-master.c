#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argcv[]){
	
	int 	iam = 0, np = 1;
	int 	p = atoi(argcv[1]);
	int		datos[100];
	int		i = 0, j = 0;


	#pragma omp parallel num_threads(p) shared(i) private(iam, np, j)
	{

		#if defined(_OPENMP)
			np 	= omp_get_num_threads();
			iam = omp_get_thread_num();
		#endif

		#pragma omp master
		{
			printf("El trabajo "YELLOW"MASTER "RESET"solo lo realiza el hilo: "RED "\t%d"RESET"\n", iam);
			for(j=0;j<10000;j++)
					i++;

			i = 222;			
		}
		printf("Despues de "YELLOW"MASTER"RESET" el valor de "YELLOW"i = %d "RESET"para el hilo: "RED"\t%d"RESET"\n", i, iam);
	
	}

}

	
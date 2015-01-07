#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argcv[]){
	
	int 	iam = 0, np = 1;
	int 	p = atoi(argcv[1]);
	int		datos[100];
	int		i = 0, j = 0;


	#pragma omp parallel num_threads(p) private(iam, np, i) shared(j)
	{

		#if defined(_OPENMP)
			np 	= omp_get_num_threads();
			iam = omp_get_thread_num();
		#endif
		for(i=0;i<5;i++){

			//#pragma omp critical
			{
				j++;
			}
		}
		printf("\tSoy el thread "YELLOW"%d"RESET", valor actual de j: "GREEN"%d"RESET"\n", iam, j);
	
	}
	printf("\t\tSoy el thread "YELLOW"%d"RESET", valor FINAL de j: "GREEN"%d"RESET"\n", iam, j);
}

	
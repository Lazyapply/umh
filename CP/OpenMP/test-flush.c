#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argcv[]){
	
	int 	iam = 0, np = 1;
	int 	p = atoi(argcv[1]);
	int		datos[100], suma[4];
	int		i = 0, j = 0;

	for(i=0;i<5;i++)
		datos[i] = 0;


	#pragma omp parallel num_threads(p) private(iam, np, i) shared(j, datos)
	{

		#if defined(_OPENMP)
			np 	= omp_get_num_threads();
			iam = omp_get_thread_num();
		#endif
		
		datos[iam] = 10 * iam + 1;
		#pragma omp flush(datos)
		printf("\tSoy el thread %d. Array: %d %d %d %d\n", iam, datos[0], datos[1], datos[2], datos[3]);
	
	}
	
}
	
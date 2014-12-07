#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argcv[]){
	
	int 	iam = 0, np = 1;
	int 	p = atoi(argcv[1]);
	int		datos[100];
	int		i = 0;


	#pragma omp parallel num_threads(p) private(iam, np, i)
	{

		#if defined(_OPENMP)
			np 	= omp_get_num_threads();
			iam = omp_get_thread_num();
		#endif

		#pragma omp for ordered
		{
			for(i=0;i<5;i++){
				

				#pragma omp ordered
				{
					printf("\tSoy el thread "YELLOW"%d "RESET"antes del ordered en la iteracion "GREEN"%d"RESET"\n", iam, i);
					printf("\t\tSoy el thread "YELLOW"%d"RESET", actuando en la iteracion "GREEN"%d"RESET"\n", iam, i);
					sleep(1);
				}
				// printf("\tSoy el thread "YELLOW"%d "RESET"antes del ordered en la iteracion "GREEN"%d"RESET"\n", iam, i);

				// #pragma omp ordered
				// {
				// 	printf("\t\tSoy el thread "YELLOW"%d"RESET", actuando en la iteracion "GREEN"%d"RESET"\n", iam, i);
				// 	sleep(1);
				// }		
			}
		}
	
	}

}

	
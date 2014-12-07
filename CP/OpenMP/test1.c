#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argcv[]){
	
	int 	iam = 0, np = 1;
	int		datos[100], i;
	int 	p = atoi(argcv[1]);

	#pragma omp parallel num_threads(p) private(iam)
	{
		np 	= omp_get_num_threads();
		iam = omp_get_thread_num();

		//cada SECTION se ejecuta en UN THREAD
		//hay una BARRERA en el final de la SECTIONS
		#pragma omp sections{

			#pragma omp section{
				printf("El thread %d realiza la seccion 1.\n", iam);
				for(i=0;i<100000;i++)
					datos[0]++;
			}

			#pragma omp section
				printf("El thread %d realiza la seccion 2.\n", iam);
			#pragma omp section
				printf("El thread %d realiza la seccion 3.\n", iam);
			#pragma omp section
				printf("El thread %d realiza la seccion 4.\n", iam);
			#pragma omp section
				printf("El thread %d realiza la seccion 5.\n", iam);
		}
	}

}
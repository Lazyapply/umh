#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argcv[]){
	
	int 	iam = 0, np = 1;
	int 	p = atoi(argcv[1]);
	int		datos[100], suma[4];
	int		i = 0, j = 0;
	int 	tam_bloque = atoi(argcv[2]), ini, fin, suma_global = 0;


	for(i=0;i<tam_bloque;i++)
		datos[i] = i;

	#pragma omp parallel num_threads(p) private(iam, np, i, ini, fin) shared(j, suma, datos, suma_global)
	{

		#if defined(_OPENMP)
			np 	= omp_get_num_threads();
			iam = omp_get_thread_num();
		#endif
		
		tam_bloque 	= tam_bloque/np;
		ini 		= tam_bloque * iam;
		fin 		= tam_bloque * (iam + 1);
		suma[iam] 	= 0;

		sleep(iam*2 +1);

		for(i=ini;i<fin;i++)
			suma[iam] += datos[i];

		#pragma omp barrier

		#pragma omp master
		{
			for(i=0;i<np;i++)
				suma_global += suma[i];

			printf("Valor final de "GREEN"suma global: %d "RED"(hilo:%d)."RESET"\n", suma_global, iam);
		}
	}
}
	
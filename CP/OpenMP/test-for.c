#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argcv[]){
	
	int 	iam = 0, np = 1;
	int 	p = atoi(argcv[1]);
	int		datos[100], i;


	#pragma omp parallel num_threads(p) private(iam, np, i)
	{

		#if defined(_OPENMP)	
			np 	= omp_get_num_threads();
			iam = omp_get_thread_num();
		#endif

		printf("Hola Mundo: soy el proceso %d de %d procesos.\n", iam, np);
		// schedule
		// static, np -> Se dividen las iteraciones en partes iguales, segun np
		// dynamic, np -> Se divide igual que en el anterior, pero
		// se asignan a los threads dinámicamente conforme terminan el trabajo
		// guided, np -> se asignan a los threads pero con tamaños diferentes.
		// Se empieza por (num_iteraciones/np) luego (num_iteraciones_restantes/np)
		// runtime -> en tiempo de ejecución mediante la variable de entrono
		// OMP_SCHEDULE

		#pragma omp for schedule(static, 4)
		for(i=0;i<12;i++){
			printf("Hilo %d, realiza iteracion %d \n", iam, i);
		}
	}
}
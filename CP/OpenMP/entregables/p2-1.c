/****************************************************************************************

		Practica:			matrizVector
		Archivo:			p2-1.c
		Alias:				----
		Fecha creacion:		05/12/2014
		Ultima modif:		12/12/2014
		Versión: 			1.0
		Autor: 				Diego Velaochaga Vilar


		Descripción:
		Matriz por vector usando cuatro variantes:

			a1) Cada hilo calcula un bloque del resultado, CON automatizadores
			a2) Cada hilo calcula un bloque del resultado, SIN automatizadores
			b1) Entre todos los hilos calculan bloque a bloque, CON automatizadores
			b2) Entre todos los hilos calculan bloque a bloque, SIN automatizadores

***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "colors.h"


int main(int argc, char *argv[]){

	int 	i=0, j=0, iam, np=1, tBloque, N;
	double	*vector, **matriz, *vResultado, aux;

	double	t1_a1 = 0, t1_a2 = 0, t1_b1 = 0, t1_b2 = 0;
	double	t2_a1 = 0, t2_a2 = 0, t2_b1 = 0, t2_b2 = 0;



	//el número de procesos viene del primer argumento
	//y el tamaño de N del segundo.
	np 		= atoi(argv[1]);
	N 		= atoi(argv[2]);
	tBloque = N/np;

	//reservamos memoria
	vector 		= (double*) malloc(N * sizeof(double));
	vResultado	= (double*) malloc(N * sizeof(double));
	matriz 		= (double**) malloc(N * sizeof(double*));

	for(i=0;i<N;i++){
		vector[i] = rand()%9;
		matriz[i] = (double*) malloc(N * sizeof(double));

		for(j=0;j<N;j++)
			matriz[i][j] = rand()%9;
	}




	/*
	INICIO OPCIÓN A1
	 */
	t1_a1 = omp_get_wtime();
	#pragma omp parallel num_threads(np) private(iam, i) default(shared)
	{
		iam = omp_get_thread_num();

		#pragma omp for private(j) schedule(static, tBloque)
		for(i=0;i<N;i++){
			for(j=0;j<N;j++)
				vResultado[i] += matriz[i][j] * vector[j];
		}

	}//fin parallel
	t2_a1 = omp_get_wtime();

	/*
	FIN OPCIÓN A1
	 */

	//borramos el vResultado
	for(i=0;i<N;i++)
		vResultado[i] = 0.0;

	/*
	INICIO OPCIÓN A2
	 */
	t1_a2 = omp_get_wtime();
	#pragma omp parallel num_threads(np) private(iam, i, j) default(shared)
	{
		iam = omp_get_thread_num();

		for(i=0;i<tBloque;i++){
			for(j=0;j<N;++j){
				vResultado[(iam*tBloque)+i] += matriz[(iam*tBloque)+i][j];
			}
		}
	}
	t2_a2 = omp_get_wtime();

	

	/*
	FIN OPCIÓN A2
	 */
	//borramos el vResultadoF
	for(i=0;i<N;i++)
		vResultado[i] = 0.0;
	/*
	INICIO OPCIÓN B1
	 */
	t1_b1 = omp_get_wtime();
	for(i=0;i<N;i++){

		aux = 0.0;
		#pragma omp parallel num_threads(np) private(iam) shared(aux)  default(shared)
		{
			iam = omp_get_thread_num();

			#pragma omp for private(j) schedule(static, tBloque) reduction(+:aux)
			for(j=0;j<N;j++){
				aux += matriz[i][j] * vector[j];
			}

		}
		vResultado[i] = aux;
	}

	t2_b1 = omp_get_wtime();
	/*
	FIN OPCIÓN B1
	 */
	//borramos el vResultado
	for(i=0;i<N;i++)
		vResultado[i] = 0.0;
	/*
	INICIO OPCIÓN B2
	 */
	t1_b2 = omp_get_wtime();

	#pragma omp parallel num_threads(np) private(iam, i, j, aux) default(shared)
	{
		iam = omp_get_thread_num();

		for(i=0;i<N;i++){

			aux = 0.0;
			aux += matriz[i][iam*tBloque+j] * vector[iam*tBloque+j];
		}

		#pragma omp critical
		{
			vResultado[i] += aux;
		}
	}

	t2_b2 = omp_get_wtime();

	/*
	FIN OPCIÓN B2
	 */
	


	//RESULTADOS
	printf("\n\t----------------------- "BOLDWHITE"RESULTADOS"RESET" -----------------------\n");
	printf("\tEjercicio\tResultado\n");
	printf("\t"GREEN"A1"RESET"\t\tnp="YELLOW"%d"RESET" N="YELLOW"%d"RESET" tiempo="YELLOW"%fs"RESET"\n", np, N, (t2_a1 - t1_a1));
	printf("\t"GREEN"A2"RESET"\t\tnp="YELLOW"%d"RESET" N="YELLOW"%d"RESET" tiempo="YELLOW"%fs"RESET"\n", np, N, (t2_a2 - t1_a2));
	printf("\t"GREEN"B1"RESET"\t\tnp="YELLOW"%d"RESET" N="YELLOW"%d"RESET" tiempo="YELLOW"%fs"RESET"\n", np, N, (t2_b1 - t1_b1));
	printf("\t"GREEN"B2"RESET"\t\tnp="YELLOW"%d"RESET" N="YELLOW"%d"RESET" tiempo="YELLOW"%fs"RESET"\n", np, N, (t2_b2 - t1_b2));


	printf("\n\n");
}
/****************************************************************************************

		Practica:			matVector
		Archivo:			p2-1.c
		Alias:				----
		Fecha creacion:		08/12/2014
		Ultima modif:		12/12/2014
		Versión: 			1.0
		Autor: 				Diego Velaochaga Vilar


		Descripción:
		mat por mat usando 8 variantes (con y sin automatizadores):

			a1) Cada hilo calcula un grupo de filas adyacentes
			a2) Cada hilo calcula grupos de filas adyacentes igual a 10
			b1) Cada hilo calcula un grupos de columnas adyacentes
			b2) Cada hilo calcula grupos de columnas adyacentes igual a 10

***************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "colors.h"


int main(int argc, char *argv[]){

	int 	i=0, j=0, iam, np, tBloque, k=0, N;
	double	**matA, **matB, **matR;
	double	t2 = 0.0, t1 = 0.0;



	//el número de procesos viene del primer argumento
	//y el tamaño de N del segundo.
	np 		= atoi(argv[1]);
	N 		= atoi(argv[2]);
	tBloque = N/np;

	//reservamos memoria
	matA 		= (double**) malloc(N * sizeof(double*));
	matB 		= (double**) malloc(N * sizeof(double*));
	matR 		= (double**) malloc(N * sizeof(double*));

	for(i=0;i<N;i++){
		matA[i] = (double*) malloc(N * sizeof(double));
		matB[i] = (double*) malloc(N * sizeof(double));
		matR[i] = (double*) malloc(N * sizeof(double));

		for(j=0;j<N;j++){
			matA[i][j] = rand()%9;
			matB[i][j] = rand()%9;
			matR[i][j] = 0.0;
		}
	}

	//imprimimos cabecera
	printf("\n\t----------------------- "BOLDWHITE"RESULTADOS"RESET" -----------------------\n");
	printf("\tEjercicio\tResultado\n");
	

	/*
	INICIO OPCIÓN A1 CON
	 */
	t1 = omp_get_wtime();
	#pragma omp parallel num_threads(np) private(i, k, iam) default(shared)
	{

		iam = omp_get_thread_num();

		#pragma omp for private(j) schedule(static, tBloque)
		for (k=0;k<N;++k){
			for (i=0;i<N;++i){
				for (j=0;j<N;++j){
					matR[k][i] += matA[k][j] * matB[j][i];
				}
			}
		}
	}
	t2 = omp_get_wtime();

	printf("\t"GREEN"A1 CON"RESET"\t\tnp="YELLOW"%d"RESET" N="YELLOW"%d"RESET" tiempo="YELLOW"%fs"RESET"\n", np, N, (t2 - t1));
	t1 = t2 = 0.0;
	/*
	FIN OPCIÓN A1 CON
	 */
	

	/*
	INICIO OPCIÓN A2 CON
	 */
	t1 = omp_get_wtime();
	#pragma omp parallel num_threads(np) private(i, k, iam) default(shared)
	{

		iam = omp_get_thread_num();

		#pragma omp for private(j) schedule(static,10)
		for (k=0;k<N;++k){
			for (i=0;i<N;++i){
				for (j=0;j<N;++j){
					matR[k][i] += matA[k][j] * matB[j][i];
				}
			}
		}
	}
	t2 = omp_get_wtime();

	printf("\t"GREEN"A2 CON"RESET"\t\tnp="YELLOW"%d"RESET" N="YELLOW"%d"RESET" tiempo="YELLOW"%fs"RESET"\n", np, N, (t2 - t1));
	t1 = t2 = 0.0;
	/*
	FIN OPCIÓN A2 CON
	 */


	/*
	INICIO OPCIÓN A1 SIN
	 */
	t1 = omp_get_wtime();
	#pragma omp parallel num_threads(np) private(k, i, j, iam) default(shared)
	{
		iam = omp_get_thread_num();


		for (k=0;k<tBloque;k++){
			for (i=0;i<N;i++){
				for (j=0;j<N;j++){
					matR[(tBloque*iam)+k][i] += matA[(tBloque*iam)+k][j] * matB[j][i];			
				}
			}
		}
	}
	t2 = omp_get_wtime();

	printf("\t"GREEN"A1 SIN"RESET"\t\tnp="YELLOW"%d"RESET" N="YELLOW"%d"RESET" tiempo="YELLOW"%fs"RESET"\n", np, N, (t2 - t1));
	t1 = t2 = 0.0;
	/*
	FIN OPCIÓN A1 SIN
	 */
	
		/*
	INICIO OPCIÓN A2 SIN
	 */
	int iN;
	int h;
	int salir;

	t1 = omp_get_wtime();
	#pragma omp parallel num_threads(np) private(iam, salir, np, i, j, k, h, iN) default(shared)
	{
		np = omp_get_num_threads();
		iam = omp_get_thread_num();

	
		salir = (N/10)/np;
		iN = 0;

		for(h=0;h<salir;h++){	
				for (k=0;k<10;k++){ 
					for (i=0;i<N;i++){
						for (j=0;j<N;j++){
							matR[(iam*10)+(iN*10)+k][i] += matA[(iam*10)+(iN*10)+k][j] * matB[j][i];			
						}
					}
				}
				iN += np;
		}
	}
	t2 = omp_get_wtime();

	printf("\t"GREEN"A2 SIN"RESET"\t\tnp="YELLOW"%d"RESET" N="YELLOW"%d"RESET" tiempo="YELLOW"%fs"RESET"\n", np, N, (t2 - t1));
	t1 = t2 = 0.0;
	/*
	FIN OPCIÓN A2 SIN
	 */
	
	/*
	INICIO OPCIÓN B1 CON
	 */
	double prod = 0.0;
	t1 = omp_get_wtime();
	for(k=0;k<N;k++){
		for(i=0;i<N;i++){	
			prod = 0;
			#pragma omp parallel num_threads(np) private(iam) shared(prod)
			{
				iam = omp_get_thread_num();

				#pragma omp for private(j) schedule(static,tBloque) reduction(+:prod)
				for(j=0;j<N;j++){
					prod += matA[k][j] * matB[j][i];
				}
			}
			matR[k][i] += prod;

		}
	}
	t2 = omp_get_wtime();

	printf("\t"GREEN"B1 CON"RESET"\t\tnp="YELLOW"%d"RESET" N="YELLOW"%d"RESET" tiempo="YELLOW"%fs"RESET"\n", np, N, (t2 - t1));
	t1 = t2 = 0.0;
	/*
	FIN OPCIÓN B1 CON
	 */
	
	/*
	INICIO OPCIÓN B1 SIN
	 */
	t1 = omp_get_wtime();
	#pragma omp parallel num_threads(np) private(i, j, k, iam, prod) default(shared)
	{

		iam = omp_get_thread_num();
		prod = 0.0;
		for (k=0;k<N;++k){
			for(i=0;i<N;++i){
				for(j=0;j<tBloque;++j){
					prod += matA[k][iam*tBloque+j] * matB[iam*tBloque+j][i];
				}

				#pragma omp critical
				{
					matR[k][i] += prod;
					prod = 0.0;
				}	
			}
		}
	}
	t2 = omp_get_wtime();

	printf("\t"GREEN"B1 SIN"RESET"\t\tnp="YELLOW"%d"RESET" N="YELLOW"%d"RESET" tiempo="YELLOW"%fs"RESET"\n", np, N, (t2 - t1));
	t1 = t2 = 0.0;
	/*
	FIN OPCIÓN B1 SIN
	 */
	
	/*
	INICIO OPCIÓN B2 CON
	 */
	t1 = omp_get_wtime();
	for(k=0;k<N;k++){
		for (i = 0; i < N; i++){

			prod = 0;
			#pragma omp parallel num_threads(np) private(iam) shared(prod)
			{
				iam = omp_get_thread_num();

				#pragma omp for private(j) schedule(static, 10) reduction(+:prod)//private(j) //schedule(static,tBloque)//reduction(+:prod)
				for (j=0;j<N;j++){
					prod += matA[k][j] * matB[j][i];
				}
			}
			matR[k][i] += prod;

		}
	}
	t2 = omp_get_wtime();

	printf("\t"GREEN"B2 CON"RESET"\t\tnp="YELLOW"%d"RESET" N="YELLOW"%d"RESET" tiempo="YELLOW"%fs"RESET"\n", np, N, (t2 - t1));
	t1 = t2 = 0.0;
	/*
	FIN OPCIÓN B2 CON
	 */
	
	/*
	INICIO OPCIÓN B2 SIN
	 */
	t1 = omp_get_wtime();
	#pragma omp parallel num_threads(np) private(iam, salir, np, prod, i, j, k, h, iN) default(shared)
	{
		np = omp_get_num_threads();
		iam = omp_get_thread_num();
		salir 	= 0;
		prod 	= 0.0;
	
		salir 	= (N/10)/np;
		iN 		= 0;

		for(k=0;k<N;k++){	
			for(i=0;i<N;i++){ 
				for(h=0;h<salir;h++){
					for (j=0;j<10;j++){
						prod += matA[k][(iam*10)+(iN*10)+j] * matB[(iam*10)+(iN*10)+j][i];			
					}
					iN += np;
					#pragma omp critical
					{
						matR[k][i] += prod;
						prod = 0.0;
					}
					// printf("%.0f-", matR[i][j]);
				}
				iN=0;
			}
		}
	}
	t2 = omp_get_wtime();

	printf("\t"GREEN"B2 SIN"RESET"\t\tnp="YELLOW"%d"RESET" N="YELLOW"%d"RESET" tiempo="YELLOW"%fs"RESET"\n", np, N, (t2 - t1));
	t1 = t2 = 0.0;
	/*
	FIN OPCIÓN B2 SIN
	 */




	//APARTADO B ---------------------------------------------------------------------------
	
	/*
	INI OPCIÓN TODOS CON
	 */
	t1 = omp_get_wtime();
	for(k=0;k<N;k++){
		for(i=0;i<N;i++){	
			prod = 0.0;
			#pragma omp parallel num_threads(np) private(iam) shared(prod)
			{

				iam = omp_get_thread_num();

				#pragma omp for private(j) schedule(static,tBloque) reduction(+:prod)
				for (j=0;j<N;j++){
					prod += matA[k][j] * matB[j][i];

				}
			}
			matR[k][i] += prod;
			// printf("%.0f ", matR[k][i]);
		}
		// printf("\n");
	}
	t2 = omp_get_wtime();

	printf("\t"GREEN"TODOS CON"RESET"\tnp="YELLOW"%d"RESET" N="YELLOW"%d"RESET" tiempo="YELLOW"%fs"RESET"\n", np, N, (t2 - t1));
	t1 = t2 = 0.0;
	/*
	FIN OPCIÓN TODOS CON
	 */


/*
	INI OPCIÓN TODOS SIN
	 */
	t1 = omp_get_wtime();
	double prod_int[np];
	#pragma omp parallel num_threads(np) private(i, j, k, iam, np) default(shared)
	{
		np = omp_get_num_threads();
		iam = omp_get_thread_num();
		prod_int[iam] = 0;
		for(k=0;k<N;++k){
			for(i=0;i<N;++i){
				for(j=0;j<tBloque;++j){
					prod_int[iam] += matA[k][iam*tBloque+j] * matB[iam*tBloque+j][i];
				}
				#pragma omp barrier
				#pragma omp master
				{
					for(h=0;h<np;++h){
						matR[k][i] += prod_int[h];
						prod_int[h]=0;
					}
				}	
				#pragma omp barrier
			}
		}
	}
	t2 = omp_get_wtime();

	printf("\t"GREEN"TODOS SIN"RESET"\tnp="YELLOW"%d"RESET" N="YELLOW"%d"RESET" tiempo="YELLOW"%fs"RESET"\n", np, N, (t2 - t1));
	t1 = t2 = 0.0;
	/*
	FIN OPCIÓN TODOS SIN
	 */


/*
	INI OPCIÓN TODOS CON
	 */
	
	/*
	FIN OPCIÓN TODOS CON
	 */


/*
	INI OPCIÓN TODOS CON
	 */
	
	/*
	FIN OPCIÓN TODOS CON
	 */

	printf("\n\n");
}
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
	int tamMatriz;
	double t1, t2;
	int tamBloque, i, j,nproces, myrank;
	double **matrizA, **matrizB, **matrizRes;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nproces);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	tamMatriz = atoi(argv[1]);
	tamBloque = tamMatriz / nproces;

	

/********************************************	

 Reserva de memoria y preparacion de datos.

********************************************/
	
	if (myrank == 0)		
	{
		matrizA = (double**)malloc(tamMatriz*sizeof(double*));
		matrizRes = (double**)malloc(tamMatriz*sizeof(double*));
		for (i = 0; i < tamMatriz ; i++)
		{
			matrizA[i] = (double*)malloc(tamMatriz*sizeof(double));
			matrizRes[i] = (double*)malloc(tamMatriz*sizeof(double));
			//Rellenar matriz
			for (j = 0; j < tamMatriz; ++j)
			{
				matrizA[i][j] = rand()%9;
				matrizRes[i][j] = 0;
				// printf("%.2f - ",matrizB[i][j]);
			}
		// printf("\n");
		}

		matrizB = (double**)malloc(tamMatriz*sizeof(double*));
		for (i = 0; i < tamMatriz ; i++)
		{
			matrizB[i] = (double*)malloc(tamMatriz*sizeof(double));
			//Rellenar matriz
			for (j = 0; j < tamMatriz; ++j)
			{
				matrizB[i][j] = rand()%9;
			}

			MPI_Bcast(matrizB[i], tamMatriz, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		}


	}
	else
	{ 
		matrizB = (double**)malloc(tamMatriz*sizeof(double*));
		matrizA = (double**)malloc(tamMatriz*sizeof(double*));
		matrizRes = (double**)malloc(tamMatriz*sizeof(double*));
		for (i = 0; i < tamBloque ; i++)
		{
			matrizA[i] = (double*)malloc(tamMatriz*sizeof(double));
			matrizRes[i] = (double*)malloc(tamMatriz*sizeof(double));
			for (j = 0; j < tamMatriz; ++j)
			{
				matrizA[i][j] = 0;
				matrizRes[i][j] = 0;
				// printf("%.2f - ",matrizB[i][j]);
			}
		}


		//Reservo MatrizB y Recivo Bcast
		for (i = 0; i < tamMatriz ; i++)
		{
			matrizB[i] = (double*)malloc(tamMatriz*sizeof(double));
			MPI_Bcast(matrizB[i], tamMatriz, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		}
	}

/********************************************	

 		Envio y recepcion de datos

********************************************/

	if (myrank == 0)
	{
		for (i = 1; i < nproces; i++)
		{
			for (j = 0; j < tamBloque; j++)
			{
				MPI_Send(matrizA[tamBloque*i+j],tamMatriz,MPI_DOUBLE,i,5,MPI_COMM_WORLD);
			}	
		}
		t1 = MPI_Wtime();
	}
	else
	{
		for (i = 0; i < tamBloque; i++)
		{
			MPI_Recv(matrizA[i], tamMatriz, MPI_DOUBLE,0,5,MPI_COMM_WORLD,&status);
		}
	}


/********************************************	

 		Calculo resultados

********************************************/

 	
 		
	int k;
	for (k = 0; k < tamBloque; k++) 
	{
		for (i = 0; i < tamMatriz; i++)
		{
			for (j = 0; j < tamMatriz; j++)
			{
				matrizRes[k][i] += matrizA[k][j] * matrizB[j][i];			
			}
		}
	}
 		
/********************************************	

 		envio y recibo resultados 

********************************************/

 	if (myrank == 0)
 	{
 		for (i = 1; i < nproces; i++)
		{
			for (j = 0; j < tamBloque; j++)
			{
				MPI_Recv(matrizRes[tamBloque*i+j], tamMatriz, MPI_DOUBLE, i,5, MPI_COMM_WORLD, &status);
			}
		}

		//Imprimir matriz final
		// for (i = 0; i < tamMatriz; i++)
		// {
		// 	for (j = 0; j < tamMatriz; j++)
		// 	{
		// 		printf("%.2f - ", matrizRes[i][j]);
		// 	}
		// 	printf("\n");
		// }	
 	}
 	else
 	{
 		for (i = 0; i < tamBloque; i++)
 		{
 			MPI_Send(matrizRes[i], tamMatriz, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);
 		}
 	}


 	

 	if(myrank == 0){
 		t2 = MPI_Wtime();
		printf("Con %d procesos el tiempo es %f\n",nproces, (t2-t1));
	}

	MPI_Finalize();
}
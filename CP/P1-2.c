#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]){

	int 		tamMatriz, tamBloque, i, j, nproces, myrank;
	double 		t1, t2;
	double		**matrizA, **matrizB, **matriz_r;
	MPI_Status	status;


	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nproces);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	tamMatriz	= atoi(argv[1]);
	tamBloque	= tamMatriz/nproces;

	//reserva de memoria e inicialización
	if(myrank == 0){
		matrizA 	= (double**)malloc(tamMatriz * sizeof(double*));
		matriz_r 	= (double**)malloc(tamMatriz * sizeof(double*));

		for(i=0;i<tamMatriz;i++){
			matrizA[i] 	= (double*)malloc(tamMatriz * sizeof(double));
			matriz_r[i] = (double*)malloc(tamMatriz * sizeof(double));

			for(j=0;j<tamMatriz;j++){
				matrizA[i][j] 	= rand()%9;
				matriz_r[i][j] 	= 0;
			}
		}

		matrizB = (double**) malloc(tamMatriz *sizeof(double*));
		for(i=0;i<tamMatriz;i++){
			matrizB[i] = (double*)malloc(tamMatriz * sizeof(double));

			for(j=0;j<tamMatriz;j++){
				matrizB[i][j] = rand()%9;
			}
		}
		MPI_Bcast(matrizB[i], tamMatriz, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	}
	else{
		matrizA 	= (double**)malloc(tamMatriz * sizeof(double*));
		matrizB 	= (double**)malloc(tamMatriz * sizeof(double*));
		matriz_r 	= (double**)malloc(tamMatriz * sizeof(double*));

		for(i=0;i<tamBloque;i++){
			matrizA[i] 	= (double*)malloc(tamMatriz * sizeof(double));
			matriz_r[i] = (double*)malloc(tamMatriz * sizeof(double));

			for(j=0;j<tamMatriz;j++){
				matrizA[i][j] 	= 0;
				matriz_r[i][j] 	= 0;
			}
		}

		//reserva y Broadcast
		for(i=0;i<tamMatriz;i++){
			matrizB[i] = (double*)malloc(tamMatriz * sizeof(double));
			MPI_Bcast(matrizB[i], tamMatriz, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		}
	}


	//comunicaciones
	if(myrank == 0){
		for(i=1; i<nproces;i++){
			for(j=0;j<tamBloque;j++){
				MPI_Send(matrizA[tamBloque*i+j], tamMatriz, MPI_DOUBLE, i, 5, MPI_COMM_WORLD);
			}
		}

		t1 = MPI_Wtime();
	}
	else{
		for(i=0; i<tamBloque;i++){
			MPI_Recv(matrizA[i], tamMatriz, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD, &status);
		}
	}

	//calculo de resultados
	int z;
	for(z=0;z<tamBloque;z){
		for(i=0;i<tamMatriz;i++){
			for(j=0;j<tamMatriz;j++){
				matriz_r[z][i] += matrizA[z][j] * matrizB[j][i];
			}
		}
	}


	//comunicacion (resutlados parciales)
	if(myrank == 0){
		for(i=1;i<nproces;i++){
			for(j=0;j<tamBloque;j++){
				MPI_Recv(matriz_r[tamBloque*i+j], tamMatriz, MPI_DOUBLE, i, 5, MPI_COMM_WORLD, &status);
			}
		}
	}
	else{
		for(i=0;i<tamBloque;i++){
			MPI_Send(matriz_r[i], tamMatriz, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);
		}
	}



	if(myrank == 0){
		t2 = MPI_Wtime();
		printf("Tiempo con %d procesos >> %f\n", nproces, (t2-t1));
	}


	MPI_Finalize();
}

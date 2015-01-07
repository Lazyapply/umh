#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]){

	int 		tamMatriz, tamBloque, i, j, nproces, myrank;
	double 		t1, t2;
	double		*vector, *vector_r, **matriz;
	MPI_Status	status;


	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nproces);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	tamMatriz = atoi(argv[1]);
	tamBloque = tamMatriz/nproces;


	//reserva de memoria e inicialización
	if(myrank == 0){
		vector 		= (double*)malloc(tamMatriz * sizeof(double));
		vector_r 	= (double*)malloc(tamMatriz * sizeof(double));
		matriz 		= (double**)malloc(tamMatriz * sizeof(double*));

		for(i=0;i<tamMatriz;i++){
			vector[i] 	= rand()%9;
			vector_r[i] = 0;


			matriz[i] = (double*)malloc(tamMatriz * sizeof(double));
			for(j=0;j<tamMatriz;j++){
				matriz[i][j] = rand()%9;
			}
		}

		MPI_Bcast(vector, tamMatriz, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	}
	else{
		vector 		= (double*)malloc(tamMatriz * sizeof(double));
		vector_r 	= (double*)malloc(tamMatriz * sizeof(double));
		matriz 		= (double**)malloc(tamMatriz * sizeof(double*));

		for(i=0;i<tamBloque;i++){
			matriz[i] = (double*)malloc(tamMatriz * sizeof(double));
		}
	
		MPI_Bcast(vector, tamMatriz, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	}



	//Comunicación (envio datos)
	if(myrank == 0){
		for(i=1;i<nproces;i++){
			for(j=0;j<tamBloque;j++){
				MPI_Send(matriz[tamBloque*i+j], tamMatriz, MPI_DOUBLE, i, 5, MPI_COMM_WORLD);
			}
		}
		t1 = MPI_Wtime();
	}
	else{
		for(i=0;i<tamBloque;i++){
			MPI_Recv(matriz[i], tamMatriz, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD, &status);
		}
	}


	//calculos
	for(i=0;i<tamBloque;i++){
		for(j=0;j<tamMatriz;j++){
			vector_r[i] += matriz[i][j] * vector[j];
		}
	}


	//envio/recepcio (resultados parciales)
	if(myrank == 0){
		for(i=1;i<nproces;i++){
			MPI_Recv(&vector_r[i*tamBloque], tamBloque, MPI_DOUBLE, i, 5, MPI_COMM_WORLD, &status);
		}
	}
	else{
		MPI_Send(vector_r, tamBloque, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);
	}


	if(myrank == 0){
		t2 = MPI_Wtime();
		printf("Tiempo con %d procesos >> %f\n", nproces, (t2-t1));
	}

	MPI_Finalize();
}
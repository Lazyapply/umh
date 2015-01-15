#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]){


	int 		nproces, myrank, i;
	int 		vector1[10], vector2[20];
	MPI_Status 	status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nproces);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	if(myrank == 1){
		//inicializamos los vectores
		for(i=0;i<10;i++)
			vector1[i] = 100 * i;

		for(i=0;i<20;i++)
			vector2[i] = 101 * i;

		
		//MPI_Send(matrizA[tamBloque*i+j], tamMatriz, MPI_DOUBLE, i, 5, MPI_COMM_WORLD);
		////envio V1
		for(i=0;i<5;i++){
			if(i != 1)
				MPI_Send(vector1, 10, MPI_INT, i, 5, MPI_COMM_WORLD);
		}

		for(i=5;i<nproces;i++){
			MPI_Send(vector2, 20, MPI_INT, i, 5, MPI_COMM_WORLD);
		}
	}
	else{
		//MPI_Recv(matrizA[i], tamMatriz, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD, &status);
		if(myrank < 5)
			MPI_Recv(vector1, 10, MPI_INT, 1, 5, MPI_COMM_WORLD, &status);
		else
			MPI_Recv(vector2, 20, MPI_INT, 1, 5, MPI_COMM_WORLD, &status);
	}

	printf("\tSoy el proceso: %d de %d procesos y mi vector es: ", myrank, nproces);
	if(myrank < 5){
		for(i=0;i<10;i++)
			printf(" %d ", vector1[i]);
	}
	else{
		for(i=0;i<20;i++)
			printf(" %d ", vector2[i]);
	}
	printf("\n");

	MPI_Finalize();
}
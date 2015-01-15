#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]){

	int 		nproces, myrank, i, j, tam, tbloq;
	int 		**matriz, *vector, *matrizParcial;
	MPI_Status 	status;



	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nproces);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	tam = atoi(argv[1]);
	tbloq = tam/nproces;


	if(myrank == 0){
		//reservamos e inicializamos
		matriz = (int**)malloc(tam*sizeof(int*));
		vector = (int*)malloc(tam*sizeof(int));

		for(i=0;i<tam;i++){

			matriz[i] = (int*)malloc(tam*sizeof(int));
			vector[i] = rand()%9;

			for(j=0;j<tam;j++)
				matriz[i][j] = rand()%9;
		}

		//enviamos el vector
		
		//MPI_Bcast(matrizB[i], tamMatriz, MPI_DOUBLE, 0, MPI_COMM_WORLD);
		MPI_Bcast(vector, tam, MPI_INT, 0, MPI_COMM_WORLD);
		
		//enviamos los trozos de la matriz
		for(i=1;i<nproces;i++){
			//MPI_Send(matrizA[tamBloque*i+j], tamMatriz, MPI_DOUBLE, i, 5, MPI_COMM_WORLD);
			MPI_Send(matriz[i], tam, MPI_INT, i, 4, MPI_COMM_WORLD);
		}
	}
	else{
		matrizParcial = (int*)malloc(tam*sizeof(int));
		vector = (int*)malloc(tam*sizeof(int));

		for(i=0;i<tam;i++){
			matrizParcial[i] = 0;
			vector[i] = 0;
		}

		
		//recibimos el vector
		MPI_Bcast(vector, tam, MPI_INT, 0, MPI_COMM_WORLD);
		//recibimos el trozo de matriz
		//MPI_Recv(vector2, 20, MPI_INT, 1, 5, MPI_COMM_WORLD, &status);

			MPI_Recv(matrizParcial, tam, MPI_INT, 0, 4, MPI_COMM_WORLD, &status);


	}

	printf("\tSoy el proceso: %d de %d procesos y mi vector es: ", myrank, nproces);
	for(i=0;i<tam;i++)
		printf(" %d ", vector[i]);

	printf("\n");

	printf("\tSoy el proceso: %d de %d procesos y mi subMatriz es: ", myrank, nproces);
	for(i=0;i<tam;i++)
		printf(" %d ", matrizParcial[i]);
	
	printf("\n");


	MPI_Finalize();
}
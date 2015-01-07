#include <stdio.h>
#include <mpi.h>

int main(int argc,char *argv[]){

	int nproces, myrank, err;
	MPI_Init(&argc, &argv);

	err = MPI_Comm_size(MPI_COMM_WORLD, &nproces);
	err = MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	printf("Soy el proceso %d, de %d procesos\n", myrank, nproces);

	MPI_Finalize();
}
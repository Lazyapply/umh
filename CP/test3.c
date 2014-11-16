#include <stdio.h>
#include <mpi.h>


int main(int argc, char *argv[]){

	int 		nproces, myrank, i;
	double		data1, data2;
	MPI_Status	status;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &nproces);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

	data1 = 0;

	if(myrank > 0){
		data1 = myrank * 10;
		MPI_Send(&data1, 1, MPI_DOUBLE, i, 5, MPI_COMM_WORLD);
	}
	else{
		for(i=1;i<nproces;i++){
			MPI_Recv(&data2, 1, MPI_DOUBLE, MPI_ANY_SOURCE, 5, MPI_COMM_WORLD, &status);
			data1 = data1 + data2 * status.MPI_SOURCE;
		}
		

	}
	printf("Proceso %d ->> data1: %f, data2: %f.\n", myrank, data1, data2);
	printf("\tMPI_SOURCE: %d\n\tMPI_TAG: %d\n\tMPI_ERROR: %d\n", status.MPI_SOURCE, status.MPI_TAG, status.MPI_ERROR);
	MPI_Finalize();
}
#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <omp.h>

#define N 			512
#define BLOCK_SIZE 	512

__global__ void internProd(int *intProdParcial, int *d1, int *d2){

	__shared__ double accumR[BLOCK_SIZE];

	int pos 	= blockIdx.x * blockDim.x + threadIdx.x;
	int iAccum	= threadIdx.x;
	int vec 	= blockIdx.x;

	accumR[iAccum] = d1[pos] * d1[pos];

	for(int stride = BLOCK_SIZE/2; stride>0;stride>>=1){
		__syncthreads();
		accumR[iAccum] += accumR[stride + iAccum];
	}

	if(threadIdx.x == 0){
		intProdParcial[vec] = accumR[0];
	}
}


int main(int argc, char *argv[]){

	int i, j;
	int **m, *v, *vR;
	int *d_m, *d_v, *d_vR;
	int *res;
	double t1GPU, t2GPU;

	//reservas en HOST
	m 	= (int**)malloc(N*sizeof(int*));
	v 	= (int*)malloc(N*sizeof(int));
	vR 	= (int*)malloc(N*sizeof(int));
	res = (int*)malloc(N*sizeof(int));

	//continuación reserva e inicialización
	for(i=0;i<N;i++){
		m[i] = (int*)malloc(N*sizeof(int));
		v[i] = rand()%9;
		vR[i] = 0;
		res[i] = 0;

		for(j=0;j<N;j++)
			m[i][j] = rand()%9;
	}

	
	
	if (cuInit(0) != 0){ // Obligatorio para que funcione la API
		printf("ERROR De Inicializacion\n");
		exit(0);
	}

	int idDevice = 0;
	int deviceCount;

	cudaDeviceProp gtxProp;

	cuDeviceGetCount(&deviceCount); //Devuelve el nº de GPU's CUDA
	if (deviceCount == 0){
		printf("ERROR Ningun dispositivo es compatible con CUDA\n");
		exit(0);
	}

	//información de la GPU
	//recogemos la estrucutra de propiedades
	cudaGetDeviceProperties(&gtxProp, idDevice);

	//escribimos las propiedades del dispositivo
	printf("\n\tDispositivo CUDA Instalado: \"%s\"\n\n",gtxProp.name);
	printf("\tCapacidades de Cómputo: Revision( %d.%d )\n",gtxProp.major, gtxProp.minor);

	printf("\tCantidad TOTAL de Memoria GLOBAL: %ld MBytes\n", gtxProp.totalGlobalMem/1048576);
	printf("\tCantidad de Memoria Compartida por bloque: %ld KBytes\n", gtxProp.sharedMemPerBlock/1024);
	printf("\tTamaño de WARP: %d Threads\n",gtxProp.warpSize);
	printf("\tTamaño máximo de Hilos por Bloque: %d\n",gtxProp.maxThreadsPerBlock);

	printf("\n\t\tDIMENSIONES\n\n");
	printf("\tDimensiones maximas de bloque:  ( %d x %d x %d )\n", 
		gtxProp.maxThreadsDim[0],
		gtxProp.maxThreadsDim[1],
		gtxProp.maxThreadsDim[2]);
	printf("\tDimensiones maximas de grid:   ( %d x %d x %d )\n",
	   gtxProp.maxGridSize[0],
	   gtxProp.maxGridSize[1],
	   gtxProp.maxGridSize[2]);
	printf("\tFrecuencia de Reloj: %.3f GHz\n", (float)gtxProp.clockRate/1000000);
	printf("\tMemoria CONSTANT disponible: %ld Bytes\n", gtxProp.totalConstMem);

	//reserva de momoria en DEVICE
	cudaMalloc((void**)&d_m, N*sizeof(d_m));
	cudaMemset(d_m, 0, N*sizeof(d_m));
	cudaMalloc((void**)&d_v, N*sizeof(d_v));
	cudaMemset(d_v, 0, N*sizeof(d_v));
	cudaMalloc((void**)&d_vR, N*sizeof(d_vR));
	cudaMemset(d_vR, 0, N*sizeof(d_vR));

	//copiamos del HOST hacia el DEVICE
	cudaMemcpy(d_v, v, N*sizeof(int), cudaMemcpyHostToDevice);

	//1,512
	t1GPU = omp_get_wtime();
	for(i=0;i<N;i++){
		cudaMemcpy(d_m, m[i], N*sizeof(int), cudaMemcpyHostToDevice);
		internProd<<<1,512>>>(d_vR, d_m, d_v);

		cudaMemcpy(vR, d_vR, N*sizeof(int), cudaMemcpyDeviceToHost);
		
		for(j=0;j<N;j++){
			res[i] += vR[j];
		}
	}

	t2GPU = omp_get_wtime();

	printf("\n\tRESULTADOS\n\t---------------------------------\n");
	printf("\tTiempo GPU <<<1,512>>>: %f\n", t2GPU - t1GPU);


	//2,256
	t1GPU = omp_get_wtime();
	for(i=0;i<N;i++){
		cudaMemcpy(d_m, m[i], N*sizeof(int), cudaMemcpyHostToDevice);
		internProd<<<2,256>>>(d_vR, d_m, d_v);

		cudaMemcpy(vR, d_vR, N*sizeof(int), cudaMemcpyDeviceToHost);
		
		for(j=0;j<N;j++){
			res[i] += vR[j];
		}
	}

	t2GPU = omp_get_wtime();
	printf("\tTiempo GPU <<<2,256>>>: %f\n", t2GPU - t1GPU);


	//4,128
	t1GPU = omp_get_wtime();
	for(i=0;i<N;i++){
		cudaMemcpy(d_m, m[i], N*sizeof(int), cudaMemcpyHostToDevice);
		internProd<<<4,128>>>(d_vR, d_m, d_v);

		cudaMemcpy(vR, d_vR, N*sizeof(int), cudaMemcpyDeviceToHost);
		
		for(j=0;j<N;j++){
			res[i] += vR[j];
		}
	}

	t2GPU = omp_get_wtime();
	printf("\tTiempo GPU <<<4,128>>>: %f\n", t2GPU - t1GPU);


	//8,64
	t1GPU = omp_get_wtime();
	for(i=0;i<N;i++){
		cudaMemcpy(d_m, m[i], N*sizeof(int), cudaMemcpyHostToDevice);
		internProd<<<8,64>>>(d_vR, d_m, d_v);

		cudaMemcpy(vR, d_vR, N*sizeof(int), cudaMemcpyDeviceToHost);
		
		for(j=0;j<N;j++){
			res[i] += vR[j];
		}
	}

	t2GPU = omp_get_wtime();
	printf("\tTiempo GPU <<<8,64>>>: %f\n", t2GPU - t1GPU);


	printf("\n");

	cudaFree(d_m);
	cudaFree(d_v);
	cudaFree(d_vR);
	free(m);
	free(v);
	free(vR);
}
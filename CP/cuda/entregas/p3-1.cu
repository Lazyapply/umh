#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <omp.h>


#define N 256


__global__ void add2Vectors(int *v1, int *v2, int *vR){
	//indice del hilo
	int indexT = blockIdx.x * blockDim.x + threadIdx.x;
	vR[indexT] = v1[indexT] + v2[indexT];
}

int main(){

	int 	i, j; //iteradores
	int		**h_m1, **h_m2, **h_mR; //host
	int		*d_v1, *d_v2, *d_vR; //device
	double	t1CPU, t2CPU, t1GPU, t2GPU;


	//reservamos memoria
	h_m1 = (int**)malloc(N*sizeof(int*));
	h_m2 = (int**)malloc(N*sizeof(int*));
	h_mR = (int**)malloc(N*sizeof(int*));
	
	for(i=0;i<N;i++){
		h_m1[i] = (int*)malloc(N*sizeof(int));
		h_m2[i] = (int*)malloc(N*sizeof(int));
		h_mR[i] = (int*)malloc(N*sizeof(int));

		//inicializacion de las matrices
		for(j=0;j<N;j++){
			h_m1[i][j] = rand()%9;
			h_m2[i][j] = rand()%9;
			h_mR[i][j] = 0;
			//printf(" %d ", h_m1[i][j]);
		}
		//printf("\n");
	}

	//resultado CPU (secuencial)
	t1CPU = omp_get_wtime();
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			h_mR[i][j] = h_m1[i][j] + h_m2[i][j];
		}
	}
	t2CPU = omp_get_wtime();

	int idDevice = 0;
	int deviceCount;

	cudaDeviceProp gtxProp;
	
	if (cuInit(0) != 0){ // Obligatorio para que funcione la API
		printf("ERROR De Inicializacion\n");
		exit(0);
	}

	cuDeviceGetCount(&deviceCount); //Devuelve el nº de GPU's CUDA
	if (deviceCount == 0){
		printf("ERROR Ningun dispositivo es compatible con CUDA\n");
		exit(0);
	}

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


	//reservamos CUDA
	cudaMalloc((void**)&d_v1, N*N * sizeof(d_v1));
	cudaMalloc((void**)&d_v2, N*N * sizeof(d_v2));
	cudaMalloc((void**)&d_vR, N*N * sizeof(d_vR));
	cudaMemset(d_v1, 0, N*N*sizeof(d_v1));
	cudaMemset(d_v2, 0, N*N*sizeof(d_v2));
	cudaMemset(d_vR, 0, N*N*sizeof(d_vR));


	//copiamos la matriz en forma de vector
	//-----------------------------
	//apartado A)
	//-----------------------------
	int iterador = 0;
	for(i=0;i<N;i++){
		//copiamos el vector que vamos a usar en este momento
		cudaMemcpy(&d_v1[iterador], h_m1[i], N*sizeof(int), cudaMemcpyHostToDevice);
		cudaMemcpy(&d_v2[iterador], h_m1[i], N*sizeof(int), cudaMemcpyHostToDevice);
		iterador += N - 1;
	}

	//tiempos
	t1GPU = omp_get_wtime();
	add2Vectors<<<128,512>>>(d_v1, d_v2, d_vR);
	cudaThreadSynchronize();
	t2GPU = omp_get_wtime();

	//resultados
	printf("\n\t Resultadosn--------------------------");
	printf("\n\t El tiempo CPU es %fs", t2CPU - t1CPU);
	printf("\n\t El tiempo GPU(A) es %fs", t2GPU - t1GPU);

	//-----------------------------
	//apartado B)
	//-----------------------------
	
	int *mA, *mB, *mR;
	int *d_2A, *d_2B, *d_2R;
	int tam = N * N;

	mA = (int*)malloc(tam*sizeof(int));
	mB = (int*)malloc(tam*sizeof(int));
	mR = (int*)malloc(tam*sizeof(int));

	for(i=0;i<tam;i++){
		mA[i] = rand()%9;
		mB[i] = rand()%9;
		mR[i] = 0;
	}

	//reserva de memoria
	cudaMalloc((void**)&d_2A, tam*sizeof(d_2A));
	cudaMemset(d_2A, 0, tam*sizeof(d_2A));
	cudaMalloc((void**)&d_2B, tam*sizeof(d_2B));
	cudaMemset(d_2B, 0, tam*sizeof(d_2B));
	cudaMalloc((void**)&d_2R, tam*sizeof(d_2R));
	cudaMemset(d_2R, 0, tam*sizeof(d_2R));

	//copiamos
	cudaMemcpy(d_2A, mA, tam*sizeof(int), cudaMemcpyHostToDevice);
	cudaMemcpy(d_2B, mB, tam*sizeof(int), cudaMemcpyHostToDevice);

	//llamamos al kernel
	t1GPU = omp_get_wtime();
	add2Vectors<<<1024,64>>>(d_2A, d_2B, d_2R);
	t2GPU = omp_get_wtime();

	//resultados 2
	printf("\n\t El tiempo CPU es %fs", t2CPU - t1CPU);
	printf("\n\t El tiempo GPU(B) es %fs\n", t2GPU - t1GPU);

	cudaMemcpy(mR, d_2R, tam*sizeof(int), cudaMemcpyDeviceToHost);
}
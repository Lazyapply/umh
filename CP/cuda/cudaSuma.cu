#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <cuda_runtime.h>


//device (1)
__global__ void suma_2_enteros(int *d1, int *d2, int *sum){
	*sum = *d1 + *d2;
}

//HOST
int main(int argc, char **argv){

	int DeviceCount = 0;
	int h_d1, h_d2, h_sum; //HOST
	int *d_d1, *d_d2, *d_sum; //DEVICE (2)

	h_d1 = atoi(argv[1]);
	h_d2 = atoi(argv[2]);

	//inicializamos CUDA
	if(cuInit(0) != 0){
		printf("ERROR en la inicializacion de CUDA\n");
		exit(0);
	}

	cuDeviceGetCount(&DeviceCount);
	if(DeviceCount == 0){
		printf("ERROR, ningun dispositivo compatible con CUDA\n");
		exit(0);
	}


	//reservamos memoria en DEVICE (2.1)
	cudaMalloc((void**)&d_d1, sizeof(d_d1));
	cudaMalloc((void**)&d_d2, sizeof(d_d2));
	cudaMalloc((void**)&d_sum, sizeof(d_sum));

	//copiamos desde HOST --> DEVICE (3)
	cudaMemcpy(d_d1, &h_d1, sizeof(h_d1), cudaMemcpyHostToDevice);
	cudaMemcpy(d_d2, &h_d2, sizeof(h_d2), cudaMemcpyHostToDevice);


	//llamamos al KERNEL
	suma_2_enteros<<<1,1,0,0>>>(d_d1, d_d2, d_sum);


	//recogemos los resultados del DEVICE (DEVICE --> HOST) (4)
	cudaMemcpy(&h_sum, d_sum, sizeof(h_sum), cudaMemcpyDeviceToHost);

	printf("Resultado: %d\n", h_sum);

	cudaFree(d_d1);
	cudaFree(d_d2);
	cudaFree(d_sum);
}
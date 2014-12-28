#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>

//device
__global__ void primer_kernel(){}


//host
int main(int argc, char *argv[]){
	int DeviceCount = 0;

	//inicializamos CUDA
	if(cuInit(0) != 0){
		printf("ERROR en la inicializacion\n");
		exit(0);
	}

	//obtenemos el numero de dispositivos compatibles con CUDA
	cuDeviceGetCount(&DeviceCount);
	if(DeviceCount == 0){
		printf("ERROR, ningun dispositivo soporta CUDA\n");
		return EXIT_FAILURE;
	}

	//llamamos al codigo del kernel
	primer_kernel<<<1,1,0,0>>>();
	printf("Se dispone de %d unidad(es) GPU\n", DeviceCount);
}
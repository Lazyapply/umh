
/* Includes, system */
#include <stdio.h>

#include <cuda.h>
#include <cuda_runtime.h>

/* DEVICE CODE */
__global__ void suma_2_enteros(int *d1, int *d2, int *sum){
	*sum = *d1 + *d2;
}

/* HOST CODE*/
int main(int argc, char** argv)
{
    int DeviceCount = 0;
    int h_d1,h_d2,h_sum;
    int *d_d1,*d_d2,*d_sum;

    h_d1 = 2; h_d2 = 3;
    /* Initialize CUDA */
    if (cuInit(0) != 0){
        printf("ERROR de inicializacion\n");
        exit(0);
        }
    cuDeviceGetCount(&DeviceCount);
    if (DeviceCount == 0){
        printf("ERROR ningun dispositivo soporta CUDA\n");
        exit(0);
        }

    cudaMalloc((void**)&d_d1, sizeof(d_d1));
    cudaMalloc((void**)&d_d2, sizeof(d_d2));
    cudaMalloc((void**)&d_sum, sizeof(d_sum));


    cudaMemcpy(d_d1,&h_d1,sizeof(h_d1),cudaMemcpyHostToDevice);
    cudaMemcpy(d_d2,&h_d2,sizeof(h_d2),cudaMemcpyHostToDevice);

     suma_2_enteros<<<1,1>>>(d_d1,d_d2,d_sum);

     cudaMemcpy(&h_sum,d_sum,sizeof(h_sum),cudaMemcpyDeviceToHost);

     printf("Resultado: %d \n",h_sum);
     cudaFree(d_d1);cudaFree(d_d2);cudaFree(d_sum);
}

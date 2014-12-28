
/* Includes, system */
#include <stdio.h>

#include <cuda.h>
#include <cuda_runtime.h>

/* DEVICE CODE */
__global__ void primer_kernel(){
}

/* HOST CODE*/
int main(int argc, char** argv)
{
    int DeviceCount = 0;

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
  primer_kernel<<<1,1,0,0>>>();
  printf("Se dispone de %d unidade(s) GPU.\n",DeviceCount);

}

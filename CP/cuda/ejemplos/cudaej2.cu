
/* Includes, system */
#include <stdio.h>

/* DEVICE CODE */
__global__ void primer_kernel(){
}


/* HOST CODE*/
int main(int argc, char** argv)
{
  primer_kernel<<<1,1,0,0>>>();
  printf("Para ser original -- HOLA MUNDO\n");

}

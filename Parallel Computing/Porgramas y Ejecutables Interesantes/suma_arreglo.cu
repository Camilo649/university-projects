#include <stdio.h>
#include <cuda_runtime.h>

// Función del kernel que suma los elementos del arreglo
__global__ void suma_arreglo(float *a, size_t tam) {
    __shared__ float suma_par;

    size_t gtid = blockIdx.x * blockDim.x + threadIdx.x;	//global id
    size_t tid  = threadIdx.x;		// thread id, dentro del bloque
    size_t lid  = tid%warpSize;		// lane id, dentro del warp

    // Fase 1, inicialización
    if (tid==0)
    	suma_par = 0.0f;
    __syncthreads();

    // Fase 2, cómputo dentro del bloque
    float warp_reduce = a[gtid];

    // Fase 2.1, suma en warp
    #define FULL_MASK 0xffffffff
    warp_reduce += __shfl_down_sync(FULL_MASK, warp_reduce, 16);
    warp_reduce += __shfl_down_sync(FULL_MASK, warp_reduce, 8);
    warp_reduce += __shfl_down_sync(FULL_MASK, warp_reduce, 4);
    warp_reduce += __shfl_down_sync(FULL_MASK, warp_reduce, 2);
    warp_reduce += __shfl_down_sync(FULL_MASK, warp_reduce, 1);

    // Fase 2.2, acumulacion a shared
    if (lid==0) {
	atomicAdd(&suma_par, warp_reduce);
    }
    __syncthreads();

    // Fase 3, acumulación del resultado local del bloque en la global
    if (tid==0)
    	atomicAdd(&a[0], suma_par);
}



int main() {
    size_t tam = 1L<<31; // Tamaño del arreglo

    float *d_a;
    cudaMalloc((void **)&d_a, tam * sizeof(float));

    // Configuramos los bloques y hilos para la ejecución del kernel
    suma_arreglo<<<tam/128L, 128>>>(d_a, tam);

    // Esperamos a que el kernel termine
    cudaDeviceSynchronize();
    float suma_total;
    cudaMemcpy(&suma_total, d_a, sizeof(float), cudaMemcpyDeviceToHost);


    // Imprimimos la suma total
    printf("La suma total es: %f\n", suma_total);

    // Liberamos la memoria
    cudaFree(d_a);
    return 0;
}

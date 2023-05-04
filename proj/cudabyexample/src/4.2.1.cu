#include "../common/book.h"
#include "../common/timer.h"
#define N 50000

void add(int *a, int *b, int *c)
{
    int tid = 0; // this is CPU zero, so we start at zero
    while (tid < N)
    {
        c[tid] = a[tid] + b[tid];
        tid += 1; // we have one CPU, so we increment by one
    }
}

__global__ void gpuadd(int *a, int *b, int *c)
{
    int tid = blockIdx.x; // handle the data at this index
    if (tid < N)
        c[tid] = a[tid] + b[tid];
}

int main(void)
{
    int a[N], b[N], c[N];
    // fill the arrays 'a' and 'b' on the CPU
    for (int i = 0; i < N; i++)
    {
        a[i] = -i;
        b[i] = i * i;
    }
    PriciseTimer timer;
    timer.start();
    add(a, b, c);
    timer.end();
    timer.print_time();
    // display the results
    // for (int i = 0; i < N; i++)
    // {
    //     printf("%d + %d = %d\n", a[i], b[i], c[i]);
    // }

    int *dev_a, *dev_b, *dev_c;
    // allocate the memory on the GPU
    HANDLE_ERROR(cudaMalloc((void **)&dev_a, N * sizeof(int)));
    HANDLE_ERROR(cudaMalloc((void **)&dev_b, N * sizeof(int)));
    HANDLE_ERROR(cudaMalloc((void **)&dev_c, N * sizeof(int)));
    // fill the arrays 'a' and 'b' on the CPU
    for (int i = 0; i < N; i++)
    {
        a[i] = -i;
        b[i] = i * i;
    }

    // copy the arrays 'a' and 'b' to the GPU
    HANDLE_ERROR(cudaMemcpy(dev_a, a, N * sizeof(int),
                            cudaMemcpyHostToDevice));
    HANDLE_ERROR(cudaMemcpy(dev_b, b, N * sizeof(int),
                            cudaMemcpyHostToDevice));
    timer.start();
    gpuadd<<<N, 1>>>(dev_a, dev_b, dev_c);
    timer.end();
    timer.print_time();
    // copy the array 'c' back from the GPU to the CPU
    HANDLE_ERROR(cudaMemcpy(c, dev_c, N * sizeof(int),
                            cudaMemcpyDeviceToHost));

    // // display the results
    // for (int i = 0; i < N; i++)
    // {
    //     printf("%d + %d = %d\n", a[i], b[i], c[i]);
    // }

    // free the memory allocated on the GPU
    cudaFree(dev_a);
    cudaFree(dev_b);
    cudaFree(dev_c);
    return 0;
}
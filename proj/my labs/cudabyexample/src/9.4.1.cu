#include "../common/book.h"

#define SIZE (100 * 1024 * 1024)
int main(void)
{

    unsigned char *buffer = (unsigned char *)big_random_block(SIZE);
    unsigned int histo[256];
    auto start_time = clock();
    for (int i = 0; i < 256; i++)
        histo[i] = 0;
    for (int i = 0; i < SIZE; i++)
        histo[buffer[i]]++;
    long histoCount = 0;
    for (int i = 0; i < 256; i++)
    {
        histoCount += histo[i];
    }

    auto end_time = clock();
    double cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("time cost %f s\n", cpu_time_used);

    printf("Histogram Sum: %ld\n", histoCount);
    free(buffer);
    return 0;
}
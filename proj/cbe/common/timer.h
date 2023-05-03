#ifndef __TIMER_H__
#define __TIMER_H__
#include <time.h>
#include <chrono>

class Timer
{
public:
    void start()
    {
        start_time = clock();
    }

    void end()
    {
        end_time = clock();
    }

    void print_time()
    {
        double cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("time cost %f s\n", cpu_time_used);
    }

private:
    clock_t start_time;
    clock_t end_time;
};

class PriciseTimer
{
private:
    std::chrono::_V2::system_clock::time_point start_time;
    std::chrono::_V2::system_clock::time_point end_time;
public:

void start()
    {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void end()
    {
        end_time = std::chrono::high_resolution_clock::now();
    }

    void print_time()
    {
        std::chrono::duration<double> elapsed = end_time - start_time;
        printf("time cost %f s\n", elapsed.count());
    }
};



#endif // __TIMER_H__
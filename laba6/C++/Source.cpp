#include "pch.h"      
#include "Header.h"   
#include <vector>
#include <ctime>      
#include <cstdlib>    

double scalar_proizv(double* v1, double* v2, int vector_size, int iterations) {

    volatile double total_result = 0.0;

    clock_t start_time = clock();

    for (int k = 0; k < iterations; ++k) {
        double dot_product = 0.0;

        for (int i = 0; i < vector_size; ++i) {
            dot_product += v1[i] * v2[i];
        }

        total_result += dot_product;
    }

    clock_t end_time = clock();

    return (double)(end_time - start_time) / CLOCKS_PER_SEC;
}
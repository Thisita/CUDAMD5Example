/*
    CUDAMD5Example
    Copyright © 2014 Ian Zachary Ledrick, also known as Thisita.
    
    This file is part of CUDAMD5Example.

    CUDAMD5Example is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CUDAMD5Example is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with CUDAMD5Example.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include "md5kernel.h"
#include "md5.h"

int main(int argc, char **argv) {
    char *msg = argv[1];
    size_t len;
    int i;
    uint8_t result[16];
	cudaError_t cudaStatus;
 
    if (argc < 2) {
        printf("usage: %s 'string'\n", argv[0]);
        return 1;
    }
 
    len = strlen(msg);
 
    // benchmark
    for (i = 0; i < 100; i++) {
        md5((uint8_t*)msg, len, result);
    }
 
    // display result
    for (i = 0; i < 16; i++)
        printf("%2.2x", result[i]);
    puts("");
    
    // cudaDeviceReset must be called before exiting in order for profiling and
    // tracing tools such as Nsight and Visual Profiler to show complete traces.
    cudaStatus = cudaDeviceReset();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceReset failed!");
        return 1;
    }
    
    return 0;
}


/** original main **/
#if 0
int main()
{
    const int arraySize = 5;
    const int a[arraySize] = { 1, 2, 3, 4, 5 };
    const int b[arraySize] = { 10, 20, 30, 40, 50 };
    int c[arraySize] = { 0 };

    // Add vectors in parallel.
    cudaError_t cudaStatus = md5WithCuda(c, a, b, arraySize);
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "addWithCuda failed!");
        return 1;
    }

    printf("{1,2,3,4,5} + {10,20,30,40,50} = {%d,%d,%d,%d,%d}\n",
        c[0], c[1], c[2], c[3], c[4]);

    // cudaDeviceReset must be called before exiting in order for profiling and
    // tracing tools such as Nsight and Visual Profiler to show complete traces.
    cudaStatus = cudaDeviceReset();
    if (cudaStatus != cudaSuccess) {
        fprintf(stderr, "cudaDeviceReset failed!");
        return 1;
    }

    return 0;
}
#endif
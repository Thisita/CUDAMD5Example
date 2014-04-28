#pragma once

#include "cuda_runtime.h"

cudaError_t addWithCuda(int *c, const int *a, const int *b, unsigned int size);
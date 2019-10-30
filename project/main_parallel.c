#include <stdio.h>
#include <stdlib.h>
#include "parallel.h"

int main(int argc, char const *argv[]) {
    double * sum_vector_parallel = parallel_sum_calculation("project/test/data/in3.txt");
    free(sum_vector_parallel);
    return 0;
}
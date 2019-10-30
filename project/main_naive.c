#include <stdio.h>
#include <stdlib.h>
#include "naive.h"

int main(int argc, char const *argv[]) {
    NAIVE_matrix * A = create_matrix_from_file("project/test/data/in3.txt");
    double * sum_vector_naive = naive_sum_calculation(A);
    free_matrix(A);
    free(sum_vector_naive);
    return 0;
}
#ifndef PROJECT_NAIVE_NAIVE_H_
#define PROJECT_NAIVE_NAIVE_H_

#define NAIVE_NULL -1
#define NAIVE_OK 0

typedef struct NAIVE_matrix {
    double ** data;
    size_t  rows;
    size_t  cols;
} NAIVE_matrix;

NAIVE_matrix * create_matrix_from_file(const char * path_file);
NAIVE_matrix * create_matrix(size_t rows, size_t cols);
int free_matrix(NAIVE_matrix * matrix);

double * naive_sum_calculation(const NAIVE_matrix * matrix);

#endif  // PROJECT_NAIVE_NAIVE_H_

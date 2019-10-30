#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "naive.h"

double * naive_sum_calculation(const NAIVE_matrix * matrix) {
    double * sum_vector = (double *)calloc(matrix->cols, sizeof(double));
    for (size_t j = 0; j != matrix->cols; j++) {
        for (size_t i = 0; i != matrix->rows; i++) {
            sum_vector[j] += matrix->data[i][j];
        }
    }
    return sum_vector;
}

NAIVE_matrix * create_matrix_from_file(const char * path_file) {
    FILE * ptr_file = fopen(path_file, "r");
    if (ptr_file == NULL) {
        return NULL;
    }
    size_t rows = 0;
    size_t cols = 0;
    if (fscanf(ptr_file, "%zu %zu", &rows, &cols) != 2) {
        fclose(ptr_file);
        return NULL;
    }

    NAIVE_matrix * matrix = create_matrix(rows, cols);
    if (matrix == NULL) {
        fclose(ptr_file);
        return NULL;
    }
    double elem = 0;
    for (size_t i = 0; i != rows; i++) {
        for (size_t j = 0; j != cols; j++) {
            if (fscanf(ptr_file, "%lf", &elem) != 1) {
                free_matrix(matrix);
                fclose(ptr_file);
                return NULL;
            }
            matrix->data[i][j] = elem;
        }
    }
    fclose(ptr_file);
    return matrix;
}

NAIVE_matrix * create_matrix(size_t rows, size_t cols) {
    NAIVE_matrix * matrix = (NAIVE_matrix *)calloc(1, sizeof(NAIVE_matrix));
    if (matrix == NULL) {
        return NULL;
    }
    matrix->data = (double **)calloc(rows, sizeof(double *));
    if (matrix->data == NULL) {
        free(matrix);
        return NULL;
    }
    for (size_t i = 0; i != rows; i++) {
        matrix->data[i] = (double *)calloc(cols, sizeof(double));
        if ((matrix->data[i]) == NULL) {
            free_matrix(matrix);
            return NULL;
        }
    }
    matrix->cols = cols;
    matrix->rows = rows;
    return matrix;
}

int free_matrix(NAIVE_matrix * matrix) {
    if (matrix == NULL) {
        return NAIVE_NULL;
    }
    for (size_t i = 0; i != matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
    return NAIVE_OK;
}

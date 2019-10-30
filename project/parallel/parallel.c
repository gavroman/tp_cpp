#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#include "parallel.h"

double * parallel_sum_calculation(const char * filename) {
    FILE * ptr_file = fopen(filename, "r");
    if (ptr_file == NULL) {
        return NULL;
    }
    int fd[2];
    if (pipe(fd) < 0) {
        fclose(ptr_file);
        return NULL;
    }
    size_t rows = 0;
    size_t cols = 0;
    if (fscanf(ptr_file, "%zu %zu", &rows, &cols) != 2) {
        fclose(ptr_file);
        return NULL;
    }

    const int process_number = 4;
    int n_per_poroc = rows / process_number;
    int last = rows % process_number;

    int rows_per_process[process_number];
    for (int i = 0; i != process_number; i++) {
        rows_per_process[i] = n_per_poroc;
        if (last) {
            rows_per_process[i]++;
            last--;
        }
    }

    double * sum_vector = (double *)calloc(cols, sizeof(double));
    size_t vector_size = cols * sizeof(double);
    pid_t pid = 0;
    for (size_t k = 0; k != process_number; k++) {
        PRL_matrix_chunk * chunk = create_matrix_chunk_from_file(ptr_file, rows_per_process[k], cols);
        pid = fork();
        if (pid == -1) {
            close(fd[0]);
            close(fd[1]);
            free(sum_vector);
            fclose(ptr_file);
            free_matrix_chunk(chunk);
            return NULL;
        }
        if (pid == 0) {
            for (size_t i = 0; i != rows_per_process[k]; i++) {
                for (size_t j = 0; j != cols; j++) {
                    sum_vector[j] += chunk->data[i][j];
                }
            }
            write(fd[1], sum_vector, vector_size);
            close(fd[0]);
            close(fd[1]);
            free_matrix_chunk(chunk);
            free(sum_vector);
            fclose(ptr_file);
            exit(0);
        }
        free_matrix_chunk(chunk);
    }

    double * read_vector = (double *)calloc(cols, sizeof(double));
    for (size_t i = 0; i != process_number; i++) {
        read(fd[0], read_vector, vector_size);
        for (size_t j = 0; j != cols; j++) {
            sum_vector[j] += read_vector[j];
        }
    }

    close(fd[0]);
    close(fd[1]);
    fclose(ptr_file);
    free(read_vector);
    int status = 0;
    wait(&status);

    return sum_vector;
}

PRL_matrix_chunk * create_matrix_chunk_from_file(FILE * ptr_file, const size_t rows, const size_t cols) {
    if (ptr_file == NULL) {
        return NULL;
    }

    PRL_matrix_chunk * chunk = create_matrix_chunk(rows, cols);
    if (chunk == NULL) {
        return NULL;
    }
    double elem = 0;
    for (size_t i = 0; i != rows; i++) {
        for (size_t j = 0; j != cols; j++) {
            if (fscanf(ptr_file, "%lf", &elem) != 1) {
                free_matrix_chunk(chunk);
                return NULL;
            }
            chunk->data[i][j] = elem;
        }
    }
    return chunk;
}

PRL_matrix_chunk * create_matrix_chunk(const size_t rows, const size_t cols) {
    PRL_matrix_chunk * chunk = (PRL_matrix_chunk *)calloc(1, sizeof(PRL_matrix_chunk));
    if (chunk == NULL) {
        return NULL;
    }
    chunk->data = (double **)calloc(rows, sizeof(double *));
    if (chunk->data == NULL) {
        free(chunk);
        return NULL;
    }
    for (size_t i = 0; i != rows; i++) {
        chunk->data[i] = (double *)calloc(cols, sizeof(double));
        if ((chunk->data[i]) == NULL) {
            free_matrix_chunk(chunk);
            return NULL;
        }
    }
    chunk->cols = cols;
    chunk->rows = rows;
    return chunk;
}

int free_matrix_chunk(PRL_matrix_chunk * chunk) {
    if (chunk == NULL) {
        return PRL_NO_CHUNK;
    }
    for (size_t i = 0; i != chunk->rows; i++) {
        free(chunk->data[i]);
    }
    free(chunk->data);
    free(chunk);
    return PRL_OK;
}


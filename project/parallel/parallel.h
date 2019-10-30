#ifndef PROJECT_PARALLEL_PARALLEL_H_
#define PROJECT_PARALLEL_PARALLEL_H_

#define PRL_READ_ERROR -5
#define PRL_NO_CHUNK -4
#define PRL_NO_PIPE -3
#define PRL_NO_FILE -2
#define PRL_NO_CHILD -1
#define PRL_OK 0

typedef struct PRL_matrix_chunk {
    double ** data;
    size_t  rows;
    size_t  cols;
} PRL_matrix_chunk;

int * calculate_process_number(size_t rows);
double * parallel_sum_calculation(const char * filename);

PRL_matrix_chunk * create_matrix_chunk(const size_t rows, const size_t cols);
PRL_matrix_chunk * create_matrix_chunk_from_file(FILE * ptr_file, const size_t rows, const size_t cols);
int free_matrix_chunk(PRL_matrix_chunk * chunk);

#endif  // PROJECT_PARALLEL_PARALLEL_H_

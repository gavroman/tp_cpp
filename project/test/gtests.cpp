#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <gtest/gtest.h>

extern "C" {
    #include "naive.h"
    #include "parallel.h"
}

void compare_algorithms(size_t cols, const std::string & file_name) {
    using namespace std::chrono;

    unsigned int time1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    NAIVE_matrix * A = create_matrix_from_file(file_name.c_str());
    double * sum_vector_naive = naive_sum_calculation(A);
    free_matrix(A);
    unsigned int time2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    double * sum_vector_parallel = parallel_sum_calculation(file_name.c_str());
    unsigned int time3 = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    std::cout << "Naive algorithm time: "<< time2 - time1 << "ms" << std::endl;
    std::cout << "Parallel algorithm time: "<< time3 - time2 << "ms" << std::endl;

    const double epsilon = 0.01;
    for (int i = 0; i != cols; i++) {
        if (std::fabs(sum_vector_parallel[i] - sum_vector_naive[i]) > epsilon) {
            std::cout << i << "  " << sum_vector_parallel[i] << " " << sum_vector_naive[i] << std::endl;
            GTEST_FAIL() << "Elements differ more then epsilon";
        }
    }
    free(sum_vector_naive);
    free(sum_vector_parallel);
}

// case 1 8x8
TEST(matrix_col_sum, compare1) {
    std::cout << "Case 1, matrix 8x8" << std::endl;
    compare_algorithms(8, "project/test/data/in1.txt");
}

// case 2 10000x5000  (GitHub reject files > 100 Mb)
// TEST(matrix_col_sum, compare2) {
//     std::cout << "Case 2, matrix 10000x5000" << std::endl;
//     compare_algorithms(5000, "project/test/data/in2gitnopush.txt");
// }

// case 3 1500x1193
TEST(matrix_col_sum, compare3) {
    std::cout << "Case 3, matrix 1500x1193" << std::endl;
    compare_algorithms(1193, "project/test/data/in3.txt");
}

// case 4 1500x1000
TEST(matrix_col_sum, compare4) {
    std::cout << "Case 4, matrix 1500x1000" << std::endl;
    compare_algorithms(1000, "project/test/data/in4.txt");
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}